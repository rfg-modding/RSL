#include "Launcher.h"

// Launcher is disabled for now due to it (for some unknown reason) causing issues with multiplayer even when the vanilla game option is selected.
#define UseLauncher false

DWORD WINAPI MainThread(HMODULE hModule);
DWORD WINAPI LauncherThread(HMODULE hModule);
HANDLE LauncherThreadHandle;

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
        Globals::PID = GetCurrentProcessId();
        Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
#if UseLauncher
        std::cout << "Starting launcher thread...\n";
        LauncherThreadHandle = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LauncherThread), hModule, 0, 0);
        //Todo: Test if different flags/permissions passed to the threads would help fix some bugs/crashes ^^
#else
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
#endif

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
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Uncaught exception in RSL main thread!", MB_OK);
    }
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI LauncherThread(HMODULE hModule)
{
    Launcher RslLauncher(LauncherThreadHandle, hModule);
    RslLauncher.Run();

    if(Globals::Launcher::ShouldRunRsl)
    {
        //Todo: Dunno if the message below still applies...
        //Todo: ResumeAllThreads should be called after RSL init in the RSL thread. That way it can init safely then re-enabled threads.
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
    }

    ExitThread(0);
}