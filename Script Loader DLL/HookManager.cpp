#include "HookManager.h"

HookManager::~HookManager()
{
	DisableAllHooks();
}

bool HookManager::CreateHook(const std::string& HookName, const HookType Type, const LPVOID Target, LPVOID Detour, LPVOID* Original, const bool EnableNow)
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

	HookMap[HookName] = Hook(Type, Target, Detour, Original);
	if (EnableNow)
	{
		EnableHook(HookName);
	}
	return true;
}

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

void HookManager::EnableAllHooks()
{
	for (auto& i : HookMap)
	{
		EnableHook(i.first);
	}
}

void HookManager::DisableAllHooks()
{
	for (auto& i : HookMap)
	{
		DisableHook(i.first);
	}
}

void HookManager::EnableAllHooksOfType(const HookType Type)
{
	for (auto& i : HookMap)
	{
		if (i.second.Type == Type)
		{
			EnableHook(i.first);
		}
	}
}

void HookManager::DisableAllHooksOfType(const HookType Type)
{
	for (auto& i : HookMap)
	{
		if (i.second.Type == Type)
		{
			DisableHook(i.first);
		}
	}
}

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
