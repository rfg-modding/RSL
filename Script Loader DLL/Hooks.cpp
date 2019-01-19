#include "Hooks.h"

D3D11Present D3D11PresentObject;

MainOverlay Overlay;

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

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (OverlayActive)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
		return true;
	}


	//LRESULT ImGuiWndProcResult = ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	//std::cout << "ImGuiWndProcResult: " << ImGuiWndProcResult << std::endl << std::endl;

	/*ConsoleLog("WndProc: Window resized", LOGWARNING, false, true, true);
	std::cout << "WndProc D3D11Device: " << std::hex << std::uppercase << D3D11Device << std::endl;
	std::cout << "WndProc D3D11Context: " << std::hex << std::uppercase << D3D11Context << std::endl;
	UpdateD3D11Pointers = true;
	if (D3D11SwapchainPtr != nullptr)
	{
		ConsoleLog("WndProc: D3D11SwapchainPtr is not a nullptr", LOGSUCCESS, false, true, true);
	}
	if (D3D11Device != nullptr)
	{
		ConsoleLog("WndProc: D3D11Device is not a nullptr", LOGSUCCESS, false, true, true);
	}
	if (D3D11Context != nullptr)
	{
		ConsoleLog("WndProc: D3D11Context is not a nullptr", LOGSUCCESS, false, true, true);
	}
	if (D3D11Device == nullptr && wParam != SIZE_MINIMIZED)//g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
	{
		ConsoleLog("Window resize test 1 passed, setting UpdateD3D11Pointers to true", LOGWARNING, false, true, true);
		//UpdateD3D11Pointers = true;
		//CleanupRenderTarget();
		//g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
		//CreateRenderTarget();
	}*/

	//ConsoleLog("You better see this #1", LOGSUCCESS, false, true, true);
	
	switch (msg)
	{
	case WM_SIZE:
		ConsoleLog("WM_SIZE Recieved in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LOGWARNING, false, true, true);
		ImGui_ImplDX11_InvalidateDeviceObjects();
		UpdateD3D11Pointers = true;
		D3D11Context->OMSetRenderTargets(0, 0, 0);
		MainRenderTargetView->Release();
		break;
	/*case WM_SIZE:
		/*if (D3D11SwapchainPtr)
		{
			DXGI_SWAP_CHAIN_DESC SwapchainDescription;
			D3D11SwapchainPtr->GetDesc(&SwapchainDescription);

			ImGui_ImplDX11_InvalidateDeviceObjects();

			D3D11Context->OMSetRenderTargets(0, 0, 0);
			MainRenderTargetView->Release();

			HRESULT Result = D3D11SwapchainPtr->ResizeBuffers(SwapchainDescription.BufferCount, 0, 0, SwapchainDescription.BufferDesc.Format, SwapchainDescription.Flags);
			//HRESULT Result = D3D11SwapchainPtr->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			if (Result != S_OK)
			{
				ConsoleLog(std::string("ResizeBuffers() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			}

			ID3D11Texture2D* BackBuffer;
			Result = D3D11SwapchainPtr->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
			if (Result != S_OK)
			{
				ConsoleLog(std::string("GetBuffer() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			}

			Result = D3D11Device->CreateRenderTargetView(BackBuffer, NULL, &MainRenderTargetView);
			if (Result != S_OK)
			{
				ConsoleLog(std::string("CreateRenderTargetView() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			}

			BackBuffer->Release();
			D3D11Context->OMSetRenderTargets(1, &MainRenderTargetView, NULL);

			// Set up the viewport.
			D3D11_VIEWPORT Viewport;
			Viewport.Width = LOWORD(lParam);
			Viewport.Height = HIWORD(lParam);
			Viewport.MinDepth = 0.0f;
			Viewport.MaxDepth = 1.0f;
			Viewport.TopLeftX = 0;
			Viewport.TopLeftY = 0;
			D3D11Context->RSSetViewports(1, &Viewport);

			ImGui_ImplDX11_CreateDeviceObjects();
		}*/
		//return true;*/
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

HRESULT D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(IDXGISwapChain * pSwapChain, ID3D11Device ** ppDevice, ID3D11DeviceContext ** ppContext)
{
	HRESULT Result = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if(Result != S_OK)
	{
		ConsoleLog(std::string("ID3D11SwapChain::GetDevice() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
		return E_FAIL;
	}
	(*ppDevice)->GetImmediateContext(ppContext);

	return Result;
}

HRESULT __stdcall D3D11PresentHook(IDXGISwapChain * pSwapChain, UINT SyncInterval, UINT Flags)
{
	std::call_once(HookD3D11PresentInitialCall, [&]()
	{
#if !PublicMode
		ConsoleLog("First time in D3D11Present() hook.", LOGSUCCESS, false, true, true);
#endif
		HRESULT Result;

		Result = D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(pSwapChain, &D3D11Device, &D3D11Context);
		if (Result != S_OK)
		{
			ConsoleLog(std::string("D3D11DeviceContextFromSwapchain() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			return E_FAIL;
		}
		D3D11SwapchainPtr = pSwapChain;
		//
		ID3D11Texture2D* BackBuffer;
		Result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
		if (Result != S_OK)
		{
			ConsoleLog(std::string("GetBuffer() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			return E_FAIL;
		}

		Result = D3D11Device->CreateRenderTargetView(BackBuffer, NULL, &MainRenderTargetView);
		if (Result != S_OK)
		{
			ConsoleLog(std::string("CreateRenderTargetView() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			return E_FAIL;
		}

		BackBuffer->Release();

		/*DXGI_SWAP_CHAIN_DESC SwapChainDescription;
		pSwapChain->GetDesc(&SwapChainDescription);
		ConsoleLog(std::string("Initial buffer count: " + std::to_string(SwapChainDescription.BufferCount)).c_str(), LOGWARNING, false, true, true);
		ConsoleLog(std::string("Initial flags: " + std::to_string(SwapChainDescription.Flags)).c_str(), LOGWARNING, false, true, true);
		ConsoleLog(std::string("Initial format: " + std::to_string(SwapChainDescription.BufferDesc.Format)).c_str(), LOGWARNING, false, true, true);*/
		
		ConsoleLog("Initializing ImGui.\n", LOGMESSAGE, false, true);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();

		ImGui_ImplDX11_Init(D3D11Device, D3D11Context);
		hwnd = find_main_window(GetProcessID("rfg.exe"));
		ImGui_ImplWin32_Init(hwnd);

		std::string DroidSansPath = std::string(GetEXEPath(false) + "RFGR Script Loader/Fonts/DroidSans.ttf");
		if (fs::exists(DroidSansPath))
		{
			ImGui::GetIO().Fonts->AddFontFromFileTTF(DroidSansPath.c_str(), 17.0f);
		}
		else
		{
			ConsoleLog("DroidSans.ttf not found. Using default font.", LOGERROR, false, true, true);
		}

		/*if (OverlayActive)
		{
			OriginalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
		}*/

		Overlay.Initialize();
		ImGuiInitialized = true;
		UpdateD3D11Pointers = false;
		ConsoleLog("ImGui Initialized.", LOGSUCCESS, false, true, true);
	});

	if (UpdateD3D11Pointers)
	{
		ConsoleLog("UpdateD3D11Pointers = true. Reforming MainRenderTargetView and ImGui DX11 Devices.", LOGWARNING, false, true, true);

		HRESULT Result;

		Result = D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(pSwapChain, &D3D11Device, &D3D11Context);
		if (Result != S_OK)
		{
			ConsoleLog(std::string("D3D11DeviceContextFromSwapchain() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			return E_FAIL;
		}
		D3D11SwapchainPtr = pSwapChain;
		//
		ID3D11Texture2D* BackBuffer;
		Result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
		if (Result != S_OK)
		{
			ConsoleLog(std::string("GetBuffer() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			return E_FAIL;
		}

		Result = D3D11Device->CreateRenderTargetView(BackBuffer, NULL, &MainRenderTargetView);
		if (Result != S_OK)
		{
			ConsoleLog(std::string("CreateRenderTargetView() failed, return value: " + std::to_string(Result)).c_str(), LOGFATALERROR, false, true, true);
			return E_FAIL;
		}

		BackBuffer->Release();

		//ImGui_ImplDX11_Init(D3D11Device, D3D11Context);
		ImGui_ImplDX11_CreateDeviceObjects();
		ConsoleLog("Finish reforming after resize.", LOGSUCCESS, false, true, true);
		UpdateD3D11Pointers = false;
	}
	if (!ImGuiInitialized)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}
	if (!OverlayActive)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);*/

	Overlay.Draw("Main Overlay", &ShowMainOverlay);

	D3D11Context->OMSetRenderTargets(1, &MainRenderTargetView, NULL);
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
}

bool __cdecl KeenGraphicsResizeRenderSwapchainHook(void* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight)
{
	ConsoleLog("In KeenGraphicsResizeSwapchainHook()", LOGFATALERROR, false, true, true);
	std::cout << "NewWidth: " << NewWidth << ", NewHeight: " << NewHeight << std::endl;
	UpdateD3D11Pointers = true;

	return KeenGraphicsResizeRenderSwapchain(KeenSwapchain, NewWidth, NewHeight);
}

void __fastcall PlayerConstructorHook(Player* PlayerPtr)
{
	GlobalPlayerPtr = (DWORD*)PlayerPtr;
	Overlay.PlayerPtr = PlayerPtr;
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
			GlobalPlayerPtr = (DWORD*)PlayerPtr;
			GlobalPlayerPtrInitialized = true;

			Overlay.PlayerPtr = PlayerPtr;

#if !PublicMode
			std::cout << "PlayerPtr: " << std::hex << std::uppercase << PlayerPtr << std::endl;
			std::cout << "PlayerPtr->Position.x: " << std::hex << std::uppercase << &PlayerPtr->Position.x << std::endl;
			std::cout << "PlayerPtr->FrametimeMultiplier: " << std::hex << std::uppercase << &PlayerPtr->FrametimeMultiplier << std::endl;
#endif
		}
	});
	if (GlobalPlayerPtr != (DWORD*)PlayerPtr)
	{
		GlobalPlayerPtr = (DWORD*)PlayerPtr;
		Overlay.PlayerPtr = PlayerPtr;

#if !PublicMode
		std::cout << "PlayerPtr: " << std::hex << std::uppercase << PlayerPtr << std::endl;
		std::cout << "PlayerPtr->Position.x: " << std::hex << std::uppercase << &PlayerPtr->Position.x << std::endl;
		std::cout << "PlayerPtr->FrametimeMultiplier: " << std::hex << std::uppercase << &PlayerPtr->FrametimeMultiplier << std::endl;
#endif
	}

	NewPlayerObject = *PlayerPtr;

	if (InfiniteJetpack)
	{
		PlayerPtr->JetpackFuelPercent = 1.0f;
	}
	if (Overlay.Invulnerable)
	{
		PlayerPtr->Flags.invulnerable = true;
		//PlayerPtr->Flags.super_jump = true;
		//PlayerPtr->Flags.use_bigsteps = true;
		//PlayerPtr->PFlags.UnlimitedAmmo = true;
		//PlayerPtr->MaxHitPoints = 2147483647;
		//PlayerPtr->HitPoints = 2147483647.0f;
		//PlayerPtr->InitialMaxHitPoints = 2147483647;
	}

	return PlayerDoFrame(&NewPlayerObject);
}

void __cdecl ExplosionCreateHook(explosion_info * ExplosionInfo, void * Source, void * Owner, vector * Position, matrix * Orientation, vector * Direction, void * WeaponInfo, bool FromServer)
{
	std::call_once(HookExplosionCreateInitialCall, [&]()
	{
#if !PublicMode
		ConsoleLog("First time in ExplosionCreate() hook.\n", LOGSUCCESS, false, true);
#endif
	});

	NewExplosionInfo = *ExplosionInfo;
	if (MinimumExplosionRadius < 0.000000f)
	{
		MinimumExplosionRadius = 0.000000f;
	}

	if (UseGlobalExplosionStrengthMultiplier)
	{
		std::cout << "Address of ExplosionInfo: " << ExplosionInfo << ", Hex: " << std::hex << std::uppercase << ExplosionInfo << std::endl;
		ConsoleLog(std::string("ExplosionInfo->m_name: " + std::string(NewExplosionInfo.m_name)).c_str(), LOGMESSAGE, false, true, true);
		ConsoleLog(std::string("ExplosionInfo->m_unique_id: " + std::to_string(NewExplosionInfo.m_unique_id)).c_str(), LOGMESSAGE, false, true, true);
		ConsoleLog(std::string("Before, Explosion radius: " + std::to_string(NewExplosionInfo.m_radius)).c_str(), LOGMESSAGE, false, true, true);
		ConsoleLog(std::string("Increasing explosion values by a factor of " + std::to_string(GlobalExplosionStrengthMultiplier)).c_str(), LOGMESSAGE, false, true, true);

		NewExplosionInfo.m_radius *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_impulse_magnitude *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_knockdown_radius *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_secondary_radius *= GlobalExplosionStrengthMultiplier;
		NewExplosionInfo.m_structural_damage = (int)(GlobalExplosionStrengthMultiplier * (float)(NewExplosionInfo.m_structural_damage)); //Did this instead of *= to avoid a compiler error. Probably unecessary.

		ConsoleLog(std::string("After, Explosion radius: " + std::to_string(NewExplosionInfo.m_radius) + "\n").c_str(), LOGMESSAGE, false, true, true);

		*ExplosionInfo = NewExplosionInfo;
	}

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
		ConsoleLog("First time in ObjectUpdatePosAndOrient() hook.\n", LOGSUCCESS, false, true);
#endif
	});
	//ConsoleLog("1\n", LOGSUCCESS, false, true);
	/*if (Overlay.NeedPlayerPosSet)
	{
		if (GlobalPlayerPtrInitialized)
		{
			if (GlobalPlayerPtr == (DWORD*)ObjectPtr)
			{
				//ConsoleLog("Manually setting Player.Object.Position in ObjectUpdatePosAndOrient() hook.\n", LOGWARNING, false, true);
				NewObjectPosition = *UpdatedPosition;
				
				NewObjectPosition.x = Overlay.PlayerPositionTargetArray[0];
				NewObjectPosition.y = Overlay.PlayerPositionTargetArray[1];
				NewObjectPosition.z = Overlay.PlayerPositionTargetArray[2];
				
				//UpdatedPosition->x = Overlay.PlayerPositionTargetArray[0];
				//UpdatedPosition->y = Overlay.PlayerPositionTargetArray[1];
				//UpdatedPosition->z = Overlay.PlayerPositionTargetArray[2];

				//ConsoleLog("Done manually setting Player.Object.Position in ObjectUpdatePosAndOrient() hook.\n", LOGSUCCESS, false, true);
				Overlay.NeedPlayerPosSet = false;
				return ObjectUpdatePosAndOrient(ObjectPtr, edx, &NewObjectPosition, UpdatedOrientation, SetHavokData);
				//ConsoleLog("You shouldn't see this. In ObjectUpdatePosAndOrient() hook\n", LOGSUCCESS, false, true);
			}
		}
	}*/
	//ConsoleLog("2\n", LOGSUCCESS, false, true);
	if (GlobalPlayerPtrInitialized)
	{
		if (GlobalPlayerPtr == (DWORD*)ObjectPtr)
		{
			///std::cout << "PlayerSetHavokData: " << SetHavokData << std::endl;
		}
	}
	///SetHavokData = true;
	//ConsoleLog("3\n", LOGSUCCESS, false, true);
	return ObjectUpdatePosAndOrient(ObjectPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
}

void __fastcall HumanUpdatePosAndOrientHook(Human* HumanPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData)
{
	std::call_once(HookHumanUpdatePosAndOrientInitialCall, [&]()
	{
#if !PublicMode
		ConsoleLog("First time in HumanUpdatePosAndOrient() hook.\n", LOGSUCCESS, false, true);
#endif
	});
	if (Overlay.NeedPlayerPosSet)
	{
		if (GlobalPlayerPtrInitialized)
		{
			if (GlobalPlayerPtr == (DWORD*)HumanPtr)
			{
				//std::cout << "Player HumanPtr found!" << std::endl;
				//std::cout << "Proof, HumanPtr->Position.y: " << HumanPtr->Position.y << std::endl;
				ConsoleLog("Manually setting Player.Object.Position in HumanUpdatePosAndOrient() hook.\n", LOGWARNING, false, true);
				NewObjectPosition = *UpdatedPosition;

				NewObjectPosition.x = Overlay.PlayerPositionTargetArray[0];
				NewObjectPosition.y = Overlay.PlayerPositionTargetArray[1];
				NewObjectPosition.z = Overlay.PlayerPositionTargetArray[2];

				Overlay.NeedPlayerPosSet = false;

				return HumanUpdatePosAndOrient(HumanPtr, edx, &NewObjectPosition, UpdatedOrientation, SetHavokData);
			}
		}
	}
	if (Overlay.NeedPlayerVelocitySet)
	{
		if (GlobalPlayerPtrInitialized)
		{
			if (GlobalPlayerPtr == (DWORD*)HumanPtr)
			{
					HumanPtr->Velocity.x = Overlay.PlayerVelocityTargetArray[0];
					HumanPtr->Velocity.y = Overlay.PlayerVelocityTargetArray[1];
					HumanPtr->Velocity.z = Overlay.PlayerVelocityTargetArray[2];
			}
		}
	}

	//HumanPtr->Flags.start_jump = 2147483647;
	//HumanPtr->Flags.super_jump = 2147483647;

	//std::cout << "HumanPtr->Flags.start_jump: " << HumanPtr->Flags.start_jump << std::endl;
	//std::cout << "HumanPtr->Flags.super_jump: " << HumanPtr->Flags.super_jump << std::endl;

	return HumanUpdatePosAndOrient(HumanPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
}

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

	std::cout << "CharacterController Address: " << std::hex << std::uppercase << CharController << std::endl;

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