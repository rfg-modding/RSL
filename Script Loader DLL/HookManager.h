#pragma once
#include "Hooks.h"

enum HookType
{
	GAMEHOOK,
	D3D11HOOK
};

class Hook
{
public:
	Hook() { }
	Hook(HookType _Type, LPVOID _Target, LPVOID _Detour, LPVOID* _Original) : Type(_Type), Target(_Target), Detour(_Detour), Original(_Original) { }

	HookType Type;
	LPVOID Target;
	LPVOID Detour;
	LPVOID* Original;
	bool Enabled = false;
};

class HookManager
{
public:
	HookManager();
	~HookManager();

	bool CreateHook(std::string HookName, HookType Type, LPVOID Target, LPVOID Detour, LPVOID* Original, bool EnableNow);
	bool EnableHook(std::string HookName);
	bool DisableHook(std::string HookName);

	void EnableAllHooks();
	void DisableAllHooks();
	
	void EnableAllHooksOfType(HookType Type);
	void DisableAllHooksOfType(HookType Type);

	bool HookExists(std::string HookName);

	std::map <std::string, Hook> HookMap;
};

