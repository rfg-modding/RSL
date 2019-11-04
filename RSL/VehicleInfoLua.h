#pragma once
#include "SolStateForward.h"

namespace Lua
{
    void BindRfgFarrayVehicleInfo163(sol::state& LuaState);
    void BindBbox(sol::state& LuaState);
    void BindVehicleInfoAxleWheelInfo(sol::state& LuaState);
    void BindVehicleInfoTransmissionInfo(sol::state& LuaState);
    void BindVehicleCameraSettings(sol::state& LuaState);
    void BindAnimlibBonesUsedInfo(sol::state& LuaState);
    void BindVehicleInfoFlags(sol::state& LuaState);
    void BindLodInfo(sol::state& LuaState);
    void BindVehicleInfo(sol::state& LuaState);
}