#pragma once
#include "ScriptManager.h"
#include "CameraWrapper.h"
#include "HookManager.h"
#include "FunctionManager.h"
#include "GuiSystem.h"

/* This class initializes the script loader when it's first run, and cleans up after it when
 * it's shut down. It contains all the core modules of the script loader such as the 
 * CameraWrapper, FunctionManager, ScriptManager, HookManager, and GuiSystem. Beyond 
 * initialization this class should not have much behavior in it. More detailed behavior,
 * like rendering the script loader overlay, or running scripts, should be delegated to the
 * other modules of the script loader.
 */
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

    /* Used to ensure proper opening/closing of the debug console. Mainly used to make sure 
       multiple consoles aren't opened when repeatedly injecting the script loader during dev.*/
	bool PreExistingConsole = true;
    //Keeps track of how long someone has held down the deactivation key. Currently F3.
	unsigned int ExitKeysPressCount = 0;
};

