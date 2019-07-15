#include "Hooks.h"
#include "Application.h"

//Todo: Move each hook function into their own file, stick the in the Hooks namespace
//Todo: See if the std::once_flag values can just be made into static vars in their hooks
//Todo: Add uncaught exception handling to D3DPresent hook since a lot of gui and other stuff goes on in there

D3D11Present D3D11PresentObject;

std::chrono::steady_clock::time_point ExplosionTimerBegin;
std::chrono::steady_clock::time_point ExplosionTimerEnd;

std::once_flag HookD3D11PresentInitialCall;
std::once_flag KeenGraphicsBeginFrameHookInitialCall;

std::once_flag HookExplosionCreateInitialCall;

std::once_flag HookPlayerDoFrameInitialCall;

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
			Logger::LogWarning("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.\n");
			ImGui_ImplDX11_InvalidateDeviceObjects();
			UpdateD3D11Pointers = true;
			Globals::D3D11Context->OMSetRenderTargets(0, 0, 0);
			Globals::MainRenderTargetView->Release();
			return CallWindowProc(Globals::OriginalWndProc, Globals::GameWindowHandle, msg, wParam, lParam);
		}
		return true;
	}

	switch (msg)
	{
		case WM_SIZE:
			//Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
   //         Globals::MainRenderTargetView->Release();
   //         Globals::MainRenderTargetView = nullptr;
   //         Globals::D3D11SwapchainPtr->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
   //         ID3D11Texture2D* pBackBuffer;
   //         Globals::D3D11SwapchainPtr->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
   //         Globals::D3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &Globals::MainRenderTargetView);
   //         pBackBuffer->Release();
	    
	        //ImGui_ImplDX11_InvalidateDeviceObjects();
			//UpdateD3D11Pointers = true;
			//Globals::D3D11Context->OMSetRenderTargets(0, 0, 0);
			//Globals::MainRenderTargetView->Release();
			break;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			break;
	}

	return CallWindowProc(Globals::OriginalWndProc, Globals::GameWindowHandle, msg, wParam, lParam);
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
        case VK_NUMPAD4:
            if(Globals::Gui)
            {
                if(Globals::Gui->Introspection)
                {
                    if(Globals::PlayerPtr)
                    {
                        Globals::Gui->Introspection->SavedTargetObjectHandle = Globals::PlayerPtr->aim_target;
                    }
                }
            }
            break;
        case VK_NUMPAD5:
            if(Globals::PlayerPtr) //Rough check of if the player is inited / a save is loaded.
            {
                UnusedDcfRagdollPlayer();
            }
            break;
		case VK_F4: //Tilde
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

	if (MiddleMouseDown && Globals::Gui->ExplosionSpawner->MiddleMouseBoomActive)
	{
		ExplosionTimerEnd = std::chrono::steady_clock::now();
		//std::cout << "Time since last explosion spawn: " << std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() << "\n";
		if (std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() > 1000 / Globals::Gui->ExplosionSpawner->MiddleMouseExplosionsPerSecond)
		{
			ExplosionCreate(&Globals::Gui->ExplosionSpawner->CustomExplosionInfo, Globals::PlayerPtr, Globals::PlayerPtr,
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
				RfgDynRepairSphere(&Gui.TweaksMenu.PlayerPtr->Position, Radius, Duration, Gui.TweaksMenu.PlayerPtr);
			}
			else if (Gui.TweaksMenu.RepairPosition == 1)
			{
				const float Radius = Gui.TweaksMenu.RepairRadius;
				const int Duration = Gui.TweaksMenu.RepairDuration;
				RfgDynRepairSphere(&Gui.TweaksMenu.PlayerPtr->aim_pos, Radius, Duration, Gui.TweaksMenu.PlayerPtr);
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
			Logger::LogFatalError("Exception when using Ctrl+S save script shortcut. Message: {}\n", Ex.what());
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
                    Globals::Gui->ScriptEditor->RunCurrentScript();
					Sleep(175);
				}
			}
		}
		catch (const std::exception& Ex)
		{
			Logger::LogFatalError("Exception when using F5 run script shortcut. Message: {}\n", Ex.what());
		}
	}
	return 0;
}

