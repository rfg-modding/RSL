#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindTimestampRealtime(sol::state& LuaState);
	void BindColor(sol::state& LuaState);
	void BindNanoCallbackInfo(sol::state& LuaState);
	void BindTimestamp(sol::state& LuaState);
	void BindTimestampPercent(sol::state& LuaState);
}