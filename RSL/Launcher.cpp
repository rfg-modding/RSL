#include "Launcher.h"
#include <iostream>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#include <handleapi.h>

void Launcher::Run()
{
    Globals::LockGameMain();
    Globals::SuspendAllThreadsExceptLauncher(LauncherThreadHandle);

    MainLoop(); 
}

bool Launcher::MainLoop()
{
    const char* ClassName = "RSL Launcher Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = LauncherWndProc;
    wc.hInstance = hModule;
    wc.lpszClassName = ClassName;

    RegisterClass(&wc);

    HWND LauncherHwnd = CreateWindowEx(
        0,                              // Optional window styles.
        ClassName,                     // Window class
        "RSL Launcher",    // Window text
        WS_OVERLAPPED,            // Window style

        // Size and position
        1000, 400, 300, 500,

        nullptr,       // Parent window    
        nullptr,       // Menu
        hModule,  // Instance handle
        nullptr        // Additional application data
    );

    if (!LauncherHwnd)
    {
        return false;
    }

    auto TopStaticText = CreateWindow("Static", "Choose whether or not to load the RSL into RFGR.", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 20, 200, 40, LauncherHwnd, nullptr, hModule, nullptr);
    auto Button0 = CreateWindow("Button", "Play with RSL (MP Disabled)", WS_CHILD | WS_VISIBLE, 50, 70, 200, 30, LauncherHwnd, nullptr, hModule, nullptr);
    auto Button1 = CreateWindow("Button", "Play vanilla Re-mars-tered", WS_CHILD | WS_VISIBLE, 50, 110, 200, 30, LauncherHwnd, reinterpret_cast<HMENU>(1), hModule, nullptr);

    ShowWindow(LauncherHwnd, SW_SHOW);
    UpdateWindow(LauncherHwnd);

    MSG msg;// = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

LRESULT __stdcall LauncherWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case 0:
            Globals::Launcher::ShouldRunRsl = true;
            PostQuitMessage(0);
            break;
        case 1:
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}