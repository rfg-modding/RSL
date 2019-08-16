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

        Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
        Functions.Initialize();

        InitHookingSystem();
        CreateHooks(); //Creates and enables all function hooks.

#if UseLauncher
        Globals::ResumeAllThreads();
        Globals::UnlockGameMain();
#endif
        WaitForValidGameState();

        //Set global values which are frequently used in hooks.
        Globals::GameWindowHandle = Globals::FindRfgTopWindow();
        Globals::MouseGenericPollMouseVisible = Globals::FindPattern("rfg.exe", "\x84\xD2\x74\x08\x38\x00\x00\x00\x00\x00\x75\x02", "xxxxx?????xx");
        Globals::CenterMouseCursorCall = Globals::FindPattern("rfg.exe", "\xE8\x00\x00\x00\x00\x89\x46\x4C\x89\x56\x50", "x????xxxxxx");
        Globals::Program = this;
        Globals::Gui = &this->Gui;
        Globals::Scripts = &this->Scripts;
        Globals::Camera = &this->Camera;

        Camera.Initialize(Globals::DefaultFreeCameraSpeed, 5.0);
        Scripts.Initialize();
        
        Globals::OriginalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Globals::GameWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::WndProc)));
        if(!Globals::OriginalWndProc)
        {
            Logger::LogFatalError("Failed to set custom WndProc! Error message: {}\n", Globals::GetLastWin32ErrorAsString());
        }
        Logger::Log("Custom WndProc set.\n");

        Globals::ReadyForImGuiInit = true;

        /*Waits for ImGui init to complete before continuing to GuiSystem (The overlay) init.*/
        while (!Globals::ImGuiInitialized) //ImGui Initialization occurs in KeenGraphicsBeginFrameHook 
        {
            Sleep(100);
        }

        InitOverlays();
        Gui.Initialize(); //Todo: Change gui so it can be initialized before imgui is initialized

        //Update global lua pointers after init just to be sure. Can't hurt.
        Scripts.UpdateRfgPointers();
        Scripts.ScanScriptsFolder();

        //Attempts to set important memory values and tries to compensate for varied game loading times by retrying the process if it fails the first time.
        TrySetMemoryLocations(); 

        Beep(600, 100);
        Beep(700, 100);
        Beep(900, 200);

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

void Application::InitHookingSystem()
{        
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
}

void Application::WaitForValidGameState() const
{
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
            Logger::Log("Current RFGR State: {}\n", uint(RFGRState));
        }
        EndTime = std::chrono::steady_clock::now();
    } 
    while (RFGRState < 0 || RFGRState > 63);
}

