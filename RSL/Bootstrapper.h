#pragma once
#include "IIPCManager.h"
#include "ICameraManager.h"
#include "IFunctionManager.h"
#include "IHookManager.h"
#include "ISnippetManager.h"
#include "IScriptManager.h"
#include "GuiSystem.h"

//Handles initialization of RSL hooks / managers / global data
//Todo: Define interface and have IOC Container handle this
class Bootstrapper
{
public:
    Bootstrapper();
    ~Bootstrapper() = default;

    void Init();

private:
    void InitLogger();
    void CheckForImproperInstallation();
    void InitRSL();
    void OpenDefaultLogs();

    [[nodiscard]] bool IsFolderPlacementError() const;
    [[nodiscard]] bool LoadDataFromConfig();

    void InitHooks();
    void CreateHooks();
    void WaitForValidGameState() const;
    void InitOverlays();
    void TrySetMemoryLocations();
    void SetMemoryLocations();

    std::shared_ptr<ISnippetManager> SnippetManager = nullptr;
    std::shared_ptr<ICameraManager> CameraManager = nullptr;
    std::shared_ptr<IFunctionManager> Functions = nullptr;
    std::shared_ptr<IScriptManager> Scripts = nullptr;
    std::shared_ptr<IHookManager> Hooks = nullptr;
};

