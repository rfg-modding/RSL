#pragma once
#include "Globals.h"
#include <chaiscript/chaiscript.hpp>
#include "Functions.h"

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void Initialize();
	void RunTestScript();

	chaiscript::ChaiScript ChaiScriptVM;
};