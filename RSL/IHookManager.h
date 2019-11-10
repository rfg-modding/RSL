#pragma once
#include <string>

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

protected:
    IHookManager() = default;
};