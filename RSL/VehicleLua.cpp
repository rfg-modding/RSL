#include "VehicleLua.h"
#include "Functions.h"

void Lua::BindVehicleFlags(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_flags>();
    Utype.set("Activity", sol::property(
        [](vehicle_flags& Self)->bool {return Self.activity; },
        [](vehicle_flags& Self, bool Value) {Self.activity = Value; }
    ));
    Utype.set("OldActivity", sol::property(
        [](vehicle_flags& Self)->bool {return Self.old_activity; },
        [](vehicle_flags& Self, bool Value) {Self.old_activity = Value; }
    ));
    Utype.set("ActivityDestroyed", sol::property(
        [](vehicle_flags& Self)->bool {return Self.activity_destroyed; },
        [](vehicle_flags& Self, bool Value) {Self.activity_destroyed = Value; }
    ));
    Utype.set("ConvoyVehicle", sol::property(
        [](vehicle_flags& Self)->bool {return Self.convoy_vehicle; },
        [](vehicle_flags& Self, bool Value) {Self.convoy_vehicle = Value; }
    ));
    Utype.set("AmbientSpawn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.ambient_spawn; },
        [](vehicle_flags& Self, bool Value) {Self.ambient_spawn = Value; }
    ));
    Utype.set("DeathReported", sol::property(
        [](vehicle_flags& Self)->bool {return Self.death_reported; },
        [](vehicle_flags& Self, bool Value) {Self.death_reported = Value; }
    ));
    Utype.set("NoRagdoll", sol::property(
        [](vehicle_flags& Self)->bool {return Self.no_ragdoll; },
        [](vehicle_flags& Self, bool Value) {Self.no_ragdoll = Value; }
    ));
    Utype.set("DespawnedSquadVehicle", sol::property(
        [](vehicle_flags& Self)->bool {return Self.despawned_squad_vehicle; },
        [](vehicle_flags& Self, bool Value) {Self.despawned_squad_vehicle = Value; }
    ));
    Utype.set("DeleteMissionVehicle", sol::property(
        [](vehicle_flags& Self)->bool {return Self.delete_mission_vehicle; },
        [](vehicle_flags& Self, bool Value) {Self.delete_mission_vehicle = Value; }
    ));
    Utype.set("DoNotDestroyWithSquad", sol::property(
        [](vehicle_flags& Self)->bool {return Self.do_not_destroy_with_squad; },
        [](vehicle_flags& Self, bool Value) {Self.do_not_destroy_with_squad = Value; }
    ));
    Utype.set("Corpse", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_corpse; },
        [](vehicle_flags& Self, bool Value) {Self.m_corpse = Value; }
    ));
    Utype.set("DespawnAfterFade", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_despawn_after_fade; },
        [](vehicle_flags& Self, bool Value) {Self.m_despawn_after_fade = Value; }
    ));
    Utype.set("DoorCollisionEnabled", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_door_collision_enabled; },
        [](vehicle_flags& Self, bool Value) {Self.m_door_collision_enabled = Value; }
    ));
    Utype.set("EngineRunning", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_engine_running; },
        [](vehicle_flags& Self, bool Value) {Self.m_engine_running = Value; }
    ));
    Utype.set("EngineSmoking", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_engine_smoking; },
        [](vehicle_flags& Self, bool Value) {Self.m_engine_smoking = Value; }
    ));
    Utype.set("FadingIn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_fading_in; },
        [](vehicle_flags& Self, bool Value) {Self.m_fading_in = Value; }
    ));
    Utype.set("FadingOut", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_fading_out; },
        [](vehicle_flags& Self, bool Value) {Self.m_fading_out = Value; }
    ));
    Utype.set("FadingFromNano", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_fading_from_nano; },
        [](vehicle_flags& Self, bool Value) {Self.m_fading_from_nano = Value; }
    ));
    Utype.set("Hidden", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_hidden; },
        [](vehicle_flags& Self, bool Value) {Self.m_hidden = Value; }
    ));
    Utype.set("Hijacked", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_hijacked; },
        [](vehicle_flags& Self, bool Value) {Self.m_hijacked = Value; }
    ));
    Utype.set("ScriptedBail", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_scripted_bail; },
        [](vehicle_flags& Self, bool Value) {Self.m_scripted_bail = Value; }
    ));
    Utype.set("ScriptedAbandon", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_scripted_abandon; },
        [](vehicle_flags& Self, bool Value) {Self.m_scripted_abandon = Value; }
    ));
    Utype.set("HornDown", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_horn_down; },
        [](vehicle_flags& Self, bool Value) {Self.m_horn_down = Value; }
    ));
    Utype.set("Invulnerable", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_invulnerable; },
        [](vehicle_flags& Self, bool Value) {Self.m_invulnerable = Value; }
    ));
    Utype.set("MissionInvulnerable", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_mission_invulnerable; },
        [](vehicle_flags& Self, bool Value) {Self.m_mission_invulnerable = Value; }
    ));
    Utype.set("IsPlayerCar", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_is_player_car; },
        [](vehicle_flags& Self, bool Value) {Self.m_is_player_car = Value; }
    ));
    Utype.set("KillByVehicle", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_kill_by_vehicle; },
        [](vehicle_flags& Self, bool Value) {Self.m_kill_by_vehicle = Value; }
    ));
    //Utype.set("MpHonkedHorn", sol::property(
    //    [](vehicle_flags& Self)->bool {return Self.; },
    //    [](vehicle_flags& Self, bool Value)->bool {Self. = Value; }
    //));
    Utype.set("NeedsRepair", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_needs_repair; },
        [](vehicle_flags& Self, bool Value) {Self.m_needs_repair = Value; }
    ));
    Utype.set("Occupied", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_occupied; },
        [](vehicle_flags& Self, bool Value) {Self.m_occupied = Value; }
    ));
    Utype.set("OnFire", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_on_fire; },
        [](vehicle_flags& Self, bool Value) {Self.m_on_fire = Value; }
    ));
    Utype.set("NanoSimFire", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_nano_sim_fire; },
        [](vehicle_flags& Self, bool Value) {Self.m_nano_sim_fire = Value; }
    ));
    Utype.set("NanoSimSmoke", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_nano_sim_smoke; },
        [](vehicle_flags& Self, bool Value) {Self.m_nano_sim_smoke = Value; }
    ));
    Utype.set("GrenadeInside", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_grenade_inside; },
        [](vehicle_flags& Self, bool Value) {Self.m_grenade_inside = Value; }
    ));
    Utype.set("ReleasedFromCutscene", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_released_from_cutscene; },
        [](vehicle_flags& Self, bool Value) {Self.m_released_from_cutscene = Value; }
    ));
    Utype.set("ResourceAccessDisabled", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_resource_access_disabled; },
        [](vehicle_flags& Self, bool Value) {Self.m_resource_access_disabled = Value; }
    ));
    Utype.set("ReverseLastFrame", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_reverse_last_frame; },
        [](vehicle_flags& Self, bool Value) {Self.m_reverse_last_frame = Value; }
    ));
    Utype.set("SeriesOfHonks", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_series_of_honks; },
        [](vehicle_flags& Self, bool Value) {Self.m_series_of_honks = Value; }
    ));
    Utype.set("SirenDying", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_siren_dying; },
        [](vehicle_flags& Self, bool Value) {Self.m_siren_dying = Value; }
    ));
    Utype.set("SirenAudioOn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_siren_audio_on; },
        [](vehicle_flags& Self, bool Value) {Self.m_siren_audio_on = Value; }
    ));
    Utype.set("UsingHorn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_using_horn; },
        [](vehicle_flags& Self, bool Value) {Self.m_using_horn = Value; }
    ));
    Utype.set("PassByGettingCloser", sol::property(
        [](vehicle_flags& Self)->bool {return Self.pass_by_getting_closer; },
        [](vehicle_flags& Self, bool Value) {Self.pass_by_getting_closer = Value; }
    ));
    Utype.set("WheelsOnGround", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_wheels_on_ground; },
        [](vehicle_flags& Self, bool Value) {Self.m_wheels_on_ground = Value; }
    ));
    Utype.set("AllWheelsOnGround", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_all_wheels_on_ground; },
        [](vehicle_flags& Self, bool Value) {Self.m_all_wheels_on_ground = Value; }
    ));
    Utype.set("OnlyFireDamage", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_only_fire_damage; },
        [](vehicle_flags& Self, bool Value) {Self.m_only_fire_damage = Value; }
    ));
    Utype.set("HeadlightsOn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_headlights_on; },
        [](vehicle_flags& Self, bool Value) {Self.m_headlights_on = Value; }
    ));
    Utype.set("EmergencyLightsOn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.m_emergency_lights_on; },
        [](vehicle_flags& Self, bool Value) {Self.m_emergency_lights_on = Value; }
    ));
    Utype.set("HighPriorityTarget", sol::property(
        [](vehicle_flags& Self)->bool {return Self.high_priority_target; },
        [](vehicle_flags& Self, bool Value) {Self.high_priority_target = Value; }
    ));
    Utype.set("PlayerMayCapture", sol::property(
        [](vehicle_flags& Self)->bool {return Self.player_may_capture; },
        [](vehicle_flags& Self, bool Value) {Self.player_may_capture = Value; }
    ));
    Utype.set("DisableForNpcDrivers", sol::property(
        [](vehicle_flags& Self)->bool {return Self.disable_for_npc_drivers; },
        [](vehicle_flags& Self, bool Value) {Self.disable_for_npc_drivers = Value; }
    ));
    Utype.set("DisableForPlayer", sol::property(
        [](vehicle_flags& Self)->bool {return Self.disable_for_player; },
        [](vehicle_flags& Self, bool Value) {Self.disable_for_player = Value; }
    ));
    Utype.set("DisableAccelerator", sol::property(
        [](vehicle_flags& Self)->bool {return Self.disable_accelerator; },
        [](vehicle_flags& Self, bool Value) {Self.disable_accelerator = Value; }
    ));
    Utype.set("LockedInPlace", sol::property(
        [](vehicle_flags& Self)->bool {return Self.locked_in_place; },
        [](vehicle_flags& Self, bool Value) {Self.locked_in_place = Value; }
    ));
    Utype.set("FixedMotion", sol::property(
        [](vehicle_flags& Self)->bool {return Self.fixed_motion; },
        [](vehicle_flags& Self, bool Value) {Self.fixed_motion = Value; }
    ));
    Utype.set("DisableTurretsForNpcs", sol::property(
        [](vehicle_flags& Self)->bool {return Self.disable_turrets_for_npcs; },
        [](vehicle_flags& Self, bool Value) {Self.disable_turrets_for_npcs = Value; }
    ));
    Utype.set("ImmediateSpawn", sol::property(
        [](vehicle_flags& Self)->bool {return Self.immediate_spawn; },
        [](vehicle_flags& Self, bool Value) {Self.immediate_spawn = Value; }
    ));
    Utype.set("NoPlayerUse", sol::property(
        [](vehicle_flags& Self)->bool {return Self.no_player_use; },
        [](vehicle_flags& Self, bool Value) {Self.no_player_use = Value; }
    ));
    Utype.set("InvisibleDriver", sol::property(
        [](vehicle_flags& Self)->bool {return Self.invisible_driver; },
        [](vehicle_flags& Self, bool Value) {Self.invisible_driver = Value; }
    ));
    RfgTable.set_usertype("VehicleFlags", Utype);
}

