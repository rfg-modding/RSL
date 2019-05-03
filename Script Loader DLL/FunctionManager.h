#pragma once
#include "Functions.h"

/* Simple class used to initialize rfg function pointers when the script loader is run. Needs
 * to be done at runtime since the ModuleBase address value of the script loader DLL varies
 * depending on the user and when it's run. See Functions.h/.cpp for the declarations of the
 * function pointers.
 */
class FunctionManager
{
public:
	FunctionManager() = default;
	~FunctionManager() = default;

	void Initialize();
};

