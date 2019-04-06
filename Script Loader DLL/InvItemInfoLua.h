#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindInventoryItem(sol::state& LuaState);
	void BindChecksumStri(sol::state& LuaState);
	void BindInvItemInfo(sol::state& LuaState);
}