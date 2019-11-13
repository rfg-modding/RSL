#pragma once
#include "Hooks.h"
#include "IHookManager.h"

/* Handles function hooking. This includes creating, enabling, and disabling hooks. 
 * Makes it simpler, and avoids code duplication.
 */
class HookManager : public IHookManager
{
public:
    HookManager();
	~HookManager();

	bool EnableHook(const std::string& HookName) override;
	bool DisableHook(const std::string& HookName) override;

	void EnableAllHooks() override;
	void DisableAllHooks() override;

    [[nodiscard]] bool HookExists(const std::string& HookName) const override;
};