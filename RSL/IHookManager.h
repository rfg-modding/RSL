#pragma once
#include <string>
#include "Hook.h"
#include "Logger.h"

using ulong = unsigned long;

class IHookManager
{
public:
    IHookManager(const IHookManager&) = delete;
    IHookManager& operator=(const IHookManager&) = delete;
    virtual ~IHookManager() noexcept = default;

    virtual bool EnableHook(const std::string& HookName) = 0;
    virtual bool DisableHook(const std::string& HookName) = 0;

    virtual void EnableAllHooks() = 0;
    virtual void DisableAllHooks() = 0;

    [[nodiscard]] virtual bool HookExists(const std::string& HookName) const = 0;

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

protected:
    IHookManager() = default;

    std::unordered_map <std::string, Hook> HookMap{};
};