#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindSsaoStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<SsaoStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Enabled", sol::property(
		[](SsaoStateBlock& self) { return *self.Enabled; },
		[](SsaoStateBlock& self, bool value) { *self.Enabled = value; }
	));
	Utype.set("Bias", sol::property(
		[](SsaoStateBlock& self) { return *self.Bias; },
		[](SsaoStateBlock& self, float value) { *self.Bias = value; }
	));
	Utype.set("Clamp", sol::property(
		[](SsaoStateBlock& self) { return *self.Clamp; },
		[](SsaoStateBlock& self, float value) { *self.Clamp = value; }
	));
	Utype.set("Epsilon", sol::property(
		[](SsaoStateBlock& self) { return *self.Epsilon; },
		[](SsaoStateBlock& self, float value) { *self.Epsilon = value; }
	));
	Utype.set("Falloff", sol::property(
		[](SsaoStateBlock& self) { return *self.Falloff; },
		[](SsaoStateBlock& self, float value) { *self.Falloff = value; }
	));
	Utype.set("Intensity", sol::property(
		[](SsaoStateBlock& self) { return *self.Intensity; },
		[](SsaoStateBlock& self, float value) { *self.Intensity = value; }
	));
	Utype.set("Radius", sol::property(
		[](SsaoStateBlock& self) { return *self.Radius; },
		[](SsaoStateBlock& self, float value) { *self.Radius = value; }
	));
	Utype.set("DepthFadeRange", sol::property(
		[](SsaoStateBlock& self) { return *self.DepthFadeRange; },
		[](SsaoStateBlock& self, float value) { *self.DepthFadeRange = value; }
	));
	Utype.set("DepthThreshold", sol::property(
		[](SsaoStateBlock& self) { return *self.DepthThreshold; },
		[](SsaoStateBlock& self, float value) { *self.DepthThreshold = value; }
	));
	Utype.set("EdgeSharpness", sol::property(
		[](SsaoStateBlock& self) { return *self.EdgeSharpness; },
		[](SsaoStateBlock& self, float value) { *self.EdgeSharpness = value; }
	));
	Utype.set("ImagePlanePixelsPerMeterFactor", sol::property(
		[](SsaoStateBlock& self) { return *self.ImagePlanePixelsPerMeterFactor; },
		[](SsaoStateBlock& self, float value) { *self.ImagePlanePixelsPerMeterFactor = value; }
	));
	RfgTable.set_usertype("SsaoStateBlock", Utype);
#endif
}