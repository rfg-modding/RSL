#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindNanoCallbackInfo(sol::state& LuaState);
	void BindTimestamp(sol::state& LuaState);
	void BindTimestampPercent(sol::state& LuaState);
}