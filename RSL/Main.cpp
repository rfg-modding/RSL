#include "Launcher.h"
#include "IpcManager.h"
#include "CameraManager.h"
#include "FunctionManager.h"
#include "HookManager.h"
#include "SnippetManager.h"
#include "ScriptManager.h"
#include "GuiManager.h"

DWORD WINAPI MainThread(HMODULE hModule);
DWORD WINAPI LauncherThread(HMODULE hModule);
HANDLE LauncherThreadHandle;
void BuildIocContainer();

/* This function is the first thing called when the script loader DLL is loaded into rfgr.
 * All it does is start a new thread which runs MainThread. You shouldn't do anything major
 * in DllMain, especially not load other DLLs, as it can apparently cause unstable behavior
 * and crashes due to the way windows handles DLL loading. You should instead place your code
 * in MainThread or some function it calls.
 */
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason != DLL_PROCESS_ATTACH)
        return TRUE;

    Globals::PID = GetCurrentProcessId();
    Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    BuildIocContainer();
#if UseLauncher

    //First, check for txt files which skip the launcher. Workaround until bugs with the launcher running can be fixed
    if(fs::exists(Globals::GetEXEPath() + "\\RSL_No_Launcher.txt")) //Skip launcher, run with RSL
    {
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
    }
    else if(fs::exists(Globals::GetEXEPath() + "\\Vanilla_No_Launcher.txt")) //Skip launcher, run vanilla game
    {
        return TRUE;
    }
    else //If neither file is found, start the launcher like normal
    {
        LauncherThreadHandle = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LauncherThread), hModule, 0, 0);
    }

#else

    CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);

#endif
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
        //Todo: Maybe consider letting the script loader thread init, and do all it's hooking, and then resuming the games threads. This should allow early code patches and hooks.
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
    }
    else
    {
        Globals::ResumeAllThreads();
    }

    ExitThread(0);
}

void BuildIocContainer()
{
    Hypodermic::ContainerBuilder builder;
    builder.registerType<IpcManager>().as<IIpcManager>().singleInstance();
    builder.registerType<SnippetManager>().as<ISnippetManager>().singleInstance();
    builder.registerType<CameraManager>().as<ICameraManager>().singleInstance();
    builder.registerType<FunctionManager>().as<IFunctionManager>().singleInstance();
    builder.registerType<ScriptManager>().as<IScriptManager>().singleInstance();
    builder.registerType<HookManager>().as<IHookManager>().singleInstance();
    builder.registerType<GuiManager>().as<IGuiManager>().singleInstance();

    IocContainer = builder.build();
}
