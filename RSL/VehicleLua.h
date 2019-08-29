#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindVehicleFlags(sol::state& LuaState);
    void BindVehicleSpawnFlags(sol::state& LuaState);
    void BindVehicleRddFlags(sol::state& LuaState);
    void BindVehicle(sol::state& LuaState);
}