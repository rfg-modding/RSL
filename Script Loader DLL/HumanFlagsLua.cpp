#include "HumanFlagsLua.h"
#include "Functions.h"

void Lua::BindHumanFlags(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<HumanFlags>();
	Utype.set("new", sol::constructors<HumanFlags(), HumanFlags(const HumanFlags&)>());
	Utype.set("BoredHeadtrackDisabled", sol::property([](HumanFlags& Self) -> const bool& {return Self.bored_headtrack_disabled; }, [](HumanFlags& Self, bool Value) {Self.bored_headtrack_disabled = Value; })); //bool - 1
	Utype.set("Hidden", sol::property([](HumanFlags& Self) -> const bool& {return Self.hidden; }, [](HumanFlags& Self, bool Value) {Self.hidden = Value; })); //bool - 1
	Utype.set("CapSpeed", sol::property([](HumanFlags& Self) -> const bool& {return Self.cap_speed; }, [](HumanFlags& Self, bool Value) {Self.cap_speed = Value; })); //bool - 1
	Utype.set("WasRendered", sol::property([](HumanFlags& Self) -> const bool& {return Self.was_rendered; }, [](HumanFlags& Self, bool Value) {Self.was_rendered = Value; })); //bool - 1
	Utype.set("LockedController", sol::property([](HumanFlags& Self) -> const bool& {return Self.locked_controller; }, [](HumanFlags& Self, bool Value) {Self.locked_controller = Value; })); //bool - 1
	Utype.set("Invulnerable", sol::property([](HumanFlags& Self) -> const bool& {return Self.invulnerable; }, [](HumanFlags& Self, bool Value) {Self.invulnerable = Value; })); //bool - 1
	Utype.set("MissionInvulnerable", sol::property([](HumanFlags& Self) -> const bool& {return Self.mission_invulnerable; }, [](HumanFlags& Self, bool Value) {Self.mission_invulnerable = Value; })); //bool - 1
	Utype.set("NoDamage", sol::property([](HumanFlags& Self) -> const bool& {return Self.no_damage; }, [](HumanFlags& Self, bool Value) {Self.no_damage = Value; })); //bool - 1
	Utype.set("ActivityEngage", sol::property([](HumanFlags& Self) -> const bool& {return Self.activity_engage; }, [](HumanFlags& Self, bool Value) {Self.activity_engage = Value; })); //bool - 1
	Utype.set("ConsideredArmed", sol::property([](HumanFlags& Self) -> const bool& {return Self.considered_armed; }, [](HumanFlags& Self, bool Value) {Self.considered_armed = Value; })); //bool - 1
	Utype.set("RiotShield", sol::property([](HumanFlags& Self) -> const bool& {return Self.riot_shield; }, [](HumanFlags& Self, bool Value) {Self.riot_shield = Value; })); //bool - 1
	Utype.set("SafehouseVIP", sol::property([](HumanFlags& Self) -> const bool& {return Self.safehouse_vip; }, [](HumanFlags& Self, bool Value) {Self.safehouse_vip = Value; })); //bool - 1
	Utype.set("RadioOperator", sol::property([](HumanFlags& Self) -> const bool& {return Self.radio_operator; }, [](HumanFlags& Self, bool Value) {Self.radio_operator = Value; })); //bool - 1
	Utype.set("ActivityRaidRequired", sol::property([](HumanFlags& Self) -> const bool&{return Self.activity_raid_required; }, [](HumanFlags& Self, bool Value) {Self.activity_raid_required = Value; })); //bool - 1
	Utype.set("ActivityRaidOptional", sol::property([](HumanFlags& Self) -> const bool&{return Self.activity_raid_optional; }, [](HumanFlags& Self, bool Value) {Self.activity_raid_optional = Value; })); //bool - 1
	Utype.set("ActivateHouseArrestHostage", sol::property([](HumanFlags& Self) -> const bool& {return Self.activity_ha_hostage; }, [](HumanFlags& Self, bool Value) {Self.activity_ha_hostage = Value; })); //bool - 1
	Utype.set("RaidIntroductionLines", sol::property([](HumanFlags& Self) -> const bool& {return Self.raid_introduction_lines; }, [](HumanFlags& Self, bool Value) {Self.raid_introduction_lines = Value; })); //bool - 1
	Utype.set("MinerPersonaLines", sol::property([](HumanFlags& Self) -> const bool& {return Self.miner_persona_lines; }, [](HumanFlags& Self, bool Value) {Self.miner_persona_lines = Value; })); //bool - 1
	Utype.set("DamagedByPlayer", sol::property([](HumanFlags& Self) -> const bool& {return Self.damaged_by_player; }, [](HumanFlags& Self, bool Value) {Self.damaged_by_player = Value; })); //bool - 1
	Utype.set("AiIgnore", sol::property([](HumanFlags& Self) -> const bool& {return Self.ai_ignore; }, [](HumanFlags& Self, bool Value) {Self.ai_ignore = Value; })); //bool - 1
	Utype.set("CastsShadows", sol::property([](HumanFlags& Self) -> const bool& {return Self.casts_shadows; }, [](HumanFlags& Self, bool Value) {Self.casts_shadows = Value; })); //bool - 1
	Utype.set("CastsDropShadows", sol::property([](HumanFlags& Self) -> const bool& {return Self.casts_drop_shadows; }, [](HumanFlags& Self, bool Value) {Self.casts_drop_shadows = Value; })); //bool - 1
	Utype.set("IsTurning", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_turning; }, [](HumanFlags& Self, bool Value) {Self.is_turning = Value; })); //bool - 1 
	Utype.set("IsFalling", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_falling; }, [](HumanFlags& Self, bool Value) {Self.is_falling = Value; })); //bool - 1 
	Utype.set("DontDeformBones", sol::property([](HumanFlags& Self) -> const bool& {return Self.dont_deform_bones; }, [](HumanFlags& Self, bool Value) {Self.dont_deform_bones = Value; })); //bool - 1 
	Utype.set("DontLodBones", sol::property([](HumanFlags& Self) -> const bool& {return Self.dont_lod_bones; }, [](HumanFlags& Self, bool Value) {Self.dont_lod_bones = Value; })); //bool - 1 
	Utype.set("PlayingEquipAnim", sol::property([](HumanFlags& Self) -> const bool& {return Self.playing_equip_anim; }, [](HumanFlags& Self, bool Value) {Self.playing_equip_anim = Value; })); //bool - 1 
	Utype.set("PlayingUnequipAnim", sol::property([](HumanFlags& Self) -> const bool& {return Self.playing_unequip_anim; }, [](HumanFlags& Self, bool Value) {Self.playing_unequip_anim = Value; })); //bool - 1 
	Utype.set("DoInstantEquip", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_instant_equip; }, [](HumanFlags& Self, bool Value) {Self.do_instant_equip = Value; })); //bool - 1 
	Utype.set("AnimDirectBlend", sol::property([](HumanFlags& Self) -> const bool& {return Self.anim_direct_blend; }, [](HumanFlags& Self, bool Value) {Self.anim_direct_blend = Value; })); //bool - 1 
	Utype.set("StartJump", sol::property([](HumanFlags& Self) -> const bool&{return Self.start_jump; }, [](HumanFlags& Self, bool Value) {Self.start_jump = Value; })); //bool - 1 
	Utype.set("SuperJump", sol::property([](HumanFlags& Self) -> const bool&{return Self.super_jump; }, [](HumanFlags& Self, bool Value) {Self.super_jump = Value; })); //bool - 1 
	Utype.set("ProcessedThisFrame", sol::property([](HumanFlags& Self) -> const bool&{return Self.processed_this_frame; }, [](HumanFlags& Self, bool Value) {Self.processed_this_frame = Value; })); //bool - 1 
	Utype.set("SilentVehicleStart", sol::property([](HumanFlags& Self) -> const bool&{return Self.silent_vehicle_start; }, [](HumanFlags& Self, bool Value) {Self.silent_vehicle_start = Value; })); //bool - 1 
	Utype.set("SupressFleeOnVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.suppress_flee_on_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.suppress_flee_on_vehicle_exit = Value; })); //bool - 1 
	Utype.set("DeathFunctionDone", sol::property([](HumanFlags& Self) -> const bool& {return Self.death_func_done; }, [](HumanFlags& Self, bool Value) {Self.death_func_done = Value; })); //bool - 1 
	Utype.set("FadingIn", sol::property([](HumanFlags& Self) -> const bool& {return Self.fading_in; }, [](HumanFlags& Self, bool Value) {Self.fading_in = Value; })); //bool - 1 
	Utype.set("FadingOut", sol::property([](HumanFlags& Self) -> const bool& {return Self.fading_out; }, [](HumanFlags& Self, bool Value) {Self.fading_out = Value; })); //bool - 1 
	Utype.set("FadingOutFromNano", sol::property([](HumanFlags& Self) -> const bool& {return Self.fading_out_from_nano; }, [](HumanFlags& Self, bool Value) {Self.fading_out_from_nano = Value; })); //bool - 1 
	Utype.set("IsNanoEffectCurrentlyApplied", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_nano_effect_currently_applied; }, [](HumanFlags& Self, bool Value) {Self.is_nano_effect_currently_applied = Value; })); //bool - 1 
	Utype.set("OnFire", sol::property([](HumanFlags& Self) -> const bool& {return Self.on_fire; }, [](HumanFlags& Self, bool Value) {Self.on_fire = Value; })); //bool - 1 
	Utype.set("DroppedCash", sol::property([](HumanFlags& Self) -> const bool& {return Self.dropped_cash; }, [](HumanFlags& Self, bool Value) {Self.dropped_cash = Value; })); //bool - 1 
	Utype.set("OnMover", sol::property([](HumanFlags& Self) -> const bool& {return Self.on_mover; }, [](HumanFlags& Self, bool Value) {Self.on_mover = Value; })); //bool - 1 
	Utype.set("RecalculateAtNode", sol::property([](HumanFlags& Self) -> const bool& {return Self.recalculate_at_node; }, [](HumanFlags& Self, bool Value) {Self.recalculate_at_node = Value; })); //bool - 1 
	Utype.set("SpinebendingDone", sol::property([](HumanFlags& Self) -> const bool& {return Self.spinebending_done; }, [](HumanFlags& Self, bool Value) {Self.spinebending_done = Value; })); //bool - 1 
	Utype.set("LastDestinationInRepulsor", sol::property([](HumanFlags& Self) -> const bool& {return Self.last_dest_in_repulsor; }, [](HumanFlags& Self, bool Value) {Self.last_dest_in_repulsor = Value; })); //bool - 1 
	Utype.set("JumpingFromBuilding", sol::property([](HumanFlags& Self) -> const bool& {return Self.jumping_from_building; }, [](HumanFlags& Self, bool Value) {Self.jumping_from_building = Value; })); //bool - 1 
	Utype.set("IsOnLadder", sol::property([](HumanFlags& Self) -> const bool& {return Self.is_on_ladder; }, [](HumanFlags& Self, bool Value) {Self.is_on_ladder = Value; })); //bool - 1 
	Utype.set("LadderForceSlide", sol::property([](HumanFlags& Self) -> const bool& {return Self.ladder_force_slide; }, [](HumanFlags& Self, bool Value) {Self.ladder_force_slide = Value; })); //bool - 1 
	Utype.set("LadderForceExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.ladder_force_exit; }, [](HumanFlags& Self, bool Value) {Self.ladder_force_exit = Value; })); //bool - 1 
	Utype.set("LadderReEquipWeapon", sol::property([](HumanFlags& Self) -> const bool& {return Self.ladder_reequip_weapon; }, [](HumanFlags& Self, bool Value) {Self.ladder_reequip_weapon = Value; })); //bool - 1 
	Utype.set("AllowFlyingEquips", sol::property([](HumanFlags& Self) -> const bool& {return Self.allow_flying_equips; }, [](HumanFlags& Self, bool Value) {Self.allow_flying_equips = Value; })); //bool - 1 
	Utype.set("CorpseSpotted", sol::property([](HumanFlags& Self) -> const bool& {return Self.corpse_spotted; }, [](HumanFlags& Self, bool Value) {Self.corpse_spotted = Value; })); //bool - 1 
	Utype.set("CorpseSpottedByEnemy", sol::property([](HumanFlags& Self) -> const bool& {return Self.corpse_spotted_by_enemy; }, [](HumanFlags& Self, bool Value) {Self.corpse_spotted_by_enemy = Value; })); //bool - 1 
	Utype.set("DeathReported", sol::property([](HumanFlags& Self) -> const bool& {return Self.death_reported; }, [](HumanFlags& Self, bool Value) {Self.death_reported = Value; })); //bool - 1 
	Utype.set("RaidDeathAck", sol::property([](HumanFlags& Self) -> const bool& {return Self.raid_death_ack; }, [](HumanFlags& Self, bool Value) {Self.raid_death_ack = Value; })); //bool - 1 
	Utype.set("AnchorOrient", sol::property([](HumanFlags& Self) -> const bool& {return Self.anchor_orient; }, [](HumanFlags& Self, bool Value) {Self.anchor_orient = Value; })); //bool - 1 
	Utype.set("BonesTransformedThisFrame", sol::property([](HumanFlags& Self) -> const bool& {return Self.bones_transformed_this_frame; }, [](HumanFlags& Self, bool Value) {Self.bones_transformed_this_frame = Value; })); //bool - 1 
	Utype.set("UseCurrentVelocity", sol::property([](HumanFlags& Self) -> const bool& {return Self.use_current_velocity; }, [](HumanFlags& Self, bool Value) {Self.use_current_velocity = Value; })); //bool - 1 
	Utype.set("UseAsFinalVelocity", sol::property([](HumanFlags& Self) -> const bool& {return Self.use_as_final_velocity; }, [](HumanFlags& Self, bool Value) {Self.use_as_final_velocity = Value; })); //bool - 1 
	Utype.set("AimAtPos", sol::property([](HumanFlags& Self) -> const bool& {return Self.aim_at_pos; }, [](HumanFlags& Self, bool Value) {Self.aim_at_pos = Value; })); //bool - 1 
	Utype.set("BlockForcedMovement", sol::property([](HumanFlags& Self) -> const bool& {return Self.block_forced_movement; }, [](HumanFlags& Self, bool Value) {Self.block_forced_movement = Value; })); //bool - 1 
	Utype.set("CancellingMeleeAttack", sol::property([](HumanFlags& Self) -> const bool& {return Self.cancelling_melee_attack; }, [](HumanFlags& Self, bool Value) {Self.cancelling_melee_attack = Value; })); //bool - 1 
	Utype.set("DoContinuousMeleeDamage", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_continuous_melee_damage; }, [](HumanFlags& Self, bool Value) {Self.do_continuous_melee_damage = Value; })); //bool - 1 
	Utype.set("InAirMelee", sol::property([](HumanFlags& Self) -> const bool& {return Self.in_air_melee; }, [](HumanFlags& Self, bool Value) {Self.in_air_melee = Value; })); //bool - 1 
	Utype.set("CantHitWithMelee", sol::property([](HumanFlags& Self) -> const bool& {return Self.cant_hit_with_melee; }, [](HumanFlags& Self, bool Value) {Self.cant_hit_with_melee = Value; })); //bool - 1 
	Utype.set("InvulnerableToDebris", sol::property([](HumanFlags& Self) -> const bool& {return Self.invulnerable_to_debris; }, [](HumanFlags& Self, bool Value) {Self.invulnerable_to_debris = Value; })); //bool - 1 
	Utype.set("OverrideDefaultAnimState", sol::property([](HumanFlags& Self) -> const bool& {return Self.override_default_fire_anim; }, [](HumanFlags& Self, bool Value) {Self.override_default_fire_anim = Value; })); //bool - 1 
	Utype.set("OverrideDefaultFireAnim", sol::property([](HumanFlags& Self) -> const bool& {return Self.override_default_fire_anim; }, [](HumanFlags& Self, bool Value) {Self.override_default_fire_anim = Value; })); //bool - 1 
	Utype.set("MovingAndTransitioningStates", sol::property([](HumanFlags& Self) -> const bool& {return Self.moving_and_transitioning_states; }, [](HumanFlags& Self, bool Value) {Self.moving_and_transitioning_states = Value; })); //bool - 1 
	Utype.set("CheckForCover", sol::property([](HumanFlags& Self) -> const bool& {return Self.check_for_cover; }, [](HumanFlags& Self, bool Value) {Self.check_for_cover = Value; })); //bool - 1 
	Utype.set("JumpTakeOff", sol::property([](HumanFlags& Self) -> const bool& {return Self.jump_take_off; }, [](HumanFlags& Self, bool Value) {Self.jump_take_off = Value; })); //bool - 1 
	Utype.set("RotateInternalHeadingUpdated", sol::property([](HumanFlags& Self) -> const bool& {return Self.rotate_internal_heading_updated; }, [](HumanFlags& Self, bool Value) {Self.rotate_internal_heading_updated = Value; })); //bool - 1 
	Utype.set("CrouchCover", sol::property([](HumanFlags& Self) -> const bool& {return Self.crouch_cover; }, [](HumanFlags& Self, bool Value) {Self.crouch_cover = Value; })); //bool - 1 
	Utype.set("CoverCrouchHighOnly", sol::property([](HumanFlags& Self) -> const bool& {return Self.cover_crouch_high_only; }, [](HumanFlags& Self, bool Value) {Self.cover_crouch_high_only = Value; })); //bool - 1 
	Utype.set("CoverCrouchNoLean", sol::property([](HumanFlags& Self) -> const bool& {return Self.cover_crouch_no_lean; }, [](HumanFlags& Self, bool Value) {Self.cover_crouch_no_lean = Value; })); //bool - 1 
	Utype.set("SideFiring", sol::property([](HumanFlags& Self) -> const bool& {return Self.side_firing; }, [](HumanFlags& Self, bool Value) {Self.side_firing = Value; })); //bool - 1 
	Utype.set("SideFiringWalkBack", sol::property([](HumanFlags& Self) -> const bool& {return Self.side_firing_walk_back; }, [](HumanFlags& Self, bool Value) {Self.side_firing_walk_back = Value; })); //bool - 1 
	Utype.set("RagdollOnImpactAllCollisions", sol::property([](HumanFlags& Self) -> const bool& {return Self.ragdoll_on_impact_all_collisions; }, [](HumanFlags& Self, bool Value) {Self.ragdoll_on_impact_all_collisions = Value; })); //bool - 1 
	Utype.set("RagdollOnImpactUseRagdollPos", sol::property([](HumanFlags& Self) -> const bool& {return Self.ragdoll_on_impact_use_ragdoll_pos; }, [](HumanFlags& Self, bool Value) {Self.ragdoll_on_impact_use_ragdoll_pos = Value; })); //bool - 1 
	Utype.set("DiveCapsule", sol::property([](HumanFlags& Self) -> const bool& {return Self.dive_capsule; }, [](HumanFlags& Self, bool Value) {Self.dive_capsule = Value; })); //bool - 1 
	Utype.set("MaintainAmbientProps", sol::property([](HumanFlags& Self) -> const bool& {return Self.maintain_ambient_props; }, [](HumanFlags& Self, bool Value) {Self.maintain_ambient_props = Value; })); //bool - 1 
	Utype.set("LeaningDisabled", sol::property([](HumanFlags& Self) -> const bool& {return Self.leaning_disabled; }, [](HumanFlags& Self, bool Value) {Self.leaning_disabled = Value; })); //bool - 1 
	Utype.set("OverrideSteeringHeadingOffset", sol::property([](HumanFlags& Self) -> const bool& {return Self.override_steering_heading_offset; }, [](HumanFlags& Self, bool Value) {Self.override_steering_heading_offset = Value; })); //bool - 1 
	Utype.set("PushesOtherHumans", sol::property([](HumanFlags& Self) -> const bool& {return Self.pushes_other_humans; }, [](HumanFlags& Self, bool Value) {Self.pushes_other_humans = Value; })); //bool - 1 
	Utype.set("PushesDebrisScripted", sol::property([](HumanFlags& Self) -> const bool& {return Self.pushes_debris_scripted; }, [](HumanFlags& Self, bool Value) {Self.pushes_debris_scripted = Value; })); //bool - 1 
	Utype.set("AllowSteepSlopes", sol::property([](HumanFlags& Self) -> const bool& {return Self.allow_steep_slopes; }, [](HumanFlags& Self, bool Value) {Self.allow_steep_slopes = Value; })); //bool - 1 
	Utype.set("ExternalForceApplied", sol::property([](HumanFlags& Self) -> const bool& {return Self.external_force_applied; }, [](HumanFlags& Self, bool Value) {Self.external_force_applied = Value; })); //bool - 1 
	Utype.set("RagdollShot", sol::property([](HumanFlags& Self) -> const bool& {return Self.ragdoll_shot; }, [](HumanFlags& Self, bool Value) {Self.ragdoll_shot = Value; })); //bool - 1 
	Utype.set("SavedPushesDebrisScripted", sol::property([](HumanFlags& Self) -> const bool& {return Self.saved_pushes_debris_scripted; }, [](HumanFlags& Self, bool Value) {Self.saved_pushes_debris_scripted = Value; })); //bool - 1 
	Utype.set("FilterHandleValid", sol::property([](HumanFlags& Self) -> const bool& {return Self.filter_handle_valid; }, [](HumanFlags& Self, bool Value) {Self.filter_handle_valid = Value; })); //bool - 1 
	Utype.set("JustGotUpFromRagdoll", sol::property([](HumanFlags& Self) -> const bool& {return Self.just_got_up_from_ragdoll; }, [](HumanFlags& Self, bool Value) {Self.just_got_up_from_ragdoll = Value; })); //bool - 1 
	Utype.set("DisablePathSmoothingForRequest", sol::property([](HumanFlags& Self) -> const bool& {return Self.disable_path_smoothing_for_request; }, [](HumanFlags& Self, bool Value) {Self.disable_path_smoothing_for_request = Value; })); //bool - 1 
	Utype.set("DisableAllPathSmoothing", sol::property([](HumanFlags& Self) -> const bool& {return Self.disable_all_path_smoothing; }, [](HumanFlags& Self, bool Value) {Self.disable_all_path_smoothing = Value; })); //bool - 1 
	Utype.set("InFetalPosition", sol::property([](HumanFlags& Self) -> const bool& {return Self.in_fetal_position; }, [](HumanFlags& Self, bool Value) {Self.in_fetal_position = Value; })); //bool - 1 
	Utype.set("DisallowVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.disallow_vehicle_exit = Value; })); //bool - 1 
	Utype.set("LimitedVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.limited_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.limited_vehicle_exit = Value; })); //bool - 1 
	Utype.set("DriverlessExitOnly", sol::property([](HumanFlags& Self) -> const bool& {return Self.driverless_exit_only; }, [](HumanFlags& Self, bool Value) {Self.driverless_exit_only = Value; })); //bool - 1 
	Utype.set("StuckInVehicle", sol::property([](HumanFlags& Self) -> const bool& {return Self.stuck_in_vehicle; }, [](HumanFlags& Self, bool Value) {Self.stuck_in_vehicle = Value; })); //bool - 1 
	Utype.set("ConvoyVehicleExit", sol::property([](HumanFlags& Self) -> const bool& {return Self.convoy_vehicle_exit; }, [](HumanFlags& Self, bool Value) {Self.convoy_vehicle_exit = Value; })); //bool - 1 
	Utype.set("DisallowVehicleEntry", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_vehicle_entry; }, [](HumanFlags& Self, bool Value) {Self.disallow_vehicle_entry = Value; })); //bool - 1 
	Utype.set("DisallowVehicleDrive", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_vehicle_drive; }, [](HumanFlags& Self, bool Value) {Self.disallow_vehicle_drive = Value; })); //bool - 1 
	Utype.set("AmbientEDF", sol::property([](HumanFlags& Self) -> const bool& {return Self.ambient_edf; }, [](HumanFlags& Self, bool Value) {Self.ambient_edf = Value; })); //bool - 1 
	Utype.set("BashedCharacterController", sol::property([](HumanFlags& Self) -> const bool& {return Self.bashed_character_controller; }, [](HumanFlags& Self, bool Value) {Self.bashed_character_controller = Value; })); //bool - 1 
	Utype.set("HeadLoaded", sol::property([](HumanFlags& Self) -> const bool& {return Self.head_loaded; }, [](HumanFlags& Self, bool Value) {Self.head_loaded = Value; })); //bool - 1 
	Utype.set("LodHeadLoaded", sol::property([](HumanFlags& Self) -> const bool& {return Self.lod_head_loaded; }, [](HumanFlags& Self, bool Value) {Self.lod_head_loaded = Value; })); //bool - 1 
	Utype.set("InVehicleInvisible", sol::property([](HumanFlags& Self) -> const bool& {return Self.in_vehicle_invisible; }, [](HumanFlags& Self, bool Value) {Self.in_vehicle_invisible = Value; })); //bool - 1 
	Utype.set("HighPriorityTarget", sol::property([](HumanFlags& Self) -> const bool& {return Self.high_priority_target; }, [](HumanFlags& Self, bool Value) {Self.high_priority_target = Value; })); //bool - 1 
	Utype.set("HealthChangeWasNegative", sol::property([](HumanFlags& Self) -> const bool& {return Self.health_change_was_negative; }, [](HumanFlags& Self, bool Value) {Self.health_change_was_negative = Value; })); //bool - 1 
	Utype.set("VoiceLinePlay2D", sol::property([](HumanFlags& Self) -> const bool& {return Self.voice_line_play_2d; }, [](HumanFlags& Self, bool Value) {Self.voice_line_play_2d = Value; })); //bool - 1 
	Utype.set("VoiceLinePainOnly", sol::property([](HumanFlags& Self) -> const bool& {return Self.voice_line_pain_only; }, [](HumanFlags& Self, bool Value) {Self.voice_line_pain_only = Value; })); //bool - 1 
	Utype.set("KilledByKillzone", sol::property([](HumanFlags& Self) -> const bool& {return Self.killed_by_killzone; }, [](HumanFlags& Self, bool Value) {Self.killed_by_killzone = Value; })); //bool - 1 
	Utype.set("FirstTimeStreamed", sol::property([](HumanFlags& Self) -> const bool& {return Self.first_time_streamed; }, [](HumanFlags& Self, bool Value) {Self.first_time_streamed = Value; })); //bool - 1 
	Utype.set("Tired", sol::property([](HumanFlags& Self) -> const bool& {return Self.tired; }, [](HumanFlags& Self, bool Value) {Self.tired = Value; })); //bool - 1 
	Utype.set("UseBigsteps", sol::property([](HumanFlags& Self) -> const bool& {return Self.use_bigsteps; }, [](HumanFlags& Self, bool Value) {Self.use_bigsteps = Value; })); //bool - 1 
	Utype.set("Stuck", sol::property([](HumanFlags& Self) -> const bool& {return Self.stuck; }, [](HumanFlags& Self, bool Value) {Self.stuck = Value; })); //bool - 1 
	Utype.set("LastPfFailed", sol::property([](HumanFlags& Self) -> const bool& {return Self.last_pf_failed; }, [](HumanFlags& Self, bool Value) {Self.last_pf_failed = Value; })); //bool - 1 
	Utype.set("ExtendedStuck", sol::property([](HumanFlags& Self) -> const bool& {return Self.extended_stuck; }, [](HumanFlags& Self, bool Value) {Self.extended_stuck = Value; })); //bool - 1 
	Utype.set("XrayVisible", sol::property([](HumanFlags& Self) -> const bool& {return Self.xray_visible; }, [](HumanFlags& Self, bool Value) {Self.xray_visible = Value; })); //bool - 1 
	Utype.set("WasGibbed", sol::property([](HumanFlags& Self) -> const bool& {return Self.was_gibbed; }, [](HumanFlags& Self, bool Value) {Self.was_gibbed = Value; })); //bool - 1 
	Utype.set("PreventRagdollSfx", sol::property([](HumanFlags& Self) -> const bool& {return Self.prevent_ragdoll_sfx; }, [](HumanFlags& Self, bool Value) {Self.prevent_ragdoll_sfx = Value; })); //bool - 1 
	Utype.set("AlwaysShowOnMinimap", sol::property([](HumanFlags& Self) -> const bool& {return Self.always_show_on_minimap; }, [](HumanFlags& Self, bool Value) {Self.always_show_on_minimap = Value; })); //bool - 1 
	Utype.set("UsedDeathBuffer", sol::property([](HumanFlags& Self) -> const bool& {return Self.used_death_buffer; }, [](HumanFlags& Self, bool Value) {Self.used_death_buffer = Value; })); //bool - 1 
	Utype.set("DoNotConvertToGuerrilla", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_not_convert_to_guerrilla; }, [](HumanFlags& Self, bool Value) {Self.do_not_convert_to_guerrilla = Value; })); //bool - 1 
	Utype.set("DoNotPlayAmbientOrGreetLines", sol::property([](HumanFlags& Self) -> const bool& {return Self.do_not_play_ambient_or_greet_lines; }, [](HumanFlags& Self, bool Value) {Self.do_not_play_ambient_or_greet_lines = Value; })); //bool - 1 
	Utype.set("DisallowFlinchesAndRagdolls", sol::property([](HumanFlags& Self) -> const bool& {return Self.disallow_flinches_and_ragdolls; }, [](HumanFlags& Self, bool Value) {Self.disallow_flinches_and_ragdolls = Value; })); //bool - 1 
	Utype.set("OnlyUseActionNodes", sol::property([](HumanFlags& Self) -> const bool& {return Self.only_use_action_nodes; }, [](HumanFlags& Self, bool Value) {Self.only_use_action_nodes = Value; })); //bool - 1 
	Utype.set("ComplainWhenShot", sol::property([](HumanFlags& Self) -> const bool& {return Self.complain_when_shot; }, [](HumanFlags& Self, bool Value) {Self.complain_when_shot = Value; })); //bool - 1 
	LuaState.set_usertype("HumanFlags", Utype);

	/*RfgTable.new_usertype<HumanFlags>
	(
		"HumanFlags",
		"new", sol::constructors<HumanFlags(), HumanFlags(const HumanFlags&)>(),
		"BoredHeadtrackDisabled", sol::property(itsy_bitsy::read<HumanFlags, 0>, itsy_bitsy::write<HumanFlags, 0>), //int32 - 1
		"Hidden", sol::property(itsy_bitsy::read<HumanFlags, 1>, itsy_bitsy::write<HumanFlags, 1>), //int32 - 1
		"CapSpeed", sol::property(itsy_bitsy::read<HumanFlags, 2>, itsy_bitsy::write<HumanFlags, 2>), //int32 - 1
		"WasRendered", sol::property(itsy_bitsy::read<HumanFlags, 3>, itsy_bitsy::write<HumanFlags, 3>), //int32 - 1
		"LockedController", sol::property(itsy_bitsy::read<HumanFlags, 4>, itsy_bitsy::write<HumanFlags, 4>), //int32 - 1
		"Invulnerable", sol::property(itsy_bitsy::read<HumanFlags, 5>, itsy_bitsy::write<HumanFlags, 5>), //int32 - 1
		"MissionInvulnerable", sol::property(itsy_bitsy::read<HumanFlags, 6>, itsy_bitsy::write<HumanFlags, 6>), //int32 - 1
		"NoDamage", sol::property(itsy_bitsy::read<HumanFlags, 7>, itsy_bitsy::write<HumanFlags, 7>), //int32 - 1
		"ActivityEngage", sol::property(itsy_bitsy::read<HumanFlags, 8>, itsy_bitsy::write<HumanFlags, 8>), //int32 - 1
		"ConsideredArmed", sol::property(itsy_bitsy::read<HumanFlags, 9>, itsy_bitsy::write<HumanFlags, 9>), //int32 - 1
		"RiotShield", sol::property(itsy_bitsy::read<HumanFlags, 10>, itsy_bitsy::write<HumanFlags, 10>), //int32 - 1
		"SafehouseVIP", sol::property(itsy_bitsy::read<HumanFlags, 11>, itsy_bitsy::write<HumanFlags, 11>), //int32 - 1
		"RadioOperator", sol::property(itsy_bitsy::read<HumanFlags, 12>, itsy_bitsy::write<HumanFlags, 12>), //int32 - 1
		"ActivityRaidRequired", sol::property(itsy_bitsy::read<HumanFlags, 13>, itsy_bitsy::write<HumanFlags, 13>), //int32 - 1
		"ActivityRaidOptional", sol::property(itsy_bitsy::read<HumanFlags, 14>, itsy_bitsy::write<HumanFlags, 14>), //int32 - 1
		"ActivateHouseArrestHostage", sol::property(itsy_bitsy::read<HumanFlags, 15>, itsy_bitsy::write<HumanFlags, 15>), //int32 - 1
		"RaidIntroductionLines", sol::property(itsy_bitsy::read<HumanFlags, 16>, itsy_bitsy::write<HumanFlags, 16>), //int32 - 1
		"MinerPersonaLines", sol::property(itsy_bitsy::read<HumanFlags, 17>, itsy_bitsy::write<HumanFlags, 17>), //int32 - 1
		"DamagedByPlayer", sol::property(itsy_bitsy::read<HumanFlags, 18>, itsy_bitsy::write<HumanFlags, 18>), //int32 - 1
		"AiIgnore", sol::property(itsy_bitsy::read<HumanFlags, 19>, itsy_bitsy::write<HumanFlags, 19>), //int32 - 1
		"CastsShadows", sol::property(itsy_bitsy::read<HumanFlags, 20>, itsy_bitsy::write<HumanFlags, 20>),//int32 - 1
		"CastsDropShadows", sol::property(itsy_bitsy::read<HumanFlags, 21>, itsy_bitsy::write<HumanFlags, 21>), //int32 - 1
		"IsTurning", sol::property(itsy_bitsy::read<HumanFlags, 22>, itsy_bitsy::write<HumanFlags, 22>), //int32 - 1 
		"IsFalling", sol::property(itsy_bitsy::read<HumanFlags, 23>, itsy_bitsy::write<HumanFlags, 23>), //int32 - 1 
		"DontDeformBones", sol::property(itsy_bitsy::read<HumanFlags, 24>, itsy_bitsy::write<HumanFlags, 24>), //int32 - 1 
		"DontLodBones", sol::property(itsy_bitsy::read<HumanFlags, 25>, itsy_bitsy::write<HumanFlags, 25>), //int32 - 1 
		"PlayingEquipAnim", sol::property(itsy_bitsy::read<HumanFlags, 26>, itsy_bitsy::write<HumanFlags, 26>), //int32 - 1 
		"PlayingUnequipAnim", sol::property(itsy_bitsy::read<HumanFlags, 27>, itsy_bitsy::write<HumanFlags, 27>), //int32 - 1 
		"DoInstantEquip", sol::property(itsy_bitsy::read<HumanFlags, 28>, itsy_bitsy::write<HumanFlags, 28>), //int32 - 1 
		"AnimDirectBlend", sol::property(itsy_bitsy::read<HumanFlags, 29>, itsy_bitsy::write<HumanFlags, 29>), //int32 - 1 
		"StartJump", sol::property(itsy_bitsy::read<HumanFlags, 30>, itsy_bitsy::write<HumanFlags, 30>), //int32 - 1 
		"SuperJump", sol::property(itsy_bitsy::read<HumanFlags, 31>, itsy_bitsy::write<HumanFlags, 31>), //int32 - 1 
		"ProcessedThisFrame", sol::property(itsy_bitsy::read<HumanFlags, 32>, itsy_bitsy::write<HumanFlags, 32>), //int32 - 1 
		"SilentVehicleStart", sol::property(itsy_bitsy::read<HumanFlags, 33>, itsy_bitsy::write<HumanFlags, 33>), //int32 - 1 
		"SupressFleeOnVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 34>, itsy_bitsy::write<HumanFlags, 34>), //int32 - 1 
		"DeathFunctionDone", sol::property(itsy_bitsy::read<HumanFlags, 35>, itsy_bitsy::write<HumanFlags, 35>), //int32 - 1 
		"FadingIn", sol::property(itsy_bitsy::read<HumanFlags, 36>, itsy_bitsy::write<HumanFlags, 36>), //int32 - 1 
		"FadingOut", sol::property(itsy_bitsy::read<HumanFlags, 37>, itsy_bitsy::write<HumanFlags, 37>), //int32 - 1 
		"FadingOutFromNano", sol::property(itsy_bitsy::read<HumanFlags, 38>, itsy_bitsy::write<HumanFlags, 38>), //int32 - 1 
		"IsNanoEffectCurrentlyApplied", sol::property(itsy_bitsy::read<HumanFlags, 39>, itsy_bitsy::write<HumanFlags, 39>), //int32 - 1 
		"OnFire", sol::property(itsy_bitsy::read<HumanFlags, 40>, itsy_bitsy::write<HumanFlags, 40>), //int32 - 1 
		"DroppedCash", sol::property(itsy_bitsy::read<HumanFlags, 41>, itsy_bitsy::write<HumanFlags, 41>), //int32 - 1 
		"OnMover", sol::property(itsy_bitsy::read<HumanFlags, 42>, itsy_bitsy::write<HumanFlags, 42>), //int32 - 1 
		"RecalculateAtNode", sol::property(itsy_bitsy::read<HumanFlags, 43>, itsy_bitsy::write<HumanFlags, 43>), //int32 - 1 
		"SpinebendingDone", sol::property(itsy_bitsy::read<HumanFlags, 44>, itsy_bitsy::write<HumanFlags, 44>), //int32 - 1 
		"LastDestinationInRepulsor", sol::property(itsy_bitsy::read<HumanFlags, 45>, itsy_bitsy::write<HumanFlags, 45>), //int32 - 1 
		"JumpingFromBuilding", sol::property(itsy_bitsy::read<HumanFlags, 46>, itsy_bitsy::write<HumanFlags, 46>), //int32 - 1 
		"IsOnLadder", sol::property(itsy_bitsy::read<HumanFlags, 47>, itsy_bitsy::write<HumanFlags, 47>), //int32 - 1 
		"LadderForceSlide", sol::property(itsy_bitsy::read<HumanFlags, 48>, itsy_bitsy::write<HumanFlags, 48>), //int32 - 1 
		"LadderForceExit", sol::property(itsy_bitsy::read<HumanFlags, 49>, itsy_bitsy::write<HumanFlags, 49>), //int32 - 1 
		"LadderReEquipWeapon", sol::property(itsy_bitsy::read<HumanFlags, 50>, itsy_bitsy::write<HumanFlags, 50>), //int32 - 1 
		"AllowFlyingEquips", sol::property(itsy_bitsy::read<HumanFlags, 51>, itsy_bitsy::write<HumanFlags, 51>), //int32 - 1 
		"CorpseSpotted", sol::property(itsy_bitsy::read<HumanFlags, 52>, itsy_bitsy::write<HumanFlags, 52>), //int32 - 1 
		"CorpseSpottedByEnemy", sol::property(itsy_bitsy::read<HumanFlags, 53>, itsy_bitsy::write<HumanFlags, 53>), //int32 - 1 
		"DeathReported", sol::property(itsy_bitsy::read<HumanFlags, 54>, itsy_bitsy::write<HumanFlags, 54>), //int32 - 1 
		"RaidDeathAck", sol::property(itsy_bitsy::read<HumanFlags, 55>, itsy_bitsy::write<HumanFlags, 55>), //int32 - 1 
		"AnchorOrient", sol::property(itsy_bitsy::read<HumanFlags, 56>, itsy_bitsy::write<HumanFlags, 56>), //int32 - 1 
		"BonesTransformedThisFrame", sol::property(itsy_bitsy::read<HumanFlags, 57>, itsy_bitsy::write<HumanFlags, 57>), //int32 - 1 
		"UseCurrentVelocity", sol::property(itsy_bitsy::read<HumanFlags, 58>, itsy_bitsy::write<HumanFlags, 58>), //int32 - 1 
		"UseAsFinalVelocity", sol::property(itsy_bitsy::read<HumanFlags, 59>, itsy_bitsy::write<HumanFlags, 59>), //int32 - 1 
		"AimAtPos", sol::property(itsy_bitsy::read<HumanFlags, 60>, itsy_bitsy::write<HumanFlags, 60>), //int32 - 1 
		"BlockForcedMovement", sol::property(itsy_bitsy::read<HumanFlags, 61>, itsy_bitsy::write<HumanFlags, 61>), //int32 - 1 
		"CancellingMeleeAttack", sol::property(itsy_bitsy::read<HumanFlags, 62>, itsy_bitsy::write<HumanFlags, 62>), //int32 - 1 
		"DoContinuousMeleeDamage", sol::property(itsy_bitsy::read<HumanFlags, 63>, itsy_bitsy::write<HumanFlags, 63>), //int32 - 1 
		"InAirMelee", sol::property(itsy_bitsy::read<HumanFlags, 64>, itsy_bitsy::write<HumanFlags, 64>), //int32 - 1 
		"CantHitWithMelee", sol::property(itsy_bitsy::read<HumanFlags, 65>, itsy_bitsy::write<HumanFlags, 65>), //int32 - 1 
		"InvulnerableToDebris", sol::property(itsy_bitsy::read<HumanFlags, 66>, itsy_bitsy::write<HumanFlags, 66>), //int32 - 1 
		"OverrideDefaultAnimState", sol::property(itsy_bitsy::read<HumanFlags, 67>, itsy_bitsy::write<HumanFlags, 67>), //int32 - 1 
		"OverrideDefaultFireAnim", sol::property(itsy_bitsy::read<HumanFlags, 68>, itsy_bitsy::write<HumanFlags, 68>), //int32 - 1 
		"MovingAndTransitioningStates", sol::property(itsy_bitsy::read<HumanFlags, 69>, itsy_bitsy::write<HumanFlags, 69>), //int32 - 1 
		"CheckForCover", sol::property(itsy_bitsy::read<HumanFlags, 70>, itsy_bitsy::write<HumanFlags, 70>), //int32 - 1 
		"JumpTakeOff", sol::property(itsy_bitsy::read<HumanFlags, 71>, itsy_bitsy::write<HumanFlags, 71>), //int32 - 1 
		"RotateInternalHeadingUpdated", sol::property(itsy_bitsy::read<HumanFlags, 72>, itsy_bitsy::write<HumanFlags, 72>), //int32 - 1 
		"CrouchCover", sol::property(itsy_bitsy::read<HumanFlags, 73>, itsy_bitsy::write<HumanFlags, 73>), //int32 - 1 
		"CoverCrouchHighOnly", sol::property(itsy_bitsy::read<HumanFlags, 74>, itsy_bitsy::write<HumanFlags, 74>), //int32 - 1 
		"CoverCrouchNoLean", sol::property(itsy_bitsy::read<HumanFlags, 75>, itsy_bitsy::write<HumanFlags, 75>), //int32 - 1 
		"SideFiring", sol::property(itsy_bitsy::read<HumanFlags, 76>, itsy_bitsy::write<HumanFlags, 76>), //int32 - 1 
		"SideFiringWalkBack", sol::property(itsy_bitsy::read<HumanFlags, 77>, itsy_bitsy::write<HumanFlags, 77>), //int32 - 1 
		"RagdollOnImpactAllCollisions", sol::property(itsy_bitsy::read<HumanFlags, 78>, itsy_bitsy::write<HumanFlags, 78>), //int32 - 1 
		"RagdollOnImpactUseRagdollPos", sol::property(itsy_bitsy::read<HumanFlags, 79>, itsy_bitsy::write<HumanFlags, 79>), //int32 - 1 
		"DiveCapsule", sol::property(itsy_bitsy::read<HumanFlags, 80>, itsy_bitsy::write<HumanFlags, 80>), //int32 - 1 
		"MaintainAmbientProps", sol::property(itsy_bitsy::read<HumanFlags, 81>, itsy_bitsy::write<HumanFlags, 81>), //int32 - 1 
		"LeaningDisabled", sol::property(itsy_bitsy::read<HumanFlags, 82>, itsy_bitsy::write<HumanFlags, 82>), //int32 - 1 
		"OverrideSterringHeadingOffset", sol::property(itsy_bitsy::read<HumanFlags, 83>, itsy_bitsy::write<HumanFlags, 83>), //int32 - 1 
		"PushesOtherHumans", sol::property(itsy_bitsy::read<HumanFlags, 84>, itsy_bitsy::write<HumanFlags, 84>), //int32 - 1 
		"PushesDebrisScripted", sol::property(itsy_bitsy::read<HumanFlags, 85>, itsy_bitsy::write<HumanFlags, 85>), //int32 - 1 
		"AllowSteepSlopes", sol::property(itsy_bitsy::read<HumanFlags, 86>, itsy_bitsy::write<HumanFlags, 86>), //int32 - 1 
		"ExternalForceApplied", sol::property(itsy_bitsy::read<HumanFlags, 87>, itsy_bitsy::write<HumanFlags, 87>), //int32 - 1 
		"RagdollShot", sol::property(itsy_bitsy::read<HumanFlags, 88>, itsy_bitsy::write<HumanFlags, 88>), //int32 - 1 
		"SavedPushesDebrisScripted", sol::property(itsy_bitsy::read<HumanFlags, 89>, itsy_bitsy::write<HumanFlags, 89>), //int32 - 1 
		"FilterHandleValid", sol::property(itsy_bitsy::read<HumanFlags, 90>, itsy_bitsy::write<HumanFlags, 90>), //int32 - 1 
		"JustGotUpFromRagdoll", sol::property(itsy_bitsy::read<HumanFlags, 91>, itsy_bitsy::write<HumanFlags, 91>), //int32 - 1 
		"DisablePathSmoothingForRequest", sol::property(itsy_bitsy::read<HumanFlags, 92>, itsy_bitsy::write<HumanFlags, 92>), //int32 - 1 
		"DisableAllPathSmoothing", sol::property(itsy_bitsy::read<HumanFlags, 93>, itsy_bitsy::write<HumanFlags, 93>), //int32 - 1 
		"InFetalPosition", sol::property(itsy_bitsy::read<HumanFlags, 94>, itsy_bitsy::write<HumanFlags, 94>), //int32 - 1 
		"DisallowVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 95>, itsy_bitsy::write<HumanFlags, 95>), //int32 - 1 
		"LimitedVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 96>, itsy_bitsy::write<HumanFlags, 96>), //int32 - 1 
		"DriverlessExitOnly", sol::property(itsy_bitsy::read<HumanFlags, 97>, itsy_bitsy::write<HumanFlags, 97>), //int32 - 1 
		"StuckInVehicle", sol::property(itsy_bitsy::read<HumanFlags, 98>, itsy_bitsy::write<HumanFlags, 98>), //int32 - 1 
		"ConvoyVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 99>, itsy_bitsy::write<HumanFlags, 99>), //int32 - 1 
		"DisallowVehicleEntry", sol::property(itsy_bitsy::read<HumanFlags, 100>, itsy_bitsy::write<HumanFlags, 100>), //int32 - 1 
		"DisallowVehicleDrive", sol::property(itsy_bitsy::read<HumanFlags, 101>, itsy_bitsy::write<HumanFlags, 101>), //int32 - 1 
		"AmbientEDF", sol::property(itsy_bitsy::read<HumanFlags, 102>, itsy_bitsy::write<HumanFlags, 102>), //int32 - 1 
		"BashedCharacterController", sol::property(itsy_bitsy::read<HumanFlags, 103>, itsy_bitsy::write<HumanFlags, 103>), //int32 - 1 
		"HeadLoaded", sol::property(itsy_bitsy::read<HumanFlags, 104>, itsy_bitsy::write<HumanFlags, 104>), //int32 - 1 
		"LodHeadLoaded", sol::property(itsy_bitsy::read<HumanFlags, 105>, itsy_bitsy::write<HumanFlags, 105>), //int32 - 1 
		"InVehicleInvisible", sol::property(itsy_bitsy::read<HumanFlags, 106>, itsy_bitsy::write<HumanFlags, 106>), //int32 - 1 
		"HighPriorityTarget", sol::property(itsy_bitsy::read<HumanFlags, 107>, itsy_bitsy::write<HumanFlags, 107>), //int32 - 1 
		"HealthChangeWasNegative", sol::property(itsy_bitsy::read<HumanFlags, 108>, itsy_bitsy::write<HumanFlags, 108>), //int32 - 1 
		"VoiceLinePlay2D", sol::property(itsy_bitsy::read<HumanFlags, 109>, itsy_bitsy::write<HumanFlags, 109>), //int32 - 1 
		"VoiceLinePainOnly", sol::property(itsy_bitsy::read<HumanFlags, 110>, itsy_bitsy::write<HumanFlags, 110>), //int32 - 1 
		"KilledByKillzone", sol::property(itsy_bitsy::read<HumanFlags, 111>, itsy_bitsy::write<HumanFlags, 111>), //int32 - 1 
		"FirstTimeStreamed", sol::property(itsy_bitsy::read<HumanFlags, 112>, itsy_bitsy::write<HumanFlags, 112>), //int32 - 1 
		"Tired", sol::property(itsy_bitsy::read<HumanFlags, 113>, itsy_bitsy::write<HumanFlags, 113>), //int32 - 1 
		"UseBigsteps", sol::property(itsy_bitsy::read<HumanFlags, 114>, itsy_bitsy::write<HumanFlags, 114>), //int32 - 1 
		"Stuck", sol::property(itsy_bitsy::read<HumanFlags, 115>, itsy_bitsy::write<HumanFlags, 115>), //int32 - 1 
		"LastPfFailed", sol::property(itsy_bitsy::read<HumanFlags, 116>, itsy_bitsy::write<HumanFlags, 116>), //int32 - 1 
		"ExtendedStuck", sol::property(itsy_bitsy::read<HumanFlags, 117>, itsy_bitsy::write<HumanFlags, 117>), //int32 - 1 
		"XrayVisible", sol::property(itsy_bitsy::read<HumanFlags, 118>, itsy_bitsy::write<HumanFlags, 118>), //int32 - 1 
		"WasGibbed", sol::property(itsy_bitsy::read<HumanFlags, 119>, itsy_bitsy::write<HumanFlags, 119>), //int32 - 1 
		"PreventRagdollSfx", sol::property(itsy_bitsy::read<HumanFlags, 120>, itsy_bitsy::write<HumanFlags, 120>), //int32 - 1 
		"AlwaysShowOnMinimap", sol::property(itsy_bitsy::read<HumanFlags, 121>, itsy_bitsy::write<HumanFlags, 121>), //int32 - 1 
		"UsedDeathBuffer", sol::property(itsy_bitsy::read<HumanFlags, 122>, itsy_bitsy::write<HumanFlags, 122>), //int32 - 1 
		"DoNotConvertToGuerrilla", sol::property(itsy_bitsy::read<HumanFlags, 123>, itsy_bitsy::write<HumanFlags, 123>), //int32 - 1 
		"DoNotPlayAmbientOrGreetLines", sol::property(itsy_bitsy::read<HumanFlags, 124>, itsy_bitsy::write<HumanFlags, 124>), //int32 - 1 
		"DisallowFlinchesAndRagdolls", sol::property(itsy_bitsy::read<HumanFlags, 125>, itsy_bitsy::write<HumanFlags, 125>), //int32 - 1 
		"OnlyUseActionNodes", sol::property(itsy_bitsy::read<HumanFlags, 126>, itsy_bitsy::write<HumanFlags, 126>), //int32 - 1 
		"ComplainWhenShot", sol::property(itsy_bitsy::read<HumanFlags, 127>, itsy_bitsy::write<HumanFlags, 127>) //int32 - 1 
	);*/
}