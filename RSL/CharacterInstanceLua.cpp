#include "CharacterInstanceLua.h"
#include "Functions.h"

void Lua::BindCharacterInstance(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<CharacterInstance>
    (
        "CharacterInstance",
        "new", sol::no_constructor,
        "AimHandle", &CharacterInstance::aim_handle,
        //"UnimpVAnimatePointer", &CharacterInstance::unimp_v_animate_pointer,
        "OrigCharacterScale", &CharacterInstance::orig_character_scale,
        "CharacterScale", &CharacterInstance::character_scale,
        "CiFlags", &CharacterInstance::ci_flags,
        "RenderAlpha", sol::property([](CharacterInstance& Self) -> int {return static_cast<int>(Self.render_alpha); }, [](CharacterInstance& Self, int Value) {Self.render_alpha = static_cast<char>(Value); }),
        "CacheLod", sol::property([](CharacterInstance& Self) -> int {return static_cast<int>(Self.cache_lod); }, [](CharacterInstance& Self, int Value) {Self.cache_lod = static_cast<char>(Value); }),
        "BufVertsShadowOffset", &CharacterInstance::buf_verts_shadow_offset,
        "BufFrameVerts", &CharacterInstance::buf_frame_verts,
        "Next", &CharacterInstance::next,
        "Prev", &CharacterInstance::prev,
        "VariantIndex", &CharacterInstance::variant_index,
        "BboxMaxDimension", &CharacterInstance::bbox_max_dimension//,
        //"Rdd", & CharacterInstance::rdd
    );
}
