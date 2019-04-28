#include "ProgramManager.h"

ProgramManager::~ProgramManager()
{
	if (Globals::OverlayActive)
	{
		SetWindowLongPtr(Globals::GameWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Globals::OriginalWndProc));
		SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
		SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
	}
	Hooks.DisableAllHooks();

	Beep(900, 100);
	Beep(700, 100);
	Beep(600, 200);
}

void ProgramManager::Initialize()
{
	Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

	Globals::Program = this;
	Globals::Gui = &this->Gui;
	Globals::Scripts = &this->Scripts;
	Globals::Camera = &this->Camera;
	Camera.Initialize(Globals::DefaultFreeCameraSpeed, 5.0);
	Functions.Initialize();
	Scripts.Initialize();

	if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
	{
		Logger::Log(std::string("Kiero error: " + std::to_string(kiero::init(kiero::RenderType::D3D11))), LogFatalError, true);
		Logger::Log("Failed to initialize kiero for D3D11. RFGR Script loader deactivating.", LogFatalError, true);
		FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
		return;
	}
	if (MH_Initialize() != MH_OK)
	{
		Logger::Log("Failed to initialize MinHook. RFGR Script loader deactivating.", LogFatalError, true);
		FreeLibraryAndExitThread(Globals::ScriptLoaderModule, 0);
		return;
	}
	Globals::GameWindowHandle = Globals::FindRfgTopWindow();

	CreateGameHooks(true);

	Globals::MouseGenericPollMouseVisible = Globals::FindPattern("rfg.exe", "\x84\xD2\x74\x08\x38\x00\x00\x00\x00\x00\x75\x02", "xxxxx?????xx");
	Globals::CenterMouseCursorCall = Globals::FindPattern("rfg.exe", "\xE8\x00\x00\x00\x00\x89\x46\x4C\x89\x56\x50", "x????xxxxxx");

	///Logger::Log("Now monitoring RFGR State", LogInfo);
	GameState RFGRState = GameseqGetState();;
	auto StartTime = std::chrono::steady_clock::now();
	auto EndTime = std::chrono::steady_clock::now();
	long long TimeElapsed = 0;
	do
	{
		TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
		if (TimeElapsed > 1000)
		{
			RFGRState = GameseqGetState();
			StartTime = EndTime;
			///std::cout << "TimeElapsed: " << TimeElapsed << "\n";
			///std::cout << "Current RFGR State: " << (UINT32)RFGRState << "\n";
		}
		EndTime = std::chrono::steady_clock::now();
	} 
	while (RFGRState < 0 || RFGRState > 63);

	Globals::OriginalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Globals::GameWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
	Logger::Log("Custom WndProc set.", LogInfo);
	CreateD3D11Hooks(true);
	Logger::Log("D3D11 hooks created and enabled.", LogInfo);
	//Logger::Log("Finished hooking D3D11 functions.", LogInfo);

	Sleep(5000);

	StartTime = std::chrono::steady_clock::now();
	EndTime = std::chrono::steady_clock::now();
	while (!Globals::ImGuiInitialized) //ImGui Initialization done in D3DPresentHook in Hooks.cpp
	{
		long long TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
		if (TimeElapsed > 2000LL) 
		{
			///Logger::Log("Waiting for ImGui to be initialized.", LogInfo);
		}
		EndTime = StartTime;
		StartTime = std::chrono::steady_clock::now();
	}
	Gui.Initialize();
	Gui.SetScriptManager(&Scripts);
	Gui.FreeCamSettings->Camera = &Camera;
	Scripts.UpdateRfgPointers();

	Beep(600, 100);
	Beep(700, 100);
	Beep(900, 200);

	Initialized = true;
}

void ProgramManager::Exit()
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
	
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	if (Globals::PlayerPtr)
	{
		Globals::PlayerPtr->Flags.invulnerable = false;
		Globals::PlayerPtr->HitPoints = 230.0f;
	}

	Beep(900, 100);
	Beep(700, 100);
	Beep(600, 200);
	SuccessfulExit = true;
}

