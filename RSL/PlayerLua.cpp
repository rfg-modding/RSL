#include "PlayerLua.h"
#include "Functions.h"

void Lua::BindUpgradeItem(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<UpgradeItem>();
	Utype.set("new", sol::no_constructor);
	Utype.set("CurrentLevel", &UpgradeItem::current_level);
	Utype.set("AvailabilityBitfield", &UpgradeItem::availability_bitfield);
	Utype.set("UnlockedNotifiedBitfield", &UpgradeItem::unlocked_notified_bitfield);
	Utype.set("NewNotifiedBitfield", &UpgradeItem::new_notified_bitfield);
	RfgTable.set_usertype("PlayerMetadata", Utype);
}

void Lua::BindPlayerMetadata(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<PlayerMetadata>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Salvage", &PlayerMetadata::Salvage);
	Utype.set("MiningCount", &PlayerMetadata::MiningCount);
	Utype.set("SupplyCrateCount", &PlayerMetadata::SupplyCrateCount);
	Utype.set("DistrictHash", &PlayerMetadata::DistrictHash);
	Utype.set("DistrictTime", &PlayerMetadata::DistrictTime);
	Utype.set("Upgrades", sol::property([](PlayerMetadata& Self) { return std::ref(Self.upgrades); })); //Size 128 array of UpgradeItem
	Utype.set("PlayTime", &PlayerMetadata::PlayTime);
	Utype.set("LastDeathTime", &PlayerMetadata::LastDeathTime);
	RfgTable.set_usertype("PlayerMetadata", Utype);
}

void Lua::BindPathfindNavInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<PathfindNavInfo>();
	Utype.set("new", sol::no_constructor);
	Utype.set("LastVisitedVehicleNavCellHandle", &PathfindNavInfo::LastVisitedVehicleNavCellHandle);
	Utype.set("LastVisitedVehicleNavCellUpdateTimer", &PathfindNavInfo::LastVisitedVehicleNavCellUpdateTimer);
	RfgTable.set_usertype("PathfindNavInfo", Utype);
}

void Lua::BindVehicleEnterStruct(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<VehicleEnterStruct>();
	Utype.set("new", sol::no_constructor);
	Utype.set("VehicleHandle", &VehicleEnterStruct::VehicleHandle);
	Utype.set("Run", &VehicleEnterStruct::Run);
	RfgTable.set_usertype("VehicleEnterStruct", Utype);
}

void Lua::BindScriptSpecificData(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<ScriptSpecificData>();
	Utype.set("new", sol::no_constructor);
	Utype.set("VehicleEnterData", &ScriptSpecificData::VehicleEnterData);
	RfgTable.set_usertype("ScriptSpecificData", Utype);
}

