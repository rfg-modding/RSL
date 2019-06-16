#include "HookManager.h"

HookManager::~HookManager()
{
	DisableAllHooks();
}

/* Creates a function hook using the given args. HookName is used for debugging and logging 
 * purposes. If EnableNow is true, then the hook will be immediately enabled. Returns true if
 * the hook was successfully created and false if it was not.
 */
bool HookManager::CreateHook(const std::string& HookName, LPVOID Target, LPVOID Detour, LPVOID* Original)
{
	if (HookExists(HookName))
	{
		Logger::Log(std::string("A hook with the name \"" + HookName + "\" already exists. Failed to create."), LogError);
		return false;
	}
	if (MH_CreateHook(Target, Detour, Original) != MH_OK)
	{
		Logger::Log(std::string("Failed to create " + HookName + " hook. RFGR Script Loader deactivating."), LogFatalError);
		return false;
	}

	HookMap[HookName] = Hook(Target, Detour, Original);
	EnableHook(HookName);

	return true;
}

/* Enables a hook of the provided name if it exists. Returns true if it was successfully
 * enabled and false if it was not.
 */
bool HookManager::EnableHook(const std::string& HookName)
{
	if (!HookExists(HookName))
	{
		Logger::Log(std::string("A hook with the name \"" + HookName + "\" does not exist. Failed to enable."), LogError);
		return false;
	}
	if (MH_EnableHook(HookMap[HookName].Target) != MH_OK)
	{
		Logger::Log(std::string("Failed to enable " + HookName + " hook. RFGR Script Loader deactivating."), LogFatalError);
		return false;
	}
	return true;
}

/* Disables a hook of the provided name if it exists. Returns true if it was successfully
 * disabled and false if it was not.
 */
bool HookManager::DisableHook(const std::string& HookName)
{
	if (!HookExists(HookName))
	{
		Logger::Log(std::string("A hook with the name \"" + HookName + "\" does not exist. Failed to disable."), LogError);
		return false;
	}
	if (MH_DisableHook(HookMap[HookName].Target) != MH_OK)
	{
		Logger::Log(std::string("Failed to disable " + HookName + " hook. RFGR Script Loader deactivating."), LogFatalError);
		return false;
	}
	return false;
}

/* Enables all hooks.*/
void HookManager::EnableAllHooks()
{
	for (auto& i : HookMap)
	{
		EnableHook(i.first);
	}
}

/* Disabled all hooks.*/
void HookManager::DisableAllHooks()
{
	for (auto& i : HookMap)
	{
		DisableHook(i.first);
	}
}

/* Takes a std::string as input. Returns a hook with that name exists, and false if it doesn't.*/
bool HookManager::HookExists(const const std::string& HookName) const
{
	for (const auto& i : HookMap)
	{
		if (i.first == HookName)
		{
			return true;
		}
	}
	return false;
}
