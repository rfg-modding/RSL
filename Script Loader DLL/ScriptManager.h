#pragma once
//#include "Globals.h"
//#include <chaiscript/chaiscript.hpp>
//#include "Functions.h"
#include "CameraWrapper.h"
#include "FunctionManager.h"
#include "HookManager.h"
//#include "Hooks.h"

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void Initialize();
	void RunTestScript();
	void RunTestScript2();
};