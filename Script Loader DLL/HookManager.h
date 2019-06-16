#pragma once
#include "Hooks.h"


/* POD class with basic info about a hook that minhook needs to create, enable, disable them.*/
class Hook
{
public:
	Hook() = default;
	Hook(LPVOID Target_, LPVOID Detour_, LPVOID* Original_) : Target(Target_), Detour(Detour_), Original(Original_) { }

	LPVOID Target = nullptr;
	LPVOID Detour = nullptr;
	LPVOID* Original = nullptr;
	bool Enabled = false;
};

/* Handles function hooking. This includes creating, enabling, and disabling hooks. 
 * Makes it simpler, and avoids code duplication.
 */
class HookManager
{
public:
	HookManager() = default;
	~HookManager();

	bool CreateHook(const std::string& HookName, LPVOID Target, LPVOID Detour, LPVOID* Original);
	bool EnableHook(const std::string& HookName);
	bool DisableHook(const std::string& HookName);

	void EnableAllHooks();
	void DisableAllHooks();

	bool HookExists(const std::string& HookName) const;

	std::unordered_map <std::string, Hook> HookMap;
};