void Lua::BindVehicleSpawnFlags(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_spawn_flags>();
    Utype.set("HighPriority", sol::property(
        [](vehicle_spawn_flags& Self)->bool {return Self.high_priority; },
        [](vehicle_spawn_flags& Self, bool Value) {Self.high_priority = Value; }
        ));
    Utype.set("MobileSpawn", sol::property(
        [](vehicle_spawn_flags& Self)->bool {return Self.mobile_spawn; },
        [](vehicle_spawn_flags& Self, bool Value) {Self.mobile_spawn = Value; }
    ));
    Utype.set("StaticPlacement", sol::property(
        [](vehicle_spawn_flags& Self)->bool {return Self.static_placement; },
        [](vehicle_spawn_flags& Self, bool Value) {Self.static_placement = Value; }
    ));
    Utype.set("SnapToGround", sol::property(
        [](vehicle_spawn_flags& Self)->bool {return Self.snap_to_ground; },
        [](vehicle_spawn_flags& Self, bool Value) {Self.snap_to_ground = Value; }
    ));
    Utype.set("RoadSpawn", sol::property(
        [](vehicle_spawn_flags& Self)->bool {return Self.road_spawn; },
        [](vehicle_spawn_flags& Self, bool Value) {Self.road_spawn = Value; }
    ));
    RfgTable.set_usertype("VehicleSpawnFlags", Utype);
}

