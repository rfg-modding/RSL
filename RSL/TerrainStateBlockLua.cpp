#include "GraphicsStatesLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindTerrainStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<TerrainStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("DetailMapTiling", sol::property(
		[](TerrainStateBlock& self) { return *self.DetailMapTiling; },
		[](TerrainStateBlock& self, float value) { *self.DetailMapTiling = value; }
	));
	Utype.set("DetailMapScale", sol::property(
		[](TerrainStateBlock& self) { return *self.DetailMapScale; },
		[](TerrainStateBlock& self, float value) { *self.DetailMapScale = value; }
	));
	Utype.set("DetailMapBias", sol::property(
		[](TerrainStateBlock& self) { return *self.DetailMapBias; },
		[](TerrainStateBlock& self, float value) { *self.DetailMapBias = value; }
	));
	Utype.set("DetailMapBlend", sol::property(
		[](TerrainStateBlock& self) { return *self.DetailMapBlend; },
		[](TerrainStateBlock& self, float value) { *self.DetailMapBlend = value; }
	));
	Utype.set("DetailMapEnable", sol::property(
		[](TerrainStateBlock& self) { return *self.DetailMapEnable; },
		[](TerrainStateBlock& self, bool value) { *self.DetailMapEnable = value; }
	));
	Utype.set("SpecularEnable", sol::property(
		[](TerrainStateBlock& self) { return *self.SpecularEnable; },
		[](TerrainStateBlock& self, bool value) { *self.SpecularEnable = value; }
	));
	Utype.set("RenderAlphaSkirts", sol::property(
		[](TerrainStateBlock& self) { return *self.RenderAlphaSkirts; },
		[](TerrainStateBlock& self, bool value) { *self.RenderAlphaSkirts = value; }
	));
	Utype.set("AnisotropyLevel", sol::property(
		[](TerrainStateBlock& self) { return *self.AnisotropyLevel; },
		[](TerrainStateBlock& self, int value) { *self.AnisotropyLevel = value; }
	));
	Utype.set("FadeStart", sol::property(
		[](TerrainStateBlock& self) { return *self.FadeStart; },
		[](TerrainStateBlock& self, float value) { *self.FadeStart = value; }
	));
	Utype.set("FadeEnd", sol::property(
		[](TerrainStateBlock& self) { return *self.FadeEnd; },
		[](TerrainStateBlock& self, float value) { *self.FadeEnd = value; }
	));
	Utype.set("MedLod", sol::property(
		[](TerrainStateBlock& self) { return *self.MedLod; },
		[](TerrainStateBlock& self, bool value) { *self.MedLod = value; }
	));
	Utype.set("UseNewRenderer", sol::property(
		[](TerrainStateBlock& self) { return *self.UseNewRenderer; },
		[](TerrainStateBlock& self, bool value) { *self.UseNewRenderer = value; }
	));
	RfgTable.set_usertype("TerrainStateBlock", Utype);
#endif
}