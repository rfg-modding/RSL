#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindStreamGridCell(sol::state& LuaState);
	void BindStreamLayerMaskedCell(sol::state& LuaState);
	void BindStreamLayer(sol::state& LuaState);
	void BindDistrictFlags(sol::state& LuaState);
	void BindTDistrict(sol::state& LuaState);
	void BindTerritory(sol::state& LuaState);
	void BindStreamGrid(sol::state& LuaState);
	void BindGameSaveInfoNewData(sol::state& LuaState);
	void BindGameSaveInfo(sol::state& LuaState);
	void BindSaveLoadInfo(sol::state& LuaState);
	void BindWorldStateBuf(sol::state& LuaState);
	void BindWorldZone(sol::state& LuaState);
	void BindWorld(sol::state& LuaState);
}