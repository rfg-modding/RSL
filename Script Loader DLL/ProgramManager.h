#pragma once
#include "ScriptManager.h"
#include "CameraWrapper.h"
#include "HookManager.h"
#include "FunctionManager.h"
#include "GuiSystem.h"

class ProgramManager
{
public:
	ProgramManager() = default;
	~ProgramManager();

	void Initialize();
	void OpenConsole();
	bool LoadDataFromConfig();
	void SetMemoryLocations();

	void CreateGameHooks(bool EnableNow);
	void CreateD3D11Hooks(bool EnableNow);

	bool ShouldClose() const;
	void Update();

	void CloseConsole() const;
	void Exit();

	CameraWrapper Camera;
	FunctionManager Functions;
	ScriptManager Scripts;
	HookManager Hooks;
	GuiSystem Gui;

	bool PreExistingConsole = true;
	unsigned int ExitKeysPressCount = 0;
};