void Lua::BindPlayerFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<PlayerFlags>();
	Utype.set("new", sol::no_constructor);
	Utype.set("ActionNodeAnimStarted", sol::property(itsy_bitsy::read<PlayerFlags, 0>, itsy_bitsy::write<PlayerFlags, 0>)); //uint32 - 1
	Utype.set("CustomMesh", sol::property(itsy_bitsy::read<PlayerFlags, 1>, itsy_bitsy::write<PlayerFlags, 1>)); //uint32 - 1
	Utype.set("IsLoaded", sol::property(itsy_bitsy::read<PlayerFlags, 2>, itsy_bitsy::write<PlayerFlags, 2>)); //uint32 - 1
	Utype.set("ScriptControlled", sol::property(itsy_bitsy::read<PlayerFlags, 3>, itsy_bitsy::write<PlayerFlags, 3>)); //uint32 - 1
	Utype.set("NeverDie", sol::property(itsy_bitsy::read<PlayerFlags, 4>, itsy_bitsy::write<PlayerFlags, 4>)); //uint32 - 1
	Utype.set("MissionNeverDie", sol::property(itsy_bitsy::read<PlayerFlags, 5>, itsy_bitsy::write<PlayerFlags, 5>)); //uint32 - 1
	Utype.set("DoSprint", sol::property(itsy_bitsy::read<PlayerFlags, 6>, itsy_bitsy::write<PlayerFlags, 6>)); //uint32 - 1
	Utype.set("DisableControls", sol::property(itsy_bitsy::read<PlayerFlags, 7>, itsy_bitsy::write<PlayerFlags, 7>)); //uint32 - 1
	Utype.set("JetpackStarted", sol::property(itsy_bitsy::read<PlayerFlags, 8>, itsy_bitsy::write<PlayerFlags, 8>)); //uint32 - 1
	Utype.set("JetpackReady", sol::property(itsy_bitsy::read<PlayerFlags, 9>, itsy_bitsy::write<PlayerFlags, 9>)); //uint32 - 1
	Utype.set("MovingToAStop", sol::property(itsy_bitsy::read<PlayerFlags, 10>, itsy_bitsy::write<PlayerFlags, 10>)); //uint32 - 1
	Utype.set("QuickTurn", sol::property(itsy_bitsy::read<PlayerFlags, 11>, itsy_bitsy::write<PlayerFlags, 11>)); //uint32 - 1
	Utype.set("CrouchingState", sol::property(itsy_bitsy::read<PlayerFlags, 12>, itsy_bitsy::write<PlayerFlags, 12>)); //uint32 - 1
	Utype.set("WeaponHidden", sol::property(itsy_bitsy::read<PlayerFlags, 13>, itsy_bitsy::write<PlayerFlags, 13>)); //uint32 - 1
	Utype.set("IsStuck", sol::property(itsy_bitsy::read<PlayerFlags, 14>, itsy_bitsy::write<PlayerFlags, 14>)); //uint32 - 1
	Utype.set("CoverFiring", sol::property(itsy_bitsy::read<PlayerFlags, 15>, itsy_bitsy::write<PlayerFlags, 15>)); //uint32 - 2
	Utype.set("CoverLeanup", sol::property(itsy_bitsy::read<PlayerFlags, 16>, itsy_bitsy::write<PlayerFlags, 16>)); //uint32 - 1
	Utype.set("UseCover", sol::property(itsy_bitsy::read<PlayerFlags, 17>, itsy_bitsy::write<PlayerFlags, 17>)); //uint32 - 1
	Utype.set("NoReticule", sol::property(itsy_bitsy::read<PlayerFlags, 18>, itsy_bitsy::write<PlayerFlags, 18>)); //uint32 - 1
	Utype.set("NoFineaim", sol::property(itsy_bitsy::read<PlayerFlags, 19>, itsy_bitsy::write<PlayerFlags, 19>)); //uint32 - 1
	Utype.set("CoverSearchForEdge", sol::property(itsy_bitsy::read<PlayerFlags, 20>, itsy_bitsy::write<PlayerFlags, 20>)); //uint32 - 1
	Utype.set("CoverAgainstVehicle", sol::property(itsy_bitsy::read<PlayerFlags, 21>, itsy_bitsy::write<PlayerFlags, 21>)); //uint32 - 1
	Utype.set("InCommTowerRange", sol::property(itsy_bitsy::read<PlayerFlags, 22>, itsy_bitsy::write<PlayerFlags, 22>)); //uint32 - 1 
	Utype.set("CommRangeChecked", sol::property(itsy_bitsy::read<PlayerFlags, 23>, itsy_bitsy::write<PlayerFlags, 23>)); //uint32 - 1 
	Utype.set("PassengerBrake", sol::property(itsy_bitsy::read<PlayerFlags, 24>, itsy_bitsy::write<PlayerFlags, 24>)); //uint32 - 1 
	Utype.set("LocalPlayerHitSomeoneThisFrame", sol::property(itsy_bitsy::read<PlayerFlags, 25>, itsy_bitsy::write<PlayerFlags, 25>)); //uint32 - 1 
	Utype.set("WeaponSwapLock", sol::property(itsy_bitsy::read<PlayerFlags, 26>, itsy_bitsy::write<PlayerFlags, 26>)); //uint32 - 1 
	Utype.set("UnlimitedAmmo", sol::property(itsy_bitsy::read<PlayerFlags, 27>, itsy_bitsy::write<PlayerFlags, 27>)); //uint32 - 1 
	Utype.set("InRadiation", sol::property(itsy_bitsy::read<PlayerFlags, 28>, itsy_bitsy::write<PlayerFlags, 28>)); //uint32 - 1 
	Utype.set("RagdollOnNextExplosion", sol::property(itsy_bitsy::read<PlayerFlags, 29>, itsy_bitsy::write<PlayerFlags, 29>)); //uint32 - 1 
	Utype.set("LeavingSquadMemberBehind", sol::property(itsy_bitsy::read<PlayerFlags, 30>, itsy_bitsy::write<PlayerFlags, 30>)); //uint32 - 1 
	Utype.set("IsWaitingForHostageVehicleExit", sol::property(itsy_bitsy::read<PlayerFlags, 31>, itsy_bitsy::write<PlayerFlags, 31>)); //uint32 - 1 
	Utype.set("BackpackFadeOut", sol::property(itsy_bitsy::read<PlayerFlags, 32>, itsy_bitsy::write<PlayerFlags, 32>)); //uint32 - 1 
	Utype.set("BackpackFadeIn", sol::property(itsy_bitsy::read<PlayerFlags, 33>, itsy_bitsy::write<PlayerFlags, 33>)); //uint32 - 1 
	//Utype.set("MpDisplayRespawnMsg", sol::property(itsy_bitsy::read<PlayerFlags, 34>, itsy_bitsy::write<PlayerFlags, 34>)); //uint32 - 1 
	//Utype.set("MpRemotePlayerFiredThisFrame", sol::property(itsy_bitsy::read<PlayerFlags, 35>, itsy_bitsy::write<PlayerFlags, 35>)); //uint32 - 1 
	//Utype.set("MpIgnorePlayerForRespawnCollisions", sol::property(itsy_bitsy::read<PlayerFlags, 36>, itsy_bitsy::write<PlayerFlags, 36>)); //uint32 - 1 
	//Utype.set("MpLostHP", sol::property(itsy_bitsy::read<PlayerFlags, 37>, itsy_bitsy::write<PlayerFlags, 37>)); //uint32 - 1 
	//Utype.set("MpHitSomeoneThisNetworkFrame", sol::property(itsy_bitsy::read<PlayerFlags, 38>, itsy_bitsy::write<PlayerFlags, 38>)); //uint32 - 1 
	//Utype.set("MpRemotePlayerChargedThisFrame", sol::property(itsy_bitsy::read<PlayerFlags, 39>, itsy_bitsy::write<PlayerFlags, 39>)); //uint32 - 1 
	//Utype.set("MpLocalPlayerCanSeeMe", sol::property(itsy_bitsy::read<PlayerFlags, 40>, itsy_bitsy::write<PlayerFlags, 40>)); //uint32 - 1 
	//Utype.set("MpHasReloaded", sol::property(itsy_bitsy::read<PlayerFlags, 41>, itsy_bitsy::write<PlayerFlags, 41>)); //uint32 - 1 
	//Utype.set("MpRemovingPlayer", sol::property(itsy_bitsy::read<PlayerFlags, 42>, itsy_bitsy::write<PlayerFlags, 42>)); //uint32 - 1 
	Utype.set("WaitingForLockerExit", sol::property(itsy_bitsy::read<PlayerFlags, 43>, itsy_bitsy::write<PlayerFlags, 43>)); //uint32 - 1 
	RfgTable.set_usertype("PlayerFlags", Utype);
}

