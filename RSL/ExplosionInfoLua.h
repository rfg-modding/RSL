#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindFixedArrayWrapperExplosionInfo(sol::state& LuaState);
    void BindExplosionInfo(sol::state& LuaState);
};