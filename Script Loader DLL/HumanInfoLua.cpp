#include "HumanInfoLua.h"
#include "Functions.h"

void Lua::BindHumanInfoFlags(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<human_info_flags>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Female", sol::property(itsy_bitsy::read<human_info_flags, 0>, itsy_bitsy::write<human_info_flags, 0>)); //int8 - 1
	Utype.set("Coin", sol::property(itsy_bitsy::read<human_info_flags, 1>, itsy_bitsy::write<human_info_flags, 1>)); //int8 - 1
	Utype.set("Preload", sol::property(itsy_bitsy::read<human_info_flags, 2>, itsy_bitsy::write<human_info_flags, 2>)); //int8 - 1
	Utype.set("Officer", sol::property(itsy_bitsy::read<human_info_flags, 3>, itsy_bitsy::write<human_info_flags, 3>)); //int8 - 1
	Utype.set("Unarmed", sol::property(itsy_bitsy::read<human_info_flags, 4>, itsy_bitsy::write<human_info_flags, 4>)); //int8 - 1
	Utype.set("VIP", sol::property(itsy_bitsy::read<human_info_flags, 5>, itsy_bitsy::write<human_info_flags, 5>)); //int8 - 1
	Utype.set("UseTechLevel", sol::property(itsy_bitsy::read<human_info_flags, 6>, itsy_bitsy::write<human_info_flags, 6>)); //int8 - 1
	Utype.set("Sniper", sol::property(itsy_bitsy::read<human_info_flags, 7>, itsy_bitsy::write<human_info_flags, 7>)); //int8 - 1
	Utype.set("EliteDodge", sol::property(itsy_bitsy::read<human_info_flags, 8>, itsy_bitsy::write<human_info_flags, 8>)); //int8 - 1
	Utype.set("RiotShield", sol::property(itsy_bitsy::read<human_info_flags, 9>, itsy_bitsy::write<human_info_flags, 9>)); //int8 - 1
	Utype.set("BodyArmor", sol::property(itsy_bitsy::read<human_info_flags, 10>, itsy_bitsy::write<human_info_flags, 10>)); //int8 - 1
	Utype.set("NonFlammable", sol::property(itsy_bitsy::read<human_info_flags, 11>, itsy_bitsy::write<human_info_flags, 11>)); //int8 - 1
	Utype.set("NoAttachingProjectiles", sol::property(itsy_bitsy::read<human_info_flags, 12>, itsy_bitsy::write<human_info_flags, 12>)); //int8 - 1
	Utype.set("GuerrillaTech", sol::property(itsy_bitsy::read<human_info_flags, 13>, itsy_bitsy::write<human_info_flags, 13>)); //int8 - 1
	Utype.set("GuerrillaRfc", sol::property(itsy_bitsy::read<human_info_flags, 14>, itsy_bitsy::write<human_info_flags, 14>)); //int8 - 1
	Utype.set("OldCoot", sol::property(itsy_bitsy::read<human_info_flags, 15>, itsy_bitsy::write<human_info_flags, 15>)); //int8 - 1
	Utype.set("Dan", sol::property(itsy_bitsy::read<human_info_flags, 16>, itsy_bitsy::write<human_info_flags, 16>)); //int8 - 1
	Utype.set("Jenkins", sol::property(itsy_bitsy::read<human_info_flags, 17>, itsy_bitsy::write<human_info_flags, 17>)); //int8 - 1*/
	Utype.set("DriverlessExit", &human_info_flags::driverless_exit_only); //bool*/
	RfgTable.set_usertype("HumanInfoFlags", Utype);
}

void Lua::BindHumanPropGeneralInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<human_prop_general_info>();
	Utype.set("new", sol::no_constructor);
	Utype.set("PropName", &human_prop_general_info::prop_name);
	Utype.set("AppearancePercent", &human_prop_general_info::appearance_percent);
	Utype.set("PropType", &human_prop_general_info::m_prop_type);
	Utype.set("NumProps",& human_prop_general_info::num_props);
	Utype.set("Props", &human_prop_general_info::props); //Todo: Bind this type
	RfgTable.set_usertype("HumanPropGeneralInfo", Utype);
}

void Lua::BindCharDefHead(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<char_def_head>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Name", &char_def_head::name);
	Utype.set("LodName", &char_def_head::lod_name);
	//Utype.set("BaseHeadInfo", &char_def_head::BaseHeadInfo);
	//Utype.set("BaseHead", &char_def_head::BaseHead);
	//Utype.set("LodMesh", &char_def_head::LODMesh);
	//Utype.set("Rig", &char_def_head::AnimRig);
	Utype.set("MorphMatSRID", &char_def_head::morph_mat_srid);
	Utype.set("HeadMorph", &char_def_head::head_morph);
	Utype.set("BaseHeadMorph", &char_def_head::base_head_morph);
	Utype.set("NumSkinShaderParams", &char_def_head::num_skin_shader_params);
	///Utype.set("SkinShaderParams", sol::property([](char_def_head& Self) { return std::ref(Self.skin_shader_params); })); //3x5 float array //Todo: Bind this
	RfgTable.set_usertype("CharDefHead", Utype);
}

