#include "Hooks.h"
#include "Application.h"
#include "IntrospectionGui.h"
#include "ExplosionSpawnerGui.h"
#include "TextEditorWrapper.h"

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
    ProcessInput(hWnd, msg, wParam, lParam, Keys);

    //Todo: Should probably cache this for performance
    static auto Gui = IocContainer->resolve<IGuiManager>();
    if (Globals::OverlayActive || Gui->IsLuaConsoleActive())
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

LRESULT Hooks::ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, const KeyState& keys)
{
    static Timer ExplosionSpawnTimer(true);
    static bool MiddleMouseDown = false;

    //Todo: Should probably cache this for performance
    static auto Gui = IocContainer->resolve<IGuiManager>();
    if (!Gui->Ready())
    {
        return 0;
    }

    //Todo: Should probably cache this for performance
    auto ScriptEditorGuiRef = Gui->GetGuiReference<TextEditorWrapper>("Script editor").value();
    auto ExplosionSpawnerGuiRef = Gui->GetGuiReference<ExplosionSpawnerGui>("Explosion spawner").value();
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
                if (!Gui->IsLuaConsoleActive())
                {
                    SnippetManager->BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
                    SnippetManager->BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
                }
            }
            else
            {
                if (!Gui->IsLuaConsoleActive())
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
            Globals::ExitKeysPressCount++;
            break;
        case VK_F4:
            if (!SnippetManager)
            {
                Logger::LogWarning("Failed to resolve ISnippetManager in WndProc F4 code.\n");
                break;
            }
            Gui->ToggleLuaConsole();
            if (Gui->IsLuaConsoleActive())
            {
                Gui->LuaConsole.Get().InputBuffer.clear();
                Gui->LuaConsole.Get().ReclaimFocus = true; //Tell console to set focus to it's text input.
                if (!Globals::OverlayActive)
                {
                    SnippetManager->BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
                    SnippetManager->BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
                }
            }
            else
            {
                Gui->LuaConsole.Get().InputBuffer.clear();
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

    if(ScriptEditorGuiRef.IsReady())
        ProcessScriptEditorInput(hwnd, msg, wParam, lParam, keys, ScriptEditorGuiRef);

    return 0;
}

void Hooks::ProcessScriptEditorInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, const KeyState& keys, GuiReference<TextEditorWrapper>& textEditor)
{
    static Timer RunScriptButtonTimer(true);
    if (textEditor.Get().IsVisible() && Globals::OverlayActive)
    {
        if (msg == WM_KEYDOWN)
        {
            if (keys.ControlDown && wParam == 0x53) //Ctrl + S
            {
                try
                {
                    textEditor.Get().SaveScript();
                }
                catch (const std::exception & Ex)
                {
                    Logger::LogFatalError("Exception when using Ctrl+S save script shortcut. Message: {}\n", Ex.what());
                }
            }
            else if (keys.ControlDown && keys.ShiftDown && wParam == 0x53) //Ctrl + Shift + S
                textEditor.Get().ShowSaveAsScriptPopup = true;
            else if (keys.ControlDown && wParam == 0x4F) //Ctrl + O
                textEditor.Get().ShowOpenScriptPopup = true;
            else if (keys.ControlDown && wParam == 0x4E) //Ctrl + N
                textEditor.Get().ShowNewScriptPopup = true;
            else if (wParam == VK_F5)
            {
                if (RunScriptButtonTimer.ElapsedMilliseconds() > 175)
                {
                    try
                    {
                        textEditor.Get().RunCurrentScript();
                        RunScriptButtonTimer.Reset();
                    }
                    catch (const std::exception & Ex)
                    {
                        Logger::LogFatalError("Exception when using F5 run script shortcut. Message: {}\n", Ex.what());
                    }
                }
            }
        }
    }
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
    //Todo: Should probably cache this for performance
    static auto Gui = IocContainer->resolve<IGuiManager>();
    if (Globals::DisableNumpadWhileOverlayVisible)
    {
        if (Globals::OverlayActive || Gui->IsLuaConsoleActive())
        {
            return;
        }
    }

    auto Camera = IocContainer->resolve<ICameraManager>();
    auto MaybeIntrospectionGuiRef = Gui->GetGuiReference<IntrospectionGui>("Object introspection");

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
        if (MaybeIntrospectionGuiRef.has_value())
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