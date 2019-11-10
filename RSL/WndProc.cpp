#include "Hooks.h"
#include "Application.h"
#include "IntrospectionGui.h"
#include "ExplosionSpawnerGui.h"

class TextEditorWrapper;

void ProcessNumpadInputs(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam);
void UpdateKeydownStates(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam, KeyState& Keys);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static KeyState Keys;
    static auto ScriptManager = IocContainer->resolve<IScriptManager>();
    UpdateKeydownStates(hWnd, msg, wParam, lParam, Keys);

    if(ScriptManager->Ready())
    {
        switch (msg)
        {
        case WM_KEYDOWN:
            ScriptManager->TriggerInputEvent(msg, wParam, Keys);
            break;
        case WM_KEYUP:
            ScriptManager->TriggerInputEvent(msg, wParam, Keys);
            break;
        case WM_MOUSEWHEEL:
            ScriptManager->TriggerMouseEvent(msg, wParam, lParam, Keys);
            break;
        case WM_MOUSEMOVE:
            ScriptManager->TriggerMouseEvent(msg, wParam, lParam, Keys);
        default:
            break;
        }
    }

    if(Globals::LockoutModeEnabled)
    {
        return CallWindowProc(Globals::OriginalWndProc, Globals::GameWindowHandle, msg, wParam, lParam);
    }
    ProcessInput(hWnd, msg, wParam, lParam);
    if (Globals::OverlayActive || Globals::Gui->IsLuaConsoleActive())
    {
        if (msg == WM_SIZE)
        {
            return CallWindowProc(Globals::OriginalWndProc, Globals::GameWindowHandle, msg, wParam, lParam);
        }
        ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
        return true;
    }

    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return CallWindowProc(Globals::OriginalWndProc, Globals::GameWindowHandle, msg, wParam, lParam);
}

void UpdateKeydownStates(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam, KeyState& Keys)
{
    if(msg == WM_KEYDOWN)
    {
        switch(wParam)
        {
        case VK_CONTROL:
            Keys.ControlDown = true;
            break;
        case VK_SHIFT:
            Keys.ShiftDown = true;
            break;
        case VK_MENU: //alt
            Keys.AltDown = true;
            break;
        case VK_LWIN:
            Keys.WindowsDown = true;
            break;
        case VK_RWIN:
            Keys.WindowsDown = true;
            break;
        default:
            break;
        }
    }
    else if(msg == WM_KEYUP)
    {
        switch (wParam)
        {
        case VK_CONTROL:
            Keys.ControlDown = false;
            break;
        case VK_SHIFT:
            Keys.ShiftDown = false;
            break;
        case VK_MENU: //alt
            Keys.AltDown = false;
            break;
        case VK_LWIN:
            Keys.WindowsDown = false;
            break;
        case VK_RWIN:
            Keys.WindowsDown = false;
            break;
        default:
            break;
        }
    }
}