void UpdateDebugDrawRenderInterfaceValues()
{
    if(Globals::RlCameraPtr)
    {
        //matrix44& ViewMatrix = Globals::RlCameraPtr->m_view_transform;
        //matrix44& ProjectionMatrix = Globals::RlCameraPtr->m_projection_transform;
        //matrix44 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
        //matrix44 TransposedViewProjectionMatrix = ViewProjectionMatrix.GetTransposed();
        //Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&TransposedViewProjectionMatrix));

        matrix44 ModelMatrix; 
        ModelMatrix.SetToIdentity();
        rfg_camera& GameData = *Globals::Camera->GameData;
        matrix44 ViewMatrix(GameData.real_orient.rvec, GameData.real_orient.uvec, GameData.real_orient.fvec, GameData.real_pos);

        float f = tanf((Globals::pi / 2.0f) - (0.5f - GameData.real_fov));
        float RangeInv = (1.0f / (GameData.m_near_clip_dist - GameData.m_far_clip_dist));
        float Aspect = (Globals::WindowRect.right - Globals::WindowRect.left) / (Globals::WindowRect.bottom - Globals::WindowRect.top);
        vector4 Col1((f / Aspect), 0.0f, 0.0f, 0.0f);
        vector4 Col2(0.0f, f, 0.0f, 0.0f);
        vector4 Col3(0.0f, 0.0f, ((GameData.m_near_clip_dist + GameData.m_far_clip_dist) * RangeInv), -1.0f);
        vector4 Col4(0.0f, 0.0f, (((GameData.m_near_clip_dist - GameData.m_far_clip_dist) * RangeInv) * 2.0f), 0.0f);
        matrix44 ProjectionMatrix(Col1, Col2, Col3, Col4);
        Globals::vpMatrix = ProjectionMatrix * ViewMatrix;
        matrix44 MvpMatrix = ProjectionMatrix * ViewMatrix * ModelMatrix;
        Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&MvpMatrix));
        //matrix44 TransposedvpMatrix = Globals::vpMatrix.GetTransposed();
        //Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&TransposedvpMatrix));
    }

    if(Globals::Camera)
    {
        if(Globals::Camera->GameData)
        {
            vector& RealUpVec = Globals::Camera->GameData->real_orient.uvec;
            Vector3 CameraUpVector(RealUpVec.x, RealUpVec.y, RealUpVec.z);

            vector& RealRightVec = Globals::Camera->GameData->real_orient.rvec;
            Vector3 CameraRightVector(RealRightVec.x, RealRightVec.y, RealRightVec.z);

            vector& RealForwardVec = Globals::Camera->GameData->real_orient.fvec;
            Vector3 CameraForwardVector(RealForwardVec.x, RealForwardVec.y, RealForwardVec.z);
            Globals::DebugDrawRenderInterface->setCameraFrame(CameraUpVector, CameraRightVector, CameraForwardVector);
        }
    }
}

HRESULT D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext)
{
	const HRESULT Result = pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<PVOID*>(ppDevice));

	if(Result != S_OK)
	{
        Logger::LogFatalError("ID3D11SwapChain::GetDevice() failed, return value: {}\n", Result);
		return E_FAIL;
	}
	(*ppDevice)->GetImmediateContext(ppContext);

	return Result;
}


HRESULT __stdcall D3D11PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!Globals::ImGuiInitialized)
	{
		return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
	}

	if (!Globals::ScriptLoaderCloseRequested)
	{
#if DebugDrawTestEnabled
        try
        {
            if (Globals::DebugDrawRenderInterface)
            {
                UpdateDebugDrawRenderInterfaceValues();
                if (Globals::PlayerPtr)
                {

                    const ddVec3 boxColor = { 0.0f, 0.8f, 0.8f };
                    const ddVec3 boxCenter = { Globals::PlayerPtr->Position.x, Globals::PlayerPtr->Position.y, Globals::PlayerPtr->Position.z };
                    const ddVec3 UpVector = { 0.0f, 1.0f, 0.0f };

                    dd::circle(boxCenter, UpVector, boxColor, 500.0f, 2000, 5000);
                    dd::box(boxCenter, boxColor, 15.0f, 15.0f, 15.0f);
                    dd::cross(boxCenter, 1.0f);

                    const ddVec3 DebugTextPosition = { 0.2f, 0.2f, 0.0f };
                    const ddVec3 DebugTextColor = { 1.0f, 0.0f, 0.0f };
                    dd::screenText("hOi!!!!! I'm tEMMIE!!", DebugTextPosition, DebugTextColor, 2.0f, 5000); //Highly experimental code...

                    //dd::projectedText("Space asshole", boxCenter, DebugTextColor, Globals::vpMatrix, 300, 300, 300, 300, 1.0f);
                }
                dd::flush();
            }
        }
        catch (std::exception& Ex)
        {
            Logger::LogError("Exception caught while testing debug draw cube! Message: {}\n", Ex.what());
        }
#endif
        
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		Globals::Gui->Draw();
        //ImGui::ShowDemoWindow(&Globals::OverlayActive);
		Globals::D3D11Context->OMSetRenderTargets(1, &Globals::MainRenderTargetView, nullptr);
        //Globals::D3D11Context->ClearRenderTargetView(Globals::MainRenderTargetView, (float*)& clear_color);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return D3D11PresentObject(pSwapChain, SyncInterval, Flags);
}

