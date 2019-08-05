#include "Application.h"

void Application::Run()
{
    Init();
    MainLoop();
    Exit();
}

void Application::Init()
{
    InitLogger();
    CheckForImproperInstallation();
    InitRSL();
    OpenDefaultLogs();
}

void Application::InitLogger()
{
    try
    {
        Logger::Init(LogAll, Globals::GetEXEPath(false) + "RSL/Logs/", 10000);
        Logger::OpenLogFile("Load Log.txt", LogAll, std::ios_base::trunc);
        Logger::OpenLogFile("Master Log.txt", LogAll, std::ios_base::trunc);
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

void Application::CheckForImproperInstallation() const
{
    if (IsFolderPlacementError())
    {
        FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
    }
}

void Application::InitRSL()
{
    try
    {
        if (!LoadDataFromConfig())
        {
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            return;
        }
        OpenConsole();

        //Sleep(5000);

        //Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));


        Functions.Initialize();

        GameState RFGRState = GameseqGetState();;
        auto StartTime = std::chrono::steady_clock::now();
        auto EndTime = std::chrono::steady_clock::now();
        long long TimeElapsed = 0LL;
        do
        {
            TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
            if (TimeElapsed > 1000LL) //Todo: Figure out if casting 1000 as a long long is necessary in this case or ever.
            {
                RFGRState = GameseqGetState();
                StartTime = EndTime;
                std::cout << "TimeElapsed: " << TimeElapsed << "\n";
                std::cout << "Current RFGR State: " << (UINT32)RFGRState << "\n";
            }
            EndTime = std::chrono::steady_clock::now();
        } while (RFGRState < 0 || RFGRState > 63);


        //Attempt to init kiero which is used for easy directx hooking. Shutdown if it fails.
        if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
        {
            Logger::LogFatalError("Kiero error: {}\n", kiero::init(kiero::RenderType::D3D11));
            Logger::LogFatalError("Failed to initialize kiero for D3D11. RSL deactivating.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            return;
        }
        if (MH_Initialize() != MH_OK)
        {
            Logger::LogFatalError("Failed to initialize MinHook. RSL deactivating.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            return;
        }

        //Sleep(10000);
        Globals::GameWindowHandle = Globals::FindRfgTopWindow();
        CreateHooks();


        ////Attempt to init kiero which is used for easy directx hooking. Shutdown if it fails.
        //if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
        //{
        //    Logger::LogFatalError("Kiero error: {}\n", kiero::init(kiero::RenderType::D3D11));
        //    Logger::LogFatalError("Failed to initialize kiero for D3D11. RSL deactivating.\n");
        //    FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
        //    return;
        //}
        //if (MH_Initialize() != MH_OK)
        //{
        //    Logger::LogFatalError("Failed to initialize MinHook. RSL deactivating.\n");
        //    FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
        //    return;
        //}

        //Set global values which are frequently used in hooks.
        Globals::MouseGenericPollMouseVisible = Globals::FindPattern("rfg.exe", "\x84\xD2\x74\x08\x38\x00\x00\x00\x00\x00\x75\x02", "xxxxx?????xx");
        Globals::CenterMouseCursorCall = Globals::FindPattern("rfg.exe", "\xE8\x00\x00\x00\x00\x89\x46\x4C\x89\x56\x50", "x????xxxxxx");
        Globals::Program = this;
        Globals::Gui = &this->Gui;
        Globals::Scripts = &this->Scripts;
        Globals::Camera = &this->Camera;

        Camera.Initialize(Globals::DefaultFreeCameraSpeed, 5.0);
        Scripts.Initialize();

        //Creates and enables all function hooks.
        ///CreateHooks();
        
        Globals::OriginalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Globals::GameWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::WndProc)));
        if(!Globals::OriginalWndProc)
        {
            Logger::LogFatalError("Failed to set custom WndProc! Error message: {}\n", Globals::GetLastWin32ErrorAsString());
        }
        Logger::Log("Custom WndProc set.\n");

        /*Waits for ImGui init to complete before continuing to GuiSystem (The overlay) init.*/
        while (!Globals::ImGuiInitialized) //ImGui Initialization occurs in KeenGraphicsBeginFrameHook in Hooks.cpp
        {
            Sleep(100);
        }

        InitOverlays();
        Gui.Initialize(); //Todo: Change gui so it can be initialized before imgui is initialized
        //Gui.SetScriptManager(&Scripts);
        //Gui.FreeCamSettings->Camera = &Camera;

        //Update global lua pointers after init just to be sure. Can't hurt.
        Scripts.UpdateRfgPointers();
        Scripts.ScanScriptsFolder();

        Beep(600, 100);
        Beep(700, 100);
        Beep(900, 200);

        SetMemoryLocations();
        Scripts.RunStartupScripts();
    }
    catch (std::exception& Ex)
    {
        std::string MessageBoxString = R"(Exception detected during script loader initialization! Please provide this and a zip file with your logs folder (./RSL/Logs/) to the maintainer. Message: )";
        MessageBoxString += Ex.what();
        Logger::LogFatalError("{}\n", MessageBoxString);
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Script loader failed to initialize!", MB_OK);
    }
}

void Application::InitOverlays()
{
    Gui.AddChildGui(new MenuBarGui("Top menu bar"), true);
    Gui.AddChildGui(new GeneralTweaksGui("General tweaks"));
    Gui.AddChildGui(new OverlayConsole("Lua console"));
    Gui.LuaConsole = Gui.GetGuiReference<OverlayConsole>("Lua console").value();
    Gui.AddChildGui(new ScriptSelectGui("Scripts"));
    Gui.AddChildGui(new FreeCamGui("Camera settings"));
    Gui.AddChildGui(new TextEditorWrapper("Script editor"));
    Gui.AddChildGui(new LogWindow("Logger"));
    Gui.AddChildGui(new WelcomeGui("Welcome"), true);
    Gui.AddChildGui(new ThemeEditorGui("Theme editor"));
    Gui.AddChildGui(new PhysicsGui("Physics settings"));
    Gui.AddChildGui(new TeleportGui("Teleport"));
    Gui.AddChildGui(new IntrospectionGui("Object introspection"));
    Gui.AddChildGui(new ExplosionSpawnerGui("Explosion spawner"));
}

void Application::OpenDefaultLogs()
{
    try
    {
        Logger::Log("RSL successfully activated.\n");
        Logger::CloseLogFile("Load Log.txt");

        Logger::OpenLogFile("General Log.txt", LogInfo, std::ios_base::trunc);
        Logger::OpenLogFile("Error Log.txt", LogWarning | LogError | LogFatalError, std::ios_base::trunc);
        Logger::OpenLogFile("Json Log.txt", LogJson, std::ios_base::trunc);
        Logger::OpenLogFile("Lua Log.txt", LogLua, std::ios_base::trunc);
    }
    catch (std::exception& Ex)
    {
        std::string MessageBoxString = R"(Exception detected when opening the default log files. Please show this to the current script loader maintainer. It's much harder to fix any further problems which might occur without logs.)";
        MessageBoxString += Ex.what();
        Logger::Log("{}\n", MessageBoxString);
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Logger failed to open default log files!", MB_OK);
    }
}

void Application::MainLoop()
{
    const ulong UpdatesPerSecond = 1;
    const ulong MillisecondsPerUpdate = 1000 / UpdatesPerSecond;
    while (!ShouldClose()) //Todo: Change to respond to PostQuitMessage(0) in WndProc
    {
        //Todo: Have startup event here which checks for playerptr being valid and perhaps other values.
        //if(!AutorunScriptsRun)
        //{
        //    if(Globals::PlayerPtr && Globals::RfgWorldPtr && Globals::hkpWorldPtr) //Todo: Make a func that checks all pointers and other info used by scripts. For now this should work.
        //    {
        //        
        //    }
        //}
        std::chrono::steady_clock::time_point Begin = std::chrono::steady_clock::now();
        switch (GameseqGetState())
        {
        case GS_WRECKING_CREW_MAIN_MENU:
            Logger::LogFatalError("Wrecking crew is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        case GS_WRECKING_CREW_CHARACTER_SELECT:
            Logger::LogFatalError("Wrecking crew is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        case GS_WRECKING_CREW_SCOREBOARD:
            Logger::LogFatalError("Wrecking crew is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        case GS_MULTIPLAYER_LIVE:
            Logger::LogFatalError("MP is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        case GS_WC_INIT:
            Logger::LogFatalError("Wrecking crew is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        case GS_WC_SHUTDOWN:
            Logger::LogFatalError("Wrecking crew is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        case GS_MULTIPLAYER_LIVE_FIND_SERVERS:
            Logger::LogFatalError("MP is disabled while the RSL is active. Exiting.\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            break;
        default:
            break;
        }
        if (*Globals::InMultiplayer)
        {
            Logger::LogFatalError("Invalid graphics state in RSL overlay, crashing!\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            return;
        }
        if ((void*)(!Globals::HookDidFrame) == nullptr)
        {
            Logger::LogFatalError("Null pointer in RSL callback system, crashing!\n");
            FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
            return;
        }
        if (Globals::ScriptLoaderCloseRequested)
        {
            ExitKeysPressCount = 10;
        }
        std::chrono::steady_clock::time_point End = std::chrono::steady_clock::now();
        Sleep(MillisecondsPerUpdate - std::chrono::duration_cast<std::chrono::milliseconds>(End - Begin).count());
    }
}

void Application::Exit()
{
    if (Globals::OverlayActive || Gui.IsLuaConsoleActive())
    {
        SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
        SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
    }
    SetWindowLongPtr(Globals::GameWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Globals::OriginalWndProc));
    Camera.DeactivateFreeCamera(true);

    HideHud(false);
    HideFog(false);

    Hooks.DisableAllHooks();

#if DebugDrawTestEnabled
    dd::shutdown();
#endif

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

void Application::CreateHooks()
{
    //Todo: Make helpers or improve this function to need less casting fuckery
    Hooks.CreateHook("PlayerDoFrame", Globals::ModuleBase + 0x6D5A80, Hooks::PlayerDoFrameHook, PlayerDoFrame);
    Hooks.CreateHook("CsWrapSlice", Globals::ModuleBase + 0x516D80, Hooks::CsWrapSliceHook, CsWrapSlice);

    Hooks.CreateHook("ExplosionCreate", Globals::ModuleBase + 0x2EC720, Hooks::ExplosionCreateHook, ExplosionCreate);
    Hooks.CreateHook("KeenGraphicsBeginFrame", Globals::ModuleBase + 0x86DD00, Hooks::KeenGraphicsBeginFrameHook, KeenGraphicsBeginFrame);
    Hooks.CreateHook("IsValidEigenGradient", Globals::ModuleBase + 0x1D0DD0, Hooks::IsValidEigenGradientHook, IsValidEigenGradient);
    Hooks.CreateHook("KeenGraphicsResizeRenderSwapchain", Globals::ModuleBase + 0x86AB20, Hooks::KeenGraphicsResizeRenderSwapchainHook, KeenGraphicsResizeRenderSwapchain);

    Hooks.CreateHook("world::do_frame", Globals::ModuleBase + 0x540AB0, Hooks::world_do_frame_hook, WorldDoFrame);
    Hooks.CreateHook("rl_camera::render_begin", Globals::ModuleBase + 0x137660, Hooks::rl_camera_render_begin_hook, RlCameraRenderBegin);
    Hooks.CreateHook("hkpWorld::stepDeltaTime", Globals::ModuleBase + 0x9E1A70, Hooks::hkpWorld_stepDeltaTime_hook, hkpWorldStepDeltaTime);
    Hooks.CreateHook("HookDoFrame", Globals::ModuleBase + 0x3CC750, Hooks::HookDoFrameHook, HookDoFrame);

    Hooks.CreateHook("Application::UpdateTime", Globals::ModuleBase + 0x5A880, Hooks::ApplicationUpdateTimeHook, ApplicationUpdateTime);
    Hooks.CreateHook("InvertDataItem", Globals::ModuleBase + 0x497740, Hooks::InvertDataItemHook, InvertDataItem);

    Hooks.CreateHook("LuaDoBuffer", Globals::ModuleBase + 0x82FD20, Hooks::LuaDoBufferHook, LuaDoBuffer);

    Hooks.CreateHook("D3D11Present", kiero::getMethodsTable()[8], Hooks::D3D11PresentHook, Hooks::D3D11PresentFuncPtr);
    Hooks.CreateHook("AllocatorStillValid", Globals::ModuleBase + 0x4F50B0, Hooks::AllocatorStillValidHook, AllocatorStillValid);

    Hooks.CreateHook("peg_load_wrapper", Globals::ModuleBase + 0x1D1F10, Hooks::peg_load_wrapper_hook, peg_load_wrapper);

    //Disabling for now since stream grid tests had issues.
    //Hooks.CreateHook("StreamGridDoFrame", reinterpret_cast<LPVOID>(Globals::ModuleBase + 0x530FB0), StreamGridDoFrameHook, reinterpret_cast<LPVOID*>(&StreamGridDoFrame));
    //Hooks.CreateHook("ObjectSpawnVehicle", reinterpret_cast<LPVOID>(Globals::ModuleBase + 0x757F40), ObjectSpawnVehicleHook, reinterpret_cast<LPVOID*>(&ObjectSpawnVehicle));
}

bool Application::ShouldClose() const
{
    return ExitKeysPressCount > 5;
}

void Application::OpenConsole()
{
    if (Globals::OpenDebugConsole)
    {
        FILE* pFile = nullptr;

        if (AttachConsole(Globals::PID) == 0)
        {
            PreExistingConsole = false;
            AllocConsole();
        }
        else
        {
            PreExistingConsole = true;
        }
        freopen_s(&pFile, "CONOUT$", "r+", stdout);

        Globals::ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        Globals::SetConsoleAttributes(Globals::ConsoleDefaultTextAttributes);
    }
}

void Application::CloseConsole() const
{
    if (PreExistingConsole)
	{
		FreeConsole();
	}
}

void Application::SetMemoryLocations()
{
    Globals::InMultiplayer = reinterpret_cast<bool*>(*reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x002CA210));
    if (*Globals::InMultiplayer)
    {
        MessageBoxA(Globals::FindRfgTopWindow(), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
        std::cout << "MP detected. Shutting down!\n";
    }
    //Todo: See if I can simplify this cast by removing the DWORD* bit. 
    //Todo: Make helpers for stuff like this so theres less casting fuckery and guess work.
    Globals::NumExplosionInfos = reinterpret_cast<uint*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x19EE490));
    Logger::Log("NumExplosionInfos = {}\n", *Globals::NumExplosionInfos);
    auto ExplosionInfosPtr = reinterpret_cast<explosion_info*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x19E6CD8));
    Globals::ExplosionInfos.Init(ExplosionInfosPtr, 80, *Globals::NumExplosionInfos);

    Globals::NumMaterialEffectInfos = reinterpret_cast<uint*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x19EE4C4));
    Logger::Log("Num material effect infos = {}\n", *Globals::NumMaterialEffectInfos);
    auto MaterialEffectInfosPtr = reinterpret_cast<material_effect_info*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x19EB6F0));
    Globals::MaterialEffectInfos.Init(MaterialEffectInfosPtr, *Globals::NumMaterialEffectInfos, *Globals::NumMaterialEffectInfos);

    Globals::NumEffectInfos = reinterpret_cast<uint*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x1D82DF0));
    Logger::Log("Num effect infos = {}\n", *Globals::NumEffectInfos);
    auto EffectInfosPtr = reinterpret_cast<effect_info*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x1D82E60));
    Globals::EffectInfos.Init(EffectInfosPtr, *Globals::NumEffectInfos, *Globals::NumEffectInfos);

    Globals::VehicleInfos = reinterpret_cast<rfg::farray<vehicle_info, 163>*>(reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x12BA5F8));

    Scripts.UpdateRfgPointers();
} 