void Lua::BindVehicleRddFlags(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_rdd_flags>();
    Utype.set("PositionOnGroundForCreate", sol::property(
        [](vehicle_rdd_flags& Self)->bool {return Self.m_pos_on_ground_for_create; },
        [](vehicle_rdd_flags& Self, bool Value) {Self.m_pos_on_ground_for_create = Value; }
    ));
    Utype.set("HideVehicle", sol::property(
        [](vehicle_rdd_flags& Self)->bool {return Self.m_hide_vehicle; },
        [](vehicle_rdd_flags& Self, bool Value) {Self.m_hide_vehicle = Value; }
    ));
    RfgTable.set_usertype("VehicleRddFlags", Utype);
}

void Lua::BindVehicle(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle>();
    Utype.set("new", sol::no_constructor);
    Utype.set(sol::base_classes, sol::bases<Object>());
    //Utype.set("Rdd", &vehicle::rdd);
    Utype.set("SpawnPriority", &vehicle::spawn_priority);
    Utype.set("Info", &vehicle::info);
    Utype.set("LastPos", &vehicle::last_pos);
    Utype.set("LastOrient", &vehicle::last_orient);
    Utype.set("LastVelocity", &vehicle::last_velocity);
    Utype.set("LastAngularVelocity", &vehicle::last_angular_velocity);
    Utype.set("ForwardVelocity", &vehicle::forward_velocity);
    Utype.set("LastForwardVelocity", &vehicle::last_forward_velocity);
    //Utype.set("Vai", &vehicle::vai);
    //Utype.set("Vii", &vehicle::vii);
    Utype.set("AimHandle", &vehicle::aim_handle);
    //Utype.set("Vp", &vehicle::vp);
    Utype.set("LastAnimTransform", &vehicle::last_anim_transform);
    Utype.set("PfFailureTimeout", &vehicle::pf_failure_timeout);
    Utype.set("DisableForNpcDriversTimer", &vehicle::disable_for_npc_drivers_timer);
    Utype.set("NoNpcEntryTimer", &vehicle::no_npc_entry_timer);
    Utype.set("RenderDistance", &vehicle::render_distance);
    Utype.set("SeatInfo", sol::property([](vehicle& Self) {return std::ref(Self.m_seat_info); })); 
    //Utype.set("DamageAreas", sol::property([](vehicle& Self) {return std::ref(Self.m_damage_areas); })); //Todo: bind
    Utype.set("NumTurretMounts", &vehicle::m_num_turret_mounts);
    //Utype.set("TurretMounts", sol::property([](vehicle& Self) {return std::ref(Self.m_turret_mounts); })); //Todo: Bind type
    Utype.set("BombStatus", &vehicle::m_bomb_status);
    //Utype.set("CollisionsThisFrame", &vehicle::m_collisions_this_frame); //Todo: Bind type
    Utype.set("WalkerVelocityHack", &vehicle::m_walker_velocity_hack);
    Utype.set("WalkerVelocityHackFollowup", &vehicle::m_walker_velocity_hack_followup);
    Utype.set("WalkerThrownEnergyScaled", &vehicle::m_walker_thrown_energy_scaled);
    Utype.set("SavedAngularDampening", &vehicle::saved_angular_dampening);
    Utype.set("WalkerVehicleCollisions", &vehicle::walker_vehicle_collisions);
    Utype.set("VehicleVsBuildingDamage", &vehicle::m_vehicle_vs_building_damage);
    //Utype.set("DamageEvents", sol::property([](vehicle& Self) {return std::ref(Self.damage_events); })); //Todo: Bind type
    Utype.set("NumDamageEvents", &vehicle::num_damage_events);
    //Utype.set("DamageEventsCs", &vehicle::damage_events_cs);
    Utype.set("CorpseTimer", &vehicle::m_corpse_timer);
    Utype.set("CorpseAbsoluteLongestTimer", &vehicle::m_corpse_absolute_longest_timer);
    Utype.set("OnFireTimestamp", &vehicle::on_fire_timestamp);
    Utype.set("CorpseEffect", &vehicle::m_corpse_effect);
    Utype.set("ExhaustEffectNormal", sol::property([](vehicle& Self) {return std::ref(Self.m_exhaust_effect_normal); }));
    Utype.set("ExhaustEffectBurst", sol::property([](vehicle& Self) {return std::ref(Self.m_exhaust_effect_burst); }));
    Utype.set("Flags", &vehicle::m_flags);
    Utype.set("TurretAutofireMs", &vehicle::m_turret_autofire_ms);
    Utype.set("NumSubPieces", &vehicle::m_num_sub_pieces);
    Utype.set("StreamPlacementFlags", &vehicle::stream_placement_flags);
    Utype.set("RddFlags", &vehicle::m_rdd_flags);
    Utype.set("KillerHandle", &vehicle::m_killer_handle);
    Utype.set("MostRecentDriver", &vehicle::most_recent_driver);
    Utype.set("TeamOfMostRecentDriver", &vehicle::team_of_most_recent_driver);
    Utype.set("MostRecentDriverExitTime", &vehicle::most_recent_driver_exit_time);
    Utype.set("DamageSoundPropagateTimer", &vehicle::damage_sound_propagate_timer);
    Utype.set("KillerWeapon", &vehicle::m_killer_weapon);
    Utype.set("RammingDamageTaken", &vehicle::ramming_damage_taken);
    Utype.set("ElectricalDamagePercent", &vehicle::m_electrical_damage_percent);
    Utype.set("DamagePercent", &vehicle::damage_percent);
    Utype.set("DamageFuncHandle", &vehicle::damage_func_handle);
    Utype.set("DestroyFuncHandle", &vehicle::destroy_func_handle);
    Utype.set("OnEnterFuncHandle", &vehicle::on_enter_func_handle);
    Utype.set("OnExitFuncHandle", &vehicle::on_exit_func_handle);
    Utype.set("OnTakeDamageHandle", &vehicle::on_take_damage_handle);
    Utype.set("OnCollisionHandle", &vehicle::on_collision_handle);
    Utype.set("OnHitPedHandle", &vehicle::on_hit_ped_handle);
    Utype.set("ReservedBy", &vehicle::reserved_by);
    Utype.set("SoundDelayAfterExplosion", &vehicle::m_sound_delay_after_explosion);
    Utype.set("FireDamageRate", &vehicle::m_fire_damage_rate);
    Utype.set("FireFractionalDamage", &vehicle::m_fire_fractional_damage);
    Utype.set("FadeTimer", &vehicle::m_fade_timer);
    Utype.set("FadeTime", &vehicle::m_fade_time);
    Utype.set("NumMeshDeformSpheres", &vehicle::m_num_mesh_deform_spheres);
    //Utype.set("TagDeformWeights", sol::property([](vehicle& Self) {return std::ref(reinterpret_cast<int*>(&Self.m_tag_deform_weights)); }));
    //Utype.set("NavcellInfo", &vehicle::m_navcell_info); //Todo: Bind type
    Utype.set("EmergencyLightTimer", &vehicle::emergency_light_timer);
    Utype.set("StreamLoadDistanceSqr", &vehicle::stream_load_distance_sqr);
    Utype.set("StreamUnloadDistanceSqr", &vehicle::stream_unload_distance_sqr);
    Utype.set("EngineInst", &vehicle::engine_inst);
    Utype.set("EngineStartedInst", &vehicle::engine_started_inst);
    Utype.set("EngineHighLoadStartTimer", &vehicle::engine_high_load_start_timer);
    Utype.set("PassByPlayId", &vehicle::pass_by_play_id);
    Utype.set("PassByDistance", &vehicle::pass_by_distance);
    Utype.set("NavCellDetourRequestHandle", &vehicle::m_nav_cell_detour_request_handle);
    Utype.set("NavCellDetourComponentRequestHandles", sol::property([](vehicle& Self) {return std::ref(Self.m_nav_cell_detour_component_request_handles); }));
    Utype.set("NumNavCellDetourComponentRequestHandles", &vehicle::m_num_nav_cell_detour_component_request_handles);
    Utype.set("LastDamageReported", &vehicle::last_damage_reported);
    Utype.set("SpawnNodeHandle", &vehicle::spawn_node_handle);
    Utype.set("SquadHandle", &vehicle::squad_handle);
    Utype.set("VehicleCheckCoverTimestamp", &vehicle::vehicle_check_cover_timestamp);
    Utype.set("VehicleCoverTimestamp", &vehicle::vehicle_cover_timestamp);
    Utype.set("VehicleCoverCreationPos", &vehicle::vehicle_cover_creation_pos);
    //Utype.set("VehicleCoverNodes", &vehicle::vehicle_cover_nodes); //Todo: Bind type
    Utype.set("VehicleCheckCoverIndex", &vehicle::vehicle_check_cover_index);
    Utype.set("VehicleCoverIndex", &vehicle::vehicle_cover_index);
    //Utype.set("ComponentRinstanceCs", &vehicle::component_rinstance_cs);
    Utype.set("InfiniteMass", &vehicle::infinite_mass);
    Utype.set("ExtraMass", &vehicle::extra_mass);
    Utype.set("ExtraMassValue", &vehicle::extra_mass_value);
    RfgTable.set_usertype("Vehicle", Utype);
}
