#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindDofStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<DofStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("FocusStartA", sol::property(
		[](DofStateBlock& self) { return *self.FocusStartA; },
		[](DofStateBlock& self, float value) { *self.FocusStartA = value; }
	));
	Utype.set("FocusStartB", sol::property(
		[](DofStateBlock& self) { return *self.FocusStartB; },
		[](DofStateBlock& self, float value) { *self.FocusStartB = value; }
	));
	Utype.set("FocusEndA", sol::property(
		[](DofStateBlock& self) { return *self.FocusEndA; },
		[](DofStateBlock& self, float value) { *self.FocusEndA = value; }
	));
	Utype.set("FocusEndB", sol::property(
		[](DofStateBlock& self) { return *self.FocusEndB; },
		[](DofStateBlock& self, float value) { *self.FocusEndB = value; }
	));
	RfgTable.set_usertype("DofStateBlock", Utype);
#endif
}