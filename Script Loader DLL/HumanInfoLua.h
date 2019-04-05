#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindHumanInfoFlags(sol::state& LuaState);
	void BindHumanPropGeneralInfo(sol::state& LuaState);
	void BindCharDefHead(sol::state& LuaState);
	void BindFootGroundEffects(sol::state& LuaState);
	void BindHumanInfo(sol::state& LuaState);
}