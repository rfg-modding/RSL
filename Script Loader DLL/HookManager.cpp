#include "HookManager.h"

HookManager::HookManager()
{

}

HookManager::~HookManager()
{
	DisableAllHooks();
}

bool HookManager::CreateHook(std::string HookName, HookType Type, LPVOID Target, LPVOID Detour, LPVOID* Original, bool EnableNow)
{
	if (HookExists(HookName))
	{
		Logger::Log(std::string("A hook with the name \"" + HookName + "\" already exists. Failed to create."), LOGERROR);
		return false;
	}
	if (MH_CreateHook(Target, Detour, Original) != MH_OK)
	{
		Logger::Log(std::string("Failed to create " + HookName + " hook. RFGR Script Loader deactivating."), LOGFATALERROR);
		return false;
	}

	HookMap[HookName] = Hook(Type, Target, Detour, Original);
	if (EnableNow)
	{
		EnableHook(HookName);
	}
	return true;
}

bool HookManager::EnableHook(std::string HookName)
{
	if (!HookExists(HookName))
	{
		Logger::Log(std::string("A hook with the name \"" + HookName + "\" does not exist. Failed to enable."), LOGERROR);
		return false;
	}
	if (MH_EnableHook(HookMap[HookName].Target) != MH_OK)
	{
		Logger::Log(std::string("Failed to enable " + HookName + " hook. RFGR Script Loader deactivating."), LOGFATALERROR);
		return false;
	}
	return true;
}

bool HookManager::DisableHook(std::string HookName)
{
	if (!HookExists(HookName))
	{
		Logger::Log(std::string("A hook with the name \"" + HookName + "\" does not exist. Failed to disable."), LOGERROR);
		return false;
	}
	if (MH_DisableHook(HookMap[HookName].Target) != MH_OK)
	{
		Logger::Log(std::string("Failed to disable " + HookName + " hook. RFGR Script Loader deactivating."), LOGFATALERROR);
		return false;
	}
	return false;
}

void HookManager::EnableAllHooks()
{
	for (auto i = HookMap.begin(); i != HookMap.end(); i++)
	{
		EnableHook(i->first);
	}
}

void HookManager::DisableAllHooks()
{
	for (auto i = HookMap.begin(); i != HookMap.end(); i++)
	{
		DisableHook(i->first);
	}
}

void HookManager::EnableAllHooksOfType(HookType Type)
{
	for (auto i = HookMap.begin(); i != HookMap.end(); i++)
	{
		if (i->second.Type == Type)
		{
			EnableHook(i->first);
		}
	}
}

void HookManager::DisableAllHooksOfType(HookType Type)
{
	for (auto i = HookMap.begin(); i != HookMap.end(); i++)
	{
		if (i->second.Type == Type)
		{
			DisableHook(i->first);
		}
	}
}

bool HookManager::HookExists(std::string HookName)
{
	for (auto i = HookMap.begin(); i != HookMap.end(); i++)
	{
		if (i->first == HookName)
		{
			return true;
		}
	}
	return false;
}
