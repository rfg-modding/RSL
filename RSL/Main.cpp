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
void InitLogger();

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

    InitLogger();

    Logger::Log("Getting PID.\n");
    Globals::PID = GetCurrentProcessId();
    Logger::Log("Getting module base address.\n");
    Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    Logger::Log("Building IoC container.\n");
    BuildIocContainer();

    //First, check for txt files which skip the launcher. Workaround until bugs with the launcher running can be fixed
    if(fs::exists(Globals::GetEXEPath() + "\\RSL_No_Launcher.txt")) //Skip launcher, run with RSL
    {
        Logger::Log("Found \"RSL_No_Launcher.txt\". Starting RSL main thread without displaying launcher.\n");
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
    }
    else if(fs::exists(Globals::GetEXEPath() + "\\Vanilla_No_Launcher.txt")) //Skip launcher, run vanilla game
    {
        Logger::Log("Found \"Vanilla_No_Launcher.txt\". Starting vanilla game without loading the RSL.\n");
        return TRUE;
    }
    else //If neither file is found, start the launcher like normal
    {
        Logger::Log("No override files found. Opening launcher.\n");
        LauncherThreadHandle = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LauncherThread), hModule, 0, 0);
    }
    return TRUE;
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    Logger::Log("Entered RSL main thread.\n");
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
    Logger::Log("Entered launcher thread.\n");
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

void InitLogger()
{
    try
    {
        Logger::Init(LogAll, Globals::GetEXEPath(false) + "RSL/Logs/", 1000);
        Logger::OpenLogFile("Load Log.log", LogAll, std::ios_base::trunc);
        Logger::OpenLogFile("Master Log.log", LogAll, std::ios_base::trunc);
        Logger::Log("RSL started. Activating.\n");
    }
    catch (std::exception& Ex)
    {
        std::string MessageBoxString = R"(Exception detected during Logger initialization! Please show this to the current script loader maintainer. It's much harder to fix any further problems which might occur without logs.)";
        MessageBoxString += Ex.what();
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Logger failed to initialize!", MB_OK);
        Logger::CloseAllLogFiles();
    }
}