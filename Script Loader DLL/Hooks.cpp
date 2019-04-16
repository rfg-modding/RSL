#include "Hooks.h"
#include "ProgramManager.h"

D3D11Present D3D11PresentObject;

//MainOverlay Overlay;
GuiSystem Gui;

std::chrono::steady_clock::time_point ExplosionTimerBegin;
std::chrono::steady_clock::time_point ExplosionTimerEnd;

std::once_flag HookD3D11PresentInitialCall;
std::once_flag HookExplosionCreateInitialCall;
explosion_info NewExplosionInfo;

Player NewPlayerObject;
std::once_flag HookPlayerDoFrameInitialCall;
bool GlobalPlayerPtrInitialized = false;

//camera_view_data::set_view()
CameraViewData NewCameraViewData;
CameraViewTableEntry NewCameraViewTableEntry;
bool NewSkipTransition;

std::once_flag HookObjectUpdatePosAndOrientInitialCall;
std::once_flag HookHumanUpdatePosAndOrientInitialCall;
vector NewObjectPosition;

bool UpdateD3D11Pointers = true;

std::once_flag HookRlDrawTristip2dInitialCall;
std::once_flag HookWorldDoFrameInitialCall;

std::once_flag HookRlCameraRenderBegin;
std::once_flag HookhkpWorld_stepDeltaTime;
std::once_flag HookApplicationUpdateTime;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ProcessInput(hWnd, msg, wParam, lParam);
	if (OverlayActive || Gui.IsLuaConsoleActive())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		if (msg == WM_SIZE)
		{
			Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
			ImGui_ImplDX11_InvalidateDeviceObjects();
			UpdateD3D11Pointers = true;
			D3D11Context->OMSetRenderTargets(0, 0, 0);
			MainRenderTargetView->Release();
			return CallWindowProc(OriginalWndProc, hwnd, msg, wParam, lParam);
		}
		return true;
	}

	switch (msg)
	{
		case WM_SIZE:
			Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
			ImGui_ImplDX11_InvalidateDeviceObjects();
			UpdateD3D11Pointers = true;
			D3D11Context->OMSetRenderTargets(0, 0, 0);
			MainRenderTargetView->Release();
			break;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return CallWindowProc(OriginalWndProc, hwnd, msg, wParam, lParam);
	//return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool MiddleMouseDown = false;
	if(!Gui.Ready())
	{
		return 0;
	}
	switch(msg)
	{
	case WM_KEYDOWN:
		if(GlobalCamera->IsFreeCameraActive())
		{
			switch(wParam)
			{
			case 0x51: //q
				GlobalCamera->CameraSpeed -= 0.02f;
				break;
			case 0x45: //e
				GlobalCamera->CameraSpeed += 0.02f;
				break;
			case 0x5A: //z
				GlobalCamera->MoveFreeCamera(DOWN);
				break;
			case 0x58: //x
				GlobalCamera->MoveFreeCamera(UP);	
				break;
			case VK_UP: //Up arrow key
				GlobalCamera->MoveFreeCamera(FORWARD);
				break;
			case VK_DOWN: //Down arrow key
				GlobalCamera->MoveFreeCamera(BACKWARD);
				break;
			case VK_RIGHT: //Right arrow key
				GlobalCamera->MoveFreeCamera(RIGHT);
				break;
			case VK_LEFT: //Left arrow key
				GlobalCamera->MoveFreeCamera(LEFT);
				break;
			default:
				break;
			}
		}
		switch(wParam)
		{
		case VK_F1:
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
			//Sleep(150);
			break;
		case VK_F2:
			Gui.ShowAppScriptEditor = !Gui.ShowAppScriptEditor;
			break;
		case VK_NUMPAD1:
			ToggleHud();
			break;
		case VK_NUMPAD2:
			ToggleFog();
			break;
		case VK_NUMPAD3:
			GlobalCamera->ToggleFreeCamera();
			break;
		case VK_OEM_3: //Tilde
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
			break;
		case VK_F3:
			GlobalProgram->ExitKeysPressCount++;
			break;
		default:
			break;
		}
		break;
	case WM_MBUTTONDOWN:
		MiddleMouseDown = true;
		break;
	case WM_MBUTTONUP:
		MiddleMouseDown = false;
		break;
	default:
		break;
	}

	if (MiddleMouseDown && Gui.TweaksMenu->MiddleMouseBoomActive)
	{
		ExplosionTimerEnd = std::chrono::steady_clock::now();
		std::cout << "Time since last explosion spawn: " << std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() << "\n";
		if (std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() > 1000 / Gui.TweaksMenu->MiddleMouseExplosionsPerSecond)
		{
			ExplosionCreate(&Gui.TweaksMenu->CustomExplosionInfo, Gui.TweaksMenu->PlayerPtr, Gui.TweaksMenu->PlayerPtr,
				&Gui.TweaksMenu->PlayerPtr->aim_pos, &Gui.TweaksMenu->PlayerPtr->mp_camera_orient, &Gui.TweaksMenu->PlayerPtr->aim_pos, NULL, false);
			ExplosionTimerBegin = std::chrono::steady_clock::now();
		}
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
				if(Gui.HasValidScriptManager())
				{
					std::string ScriptString = Gui.ScriptEditor->GetCurrentScriptString();
					Gui.GetScriptManager()->RunStringAsScript(ScriptString, "script editor run");
					Sleep(175);
				}
			}
		}
		catch (const std::exception& Ex)
		{
			Logger::Log(std::string("Exception when using F5 run script shortcut. Message: " + std::string(Ex.what())), LogFatalError);
		}
	}
	return 0;
}

