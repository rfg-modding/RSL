#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindBaseGui(sol::state& LuaStateRef);
    void BindLuaGui(sol::state& LuaStateRef);
}