/* Tries to find common installation mistakes such as placing it in the rfg root directory rather than it's own
 * folder. Returns true if errors were found. Returns false if errors were not found.
 */
bool Application::IsFolderPlacementError() const
{
    const std::string ExePath = Globals::GetEXEPath(false);
    if (!fs::exists(ExePath + "RSL/Core/")) //Detect if the core lua lib folder is missing.
    {
        if (fs::exists(ExePath + "Core/")) //Detect if the user put it in the rfg folder on accident rather than the script loader folder.
        {
            const std::string ErrorString = R"(RSL Core folder is in the wrong directory! Make sure that it's at "Red Faction Guerrilla Re-MARS-tered\RSL\Core". It should not be in the same folder as rfg.exe! Shutting down script loader.)";
            Logger::LogFatalError("{}\n", ErrorString);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Core folder in wrong root directory!", MB_OK);
        }
        else
        {
            const std::string ErrorString = R"(RSL Core folder not detected! Make sure that it's at "\Red Faction Guerrilla Re-MARS-tered\RSL\Core". Double check the installation guide for an image of how it should look when installed properly. Shutting down script loader.)";
            Logger::LogFatalError("{}\n", ErrorString);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Core folder not found!", MB_OK);
        }
        return true;
    }
    if (!fs::exists(ExePath + "RSL/Fonts/")) //Detect if the fonts folder is missing.
    {
        if (fs::exists(ExePath + "Fonts/")) //Detect if the user put it in the rfg folder on accident rather than the script loader folder.
        {
            const std::string ErrorString = R"(Script Loader Fonts folder is in the wrong directory! Make sure that it's at "\Red Faction Guerrilla Re-MARS-tered\RSL\Fonts". It should not be in the same folder as rfg.exe! Shutting down script loader.)";
            Logger::LogFatalError("{}\n", ErrorString);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Fonts folder in wrong root directory!", MB_OK);
        }
        else
        {
            const std::string ErrorString = R"(Script Loader Fonts folder not detected! Make sure that it's at "\Red Faction Guerrilla Re-MARS-tered\RSL\Fonts". Double check the installation guide for an image of how it should look when installed properly. Shutting down script loader.)";
            Logger::LogFatalError("{}\n", ErrorString);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Fonts folder not found.", MB_OK);
        }
        return true;
    }
    return false;
}