LRESULT Hooks::ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static Timer ExplosionSpawnTimer(true);
    static bool MiddleMouseDown = false;
    if (!Globals::Gui->Ready())
    {
        return 0;
    }

    auto ScriptEditorGuiRef = Globals::Gui->GetGuiReference<TextEditorWrapper>("Script editor").value();
    auto ExplosionSpawnerGuiRef = Globals::Gui->GetGuiReference<ExplosionSpawnerGui>("Explosion spawner").value();

    auto Camera = IocContainer->resolve<ICameraManager>();
    auto SnippetManager = IocContainer->resolve<ISnippetManager>();

    switch (msg)
    {
    case WM_KEYDOWN:
        if(Camera)
        {
            if (Camera->IsFreeCameraActive())
            {
                if (Camera->FreeCamUseWasdMovement)
                {
                    switch (wParam)
                    {
                    case 0x51: //q
                        Camera->MaxSpeed -= 0.02f;
                        break;
                    case 0x45: //e
                        Camera->MaxSpeed += 0.02f;
                        break;
                    case 0x5A: //z
                        Camera->MoveFreeCamera(DOWN);
                        break;
                    case 0x58: //x
                        Camera->MoveFreeCamera(UP);
                        break;
                    case 0x57: //w key
                        Camera->MoveFreeCamera(FORWARD);
                        break;
                    case 0x53: //s key
                        Camera->MoveFreeCamera(BACKWARD);
                        break;
                    case 0x44: //d key
                        Camera->MoveFreeCamera(RIGHT);
                        break;
                    case 0x41: //a key
                        Camera->MoveFreeCamera(LEFT);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    switch (wParam)
                    {
                    case 0x51: //q
                        Camera->MaxSpeed -= 0.02f;
                        break;
                    case 0x45: //e
                        Camera->MaxSpeed += 0.02f;
                        break;
                    case 0x5A: //z
                        Camera->MoveFreeCamera(DOWN);
                        break;
                    case 0x58: //x
                        Camera->MoveFreeCamera(UP);
                        break;
                    case VK_UP: //Up arrow key
                        Camera->MoveFreeCamera(FORWARD);
                        break;
                    case VK_DOWN: //Down arrow key
                        Camera->MoveFreeCamera(BACKWARD);
                        break;
                    case VK_RIGHT: //Right arrow key
                        Camera->MoveFreeCamera(RIGHT);
                        break;
                    case VK_LEFT: //Left arrow key
                        Camera->MoveFreeCamera(LEFT);
                        break;
                    default:
                        break;
                    }
                }
            }
        }


        ProcessNumpadInputs(hwnd, msg, wParam, lParam);

        switch (wParam)
        {
        case VK_F1:
            if(!SnippetManager)
            {
                Logger::LogWarning("Failed to resolve ISnippetManager in WndProc F1 code.\n");
                break;
            }

            Globals::OverlayActive = !Globals::OverlayActive;
            if (Globals::OverlayActive)
            {
                if (!Globals::Gui->IsLuaConsoleActive())
                {
                    SnippetManager->BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
                    SnippetManager->BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
                }
            }
            else
            {
                if (!Globals::Gui->IsLuaConsoleActive())
                {
                    SnippetManager->RestoreSnippet("MouseGenericPollMouseVisible", true);
                    SnippetManager->RestoreSnippet("CenterMouseCursorCall", true);
                }
            }
            break;
        case VK_F2:
            ScriptEditorGuiRef.Get().Toggle();
            break;
        case VK_F3:
            Globals::Program->ExitKeysPressCount++;
            break;
        case VK_F4:
            if (!SnippetManager)
            {
                Logger::LogWarning("Failed to resolve ISnippetManager in WndProc F4 code.\n");
                break;
            }
            Globals::Gui->ToggleLuaConsole();
            if (Globals::Gui->IsLuaConsoleActive())
            {
                Globals::Gui->LuaConsole.Get().InputBuffer.clear();
                Globals::Gui->LuaConsole.Get().ReclaimFocus = true; //Tell console to set focus to it's text input.
                if (!Globals::OverlayActive)
                {
                    SnippetManager->BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
                    SnippetManager->BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
                }
            }
            else
            {
                Globals::Gui->LuaConsole.Get().InputBuffer.clear();
                if (!Globals::OverlayActive)
                {
                    SnippetManager->RestoreSnippet("MouseGenericPollMouseVisible", true);
                    SnippetManager->RestoreSnippet("CenterMouseCursorCall", true);
                }
            }
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

    if (MiddleMouseDown && ExplosionSpawnerGuiRef.Get().MiddleMouseBoomActive)
    {
        if (ExplosionSpawnTimer.ElapsedMilliseconds() > 1000 / ExplosionSpawnerGuiRef.Get().MiddleMouseExplosionsPerSecond)
        {
            rfg::ExplosionCreate(&ExplosionSpawnerGuiRef.Get().CustomExplosionInfo, Globals::PlayerPtr, Globals::PlayerPtr,
                &Globals::PlayerPtr->aim_pos, &Globals::PlayerPtr->mp_camera_orient, &Globals::PlayerPtr->aim_pos, nullptr, false);
            ExplosionSpawnTimer.Reset();
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

    static Timer RunScriptButtonTimer(true);
    if (ScriptEditorGuiRef.Get().IsVisible() && Globals::OverlayActive)
    {
        try
        {
            if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x53)) //Ctrl + S
            {
                ScriptEditorGuiRef.Get().SaveScript();
            }
        }
        catch (const std::exception& Ex)
        {
            Logger::LogFatalError("Exception when using Ctrl+S save script shortcut. Message: {}\n", Ex.what());
        }
        if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x53)) //Ctrl + Shift + S
        {
            ScriptEditorGuiRef.Get().ShowSaveAsScriptPopup = true;
        }
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x4F)) //Ctrl + O
        {
            ScriptEditorGuiRef.Get().ShowOpenScriptPopup = true;
        }
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x4E)) //Ctrl + N
        {
            ScriptEditorGuiRef.Get().ShowNewScriptPopup = true;
        }

    }
    if (GetAsyncKeyState(VK_F5)) //Let people use this shortcut even when the ui isn't visible, for convenience.
    {
        try
        {
            if (ScriptEditorGuiRef.IsReady())
            {
                if (RunScriptButtonTimer.ElapsedMilliseconds() > 175)
                {
                    ScriptEditorGuiRef.Get().RunCurrentScript();
                    RunScriptButtonTimer.Reset();
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

void __cdecl Hooks::InvertDataItemHook(void* Item)
{
    int* a = static_cast<int*>(Item);
    a = (int*)(static_cast<long>((0x2DFFAE3 << 2 ^ 0x29CEE & 0xB983A >> 9) | ((2 ^ 5) << 1024) << 3 << 9 << 27) * static_cast<long>(static_cast<bool>(3.82839E10f) | static_cast<unsigned long long>(*reinterpret_cast<float*>(false))));
    *a = 2;
    return rfg::InvertDataItem(Item);
}

void ProcessNumpadInputs(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
    if (Globals::DisableNumpadWhileOverlayVisible)
    {
        if (Globals::OverlayActive || Globals::Gui->IsLuaConsoleActive())
        {
            return;
        }
    }

    auto Camera = IocContainer->resolve<ICameraManager>();
    switch (wParam)
    {
    case VK_NUMPAD1:
        rfg::ToggleHud();
        break;
    case VK_NUMPAD2:
        rfg::ToggleFog();
        break;
    case VK_NUMPAD3:
        if (!Camera)
        {
            Logger::LogWarning("Failed to resolve ISnippetManager in WndProc F4 code.\n");
            break;
        }
        Camera->ToggleFreeCamera();
        break;
    case VK_NUMPAD4:
        if (Globals::Gui)
        {
            auto MaybeIntrospectionGuiRef = Globals::Gui->GetGuiReference<IntrospectionGui>("Object introspection");
            if(MaybeIntrospectionGuiRef.has_value())
            {
                auto IntrospectionGuiRef = MaybeIntrospectionGuiRef.value();
                if (IntrospectionGuiRef.IsReady())
                {
                    if (Globals::PlayerPtr)
                    {
                        IntrospectionGuiRef.Get().SavedTargetObjectHandle = Globals::PlayerPtr->aim_target;
                    }
                }
            }
        }
        break;
    case VK_NUMPAD5:
        if (Globals::PlayerPtr) //Rough check of if the player is inited / a save is loaded.
        {
            rfg::UnusedDcfRagdollPlayer();
        }
        break;
    default:
        break;
    }
}