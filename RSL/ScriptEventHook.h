#pragma once
#include <sol_forward.hpp>
#include "String.h"

class ScriptEventHook
{
public:
    ScriptEventHook(std::string _HookName, sol::function _Hook) : HookName(_HookName), Hook(_Hook) {}
    ScriptEventHook() = default;
    ~ScriptEventHook() = default;

    std::string HookName; //Todo: Figure out if this is really needed
    sol::function Hook;
    bool Enabled = true;
    bool DeleteOnNextUpdate = false;
};
