#include "HookManager.h"

HookManager::~HookManager()
{
	DisableAllHooks();
}

/* Enables a hook of the provided name if it exists. Returns true if it was successfully
 * enabled and false if it was not.
 */
bool HookManager::EnableHook(const std::string& HookName)
{
	if (!HookExists(HookName))
	{
        Logger::LogError("A hook with the name \"{}\" does not exist. Failed to enable.\n", HookName);
		return false;
	}
	if (MH_EnableHook(HookMap[HookName].Target) != MH_OK)
	{
        Logger::LogFatalError("Failed to enable {} hook. RSL deactivating.\n", HookName);
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
        Logger::LogError("A hook with the name \"{}\" does not exist. Failed to disable.\n", HookName);
		return false;
	}
	if (MH_DisableHook(HookMap[HookName].Target) != MH_OK)
	{
        Logger::LogFatalError("Failed to disable {} hook. RSL deactivating.\n", HookName);
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
