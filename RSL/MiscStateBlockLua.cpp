#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindMiscStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<MiscStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("FxaaEnabled", sol::property(
		[](MiscStateBlock& self) { return *self.FxaaEnabled; },
		[](MiscStateBlock& self, bool value) { *self.FxaaEnabled = value; }
	));
	Utype.set("DecalDepthBias", sol::property(
		[](MiscStateBlock& self) { return *self.DecalDepthBias; },
		[](MiscStateBlock& self, float value) { *self.DecalDepthBias = value; }
	));
	Utype.set("AlphaDistEnabled", sol::property(
		[](MiscStateBlock& self) { return *self.AlphaDistEnabled; },
		[](MiscStateBlock& self, bool value) { *self.AlphaDistEnabled = value; }
	));
	Utype.set("AlphaDistStart", sol::property(
		[](MiscStateBlock& self) { return *self.AlphaDistStart; },
		[](MiscStateBlock& self, float value) { *self.AlphaDistStart = value; }
	));
	Utype.set("AlphaDistEnd", sol::property(
		[](MiscStateBlock& self) { return *self.AlphaDistEnd; },
		[](MiscStateBlock& self, float value) { *self.AlphaDistEnd = value; }
	));
	Utype.set("DistortionScale", sol::property(
		[](MiscStateBlock& self) { return *self.DistortionScale; },
		[](MiscStateBlock& self, float value) { *self.DistortionScale = value; }
	));
	Utype.set("DistortionBlurScale", sol::property(
		[](MiscStateBlock& self) { return *self.DistortionBlurScale; },
		[](MiscStateBlock& self, float value) { *self.DistortionBlurScale = value; }
	));
	Utype.set("DistortionDepthBias", sol::property(
		[](MiscStateBlock& self) { return *self.DistortionDepthBias; },
		[](MiscStateBlock& self, float value) { *self.DistortionDepthBias = value; }
	));
	RfgTable.set_usertype("MiscStateBlock", Utype);
#endif
}