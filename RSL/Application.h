#pragma once
#include "GuiSystem.h"
#include "IIPCManager.h"
#include "ICameraManager.h"
#include "IFunctionManager.h"
#include "IHookManager.h"
#include "ISnippetManager.h"

class Application
{
public:
    Application();
    ~Application() = default;

    void Run();
    bool LoadDataFromConfig();

    //Keeps track of how long someone has held down the deactivation key. Currently F3.
    unsigned int ExitKeysPressCount = 0;

private:
    void Init();
    void InitLogger();
    void CheckForImproperInstallation() const;
    void InitRSL();
    void InitHookingSystem();
    void WaitForValidGameState() const;
    void TrySetMemoryLocations();
    void InitOverlays();
    void OpenDefaultLogs();
    void MainLoop();
    void Exit();
    void CreateHooks();

    [[nodiscard]] bool ShouldClose() const;
    void OpenConsole();
    void CloseConsole() const;
    void SetMemoryLocations();
    [[nodiscard]] bool IsFolderPlacementError() const;

    std::shared_ptr<IIpcManager> IpcManager = nullptr;
    std::shared_ptr<ISnippetManager> SnippetManager = nullptr;
    std::shared_ptr<ICameraManager> CameraManager = nullptr;
    std::shared_ptr<IFunctionManager> Functions = nullptr;
    std::shared_ptr<IScriptManager> Scripts = nullptr;
    std::shared_ptr<IHookManager> Hooks = nullptr;
    GuiSystem Gui;

    /* Used to ensure proper opening/closing of the debug console. Mainly used to make sure
       multiple consoles aren't opened when repeatedly injecting the script loader during dev.*/
    bool PreExistingConsole = true;
    bool AutorunScriptsRun = false;
};
