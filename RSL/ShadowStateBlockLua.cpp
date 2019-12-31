#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindShadowStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<ShadowStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("ShadowsEnabled", sol::property(
		[](ShadowStateBlock& self) { return *self.ShadowsEnabled; },
		[](ShadowStateBlock& self, bool value) { *self.ShadowsEnabled = value; }
	));
	Utype.set("CloudShadowEnabled", sol::property(
		[](ShadowStateBlock& self) { return *self.CloudShadowEnabled; },
		[](ShadowStateBlock& self, bool value) { *self.CloudShadowEnabled = value; }
	));
	Utype.set("CloudShadowScale", sol::property(
		[](ShadowStateBlock& self) { return *self.CloudShadowScale; },
		[](ShadowStateBlock& self, float value) { *self.CloudShadowScale = value; }
	));
	Utype.set("CloudShadowIntensityScale", sol::property(
		[](ShadowStateBlock& self) { return *self.CloudShadowIntensityScale; },
		[](ShadowStateBlock& self, float value) { *self.CloudShadowIntensityScale = value; }
	));
	Utype.set("CloudShadowIntensityBias", sol::property(
		[](ShadowStateBlock& self) { return *self.CloudShadowIntensityBias; },
		[](ShadowStateBlock& self, float value) { *self.CloudShadowIntensityBias = value; }
	));
	Utype.set("ShadowMapMaxDist", sol::property(
		[](ShadowStateBlock& self) { return *self.ShadowMapMaxDist; },
		[](ShadowStateBlock& self, float value) { *self.ShadowMapMaxDist = value; }
	));
	Utype.set("ShadowMapFadePercent", sol::property(
		[](ShadowStateBlock& self) { return *self.ShadowMapFadePercent; },
		[](ShadowStateBlock& self, float value) { *self.ShadowMapFadePercent = value; }
	));
	Utype.set("ShadowPercent", sol::property(
		[](ShadowStateBlock& self) { return *self.ShadowPercent; },
		[](ShadowStateBlock& self, float value) { *self.ShadowPercent = value; }
	));
	Utype.set("DropShadowPercent", sol::property(
		[](ShadowStateBlock& self) { return *self.DropShadowPercent; },
		[](ShadowStateBlock& self, float value) { *self.DropShadowPercent = value; }
	));
	Utype.set("TerrainShadowMaxDist", sol::property(
		[](ShadowStateBlock& self) { return *self.TerrainShadowMaxDist; },
		[](ShadowStateBlock& self, float value) { *self.TerrainShadowMaxDist = value; }
	));
	RfgTable.set_usertype("ShadowStateBlock", Utype);
#endif
}