bool Application::LoadDataFromConfig()
{
    std::string ExePath = Globals::GetEXEPath(false);
    Logger::Log("Started loading \"Settings.json\".\n");

    if (fs::exists(ExePath + "RSL/Settings/Settings.json"))
    {
        if (!JsonExceptionHandler([&]
        {
            Logger::Log("Parsing \"Settings.json\"\n");
            std::ifstream Config(ExePath + "RSL/Settings/Settings.json");
            Config >> Globals::MainConfig;
            Config.close();
            return true;
        }, "Settings.json", "parse", "parsing"))
        {
            return false;
        }
            Logger::Log("No parse exceptions detected.\n");
    }
    else
    {
        if (!JsonExceptionHandler([&]
        {
            Globals::CreateDirectoryIfNull(ExePath + "RSL/Settings/");
            Logger::Log("\"Settings.json\" not found. Creating from default values.\n");

            Globals::MainConfig["Open debug console"] = false;
            Globals::MainConfig["Dump textures when loading"] = false;

            std::ofstream ConfigOutput(ExePath + "RSL/Settings/Settings.json");
            ConfigOutput << std::setw(4) << Globals::MainConfig << "\n";
            ConfigOutput.close();
            return true;
        }, "Settings.json", "write", "writing"))
        {
            return false;
        }
            Logger::Log("No write exceptions detected.\n");
    }

    if (!JsonExceptionHandler([&]
    {
        Globals::OpenDebugConsole = Globals::MainConfig["Open debug console"].get<bool>();
        Globals::DumpTexturesWhenLoading = Globals::MainConfig["Dump textures when loading"].get<bool>();
        return true;
    }, "Settings.json", "read", "reading"))
    {
        return false;
    }
    Logger::Log("No read exceptions detected.\n");

    Logger::Log("Done loading \"Settings.json\".\n");
    return true;
}