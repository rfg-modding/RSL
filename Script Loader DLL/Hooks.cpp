#include "Hooks.h"
#include "ProgramManager.h"

D3D11Present D3D11PresentObject;

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

bool UpdateD3D11Pointers = true;

std::once_flag HookWorldDoFrameInitialCall;

std::once_flag HookRlCameraRenderBegin;
std::once_flag HookhkpWorld_stepDeltaTime;
std::once_flag HookApplicationUpdateTime;
std::once_flag HookLuaDoBuffer;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ProcessInput(hWnd, msg, wParam, lParam);
	if (Globals::OverlayActive || Globals::Gui->IsLuaConsoleActive())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		if (msg == WM_SIZE)
		{
			Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
			ImGui_ImplDX11_InvalidateDeviceObjects();
			UpdateD3D11Pointers = true;
			Globals::D3D11Context->OMSetRenderTargets(0, 0, 0);
			Globals::MainRenderTargetView->Release();
			return CallWindowProc(Globals::OriginalWndProc, Globals::hwnd, msg, wParam, lParam);
		}
		return true;
	}

	switch (msg)
	{
		case WM_SIZE:
			Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
			ImGui_ImplDX11_InvalidateDeviceObjects();
			UpdateD3D11Pointers = true;
			Globals::D3D11Context->OMSetRenderTargets(0, 0, 0);
			Globals::MainRenderTargetView->Release();
			break;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return CallWindowProc(Globals::OriginalWndProc, Globals::hwnd, msg, wParam, lParam);
	//return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool MiddleMouseDown = false;
	if(!Globals::Gui->Ready())
	{
		return 0;
	}
	switch(msg)
	{
	case WM_KEYDOWN:
		if(Globals::Camera->IsFreeCameraActive())
		{
			switch(wParam)
			{
			case 0x51: //q
				Globals::Camera->MaxSpeed -= 0.02f;
				break;
			case 0x45: //e
				Globals::Camera->MaxSpeed += 0.02f;
				break;
			case 0x5A: //z
				Globals::Camera->MoveFreeCamera(DOWN);
				break;
			case 0x58: //x
				Globals::Camera->MoveFreeCamera(UP);	
				break;
			case VK_UP: //Up arrow key
				Globals::Camera->MoveFreeCamera(FORWARD);
				break;
			case VK_DOWN: //Down arrow key
				Globals::Camera->MoveFreeCamera(BACKWARD);
				break;
			case VK_RIGHT: //Right arrow key
				Globals::Camera->MoveFreeCamera(RIGHT);
				break;
			case VK_LEFT: //Left arrow key
				Globals::Camera->MoveFreeCamera(LEFT);
				break;
			default:
				break;
			}
		}
		switch(wParam)
		{
		case VK_F1:
			Globals::OverlayActive = !Globals::OverlayActive;
			///Logger::Log(std::string("Overlay active value: " + std::to_string(OverlayActive)), LogInfo);
			if (Globals::OverlayActive)
			{
				if (!Globals::Gui->IsLuaConsoleActive())
				{
					SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
					SnippetManager::BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
				}
			}
			else
			{
				Globals::Gui->DeactivateLuaConsole();
				SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
				SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
			}
			//Sleep(150);
			break;
		case VK_F2:
			Globals::Gui->ShowAppScriptEditor = !Globals::Gui->ShowAppScriptEditor;
			break;
		case VK_NUMPAD1:
			ToggleHud();
			break;
		case VK_NUMPAD2:
			ToggleFog();
			break;
		case VK_NUMPAD3:
			Globals::Camera->ToggleFreeCamera();
			break;
		case VK_OEM_3: //Tilde
			Globals::Gui->ToggleLuaConsole();
			if (Globals::Gui->IsLuaConsoleActive())
			{
				Globals::Gui->Console->InputBuffer.clear();
				Globals::Gui->Console->ReclaimFocus = true; //Tell console to set focus to it's text input.
				if (!Globals::OverlayActive)
				{
					SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
					SnippetManager::BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
				}
			}
			else
			{
				Globals::Gui->Console->InputBuffer.clear();
				if (!Globals::OverlayActive)
				{
					SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
					SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
				}
			}
			break;
		case VK_F3:
			Globals::Program->ExitKeysPressCount++;
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

	if (MiddleMouseDown && Globals::Gui->TweaksMenu->MiddleMouseBoomActive)
	{
		ExplosionTimerEnd = std::chrono::steady_clock::now();
		//std::cout << "Time since last explosion spawn: " << std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() << "\n";
		if (std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() > 1000 / Globals::Gui->TweaksMenu->MiddleMouseExplosionsPerSecond)
		{
			ExplosionCreate(&Globals::Gui->TweaksMenu->CustomExplosionInfo, Globals::PlayerPtr, Globals::PlayerPtr,
				&Globals::PlayerPtr->aim_pos, &Globals::PlayerPtr->mp_camera_orient, &Globals::PlayerPtr->aim_pos, nullptr, false);
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

	if (Globals::Gui->ShowAppScriptEditor)
	{
		try
		{
			if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x53)) //Ctrl + S
			{
				Globals::Gui->ScriptEditor->SaveScript();
			}
		}
		catch (const std::exception& Ex)
		{
			Logger::Log(std::string("Exception when using Ctrl+S save script shortcut. Message: " + std::string(Ex.what())), LogFatalError);
		}
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x53)) //Ctrl + Shift + S
		{
			Globals::Gui->ScriptEditor->ShowSaveAsScriptPopup = true;
		}
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x4F)) //Ctrl + O
		{
			Globals::Gui->ScriptEditor->ShowOpenScriptPopup = true;
		}
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x4E)) //Ctrl + N
		{
			Globals::Gui->ScriptEditor->ShowNewScriptPopup = true;
		}
		try
		{
			if (GetAsyncKeyState(VK_F5))
			{
				if(Globals::Gui->HasValidScriptManager())
				{
					std::string ScriptString = Globals::Gui->ScriptEditor->GetCurrentScriptString();
					Globals::Gui->GetScriptManager()->RunStringAsScript(ScriptString, "script editor run");
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
		//Logger::ConsoleLog("First time in D3D11Present() hook.", LogInfo, false, true, true);
#endif
		ExplosionTimerBegin = std::chrono::steady_clock::now();
		HRESULT Result = D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(pSwapChain, &Globals::D3D11Device, &Globals::D3D11Context);
		if (Result != S_OK)
		{
			Logger::Log(std::string("D3D11DeviceContextFromSwapchain() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}
		Globals::D3D11SwapchainPtr = pSwapChain;
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
		Result = Globals::D3D11Device->CreateRenderTargetView(BackBuffer, &desc, &Globals::MainRenderTargetView);
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
		Globals::io = ImGui::GetIO();
		Globals::io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();

		ImGui_ImplDX11_Init(Globals::D3D11Device, Globals::D3D11Context);
		Globals::hwnd = Globals::find_main_window(Globals::GetProcessID("rfg.exe"));
		bool RectResult = GetWindowRect(Globals::hwnd, &Globals::WindowRect);
		if (!RectResult)
		{
			std::cout << "GetWindowRect Failed! Result: " << GetLastError() << "\n";
			//Sleep(10000);
		}
		else
		{
			//Logger::Log("GetWindowRect() Succeeded", LogWarning);
		}
		ImGui_ImplWin32_Init(Globals::hwnd);

		ImGuiIO& io = ImGui::GetIO();
		float GlobalFontSize = 17.0f;
		std::string DefaultFontPath = std::string(Globals::GetEXEPath(false) + "RFGR Script Loader/Fonts/Roboto-Regular.ttf");
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
		std::string FontAwesomeSolidPath(Globals::GetEXEPath(false) + "RFGR Script Loader/Fonts/fa-solid-900.ttf");
		Logger::Log(FontAwesomeSolidPath, LogWarning);
		Globals::FontNormal = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalFontSize, &IconsConfig, IconsRanges);
		//Logger::Log("Done merging FontAwesome...", LogWarning);
		
		float GlobalBigFontSize = 24.0f;
		if (DefaultFontLoaded)
		{
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalBigFontSize);
		}
		Globals::FontBig = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalBigFontSize, &IconsConfig, IconsRanges);

		/*Start of FontLarge loading*/
		float GlobalLargeFontSize = 35.0f;
		if (DefaultFontLoaded)
		{
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalLargeFontSize);
		}
		Globals::FontLarge = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalLargeFontSize, &IconsConfig, IconsRanges);
		/*End of FontLarge loading*/

		/*Start of FontHuge loading*/
		float GlobalHugeFontSize = 70.0f;
		if (DefaultFontLoaded)
		{
			io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalHugeFontSize);
		}
		Globals::FontHuge = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalHugeFontSize, &IconsConfig, IconsRanges);
		/*End of FontHuge loading*/

		Globals::ImGuiInitialized = true;
		UpdateD3D11Pointers = false;

		//static RenderInterfaceD3D11 RenderInterface(D3D11Device, D3D11Context);
		//dd::initialize(&RenderInterface);

		Logger::Log("ImGui Initialized.", LogInfo);
		return S_OK;
	});

	if (UpdateD3D11Pointers)
	{
		Logger::Log("UpdateD3D11Pointers = true. Reforming MainRenderTargetView and ImGui DX11 Devices.", LogWarning);

		HRESULT Result = D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(pSwapChain, &Globals::D3D11Device, &Globals::D3D11Context);
		if (Result != S_OK)
		{
			Logger::Log(std::string("D3D11DeviceContextFromSwapchain() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}
		Globals::D3D11SwapchainPtr = pSwapChain;
		//
		ID3D11Texture2D* BackBuffer;
		Result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
		if (Result != S_OK)
		{
			Logger::Log(std::string("GetBuffer() failed, return value: " + std::to_string(Result)), LogFatalError);
			return E_FAIL;
		}

		Result = Globals::D3D11Device->CreateRenderTargetView(BackBuffer, nullptr, &Globals::MainRenderTargetView);
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
	if (!Globals::ImGuiInitialized)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}
	/*if (!OverlayActive)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}*/

	if (!Globals::ScriptLoaderCloseRequested)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
#if !PublicMode
		//if (OverlayActive)
		//{
		//	if (show_demo_window)
		//	{
		//		ImGui::ShowDemoWindow(&show_demo_window);
		//	}
		//}
#endif
		Globals::Gui->Draw();
		Globals::D3D11Context->OMSetRenderTargets(1, &Globals::MainRenderTargetView, nullptr);
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
	Globals::PlayerPtr = PlayerPtr;
	//Overlay.PlayerPtr = PlayerPtr;
	Globals::Gui->SetPlayerPtr(PlayerPtr);
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
			Globals::PlayerPtr = PlayerPtr;
			GlobalPlayerPtrInitialized = true;
			Globals::PlayerRigidBody = HavokBodyGetPointer(PlayerPtr->HavokHandle);

			//Overlay.PlayerPtr = PlayerPtr;
			Globals::Gui->SetPlayerPtr(PlayerPtr);
			if(Globals::Scripts)
			{
				Globals::Scripts->UpdateRfgPointers();
			}

#if !PublicMode
			std::cout << "PlayerPtr: " << std::hex << std::uppercase << PlayerPtr << "\n";
			std::cout << "PlayerPtr->Position.x: " << std::hex << std::uppercase << &PlayerPtr->Position.x << "\n";
			std::cout << "PlayerPtr->FrametimeMultiplier: " << std::hex << std::uppercase << &PlayerPtr->FrametimeMultiplier << "\n";
#endif
		}
	});
	if (Globals::PlayerPtr != PlayerPtr)
	{
		Globals::PlayerPtr = PlayerPtr;
		Globals::PlayerRigidBody = HavokBodyGetPointer(PlayerPtr->HavokHandle);
		Globals::Gui->SetPlayerPtr(PlayerPtr);
		if (Globals::Scripts)
		{
			Globals::Scripts->UpdateRfgPointers();
		}

#if !PublicMode
		std::cout << "PlayerPtr: " << std::hex << std::uppercase << PlayerPtr << "\n";
		std::cout << "PlayerPtr->Position.x: " << std::hex << std::uppercase << &PlayerPtr->Position.x << "\n";
		std::cout << "PlayerPtr->FrametimeMultiplier: " << std::hex << std::uppercase << &PlayerPtr->FrametimeMultiplier << "\n";
#endif
	}
	if (!Globals::Gui->TweaksMenu || !Globals::Gui->FreeCamSettings || !Globals::Gui->FreeCamSettings->Camera)
	{
		return PlayerDoFrame(PlayerPtr);
	}
	//NewPlayerObject = *PlayerPtr;

	if (Globals::InfiniteJetpack)
	{
		PlayerPtr->JetpackFuelPercent = 1.0f;
	}
	if (Globals::Gui->TweaksMenu->Invulnerable || (Globals::Camera->IsFreeCameraActive() && Globals::Gui->FreeCamSettings->PlayerFollowCam))
	{
		PlayerPtr->Flags.invulnerable = true;
		//PlayerPtr->Flags.super_jump = true;
		//PlayerPtr->Flags.use_bigsteps = true;
		//PlayerPtr->PFlags.UnlimitedAmmo = true;
		//PlayerPtr->MaxHitPoints = 2147483647;
		PlayerPtr->HitPoints = 2147483647.0f;
		//PlayerPtr->InitialMaxHitPoints = 2147483647;
	}
	if(Globals::Camera->IsFreeCameraActive())
	{
		PlayerPtr->Flags.ai_ignore = true;
	}
	if (Globals::Gui->TweaksMenu->NeedCustomJumpHeightSet)
	{
		PlayerPtr->CodeDrivenJumpHeight = Globals::Gui->TweaksMenu->CustomJumpHeight;
	}
	if (Globals::Gui->TweaksMenu->NeedCustomMoveSpeedSet)
	{
		PlayerPtr->MoveSpeed = Globals::Gui->TweaksMenu->CustomPlayerMoveSpeed;
	}
	if (Globals::Gui->TweaksMenu->NeedCustomMaxMoveSpeedSet)
	{
		PlayerPtr->MaxSpeed = Globals::Gui->TweaksMenu->CustomPlayerMaxSpeed;
	}
	if (Globals::Gui->TweaksMenu->LockAlertLevel)
	{
		gsm_set_alert_level(Globals::Gui->TweaksMenu->CustomAlertLevel);
	}
	/*if (Gui.TweaksMenu->TempUseCustoms)
	{
		PlayerPtr->PFlags.UnlimitedAmmo = Gui.TweaksMenu->CustomUnlimitedAmmo;
		PlayerPtr->RenderAlpha = Gui.TweaksMenu->CustomRenderAlpha;
		PlayerPtr->StealthPercent = Gui.TweaksMenu->CustomStealthPercent;
	}*/

	if (Globals::Camera->IsFreeCameraActive() && Globals::Gui->FreeCamSettings->PlayerFollowCam)
	{
		Globals::Camera->UpdateFreeView();
		vector CameraPos(*Globals::Camera->RealX, *Globals::Camera->RealY + 1.5f, *Globals::Camera->RealZ);
		HumanTeleportUnsafe(PlayerPtr, CameraPos, PlayerPtr->Orientation);
	}
	if (!Globals::Camera->IsFreeCameraActive() && Globals::Camera->NeedPostDeactivationCleanup)
	{
		if (Globals::Gui->FreeCamSettings->ReturnPlayerToOriginalPosition)
		{
			HumanTeleportUnsafe(PlayerPtr, Globals::Camera->OriginalCameraPosition, PlayerPtr->Orientation);
		}
		Globals::Camera->NeedPostDeactivationCleanup = false;
	}

	if(Globals::Camera)
	{
		if(Globals::Camera->IsFirstPersonCameraActive())
		{
			Globals::PlayerPtr->Flags.ai_ignore = true;
			Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls = true;
		}
		if(Globals::Camera->IsFirstPersonCameraActive())
		{
			Globals::Camera->UpdateFirstPersonView();
		}
	}

	return PlayerDoFrame(PlayerPtr);
}