void Lua::BindFootGroundEffects(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<foot_ground_effects>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Name", sol::property([](foot_ground_effects& Self) { return std::ref(Self.name); })); //char[20]
	Utype.set("WalkFoley", &foot_ground_effects::walk_foley);
	Utype.set("RunFoley", &foot_ground_effects::run_foley);
	Utype.set("JumpFoley", &foot_ground_effects::jump_foley);
	Utype.set("LandFoley", &foot_ground_effects::land_foley);
	//Utype.set("Footstep", );
	//Utype.set("Jump", );
	RfgTable.set_usertype("FootGroundEffects", Utype);
}

void Lua::BindHumanInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<HumanInfo>();
	Utype.set("new", sol::no_constructor);//("new", sol::constructors<Human(), Human(const Human&)>());
	Utype.set("MaxHitPoints", &HumanInfo::max_hit_points);
	Utype.set("MaxKnockdownHits", &HumanInfo::max_knockdown_hits);
	Utype.set("MaxSpeed", &HumanInfo::max_speed);
	Utype.set("DefaultEquipItem", &HumanInfo::default_equip_item);
	Utype.set("DefaultLastEquipItem", &HumanInfo::default_last_equip_item);
	Utype.set("Name", &HumanInfo::name);
	Utype.set("NameCrc", &HumanInfo::name_crc);
	Utype.set("ModelName", &HumanInfo::model_name);
	Utype.set("AnimSetName", &HumanInfo::anim_set_name);
	Utype.set("AnimSetNameCrc", &HumanInfo::anim_set_name_crc);
	Utype.set("RigName", &HumanInfo::rig_name);
	Utype.set("SRID", &HumanInfo::srid);
	Utype.set("SlotID", &HumanInfo::slot_id);
	Utype.set("DefaultHeightScale", &HumanInfo::default_height_scale);
	Utype.set("HeightScaleVariation", &HumanInfo::height_scale_variation);
	Utype.set("DefaultTeam", &HumanInfo::default_team);
	Utype.set("HurtThreshold", &HumanInfo::hurt_threshold);
	Utype.set("HomeDistrict", &HumanInfo::home_district);
	Utype.set("AimErrorPercent", &HumanInfo::aim_error_pct);
	Utype.set("FootEffects", &HumanInfo::foot_effects);
	Utype.set("NumHeads", &HumanInfo::num_heads);
	Utype.set("Heads", sol::property([](HumanInfo& Self) { return std::ref(Self.heads); })); //heads[4]
	//Utype.set("VoicePersonas", &HumanInfo::voice_personas); //Todo: Bind this
	///Utype.set("DefaultInventory", &HumanInfo::default_inventory); //farray<human_info_inventory_info, 15> //Todo: Bind this
	Utype.set("NumGeneralProps", &HumanInfo::num_general_props);
	//Utype.set("GeneralProps", &HumanInfo::general_props); //Todo: Bind this and the types it depends on.
	Utype.set("LowerSpineBoneIndex", &HumanInfo::lower_spine_bone_index);
	Utype.set("UpperSpineBoneIndex", &HumanInfo::upper_spine_bone_index);
	Utype.set("PelvisBoneIndex", &HumanInfo::pelvis_bone_index);
	Utype.set("HeadBoneIndex", &HumanInfo::head_bone_index);
	Utype.set("NeckBoneIndex", &HumanInfo::neck_bone_index);
	Utype.set("EyeLeftBoneIndex", &HumanInfo::eye_l_bone_index);
	Utype.set("EyeRightBoneIndex", &HumanInfo::eye_r_bone_index);
	Utype.set("CalfLeftBoneIndex", &HumanInfo::calf_l_bone_index);
	Utype.set("CalfRightBoneIndex", &HumanInfo::calf_r_bone_index);
	Utype.set("CameraBoneIndex", &HumanInfo::camera_bone_index);
	Utype.set("DropCashMin", &HumanInfo::drop_cash_min);
	Utype.set("DropCashMax", &HumanInfo::drop_cash_max);
	Utype.set("LightEffectHandle", &HumanInfo::light_effect_handle);
	Utype.set("LightTagNames", sol::property([](HumanInfo& Self) { return std::ref(Self.light_tag_names); })); //char*[2]
	Utype.set("Flags", &HumanInfo::flags);
	RfgTable.set_usertype("HumanInfo", Utype);
}