bool __cdecl KeenGraphicsResizeRenderSwapchainHook(keen::RenderSwapChain* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight)
{
    ///Logger::Log("Entered Keen::Graphics::ResizeRenderSwapchain Hook!", LogWarning);
	//UpdateD3D11Pointers = true;


    //Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
    //Globals::MainRenderTargetView->Release();
    //Globals::MainRenderTargetView = nullptr;
    //Globals::D3D11SwapchainPtr->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
    //ID3D11Texture2D* pBackBuffer;
    //Globals::D3D11SwapchainPtr->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    //Globals::D3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &Globals::MainRenderTargetView);
    //pBackBuffer->Release();


	return KeenGraphicsResizeRenderSwapchain(KeenSwapchain, NewWidth, NewHeight);
    //return nullptr;
}

keen::GraphicsCommandBuffer* KeenGraphicsBeginFrameHook(keen::GraphicsSystem* pGraphicsSystem, keen::RenderSwapChain* pSwapChain)
{
    std::call_once(KeenGraphicsBeginFrameHookInitialCall, [&]()
    {
        Globals::KeenGraphicsSystemPtr = pGraphicsSystem;
    });
    if(Globals::KeenGraphicsSystemPtr != pGraphicsSystem)
    {
        Logger::LogWarning("Globals::KeenGraphicsSystemPtr changed!\n");
        Globals::KeenGraphicsSystemPtr = pGraphicsSystem;
    }
    //Grab required D3D11 pointers for rendering and set up imgui.
    if (!Globals::ImGuiInitialized)
    {
        if(pGraphicsSystem->pDevice)
        {
            Globals::D3D11Device = pGraphicsSystem->pDevice;
            if(pGraphicsSystem->pImmediateContext)
            {
                Globals::D3D11Context = pGraphicsSystem->pImmediateContext;
                if(pGraphicsSystem->pDefaultSwapChain)
                {
                    if(pGraphicsSystem->pDefaultSwapChain->pSwapChain)
                    {
                        Globals::D3D11SwapchainPtr = pGraphicsSystem->pDefaultSwapChain->pSwapChain;
                        if(pGraphicsSystem->pDefaultSwapChain->pBackBufferRenderTargetView)
                        {
                            //ImGui init
                            ID3D11Texture2D* BackBuffer;
                            HRESULT Result = Globals::D3D11SwapchainPtr->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&BackBuffer));
                            if (Result != S_OK)
                            {
                                Logger::LogFatalError("GetBuffer() failed, return value: {}\n", Result);
                            }

                            D3D11_RENDER_TARGET_VIEW_DESC desc = {};
                            memset(&desc, 0, sizeof(desc));
                            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Required to avoid rendering issue with overlay. Without this the proper rgb values will not be displayed.
                            desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
                            Result = Globals::D3D11Device->CreateRenderTargetView(BackBuffer, &desc, &Globals::MainRenderTargetView);
                            if (Result != S_OK)
                            {
                                Logger::LogFatalError("CreateRenderTargetView() failed, return value: {}\n", Result);
                            }
                            BackBuffer->Release();

                            //ImGui_ImplWin32_EnableDpiAwareness();  //Todo: viewports

                            IMGUI_CHECKVERSION();
                            ImGui::CreateContext();
                            ImGuiIO& io = ImGui::GetIO();
                            Globals::io = io;
                            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
                            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
                            ///io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Todo: viewports
                            ImGui::StyleColorsDark();

                            ImGui_ImplDX11_Init(Globals::D3D11Device, Globals::D3D11Context);
                            const bool RectResult = GetWindowRect(Globals::GameWindowHandle, &Globals::WindowRect);
                            if (!RectResult)
                            {
                                Logger::LogError("GetWindowRect() failed during script loader init!\n");
                            }
                            ImGui_ImplWin32_Init(Globals::GameWindowHandle);

                            const float GlobalFontSize = 17.0f;
                            std::string DefaultFontPath = std::string(Globals::GetEXEPath(false) + "RSL/Fonts/Roboto-Regular.ttf");
                            bool DefaultFontLoaded = false;
                            if (fs::exists(DefaultFontPath))
                            {
                                io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalFontSize);
                                DefaultFontLoaded = true;
                            }
                            else
                            {
                                io.Fonts->AddFontDefault();
                            }

                            static const ImWchar IconsRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
                            ImFontConfig IconsConfig;
                            IconsConfig.MergeMode = true;
                            IconsConfig.PixelSnapH = true;
                            std::string FontAwesomeSolidPath(Globals::GetEXEPath(false) + "RSL/Fonts/fa-solid-900.ttf");

                            Globals::FontNormal = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalFontSize, &IconsConfig, IconsRanges);

                            const float GlobalBigFontSize = 24.0f;
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

                            Logger::Log("ImGui Initialized.\n");

#if DebugDrawTestEnabled
                            try
                            {
                            	Globals::DebugDrawRenderInterface = new RenderInterfaceD3D11(Globals::D3D11Device, Globals::D3D11Context);
                            	dd::initialize(Globals::DebugDrawRenderInterface);
                            }
                            catch (std::exception& Ex)
                            {
                            	Logger::LogError("Exception caught while initializing debug draw! Message: {}\n", Ex.what());
                            }
#endif
                        }  
                    }
                }
            }
        }
    }

    return KeenGraphicsBeginFrame(pGraphicsSystem, pSwapChain);
}

