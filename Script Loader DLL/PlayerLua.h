#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindUpgradeItem(sol::state& LuaState);
	void BindPlayerMetadata(sol::state& LuaState);
	void BindPathfindNavInfo(sol::state& LuaState);
	void BindVehicleEnterStruct(sol::state& LuaState);
	void BindScriptSpecificData(sol::state& LuaState);
	void BindPlayerFlags(sol::state& LuaState);
	void BindUsableObject(sol::state& LuaState);
	void BindPlayer(sol::state& LuaState);
}