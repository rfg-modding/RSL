#include "HumanFlagsLua.h"
#include "Functions.h"

void Lua::BindHumanFlags(sol::state & LuaState)
{
#pragma warning(push)
#pragma warning(disable : 4172)
    //Note: This looks fucking atrocious
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<HumanFlags>
    (
        "HumanFlags",
        "new", sol::constructors<HumanFlags(), HumanFlags(const HumanFlags&)>(),
        "BoredHeadtrackDisabled", sol::property([](HumanFlags& Self) -> const bool& {return Self.bored_headtrack_disabled; }, [](HumanFlags& Self, bool Value) {Self.bored_headtrack_disabled = Value; }), //bool - 1
        "Hidden", sol::property([](HumanFlags& Self) -> const bool& {return Self.hidden; }, [](HumanFlags& Self, bool Value) {Self.hidden = Value; }), //bool - 1
        "CapSpeed", sol::property([](HumanFlags& Self) -> const bool& {return Self.cap_speed; }, [](HumanFlags& Self, bool Value) {Self.cap_speed = Value; }), //bool - 1
        "WasRendered", sol::property([](HumanFlags& Self) -> const bool& {return Self.was_rendered; }, [](HumanFlags& Self, bool Value) {Self.was_rendered = Value; }), //bool - 1
        "LockedController", sol::property([](HumanFlags& Self) -> const bool& {return Self.locked_controller; }, [](HumanFlags& Self, bool Value) {Self.locked_controller = Value; }), //bool - 1
        "Invulnerable", sol::property([](HumanFlags& Self) -> const bool& {return Self.invulnerable; }, [](HumanFlags& Self, bool Value) {Self.invulnerable = Value; }), //bool - 1
        "MissionInvulnerable", sol::property([](HumanFlags& Self) -> const bool& {return Self.mission_invulnerable; }, [](HumanFlags& Self, bool Value) {Self.mission_invulnerable = Value; }), //bool - 1
        "NoDamage", sol::property([](HumanFlags& Self) -> const bool& {return Self.no_damage; }, [](HumanFlags& Self, bool Value) {Self.no_damage = Value; }), //bool - 1
        "ActivityEngage", sol::property([](HumanFlags& Self) -> const bool& {return Self.activity_engage; }, [](HumanFlags& Self, bool Value) {Self.activity_engage = Value; }), //bool - 1
        "ConsideredArmed", sol::property([](HumanFlags& Self) -> const bool& {return Self.considered_armed; }, [](HumanFlags& Self, bool Value) {Self.considered_armed = Value; }), //bool - 1
        "RiotShield", sol::property([](HumanFlags& Self) -> const bool& {return Self.riot_shield; }, [](HumanFlags& Self, bool Value) {Self.riot_shield = Value; }), //bool - 1
        "SafehouseVIP", sol::property([](HumanFlags& Self) -> const bool& {return Self.safehouse_vip; }, [](HumanFlags& Self, bool Value) {Self.safehouse_vip = Value; }), //bool - 1
        "RadioOperator", sol::property([](HumanFlags& Self) -> const bool& {return Self.radio_operator; }, [](HumanFlags& Self, bool Value) {Self.radio_operator = Value; }), //bool - 1
        "ActivityRaidRequired", sol::property([](HumanFlags& Self) -> const bool&{return Self.activity_raid_required; }, [](HumanFlags& Self, bool Value) {Self.activity_raid_required = Value; }), //bool - 1
        "ActivityRaidOptional", sol::property([](HumanFlags& Self) -> const bool&{return Self.activity_raid_optional; }, [](HumanFlags& Self, bool Value) {Self.activity_raid_optional = Value; }), //bool - 1
        "ActivityHouseArrestHostage", sol::property([](HumanFlags& Self) -> const bool& {return Self.activity_ha_hostage; }, [](HumanFlags& Self, bool Value) {Self.activity_ha_hostage = Value; }), //bool - 1
        "RaidIntroductionLines", sol::property([](HumanFlags& Self) -> const bool& {return Self.raid_introduction_lines; }, [](HumanFlags& Self, bool Value) {Self.raid_introduction_lines = Value; }), //bool - 1
        "MinerPersonaLines", sol::property([](HumanFlags& Self) -> const bool& {return Self.miner_persona_lines; }, [](HumanFlags& Self, bool Value) {Self.miner_persona_lines = Value; }), //bool - 1
        "DamagedByPlayer", sol::property([](HumanFlags& Self) -> const bool& {return Self.damaged_by_player; }, [](HumanFlags& Self, bool Value) {Self.damaged_by_player = Value; }), //bool - 1
        "AiIgnore", sol::property([](HumanFlags& Self) -> const bool& {return Self.ai_ignore; }, [](HumanFlags& Self, bool Value) {Self.ai_ignore = Value; }), //bool - 1
        "CastsShadows", sol::property([](HumanFlags& Self) -> const bool& {return Self.casts_shadows; }, [](HumanFlags& Self, bool Value) {Self.casts_shadows = Value; }), //bool - 1
        "CastsDropShadows", sol::property([](HumanFlags& Self) -> const bool& {return Self.casts_drop_shadows; }, [](HumanFlags& Self, bool Value) {Self.casts_drop_shadows = Value; }), //bool - 1
        "IsTurning", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_turning; }, [](HumanFlags& Self, bool Value) {Self.is_turning = Value; }), //bool - 1 
        "IsFalling", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_falling; }, [](HumanFlags& Self, bool Value) {Self.is_falling = Value; }), //bool - 1 
        "DontDeformBones", sol::property([](HumanFlags& Self) -> const bool& {return Self.dont_deform_bones; }, [](HumanFlags& Self, bool Value) {Self.dont_deform_bones = Value; }), //bool - 1 
        "DontLodBones", sol::property([](HumanFlags& Self) -> const bool& {return Self.dont_lod_bones; }, [](HumanFlags& Self, bool Value) {Self.dont_lod_bones = Value; }), //bool - 1 
        "PlayingEquipAnim", sol::property([](HumanFlags& Self) -> const bool& {return Self.playing_equip_anim; }, [](HumanFlags& Self, bool Value) {Self.playing_equip_anim = Value; }), //bool - 1 
        "PlayingUnequipAnim", sol::property([](HumanFlags& Self) -> const bool& {return Self.playing_unequip_anim; }, [](HumanFlags& Self, bool Value) {Self.playing_unequip_anim = Value; }), //bool - 1 
        "DoInstantEquip", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_instant_equip; }, [](HumanFlags& Self, bool Value) {Self.do_instant_equip = Value; }), //bool - 1 
        "AnimDirectBlend", sol::property([](HumanFlags& Self) -> const bool& {return Self.anim_direct_blend; }, [](HumanFlags& Self, bool Value) {Self.anim_direct_blend = Value; }), //bool - 1 
        "StartJump", sol::property([](HumanFlags& Self) -> const bool&{return Self.start_jump; }, [](HumanFlags& Self, bool Value) {Self.start_jump = Value; }), //bool - 1 
        "SuperJump", sol::property([](HumanFlags& Self) -> const bool&{return Self.super_jump; }, [](HumanFlags& Self, bool Value) {Self.super_jump = Value; }), //bool - 1 
        "ProcessedThisFrame", sol::property([](HumanFlags& Self) -> const bool&{return Self.processed_this_frame; }, [](HumanFlags& Self, bool Value) {Self.processed_this_frame = Value; }), //bool - 1 
        "SilentVehicleStart", sol::property([](HumanFlags& Self) -> const bool&{return Self.silent_vehicle_start; }, [](HumanFlags& Self, bool Value) {Self.silent_vehicle_start = Value; }), //bool - 1 
        "SupressFleeOnVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.suppress_flee_on_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.suppress_flee_on_vehicle_exit = Value; }), //bool - 1 
        "DeathFunctionDone", sol::property([](HumanFlags& Self) -> const bool& {return Self.death_func_done; }, [](HumanFlags& Self, bool Value) {Self.death_func_done = Value; }), //bool - 1 
        "FadingIn", sol::property([](HumanFlags& Self) -> const bool& {return Self.fading_in; }, [](HumanFlags& Self, bool Value) {Self.fading_in = Value; }), //bool - 1 
        "FadingOut", sol::property([](HumanFlags& Self) -> const bool& {return Self.fading_out; }, [](HumanFlags& Self, bool Value) {Self.fading_out = Value; }), //bool - 1 
        "FadingOutFromNano", sol::property([](HumanFlags& Self) -> const bool& {return Self.fading_out_from_nano; }, [](HumanFlags& Self, bool Value) {Self.fading_out_from_nano = Value; }), //bool - 1 
        "IsNanoEffectCurrentlyApplied", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_nano_effect_currently_applied; }, [](HumanFlags& Self, bool Value) {Self.is_nano_effect_currently_applied = Value; }), //bool - 1 
        "OnFire", sol::property([](HumanFlags& Self) -> const bool& {return Self.on_fire; }, [](HumanFlags& Self, bool Value) {Self.on_fire = Value; }), //bool - 1 
        "DroppedCash", sol::property([](HumanFlags& Self) -> const bool& {return Self.dropped_cash; }, [](HumanFlags& Self, bool Value) {Self.dropped_cash = Value; }), //bool - 1 
        "OnMover", sol::property([](HumanFlags& Self) -> const bool& {return Self.on_mover; }, [](HumanFlags& Self, bool Value) {Self.on_mover = Value; }), //bool - 1 
        "RecalculateAtNode", sol::property([](HumanFlags& Self) -> const bool& {return Self.recalculate_at_node; }, [](HumanFlags& Self, bool Value) {Self.recalculate_at_node = Value; }), //bool - 1 
        "SpinebendingDone", sol::property([](HumanFlags& Self) -> const bool& {return Self.spinebending_done; }, [](HumanFlags& Self, bool Value) {Self.spinebending_done = Value; }), //bool - 1 
        "LastDestinationInRepulsor", sol::property([](HumanFlags& Self) -> const bool& {return Self.last_dest_in_repulsor; }, [](HumanFlags& Self, bool Value) {Self.last_dest_in_repulsor = Value; }), //bool - 1 
        "JumpingFromBuilding", sol::property([](HumanFlags& Self) -> const bool& {return Self.jumping_from_building; }, [](HumanFlags& Self, bool Value) {Self.jumping_from_building = Value; }), //bool - 1 
        "IsOnLadder", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_on_ladder; }, [](HumanFlags& Self, bool Value) {Self.is_on_ladder = Value; }), //bool - 1 
        "LadderForceSlide", sol::property([](HumanFlags& Self) -> const bool& {return Self.ladder_force_slide; }, [](HumanFlags& Self, bool Value) {Self.ladder_force_slide = Value; }), //bool - 1 
        "LadderForceExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.ladder_force_exit; }, [](HumanFlags& Self, bool Value) {Self.ladder_force_exit = Value; }), //bool - 1 
        "LadderReEquipWeapon", sol::property([](HumanFlags& Self) -> const bool& {return Self.ladder_reequip_weapon; }, [](HumanFlags& Self, bool Value) {Self.ladder_reequip_weapon = Value; }), //bool - 1 
        "AllowFlyingEquips", sol::property([](HumanFlags& Self) -> const bool& {return Self.allow_flying_equips; }, [](HumanFlags& Self, bool Value) {Self.allow_flying_equips = Value; }), //bool - 1 
        "CorpseSpotted", sol::property([](HumanFlags& Self) -> const bool& {return Self.corpse_spotted; }, [](HumanFlags& Self, bool Value) {Self.corpse_spotted = Value; }), //bool - 1 
        "CorpseSpottedByEnemy", sol::property([](HumanFlags& Self) -> const bool& {return Self.corpse_spotted_by_enemy; }, [](HumanFlags& Self, bool Value) {Self.corpse_spotted_by_enemy = Value; }), //bool - 1 
        "DeathReported", sol::property([](HumanFlags& Self) -> const bool& {return Self.death_reported; }, [](HumanFlags& Self, bool Value) {Self.death_reported = Value; }), //bool - 1 
        "RaidDeathAck", sol::property([](HumanFlags& Self) -> const bool& {return Self.raid_death_ack; }, [](HumanFlags& Self, bool Value) {Self.raid_death_ack = Value; }), //bool - 1 
        "AnchorOrient", sol::property([](HumanFlags& Self) -> const bool& {return Self.anchor_orient; }, [](HumanFlags& Self, bool Value) {Self.anchor_orient = Value; }), //bool - 1 
        "BonesTransformedThisFrame", sol::property([](HumanFlags& Self) -> const bool& {return Self.bones_transformed_this_frame; }, [](HumanFlags& Self, bool Value) {Self.bones_transformed_this_frame = Value; }), //bool - 1 
        "UseCurrentVelocity", sol::property([](HumanFlags& Self) -> const bool& {return Self.use_current_velocity; }, [](HumanFlags& Self, bool Value) {Self.use_current_velocity = Value; }), //bool - 1 
        "UseAsFinalVelocity", sol::property([](HumanFlags& Self) -> const bool& {return Self.use_as_final_velocity; }, [](HumanFlags& Self, bool Value) {Self.use_as_final_velocity = Value; }), //bool - 1 
        "AimAtPos", sol::property([](HumanFlags& Self) -> const bool& {return Self.aim_at_pos; }, [](HumanFlags& Self, bool Value) {Self.aim_at_pos = Value; }), //bool - 1 
        "BlockForcedMovement", sol::property([](HumanFlags& Self) -> const bool& {return Self.block_forced_movement; }, [](HumanFlags& Self, bool Value) {Self.block_forced_movement = Value; }), //bool - 1 
        "CancellingMeleeAttack", sol::property([](HumanFlags& Self) -> const bool& {return Self.cancelling_melee_attack; }, [](HumanFlags& Self, bool Value) {Self.cancelling_melee_attack = Value; }), //bool - 1 
        "DoContinuousMeleeDamage", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_continuous_melee_damage; }, [](HumanFlags& Self, bool Value) {Self.do_continuous_melee_damage = Value; }), //bool - 1 
        "InAirMelee", sol::property([](HumanFlags& Self) -> const bool& {return Self.in_air_melee; }, [](HumanFlags& Self, bool Value) {Self.in_air_melee = Value; }), //bool - 1 
        "CantHitWithMelee", sol::property([](HumanFlags& Self) -> const bool& {return Self.cant_hit_with_melee; }, [](HumanFlags& Self, bool Value) {Self.cant_hit_with_melee = Value; }), //bool - 1 
        "InvulnerableToDebris", sol::property([](HumanFlags& Self) -> const bool& {return Self.invulnerable_to_debris; }, [](HumanFlags& Self, bool Value) {Self.invulnerable_to_debris = Value; }), //bool - 1 
        "OverrideDefaultAnimState", sol::property([](HumanFlags& Self) -> const bool& {return Self.override_default_fire_anim; }, [](HumanFlags& Self, bool Value) {Self.override_default_fire_anim = Value; }), //bool - 1 
        "OverrideDefaultFireAnim", sol::property([](HumanFlags& Self) -> const bool& {return Self.override_default_fire_anim; }, [](HumanFlags& Self, bool Value) {Self.override_default_fire_anim = Value; }), //bool - 1 
        "MovingAndTransitioningStates", sol::property([](HumanFlags& Self) -> const bool& {return Self.moving_and_transitioning_states; }, [](HumanFlags& Self, bool Value) {Self.moving_and_transitioning_states = Value; }), //bool - 1 
        "CheckForCover", sol::property([](HumanFlags& Self) -> const bool& {return Self.check_for_cover; }, [](HumanFlags& Self, bool Value) {Self.check_for_cover = Value; }), //bool - 1 
        "JumpTakeOff", sol::property([](HumanFlags& Self) -> const bool& {return Self.jump_take_off; }, [](HumanFlags& Self, bool Value) {Self.jump_take_off = Value; }), //bool - 1 
        "RotateInternalHeadingUpdated", sol::property([](HumanFlags& Self) -> const bool& {return Self.rotate_internal_heading_updated; }, [](HumanFlags& Self, bool Value) {Self.rotate_internal_heading_updated = Value; }), //bool - 1 
        "CrouchCover", sol::property([](HumanFlags& Self) -> const bool& {return Self.crouch_cover; }, [](HumanFlags& Self, bool Value) {Self.crouch_cover = Value; }), //bool - 1 
        "CoverCrouchHighOnly", sol::property([](HumanFlags& Self) -> const bool& {return Self.cover_crouch_high_only; }, [](HumanFlags& Self, bool Value) {Self.cover_crouch_high_only = Value; }), //bool - 1 
        "CoverCrouchNoLean", sol::property([](HumanFlags& Self) -> const bool& {return Self.cover_crouch_no_lean; }, [](HumanFlags& Self, bool Value) {Self.cover_crouch_no_lean = Value; }), //bool - 1 
        "SideFiring", sol::property([](HumanFlags& Self) -> const bool& {return Self.side_firing; }, [](HumanFlags& Self, bool Value) {Self.side_firing = Value; }), //bool - 1 
        "SideFiringWalkBack", sol::property([](HumanFlags& Self) -> const bool& {return Self.side_firing_walk_back; }, [](HumanFlags& Self, bool Value) {Self.side_firing_walk_back = Value; }), //bool - 1 
        "RagdollOnImpactAllCollisions", sol::property([](HumanFlags& Self) -> const bool& {return Self.ragdoll_on_impact_all_collisions; }, [](HumanFlags& Self, bool Value) {Self.ragdoll_on_impact_all_collisions = Value; }), //bool - 1 
        "RagdollOnImpactUseRagdollPos", sol::property([](HumanFlags& Self) -> const bool& {return Self.ragdoll_on_impact_use_ragdoll_pos; }, [](HumanFlags& Self, bool Value) {Self.ragdoll_on_impact_use_ragdoll_pos = Value; }), //bool - 1 
        "DiveCapsule", sol::property([](HumanFlags& Self) -> const bool& {return Self.dive_capsule; }, [](HumanFlags& Self, bool Value) {Self.dive_capsule = Value; }), //bool - 1 
        "MaintainAmbientProps", sol::property([](HumanFlags& Self) -> const bool& {return Self.maintain_ambient_props; }, [](HumanFlags& Self, bool Value) {Self.maintain_ambient_props = Value; }), //bool - 1 
        "LeaningDisabled", sol::property([](HumanFlags& Self) -> const bool& {return Self.leaning_disabled; }, [](HumanFlags& Self, bool Value) {Self.leaning_disabled = Value; }), //bool - 1 
        "OverrideSteeringHeadingOffset", sol::property([](HumanFlags& Self) -> const bool& {return Self.override_steering_heading_offset; }, [](HumanFlags& Self, bool Value) {Self.override_steering_heading_offset = Value; }), //bool - 1 
        "PushesOtherHumans", sol::property([](HumanFlags& Self) -> const bool& {return Self.pushes_other_humans; }, [](HumanFlags& Self, bool Value) {Self.pushes_other_humans = Value; }), //bool - 1 
        "PushesDebrisScripted", sol::property([](HumanFlags& Self) -> const bool& {return Self.pushes_debris_scripted; }, [](HumanFlags& Self, bool Value) {Self.pushes_debris_scripted = Value; }), //bool - 1 
        "AllowSteepSlopes", sol::property([](HumanFlags& Self) -> const bool& {return Self.allow_steep_slopes; }, [](HumanFlags& Self, bool Value) {Self.allow_steep_slopes = Value; }), //bool - 1 
        "ExternalForceApplied", sol::property([](HumanFlags& Self) -> const bool& {return Self.external_force_applied; }, [](HumanFlags& Self, bool Value) {Self.external_force_applied = Value; }), //bool - 1 
        "RagdollShot", sol::property([](HumanFlags& Self) -> const bool& {return Self.ragdoll_shot; }, [](HumanFlags& Self, bool Value) {Self.ragdoll_shot = Value; }), //bool - 1 
        "SavedPushesDebrisScripted", sol::property([](HumanFlags& Self) -> const bool& {return Self.saved_pushes_debris_scripted; }, [](HumanFlags& Self, bool Value) {Self.saved_pushes_debris_scripted = Value; }), //bool - 1 
        "FilterHandleValid", sol::property([](HumanFlags& Self) -> const bool& {return Self.filter_handle_valid; }, [](HumanFlags& Self, bool Value) {Self.filter_handle_valid = Value; }), //bool - 1 
        "JustGotUpFromRagdoll", sol::property([](HumanFlags& Self) -> const bool& {return Self.just_got_up_from_ragdoll; }, [](HumanFlags& Self, bool Value) {Self.just_got_up_from_ragdoll = Value; }), //bool - 1 
        "DisablePathSmoothingForRequest", sol::property([](HumanFlags& Self) -> const bool& {return Self.disable_path_smoothing_for_request; }, [](HumanFlags& Self, bool Value) {Self.disable_path_smoothing_for_request = Value; }), //bool - 1 
        "DisableAllPathSmoothing", sol::property([](HumanFlags& Self) -> const bool& {return Self.disable_all_path_smoothing; }, [](HumanFlags& Self, bool Value) {Self.disable_all_path_smoothing = Value; }), //bool - 1 
        "InFetalPosition", sol::property([](HumanFlags& Self) -> const bool& {return Self.in_fetal_position; }, [](HumanFlags& Self, bool Value) {Self.in_fetal_position = Value; }), //bool - 1 
        "DisallowVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.disallow_vehicle_exit = Value; }), //bool - 1 
        "LimitedVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.limited_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.limited_vehicle_exit = Value; }), //bool - 1 
        "DriverlessExitOnly", sol::property([](HumanFlags& Self) -> const bool& {return Self.driverless_exit_only; }, [](HumanFlags& Self, bool Value) {Self.driverless_exit_only = Value; }), //bool - 1 
        "StuckInVehicle", sol::property([](HumanFlags& Self) -> const bool& {return Self.stuck_in_vehicle; }, [](HumanFlags& Self, bool Value) {Self.stuck_in_vehicle = Value; }), //bool - 1 
        "ConvoyVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.convoy_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.convoy_vehicle_exit = Value; }), //bool - 1 
        "DisallowVehicleEntry", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_vehicle_entry; }, [](HumanFlags& Self, bool Value) {Self.disallow_vehicle_entry = Value; }), //bool - 1 
        "DisallowVehicleDrive", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_vehicle_drive; }, [](HumanFlags& Self, bool Value) {Self.disallow_vehicle_drive = Value; }), //bool - 1 
        "AmbientEDF", sol::property([](HumanFlags& Self) -> const bool& {return Self.ambient_edf; }, [](HumanFlags& Self, bool Value) {Self.ambient_edf = Value; }), //bool - 1 
        "BashedCharacterController", sol::property([](HumanFlags& Self) -> const bool& {return Self.bashed_character_controller; }, [](HumanFlags& Self, bool Value) {Self.bashed_character_controller = Value; }), //bool - 1 
        "HeadLoaded", sol::property([](HumanFlags& Self) -> const bool& {return Self.head_loaded; }, [](HumanFlags& Self, bool Value) {Self.head_loaded = Value; }), //bool - 1 
        "LodHeadLoaded", sol::property([](HumanFlags& Self) -> const bool& {return Self.lod_head_loaded; }, [](HumanFlags& Self, bool Value) {Self.lod_head_loaded = Value; }), //bool - 1 
        "InVehicleInvisible", sol::property([](HumanFlags& Self) -> const bool& {return Self.in_vehicle_invisible; }, [](HumanFlags& Self, bool Value) {Self.in_vehicle_invisible = Value; }), //bool - 1 
        "HighPriorityTarget", sol::property([](HumanFlags& Self) -> const bool& {return Self.high_priority_target; }, [](HumanFlags& Self, bool Value) {Self.high_priority_target = Value; }), //bool - 1 
        "HealthChangeWasNegative", sol::property([](HumanFlags& Self) -> const bool& {return Self.health_change_was_negative; }, [](HumanFlags& Self, bool Value) {Self.health_change_was_negative = Value; }), //bool - 1 
        "VoiceLinePlay2D", sol::property([](HumanFlags& Self) -> const bool& {return Self.voice_line_play_2d; }, [](HumanFlags& Self, bool Value) {Self.voice_line_play_2d = Value; }), //bool - 1 
        "VoiceLinePainOnly", sol::property([](HumanFlags& Self) -> const bool& {return Self.voice_line_pain_only; }, [](HumanFlags& Self, bool Value) {Self.voice_line_pain_only = Value; }), //bool - 1 
        "KilledByKillzone", sol::property([](HumanFlags& Self) -> const bool& {return Self.killed_by_killzone; }, [](HumanFlags& Self, bool Value) {Self.killed_by_killzone = Value; }), //bool - 1 
        "FirstTimeStreamed", sol::property([](HumanFlags& Self) -> const bool& {return Self.first_time_streamed; }, [](HumanFlags& Self, bool Value) {Self.first_time_streamed = Value; }), //bool - 1 
        "Tired", sol::property([](HumanFlags& Self) -> const bool& {return Self.tired; }, [](HumanFlags& Self, bool Value) {Self.tired = Value; }), //bool - 1 
        "UseBigsteps", sol::property([](HumanFlags& Self) -> const bool& {return Self.use_bigsteps; }, [](HumanFlags& Self, bool Value) {Self.use_bigsteps = Value; }), //bool - 1 
        "Stuck", sol::property([](HumanFlags& Self) -> const bool& {return Self.stuck; }, [](HumanFlags& Self, bool Value) {Self.stuck = Value; }), //bool - 1 
        "LastPfFailed", sol::property([](HumanFlags& Self) -> const bool& {return Self.last_pf_failed; }, [](HumanFlags& Self, bool Value) {Self.last_pf_failed = Value; }), //bool - 1 
        "ExtendedStuck", sol::property([](HumanFlags& Self) -> const bool& {return Self.extended_stuck; }, [](HumanFlags& Self, bool Value) {Self.extended_stuck = Value; }), //bool - 1 
        "XrayVisible", sol::property([](HumanFlags& Self) -> const bool& {return Self.xray_visible; }, [](HumanFlags& Self, bool Value) {Self.xray_visible = Value; }), //bool - 1 
        "WasGibbed", sol::property([](HumanFlags& Self) -> const bool& {return Self.was_gibbed; }, [](HumanFlags& Self, bool Value) {Self.was_gibbed = Value; }), //bool - 1 
        "PreventRagdollSfx", sol::property([](HumanFlags& Self) -> const bool& {return Self.prevent_ragdoll_sfx; }, [](HumanFlags& Self, bool Value) {Self.prevent_ragdoll_sfx = Value; }), //bool - 1 
        "AlwaysShowOnMinimap", sol::property([](HumanFlags& Self) -> const bool& {return Self.always_show_on_minimap; }, [](HumanFlags& Self, bool Value) {Self.always_show_on_minimap = Value; }), //bool - 1 
        "UsedDeathBuffer", sol::property([](HumanFlags& Self) -> const bool& {return Self.used_death_buffer; }, [](HumanFlags& Self, bool Value) {Self.used_death_buffer = Value; }), //bool - 1 
        "DoNotConvertToGuerrilla", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_not_convert_to_guerrilla; }, [](HumanFlags& Self, bool Value) {Self.do_not_convert_to_guerrilla = Value; }), //bool - 1 
        "DoNotPlayAmbientOrGreetLines", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_not_play_ambient_or_greet_lines; }, [](HumanFlags& Self, bool Value) {Self.do_not_play_ambient_or_greet_lines = Value; }), //bool - 1 
        "DisallowFlinchesAndRagdolls", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_flinches_and_ragdolls; }, [](HumanFlags& Self, bool Value) {Self.disallow_flinches_and_ragdolls = Value; }), //bool - 1 
        "OnlyUseActionNodes", sol::property([](HumanFlags& Self) -> const bool& {return Self.only_use_action_nodes; }, [](HumanFlags& Self, bool Value) {Self.only_use_action_nodes = Value; }), //bool - 1 
        "ComplainWhenShot", sol::property([](HumanFlags& Self) -> const bool& {return Self.complain_when_shot; }, [](HumanFlags& Self, bool Value) {Self.complain_when_shot = Value; }) //bool - 1 
    );
#pragma warning(pop) 
}