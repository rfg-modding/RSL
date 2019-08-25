#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindRfgBaseArrayObjectPtr(sol::state& LuaState);
	void BindRfgFArray(sol::state& LuaState);
	void BindTimestampRealtime(sol::state& LuaState);
	void BindColor(sol::state& LuaState);
	void BindNanoCallbackInfo(sol::state& LuaState);
	void BindTimestamp(sol::state& LuaState);
	void BindTimestampPercent(sol::state& LuaState);
}