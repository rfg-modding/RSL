#include "PlayerLua.h"
#include "Functions.h"

void Lua::BindUpgradeItem(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<UpgradeItem>
    (
        "UpgradeItem",
        "new", sol::no_constructor,
        "CurrentLevel", &UpgradeItem::current_level,
        "AvailabilityBitfield", &UpgradeItem::availability_bitfield,
        "UnlockedNotifiedBitfield", &UpgradeItem::unlocked_notified_bitfield,
        "NewNotifiedBitfield", &UpgradeItem::new_notified_bitfield
    );
}

void Lua::BindPlayerMetadata(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<PlayerMetadata>
    (
        "PlayerMetadata",
        "new", sol::no_constructor,
        "Salvage", &PlayerMetadata::Salvage,
        "MiningCount", &PlayerMetadata::MiningCount,
        "SupplyCrateCount", &PlayerMetadata::SupplyCrateCount,
        "DistrictHash", &PlayerMetadata::DistrictHash,
        "DistrictTime", &PlayerMetadata::DistrictTime,
        "Upgrades", sol::property([](PlayerMetadata& Self) { return std::ref(Self.upgrades); }), //Size 128 array of UpgradeItem
        "PlayTime", &PlayerMetadata::PlayTime,
        "LastDeathTime", &PlayerMetadata::LastDeathTime
    );
}

void Lua::BindPathfindNavInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<PathfindNavInfo>
    (
        "PathfindNavInfo",
        "new", sol::no_constructor,
        "LastVisitedVehicleNavCellHandle", &PathfindNavInfo::LastVisitedVehicleNavCellHandle,
        "LastVisitedVehicleNavCellUpdateTimer", &PathfindNavInfo::LastVisitedVehicleNavCellUpdateTimer
    );
}

void Lua::BindVehicleEnterStruct(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<VehicleEnterStruct>
    (
        "VehicleEnterStruct",
        "new", sol::no_constructor,
        "VehicleHandle", &VehicleEnterStruct::VehicleHandle,
        "Run", & VehicleEnterStruct::Run
    );
}

void Lua::BindScriptSpecificData(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<ScriptSpecificData>
    (
        "ScriptSpecificData",
        "new", sol::no_constructor,
        "VehicleEnterData", &ScriptSpecificData::VehicleEnterData
    );
}

