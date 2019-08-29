#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindFlyerFlags(sol::state& LuaState);
    void BindFlyer(sol::state& LuaState);
}