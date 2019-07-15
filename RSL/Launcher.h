#pragma once
#include "Application.h"

extern LRESULT __stdcall LauncherWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Launcher
{
public:
    Launcher(HANDLE _LauncherThreadHandle, HMODULE _hModule) : LauncherThreadHandle(_LauncherThreadHandle), hModule(_hModule) {}
    ~Launcher() = default;

    void Run();
    bool MainLoop();

    void LockGameMain();
    void UnlockGameMain();
    void SuspendAllThreadsExceptLauncher();
    void ResumeAllThreads();

    std::vector<HANDLE> RfgThreadHandles;
    HANDLE LauncherThreadHandle = nullptr;
    HMODULE hModule;
};