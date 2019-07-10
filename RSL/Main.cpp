#include "Application.h"
#include <tlhelp32.h>

DWORD WINAPI MainThread(HMODULE hModule);

void LockGameMain();
void UnlockGameMain();
void SuspendAllThreadsExceptLauncher();
void ResumeAllThreads();
DWORD WINAPI LauncherThread(HMODULE hModule);


bool ShouldLoadRSL = false;
bool LauncherDone = false;
HANDLE LauncherThreadHandle = nullptr;
std::vector<HANDLE> RfgThreadHandles;

/* This function is the first thing called when the script loader DLL is loaded into rfgr.
 * All it does is start a new thread which runs MainThread. You shouldn't do anything major
 * in DllMain, especially not load other DLLs, as it can apparently cause unstable behavior
 * and crashes due to the way windows handles DLL loading. You should instead place your code
 * in MainThread or some function it calls.
 */
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        printf("Getting PID...\n");
        Globals::PID = GetCurrentProcessId();
        printf("PID value: %i", Globals::PID);
        printf("Getting ModuleBase...\n");
        Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
        printf("ModuleBase value: %#010x\n", Globals::ModuleBase);
        printf("Locking rfg WinMain...\n");
        //LockGameMain(); //Patch rfg's WinMain func to infinitely loop so we can safely patch and hook the game.
        printf("Locked rfg WinMain!\n");
        printf("Creating Launcher thread...\n");
        LauncherThreadHandle = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LauncherThread), hModule, 0, 0);

        //while(!LauncherDone)
        //{
        //    //Sleep(1000);
        //    printf("Waiting for launcher thread to exit....\n");
        //}
        //if(ShouldInjectRSL)
        //{
        //    CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
        //}
        break;
    default:
        break;
    }
    return TRUE;
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    Globals::ScriptLoaderModule = hModule;
    Application RSL;

    try
    {
        RSL.Run();
    }
    catch (std::exception& Ex)
    {
        std::string MessageBoxString = R"(Uncaught exception in RSL main thread! Message: )";
        MessageBoxString += Ex.what();
        Logger::LogFatalError("{}\n", MessageBoxString);
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Uncaught exception in RSL main thread!", MB_OK);
    }
    FreeLibraryAndExitThread(hModule, 0);
}

void LockGameMain()
{
    //.text:019D0E80 rfg.exe:$810E80 #810280 <WinMain>
    DWORD RFGWinMainAddress = Globals::FindPattern("rfg.exe", "\x8B\x4C\x24\x3C\x53\x33\xDB\xBA", "xxxxxxxx");
    printf("RfgWinMain patch target address: %#010x\n", RFGWinMainAddress);
    printf("RfgWinMain patch target address static casted to int: %#010x\n", static_cast<int>(RFGWinMainAddress));
    printf("RfgWinMain patch target address static casted to BYTE: %#010x\n", static_cast<BYTE>(RFGWinMainAddress));

    //DWORD RFGWinMainAddress = static_cast<DWORD>(Globals::ModuleBase + static_cast<DWORD>(0x810E80) + static_cast<DWORD>(0x12));
    //std::vector<int> NewOpcodes{NOP, JMP_REL8, static_cast<int>(RFGWinMainAddress), NOP};
    std::vector<int> NewOpcodes{NOP, JMP_REL8, 0xFD, NOP};
    SnippetManager::ReplaceSnippet("RFG WinMain", RFGWinMainAddress, NewOpcodes);
}

void UnlockGameMain()
{
    SnippetManager::RestoreSnippet("RFG WinMain", true);
}