void __cdecl ExplosionCreateHook(explosion_info * ExplosionInfo, void * Source, void * Owner, vector * Position, matrix * Orientation, vector * Direction, void * WeaponInfo, bool FromServer)
{
	std::call_once(HookExplosionCreateInitialCall, [&]()
	{
#if !PublicMode
		//Logger::ConsoleLog("First time in ExplosionCreate() hook.\n", LogInfo, false, true);
#endif
	});

	NewExplosionInfo = *ExplosionInfo;
	if (Globals::MinimumExplosionRadius < 0.000000f)
	{
		Globals::MinimumExplosionRadius = 0.000000f;
	}

	if (Globals::UseGlobalExplosionStrengthMultiplier)
	{
		/*std::cout << "Address of ExplosionInfo: " << ExplosionInfo << ", Hex: " << std::hex << std::uppercase << ExplosionInfo << "\n";
		Logger::Log(std::string("ExplosionInfo->m_name: " + std::string(NewExplosionInfo.m_name)), LogInfo);
		Logger::Log(std::string("ExplosionInfo->m_unique_id: " + std::to_string(NewExplosionInfo.m_unique_id)), LogInfo);
		Logger::Log(std::string("Before, Explosion radius: " + std::to_string(NewExplosionInfo.m_radius)), LogInfo);
		Logger::Log(std::string("Increasing explosion values by a factor of " + std::to_string(GlobalExplosionStrengthMultiplier)), LogInfo);*/

		NewExplosionInfo.m_radius *= Globals::GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_impulse_magnitude *= Globals::GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_knockdown_radius *= Globals::GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_secondary_radius *= Globals::GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_structural_damage = (int)(Globals::GlobalExplosionStrengthMultiplier * (float)(NewExplosionInfo.m_structural_damage)); //Did this instead of *= to avoid a compiler error. Probably unecessary.

		//Logger::Log(std::string("After, Explosion radius: " + std::to_string(NewExplosionInfo.m_radius)), LogInfo);
		//std::cout << "\n";

		*ExplosionInfo = NewExplosionInfo;
	}

	if (Globals::UseExplosionRadiusLimits)
	{
		Globals::EnforceFloatRange(NewExplosionInfo.m_radius, Globals::MinimumExplosionRadius, Globals::MaximumExplosionRadius);
		Globals::EnforceFloatRange(NewExplosionInfo.m_knockdown_radius, Globals::MinimumExplosionRadius, Globals::MaximumExplosionRadius);
		Globals::EnforceFloatRange(NewExplosionInfo.m_secondary_radius, Globals::MinimumExplosionRadius, Globals::MaximumExplosionRadius);
	}

	return ExplosionCreate(&NewExplosionInfo, Source, Owner, Position, Orientation, Direction, WeaponInfo, FromServer);
}

