#include "WeaponInfoLua.h"
#include "Functions.h"

void Lua::BindFixedArrayWrapperWeaponInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<FixedArrayWrapper<weapon_info>>();
    Utype.set("new", sol::no_constructor);
    Utype.set("Size", &FixedArrayWrapper<weapon_info>::Size);
    Utype.set("Length", &FixedArrayWrapper<weapon_info>::Length);
    Utype.set("Capacity", &FixedArrayWrapper<weapon_info>::Capacity);
    Utype.set("Initialized", &FixedArrayWrapper<weapon_info>::Initialized);
    Utype.set(sol::meta_function::index, &FixedArrayWrapper<weapon_info>::operator[]);
    RfgTable.set_usertype("FixedArrayWrapperWeaponInfo", Utype);
}

void Lua::BindWeaponProjectileInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<weapon_projectile_info>();
    Utype.set("new", sol::constructors<weapon_projectile_info(), weapon_projectile_info(const weapon_projectile_info&)>());
    //Utype.set("ObjItemInfo", &weapon_projectile_info::obj_item_info); //Todo: item_info class, need to bind
    Utype.set("StartSpeed", &weapon_projectile_info::start_speed);
    Utype.set("MaxSpeed", &weapon_projectile_info::max_speed);
    Utype.set("Acceleration", &weapon_projectile_info::acceleration);
    Utype.set("FuseTime", &weapon_projectile_info::fuse_time);
    Utype.set("MaxThrowDist", &weapon_projectile_info::max_throw_dist);
    Utype.set("Gravity", &weapon_projectile_info::gravity);
    Utype.set("Sound", &weapon_projectile_info::sound);
    Utype.set("Effect1", &weapon_projectile_info::effect1);
    Utype.set("Effect2", &weapon_projectile_info::effect2);
    Utype.set("Effect3", &weapon_projectile_info::effect3);
    Utype.set("Effect4", &weapon_projectile_info::effect4);
    Utype.set("Flags", &weapon_projectile_info::flags);
    Utype.set("InaccurateFlight", &weapon_projectile_info::inaccurate_flight);
    Utype.set("TimeUntilPropelled", &weapon_projectile_info::time_until_propelled);
    Utype.set("TimeUntilPropExpire", &weapon_projectile_info::time_until_prop_expire);
    Utype.set("TimeUntilDrop", &weapon_projectile_info::time_until_drop);
    Utype.set("DamageEffect", &weapon_projectile_info::damage_effect);
    //Utype.set("HitCameraShake", &weapon_projectile_info::hit_camera_shake); //Todo: camera_shake class, need to bind
    RfgTable.set_usertype("WeaponProjectileInfo", Utype);
}

void Lua::BindDamageScalingInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<damage_scaling_info>();
    Utype.set("new", sol::constructors<damage_scaling_info(const damage_scaling_info&)>());
    Utype.set("ScaleValue", &damage_scaling_info::scale_value);
    Utype.set("Damage", sol::property([](damage_scaling_info& Self) { return std::ref(Self.damage); }));

    RfgTable.set_usertype("DamageScalingInfo", Utype);
}

