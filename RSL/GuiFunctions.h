#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindImVec2(sol::state& LuaStateRef);
    void BindImVec4(sol::state& LuaStateRef);
    void BindGuiFunctions(sol::state& LuaStateRef);
}