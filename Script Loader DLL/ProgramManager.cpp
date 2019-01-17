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
	DisableGameHooks();
	DisableD3D11Hooks();

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

	if (!kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		ConsoleLog(std::string("Kiero error: " + std::to_string(kiero::init(kiero::RenderType::D3D11))).c_str(), LOGFATALERROR, false, true, true);
		ConsoleLog("Failed to initialize kiero for D3D11. RFGR Script loader deactivating.\n", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_Initialize() != MH_OK)
	{
		ConsoleLog("Failed to initialize MinHook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}

	GameWindowHandle = find_main_window(GetProcessID("rfg.exe"));
	///OriginalWndProc = (WNDPROC)GetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC);//(WNDPROC)SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	///OriginalWndProc = (WNDPROC)SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);

	CreateGameHooks();
	EnableGameHooks();
#if !PublicMode
	ConsoleLog("Finished hooking game functions.", LOGSUCCESS, false, true, true);
#endif

	//FindPattern((char*)"rfg.exe", (char*)"", (char*)"");
	MouseGenericPollMouseVisible = FindPattern((char*)"rfg.exe", (char*)"\x84\xD2\x74\x08\x38\x00\x00\x00\x00\x00\x75\x02", (char*)"xxxxx?????xx");
	CenterMouseCursorCall = FindPattern((char*)"rfg.exe", (char*)"\xE8\x00\x00\x00\x00\x89\x46\x4C\x89\x56\x50", (char*)"x????xxxxxx");

	ConsoleLog("Now monitoring RFGR State", LOGMESSAGE, false, true, true);
	GameState RFGRState;
	auto StartTime = std::chrono::steady_clock::now();
	auto EndTime = std::chrono::steady_clock::now();
	long long TimeElapsed = 0LL;
	do
	{
		TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
		if (TimeElapsed > 1000LL) //Todo: Figure out if casting 1000 as a long long is necessary in this case or ever.
		{
			std::cout << "TimeElapsed: " << TimeElapsed << std::endl;
			RFGRState = GameseqGetState();
			std::cout << "Current RFGR State: " << (UINT32)RFGRState << std::endl;
			//Sleep(1000);
			StartTime = EndTime;
		}
		EndTime = std::chrono::steady_clock::now();
	} 
	while (RFGRState < 0 || RFGRState > 63); //Todo: Consider changing to hex values for consistency with enum definition. Alternatively change enum to decimal.
	ConsoleLog(std::string("RFGR State > 0. Value: " + std::to_string(RFGRState)).c_str(), LOGSUCCESS, false, true, true);

	OriginalWndProc = (WNDPROC)SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	ConsoleLog("Custom WndProc set.", LOGMESSAGE, false, true, true);
	CreateD3D11Hooks();
	EnableD3D11Hooks();
	ConsoleLog("D3D11 hooks created and enabled.", LOGMESSAGE, false, true, true);
#if !PublicMode
	ConsoleLog("Finished hooking D3D11 functions.", LOGSUCCESS, false, true, true);
#endif

	Sleep(5000);

	StartTime = std::chrono::steady_clock::now();
	EndTime = std::chrono::steady_clock::now();
	while (!ImGuiInitialized) //ImGui Initialization done in D3DPresentHook in Hooks.cpp
	{
		long long TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
		//std::cout << "ImGui TimeElapsed: " << TimeElapsed << std::endl;
		if (TimeElapsed > 2000LL) 
		{
			ConsoleLog("Waiting for ImGui to be initialized.", LOGMESSAGE, false, true, true);
			//Sleep(2000);
		}
		EndTime = StartTime;
		StartTime = std::chrono::steady_clock::now();
	}

	Beep(600, 100);
	Beep(700, 100);
	Beep(900, 200);

	ZeroMemory(&msg, sizeof(msg));
}

void ProgramManager::ProcessInput()
{
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
		//Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test2.lua", sol::load_mode::text);
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_F1))
	{
		OverlayActive = !OverlayActive;
		ConsoleLog(std::string("Overlay active value: " + std::to_string(OverlayActive)).c_str(), LOGMESSAGE, false, true, true);
		if (OverlayActive)
		{
			//OriginalWndProc = (WNDPROC)SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			///SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", MouseGenericPollMouseVisible, 12, true);
			SnippetManager::BackupSnippet("CenterMouseCursorCall", CenterMouseCursorCall, 5, true);
		}
		else
		{
			///SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (LONG_PTR)OriginalWndProc);
			SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true); //Todo: Stop removing from cache and add check to see if exists to BackupSnippet().
			SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
		}
		Sleep(150);
	}
	if (GetAsyncKeyState(VK_F2))
	{
		FirstPersonModeActive = !FirstPersonModeActive;
		ConsoleLog(std::string("FPS Mode active value: " + std::to_string(FirstPersonModeActive)).c_str(), LOGMESSAGE, false, true, true);
		Sleep(150);
	}
}

