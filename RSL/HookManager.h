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

    template<typename T, typename U>
	bool CreateHook(const std::string& HookName, DWORD TargetAddress, T& Detour, U& Original)
    {
        if (HookExists(HookName))
        {
            Logger::LogError("A hook with the name \"{}\" already exists. Failed to create.\n", HookName);
            return false;
        }
        if (MH_CreateHook(reinterpret_cast<LPVOID>(TargetAddress), reinterpret_cast<LPVOID>(Detour), reinterpret_cast<LPVOID*>(&Original)) != MH_OK)
        {
            Logger::LogFatalError("Failed to create {} hook. RSL deactivating.\n", HookName);
            return false;
        }

        HookMap[HookName] = Hook(reinterpret_cast<LPVOID>(TargetAddress), reinterpret_cast<LPVOID>(Detour), reinterpret_cast<LPVOID*>(&Original));
        EnableHook(HookName);

        return true;
    }

	bool EnableHook(const std::string& HookName);
	bool DisableHook(const std::string& HookName);

	void EnableAllHooks();
	void DisableAllHooks();

	bool HookExists(const std::string& HookName) const;

	std::unordered_map <std::string, Hook> HookMap;
};

//template<typename T>
//void RegisterFunction(T& Function, DWORD RelativeAddress)
//{
//    Function = reinterpret_cast<T>(Globals::ModuleBase + RelativeAddress);
//}
//
///* Creates a function hook using the given args. HookName is used for debugging and logging
// * purposes. If EnableNow is true, then the hook will be immediately enabled. Returns true if
// * the hook was successfully created and false if it was not.
// */
//bool HookManager::CreateHook(const std::string& HookName, LPVOID Target, LPVOID Detour, LPVOID* Original)
//{
//    if (HookExists(HookName))
//    {
//        Logger::LogError("A hook with the name \"{}\" already exists. Failed to create.\n", HookName);
//        return false;
//    }
//    if (MH_CreateHook(Target, Detour, Original) != MH_OK)
//    {
//        Logger::LogFatalError("Failed to create {} hook. RSL deactivating.\n", HookName);
//        return false;
//    }
//
//    HookMap[HookName] = Hook(Target, Detour, Original);
//    EnableHook(HookName);
//
//    return true;
//}