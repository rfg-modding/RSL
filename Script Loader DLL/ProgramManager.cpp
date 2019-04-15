#include "ProgramManager.h"

ProgramManager::ProgramManager(HMODULE hModule)
{
	ScriptLoaderModule = hModule;

	//The variables below are in Globals.h
	show_demo_window = true;
	ImGuiInitialized = false;
	OverlayActive = false;
}

ProgramManager::~ProgramManager()
{
	Beep(900, 100);
	Beep(700, 100);
	Beep(600, 200);

	if (OverlayActive)
	{
		SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (LONG_PTR)OriginalWndProc);
		SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true); //Todo: Stop removing from cache and add check to see if exists to BackupSnippet().
		SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
	}
	//Hooks.DisableAllHooksOfType(GAMEHOOK);
	//Hooks.DisableAllHooksOfType(D3D11HOOK);
	Hooks.DisableAllHooks();

	//Beep(900, 100);
	//Beep(700, 100);
	//Beep(600, 200);
}

void ProgramManager::Initialize()
{
	Camera.Initialize(DefaultFreeCameraSpeed, 5.0);
	Functions.Initialize();
	Scripts.Initialize();
	
	NewObjectPosition.x = 0.0f;
	NewObjectPosition.y = 0.0f;
	NewObjectPosition.z = 0.0f;

	ModuleBase = (uintptr_t)GetModuleHandle(NULL);

	if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
	{
		Logger::Log(std::string("Kiero error: " + std::to_string(kiero::init(kiero::RenderType::D3D11))), LogFatalError, true);
		Logger::Log("Failed to initialize kiero for D3D11. RFGR Script loader deactivating.", LogFatalError, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_Initialize() != MH_OK)
	{
		Logger::Log("Failed to initialize MinHook. RFGR Script loader deactivating.", LogFatalError, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	GameWindowHandle = find_main_window(GetProcessID("rfg.exe"));

	CreateGameHooks(true);
#if !PublicMode
	Logger::ConsoleLog("Finished hooking game functions.", LogInfo, false, true, true);
#endif

	MouseGenericPollMouseVisible = FindPattern((char*)"rfg.exe", (char*)"\x84\xD2\x74\x08\x38\x00\x00\x00\x00\x00\x75\x02", (char*)"xxxxx?????xx");
	CenterMouseCursorCall = FindPattern((char*)"rfg.exe", (char*)"\xE8\x00\x00\x00\x00\x89\x46\x4C\x89\x56\x50", (char*)"x????xxxxxx");

	///Logger::Log("Now monitoring RFGR State", LogInfo);
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
			///std::cout << "TimeElapsed: " << TimeElapsed << "\n";
			///std::cout << "Current RFGR State: " << (UINT32)RFGRState << "\n";
		}
		EndTime = std::chrono::steady_clock::now();
	} 
	while (RFGRState < 0 || RFGRState > 63); //Todo: Consider changing to hex values for consistency with enum definition. Alternatively change enum to decimal.
	///Logger::Log(std::string("RFGR State > 0. Value: " + std::to_string(RFGRState)), LogInfo);

	OriginalWndProc = (WNDPROC)SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	Logger::Log("Custom WndProc set.", LogInfo);
	CreateD3D11Hooks(true);
	Logger::Log("D3D11 hooks created and enabled.", LogInfo);
#if !PublicMode
	Logger::Log("Finished hooking D3D11 functions.", LogInfoS);
#endif

	Sleep(5000);

	StartTime = std::chrono::steady_clock::now();
	EndTime = std::chrono::steady_clock::now();
	while (!ImGuiInitialized) //ImGui Initialization done in D3DPresentHook in Hooks.cpp
	{
		long long TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
		if (TimeElapsed > 2000LL) 
		{
			///Logger::Log("Waiting for ImGui to be initialized.", LogInfo);
		}
		EndTime = StartTime;
		StartTime = std::chrono::steady_clock::now();
	}
	//Gui.Initialize() is gaurunteed to be called before here because it's called during ImGui initialization.
	Gui.SetScriptManager(&Scripts);
	Gui.FreeCamSettings->Camera = &Camera;
	Scripts.UpdateRfgPointers();

	Beep(600, 100);
	Beep(700, 100);
	Beep(900, 200);

	///ZeroMemory(&msg, sizeof(msg));
}

void ProgramManager::ProcessInput()
{
	if ((GetAsyncKeyState(VK_OEM_3))) //126 = virtual key code for tilde
	{
		///Logger::Log("Tilde pressed", LogInfo);
		Gui.ToggleLuaConsole();
		if (Gui.IsLuaConsoleActive())
		{
			Gui.Console->InputBuffer.clear();
			Gui.Console->ReclaimFocus = true; //Tell console to set focus to it's text input.
			if (!OverlayActive)
			{
				SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", MouseGenericPollMouseVisible, 12, true);
				SnippetManager::BackupSnippet("CenterMouseCursorCall", CenterMouseCursorCall, 5, true);
			}
		}
		else
		{
			Gui.Console->InputBuffer.clear();
			if (!OverlayActive)
			{
				SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
				SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
			}
		}
		Sleep(200);
	}
	if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000))
	{
		ExitKeysPressCount++;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
		ToggleHud();
		Sleep(175);
	}
	if (GetAsyncKeyState(VK_NUMPAD2))
	{
		ToggleFog();
		Sleep(175);
	}
	if (GetAsyncKeyState(VK_NUMPAD3))
	{
		Camera.ToggleFreeCamera();
		Sleep(175);
	}
	if (Camera.IsFreeCameraActive())
	{
		static int MovementSleepTime = 4;
		if (GetAsyncKeyState(0x51) & 0x8000) //q
		{
			Camera.AdjustCameraSpeed(-0.02f);
			Sleep(50);
		}
		if (GetAsyncKeyState(0x45) & 0x8000) //e
		{
			Camera.AdjustCameraSpeed(0.02f);
			Sleep(50);
		}
		/*if (GetAsyncKeyState(0x54) & 0x8000) //t
		{
			Camera.AdjustCameraRotationSpeed(-0.02f);
			Sleep(50);
		}
		if (GetAsyncKeyState(0x59) & 0x8000) //y
		{
			Camera.AdjustCameraRotationSpeed(0.02f);
			Sleep(50);
		}*/
		if (GetKeyState(0x5A) & 0x8000) //z
		{
			Camera.MoveFreeCamera(DOWN);
			Sleep(MovementSleepTime);
		}
		if (GetAsyncKeyState(0x58) & 0x8000) //x
		{
			Camera.MoveFreeCamera(UP);
			Sleep(MovementSleepTime);
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) //Up arrow key
		{
			Camera.MoveFreeCamera(FORWARD);
			Sleep(MovementSleepTime);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) //Down arrow key
		{
			Camera.MoveFreeCamera(BACKWARD);
			Sleep(MovementSleepTime);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //Right arrow key
		{
			Camera.MoveFreeCamera(RIGHT);
			Sleep(MovementSleepTime);
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //Left arrow key
		{
			Camera.MoveFreeCamera(LEFT);
			Sleep(MovementSleepTime);
		}
	}
	if (GetAsyncKeyState(VK_NUMPAD4))
	{
		std::random_device RandomDevice; // obtain a random number from hardware
		std::mt19937 Generator(RandomDevice()); // seed the generator
		std::uniform_int_distribution<> Distribution(0, 6); // define the range
		int RandError = Distribution(Generator);

		switch (RandError)
		{
		case 0:
			Logger::Log("Random Log Test", LogNone);
			break;
		case 1:
			Logger::Log("Random Log Test", LogInfo);
			break;
		case 2:
			Logger::Log("Random Log Test", LogWarning);
			break;
		case 3:
			Logger::Log("Random Log Test", LogError);
			break;
		case 4:
			Logger::Log("Random Log Test", LogFatalError);
			break;
		case 5:
			Logger::Log("Random Log Test", LogLua);
			break;
		case 6:
			Logger::Log("Random Log Test", LogJson);
			break;
		default:
			Logger::Log("Random Log Test", LogNone);
			break;
		}
		Sleep(5);
	}
	if (GetAsyncKeyState(VK_MBUTTON))
	{
		if (Gui.TweaksMenu->MiddleMouseBoomActive)
		{
			ExplosionCreate(&Gui.TweaksMenu->CustomExplosionInfo, Gui.TweaksMenu->PlayerPtr, Gui.TweaksMenu->PlayerPtr,
				&Gui.TweaksMenu->PlayerPtr->aim_pos, &Gui.TweaksMenu->PlayerPtr->mp_camera_orient, &Gui.TweaksMenu->PlayerPtr->aim_pos, NULL, false);
		}
		//For whatever reason this causes a crash. Might need to call at a specific time to not piss off havok or something.
		/*if (Gui.TweaksMenu.MiddleMouseRepairSphereActive)
		{
			if (Gui.TweaksMenu.PlayerPtr)
			{
				if (Gui.TweaksMenu.RepairPosition == 0)
				{
					const float Radius = Gui.TweaksMenu.RepairRadius;
					const int Duration = Gui.TweaksMenu.RepairDuration;
					rfg_dyn_repair_sphere(&Gui.TweaksMenu.PlayerPtr->Position, Radius, Duration, Gui.TweaksMenu.PlayerPtr);
				}
				else if (Gui.TweaksMenu.RepairPosition == 1)
				{
					const float Radius = Gui.TweaksMenu.RepairRadius;
					const int Duration = Gui.TweaksMenu.RepairDuration;
					rfg_dyn_repair_sphere(&Gui.TweaksMenu.PlayerPtr->aim_pos, Radius, Duration, Gui.TweaksMenu.PlayerPtr);
				}
			}
		}*/
		if (Gui.TweaksMenu->MiddleMouseExplosionsPerSecond >= 1)
		{
			Sleep(1000 / Gui.TweaksMenu->MiddleMouseExplosionsPerSecond);
		}
		else
		{
			Sleep(1000);
		}
	}
	if (GetAsyncKeyState(VK_F1))
	{
		OverlayActive = !OverlayActive;
		///Logger::Log(std::string("Overlay active value: " + std::to_string(OverlayActive)), LogInfo);
		if (OverlayActive)
		{
			if (!Gui.IsLuaConsoleActive())
			{
				SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", MouseGenericPollMouseVisible, 12, true);
				SnippetManager::BackupSnippet("CenterMouseCursorCall", CenterMouseCursorCall, 5, true);
			}
		}
		else
		{
			Gui.DeactivateLuaConsole();
			SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
			SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
		}
		Sleep(150);
	}
	if (GetAsyncKeyState(VK_F2))
	{
		Gui.ShowAppScriptEditor = !Gui.ShowAppScriptEditor;
	}
	/*if (GetAsyncKeyState(VK_F2))
	{
		FirstPersonModeActive = !FirstPersonModeActive;
		Logger::Log(std::string("FPS Mode active value: " + std::to_string(FirstPersonModeActive)), LogInfo);
		Sleep(150);
	}*/
	if (Gui.ShowAppScriptEditor)
	{
		try
		{
			if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x53)) //Ctrl + S
			{
				Gui.ScriptEditor->SaveScript();
			}
		}
		catch (const std::exception& Ex)
		{
			Logger::Log(std::string("Exception when using Ctrl+S save script shortcut. Message: " + std::string(Ex.what())), LogFatalError);
		}
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x53)) //Ctrl + Shift + S
		{
			Gui.ScriptEditor->ShowSaveAsScriptPopup = true;
		}
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x4F)) //Ctrl + O
		{
			Gui.ScriptEditor->ShowOpenScriptPopup = true;
		}
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x4E)) //Ctrl + N
		{
			Gui.ScriptEditor->ShowNewScriptPopup = true;
		}
		try
		{
			if (GetAsyncKeyState(VK_F5))
			{

				std::string ScriptString = Gui.ScriptEditor->GetCurrentScriptString();
				Scripts.RunStringAsScript(ScriptString, "script editor run");
				Sleep(175);
			}
		}
		catch (const std::exception& Ex)
		{
			Logger::Log(std::string("Exception when using F5 run script shortcut. Message: " + std::string(Ex.what())), LogFatalError);
		}
	}
}