void Lua::BindPlayerFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<PlayerFlags>
    (
        "PlayerFlags",
        "new", sol::no_constructor,
        "ActionNodeAnimStarted", sol::property(itsy_bitsy::read<PlayerFlags, 0>, itsy_bitsy::write<PlayerFlags, 0>), //uint32 - 1
        "CustomMesh", sol::property(itsy_bitsy::read<PlayerFlags, 1>, itsy_bitsy::write<PlayerFlags, 1>), //uint32 - 1
        "IsLoaded", sol::property(itsy_bitsy::read<PlayerFlags, 2>, itsy_bitsy::write<PlayerFlags, 2>), //uint32 - 1
        "ScriptControlled", sol::property(itsy_bitsy::read<PlayerFlags, 3>, itsy_bitsy::write<PlayerFlags, 3>), //uint32 - 1
        "NeverDie", sol::property(itsy_bitsy::read<PlayerFlags, 4>, itsy_bitsy::write<PlayerFlags, 4>), //uint32 - 1
        "MissionNeverDie", sol::property(itsy_bitsy::read<PlayerFlags, 5>, itsy_bitsy::write<PlayerFlags, 5>), //uint32 - 1
        "DoSprint", sol::property(itsy_bitsy::read<PlayerFlags, 6>, itsy_bitsy::write<PlayerFlags, 6>), //uint32 - 1
        "DisableControls", sol::property(itsy_bitsy::read<PlayerFlags, 7>, itsy_bitsy::write<PlayerFlags, 7>), //uint32 - 1
        "JetpackStarted", sol::property(itsy_bitsy::read<PlayerFlags, 8>, itsy_bitsy::write<PlayerFlags, 8>), //uint32 - 1
        "JetpackReady", sol::property(itsy_bitsy::read<PlayerFlags, 9>, itsy_bitsy::write<PlayerFlags, 9>), //uint32 - 1
        "MovingToAStop", sol::property(itsy_bitsy::read<PlayerFlags, 10>, itsy_bitsy::write<PlayerFlags, 10>), //uint32 - 1
        "QuickTurn", sol::property(itsy_bitsy::read<PlayerFlags, 11>, itsy_bitsy::write<PlayerFlags, 11>), //uint32 - 1
        "CrouchingState", sol::property(itsy_bitsy::read<PlayerFlags, 12>, itsy_bitsy::write<PlayerFlags, 12>), //uint32 - 1
        "WeaponHidden", sol::property(itsy_bitsy::read<PlayerFlags, 13>, itsy_bitsy::write<PlayerFlags, 13>), //uint32 - 1
        "IsStuck", sol::property(itsy_bitsy::read<PlayerFlags, 14>, itsy_bitsy::write<PlayerFlags, 14>), //uint32 - 1
        "CoverFiring", sol::property(itsy_bitsy::read<PlayerFlags, 15>, itsy_bitsy::write<PlayerFlags, 15>), //uint32 - 2
        "CoverLeanup", sol::property(itsy_bitsy::read<PlayerFlags, 16>, itsy_bitsy::write<PlayerFlags, 16>), //uint32 - 1
        "UseCover", sol::property(itsy_bitsy::read<PlayerFlags, 17>, itsy_bitsy::write<PlayerFlags, 17>), //uint32 - 1
        "NoReticule", sol::property(itsy_bitsy::read<PlayerFlags, 18>, itsy_bitsy::write<PlayerFlags, 18>), //uint32 - 1
        "NoFineaim", sol::property(itsy_bitsy::read<PlayerFlags, 19>, itsy_bitsy::write<PlayerFlags, 19>), //uint32 - 1
        "CoverSearchForEdge", sol::property(itsy_bitsy::read<PlayerFlags, 20>, itsy_bitsy::write<PlayerFlags, 20>), //uint32 - 1
        "CoverAgainstVehicle", sol::property(itsy_bitsy::read<PlayerFlags, 21>, itsy_bitsy::write<PlayerFlags, 21>), //uint32 - 1
        "InCommTowerRange", sol::property(itsy_bitsy::read<PlayerFlags, 22>, itsy_bitsy::write<PlayerFlags, 22>), //uint32 - 1 
        "CommRangeChecked", sol::property(itsy_bitsy::read<PlayerFlags, 23>, itsy_bitsy::write<PlayerFlags, 23>), //uint32 - 1 
        "PassengerBrake", sol::property(itsy_bitsy::read<PlayerFlags, 24>, itsy_bitsy::write<PlayerFlags, 24>), //uint32 - 1 
        "LocalPlayerHitSomeoneThisFrame", sol::property(itsy_bitsy::read<PlayerFlags, 25>, itsy_bitsy::write<PlayerFlags, 25>), //uint32 - 1 
        "WeaponSwapLock", sol::property(itsy_bitsy::read<PlayerFlags, 26>, itsy_bitsy::write<PlayerFlags, 26>), //uint32 - 1 
        "UnlimitedAmmo", sol::property(itsy_bitsy::read<PlayerFlags, 27>, itsy_bitsy::write<PlayerFlags, 27>), //uint32 - 1 
        "InRadiation", sol::property(itsy_bitsy::read<PlayerFlags, 28>, itsy_bitsy::write<PlayerFlags, 28>), //uint32 - 1 
        "RagdollOnNextExplosion", sol::property(itsy_bitsy::read<PlayerFlags, 29>, itsy_bitsy::write<PlayerFlags, 29>), //uint32 - 1 
        "LeavingSquadMemberBehind", sol::property(itsy_bitsy::read<PlayerFlags, 30>, itsy_bitsy::write<PlayerFlags, 30>), //uint32 - 1 
        "IsWaitingForHostageVehicleExit", sol::property(itsy_bitsy::read<PlayerFlags, 31>, itsy_bitsy::write<PlayerFlags, 31>), //uint32 - 1 
        "BackpackFadeOut", sol::property(itsy_bitsy::read<PlayerFlags, 32>, itsy_bitsy::write<PlayerFlags, 32>), //uint32 - 1 
        "BackpackFadeIn", sol::property(itsy_bitsy::read<PlayerFlags, 33>, itsy_bitsy::write<PlayerFlags, 33>), //uint32 - 1 
        //"MpDisplayRespawnMsg", sol::property(itsy_bitsy::read<PlayerFlags, 34>, itsy_bitsy::write<PlayerFlags, 34>), //uint32 - 1 
        //"MpRemotePlayerFiredThisFrame", sol::property(itsy_bitsy::read<PlayerFlags, 35>, itsy_bitsy::write<PlayerFlags, 35>), //uint32 - 1 
        //"MpIgnorePlayerForRespawnCollisions", sol::property(itsy_bitsy::read<PlayerFlags, 36>, itsy_bitsy::write<PlayerFlags, 36>), //uint32 - 1
        //"MpLostHP", sol::property(itsy_bitsy::read<PlayerFlags, 37>, itsy_bitsy::write<PlayerFlags, 37>), //uint32 - 1 
        //"MpHitSomeoneThisNetworkFrame", sol::property(itsy_bitsy::read<PlayerFlags, 38>, itsy_bitsy::write<PlayerFlags, 38>), //uint32 - 1 
        //"MpRemotePlayerChargedThisFrame", sol::property(itsy_bitsy::read<PlayerFlags, 39>, itsy_bitsy::write<PlayerFlags, 39>), //uint32 - 1 
        //"MpLocalPlayerCanSeeMe", sol::property(itsy_bitsy::read<PlayerFlags, 40>, itsy_bitsy::write<PlayerFlags, 40>), //uint32 - 1 
        //"MpHasReloaded", sol::property(itsy_bitsy::read<PlayerFlags, 41>, itsy_bitsy::write<PlayerFlags, 41>), //uint32 - 1 
        //"MpRemovingPlayer", sol::property(itsy_bitsy::read<PlayerFlags, 42>, itsy_bitsy::write<PlayerFlags, 42>), //uint32 - 1 
        "WaitingForLockerExit", sol::property(itsy_bitsy::read<PlayerFlags, 43>, itsy_bitsy::write<PlayerFlags, 43>) //uint32 - 1 
    );
}