void __fastcall PlayerDoFrameHook(Player* PlayerPtr)
{
	std::call_once(HookPlayerDoFrameInitialCall, [&]()
	{
		if (!Globals::PlayerPtr)
		{
			Globals::PlayerPtr = PlayerPtr;
			Globals::PlayerRigidBody = HavokBodyGetPointer(PlayerPtr->HavokHandle);
			Globals::Gui->SetPlayerPtr(PlayerPtr);
			if(Globals::Scripts)
			{
				Globals::Scripts->UpdateRfgPointers();
			}
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
	}
	if (!Globals::Gui->TweaksMenu || !Globals::Gui->FreeCamSettings || !Globals::Gui->FreeCamSettings->Camera)
	{
		return PlayerDoFrame(PlayerPtr);
	}

	if (Globals::InfiniteJetpack)
	{
		PlayerPtr->JetpackFuelPercent = 1.0f;
	}
	if (Globals::Gui->TweaksMenu->Invulnerable || (Globals::Camera->IsFreeCameraActive() && Globals::Gui->FreeCamSettings->PlayerFollowCam))
	{
		PlayerPtr->Flags.invulnerable = true;
		PlayerPtr->HitPoints = 2147483647.0f;
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
		GsmSetAlertLevel(Globals::Gui->TweaksMenu->CustomAlertLevel);
	}

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

        });

    return ExplosionCreate(ExplosionInfo, Source, Owner, Position, Orientation, Direction, WeaponInfo, FromServer);
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
        Logger::LogWarning("GlobalhkpWorldPtr address changed!\n");
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

    return hkpWorldStepDeltaTime(This, edx, PhysicsDeltaTime);
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

		Globals::MainScenePtr = GameRenderGetMainScene();
		if (Globals::MainScenePtr)
		{
			Globals::MainSceneRendererPtr = Globals::MainScenePtr->m_scene_renderer_p;
			if (!Globals::MainSceneRendererPtr)
			{
				Globals::MainSceneRendererPtr = Globals::MainScenePtr->m_default_scene_renderer_p;
			}
			Globals::MainSceneCameraPtr = Globals::MainSceneRendererPtr->m_part2_params.p_camera;
		}
	});
	if (This != Globals::RlCameraPtr)
	{
		Globals::RlCameraPtr = This;
	}

	return RlCameraRenderBegin(This, edx, Renderer);
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

