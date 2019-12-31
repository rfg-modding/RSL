#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindHdrStateBlock(sol::state& LuaState);
	void BindShadowStateBlock(sol::state& LuaState);
	void BindSsaoStateBlock(sol::state& LuaState);
	void BindTerrainStateBlock(sol::state& LuaState);
	void BindSunShaftsStateBlock(sol::state& LuaState);
	void BindLightingStateBlock(sol::state& LuaState);
	void BindDofStateBlock(sol::state& LuaState);
	void BindMiscStateBlock(sol::state& LuaState);
}