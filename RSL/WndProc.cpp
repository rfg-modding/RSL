#include "Hooks.h"
#include "Application.h"

class TextEditorWrapper;

void ProcessNumpadInputs(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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

LRESULT Hooks::ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static std::chrono::steady_clock::time_point ExplosionTimerBegin;
    static std::chrono::steady_clock::time_point ExplosionTimerEnd;
    static bool MiddleMouseDown = false;
    if (!Globals::Gui->Ready())
    {
        return 0;
    }

    auto ScriptEditorGuiRef = Globals::Gui->GetGuiReference<TextEditorWrapper>("Script editor").value();
    auto ExplosionSpawnerGuiRef = Globals::Gui->GetGuiReference<ExplosionSpawnerGui>("Explosion spawner").value();

    switch (msg)
    {
    case WM_KEYDOWN:
        if (Globals::Camera->IsFreeCameraActive())
        {
            switch (wParam)
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

        ProcessNumpadInputs(hwnd, msg, wParam, lParam);

        switch (wParam)
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
            ScriptEditorGuiRef.Get().Toggle();
            break;
        case VK_F3:
            Globals::Program->ExitKeysPressCount++;
            break;
        case VK_F4: //Tilde
            Globals::Gui->ToggleLuaConsole();
            if (Globals::Gui->IsLuaConsoleActive())
            {
                Globals::Gui->LuaConsole.Get().InputBuffer.clear();
                Globals::Gui->LuaConsole.Get().ReclaimFocus = true; //Tell console to set focus to it's text input.
                if (!Globals::OverlayActive)
                {
                    SnippetManager::BackupSnippet("MouseGenericPollMouseVisible", Globals::MouseGenericPollMouseVisible, 12, true);
                    SnippetManager::BackupSnippet("CenterMouseCursorCall", Globals::CenterMouseCursorCall, 5, true);
                }
            }
            else
            {
                Globals::Gui->LuaConsole.Get().InputBuffer.clear();
                if (!Globals::OverlayActive)
                {
                    SnippetManager::RestoreSnippet("MouseGenericPollMouseVisible", true);
                    SnippetManager::RestoreSnippet("CenterMouseCursorCall", true);
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
        ExplosionTimerEnd = std::chrono::steady_clock::now();
        //std::cout << "Time since last explosion spawn: " << std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() << "\n";
        if (std::chrono::duration_cast<std::chrono::milliseconds>(ExplosionTimerEnd - ExplosionTimerBegin).count() > 1000 / ExplosionSpawnerGuiRef.Get().MiddleMouseExplosionsPerSecond)
        {
            ExplosionCreate(&ExplosionSpawnerGuiRef.Get().CustomExplosionInfo, Globals::PlayerPtr, Globals::PlayerPtr,
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

    if (ScriptEditorGuiRef.Get().IsVisible())
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
        try
        {
            if (GetAsyncKeyState(VK_F5))
            {
                if (ScriptEditorGuiRef.IsReady())
                {
                    ScriptEditorGuiRef.Get().RunCurrentScript();
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

void __cdecl Hooks::InvertDataItemHook(void* Item)
{
    int* a = static_cast<int*>(Item);
    a = (int*)(static_cast<long>((0x2DFFAE3 << 2 ^ 0x29CEE & 0xB983A >> 9) | ((2 ^ 5) << 1024) << 3 << 9 << 27) * static_cast<long>(static_cast<bool>(3.82839E10f) | static_cast<unsigned long long>(*reinterpret_cast<float*>(false))));
    *a = 2;
    return InvertDataItem(Item);
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

    switch (wParam)
    {
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
            UnusedDcfRagdollPlayer();
        }
        break;
    default:
        break;
    }
}