void __fastcall world_do_frame_hook(World* This, void* edx, bool HardLoad)
{
    std::call_once(HookWorldDoFrameInitialCall, [&]()
        {
            Globals::RfgWorldPtr = This;
            Logger::Log("RFG::World hooked!\n");

            Globals::TODLightPtr = GameRenderGetTodLight();
            if (Globals::Scripts)
            {
                Globals::Scripts->UpdateRfgPointers();
            }
        });
    if (Globals::RfgWorldPtr != This)
    {
        Logger::LogWarning("GlobalRfgWorldPtr changed!\n");
        Globals::RfgWorldPtr = This;
        if (Globals::Scripts)
        {
            Globals::Scripts->UpdateRfgPointers();
        }
    }
    if (!Globals::TODLightPtr)
    {
        Globals::TODLightPtr = GameRenderGetTodLight();
    }
    if (!Globals::Gui->TweaksMenu)
    {
        return WorldDoFrame(This, edx, HardLoad);
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

    return WorldDoFrame(This, edx, HardLoad);
}

int __cdecl LuaDoBufferHook(lua_State *L, const char *buff, unsigned int size, const char *name)
{
    static std::string TempBuffer;
	std::call_once(HookLuaDoBuffer, [&]()
	{
		Globals::RfgVintLuaState = L;
	});
	if(!L)
	{
		Logger::LogWarning("RFG lua_state pointer null\n");
		return LuaDoBuffer(L, buff, size, name);
	}

	//Dump current script file
	std::string Buffer(buff, size);
	std::string Name(name);
	std::string RfgLuaPath = Globals::GetEXEPath(false);
	RfgLuaPath += "RSL/RFG_Lua/";
	fs::create_directory(RfgLuaPath);
	std::string DumpFilePath = RfgLuaPath + "Lua_Dumps/";
	fs::create_directory(DumpFilePath);
	DumpFilePath += Name;
    Logger::Log("Dumping {}\n", Name);
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
        Logger::Log("Overriding {}\n", Name);

        TempBuffer.clear();
        TempBuffer = OverrideBuffer;
		return LuaDoBuffer(L, TempBuffer.c_str(), TempBuffer.length(), name);
	}
	return LuaDoBuffer(L, buff, size, name);
}

void __fastcall ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData)
{
    std::call_once(HookObjectUpdatePosAndOrientInitialCall, [&]()
        {

        });

    return ObjectUpdatePosAndOrient(ObjectPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
}

void __fastcall StreamGridDoFrameHook(stream_grid* This, void* edx, vector* StreamPos, bool SingleZoneMode)
{
    if(!Globals::MainStreamGrid || Globals::MainStreamGrid != This)
    {
        Globals::MainStreamGrid = This;
        Logger::Log("StreamGridPtr changed, new address: {}\n", std::to_string(*reinterpret_cast<DWORD*>(This)));
    }
    return StreamGridDoFrame(This, edx, StreamPos, SingleZoneMode);
}

//spawn_status_result ObjectSpawnVehicleHook(vehicle_spawn_params* spawn_param)
//{
//    //Todo: Print custom params address (with adn without modulebase) as hex and compare with x32dbg values
//    std::cout << "\t[Hook] ModuleBase, decimal: " << Globals::ModuleBase << "\n";
//    std::cout << "\t[Hook] ModuleBase, hex: " << std::hex << Globals::ModuleBase << "\n";
//    std::cout << "\t[Hook] &CustomVehicleSpawnParams, decimal: " << &spawn_param << "\n";
//    std::cout << "\t[Hook] &CustomVehicleSpawnParams, hex: " << std::hex << &spawn_param << "\n";
//    std::cout << "\t[Hook] ModuleBase + &CustomVehicleSpawnParams, decimal: " << Globals::ModuleBase + (DWORD)&spawn_param << "\n";
//    std::cout << "\t[Hook] ModuleBase + &CustomVehicleSpawnParams, hex: " << std::hex << Globals::ModuleBase + (DWORD)&spawn_param << "\n";
//
//    return ObjectSpawnVehicle(spawn_param);
//}

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