void ProgramManager::Exit()
{
	if (OverlayActive || Gui.IsLuaConsoleActive())
	{
		SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true); //Todo: Stop removing from cache and add check to see if exists to BackupSnippet().
		SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
	}
	SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (LONG_PTR)OriginalWndProc);
	Camera.DeactivateFreeCamera(true);

	HideHud(false);
	HideFog(false);

	//Hooks.DisableAllHooksOfType(GAMEHOOK);
	//Hooks.DisableAllHooksOfType(D3D11HOOK);
	Hooks.DisableAllHooks();
	
	ImGui_ImplDX11_InvalidateDeviceObjects(); //Todo: Figure out if this is necessary.
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	if (GlobalPlayerPtr)
	{
		Player* TempPtr = (Player*)GlobalPlayerPtr;
		TempPtr->Flags.invulnerable = false;
	}

	Beep(900, 100);
	Beep(700, 100);
	Beep(600, 200);
	SuccessfulExit = true;
}

void ProgramManager::OpenConsole()
{
	if (OpenDebugConsole)
	{
		FILE *pFile = nullptr;
		PID = GetCurrentProcessId();

		if (AttachConsole(PID) == 0)
		{
			PreExistingConsole = false;
			AllocConsole();
		}
		else
		{
			PreExistingConsole = true;
		}
		freopen_s(&pFile, "CONOUT$", "r+", stdout);

		ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleAttributes(ConsoleDefaultTextAttributes);
	}
}