void __fastcall ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData)
{
	std::call_once(HookObjectUpdatePosAndOrientInitialCall, [&]()
	{

	});

	return ObjectUpdatePosAndOrient(ObjectPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
}

/*Start of MP Detection Hooks*/
bool __fastcall IsValidGameLinkLobbyKaikoHook(void* This)
{
	Globals::MultiplayerHookTriggered = true;
	return IsValidGameLinkLobbyKaiko(This);
}

void __cdecl GameMusicMultiplayerStartHook()
{
	Globals::MultiplayerHookTriggered = true;
	return GameMusicMultiplayerStart();
}

void __cdecl InitMultiplayerDataItemRespawnHook(void* Item)
{
	Globals::MultiplayerHookTriggered = true;
	return InitMultiplayerDataItemRespawn(Item);
}

void __cdecl HudUiMultiplayerProcessHook(float DeltaTime)
{
	Globals::MultiplayerHookTriggered = true;
	return HudUiMultiplayerProcess(DeltaTime);
}

void __cdecl HudUiMultiplayerEnterHook()
{
	Globals::MultiplayerHookTriggered = true;
	return HudUiMultiplayerEnter();
}
/*End of MP Detection Hooks*/

void __fastcall world_do_frame_hook(World* This, void* edx, bool HardLoad) //.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame>
{
	std::call_once(HookWorldDoFrameInitialCall, [&]()
	{
		Globals::RfgWorldPtr = This;
		Logger::Log("RFG::World hooked!", LogInfo);
		
		Globals::TODLightPtr = game_render_get_TOD_light();
		if (Globals::Scripts)
		{
			Globals::Scripts->UpdateRfgPointers();
		}
	});
	if (Globals::RfgWorldPtr != This)
	{
		Logger::Log("GlobalRfgWorldPtr changed!", LogWarning);
		Globals::RfgWorldPtr = This;
		if (Globals::Scripts)
		{
			Globals::Scripts->UpdateRfgPointers();
		}
	}
	if (!Globals::TODLightPtr)
	{
		Globals::TODLightPtr = game_render_get_TOD_light();
	}
	if (!Globals::Gui->TweaksMenu)
	{
		return world_do_frame(This, edx, HardLoad);
	}

	if (Globals::Gui->TweaksMenu->UseCustomLevelAmbientLight)
	{
		Globals::RfgWorldPtr->level_ambient.x = Globals::Gui->TweaksMenu->CustomLevelAmbientLight.x;
		Globals::RfgWorldPtr->level_ambient.y = Globals::Gui->TweaksMenu->CustomLevelAmbientLight.y;
		Globals::RfgWorldPtr->level_ambient.z = Globals::Gui->TweaksMenu->CustomLevelAmbientLight.z;
	}
	if (Globals::Gui->TweaksMenu->UseCustomLevelBackgroundAmbientLight)
	{
		Globals::RfgWorldPtr->level_back_ambient.x = Globals::Gui->TweaksMenu->CustomLevelBackgroundAmbientLight.x;
		Globals::RfgWorldPtr->level_back_ambient.y = Globals::Gui->TweaksMenu->CustomLevelBackgroundAmbientLight.y;
		Globals::RfgWorldPtr->level_back_ambient.z = Globals::Gui->TweaksMenu->CustomLevelBackgroundAmbientLight.z;
	}
	if (Globals::Gui->TweaksMenu->UseCustomTimeOfDayLight)
	{
		Globals::TODLightPtr->m_color.red = Globals::Gui->TweaksMenu->CustomTimeOfDayLightColor.red;
		Globals::TODLightPtr->m_color.green = Globals::Gui->TweaksMenu->CustomTimeOfDayLightColor.green;
		Globals::TODLightPtr->m_color.blue = Globals::Gui->TweaksMenu->CustomTimeOfDayLightColor.blue;
		Globals::TODLightPtr->m_color.alpha = Globals::Gui->TweaksMenu->CustomTimeOfDayLightColor.alpha;
	}																   

	return world_do_frame(This, edx, HardLoad);
}

void __fastcall rl_camera_render_begin_hook(rl_camera* This, void* edx, rl_renderer* Renderer) //.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>
{
	std::call_once(HookRlCameraRenderBegin, [&]()
	{
		Globals::RlCameraPtr = This;
		Globals::RlRendererPtr = Renderer;
	
		if (Renderer)
		{
			Globals::RlRenderLibPtr = Renderer->m_pRenderLib;
			Globals::RlStateManagerPtr = Renderer->m_state_p;
		}

		Globals::MainScenePtr = game_render_get_main_scene();
		if (Globals::MainScenePtr)
		{
			Globals::MainSceneRendererPtr = Globals::MainScenePtr->m_scene_renderer_p;
			if (!Globals::MainSceneRendererPtr)
			{
				Globals::MainSceneRendererPtr = Globals::MainScenePtr->m_default_scene_renderer_p;
			}
			Globals::MainSceneCameraPtr = Globals::MainSceneRendererPtr->m_part2_params.p_camera;

			std::cout << "Shadow map width: " << Globals::MainSceneRendererPtr->m_shadow_map_width << "\n";
			std::cout << "Shadow map height: " << Globals::MainSceneRendererPtr->m_shadow_map_height << "\n";
		}
	});
	if (This != Globals::RlCameraPtr)
	{
		//Logger::Log("GlobalRlCameraPtr address changed!", LogWarning);
		Globals::RlCameraPtr = This;
	}

	return rl_camera_render_begin(This, edx, Renderer);
}

void __fastcall hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime) //0x9E1A70
{
	std::call_once(HookhkpWorld_stepDeltaTime, [&]()
	{
		Globals::hkpWorldPtr = This;
		if (Globals::Scripts)
		{
			Globals::Scripts->UpdateRfgPointers();
		}
		if (Globals::Gui->PhysicsSettings)
		{
			Globals::Gui->PhysicsSettings->CurrentGravity = hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);

			Globals::Gui->PhysicsSettings->CustomGravityVector.m_quad.m128_f32[0] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[0];
			Globals::Gui->PhysicsSettings->CustomGravityVector.m_quad.m128_f32[1] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[1];
			Globals::Gui->PhysicsSettings->CustomGravityVector.m_quad.m128_f32[2] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[2];
			Globals::Gui->PhysicsSettings->CustomGravityVector.m_quad.m128_f32[3] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[3];
				
			Globals::Gui->PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[0] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[0];
			Globals::Gui->PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[1] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[1];
			Globals::Gui->PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[2] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[2];
			Globals::Gui->PhysicsSettings->DefaultGravityVector.m_quad.m128_f32[3] = Globals::Gui->PhysicsSettings->CurrentGravity->m_quad.m128_f32[3];
		}
	});
	if (This != Globals::hkpWorldPtr)
	{
		Logger::Log("GlobalhkpWorldPtr address changed!", LogWarning);
		Globals::hkpWorldPtr = This;
		if (Globals::Scripts)
		{
			Globals::Scripts->UpdateRfgPointers();
		}
	}

	if (Globals::Gui->PhysicsSettings)
	{
		if (Globals::Gui->PhysicsSettings->UseCustomPhysicsTimestepMultiplier)
		{
			PhysicsDeltaTime *= Globals::Gui->PhysicsSettings->CustomPhysicsTimeStepMultiplier;
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

int __cdecl LuaDoBufferHook(lua_State *L, const char *buff, unsigned int size, const char *name)
{
	std::call_once(HookLuaDoBuffer, [&]()
	{
		Globals::RfgVintLuaState = L;
		//Logger::Log("LuaDoBuffer hooked!", LogWarning);
	});
	if(!L)
	{
		Logger::Log("RFG lua_state pointer null", LogWarning);
		return LuaDoBuffer(L, buff, size, name);
	}

	//Dump current script file
	std::string Buffer(buff);
	std::string Name(name);
	std::string RfgLuaPath = Globals::GetEXEPath(false);
	RfgLuaPath += "RFGR Script Loader/RFG_Lua/";
	fs::create_directory(RfgLuaPath);
	std::string DumpFilePath = RfgLuaPath + "Lua_Dumps/";
	fs::create_directory(DumpFilePath);
	DumpFilePath += Name;
	Logger::Log(std::string(std::string("Dumping ") + Name), LogInfo);
	//std::cout << "\nBuffer: " << Buffer << "\n";
	std::ofstream myfile;
	myfile.open(DumpFilePath, std::ios_base::trunc);
	myfile << Buffer;
	myfile.close();

	std::string OverrideFilePath = RfgLuaPath + "Overrides/" + Name;
	//Load override if it exists and pass it on to lua.
	if(fs::exists(OverrideFilePath))
	{
		std::ifstream OverrideStream(OverrideFilePath);
		std::string OverrideBuffer((std::istreambuf_iterator<char>(OverrideStream)), std::istreambuf_iterator<char>());
		Logger::Log(std::string(std::string("Overriding ") + Name), LogInfo);
		return LuaDoBuffer(L, OverrideBuffer.c_str(), OverrideBuffer.length(), name);
	}
	return LuaDoBuffer(L, buff, size, name);
}