void Lua::BindUsableObject(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<UseableObject>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Handle", &UseableObject::handle);
	Utype.set("ActionType", &UseableObject::action_type);
	Utype.set("ActionIcon", &UseableObject::action_icon);
	Utype.set("DotProduct", &UseableObject::dot_prod);
	Utype.set("DistanceSquared", &UseableObject::dist_squared);
	//Utype.set("ActionCallback", &UseableObject::action_callback); //Function ptr
	RfgTable.set_usertype("UseableObject", Utype);
}

void Lua::BindPlayer(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Player>();
	Utype.set(sol::base_classes, sol::bases<Human, Object>());
	Utype.set("FrametimeMultiplier", &Player::FrametimeMultiplier);
	Utype.set("ActionObject", &Player::action_object);
	Utype.set("ActionObjectTimestamp", &Player::action_object_timestamp);
	Utype.set("LastFireTime", &Player::last_fire_time);
	//Utype.set("MpActionObjectHandle", &Player::mp_action_object_handle);
	Utype.set("RadioID", &Player::radio_id);
	Utype.set("TagTrigger", &Player::tag_trigger);
	Utype.set("TagSequence", &Player::tag_seq);
	Utype.set("TagTimer", &Player::tag_timer);
	Utype.set("TagEffect", &Player::TagEffect);
	Utype.set("HudMessage", &Player::hud_message);
	Utype.set("HavokFilterGroup", &Player::havok_filter_group);
	Utype.set("AimTarget", &Player::aim_target);
	Utype.set("PenetratingAimTarget", &Player::penetrating_aim_target);
	Utype.set("PenetratingAimPos", &Player::penetrating_aim_pos);
	Utype.set("AimTargetDuration", &Player::aim_target_duration);
	Utype.set("HeatSeekingTarget", &Player::heat_seeking_target);
	Utype.set("AimPos", &Player::aim_pos);
	Utype.set("CombatTargetUpdateTime", &Player::combat_target_update_time);
	Utype.set("RemoteChargeTime", &Player::remote_charge_time);
	Utype.set("DoingRemoteCharge", &Player::doing_remote_charge);
	Utype.set("ZoomState", &Player::zoom_state);
	Utype.set("PreviousZoomState", &Player::previous_zoom_state);
	Utype.set("CoverVector", &Player::cover_vector);
	Utype.set("CoverVectorRight", &Player::cover_vector_right);
	Utype.set("EnteringCover", &Player::entering_cover);
	Utype.set("ExitingCover", &Player::exiting_cover);
	Utype.set("CoverMoveVel", &Player::cover_move_vel);
	Utype.set("CoverApproachingEdge", &Player::cover_approaching_edge);
	Utype.set("CoverApproachingEdgeTS", &Player::cover_approaching_edge_ts);
	Utype.set("CoverEdgeHitPos", &Player::cover_edge_hit_pos);
	Utype.set("CoverEdgeMissPos", &Player::cover_edge_miss_pos);
	Utype.set("ThrownWeaponCheckPos", &Player::thrown_weapon_check_pos);
	Utype.set("CombatMoveQueue", &Player::combat_move_queue);
	Utype.set("PreviousBulletHit", &Player::previous_bullet_hit);
	Utype.set("JetpackFuelPercent", &Player::JetpackFuelPercent);
	Utype.set("JetpackFoley", &Player::JetpackFoley);
	Utype.set("JetpackEffect", &Player::JetpackEffect);
	Utype.set("AllowRagdoll", &Player::AllowRagdoll);
	Utype.set("PlayerFlags", &Player::PFlags);
	Utype.set("HoldObjectAvailable", &Player::hold_object_available);
	Utype.set("HoldObjectHandle", &Player::hold_object_handle);
	//Utype.set("AbandonedVehicles", &Player::abandoned_vehicles); //Size 3 array of uint
	Utype.set("NumAbandonedVehicles", &Player::num_abandoned_vehicles);
	//Utype.set("CustomVehicles", &Player::custom_vehicles); //Size 50 array of CustomVehicle
	//Utype.set("CustomVehicleList", &Player::custom_vehicle_list);
	//Utype.set("CustomVehicleFreeList", &Player::custom_vehicle_free_list);
	//Utype.set("NumCustomVehicles", &Player::);
	Utype.set("DeadTimestamp", &Player::dead_timestamp);
	Utype.set("MatFxHandle", sol::property([](Player& Self) { return std::ref(Self.mat_fx_handle); })); //Size 16 array of uint
	Utype.set("CurrentMatFx", &Player::current_mat_fx);
	Utype.set("ScriptMode", &Player::script_mode);
	Utype.set("ScriptData", &Player::script_data);
	///Utype.set("Backpack", &Player::Backpack); Type of MultiObjectBackpack
	/*Utype.set("MpRespawnBackpackType", &Player::mp_respawn_backpack_type);
	Utype.set("MpCurrentCommand", &Player::mp_current_command);
	Utype.set("MpCameraPos", &Player::);
	Utype.set("MpCameraOrient", &Player::);
	Utype.set("MpCameraAngularVelocity", &Player::);
	Utype.set("MpDesiredWeaponSlot", &Player::);
	Utype.set("MpLastRespawnTime", &Player::);
	Utype.set("MpData", &Player::);
	Utype.set("MpDisarmBombHandle", &Player::);
	Utype.set("MpSimState", &Player::);
	Utype.set("MpLastSpawnPointHandle", &Player::);
	Utype.set("MpTimeUntilPlayerCanRespawn", &Player::);
	Utype.set("MpTimeUntilPlayerLeavesInvulnerability", &Player::);
	Utype.set("MpSwapBackpack", &Player::);
	Utype.set("MpPlayerDamageHistory", &Player::);
	Utype.set("MpLadderState", &Player::);
	Utype.set("MpRagdollForce", &Player::);
	Utype.set("MpRagdollForceTimeout", &Player::);
	Utype.set("MpEdgeCorrectionInfo", &Player::);
	Utype.set("MpBlockedInfo", &Player::);
	Utype.set("MpRagdollLinearVelocityAggregate", &Player::);
	Utype.set("MpRagdollAngularVelocityAggregate", &Player::);
	Utype.set("MpSimulationTimeUsed", &Player::);
	Utype.set("MpSimulationTimeAccumulated", &Player::);
	Utype.set("MpSimulationTimeExtrapolated", &Player::);*/
	Utype.set("JetpackUseLogHandle", &Player::jetpack_use_log_handle);
	Utype.set("BackpackEquipLogHandle", &Player::backpack_equip_log_handle);
	Utype.set("DistrictLogHandle", &Player::district_log_handle);
	Utype.set("CameraBoneTransform", &Player::camera_bone_transform);
	Utype.set("MovementVelocity", &Player::movement_velocity);
	Utype.set("DirectControlDir", &Player::direct_control_dir);
	Utype.set("DirectControlVel", &Player::direct_control_vel);
	Utype.set("CoverCollisionNormal", &Player::cover_collision_normal);
	Utype.set("LastFrameCoverCollisionNormal", &Player::last_frame_cover_collision_normal);
	Utype.set("CoverTestQueue", &Player::cover_test_queue);
	Utype.set("CoverDelayTS", &Player::cover_exit_delay_ts);
	Utype.set("CoverEnterTS", &Player::cover_enter_ts);
	Utype.set("CoverExitDelayTS", &Player::cover_exit_delay_ts);
	Utype.set("CoverDiveCapsule", &Player::cover_dive_capsule);
	Utype.set("CoverLeanDelay", &Player::cover_lean_delay);
	Utype.set("CoverRootOffset", &Player::cover_root_offset);
	Utype.set("SpinebendRootOffset", &Player::spinebend_root_offset);
	Utype.set("FacialIdle", &Player::facial_idle);
	Utype.set("FootstepPropagateTime", &Player::footstep_propagate_time);
	Utype.set("BumpIntoPropagateTime", &Player::bump_into_propagate_time);
	Utype.set("AmmoBoxHandle", &Player::ammo_box_handle);
	Utype.set("PathfindTimeOut", &Player::pathfind_time_out);
	Utype.set("CurrentInterfaceMode", &Player::current_interface_mode);
	Utype.set("CommonControlsAllowed", &Player::common_controls_allowed);
	Utype.set("ControlsGeneralAllowed", &Player::controls_general_allowed);
	Utype.set("ControlsOnFootAllowed", &Player::controls_on_foot_allowed);
	Utype.set("ControlsDrivingAllowed", &Player::controls_driving_allowed);
	Utype.set("GeneralActionsAllowed", &Player::general_actions_allowed);
	Utype.set("WeaponSwapTimestamp", &Player::weapon_swap_Timestamp);
	Utype.set("SprintDelayTimestamp", &Player::sprint_delay_Timestamp);
	Utype.set("SprintStartTimestamp", &Player::sprint_start_Timestamp);
	Utype.set("JumpRefreshTimestamp", &Player::jump_refresh_Timestamp);
	Utype.set("AllySquadHandle", &Player::ally_squad_handle);
	Utype.set("EscortSquadHandle", &Player::escort_squad_handle);
	Utype.set("CheckSquadsTimer", &Player::check_squads_timer);
	Utype.set("PathfindInfo", &Player::pathfind_info);
	//Utype.set("BloodDecals", &Player::);
	Utype.set("BloodDecalsFadeIndex", &Player::blood_decals_fade_index);
	//Utype.set("ActivityInventorySaveFile", &Player::activity_inventory_save_file);
	Utype.set("ActivityInventoryBuffer", sol::property([](Player& Self) { return std::ref(Self.activity_inventory_buffer); })); //Todo: Check if this should be a string.
	//Utype.set("ActivityInventoryBuffer", &Player::activity_inventory_buffer); //Size 1024 array of char. Frankly not sure if this is supposed to be a string or an array of numbers. Gotta check in the debugger
	Utype.set("ZoomCancelTimestamp", &Player::zoom_cancel_Timestamp);
	Utype.set("NonInventoryItemHandle", &Player::non_inventory_item_handle);
	Utype.set("LastVehicleDriven", &Player::last_vehicle_driven);
	Utype.set("QuickTurnOrient", &Player::quick_turn_orient);
	Utype.set("QuickTurnSpeed", &Player::quick_turn_speed);
	Utype.set("Metadata", &Player::Metadata);
	Utype.set("RadiationTimestamp", &Player::radiation_Timestamp);
	Utype.set("RadiationDamage", &Player::radiation_damage);
	Utype.set("RadiationFoley", &Player::radiation_foley);
	Utype.set("IsStuckTimer", &Player::is_stuck_timer);
	Utype.set("LastStuckPos", &Player::last_stuck_pos);
	Utype.set("RagdollOverrideGetUpTime", &Player::ragdoll_override_get_up_time);
	Utype.set("FadeBackpackTime", &Player::fade_backpack_time);
	Utype.set("CommTowerCheckPeriod", &Player::comm_tower_check_period);
	Utype.set("NextRecord", &Player::NextRecord);
	Utype.set("PositionalRecords", sol::property([](Player& Self) { return std::ref(Self.PositionalRecords); })); //Size 8 array of PlayerPositionalRecord
	Utype.set("TrackingPeriod", &Player::TrackingPeriod);
    Utype.set("CastToHuman", [](Player& Self) ->Human*
    {
        return static_cast<Human*>(&Self);
    });
    Utype.set("CastToObject", [](Player& Self) ->Object*
    {
        return static_cast<Object*>(&Self);
    });
	RfgTable.set_usertype("Player", Utype);
}