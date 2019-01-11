#pragma once

#include "Globals.h"
#include "Functions.h"

class FunctionManager
{
public:
	FunctionManager();
	~FunctionManager();

	void Initialize();

	uintptr_t ModuleBase = 0;
};

