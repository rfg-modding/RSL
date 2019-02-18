#include "ProgramManager.h"

//#include <cstdarg>

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
	Gui.SetScriptManager(&Scripts);

	NewObjectPosition.x = 0.0f;
	NewObjectPosition.y = 0.0f;
	NewObjectPosition.z = 0.0f;

	ModuleBase = (uintptr_t)GetModuleHandle(NULL);

	if (!kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
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

	Logger::Log("Now monitoring RFGR State", LogInfo);
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
	} 
	while (RFGRState < 0 || RFGRState > 63); //Todo: Consider changing to hex values for consistency with enum definition. Alternatively change enum to decimal.
	Logger::Log(std::string("RFGR State > 0. Value: " + std::to_string(RFGRState)), LogInfo);

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
			Logger::Log("Waiting for ImGui to be initialized.", LogInfo);
		}
		EndTime = StartTime;
		StartTime = std::chrono::steady_clock::now();
	}

	Beep(600, 100);
	Beep(700, 100);
	Beep(900, 200);

	///ZeroMemory(&msg, sizeof(msg));
}

void ProgramManager::ProcessInput()
{
	if ((GetAsyncKeyState(VK_OEM_3))) //126 = virtual keycode for tilde
	{
		Logger::Log("Tilde pressed", LogInfo);
		Gui.ToggleLuaConsole();
		if (Gui.IsLuaConsoleActive())
		{
			Gui.Console.InputBuffer.clear();
			/*if (Gui.Console.InputBuffer[Gui.Console.InputBuffer.length() - 1] == '`')
			{
				Gui.Console.InputBuffer[Gui.Console.InputBuffer.length() - 1] = '\0';
			}*/
			Gui.Console.ReclaimFocus = true; //Tell console to set focus to it's text input.
			if (!OverlayActive)
			{
				SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", MouseGenericPollMouseVisible, 12, true);
				SnippetManager::BackupSnippet("CenterMouseCursorCall", CenterMouseCursorCall, 5, true);
			}
		}
		else
		{
			/*if (Gui.Console.InputBuffer[Gui.Console.InputBuffer.length() - 1] == '`')
			{
				Gui.Console.InputBuffer[Gui.Console.InputBuffer.length() - 1] = '\0';
			}*/
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
		Scripts.RunTestScript();
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_NUMPAD2))
	{
		std::string ExePath = GetEXEPath(false);
		Scripts.RunTestScript2();
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_NUMPAD3))
	{
		std::random_device RandomDevice; // obtain a random number from hardware
		std::mt19937 Generator(RandomDevice()); // seed the generator
		std::uniform_int_distribution<> Distribution(0, 5); // define the range
		int RandError = Distribution(Generator);

		switch (RandError)
		{
		case 0:
			Logger::Log("Random Log Test", LogInfo);
			break;
		case 1:
			Logger::Log("Random Log Test", LogWarning);
			break;
		case 2:
			Logger::Log("Random Log Test", LogError);
			break;
		case 3:
			Logger::Log("Random Log Test", LogFatalError);
			break;
		case 4:
			Logger::Log("Random Log Test", LogLua);
			break;
		case 5:
			Logger::Log("Random Log Test", LogJson);
			break;
		default:
			Logger::Log("Random Log Test", LogNone);
			break;
		}
		Sleep(5);
	}
	if (GetAsyncKeyState(VK_F1))
	{
		OverlayActive = !OverlayActive;
		Logger::Log(std::string("Overlay active value: " + std::to_string(OverlayActive)), LogInfo);
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
		FirstPersonModeActive = !FirstPersonModeActive;
		Logger::Log(std::string("FPS Mode active value: " + std::to_string(FirstPersonModeActive)), LogInfo);
		Sleep(150);
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
	
	//Hooks.DisableAllHooksOfType(GAMEHOOK);
	//Hooks.DisableAllHooksOfType(D3D11HOOK);
	Hooks.DisableAllHooks();
	
	ImGui_ImplDX11_InvalidateDeviceObjects(); //Todo: Figure out if this is necessary.
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

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
	Hooks.CreateHook("CameraViewDataSetView", GAMEHOOK, (DWORD*)(ModuleBase + 0x2D0290), CameraViewDataSetViewHook, (LPVOID*)&CameraViewDataSetView, EnableNow);
	//Hooks.CreateHook("KeenGraphicsResizeRenderSwapchain", GAMEHOOK, (DWORD*)(ModuleBase + 0x86AB20), KeenGraphicsResizeRenderSwapchainHook, (LPVOID*)&KeenGraphicsResizeRenderSwapchain, EnableNow);

	/*Start of MP Detection Hooks*/
	//Using phony names to make finding the MP hooks a bit harder to find.
	Hooks.CreateHook("CameraViewNormalizeMatrix", GAMEHOOK, (DWORD*)(ModuleBase + 0x1D0DD0), IsValidGameLinkLobbyKaikoHook, (LPVOID*)&IsValidGameLinkLobbyKaiko, EnableNow);
	Hooks.CreateHook("CameraZoomFixAlignment", GAMEHOOK, (DWORD*)(ModuleBase + 0x3CC750), GameMusicMultiplayerStartHook, (LPVOID*)&GameMusicMultiplayerStart, EnableNow);
	Hooks.CreateHook("CameraViewDataFlipMatrix", GAMEHOOK, (DWORD*)(ModuleBase + 0x497740), InitMultiplayerDataItemRespawnHook, (LPVOID*)&InitMultiplayerDataItemRespawn, EnableNow);
	Hooks.CreateHook("CameraViewDataQuaternionTranslate", GAMEHOOK, (DWORD*)(ModuleBase + 0x4F50B0), HudUiMultiplayerProcessHook, (LPVOID*)&HudUiMultiplayerProcess, EnableNow);
	Hooks.CreateHook("CameraViewDataQuaternionRotate", GAMEHOOK, (DWORD*)(ModuleBase + 0x516D80), HudUiMultiplayerEnterHook, (LPVOID*)&HudUiMultiplayerEnter, EnableNow);
	/*End of MP Detection Hooks*/

	Hooks.CreateHook("rl_draw::tristrip_2d_begin", GAMEHOOK, (DWORD*)(ModuleBase + 0x10DDA0), rl_draw_tristrip_2d_begin_hook, (LPVOID*)&rl_draw_tristrip_2d_begin, EnableNow);
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

