#include "Application.h"
#include "ScriptSelectGui.h"
#include "FreeCamGui.h"
#include "MenuBarGui.h"

Application::Application()
{
    IpcManager = IocContainer->resolve<IIpcManager>();
    SnippetManager = IocContainer->resolve<ISnippetManager>();
    CameraManager = IocContainer->resolve<ICameraManager>();
    Hooks = IocContainer->resolve<IHookManager>();
    GuiManager = IocContainer->resolve<IGuiManager>();
}

void Application::Run()
{
    OpenConsole();

    RslBootstrapper.Init();
    MainLoop();
    Exit();
    CloseConsole();
}

//Simple loop that checks for exit conditions occasionally
void Application::MainLoop()
{
    IpcManager->StartIpcThread();

    const ulong UpdatesPerSecond = 1;
    const ulong MillisecondsPerUpdate = 1000 / UpdatesPerSecond;
    Timer timer;

    while (!ShouldClose())
    {
        timer.Start();
        const GameState State = rfg::GameseqGetState();

        if(IsDisabledGameState(State) || *Globals::InMultiplayer)
        {
            Logger::LogFatalError("Wrecking crew and MP are disabled while the RSL is loaded. Exiting.\n");
            MessageBoxA(Globals::FindRfgTopWindow(), 
                "Wrecking crew and MP are disabled while the RSL is loaded. Closing game.", 
                "Disabled mode detected", MB_OK);
            exit(1);
        }
        if(State == GS_MAINMENU)
            Globals::TryHideInvalidMainMenuOptions();
        if (Globals::ScriptLoaderCloseRequested)
            Globals::ExitKeysPressCount = 10;

        if ((void*)(!Globals::HookDidFrame) == nullptr)
        {
            Logger::LogFatalError("Null pointer in RSL callback system, crashing!\n");
            exit(1);
        }

        ulong ElapsedTime = MillisecondsPerUpdate - timer.ElapsedMilliseconds();
        if (ElapsedTime < MillisecondsPerUpdate)
            Sleep(ElapsedTime);
    }
}

void Application::Exit()
{
    if (Globals::OverlayActive || GuiManager->IsLuaConsoleActive())
    {
        SnippetManager->RestoreSnippet("MouseGenericPollMouseVisible", true);
        SnippetManager->RestoreSnippet("CenterMouseCursorCall", true);
    }
    SetWindowLongPtr(Globals::GameWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Globals::OriginalWndProc));
    CameraManager->DeactivateFreeCamera(true);

    rfg::HideHud(false);
    rfg::HideFog(false);

    Hooks->DisableAllHooks();

    ImGui_ImplDX11_InvalidateDeviceObjects();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    //Attempt to disable invulnerability and reset player health.
    if (Globals::PlayerPtr)
    {
        Globals::PlayerPtr->Flags.invulnerable = false;
        Globals::PlayerPtr->HitPoints = 230.0f;
    }

    Beep(900, 100);
    Beep(700, 100);
    Beep(600, 200);

    CloseConsole();

    Logger::Log("RSL deactivated\n");
    Logger::CloseAllLogFiles();
}

bool Application::IsDisabledGameState(GameState State) const
{
    for(const auto& val : DisabledGameStates)
    {
        if (State == val)
            return true;
    }
    return false;
}

bool Application::ShouldClose() const
{
    return Globals::ExitKeysPressCount > 5;
}

void Application::OpenConsole()
{
    if (!Globals::OpenDebugConsole)
        return;

    FILE* pFile = nullptr;
    if (AttachConsole(Globals::PID) == 0)
        AllocConsole();

    freopen_s(&pFile, "CONOUT$", "r+", stdout);
    Globals::ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    Globals::SetConsoleAttributes(Globals::ConsoleDefaultTextAttributes);
}

void Application::CloseConsole() const
{
    FreeConsole();
}