void ProgramManager::OpenConsole()
{
	if (Globals::OpenDebugConsole)
	{
		FILE *pFile = nullptr;
		Globals::PID = GetCurrentProcessId();

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

void ProgramManager::SetMemoryLocations()
{
	Globals::InMultiplayer = reinterpret_cast<bool*>(*reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x002CA210));
	if (*Globals::InMultiplayer)
	{
		MessageBoxA(Globals::FindRfgTopWindow(), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
		std::cout << "MP detected. Shutting down!\n";
	}
}

void ProgramManager::CreateGameHooks(bool EnableNow)
{
	//Hooks.CreateHook("PlayerConstructor", GAMEHOOK,reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x6DECA0), PlayerConstructorHook, reinterpret_cast<LPVOID*>(&PlayerConstructor), EnableNow);
	Hooks.CreateHook("PlayerDoFrame", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x6D5A80), PlayerDoFrameHook, reinterpret_cast<LPVOID*>(&PlayerDoFrame), EnableNow);
	//Hooks.CreateHook("ObjectUpdatePosAndOrient", GAMEHOOK, (DWORD*)(ModuleBase + 0x68C310), ObjectUpdatePosAndOrientHook, (LPVOID*)&ObjectUpdatePosAndOrient, EnableNow);
	//Hooks.CreateHook("HumanUpdatePosAndOrient", GAMEHOOK, (DWORD*)(ModuleBase + 0x69AF70), HumanUpdatePosAndOrientHook, (LPVOID*)&HumanUpdatePosAndOrient, EnableNow);
	//Hooks.CreateHook("CharacterControllerSetPos", GAMEHOOK, (DWORD*)(ModuleBase + 0x4153D0), CharacterControllerSetPosHook, (LPVOID*)&CharacterControllerSetPos, EnableNow);
	Hooks.CreateHook("ExplosionCreate", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x2EC720), ExplosionCreateHook, reinterpret_cast<LPVOID*>(&ExplosionCreate), EnableNow);
	//Hooks.CreateHook("CameraViewDataSetView", GAMEHOOK, (DWORD*)(ModuleBase + 0x2D0290), CameraViewDataSetViewHook, (LPVOID*)&CameraViewDataSetView, EnableNow);
	//Hooks.CreateHook("KeenGraphicsResizeRenderSwapchain", GAMEHOOK, (DWORD*)(ModuleBase + 0x86AB20), KeenGraphicsResizeRenderSwapchainHook, (LPVOID*)&KeenGraphicsResizeRenderSwapchain, EnableNow);

	/*Start of MP Detection Hooks*/
	//Using phony names to make finding the MP hooks a bit more difficult.
	Hooks.CreateHook("FreeSubmodeDoFrame", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x516D80), HudUiMultiplayerEnterHook, reinterpret_cast<LPVOID*>(&HudUiMultiplayerEnter), EnableNow);
	Hooks.CreateHook("FreeSubmodeInit", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x3CC750), GameMusicMultiplayerStartHook, reinterpret_cast<LPVOID*>(&GameMusicMultiplayerStart), EnableNow);	
	Hooks.CreateHook("SatelliteModeInit", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x4F50B0), HudUiMultiplayerProcessHook, reinterpret_cast<LPVOID*>(&HudUiMultiplayerProcess), EnableNow);
	Hooks.CreateHook("SatelliteModeDoFrame", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x1D0DD0), IsValidGameLinkLobbyKaikoHook, reinterpret_cast<LPVOID*>(&IsValidGameLinkLobbyKaiko), EnableNow);
	Hooks.CreateHook("ModeMismatchFixState", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x497740), InitMultiplayerDataItemRespawnHook, reinterpret_cast<LPVOID*>(&InitMultiplayerDataItemRespawn), EnableNow);

	/*End of MP Detection Hooks*/

	Hooks.CreateHook("world::do_frame", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x540AB0), world_do_frame_hook, reinterpret_cast<LPVOID*>(&world_do_frame), EnableNow);
	Hooks.CreateHook("rl_camera::render_begin", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x137660), rl_camera_render_begin_hook, reinterpret_cast<LPVOID*>(&rl_camera_render_begin), EnableNow);
	Hooks.CreateHook("hkpWorld::stepDeltaTime", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x9E1A70), hkpWorld_stepDeltaTime_hook, reinterpret_cast<LPVOID*>(&hkpWorld_stepDeltaTime), EnableNow);
	Hooks.CreateHook("Application::UpdateTime", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x5A880), ApplicationUpdateTimeHook, reinterpret_cast<LPVOID*>(&ApplicationUpdateTime), EnableNow);
	
	Hooks.CreateHook("LuaDoBuffer", GAMEHOOK, reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x82FD20), LuaDoBufferHook, reinterpret_cast<LPVOID*>(&LuaDoBuffer), EnableNow);
}

void ProgramManager::CreateD3D11Hooks(bool EnableNow)
{
	Hooks.CreateHook("D3D11Present", D3D11HOOK, reinterpret_cast<LPVOID>(kiero::getMethodsTable()[8]), D3D11PresentHook, reinterpret_cast<LPVOID*>(&D3D11PresentObject), EnableNow);
}

bool ProgramManager::ShouldClose() const
{
	return ExitKeysPressCount > 5;
}

void ProgramManager::Update()
{
	if (Globals::ScriptLoaderCloseRequested)
	{
		///std::cout << "Sleeping...\n";
		Sleep(300);
		///std::cout << "Done sleeping.\n";
		ExitKeysPressCount = 10;
	}
	/*if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) //Todo: Figure out if I really need this for the overlay to work.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/
}

void ProgramManager::CloseConsole() const
{
	if (PreExistingConsole)
	{
		FreeConsole();
	}
}

bool ProgramManager::LoadDataFromConfig()
{
	std::string ExePath = Globals::GetEXEPath(false);
	Logger::Log("Started loading \"Settings.json\".", LogInfo);
	
	if (fs::exists(ExePath + "RFGR Script Loader/Settings/Settings.json"))
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("Parsing \"Settings.json\"", LogInfo);
			std::ifstream Config(ExePath + "RFGR Script Loader/Settings/Settings.json");
			Config >> Globals::MainConfig;
			Config.close();
			return true;
		}, "Settings.json", "parse", "parsing"))
		{
			return false;
		}
		Logger::Log("No parse exceptions detected.", LogInfo);
	}
	else
	{
		if (!JsonExceptionHandler([&]
		{
			Globals::CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");
			Logger::Log("\"Settings.json\" not found. Creating from default values.", LogWarning);

			Globals::MainConfig["Open debug console"] = false;

			std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/Settings.json");
			ConfigOutput << std::setw(4) << Globals::MainConfig << "\n";
			ConfigOutput.close();
			return true;
		}, "Settings.json", "write", "writing"))
		{
			return false;
		}
		Logger::Log("No write exceptions detected.", LogInfo);
	}

	if (!JsonExceptionHandler([&]
	{
		Globals::OpenDebugConsole = Globals::MainConfig["Open debug console"].get<bool>();
		return true;
	}, "Settings.json", "read", "reading"))
	{
		return false;
	}
	Logger::Log("No read exceptions detected.", LogInfo);
	
	Logger::Log("Done loading \"Settings.json\".", LogInfo);
	return true;
}

