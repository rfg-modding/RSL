#include "HumanInfoLua.h"
#include "Functions.h"

void Lua::BindHumanInfoFlags(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<human_info_flags>
    (
        "HumanInfoFlags",
        "new", sol::no_constructor,
        "Female", sol::property(itsy_bitsy::read<human_info_flags, 0>, itsy_bitsy::write<human_info_flags, 0>), //int8 - 1
        "Coin", sol::property(itsy_bitsy::read<human_info_flags, 1>, itsy_bitsy::write<human_info_flags, 1>), //int8 - 1
        "Preload", sol::property(itsy_bitsy::read<human_info_flags, 2>, itsy_bitsy::write<human_info_flags, 2>), //int8 - 1
        "Officer", sol::property(itsy_bitsy::read<human_info_flags, 3>, itsy_bitsy::write<human_info_flags, 3>), //int8 - 1
        "Unarmed", sol::property(itsy_bitsy::read<human_info_flags, 4>, itsy_bitsy::write<human_info_flags, 4>), //int8 - 1
        "VIP", sol::property(itsy_bitsy::read<human_info_flags, 5>, itsy_bitsy::write<human_info_flags, 5>), //int8 - 1
        "UseTechLevel", sol::property(itsy_bitsy::read<human_info_flags, 6>, itsy_bitsy::write<human_info_flags, 6>), //int8 - 1
        "Sniper", sol::property(itsy_bitsy::read<human_info_flags, 7>, itsy_bitsy::write<human_info_flags, 7>), //int8 - 1
        "EliteDodge", sol::property(itsy_bitsy::read<human_info_flags, 8>, itsy_bitsy::write<human_info_flags, 8>), //int8 - 1
        "RiotShield", sol::property(itsy_bitsy::read<human_info_flags, 9>, itsy_bitsy::write<human_info_flags, 9>), //int8 - 1
        "BodyArmor", sol::property(itsy_bitsy::read<human_info_flags, 10>, itsy_bitsy::write<human_info_flags, 10>), //int8 - 1
        "NonFlammable", sol::property(itsy_bitsy::read<human_info_flags, 11>, itsy_bitsy::write<human_info_flags, 11>), //int8 - 1
        "NoAttachingProjectiles", sol::property(itsy_bitsy::read<human_info_flags, 12>, itsy_bitsy::write<human_info_flags, 12>), //int8 - 1
        "GuerrillaTech", sol::property(itsy_bitsy::read<human_info_flags, 13>, itsy_bitsy::write<human_info_flags, 13>), //int8 - 1
        "GuerrillaRfc", sol::property(itsy_bitsy::read<human_info_flags, 14>, itsy_bitsy::write<human_info_flags, 14>), //int8 - 1
        "OldCoot", sol::property(itsy_bitsy::read<human_info_flags, 15>, itsy_bitsy::write<human_info_flags, 15>), //int8 - 1
        "Dan", sol::property(itsy_bitsy::read<human_info_flags, 16>, itsy_bitsy::write<human_info_flags, 16>), //int8 - 1
        "Jenkins", sol::property(itsy_bitsy::read<human_info_flags, 17>, itsy_bitsy::write<human_info_flags, 17>), //int8 - 1*/
        "DriverlessExit", &human_info_flags::driverless_exit_only //bool*/
    );
}

void Lua::BindHumanPropGeneralInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<human_prop_general_info>
    (
        "HumanPropGeneralInfo",
        "new", sol::no_constructor,
        "PropName", &human_prop_general_info::prop_name,
        "AppearancePercent", &human_prop_general_info::appearance_percent,
        "PropType", &human_prop_general_info::m_prop_type,
        "NumProps",& human_prop_general_info::num_props,
        "Props", &human_prop_general_info::props //Todo: Bind this type
    );
}