void Lua::BindUsableObject(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<UseableObject>
    (
        "UseableObject",
        "new", sol::no_constructor,
        "Handle", &UseableObject::handle,
        "ActionType", &UseableObject::action_type,
        "ActionIcon", &UseableObject::action_icon,
        "DotProduct", &UseableObject::dot_prod,
        "DistanceSquared", &UseableObject::dist_squared
        //"ActionCallback", &UseableObject::action_callback //Function ptr
    );
}

void Lua::BindPlayer(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<Player>
    (
        "Player",
        sol::base_classes, sol::bases<Human, Object>(),
        "FrametimeMultiplier", &Player::FrametimeMultiplier,
        "ActionObject", &Player::action_object,
        "ActionObjectTimestamp", &Player::action_object_timestamp,
        "LastFireTime", &Player::last_fire_time,
        //"MpActionObjectHandle", &Player::mp_action_object_handle,
        "RadioID", &Player::radio_id,
        "TagTrigger", &Player::tag_trigger,
        "TagSequence", &Player::tag_seq,
        "TagTimer", &Player::tag_timer,
        "TagEffect", &Player::TagEffect,
        "HudMessage", &Player::hud_message,
        "HavokFilterGroup", &Player::havok_filter_group,
        "AimTarget", &Player::aim_target,
        "PenetratingAimTarget", &Player::penetrating_aim_target,
        "PenetratingAimPos", &Player::penetrating_aim_pos,
        "AimTargetDuration", &Player::aim_target_duration,
        "HeatSeekingTarget", &Player::heat_seeking_target,
        "AimPos", &Player::aim_pos,
        "CombatTargetUpdateTime", &Player::combat_target_update_time,
        "RemoteChargeTime", &Player::remote_charge_time,
        "DoingRemoteCharge", &Player::doing_remote_charge,
        "ZoomState", &Player::zoom_state,
        "PreviousZoomState", &Player::previous_zoom_state,
        "CoverVector", &Player::cover_vector,
        "CoverVectorRight", &Player::cover_vector_right,
        "EnteringCover", &Player::entering_cover,
        "ExitingCover", &Player::exiting_cover,
        "CoverMoveVel", &Player::cover_move_vel,
        "CoverApproachingEdge", &Player::cover_approaching_edge,
        "CoverApproachingEdgeTS", &Player::cover_approaching_edge_ts,
        "CoverEdgeHitPos", &Player::cover_edge_hit_pos,
        "CoverEdgeMissPos", &Player::cover_edge_miss_pos,
        "ThrownWeaponCheckPos", &Player::thrown_weapon_check_pos,
        "CombatMoveQueue", &Player::combat_move_queue,
        "PreviousBulletHit", &Player::previous_bullet_hit,
        "JetpackFuelPercent", &Player::JetpackFuelPercent,
        "JetpackFoley", &Player::JetpackFoley,
        "JetpackEffect", &Player::JetpackEffect,
        "AllowRagdoll", &Player::AllowRagdoll,
        "PlayerFlags", &Player::PFlags,
        "HoldObjectAvailable", &Player::hold_object_available,
        "HoldObjectHandle", &Player::hold_object_handle,
        //"AbandonedVehicles", &Player::); //Size 3 array of uint
        "NumAbandonedVehicles", &Player::num_abandoned_vehicles,
        //"CustomVehicles", &Player::custom_vehicles); //Size 50 array of CustomVehicle
        //"CustomVehicleList", &Player::custom_vehicle_list);
        //"CustomVehicleFreeList", &Player::custom_vehicle_free_list);
        //"NumCustomVehicles", &Player::);
        "DeadTimestamp", &Player::dead_timestamp,
        "MatFxHandle", sol::property([](Player& Self) { return std::ref(Self.mat_fx_handle); }), //Size 16 array of uint
        "CurrentMatFx", &Player::current_mat_fx,
        "ScriptMode", &Player::script_mode,
        "ScriptData", &Player::script_data,
        //"Backpack", &Player::Backpack); Type of MultiObjectBackpack
        //"MpRespawnBackpackType", &Player::mp_respawn_backpack_type);
        //"MpCurrentCommand", &Player::mp_current_command);
        //"MpCameraPos", &Player::);
        //"MpCameraOrient", &Player::);
        //"MpCameraAngularVelocity", &Player::);
        //"MpDesiredWeaponSlot", &Player::);
        //"MpLastRespawnTime", &Player::);
        //"MpData", &Player::);
        //"MpDisarmBombHandle", &Player::);
        //"MpSimState", &Player::);
        //"MpLastSpawnPointHandle", &Player::);
        //"MpTimeUntilPlayerCanRespawn", &Player::);
        //"MpTimeUntilPlayerLeavesInvulnerability", &Player::);
        //"MpSwapBackpack", &Player::);
        //"MpPlayerDamageHistory", &Player::);
        //"MpLadderState", &Player::);
        //"MpRagdollForce", &Player::);
        //"MpRagdollForceTimeout", &Player::);
        //"MpEdgeCorrectionInfo", &Player::);
        //"MpBlockedInfo", &Player::);
        //"MpRagdollLinearVelocityAggregate", &Player::);
        //"MpRagdollAngularVelocityAggregate", &Player::);
        //"MpSimulationTimeUsed", &Player::);
        //"MpSimulationTimeAccumulated", &Player::);
        //"MpSimulationTimeExtrapolated", &Player::);
        "JetpackUseLogHandle", &Player::jetpack_use_log_handle,
        "BackpackEquipLogHandle", &Player::backpack_equip_log_handle,
        "DistrictLogHandle", &Player::district_log_handle,
        "CameraBoneTransform", &Player::camera_bone_transform,
        "MovementVelocity", &Player::movement_velocity,
        "DirectControlDir", &Player::direct_control_dir,
        "DirectControlVel", &Player::direct_control_vel,
        "CoverCollisionNormal", &Player::cover_collision_normal,
        "LastFrameCoverCollisionNormal", &Player::last_frame_cover_collision_normal,
        "CoverTestQueue", &Player::cover_test_queue,
        "CoverDelayTS", &Player::cover_exit_delay_ts,
        "CoverEnterTS", &Player::cover_enter_ts,
        "CoverExitDelayTS", &Player::cover_exit_delay_ts,
        "CoverDiveCapsule", &Player::cover_dive_capsule,
        "CoverLeanDelay", &Player::cover_lean_delay,
        "CoverRootOffset", &Player::cover_root_offset,
        "SpinebendRootOffset", &Player::spinebend_root_offset,
        "FacialIdle", &Player::facial_idle,
        "FootstepPropagateTime", &Player::footstep_propagate_time,
        "BumpIntoPropagateTime", &Player::bump_into_propagate_time,
        "AmmoBoxHandle", &Player::ammo_box_handle,
        "PathfindTimeOut", &Player::pathfind_time_out,
        "CurrentInterfaceMode", &Player::current_interface_mode,
        "CommonControlsAllowed", &Player::common_controls_allowed,
        "ControlsGeneralAllowed", &Player::controls_general_allowed,
        "ControlsOnFootAllowed", &Player::controls_on_foot_allowed,
        "ControlsDrivingAllowed", &Player::controls_driving_allowed,
        "GeneralActionsAllowed", &Player::general_actions_allowed,
        "WeaponSwapTimestamp", &Player::weapon_swap_Timestamp,
        "SprintDelayTimestamp", &Player::sprint_delay_Timestamp,
        "SprintStartTimestamp", &Player::sprint_start_Timestamp,
        "JumpRefreshTimestamp", &Player::jump_refresh_Timestamp,
        "AllySquadHandle", &Player::ally_squad_handle,
        "EscortSquadHandle", &Player::escort_squad_handle,
        "CheckSquadsTimer", &Player::check_squads_timer,
        "PathfindInfo", &Player::pathfind_info,
        //"BloodDecals", &Player::);
        "BloodDecalsFadeIndex", &Player::blood_decals_fade_index,
        //"ActivityInventorySaveFile", &Player::activity_inventory_save_file,
        "ActivityInventoryBuffer", sol::property([](Player& Self) { return std::ref(Self.activity_inventory_buffer); }), //Todo: Check if this should be a string.
        //"ActivityInventoryBuffer", &Player::activity_inventory_buffer, //Size 1024 array of char. Frankly not sure if this is supposed to be a string or an array of numbers. Gotta check in the debugger
        "ZoomCancelTimestamp", &Player::zoom_cancel_Timestamp,
        "NonInventoryItemHandle", &Player::non_inventory_item_handle,
        "LastVehicleDriven", &Player::last_vehicle_driven,
        "QuickTurnOrient", &Player::quick_turn_orient,
        "QuickTurnSpeed", &Player::quick_turn_speed,
        "Metadata", &Player::Metadata,
        "RadiationTimestamp", &Player::radiation_Timestamp,
        "RadiationDamage", &Player::radiation_damage,
        "RadiationFoley", &Player::radiation_foley,
        "IsStuckTimer", &Player::is_stuck_timer,
        "LastStuckPos", &Player::last_stuck_pos,
        "RagdollOverrideGetUpTime", &Player::ragdoll_override_get_up_time,
        "FadeBackpackTime", &Player::fade_backpack_time,
        "CommTowerCheckPeriod", &Player::comm_tower_check_period,
        "NextRecord", &Player::NextRecord,
        "PositionalRecords", sol::property([](Player& Self) { return std::ref(Self.PositionalRecords); }), //Size 8 array of PlayerPositionalRecord
        "TrackingPeriod", &Player::TrackingPeriod
    );
}