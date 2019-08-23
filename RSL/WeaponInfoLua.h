#pragma once
#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindFixedArrayWrapperWeaponInfo(sol::state& LuaState);
    void BindWeaponProjectileInfo(sol::state& LuaState);
    void BindDamageScalingInfo(sol::state& LuaState);
    void BindWeaponInfoFlags(sol::state& LuaState);
    void BindWeaponInfo(sol::state& LuaState);
}