void ProgramManager::SetMemoryLocations()
{
	uintptr_t ModuleBase = (uintptr_t)GetModuleHandle(NULL);
	InMultiplayer = (DWORD*)(*(DWORD*)(ModuleBase + 0x002CA210));
	if (*(bool*)InMultiplayer)
	{
		MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
		std::cout << "MP detected. Shutting down!\n";
	}
}

void ProgramManager::CreateGameHooks(bool EnableNow)
{
	Hooks.CreateHook("PlayerConstructor", GAMEHOOK,(DWORD*)(ModuleBase + 0x6DECA0), PlayerConstructorHook, (LPVOID*)&PlayerConstructor, EnableNow);
	Hooks.CreateHook("PlayerDoFrame", GAMEHOOK, (DWORD*)(ModuleBase + 0x6D5A80), PlayerDoFrameHook, (LPVOID*)&PlayerDoFrame, EnableNow);
	Hooks.CreateHook("ObjectUpdatePosAndOrient", GAMEHOOK, (DWORD*)(ModuleBase + 0x68C310), ObjectUpdatePosAndOrientHook, (LPVOID*)&ObjectUpdatePosAndOrient, EnableNow);
	Hooks.CreateHook("HumanUpdatePosAndOrient", GAMEHOOK, (DWORD*)(ModuleBase + 0x69AF70), HumanUpdatePosAndOrientHook, (LPVOID*)&HumanUpdatePosAndOrient, EnableNow);
	//Hooks.CreateHook("CharacterControllerSetPos", GAMEHOOK, (DWORD*)(ModuleBase + 0x4153D0), CharacterControllerSetPosHook, (LPVOID*)&CharacterControllerSetPos, EnableNow);
	Hooks.CreateHook("ExplosionCreate", GAMEHOOK, (DWORD*)(ModuleBase + 0x2EC720), ExplosionCreateHook, (LPVOID*)&ExplosionCreate, EnableNow);
	//Hooks.CreateHook("CameraViewDataSetView", GAMEHOOK, (DWORD*)(ModuleBase + 0x2D0290), CameraViewDataSetViewHook, (LPVOID*)&CameraViewDataSetView, EnableNow);
	//Hooks.CreateHook("KeenGraphicsResizeRenderSwapchain", GAMEHOOK, (DWORD*)(ModuleBase + 0x86AB20), KeenGraphicsResizeRenderSwapchainHook, (LPVOID*)&KeenGraphicsResizeRenderSwapchain, EnableNow);

	/*Start of MP Detection Hooks*/
	//Using phony names to make finding the MP hooks a bit more difficult.
	Hooks.CreateHook("CameraViewNormalizeMatrix", GAMEHOOK, (DWORD*)(ModuleBase + 0x1D0DD0), IsValidGameLinkLobbyKaikoHook, (LPVOID*)&IsValidGameLinkLobbyKaiko, EnableNow);
	Hooks.CreateHook("CameraZoomFixAlignment", GAMEHOOK, (DWORD*)(ModuleBase + 0x3CC750), GameMusicMultiplayerStartHook, (LPVOID*)&GameMusicMultiplayerStart, EnableNow);
	Hooks.CreateHook("CameraViewDataFlipMatrix", GAMEHOOK, (DWORD*)(ModuleBase + 0x497740), InitMultiplayerDataItemRespawnHook, (LPVOID*)&InitMultiplayerDataItemRespawn, EnableNow);
	Hooks.CreateHook("CameraViewDataQuaternionTranslate", GAMEHOOK, (DWORD*)(ModuleBase + 0x4F50B0), HudUiMultiplayerProcessHook, (LPVOID*)&HudUiMultiplayerProcess, EnableNow);
	Hooks.CreateHook("CameraViewDataQuaternionRotate", GAMEHOOK, (DWORD*)(ModuleBase + 0x516D80), HudUiMultiplayerEnterHook, (LPVOID*)&HudUiMultiplayerEnter, EnableNow);
	/*End of MP Detection Hooks*/

	Hooks.CreateHook("rl_draw::tristrip_2d_begin", GAMEHOOK, (DWORD*)(ModuleBase + 0x10DDA0), rl_draw_tristrip_2d_begin_hook, (LPVOID*)&rl_draw_tristrip_2d_begin, EnableNow);

	Hooks.CreateHook("world::do_frame", GAMEHOOK, (DWORD*)(ModuleBase + 0x540AB0), world_do_frame_hook, (LPVOID*)&world_do_frame, EnableNow);
	Hooks.CreateHook("rl_camera::render_begin", GAMEHOOK, (DWORD*)(ModuleBase + 0x137660), rl_camera_render_begin_hook, (LPVOID*)&rl_camera_render_begin, EnableNow);
	Hooks.CreateHook("hkpWorld::stepDeltaTime", GAMEHOOK, (DWORD*)(ModuleBase + 0x9E1A70), hkpWorld_stepDeltaTime_hook, (LPVOID*)&hkpWorld_stepDeltaTime, EnableNow);
	Hooks.CreateHook("Application::UpdateTime", GAMEHOOK, (DWORD*)(ModuleBase + 0x5A880), ApplicationUpdateTimeHook, (LPVOID*)&ApplicationUpdateTime, EnableNow);
}