void Lua::BindWeaponInfoFlags(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<weapon_info_flags>();
    Utype.set("new", sol::constructors<weapon_info_flags(const weapon_info_flags&)>());
    Utype.set("ArmorPiercing", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.armor_piercing; }, 
        [](weapon_info_flags& Self, bool Value) {Self.armor_piercing = Value; }));
    Utype.set("CanFineAim", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.can_fine_aim; },
        [](weapon_info_flags& Self, bool Value) {Self.can_fine_aim = Value; }));
    Utype.set("CanScope", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.can_scope; },
        [](weapon_info_flags& Self, bool Value) {Self.can_scope = Value; }));
    Utype.set("Shatter", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.shatter; },
        [](weapon_info_flags& Self, bool Value) {Self.shatter = Value; }));
    Utype.set("HeldInLeftHand", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.held_in_left_hand; },
        [](weapon_info_flags& Self, bool Value) {Self.held_in_left_hand = Value; }));
    Utype.set("DrawProjectileInOppositeHand", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.draw_proj_in_opposite_hand; },
        [](weapon_info_flags& Self, bool Value) {Self.draw_proj_in_opposite_hand = Value; }));
    Utype.set("SilentBullets", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.silent_bullets; },
        [](weapon_info_flags& Self, bool Value) {Self.silent_bullets = Value; }));
    Utype.set("PenetratingBullets", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.penetrating_bullets; },
        [](weapon_info_flags& Self, bool Value) {Self.penetrating_bullets = Value; }));
    Utype.set("NonInventory", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.non_inventory; },
        [](weapon_info_flags& Self, bool Value) {Self.non_inventory = Value; }));
    Utype.set("UseEvenSpread", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.use_even_spread; },
        [](weapon_info_flags& Self, bool Value) {Self.use_even_spread = Value; }));
    Utype.set("DisablePlayerCover", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.disable_player_cover; },
        [](weapon_info_flags& Self, bool Value) {Self.disable_player_cover = Value; }));
    Utype.set("MpSelectable", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.mp_selectable; },
        [](weapon_info_flags& Self, bool Value) {Self.mp_selectable = Value; }));
    Utype.set("IsObviousWeapon", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.is_obvious_weapon; },
        [](weapon_info_flags& Self, bool Value) {Self.is_obvious_weapon = Value; }));
    Utype.set("AutoAimCurvedTrail", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.auto_aim_curved_trail; },
        [](weapon_info_flags& Self, bool Value) {Self.auto_aim_curved_trail = Value; }));
    Utype.set("LoopingEffects", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.looping_effects; },
        [](weapon_info_flags& Self, bool Value) {Self.looping_effects = Value; }));
    Utype.set("NeverInCabinet", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.never_in_cabinet; },
        [](weapon_info_flags& Self, bool Value) {Self.never_in_cabinet = Value; }));
    Utype.set("UseSecondaryWeaponHeat", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.use_secondary_weapon_heat; },
        [](weapon_info_flags& Self, bool Value) {Self.use_secondary_weapon_heat = Value; }));
    Utype.set("DontDropOnDeath", sol::property(
        [](weapon_info_flags& Self) -> bool {return Self.dont_drop_on_death; },
        [](weapon_info_flags& Self, bool Value) {Self.dont_drop_on_death = Value; }));
    RfgTable.set_usertype("WeaponInfoFlags", Utype);
}