void ProgramManager::Exit()
{
	if (OverlayActive)
	{
		//SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (LONG_PTR)OriginalWndProc);
		SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true); //Todo: Stop removing from cache and add check to see if exists to BackupSnippet().
		SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
	}
	SetWindowLongPtr(GameWindowHandle, GWLP_WNDPROC, (LONG_PTR)OriginalWndProc);
	
	DisableGameHooks();
	DisableD3D11Hooks();
	//Beep(220, 100); //Todo: Consider removing this in release version.
	
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
			//std::cout << "AllocConsole()" << std::endl << std::endl;
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
		std::cout << "MP detected. Shutting down!" << std::endl;
	}
}

void ProgramManager::CreateGameHooks()
{
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x6DECA0), PlayerConstructorHook, (LPVOID*)&PlayerConstructor) != MH_OK)
	{
		ConsoleLog("Failed to create PlayerConstructor() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x6D5A80), PlayerDoFrameHook, (LPVOID*)&PlayerDoFrame) != MH_OK)
	{
		ConsoleLog("Failed to create PlayerDoFrame() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x68C310), ObjectUpdatePosAndOrientHook, (LPVOID*)&ObjectUpdatePosAndOrient) != MH_OK)
	{
		ConsoleLog("Failed to create ObjectUpdatePosAndOrient() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x69AF70), HumanUpdatePosAndOrientHook, (LPVOID*)&HumanUpdatePosAndOrient) != MH_OK)
	{
		ConsoleLog("Failed to create HumanUpdatePosAndOrient() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	/*if (MH_CreateHook((DWORD*)(ModuleBase + 0x4153D0), CharacterControllerSetPosHook, (LPVOID*)&CharacterControllerSetPos) != MH_OK)
	{
		ConsoleLog("Failed to create CharacterControllerSetPos() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}*/
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x2EC720), ExplosionCreateHook, (LPVOID*)&ExplosionCreate) != MH_OK)
	{
		ConsoleLog("Failed to create ExplosionCreate() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x2D0290), CameraViewDataSetViewHook, (LPVOID*)&CameraViewDataSetView) != MH_OK)
	{
		ConsoleLog("Failed to create CameraViewDataSetView() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}

	/*Start of MP Detection Hooks*/
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x1D0DD0), IsValidGameLinkLobbyKaikoHook, (LPVOID*)&IsValidGameLinkLobbyKaiko) != MH_OK)
	{
		ConsoleLog("Failed to create nameless hook 1. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x3CC750), GameMusicMultiplayerStartHook, (LPVOID*)&GameMusicMultiplayerStart) != MH_OK)
	{
		ConsoleLog("Failed to create nameless hook 2. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x497740), InitMultiplayerDataItemRespawnHook, (LPVOID*)&InitMultiplayerDataItemRespawn) != MH_OK)
	{
		ConsoleLog("Failed to create nameless hook 3. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x4F50B0), HudUiMultiplayerProcessHook, (LPVOID*)&HudUiMultiplayerProcess) != MH_OK)
	{
		ConsoleLog("Failed to create nameless hook 4. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_CreateHook((DWORD*)(ModuleBase + 0x516D80), HudUiMultiplayerEnterHook, (LPVOID*)&HudUiMultiplayerEnter) != MH_OK)
	{
		ConsoleLog("Failed to create nameless hook 5. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	/*End of MP Detection Hooks*/

	/*if (MH_CreateHook((DWORD*)(ModuleBase + 0x86AB20), KeenGraphicsResizeRenderSwapchainHook, (LPVOID*)&KeenGraphicsResizeRenderSwapchain) != MH_OK)
	{
		ConsoleLog("Failed to create KeenGraphicsResizeRenderSwapchain() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}*/
}

void ProgramManager::EnableGameHooks()
{
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x6DECA0)) != MH_OK)
	{
		ConsoleLog("Failed to enable PlayerConstructor() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x6D5A80)) != MH_OK)
	{
		ConsoleLog("Failed to enable PlayerDoFrame() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x68C310)) != MH_OK)
	{
		ConsoleLog("Failed to enable ObjectUpdatePosAndOrient() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x69AF70)) != MH_OK)
	{
		ConsoleLog("Failed to enable HumanUpdatePosAndOrient() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	/*if (MH_EnableHook((DWORD*)(ModuleBase + 0x4153D0)) != MH_OK)
	{
		ConsoleLog("Failed to enable CharacterControllerSetPos() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}*/
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x2EC720)) != MH_OK)
	{
		ConsoleLog("Failed to enable ExplosionCreate() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x2D0290)) != MH_OK)
	{
		ConsoleLog("Failed to enable CameraViewDataSetView() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}

	/*Start of MP Detection Hooks*/
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x1D0DD0)) != MH_OK)
	{
		ConsoleLog("Failed to enable nameless hook 1. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x3CC750)) != MH_OK)
	{
		ConsoleLog("Failed to enable nameless hook 2. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x497740)) != MH_OK)
	{
		ConsoleLog("Failed to enable nameless hook 3. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x4F50B0)) != MH_OK)
	{
		ConsoleLog("Failed to enable nameless hook 4. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_EnableHook((DWORD*)(ModuleBase + 0x516D80)) != MH_OK)
	{
		ConsoleLog("Failed to enable nameless hook 5. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	/*End of MP Detection Hooks*/

	/*if (MH_EnableHook((DWORD*)(ModuleBase + 0x86AB20)) != MH_OK)
	{
		ConsoleLog("Failed to enable KeenGraphicsResizeRenderSwapchain() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}*/
}

void ProgramManager::DisableGameHooks()
{
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x6DECA0)) != MH_OK)
	{
		ConsoleLog("Failed to disable PlayerConstructor() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x6D5A80)) != MH_OK)
	{
		ConsoleLog("Failed to disable PlayerDoFrame() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x68C310)) != MH_OK)
	{
		ConsoleLog("Failed to disable ObjectUpdatePosAndOrient() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x69AF70)) != MH_OK)
	{
		ConsoleLog("Failed to disable HumanUpdatePosAndOrient() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}
	/*if (MH_DisableHook((DWORD*)(ModuleBase + 0x4153D0)) != MH_OK)
	{
		ConsoleLog("Failed to disable CharacterControllerSetPos() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}*/
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x2EC720)) != MH_OK)
	{
		ConsoleLog("Failed to disable ExplosionCreate() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x2D0290)) != MH_OK)
	{
		ConsoleLog("Failed to disable CameraViewDataSetView() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}

	/*Start of MP Detection Hooks*/
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x1D0DD0)) != MH_OK)
	{
		ConsoleLog("Failed to disable nameless hook 1. RFGR might crash.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x3CC750)) != MH_OK)
	{
		ConsoleLog("Failed to disable nameless hook 2. RFGR might crash.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x497740)) != MH_OK)
	{
		ConsoleLog("Failed to disable nameless hook 3. RFGR might crash.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x4F50B0)) != MH_OK)
	{
		ConsoleLog("Failed to disable nameless hook 4. RFGR might crash.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	if (MH_DisableHook((DWORD*)(ModuleBase + 0x516D80)) != MH_OK)
	{
		ConsoleLog("Failed to disable nameless hook 5. RFGR might crash.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
	/*End of MP Detection Hooks*/

	/*if (MH_DisableHook((DWORD*)(ModuleBase + 0x86AB20)) != MH_OK)
	{
		ConsoleLog("Failed to disable KeenGraphicsResizeRenderSwapchain() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}*/
}

void ProgramManager::CreateD3D11Hooks()
{
	if (MH_CreateHook((LPVOID)kiero::getMethodsTable()[8], D3D11PresentHook, (LPVOID*)&D3D11PresentObject) != MH_OK)
	{
		ConsoleLog("Failed to create D3D11Present() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		DisableGameHooks();
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
}

void ProgramManager::EnableD3D11Hooks()
{
	if (MH_EnableHook((LPVOID)kiero::getMethodsTable()[8]) != MH_OK)
	{
		ConsoleLog("Failed to enable D3D11Present() hook. RFGR Script loader deactivating.", LOGFATALERROR, false, true, true);
		DisableGameHooks();
		FreeLibraryAndExitThread(ScriptLoaderModule, 0);
		return;
	}
}

void ProgramManager::DisableD3D11Hooks()
{
	if (MH_DisableHook((LPVOID)kiero::getMethodsTable()[8]) != MH_OK)
	{
		ConsoleLog("Failed to disable D3D11Present() hook. RFGR might crash.", LOGFATALERROR, false, true, true);
	}
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
	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) //Todo: Figure out if I really need this for the overlay to work.
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
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
	fs::remove(ExePath + "RFGR Script Loader/Logs/Load Log.txt");
	std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Load Log.txt");

	if (fs::exists(ExePath + "RFGR Script Loader/Settings/Settings.txt"))
	{
		//LogFile << "Settings.txt found. Loading into string buffer..." << std::endl;
		std::ifstream Config(ExePath + "RFGR Script Loader/Settings/Settings.txt");
		//LogFile << "Preparing to parse..." << std::endl;

		try
		{
			LogFile << "Parsing settings.txt..." << std::endl;
			Config >> MainConfig;
			Config.close();
			//MainConfig.parse(Buffer);
			//LogFile << "Done parsing settings.txt" << std::endl;
		}
		catch (nlohmann::json::parse_error& Exception)
		{
			LogFile << "Exception when parsing settings.txt!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("Exception when parsing Settings.txt!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed parse Settings.txt, exiting." << std::endl;
			return false;
		}
		catch (...)
		{
			LogFile << "Default exception when parsing settings.txt!" << std::endl;

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception while parsing Settings.txt", "Json parsing exception", MB_OK);
			LogFile << "Failed parse Settings.txt, exiting." << std::endl;
			return false;
		}
		/*catch (nlohmann::json::basic_json::invalid_iterator& Exception)
		{

		}
		catch (nlohmann::json::basic_json::type_error& Exception)
		{

		}
		catch (nlohmann::json::basic_json::out_of_range& Exception)
		{

		}
		catch (nlohmann::json::basic_json::other_error& Exception)
		{

		}*/
		LogFile << "No parse exceptions detected." << std::endl;
	}
	else
	{
		CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");
		LogFile << "Settings.txt not found. Creating from default values." << std::endl;

		MainConfig["Open debug console"] = false;

		std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/Settings.txt");
		ConfigOutput << std::setw(4) << MainConfig << std::endl;
		ConfigOutput.close();
	}
	
	//LogFile << "Setting internal values." << std::endl;

	OpenDebugConsole = MainConfig["Open debug console"].get<bool>();

	//LogFile << "Returning true and closing log file." << std::endl;
	LogFile.close();
	return true;
}

