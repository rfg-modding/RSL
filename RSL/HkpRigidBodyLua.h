#pragma once
#include "SolStateForward.h"

namespace Lua
{
	void BindHkpMaterial(sol::state& LuaState);
	void BindHkpEntity(sol::state& LuaState);
	void BindHkpRigidBody(sol::state& LuaState);
}
