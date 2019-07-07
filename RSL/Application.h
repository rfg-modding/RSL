#pragma once
#include "ScriptManager.h"
#include "CameraWrapper.h"
#include "HookManager.h"
#include "FunctionManager.h"
#include "GuiSystem.h"

class Application
{
public:
    Application() = default;
    ~Application() = default;

    void Run();

    //Keeps track of how long someone has held down the deactivation key. Currently F3.
    unsigned int ExitKeysPressCount = 0;

private:
    void Init();
    void InitLogger();
    void CheckForImproperInstallation() const;
    void InitRSL();
    void OpenDefaultLogs();
    void MainLoop();
    void Exit();
    void CreateHooks();

    bool ShouldClose() const;
    void OpenConsole();
    void CloseConsole();
    void SetMemoryLocations();
    bool IsFolderPlacementError() const;
    bool LoadDataFromConfig();

    CameraWrapper Camera;
    FunctionManager Functions;
    ScriptManager Scripts;
    HookManager Hooks;
    GuiSystem Gui;

    /* Used to ensure proper opening/closing of the debug console. Mainly used to make sure
       multiple consoles aren't opened when repeatedly injecting the script loader during dev.*/
    bool PreExistingConsole = true;

};