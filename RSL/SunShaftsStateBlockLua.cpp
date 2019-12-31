#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindSunShaftsStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<SunShaftsStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Enabled", sol::property(
		[](SunShaftsStateBlock& self) { return *self.Enabled; },
		[](SunShaftsStateBlock& self, bool value) { *self.Enabled = value; }
	));
	Utype.set("SunMask", sol::property(
		[](SunShaftsStateBlock& self) { return *self.SunMask; },
		[](SunShaftsStateBlock& self, bool value) { *self.SunMask = value; }
	));
	Utype.set("UseHalfResSource", sol::property(
		[](SunShaftsStateBlock& self) { return *self.UseHalfResSource; },
		[](SunShaftsStateBlock& self, bool value) { *self.UseHalfResSource = value; }
	));
	Utype.set("SunSize", sol::property(
		[](SunShaftsStateBlock& self) { return *self.SunSize; },
		[](SunShaftsStateBlock& self, float value) { *self.SunSize = value; }
	));
	Utype.set("Scale", sol::property(
		[](SunShaftsStateBlock& self) { return *self.Scale; },
		[](SunShaftsStateBlock& self, float value) { *self.Scale = value; }
	));
	Utype.set("BaseLum", sol::property(
		[](SunShaftsStateBlock& self) { return *self.BaseLum; },
		[](SunShaftsStateBlock& self, float value) { *self.BaseLum = value; }
	));
	Utype.set("LumStepScale", sol::property(
		[](SunShaftsStateBlock& self) { return *self.LumStepScale; },
		[](SunShaftsStateBlock& self, float value) { *self.LumStepScale = value; }
	));
	Utype.set("Radius", sol::property(
		[](SunShaftsStateBlock& self) { return *self.Radius; },
		[](SunShaftsStateBlock& self, float value) { *self.Radius = value; }
	));
	Utype.set("ColorCurveBase", sol::property(
		[](SunShaftsStateBlock& self) { return *self.ColorCurveBase; },
		[](SunShaftsStateBlock& self, float value) { *self.ColorCurveBase = value; }
	));
	Utype.set("ColorCurveExp", sol::property(
		[](SunShaftsStateBlock& self) { return *self.ColorCurveExp; },
		[](SunShaftsStateBlock& self, float value) { *self.ColorCurveExp = value; }
	));
	Utype.set("ColorCurveShift", sol::property(
		[](SunShaftsStateBlock& self) { return *self.ColorCurveShift; },
		[](SunShaftsStateBlock& self, float value) { *self.ColorCurveShift = value; }
	));
	Utype.set("BlurMultiplier", sol::property(
		[](SunShaftsStateBlock& self) { return *self.BlurMultiplier; },
		[](SunShaftsStateBlock& self, float value) { *self.BlurMultiplier = value; }
	));
	Utype.set("BlurRho", sol::property(
		[](SunShaftsStateBlock& self) { return *self.BlurRho; },
		[](SunShaftsStateBlock& self, float value) { *self.BlurRho = value; }
	));
	Utype.set("CoronaAdaption", sol::property(
		[](SunShaftsStateBlock& self) { return *self.CoronaAdaption; },
		[](SunShaftsStateBlock& self, bool value) { *self.CoronaAdaption = value; }
	));
	RfgTable.set_usertype("SunShaftsStateBlock", Utype);
#endif
}