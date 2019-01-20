#pragma once
//#include "Globals.h"
//#include "CameraWrapper.h"
//#include "FunctionManager.h"
//#include "Hooks.h"
#include "ScriptManager.h"

//#include "Polyhook2/Enums.hpp"

class ProgramManager
{
public:
	ProgramManager(HMODULE hModule);
	~ProgramManager();

	void Initialize();
	void OpenConsole();
	bool LoadDataFromConfig();
	void SetMemoryLocations();

	void CreateGameHooks(bool EnableNow);
	void CreateD3D11Hooks(bool EnableNow);

	bool ShouldClose();
	void ProcessInput();
	void Update();
	MSG msg;

	void CloseConsole();
	void Exit();

	HMODULE ScriptLoaderModule;
	HWND GameWindowHandle;

	CameraWrapper Camera;
	FunctionManager Functions;
	ScriptManager Scripts;
	HookManager Hooks;

	/*bool show_demo_window = true;
	bool ImGuiInitialized = false;
	ImGuiIO io;
	bool OverlayActive = false;
	WNDPROC OriginalWndProc;*/

	bool LoadFailed = false;
	bool PreExistingConsole = true;
	DWORD PID = 0;
	uintptr_t ModuleBase = 0;
	unsigned int ExitKeysPressCount = 0;

	DWORD MouseGenericPollMouseVisible;
	DWORD CenterMouseCursorCall;

	bool SuccessfulExit = false;
};