HRESULT D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(IDXGISwapChain * pSwapChain, ID3D11Device ** ppDevice, ID3D11DeviceContext ** ppContext)
{
	HRESULT Result = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if(Result != S_OK)
	{
		Logger::Log(std::string("ID3D11SwapChain::GetDevice() failed, return value: " + std::to_string(Result)), LogFatalError);
		return E_FAIL;
	}
	(*ppDevice)->GetImmediateContext(ppContext);

	return Result;
}

HRESULT __stdcall D3D11PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	std::call_once(HookD3D11PresentInitialCall, [&]()
	{
#if !PublicMode
		Logger::ConsoleLog("First time in D3D11Present() hook.", LogInfo, false, true, true);
#endif
		ExplosionTimerBegin = std::chrono::steady_clock::now();
		HRESULT Result = D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(pSwapChain, &D3D11Device, &D3D11Context);
		if (Result != S_OK)
		{
			Logger::Log(std::string("D3D11DeviceContextFromSwapchain() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}
		D3D11SwapchainPtr = pSwapChain;
		//
		ID3D11Texture2D* BackBuffer;
		Result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
		if (Result != S_OK)
		{
			Logger::Log(std::string("GetBuffer() failed, return value: " + std::to_string(Result)).c_str(), LogFatalError);
			return E_FAIL;
		}

		D3D11_RENDER_TARGET_VIEW_DESC desc = {};
		memset(&desc, 0, sizeof(desc));
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // most important change!
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		Result = D3D11Device->CreateRenderTargetView(BackBuffer, &desc, &MainRenderTargetView);
		if (Result != S_OK)
		{
			Logger::Log(std::string("CreateRenderTargetView() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}
		BackBuffer->Release();

		/*DXGI_SWAP_CHAIN_DESC SwapChainDescription;
		pSwapChain->GetDesc(&SwapChainDescription);
		Logger::ConsoleLog(std::string("Initial buffer count: " + std::to_string(SwapChainDescription.BufferCount)).c_str(), LogWarning, false, true, true);
		Logger::ConsoleLog(std::string("Initial flags: " + std::to_string(SwapChainDescription.Flags)).c_str(), LogWarning, false, true, true);
		Logger::ConsoleLog(std::string("Initial format: " + std::to_string(SwapChainDescription.BufferDesc.Format)).c_str(), LogWarning, false, true, true);*/

		Logger::Log("Initializing ImGui.", LogInfo);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();

		ImGui_ImplDX11_Init(D3D11Device, D3D11Context);
		hwnd = find_main_window(GetProcessID("rfg.exe"));
		bool RectResult = GetWindowRect(hwnd, &WindowRect);
		if (!RectResult)
		{
			std::cout << "GetWindowRect Failed! Result: " << GetLastError() << "\n";
			//Sleep(10000);
		}
		else
		{
			//Logger::Log("GetWindowRect() Succeeded", LogWarning);
		}
		ImGui_ImplWin32_Init(hwnd);

		ImGuiIO& io = ImGui::GetIO();
		float GlobalFontSize = 17.0f;
		std::string DefaultFontPath = std::string(GetEXEPath(false) + "RFGR Script Loader/Fonts/Roboto-Regular.ttf");
		bool DefaultFontLoaded = false;
		if (fs::exists(DefaultFontPath))
		{	
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalFontSize);
			DefaultFontLoaded = true;
		}
		else
		{
			//Logger::Log("DroidSans.ttf not found. Using default font.", LogInfo);
			io.Fonts->AddFontDefault();
		}

		//Logger::Log("Merging FontAwesome...", LogWarning);
		static const ImWchar IconsRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig IconsConfig;
		IconsConfig.MergeMode = true;
		IconsConfig.PixelSnapH = true;
		std::string FontAwesomeSolidPath(GetEXEPath(false) + "RFGR Script Loader/Fonts/fa-solid-900.ttf");
		Logger::Log(FontAwesomeSolidPath, LogWarning);
		FontNormal = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalFontSize, &IconsConfig, IconsRanges);
		//Logger::Log("Done merging FontAwesome...", LogWarning);
		
		float GlobalBigFontSize = 24.0f;
		if (DefaultFontLoaded)
		{
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalBigFontSize);
		}
		FontBig = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalBigFontSize, &IconsConfig, IconsRanges);

		/*Start of FontLarge loading*/
		float GlobalLargeFontSize = 35.0f;
		if (DefaultFontLoaded)
		{
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalLargeFontSize);
		}
		FontLarge = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalLargeFontSize, &IconsConfig, IconsRanges);
		/*End of FontLarge loading*/

		/*Start of FontHuge loading*/
		float GlobalHugeFontSize = 70.0f;
		if (DefaultFontLoaded)
		{
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalHugeFontSize);
		}
		FontHuge = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalHugeFontSize, &IconsConfig, IconsRanges);
		/*End of FontHuge loading*/

		
		//Overlay.Initialize();
		Gui.Initialize();
		ImGuiInitialized = true;
		UpdateD3D11Pointers = false;

		//static RenderInterfaceD3D11 RenderInterface(D3D11Device, D3D11Context);
		//dd::initialize(&RenderInterface);

		Logger::Log("ImGui Initialized.", LogInfo);
		return S_OK;
	});

	if (UpdateD3D11Pointers)
	{
		Logger::Log("UpdateD3D11Pointers = true. Reforming MainRenderTargetView and ImGui DX11 Devices.", LogWarning);

		HRESULT Result;

		Result = D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(pSwapChain, &D3D11Device, &D3D11Context);
		if (Result != S_OK)
		{
			Logger::Log(std::string("D3D11DeviceContextFromSwapchain() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}
		D3D11SwapchainPtr = pSwapChain;
		//
		ID3D11Texture2D* BackBuffer;
		Result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
		if (Result != S_OK)
		{
			Logger::Log(std::string("GetBuffer() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}

		Result = D3D11Device->CreateRenderTargetView(BackBuffer, NULL, &MainRenderTargetView);
		if (Result != S_OK)
		{
			Logger::Log(std::string("CreateRenderTargetView() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}

		BackBuffer->Release();

		//ImGui_ImplDX11_Init(D3D11Device, D3D11Context);
		ImGui_ImplDX11_CreateDeviceObjects();
		Logger::Log("Finished reforming after resize.", LogInfo);
		UpdateD3D11Pointers = false;
	}
	if (!ImGuiInitialized)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}
	/*if (!OverlayActive)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}*/

	if (!ScriptLoaderCloseRequested)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
#if !PublicMode
		if (OverlayActive)
		{
			if (show_demo_window)
			{
				ImGui::ShowDemoWindow(&show_demo_window);
			}
		}
#endif
		Gui.Draw();
		D3D11Context->OMSetRenderTargets(1, &MainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		//if(GlobalPlayerPtr)
		//{
		//	const ddVec3 boxColor = { 0.0f, 0.8f, 0.8f };
		//	const ddVec3 boxCenter = { GlobalPlayerPtr->Position.x, GlobalPlayerPtr->Position.y, GlobalPlayerPtr->Position.z };

		//	dd::box(boxCenter, boxColor, 1.5f, 1.5f, 1.5f);
		//	dd::cross(boxCenter, 1.0f);
		//}
		//dd::flush();
	}

	return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
}

bool __cdecl KeenGraphicsResizeRenderSwapchainHook(void* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight)
{
	//Logger::Log("In KeenGraphicsResizeSwapchainHook()", LogFatalError);
	//std::cout << "NewWidth: " << NewWidth << ", NewHeight: " << NewHeight << "\n";
	UpdateD3D11Pointers = true;

	return KeenGraphicsResizeRenderSwapchain(KeenSwapchain, NewWidth, NewHeight);
}

void __fastcall PlayerConstructorHook(Player* PlayerPtr)
{
	GlobalPlayerPtr = PlayerPtr;
	//Overlay.PlayerPtr = PlayerPtr;
	Gui.SetPlayerPtr(PlayerPtr);
	if (!GlobalPlayerPtrInitialized)
	{
		GlobalPlayerPtrInitialized = true;
	}

	return PlayerConstructor(PlayerPtr);
}

void __fastcall PlayerDoFrameHook(Player* PlayerPtr)
{
	std::call_once(HookPlayerDoFrameInitialCall, [&]()
	{
		if (!GlobalPlayerPtrInitialized)
		{
			GlobalPlayerPtr = PlayerPtr;
			GlobalPlayerPtrInitialized = true;

			//Overlay.PlayerPtr = PlayerPtr;
			Gui.SetPlayerPtr(PlayerPtr);
			ScriptManager* Scripts = Gui.GetScriptManager();
			if(Scripts)
			{
				Scripts->UpdateRfgPointers();
			}

#if !PublicMode
			std::cout << "PlayerPtr: " << std::hex << std::uppercase << PlayerPtr << "\n";
			std::cout << "PlayerPtr->Position.x: " << std::hex << std::uppercase << &PlayerPtr->Position.x << "\n";
			std::cout << "PlayerPtr->FrametimeMultiplier: " << std::hex << std::uppercase << &PlayerPtr->FrametimeMultiplier << "\n";
#endif
		}
	});
	if (GlobalPlayerPtr != PlayerPtr)
	{
		GlobalPlayerPtr = PlayerPtr;
		//Overlay.PlayerPtr = PlayerPtr;
		Gui.SetPlayerPtr(PlayerPtr);
		ScriptManager* Scripts = Gui.GetScriptManager();
		if (Scripts)
		{
			Scripts->UpdateRfgPointers();
		}

#if !PublicMode
		std::cout << "PlayerPtr: " << std::hex << std::uppercase << PlayerPtr << "\n";
		std::cout << "PlayerPtr->Position.x: " << std::hex << std::uppercase << &PlayerPtr->Position.x << "\n";
		std::cout << "PlayerPtr->FrametimeMultiplier: " << std::hex << std::uppercase << &PlayerPtr->FrametimeMultiplier << "\n";
#endif
	}
	if (!Gui.TweaksMenu || !Gui.FreeCamSettings || !Gui.FreeCamSettings->Camera)
	{
		return PlayerDoFrame(PlayerPtr);
	}
	//NewPlayerObject = *PlayerPtr;

	if (InfiniteJetpack)
	{
		PlayerPtr->JetpackFuelPercent = 1.0f;
	}
	if (Gui.TweaksMenu->Invulnerable || (Gui.FreeCamSettings->Camera->IsFreeCameraActive() && Gui.FreeCamSettings->PlayerFollowCam))
	{
		PlayerPtr->Flags.invulnerable = true;
		//PlayerPtr->Flags.super_jump = true;
		//PlayerPtr->Flags.use_bigsteps = true;
		//PlayerPtr->PFlags.UnlimitedAmmo = true;
		//PlayerPtr->MaxHitPoints = 2147483647;
		PlayerPtr->HitPoints = 2147483647.0f;
		//PlayerPtr->InitialMaxHitPoints = 2147483647;
	}
	if(Gui.FreeCamSettings->Camera->IsFreeCameraActive())
	{
		PlayerPtr->Flags.ai_ignore = true;
	}
	if (Gui.TweaksMenu->NeedCustomJumpHeightSet)
	{
		PlayerPtr->CodeDrivenJumpHeight = Gui.TweaksMenu->CustomJumpHeight;
	}
	if (Gui.TweaksMenu->NeedCustomMoveSpeedSet)
	{
		PlayerPtr->MoveSpeed = Gui.TweaksMenu->CustomPlayerMoveSpeed;
	}
	if (Gui.TweaksMenu->NeedCustomMaxMoveSpeedSet)
	{
		PlayerPtr->MaxSpeed = Gui.TweaksMenu->CustomPlayerMaxSpeed;
	}
	if (Gui.TweaksMenu->LockAlertLevel)
	{
		gsm_set_alert_level(Gui.TweaksMenu->CustomAlertLevel);
	}
	/*if (Gui.TweaksMenu->TempUseCustoms)
	{
		PlayerPtr->PFlags.UnlimitedAmmo = Gui.TweaksMenu->CustomUnlimitedAmmo;
		PlayerPtr->RenderAlpha = Gui.TweaksMenu->CustomRenderAlpha;
		PlayerPtr->StealthPercent = Gui.TweaksMenu->CustomStealthPercent;
	}*/

	if (Gui.FreeCamSettings->Camera->IsFreeCameraActive() && Gui.FreeCamSettings->PlayerFollowCam)
	{
		CameraWrapper* Cam = Gui.FreeCamSettings->Camera;
		vector CameraPos(*Cam->RealX, *Cam->RealY + 1.5f, *Cam->RealZ);
		HumanTeleportUnsafe(PlayerPtr, CameraPos, PlayerPtr->Orientation);
	}
	if (!Gui.FreeCamSettings->Camera->IsFreeCameraActive() && Gui.FreeCamSettings->Camera->NeedPostDeactivationCleanup)
	{
		if (Gui.FreeCamSettings->ReturnPlayerToOriginalPosition)
		{
			HumanTeleportUnsafe(PlayerPtr, Gui.FreeCamSettings->Camera->OriginalCameraPosition, PlayerPtr->Orientation);
		}
		Gui.FreeCamSettings->Camera->NeedPostDeactivationCleanup = false;
	}

	return PlayerDoFrame(PlayerPtr);
}

void __cdecl ExplosionCreateHook(explosion_info * ExplosionInfo, void * Source, void * Owner, vector * Position, matrix * Orientation, vector * Direction, void * WeaponInfo, bool FromServer)
{
	std::call_once(HookExplosionCreateInitialCall, [&]()
	{
#if !PublicMode
		Logger::ConsoleLog("First time in ExplosionCreate() hook.\n", LogInfo, false, true);
#endif
	});

	NewExplosionInfo = *ExplosionInfo;
	if (MinimumExplosionRadius < 0.000000f)
	{
		MinimumExplosionRadius = 0.000000f;
	}

	if (UseGlobalExplosionStrengthMultiplier)
	{
		/*std::cout << "Address of ExplosionInfo: " << ExplosionInfo << ", Hex: " << std::hex << std::uppercase << ExplosionInfo << "\n";
		Logger::Log(std::string("ExplosionInfo->m_name: " + std::string(NewExplosionInfo.m_name)), LogInfo);
		Logger::Log(std::string("ExplosionInfo->m_unique_id: " + std::to_string(NewExplosionInfo.m_unique_id)), LogInfo);
		Logger::Log(std::string("Before, Explosion radius: " + std::to_string(NewExplosionInfo.m_radius)), LogInfo);
		Logger::Log(std::string("Increasing explosion values by a factor of " + std::to_string(GlobalExplosionStrengthMultiplier)), LogInfo);*/

		NewExplosionInfo.m_radius *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_impulse_magnitude *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_knockdown_radius *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_secondary_radius *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_structural_damage = (int)(GlobalExplosionStrengthMultiplier * (float)(NewExplosionInfo.m_structural_damage)); //Did this instead of *= to avoid a compiler error. Probably unecessary.

		//Logger::Log(std::string("After, Explosion radius: " + std::to_string(NewExplosionInfo.m_radius)), LogInfo);
		//std::cout << "\n";

		*ExplosionInfo = NewExplosionInfo;
	}
	//std::cout << "\n";

	if (UseExplosionRadiusLimits)
	{
		EnforceFloatRange(NewExplosionInfo.m_radius, MinimumExplosionRadius, MaximumExplosionRadius);
		EnforceFloatRange(NewExplosionInfo.m_knockdown_radius, MinimumExplosionRadius, MaximumExplosionRadius);
		EnforceFloatRange(NewExplosionInfo.m_secondary_radius, MinimumExplosionRadius, MaximumExplosionRadius);
	}

	return ExplosionCreate(&NewExplosionInfo, Source, Owner, Position, Orientation, Direction, WeaponInfo, FromServer);
}

void __fastcall ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData)
{
	std::call_once(HookObjectUpdatePosAndOrientInitialCall, [&]()
	{
#if !PublicMode
		Logger::ConsoleLog("First time in ObjectUpdatePosAndOrient() hook.\n", LogInfo, false, true);
#endif
	});
	//Logger::ConsoleLog("1\n", LogInfo, false, true);
	/*if (Overlay.NeedPlayerPosSet)
	{
		if (GlobalPlayerPtrInitialized)
		{
			if (GlobalPlayerPtr == (DWORD*)ObjectPtr)
			{
				//Logger::ConsoleLog("Manually setting Player.Object.Position in ObjectUpdatePosAndOrient() hook.\n", LogWarning, false, true);
				NewObjectPosition = *UpdatedPosition;
				
				NewObjectPosition.x = Overlay.PlayerPositionTargetArray[0];
				NewObjectPosition.y = Overlay.PlayerPositionTargetArray[1];
				NewObjectPosition.z = Overlay.PlayerPositionTargetArray[2];
				
				//UpdatedPosition->x = Overlay.PlayerPositionTargetArray[0];
				//UpdatedPosition->y = Overlay.PlayerPositionTargetArray[1];
				//UpdatedPosition->z = Overlay.PlayerPositionTargetArray[2];

				//Logger::ConsoleLog("Done manually setting Player.Object.Position in ObjectUpdatePosAndOrient() hook.\n", LogInfo, false, true);
				Overlay.NeedPlayerPosSet = false;
				return ObjectUpdatePosAndOrient(ObjectPtr, edx, &NewObjectPosition, UpdatedOrientation, SetHavokData);
				//Logger::ConsoleLog("You shouldn't see this. In ObjectUpdatePosAndOrient() hook\n", LogInfo, false, true);
			}
		}
	}*/
	//Logger::ConsoleLog("2\n", LogInfo, false, true);
	if (GlobalPlayerPtrInitialized)
	{
		if (GlobalPlayerPtr == ObjectPtr)
		{
			///std::cout << "PlayerSetHavokData: " << SetHavokData << "\n";
		}
	}
	///SetHavokData = true;
	//Logger::ConsoleLog("3\n", LogInfo, false, true);
	return ObjectUpdatePosAndOrient(ObjectPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
}

/*Note: Attempts to manually set the player pos here failed. Required it to be 
repeatedly set else you'd return to where the game last had you. 
Might've been fighting with havok.*/
//void __fastcall HumanUpdatePosAndOrientHook(Human* HumanPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData)
//{
//	std::call_once(HookHumanUpdatePosAndOrientInitialCall, [&]()
//	{
//#if !PublicMode
//		Logger::ConsoleLog("First time in HumanUpdatePosAndOrient() hook.\n", LogInfo, false, true);
//#endif
//	});
//	/*if (Gui.MainWindow.NeedPlayerPosSet)
//	{
//		if (GlobalPlayerPtrInitialized)
//		{
//			if (GlobalPlayerPtr == (DWORD*)HumanPtr)
//			{
//				//std::cout << "Player HumanPtr found!" << "\n";
//				//std::cout << "Proof, HumanPtr->Position.y: " << HumanPtr->Position.y << "\n";
//				Logger::Log("Manually setting Player.Object.Position in HumanUpdatePosAndOrient() hook.\n", LogWarning);
//				NewObjectPosition = *UpdatedPosition;
//
//				NewObjectPosition.x = Gui.MainWindow.PlayerPositionTargetArray[0];
//				NewObjectPosition.y = Gui.MainWindow.PlayerPositionTargetArray[1];
//				NewObjectPosition.z = Gui.MainWindow.PlayerPositionTargetArray[2];
//
//				Gui.MainWindow.NeedPlayerPosSet = false;
//
//				return HumanUpdatePosAndOrient(HumanPtr, edx, &NewObjectPosition, UpdatedOrientation, SetHavokData);
//			}
//		}
//	}
//	if (Gui.MainWindow.NeedPlayerVelocitySet)
//	{
//		if (GlobalPlayerPtrInitialized)
//		{
//			if (GlobalPlayerPtr == (DWORD*)HumanPtr)
//			{
//					HumanPtr->Velocity.x = Gui.MainWindow.PlayerVelocityTargetArray[0];
//					HumanPtr->Velocity.y = Gui.MainWindow.PlayerVelocityTargetArray[1];
//					HumanPtr->Velocity.z = Gui.MainWindow.PlayerVelocityTargetArray[2];
//			}
//		}
//	}*/
//
//	//HumanPtr->Flags.start_jump = 2147483647;
//	//HumanPtr->Flags.super_jump = 2147483647;
//
//	//std::cout << "HumanPtr->Flags.start_jump: " << HumanPtr->Flags.start_jump << "\n";
//	//std::cout << "HumanPtr->Flags.super_jump: " << HumanPtr->Flags.super_jump << "\n";
//
//	return HumanUpdatePosAndOrient(HumanPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
//}

/*Disabled atm since I experience a crash with it, and it's not needed for the moment.*/
void __cdecl CameraViewDataSetViewHook(CameraViewData* ViewData, CameraViewTableEntry* ViewTableEntry, bool SkipTransition)
{
	/*if (FirstPersonModeActive)
	{
		NewCameraViewData = *CameraViewData;
		NewCameraViewTableEntry = *CameraViewTableEntry;
		NewSkipTransition = SkipTransition;

		NewCameraViewTableEntry.camera_distance = 0.0f;

		return CameraViewDataSetView(&NewCameraViewData, &NewCameraViewTableEntry, NewSkipTransition);
	}

	CameraViewData->m_camera_distance = 18.0f;
	CameraViewData->m_dof_enable = true;
	CameraViewData->m_focal_distance = 0.25f;
	CameraViewData->m_target_camera_distance = 18.0f;*/

	return CameraViewDataSetView(ViewData, ViewTableEntry, SkipTransition);
}

//*** Currently causes crashes. Fix before using. ***//
void __fastcall CharacterControllerSetPosHook(CharacterController* CharController, vector* Position) 
{
	//Set CharControllerGlobal

	/*if (Overlay.NeedPlayerPosSet)
	{
		if (GlobalPlayerPtrInitialized)
		{
			Player* TempPlayerPtr = (Player*)GlobalPlayerPtr;

			TempPlayerPtr->Position.x = Overlay.PlayerPositionTargetArray[0];
			TempPlayerPtr->Position.y = Overlay.PlayerPositionTargetArray[1];
			TempPlayerPtr->Position.z = Overlay.PlayerPositionTargetArray[2];
			Overlay.NeedPlayerPosSet = false;
		}
	}*/

	//std::cout << "CharacterController Address: " << std::hex << std::uppercase << CharController << "\n";

	return CharacterControllerSetPos(CharController, Position);
}

/*Start of MP Detection Hooks*/
bool __fastcall IsValidGameLinkLobbyKaikoHook(void* This)
{
	MultiplayerHookTriggered = true;
	return IsValidGameLinkLobbyKaiko(This);
}

void __cdecl GameMusicMultiplayerStartHook()
{
	MultiplayerHookTriggered = true;
	return GameMusicMultiplayerStart();
}

void __cdecl InitMultiplayerDataItemRespawnHook(void* Item)
{
	MultiplayerHookTriggered = true;
	return InitMultiplayerDataItemRespawn(Item);
}

void __cdecl HudUiMultiplayerProcessHook(float DeltaTime)
{
	MultiplayerHookTriggered = true;
	return HudUiMultiplayerProcess(DeltaTime);
}

void __cdecl HudUiMultiplayerEnterHook()
{
	MultiplayerHookTriggered = true;
	return HudUiMultiplayerEnter();
}
/*End of MP Detection Hooks*/

void __fastcall rl_draw_tristrip_2d_begin_hook(void* This, void* edx, rl_primitive_state* PrimitiveState)
{
	std::call_once(HookRlDrawTristip2dInitialCall, [&]()
	{
		GlobalRlDrawPtr = This;
		/*std::cout << "First time in rl_draw::tristrip_2d_begin() hook..." << "\n";
		std::cout << "Alpha mode: " << PrimitiveState->d.v.m_alpha_mode << "\n";
		std::cout << "Clamp mode: " << PrimitiveState->d.v.m_clamp_mode << "\n";
		std::cout << "Color write mode: " << PrimitiveState->d.v.m_color_write_mode << "\n";
		std::cout << "Const alpha: " << PrimitiveState->d.v.m_const_alpha << "\n";
		std::cout << "Cull mode: " << PrimitiveState->d.v.m_cull_mode << "\n";
		std::cout << "MSAA: " << PrimitiveState->d.v.m_msaa << "\n";
		std::cout << "Scissor: " << PrimitiveState->d.v.m_scissor << "\n";
		std::cout << "Stencil mode: " << PrimitiveState->d.v.m_stencil_mode << "\n";
		std::cout << "Valid: " << PrimitiveState->d.v.m_valid << "\n";
		std::cout << "Z-Bias mode: " << PrimitiveState->d.v.m_zbias_mode << "\n";
		std::cout << "Z-Buffer mode: " << PrimitiveState->d.v.m_zbuf_mode << "\n";*/
	});

	return rl_draw_tristrip_2d_begin(This, edx, PrimitiveState);
}

void __fastcall world_do_frame_hook(World* This, void* edx, bool HardLoad) //.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame>
{
	std::call_once(HookWorldDoFrameInitialCall, [&]()
	{
		GlobalRfgWorldPtr = This;
		Logger::Log("RFG::World hooked!", LogInfo);
		
		GlobalTODLightPtr = game_render_get_TOD_light();
		ScriptManager* Scripts = Gui.GetScriptManager();
		if (Scripts)
		{
			Scripts->UpdateRfgPointers();
		}
	});
	if (GlobalRfgWorldPtr != This)
	{
		Logger::Log("GlobalRfgWorldPtr changed!", LogWarning);
		GlobalRfgWorldPtr = This;
		ScriptManager* Scripts = Gui.GetScriptManager();
		if (Scripts)
		{
			Scripts->UpdateRfgPointers();
		}
	}
	if (!GlobalTODLightPtr)
	{
		GlobalTODLightPtr = game_render_get_TOD_light();
	}
	if (!Gui.TweaksMenu)
	{
		return world_do_frame(This, edx, HardLoad);
	}

	if (Gui.TweaksMenu->UseCustomLevelAmbientLight)
	{
		GlobalRfgWorldPtr->level_ambient.x = Gui.TweaksMenu->CustomLevelAmbientLight.x;
		GlobalRfgWorldPtr->level_ambient.y = Gui.TweaksMenu->CustomLevelAmbientLight.y;
		GlobalRfgWorldPtr->level_ambient.z = Gui.TweaksMenu->CustomLevelAmbientLight.z;
	}
	if (Gui.TweaksMenu->UseCustomLevelBackgroundAmbientLight)
	{
		GlobalRfgWorldPtr->level_back_ambient.x = Gui.TweaksMenu->CustomLevelBackgroundAmbientLight.x;
		GlobalRfgWorldPtr->level_back_ambient.y = Gui.TweaksMenu->CustomLevelBackgroundAmbientLight.y;
		GlobalRfgWorldPtr->level_back_ambient.z = Gui.TweaksMenu->CustomLevelBackgroundAmbientLight.z;
	}
	if (Gui.TweaksMenu->UseCustomTimeOfDayLight)
	{
		GlobalTODLightPtr->m_color.red = Gui.TweaksMenu->CustomTimeOfDayLightColor.red;
		GlobalTODLightPtr->m_color.green = Gui.TweaksMenu->CustomTimeOfDayLightColor.green;
		GlobalTODLightPtr->m_color.blue = Gui.TweaksMenu->CustomTimeOfDayLightColor.blue;
		GlobalTODLightPtr->m_color.alpha = Gui.TweaksMenu->CustomTimeOfDayLightColor.alpha;
	}																   

	return world_do_frame(This, edx, HardLoad);
}

void __fastcall rl_camera_render_begin_hook(rl_camera* This, void* edx, rl_renderer* Renderer) //.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>
{
	std::call_once(HookRlCameraRenderBegin, [&]()
	{
		GlobalRlCameraPtr = This;
		GlobalRlRendererPtr = Renderer;
	
		if (Renderer)
		{
			GlobalRlRenderLibPtr = Renderer->m_pRenderLib;
			GlobalRlStateManagerPtr = Renderer->m_state_p;
		}

		GlobalMainScenePtr = game_render_get_main_scene();
		if (GlobalMainScenePtr)
		{
			GlobalMainSceneRendererPtr = GlobalMainScenePtr->m_scene_renderer_p;
			if (!GlobalMainSceneRendererPtr)
			{
				GlobalMainSceneRendererPtr = GlobalMainScenePtr->m_default_scene_renderer_p;
			}
			GlobalMainSceneCameraPtr = GlobalMainSceneRendererPtr->m_part2_params.p_camera;

			std::cout << "Shadow map width: " << GlobalMainSceneRendererPtr->m_shadow_map_width << "\n";
			std::cout << "Shadow map height: " << GlobalMainSceneRendererPtr->m_shadow_map_height << "\n";
		}
	});
	if (This != GlobalRlCameraPtr)
	{
		//Logger::Log("GlobalRlCameraPtr address changed!", LogWarning);
		GlobalRlCameraPtr = This;
	}

	return rl_camera_render_begin(This, edx, Renderer);
}

void __fastcall hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime) //0x9E1A70
{
	std::call_once(HookhkpWorld_stepDeltaTime, [&]()
	{
		GlobalhkpWorldPtr = This;
		ScriptManager* Scripts = Gui.GetScriptManager();
		if (Scripts)
		{
			Scripts->UpdateRfgPointers();
		}
		if (Gui.PhysicsSettings)
		{
			Gui.PhysicsSettings->CurrentGravity = hkpWorldGetGravity(GlobalhkpWorldPtr, NULL);

			Gui.PhysicsSettings->CustomGravityVector.m_quad.m128_f32[0] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[0];
			Gui.PhysicsSettings->CustomGravityVector.m_quad.m128_f32[1] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[1];
			Gui.PhysicsSettings->CustomGravityVector.m_quad.m128_f32[2] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[2];
			Gui.PhysicsSettings->CustomGravityVector.m_quad.m128_f32[3] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[3];
				
			Gui.PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[0] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[0];
			Gui.PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[1] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[1];
			Gui.PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[2] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[2];
			Gui.PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[3] = Gui.PhysicsSettings->CurrentGravity->m_quad.m128_f32[3];
		}
	});
	if (This != GlobalhkpWorldPtr)
	{
		Logger::Log("GlobalhkpWorldPtr address changed!", LogWarning);
		GlobalhkpWorldPtr = This;
		ScriptManager* Scripts = Gui.GetScriptManager();
		if (Scripts)
		{
			Scripts->UpdateRfgPointers();
		}
	}

	if (Gui.TweaksMenu)
	{
		if (Gui.PhysicsSettings->UseCustomPhysicsTimestepMultiplier)
		{
			PhysicsDeltaTime *= Gui.PhysicsSettings->CustomPhysicsTimeStepMultiplier;
		}
	}

	return hkpWorld_stepDeltaTime(This, edx, PhysicsDeltaTime);
}

void __fastcall ApplicationUpdateTimeHook(void* This, void* edx, float TimeStep)
{
	std::call_once(HookApplicationUpdateTime, [&]()
	{
		//GlobalApplicationPtr = This;
	});

	/*if (Gui.TweaksMenu)
	{
		if (Gui.TweaksMenu->UseCustomPhysicsTimestepMultiplier)
		{
			TimeStep *= Gui.TweaksMenu->CustomPhysicsTimeStepMultiplier;
		}
	}*/

	return ApplicationUpdateTime(This, edx, TimeStep);
}
//.text:0117A880 rfg.exe:$5A880 #59C80 <keen::rfg::Application::updateTime> //void __thiscall fav::keen::rfg::Application::updateTime(keen::rfg::Application *this, float timeStep)
//typedef void(__fastcall* F_ApplicationUpdateTime)(void* This, void* edx, float TimeStep); //2nd arg is edx, needed for __thiscall functions.
//extern F_ApplicationUpdateTime ApplicationUpdateTime;