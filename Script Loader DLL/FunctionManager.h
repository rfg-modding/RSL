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

    /*Helper function used which sets a function pointer to ModuleBase + RelativeAddress. Makes code cleaner and less repetitive.*/
    template<typename T>
    void RegisterFunction(T& Function, DWORD RelativeAddress)
    {
        Function = reinterpret_cast<T>(Globals::ModuleBase + RelativeAddress);
    }
};

