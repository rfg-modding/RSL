#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindIKJoint(sol::state& LuaState);
	void BindWeaponAnimationFlags(sol::state& LuaState);
	void BindHuman(sol::state& LuaState);
}