/*Be VERY VERY careful with this function or else you might crash your PC or every program it's running.*/
void SuspendAllThreadsExceptLauncher()
{
    const DWORD LauncherThreadID = GetThreadId(LauncherThreadHandle);
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (h != INVALID_HANDLE_VALUE) 
    {
        THREADENTRY32 te;
        te.dwSize = sizeof(te);
        if (Thread32First(h, &te)) 
        {
            do 
            {
                if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID)) 
                {
                    if(te.th32OwnerProcessID == Globals::PID)
                    {
                        if(te.th32ThreadID != LauncherThreadID)
                        {
                            HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
                            RfgThreadHandles.push_back(ThreadHandle);
                            if(ThreadHandle)
                            {
                                SuspendThread(ThreadHandle);
                            }
                        }
                        //printf("Process 0x%04x Thread 0x%04x\n", te.th32OwnerProcessID, te.th32ThreadID);
                        //if(te.th32ThreadID == LauncherThreadID)
                        //{
                        //    printf("^^^That's the launcher thread!\n");
                        //}
                    }
                }
                te.dwSize = sizeof(te);
            } while (Thread32Next(h, &te));
        }
        CloseHandle(h);
    }
}

void ResumeAllThreads()
{
    for(auto& i : RfgThreadHandles)
    {
        ResumeThread(i);
    }
}

LRESULT __stdcall LauncherWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case 0:
            ShouldLoadRSL = true;
            PostQuitMessage(0);
            break;
        case 1:
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

bool LauncherMainLoop(HMODULE hModule)
{
    const char* ClassName = "RSL Launcher Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = LauncherWndProc;
    wc.hInstance = hModule;
    wc.lpszClassName = ClassName;

    RegisterClass(&wc);

    HWND LauncherHwnd = CreateWindowEx(
        0,                              // Optional window styles.
        ClassName,                     // Window class
        "RSL Launcher",    // Window text
        WS_OVERLAPPED,            // Window style

        // Size and position
        1000, 400, 300, 500,

        nullptr,       // Parent window    
        nullptr,       // Menu
        hModule,  // Instance handle
        nullptr        // Additional application data
    );

    if (!LauncherHwnd)
    {
        return false;
    }

    auto TopStaticText = CreateWindow("Static", "Choose whether or not to load the RSL into RFG.", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 20, 200, 40, LauncherHwnd, static_cast<HMENU>(0), hModule, nullptr);
    auto Button0 = CreateWindow("Button", "Play with RSL (MP Disabled)", BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE, 50, 70, 200, 30, LauncherHwnd, static_cast<HMENU>(0), hModule, nullptr);
    auto Button1 = CreateWindow("Button", "Play vanilla Re-mars-tered", BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE, 50, 110, 200, 30, LauncherHwnd, reinterpret_cast<HMENU>(1), hModule, nullptr);

    ShowWindow(LauncherHwnd, SW_SHOW);
    UpdateWindow(LauncherHwnd);

    MSG msg;// = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //return msg.wParam;
    return true;
}

DWORD WINAPI LauncherThread(HMODULE hModule)
{
    printf("Entered launcher thread...\n");
    printf("Sleeping all threads except launcher thread!\n");
    SuspendAllThreadsExceptLauncher();

    printf("Calling LauncherMainLoop()\n");
    LauncherMainLoop(hModule);
    printf("Exited LauncherMainLoop()\n");

    //printf("Sleeping launcher thread for 15 seconds...\n");
    //Sleep(15000);
    //printf("Done sleeping launcher thread. Unlocking rfg WinMain!\n");
    //UnlockGameMain(); //Repatch rfg's WinMain so the game can continue execution as normal.
    //printf("Done unlocking rfg winmain, sleeping for 15 seconds for debug purposes.\n");
    //Sleep(15000);

    ResumeAllThreads();
    if(ShouldLoadRSL)
    {
        //Todo: ResumeAllThreads should be called after RSL init in the RSL thread. That way it can init safely then re-enabled threads. Fix that shit!
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
    }

    LauncherDone = true;
    printf("Exiting launcher thread. Normally at this point the main RSL thread would be started if that option was selected.\n");
    ExitThread(0);
    //FreeLibraryAndExitThread(hModule, 0);
}