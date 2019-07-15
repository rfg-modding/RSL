#include "Launcher.h"
#include <iostream>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#include <handleapi.h>

void Launcher::Run()
{
    std::cout << "Entered launcher thread...\n";
    std::cout << "Sleeping all threads except launcher thread!\n";
    SuspendAllThreadsExceptLauncher();

    std::cout << "Calling Launcher::MainLoop()\n";
    MainLoop(); //Todo: Check the return value of this and try to add error reporting if the launcher fails to work.
    std::cout << "Exited Launcher::MainLoop()\n";

    //printf("Sleeping launcher thread for 15 seconds...\n");
    //Sleep(15000);
    //printf("Done sleeping launcher thread. Unlocking rfg WinMain!\n");
    //UnlockGameMain(); //Repatch rfg's WinMain so the game can continue execution as normal.
    //printf("Done unlocking rfg winmain, sleeping for 15 seconds for debug purposes.\n");
    //Sleep(15000);

    ResumeAllThreads();
    if (Globals::Launcher::ShouldRunRsl)
    {
        
        
    }

    std::cout << "Exiting launcher thread. Normally at this point the main RSL thread would be started if that option was selected.\n";
}

bool Launcher::MainLoop()
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
            Globals::Launcher::ShouldRunRsl = true;
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

/*Be VERY VERY careful with this function or else you might crash your PC or other programs.*/
void Launcher::SuspendAllThreadsExceptLauncher()
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
                    if (te.th32OwnerProcessID == Globals::PID)
                    {
                        if (te.th32ThreadID != LauncherThreadID)
                        {
                            HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
                            RfgThreadHandles.push_back(ThreadHandle);
                            if (ThreadHandle)
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

void Launcher::ResumeAllThreads()
{
    for (auto& i : RfgThreadHandles)
    {
        ResumeThread(i);
    }
}