void Lua::BindCharDefHead(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<char_def_head>
    (
        "CharDefHead",
        "new", sol::no_constructor,
        "Name", &char_def_head::name,
        "LodName", &char_def_head::lod_name,
        //"BaseHeadInfo", &char_def_head::BaseHeadInfo,
        //"BaseHead", &char_def_head::BaseHead,
        //"LodMesh", &char_def_head::LODMesh,
        //"Rig", &char_def_head::rig, //Todo: Bind this
        "MorphMatSRID", &char_def_head::morph_mat_srid,
        "HeadMorph", &char_def_head::head_morph,
        "BaseHeadMorph", &char_def_head::base_head_morph,
        "NumSkinShaderParams", &char_def_head::num_skin_shader_params//,
        //"SkinShaderParams", sol::property([](char_def_head& Self) { return std::ref(Self.skin_shader_params); }), //3x5 float array //Todo: Bind this
    );
}

void Lua::BindFootGroundEffects(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<foot_ground_effects>
    (
        "FootGroundEffects",
        "new", sol::no_constructor,
        "Name", sol::property([](foot_ground_effects& Self) { return Globals::CharArrayToString(Self.name, 20); }),
        "WalkFoley", &foot_ground_effects::walk_foley,
        "RunFoley", &foot_ground_effects::run_foley,
        "JumpFoley", &foot_ground_effects::jump_foley,
        "LandFoley", &foot_ground_effects::land_foley//,
        //"Footstep", &foot_ground_effects::footstep,
        //"Jump", &foot_ground_effects:jump
    );
}

void Lua::BindHumanInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<HumanInfo>
    (
        "HumanInfo",
        "new", sol::no_constructor,
        "MaxHitPoints", &HumanInfo::max_hit_points,
        "MaxKnockdownHits", &HumanInfo::max_knockdown_hits,
        "MaxSpeed", &HumanInfo::max_speed,
        "DefaultEquipItem", &HumanInfo::default_equip_item,
        "DefaultLastEquipItem", &HumanInfo::default_last_equip_item,
        "Name", &HumanInfo::name,
        "NameCrc", &HumanInfo::name_crc,
        "ModelName", &HumanInfo::model_name,
        "AnimSetName", &HumanInfo::anim_set_name,
        "AnimSetNameCrc", &HumanInfo::anim_set_name_crc,
        "RigName", &HumanInfo::rig_name,
        "SRID", &HumanInfo::srid,
        "SlotID", &HumanInfo::slot_id,
        "DefaultHeightScale", &HumanInfo::default_height_scale,
        "HeightScaleVariation", &HumanInfo::height_scale_variation,
        "DefaultTeam", &HumanInfo::default_team,
        "HurtThreshold", &HumanInfo::hurt_threshold,
        "HomeDistrict", &HumanInfo::home_district,
        "AimErrorPercent", &HumanInfo::aim_error_pct,
        "FootEffects", &HumanInfo::foot_effects,
        "NumHeads", &HumanInfo::num_heads,
        "Heads", sol::property([](HumanInfo& Self) { return std::ref(Self.heads); }), //heads[4]
        //"VoicePersonas", &HumanInfo::voice_personas, //Todo: Bind this
        //"DefaultInventory", &HumanInfo::default_inventory, //farray<human_info_inventory_info, 15> //Todo: Bind this
        "NumGeneralProps", &HumanInfo::num_general_props,
        //"GeneralProps", &HumanInfo::general_props, //Todo: Bind this and the types it depends on.
        "LowerSpineBoneIndex", &HumanInfo::lower_spine_bone_index,
        "UpperSpineBoneIndex", &HumanInfo::upper_spine_bone_index,
        "PelvisBoneIndex", &HumanInfo::pelvis_bone_index,
        "HeadBoneIndex", &HumanInfo::head_bone_index,
        "NeckBoneIndex", &HumanInfo::neck_bone_index,
        "EyeLeftBoneIndex", &HumanInfo::eye_l_bone_index,
        "EyeRightBoneIndex", &HumanInfo::eye_r_bone_index,
        "CalfLeftBoneIndex", &HumanInfo::calf_l_bone_index,
        "CalfRightBoneIndex", &HumanInfo::calf_r_bone_index,
        "CameraBoneIndex", &HumanInfo::camera_bone_index,
        "DropCashMin", &HumanInfo::drop_cash_min,
        "DropCashMax", &HumanInfo::drop_cash_max,
        "LightEffectHandle", &HumanInfo::light_effect_handle,
        "LightTagNames", sol::property([](HumanInfo& Self) { return std::ref(Self.light_tag_names); }), //char*[2]
        "Flags", &HumanInfo::flags
    );
}