void Lua::BindWeaponInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<weapon_info>();
    Utype.set("new", sol::constructors<weapon_info(const weapon_info&)>()); //Todo: Add a constructor so people can edit copies
    Utype.set("Name", &weapon_info::name);
    Utype.set("NameCrc", &weapon_info::name_crc);
    Utype.set("UniqueId", &weapon_info::unique_id);
    Utype.set("Flags", &weapon_info::flags);
    Utype.set("WeaponClass", &weapon_info::weapon_class);
    //Utype.set("WeaponObjItemInfo", &weapon_info::weapon_obj_item_info); //Todo: item_info class, need to bind
    Utype.set("WeaponInvItemInfo", &weapon_info::weapon_inv_item_info);
    Utype.set("DefaultTeam", &weapon_info::default_team); //enum, already in core
    Utype.set("IconName", &weapon_info::icon_name);
    Utype.set("SmallIconName", &weapon_info::small_icon_name);
    Utype.set("ReticuleName", &weapon_info::reticule_name);
    Utype.set("FineAimReticuleName", &weapon_info::fine_aim_reticule_name);
    Utype.set("MpKillPhrase", &weapon_info::mp_kill_phrase);
    Utype.set("WeaponAnimGroup", &weapon_info::weapon_anim_group);
    Utype.set("MuzzleFlashEffect", &weapon_info::muzzle_flash_effect);
    Utype.set("MuzzleSmokeEffect", &weapon_info::muzzle_smoke_effect);
    Utype.set("SpecialHitEffect", &weapon_info::special_hit_effect);
    Utype.set("SpecialEffect", &weapon_info::special_effect);
    Utype.set("SecondarySpecialEffect", &weapon_info::secondary_special_effect);
    Utype.set("OverheatedEffect", &weapon_info::overheated_effect);
    Utype.set("TracerEffect", &weapon_info::tracer_effect);
    //Utype.set("FireCameraShake", &weapon_info::fire_camera_shake); //Todo: camera_shake class, need to bind
    Utype.set("FireCameraShakeIgnoreDisabled", &weapon_info::fire_camera_shake_ignore_disabled);
    //Utype.set("SecondaryCameraShake", &weapon_info::secondary_camera_shake); //Todo: camera_shake class, need to bind
    //Utype.set("PlayerHitCameraShake", &weapon_info::player_hit_camera_shake); //Todo: camera_shake class, need to bind
    Utype.set("AttachmentPoint", sol::property([](weapon_info& Self) { return Globals::CharArrayToString(Self.attachment_point, 32); }));
    Utype.set("FireSound", &weapon_info::fire_sound);
    Utype.set("SecondarySound", &weapon_info::secondary_sound);
    Utype.set("UpgradeSound", &weapon_info::upgrade_sound);
    Utype.set("ReloadSound", &weapon_info::reload_sound);
    Utype.set("ReloadSoundDelay", &weapon_info::reload_sound_delay);
    Utype.set("NoAmmoSound", &weapon_info::no_ammo_sound);
    Utype.set("SpecialSound", &weapon_info::special_sound);
    Utype.set("FlybySound", &weapon_info::flyby_sound);
    Utype.set("NumWeaponPersonas", &weapon_info::num_weapon_personas);
    Utype.set("NpcFireSounds", sol::property([](weapon_info& Self) { return std::ref(Self.npc_fire_sounds); }));
    Utype.set("MaxRange", &weapon_info::max_range);
    Utype.set("RedRange", &weapon_info::red_range);
    Utype.set("MaxEngagementDist", &weapon_info::max_engagement_dist);
    Utype.set("MinEngagementDist", &weapon_info::min_engagement_dist);
    Utype.set("MaxAiPenetratingDist", &weapon_info::max_ai_penetrating_dist);
    Utype.set("NpcFiringPattern", &weapon_info::npc_firing_pattern);
    Utype.set("NpcAimDriftProfile", &weapon_info::npc_aim_drift_profile);
    Utype.set("TriggerType", &weapon_info::trigger_type);
    Utype.set("AmmoType", &weapon_info::ammo_type);
    Utype.set("MagazineSize", &weapon_info::magazine_size);
    Utype.set("MagazineStartNum", &weapon_info::magazine_start_num);
    Utype.set("MaxRounds", &weapon_info::max_rounds);
    Utype.set("MaxRoundsUpgrade", &weapon_info::max_rounds_upgrade);
    Utype.set("AmmoBoxRestock", &weapon_info::ammo_box_restock);
    Utype.set("ToMinSpread", &weapon_info::to_min_spread);
    Utype.set("ToMaxSpread", &weapon_info::to_max_spread);
    Utype.set("MeleeGroupIndex", sol::property(
        [](weapon_info& Self) -> int {return Self.melee_group_index; },
        [](weapon_info& Self, int Value) {Self.melee_group_index = Value; }));
    Utype.set("BulletGroupIndex", sol::property(
        [](weapon_info& Self) -> int {return Self.bullet_group_index; },
        [](weapon_info& Self, int Value) {Self.bullet_group_index = Value; }));
    Utype.set("TracerFrequency", sol::property(
        [](weapon_info& Self) -> int {return Self.tracer_frequency; },
        [](weapon_info& Self, int Value) {Self.tracer_frequency = Value; }));
    Utype.set("ShotsPerRound", sol::property(
        [](weapon_info& Self) -> int {return Self.shots_per_round; },
        [](weapon_info& Self, int Value) {Self.shots_per_round = Value; }));
    Utype.set("FiringSoundRadius", &weapon_info::firing_sound_radius);
    Utype.set("NpcRefireDelay", &weapon_info::npc_refire_delay);
    Utype.set("DefaultRefireDelay", &weapon_info::default_refire_delay);
    Utype.set("PrefireDelay", &weapon_info::prefire_delay);
    Utype.set("DefaultReloadDelay", &weapon_info::default_reload_delay);
    Utype.set("LowScaleDamage", &weapon_info::low_scale_damage);
    Utype.set("HighScaleDamage", &weapon_info::high_scale_damage);
    Utype.set("PlayerExplosionInfo", &weapon_info::m_explosion_info);
    Utype.set("AiExplosionInfo", &weapon_info::m_ai_explosion_info);
    Utype.set("FireConeDot", &weapon_info::fire_cone_dot);
    Utype.set("EvenSpreadAccuracyDot", &weapon_info::even_spread_accuracy_dot);
    Utype.set("MaxSpread", &weapon_info::max_spread);
    Utype.set("MinSpread", &weapon_info::min_spread);
    Utype.set("FineAimMaxSpread", &weapon_info::fine_aim_max_spread);
    Utype.set("FineAimMinSpread", &weapon_info::fine_aim_min_spread);
    Utype.set("NpcMaxSpread", &weapon_info::npc_max_spread);
    Utype.set("NpcMinSpread", &weapon_info::npc_min_spread);
    Utype.set("SpreadMultiplierRun", &weapon_info::spread_multiplier_run);
    Utype.set("RagdollForceShoot", &weapon_info::ragdoll_force_shoot);
    Utype.set("RagdollChance", &weapon_info::ragdoll_chance);
    Utype.set("RecoilCameraKick", &weapon_info::recoil_camera_kick);
    Utype.set("RecoilImpulse", &weapon_info::recoil_impulse);
    Utype.set("OutOfAmmoReloadDelay", &weapon_info::out_of_ammo_reload_delay);
    Utype.set("OverheatCoolDownTime", &weapon_info::overheat_cool_down_time);
    Utype.set("OverheatPercentPerShot", &weapon_info::overheat_percent_per_shot);
    Utype.set("DroppedAmmoScale", &weapon_info::dropped_ammo_scale);
    Utype.set("BulletHoleScale", &weapon_info::bullet_hole_scale);
    Utype.set("HeadshotMultiplier", &weapon_info::headshot_multiplier);
    Utype.set("ZoomMagnification", &weapon_info::zoom_magnification);
    Utype.set("AutoaimOverride", &weapon_info::autoaim_override);
    Utype.set("NpcAutoaim", &weapon_info::npc_autoaim);
    Utype.set("AimAssist", &weapon_info::aim_assist);
    Utype.set("PlayerMoveSpeedMultiplier", &weapon_info::player_move_speed_multiplier);
    Utype.set("NpcMoveSpeedMultiplier", &weapon_info::npc_move_speed_multiplier);
    Utype.set("AlertMultiplier", &weapon_info::alert_multiplier);
    Utype.set("ProjectileInfo", &weapon_info::projectile_info); //Todo: weapon_projectile_info class, need to bind
    Utype.set("StandingPrimaryMeleeAttack", &weapon_info::standing_primary_melee_attack);
    Utype.set("StandingSecondaryMeleeAttack", &weapon_info::standing_secondary_melee_attack);
    Utype.set("StandingTertiaryMeleeAttack", &weapon_info::standing_tertiary_melee_attack);
    Utype.set("CrouchingPrimaryMeleeAttack", &weapon_info::crouching_primary_melee_attack);
    Utype.set("CrouchingSecondaryMeleeAttack", &weapon_info::crouching_secondary_melee_attack);
    Utype.set("CrouchingTertiaryMeleeAttack", &weapon_info::crouching_tertiary_melee_attack);
    RfgTable.set_usertype("WeaponInfo", Utype);
}