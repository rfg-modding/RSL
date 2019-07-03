#include "CharacterInstanceLua.h"
#include "Functions.h"

void Lua::BindCharacterInstance(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<CharacterInstance>();
	Utype.set("new", sol::no_constructor);
	Utype.set("AimHandle", &CharacterInstance::aim_handle);
	//Utype.set("UnimpVAnimatePointer", &CharacterInstance::unimp_v_animate_pointer);
	Utype.set("OrigCharacterScale", &CharacterInstance::orig_character_scale);
	Utype.set("CharacterScale", &CharacterInstance::character_scale);
	Utype.set("CiFlags", &CharacterInstance::ci_flags);
	Utype.set("RenderAlpha", sol::property([](CharacterInstance& Self) -> int {return static_cast<int>(Self.render_alpha); }, [](CharacterInstance& Self, int Value) {Self.render_alpha = static_cast<char>(Value); }));
	Utype.set("CacheLod", sol::property([](CharacterInstance& Self) -> int {return static_cast<int>(Self.cache_lod); }, [](CharacterInstance& Self, int Value) {Self.cache_lod = static_cast<char>(Value); }));
	Utype.set("BufVertsShadowOffset", &CharacterInstance::buf_verts_shadow_offset);
	Utype.set("BufFrameVerts", &CharacterInstance::buf_frame_verts);
	Utype.set("Next", &CharacterInstance::next);
	Utype.set("Prev", &CharacterInstance::prev);
	Utype.set("VariantIndex", &CharacterInstance::variant_index);
	Utype.set("BboxMaxDimension", &CharacterInstance::bbox_max_dimension);
	//Utype.set("Rdd", &CharacterInstance::rdd);
	RfgTable.set_usertype("CharacterInstance", Utype);
}
