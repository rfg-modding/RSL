#pragma once
#include "Hooks.h"

enum HookType
{
	NONE,
	GAMEHOOK,
	D3D11HOOK
};

class Hook
{
public:
	Hook() = default;
	Hook(HookType Type_, LPVOID Target_, LPVOID Detour_, LPVOID* Original_) : Type(Type_), Target(Target_), Detour(Detour_), Original(Original_) { }

	HookType Type = NONE;
	LPVOID Target = nullptr;
	LPVOID Detour = nullptr;
	LPVOID* Original = nullptr;
	bool Enabled = false;
};

class HookManager
{
public:
	HookManager() = default;
	~HookManager();

	bool CreateHook(const std::string& HookName, HookType Type, LPVOID Target, LPVOID Detour, LPVOID* Original, bool EnableNow);
	bool EnableHook(const std::string& HookName);
	bool DisableHook(const std::string& HookName);

	void EnableAllHooks();
	void DisableAllHooks();
	
	void EnableAllHooksOfType(HookType Type);
	void DisableAllHooksOfType(HookType Type);

	bool HookExists(const std::string& HookName) const;

	std::map <std::string, Hook> HookMap;
};

