#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindLightingStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<LightingStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("SubstanceDiffuseScaledEnabled", sol::property(
		[](LightingStateBlock& self) { return *self.SubstanceDiffuseScaleEnabled; },
		[](LightingStateBlock& self, bool value) { *self.SubstanceDiffuseScaleEnabled = value; }
	));
	Utype.set("CoronaAdaptionRate", sol::property(
		[](LightingStateBlock& self) { return *self.CoronaAdaptionRate; },
		[](LightingStateBlock& self, float value) { *self.CoronaAdaptionRate = value; }
	));
	Utype.set("SubstanceSpecAlphaScale", sol::property(
		[](LightingStateBlock& self) { return *self.SubstanceSpecAlphaScale; },
		[](LightingStateBlock& self, float value) { *self.SubstanceSpecAlphaScale = value; }
	));
	Utype.set("SubstanceSpecPowerScale", sol::property(
		[](LightingStateBlock& self) { return *self.SubstanceSpecPowerScale; },
		[](LightingStateBlock& self, float value) { *self.SubstanceSpecPowerScale = value; }
	));
	Utype.set("SubstanceFresnelAlphaScale", sol::property(
		[](LightingStateBlock& self) { return *self.SubstanceFresnelAlphaScale; },
		[](LightingStateBlock& self, float value) { *self.SubstanceFresnelAlphaScale = value; }
	));
	Utype.set("SubstanceFresnelPowerScale", sol::property(
		[](LightingStateBlock& self) { return *self.SubstanceFresnelPowerScale; },
		[](LightingStateBlock& self, float value) { *self.SubstanceFresnelPowerScale = value; }
	));
	Utype.set("GlassFresnelBias", sol::property(
		[](LightingStateBlock& self) { return *self.GlassFresnelBias; },
		[](LightingStateBlock& self, float value) { *self.GlassFresnelBias = value; }
	));
	Utype.set("GlassFresnelPower", sol::property(
		[](LightingStateBlock& self) { return *self.GlassFresnelPower; },
		[](LightingStateBlock& self, float value) { *self.GlassFresnelPower = value; }
	));
	Utype.set("GlassDirtEnabled", sol::property(
		[](LightingStateBlock& self) { return *self.GlassDirtEnabled; },
		[](LightingStateBlock& self, bool value) { *self.GlassDirtEnabled = value; }
	));
	Utype.set("GlassReflectionEnabled", sol::property(
		[](LightingStateBlock& self) { return *self.GlassReflectionEnabled; },
		[](LightingStateBlock& self, bool value) { *self.GlassReflectionEnabled = value; }
	));
	Utype.set("IndirectLightEnabled", sol::property(
		[](LightingStateBlock& self) { return *self.IndirectLightEnabled; },
		[](LightingStateBlock& self, bool value) { *self.IndirectLightEnabled = value; }
	));
	Utype.set("AmbientSpecularEnabled", sol::property(
		[](LightingStateBlock& self) { return *self.AmbientSpecularEnabled; },
		[](LightingStateBlock& self, bool value) { *self.AmbientSpecularEnabled = value; }
	));
	Utype.set("IndirectLightScale", sol::property(
		[](LightingStateBlock& self) { return *self.IndirectLightScale; },
		[](LightingStateBlock& self, float value) { *self.IndirectLightScale = value; }
	));
	Utype.set("IndirectLightAmount", sol::property(
		[](LightingStateBlock& self) { return *self.IndirectLightAmount; },
		[](LightingStateBlock& self, float value) { *self.IndirectLightAmount = value; }
	));
	Utype.set("MainLightColorScale", sol::property(
		[](LightingStateBlock& self) { return *self.MainLightColorScale; },
		[](LightingStateBlock& self, float value) { *self.MainLightColorScale = value; }
	));
	Utype.set("AmbientColorScale", sol::property(
		[](LightingStateBlock& self) { return *self.AmbientColorScale; },
		[](LightingStateBlock& self, float value) { *self.AmbientColorScale = value; }
	));
	Utype.set("BackAmbientColorScale", sol::property(
		[](LightingStateBlock& self) { return *self.BackAmbientColorScale; },
		[](LightingStateBlock& self, float value) { *self.BackAmbientColorScale = value; }
	));
	Utype.set("AmbientSpecularScale", sol::property(
		[](LightingStateBlock& self) { return *self.AmbientSpecularScale; },
		[](LightingStateBlock& self, float value) { *self.AmbientSpecularScale = value; }
	));
	Utype.set("EnabledHemisphericAmbient", sol::property(
		[](LightingStateBlock& self) { return *self.EnabledHemisphericAmbient; },
		[](LightingStateBlock& self, bool value) { *self.EnabledHemisphericAmbient = value; }
	));
	RfgTable.set_usertype("LightingStateBlock", Utype);
#endif
}