//Note: This function is an over-redundant hack to make sure that a few memory offsets are properly set since they kept not being set and causing bugs. Will improve later on.
//Todo: Simplify this function by instead hooking explosion_parse_table (for explosions) and the relevant functions for other values, and setting their values after those functions are called
//Todo: (continued) ... that way it will be guaranteed that if the explosion presets were loaded by the game, that the script loader will have them.
void Application::TrySetMemoryLocations()
{
    SetMemoryLocations();
    for (int i = 0; i < 30; i++)
    {
        if (*Globals::NumExplosionInfos == 0)
        {
            Logger::LogWarning("Trying to set memory locations...\n");
            SetMemoryLocations();
            if (*Globals::NumExplosionInfos == 0)
            {
                Logger::Log("NumExplosionInfos = {}\n", *Globals::NumExplosionInfos);
                Logger::Log("Num material effect infos = {}\n", *Globals::NumMaterialEffectInfos);
                Logger::Log("Num effect infos = {}\n", *Globals::NumEffectInfos);
                Logger::LogWarning("Still not set... waiting 0.5 seconds\n");
                Sleep(500);
            }
            else
            {
                Logger::LogWarning("Successfully set memory locations!\n");
            }
        }
        else
        {
            Logger::LogWarning("Successfully set memory locations! NumExplosionInfos: {}, {}\n", *Globals::NumExplosionInfos, Globals::ExplosionInfos.Initialized() ? "Exp list initialized" : "Exp list not initialized");

            Globals::NumExplosionInfos = OffsetPtr<uint*>(0x19EE490);
            auto ExplosionInfosPtr = OffsetPtr<explosion_info*>(0x19E6CD8);
            Globals::ExplosionInfos.Init(ExplosionInfosPtr, 80, *Globals::NumExplosionInfos, "ExplosionInfos");

            Globals::NumMaterialEffectInfos = OffsetPtr<uint*>(0x19EE4C4);
            auto MaterialEffectInfosPtr = OffsetPtr<material_effect_info*>(0x19EB6F0);
            Globals::MaterialEffectInfos.Init(MaterialEffectInfosPtr, *Globals::NumMaterialEffectInfos, *Globals::NumMaterialEffectInfos, "MaterialEffectInfos");

            Globals::NumEffectInfos = OffsetPtr<uint*>(0x1D82DF0);
            auto EffectInfosPtr = OffsetPtr<effect_info*>(0x1D82E60);
            Globals::EffectInfos.Init(EffectInfosPtr, *Globals::NumEffectInfos, *Globals::NumEffectInfos, "EffectInfos");
            break;
        }
    }
    if (*Globals::NumExplosionInfos == 0)
    {
        Logger::LogFatalError("Failed to set memory locations! Attempting to dump explosion info to log...\n");

        Globals::NumExplosionInfos = OffsetPtr<uint*>(0x19EE490);
        Logger::Log("Alternative Address of NumExplosionInfos: {:#x}\n", (DWORD)Globals::NumExplosionInfos);
        Logger::Log("AltNumExplosionInfos = {}\n", *Globals::NumExplosionInfos);
        auto ExplosionInfosPtr = OffsetPtr<explosion_info*>(0x19E6CD8);
        Logger::Log("ExplosionInfos address: {:#x}\n", (DWORD)ExplosionInfosPtr);
        Globals::ExplosionInfos.Init(ExplosionInfosPtr, 80, 72, "ExplosionInfos");

        if (ExplosionInfosPtr)
        {
            Logger::Log("\n\n\nExplosion dump attempt: \n");
            for (int i = 0; i < 72; i++)
            {
                Logger::Log("\n\nIndex: {}\n", i);
                Logger::Log("Name: {}\n", Globals::CharArrayToString(Globals::ExplosionInfos[i].m_name, 32));
                Logger::Log("Unique ID: {}\n", Globals::ExplosionInfos[i].m_unique_id);
                Logger::Log("Knockdown radius: {}\n", Globals::ExplosionInfos[i].m_knockdown_radius);
                Logger::Log("Player damage mult: {}\n", Globals::ExplosionInfos[i].player_damage_mult);
                Logger::Log("Structural damage: {}\n", Globals::ExplosionInfos[i].m_structural_damage);
                Logger::Log("Salvage max pieces: {}\n", Globals::ExplosionInfos[i].salvage_max_pieces);
                Logger::Log("Ignore orientation: {}\n", Globals::ExplosionInfos[i].ignore_orientation);
            }
        }
        FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
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
    Gui.AddChildGui(new GraphicsTweaksGui("Graphics tweaks"));
}

void Application::OpenDefaultLogs()
{
    try
    {
        Logger::Log("RSL successfully activated.\n");
        Logger::CloseLogFile("Load Log.log");

        Logger::OpenLogFile("General Log.log", LogInfo, std::ios_base::trunc);
        Logger::OpenLogFile("Error Log.log", LogWarning | LogError | LogFatalError, std::ios_base::trunc);
        Logger::OpenLogFile("Json Log.log", LogJson, std::ios_base::trunc);
        Logger::OpenLogFile("Lua Log.log", LogLua, std::ios_base::trunc);
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
        std::chrono::steady_clock::time_point Begin = std::chrono::steady_clock::now();
        const GameState State = GameseqGetState();
        switch (State)
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
        case GS_MAINMENU:
            Globals::TryHideInvalidMainMenuOptions();
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
    Hooks.CreateHook("D3D11_ResizeBuffers", kiero::getMethodsTable()[13], Hooks::D3D11_ResizeBuffersHook, Hooks::D3D11_ResizeBuffersFuncPtr);
    Hooks.CreateHook("AllocatorStillValid", Globals::ModuleBase + 0x4F50B0, Hooks::AllocatorStillValidHook, AllocatorStillValid);

    Hooks.CreateHook("peg_load_wrapper", Globals::ModuleBase + 0x1D1F10, Hooks::peg_load_wrapper_hook, peg_load_wrapper);

    Hooks.CreateHook("object_spawn_vehicle_hook", Globals::ModuleBase + 0x757F40, Hooks::object_spawn_vehicle_hook, object_spawn_vehicle);

    Hooks.CreateHook("keen_ImmediateRenderer_beginRenderPass_hook", Globals::ModuleBase + 0x86C810, Hooks::keen_ImmediateRenderer_beginRenderPass_hook, keen_ImmediateRenderer_beginRenderPass);
    
    Hooks.CreateHook("rfgl_find_and_delete_object_mover_hook", Globals::ModuleBase + 0x324A60, Hooks::rfgl_find_and_delete_object_mover_hook, rfgl_find_and_delete_object_mover);
    Hooks.CreateHook("rfgl_find_and_delete_debris_object_hook", Globals::ModuleBase + 0x324B90, Hooks::rfgl_find_and_delete_debris_object_hook, rfgl_find_and_delete_debris_object);

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
    Logger::Log("Setting memory locations. ModuleBase value: {:#x}\n", (DWORD)Globals::ModuleBase);
    Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    Globals::InMultiplayer = reinterpret_cast<bool*>(*reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x002CA210)); //For some reason need to do this casting nonsense for this var.
    if (*Globals::InMultiplayer)
    {
        MessageBoxA(Globals::FindRfgTopWindow(), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
        std::cout << "MP detected. Shutting down!\n";
    }


    Globals::NumExplosionInfos = OffsetPtr<uint*>(0x19EE490);
    auto ExplosionInfosPtr = OffsetPtr<explosion_info*>(0x19E6CD8);
    Globals::ExplosionInfos.Init(ExplosionInfosPtr, 80, *Globals::NumExplosionInfos, "ExplosionInfos");

    Globals::NumMaterialEffectInfos = OffsetPtr<uint*>(0x19EE4C4);
    auto MaterialEffectInfosPtr = OffsetPtr<material_effect_info*>(0x19EB6F0);
    Globals::MaterialEffectInfos.Init(MaterialEffectInfosPtr, *Globals::NumMaterialEffectInfos, *Globals::NumMaterialEffectInfos, "MaterialEffectInfos");

    Globals::NumEffectInfos = OffsetPtr<uint*>(0x1D82DF0);
    auto EffectInfosPtr = OffsetPtr<effect_info*>(0x1D82E60);
    Globals::EffectInfos.Init(EffectInfosPtr, *Globals::NumEffectInfos, *Globals::NumEffectInfos, "EffectInfos");

    Globals::NumWeaponInfos = OffsetPtr<uint*>(0x3482C94);
    auto WeaponInfosPtr = OffsetPtr<weapon_info*>(0x3482C9C);
    Globals::WeaponInfos.Init(WeaponInfosPtr, *Globals::NumWeaponInfos, *Globals::NumWeaponInfos, "WeaponInfos");

    Globals::VehicleInfos = OffsetPtr<rfg::farray<vehicle_info, 163>*>(0x12BA5F8);
    
    Globals::UnlimitedAmmo = OffsetPtr<bool*>(0x3482CB6);
    Globals::UnlimitedMagazineAmmo = OffsetPtr<bool*>(0x3482CBC);
    Globals::UnlimitedAiThrownWeapons = OffsetPtr<bool*>(0x3482CB7);
    Globals::VehicleMaxSpeed = OffsetPtr<float*>(0x12BA434);
    Globals::SsaoVisionEnabled = OffsetPtr<bool*>(0x177BD1E);
    Globals::RfgMaxCharges = OffsetPtr<int*>(0x1251568);
    Globals::TodEnabled = OffsetPtr<bool*>(0x125CCA7);
    Globals::CurrentTimeOfDay = OffsetPtr<float*>(0x125CC80);

    auto ShadowMapSizesPtr = OffsetPtr<int*>(0xEC1BB4);
    Globals::ShadowMapSizes.Init(ShadowMapSizesPtr, 4, 4, "ShadowMapSizes");
    Globals::EnableMemoryRegionReadWrite((void*)ShadowMapSizesPtr, 4 * sizeof(int));

    Globals::ChargeExplosionDelay = OffsetPtr<int*>(0x1294728);

    Globals::RfgMenusList = OffsetPtr<rfg::farray<ui_menu*, 8>*>(0x1267698); //farray<ui_menu *,8> RfgMenusList //.data:015A7698 rfg.exe:$1267698 #1266098 <RfgMenusList>
    Globals::TryHideInvalidMainMenuOptions();

    Globals::GraphicsState.Init();

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
            Globals::MainConfig["Disable numpad while overlay is visible"] = true;

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
        Globals::DisableNumpadWhileOverlayVisible = Globals::MainConfig["Disable numpad while overlay is visible"].get<bool>();
        return true;
    }, "Settings.json", "read", "reading"))
    {
        return false;
    }
    Logger::Log("No read exceptions detected.\n");

    Logger::Log("Done loading \"Settings.json\".\n");
    return true;
}