void ProgramManager::CreateD3D11Hooks(bool EnableNow)
{
	Hooks.CreateHook("D3D11Present", D3D11HOOK, (LPVOID)kiero::getMethodsTable()[8], D3D11PresentHook, (LPVOID*)&D3D11PresentObject, EnableNow);
}

bool ProgramManager::ShouldClose()
{
	if (ExitKeysPressCount > 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ProgramManager::Update()
{
	if (ScriptLoaderCloseRequested)
	{
		///std::cout << "Sleeping...\n";
		Sleep(300);
		///std::cout << "Done sleeping.\n";
		ExitKeysPressCount = 10;
	}
	/*if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) //Todo: Figure out if I really need this for the overlay to work.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/
}

void ProgramManager::CloseConsole()
{
	if (PreExistingConsole)
	{
		FreeConsole();
	}
}

bool ProgramManager::LoadDataFromConfig()
{
	std::string ExePath = GetEXEPath(false);
	Logger::Log("Started loading \"Settings.json\".", LogInfo);
	
	if (fs::exists(ExePath + "RFGR Script Loader/Settings/Settings.json"))
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("Parsing \"Settings.json\"", LogInfo);
			std::ifstream Config(ExePath + "RFGR Script Loader/Settings/Settings.json");
			Config >> MainConfig;
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
			CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");
			Logger::Log("\"Settings.json\" not found. Creating from default values.", LogWarning);

			MainConfig["Open debug console"] = false;

			std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/Settings.json");
			ConfigOutput << std::setw(4) << MainConfig << "\n";
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
		OpenDebugConsole = MainConfig["Open debug console"].get<bool>();
		return true;
	}, "Settings.json", "read", "reading"))
	{
		return false;
	}
	Logger::Log("No read exceptions detected.", LogInfo);
	
	Logger::Log("Done loading \"Settings.json\".", LogInfo);
	return true;
}

