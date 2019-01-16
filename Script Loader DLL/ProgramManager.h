#pragma once
//#include "Globals.h"
#include "CameraWrapper.h"
#include "FunctionManager.h"
#include "ScriptManager.h"
#include "Hooks.h"

//#include "Polyhook2/Enums.hpp"

class ProgramManager
{
public:
	ProgramManager(HMODULE hModule);
	~ProgramManager();

	enum TestEnum
	{
		One,
		Two,
		Three
	};

	void Initialize();
	void OpenConsole();
	bool LoadDataFromConfig();
	void SetMemoryLocations();

	void CreateGameHooks();
	void EnableGameHooks();
	void DisableGameHooks();
	//void __cdecl ExplosionCreateHook(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position, matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer);

	void CreateD3D11Hooks();
	void EnableD3D11Hooks();
	void DisableD3D11Hooks();
	//HRESULT FORCEINLINE D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(IDXGISwapChain *pSwapChain, ID3D11Device **ppDevice, ID3D11DeviceContext **ppContext);
	//HRESULT __stdcall D3D11PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	
	//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
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

