#include "FunctionManager.h"

//Todo: Split this into multiple functions for organization and to make it easier to find a specific function
/* Initializes rfg function pointers. */
void FunctionManager::RegisterFunctions()
{
    //Todo: Define all of the function offsets in a separate file as macros/constants to make it easier to switch them for different platforms (Steam & GOG)
    RegisterFunction(rfg::CameraStartSlewMode, 0x2D09B0);
    RegisterFunction(rfg::CameraStopSlewMode, 0x2D09C0);
    RegisterFunction(rfg::CameraStartThirdPerson, 0x2CF0C0);
    RegisterFunction(rfg::CameraStartFirstPerson, 0x2C9AC0);
    RegisterFunction(rfg::CameraStopFirstPerson, 0x2C9B60);

    RegisterFunction(rfg::HudHide, 0x441A90);

    RegisterFunction(rfg::GameRenderSetFogEnabled, 0x3C2C70);

    RegisterFunction(rfg::ExplosionCreate, 0x2EC720);
    RegisterFunction(rfg::GraphicsBeginFrame, 0x86DD00);

    RegisterFunction(rfg::FogOfWarClear, 0x43F7F0);
    RegisterFunction(rfg::MouseGenericAutoCentering, 0x1692B0);
    RegisterFunction(rfg::CameraViewDataSetView, 0x2D0290);
    RegisterFunction(rfg::PlayerDoFrame, 0x6D5A80);
    RegisterFunction(rfg::PlayerConstructor, 0x6DECA0);
    RegisterFunction(rfg::CharacterControllerSetPos, 0x4153D0);

    RegisterFunction(rfg::ObjectUpdatePosAndOrient, 0x68C310);

    RegisterFunction(rfg::HavokBodyGetPositionAndOrient, 0x429530);
    RegisterFunction(rfg::HavokBodySetPosition, 0x416EA0);

    RegisterFunction(rfg::HavokBodySetPositionAndOrient, 0x423700);

    RegisterFunction(rfg::HumanUpdatePosAndOrient, 0x69AF70);
    RegisterFunction(rfg::HumanTeleportUnsafe, 0x67C660);

    /*Start of MP Detection Hooks*/
    RegisterFunction(rfg::IsValidEigenGradient, 0x1D0DD0);
    RegisterFunction(rfg::HookDoFrame, 0x3CC750);
    RegisterFunction(rfg::InvertDataItem, 0x497740);
    RegisterFunction(rfg::AllocatorStillValid, 0x4F50B0);
    RegisterFunction(rfg::CsWrapSlice, 0x516D80);
    /*End of MP Detection Hooks*/

    RegisterFunction(rfg::KeenGraphicsResizeRenderSwapchain, 0x86AB20);

    RegisterFunction(rfg::GameseqGetState, 0x3BFCF0);
    RegisterFunction(rfg::GameseqSetState, 0x3D8710);
    RegisterFunction(rfg::GameseqPushState, 0x3D87C0);

    RegisterFunction(rfg::ObjectEnableOutline, 0x310C50);
    RegisterFunction(rfg::ObjectDisableOutline, 0x310C60);
    RegisterFunction(rfg::HumanEnableOutline, 0x62EE80);
    RegisterFunction(rfg::HumanDisableOutline, 0x62EF00);

    RegisterFunction(rfg::TargetOutlineAddObject, 0x735390);

    RegisterFunction(rfg::XrayEffectStart, 0x2E4E30);
    RegisterFunction(rfg::XrayEffectStop, 0x2E4E50);

    RegisterFunction(rfg::UiToolTipsAddTip, 0x4DA4F0);

    RegisterFunction(rfg::ConsoleSetConsoleMode, 0x18CD30);
    RegisterFunction(rfg::ConsoleGetConsoleMode, 0x18CD50);
    RegisterFunction(rfg::ConsoleInit, 0x1CD150);
    RegisterFunction(rfg::ConsoleActivate, 0x18CAC0);
    RegisterFunction(rfg::ConsoleDeactivate, 0x1AF950);

    RegisterFunction(rfg::RlDrawTristrip2dBegin, 0x10DDA0);
    RegisterFunction(rfg::RlDrawString, 0x155BC0);

    RegisterFunction(rfg::IsGamePaused, 0x3C1690);
    RegisterFunction(rfg::WorldDoFrame, 0x540AB0);
    RegisterFunction(rfg::WorldGetObjectName, 0x51C8A0);
    
    RegisterFunction(rfg::WorldGetObjectZoneByIndex, 0x1D9F0);
    RegisterFunction(rfg::WorldGetObjectZoneByGridId, 0x51DA20);

    RegisterFunction(rfg::GsmGetAlertLevel, 0x35D610);
    RegisterFunction(rfg::GsmSetAlertLevel, 0x3AA740);
    RegisterFunction(rfg::GsmGetAlertValue, 0x35D630);
    RegisterFunction(rfg::GsmSetAlertValue, 0x3A44B0);
    RegisterFunction(rfg::GsmGetAlertLevelCap, 0x35D680);
    RegisterFunction(rfg::GsmSetAlertLevelCap, 0x3AA770);
    
    RegisterFunction(rfg::GameRenderGetTodLight, 0x3C2960);
    RegisterFunction(rfg::GameRenderSetTodLight, 0x3C2930);
    
    RegisterFunction(rfg::GameRenderGetTodOnOffValue, 0x3C3000);
    RegisterFunction(rfg::GameRenderSetTodOnOffValue, 0x3C2FF0);
    
    RegisterFunction(rfg::GameRenderSetTodLightColor, 0x3C2990);
    RegisterFunction(rfg::GameClockGetTodPartitioned, 0x3C15C0);
    
    RegisterFunction(rfg::GameClockGetTimeOfDay, 0x3C15E0);
    RegisterFunction(rfg::GameClockSetTime, 0x3C1770);
    
    RegisterFunction(rfg::GameTimeOfDayGetSkyboxTodColors, 0x3DFA10);
    RegisterFunction(rfg::GameTimeOfDayGetWeatherSettings, 0x3C5880);
    RegisterFunction(rfg::GameTimeOfDayGetCloudScrollValues, 0x3C58C0);
    RegisterFunction(rfg::GameTimeOfDayGetNumOrbitals, 0x3D20C0);
    RegisterFunction(rfg::GameTimeOfDayGetCloudLighting, 0x3E31B0);
    RegisterFunction(rfg::GameTimeOfDayGetOrbitalParams, 0x3E5400);
    
    RegisterFunction(rfg::DistrictFromName, 0x46C4D0);
    
    RegisterFunction(rfg::GetWorldZoneByIndex, 0x51D950);
    RegisterFunction(rfg::GetWorldZoneByGridId, 0x51D970);
    RegisterFunction(rfg::GetWorldZoneByName, 0x51D9A0);
    RegisterFunction(rfg::GetWorldZoneByPos, 0x523BA0);
    RegisterFunction(rfg::GetWorldZoneByObjectHandle, 0x523C00);
    
    RegisterFunction(rfg::RfgDynApplyPointImpulse, 0x3124D0);
    RegisterFunction(rfg::RfgDynRepairSphere, 0x314820);
    
    RegisterFunction(rfg::RlCameraRenderBegin, 0x137660);

    RegisterFunction(rfg::GameRenderSetFarClipDistance, 0x3C2C40);
    RegisterFunction(rfg::GameRenderGetFarClipDistance, 0x3C2C50);
    RegisterFunction(rfg::GameRenderGetMainScene, 0x3C2920);

    RegisterFunction(rfg::hkpWorldStepDeltaTime, 0x9E1A70);
    
    RegisterFunction(rfg::ApplicationUpdateTime, 0x5A880);
    
    RegisterFunction(rfg::hkpWorldGetGravity, 0x40D040);
    RegisterFunction(rfg::hkpWorldSetGravity, 0x9E0E20);
    
    RegisterFunction(rfg::VintGetLuaState, 0x620F0);
    RegisterFunction(rfg::LuaDoBuffer, 0x82FD20);
    
    RegisterFunction(rfg::HavokBodyGetPointer, 0x40E870);
    RegisterFunction(rfg::HavokBodyApplyLinearImpulseA, 0x4177A0);
    RegisterFunction(rfg::HavokBodyApplyLinearImpulseB, 0x423C20);
    RegisterFunction(rfg::havok_body_apply_point_impulse, 0x423CA0);

    RegisterFunction(rfg::KeenGraphicsBeginFrame, 0x86DD00);
    
    RegisterFunction(rfg::KeenGetBuildVersionString, 0x58740);
    
    RegisterFunction(rfg::WorldObjectFromHandle, 0x53C050);

    RegisterFunction(rfg::UnusedDcfRagdollPlayer, 0x6D4F30);

    RegisterFunction(rfg::StreamGridSetStreamRadius, 0x51AEB0);
    RegisterFunction(rfg::StreamGridGetStreamRadius, 0x51AFB0);
    RegisterFunction(rfg::StreamGridDoFrame, 0x530FB0);

    RegisterFunction(rfg::CutsceneSpawnVehicle, 0x305D70);
    RegisterFunction(rfg::object_spawn_vehicle, 0x757F40);
    RegisterFunction(rfg::VehicleInfoGetMasterList, 0x768E40);
    RegisterFunction(rfg::SpSpawnVehicle, 0x756420);

    RegisterFunction(rfg::create_new_vehicle_raw, 0x748960);

    RegisterFunction(rfg::load_level_internal, 0x4895F0);
    RegisterFunction(rfg::WorldSetPendingTerritoryLoad, 0x51C4A0);

    RegisterFunction(rfg::peg_load_wrapper, 0x1D1F10);

    RegisterFunction(rfg::string_hash, 0x18FE90);

    RegisterFunction(rfg::human_get_head_pos_orient, 0x69B5D0);
    RegisterFunction(rfg::human_set_render, 0x69B8C0);
    RegisterFunction(rfg::human_hide, 0x69B7E0);
    RegisterFunction(rfg::human_set_opacity_plus_child_items, 0x67E1D0);

    RegisterFunction(rfg::matrix_rotate_around_local_vector, 0x1A4370);

    RegisterFunction(rfg::keen_ImmediateRenderer_beginRenderPass, 0x86C810);

    RegisterFunction(rfg::ui_add_secondary_message, 0x4D8270);
    RegisterFunction(rfg::ui_add_user_message, 0x4D83D0);
    RegisterFunction(rfg::ui_add_msgbox, 0x4F6C70);
    RegisterFunction(rfg::hud_message_change_minor_message, 0x455EE0);
    RegisterFunction(rfg::hud_message_change_user, 0x455F50);
    RegisterFunction(rfg::hud_message_remove_user, 0x444BB0);

    RegisterFunction(rfg::rfgl_find_and_delete_object_mover, 0x324A60);
    RegisterFunction(rfg::rfgl_find_and_delete_debris_object, 0x324B90);

    RegisterFunction(rfg::game_clock_get, 0x3C1480);

    RegisterFunction(rfg::audiolib_cue_get_id, 0x8DC50);
    RegisterFunction(rfg::audiolib_cue_is_id_valid, 0x9F0F0);
    RegisterFunction(rfg::audiolib_cue_play, 0x9F120);
    RegisterFunction(rfg::audiolib_get_listener_pos, 0x83460);
    RegisterFunction(rfg::audiolib_cue_play_3d, 0x9FD60);

    RegisterFunction(rfg::gamestate_gp_process, 0x3EE450);
    RegisterFunction(rfg::game_is_paused, 0x3C1690);

    RegisterFunction(rfg::human_fire_ignite, 0x6D46F0);
    RegisterFunction(rfg::human_fire_stop, 0x655B20);

    RegisterFunction(rfg::rfg_init_stage_2_done, 0x1D56A0);
    RegisterFunction(rfg::rfg_init_stage_2_done_2, 0x1D2480);

    RegisterFunction(rfg::verify_gamesave_exit_notify, 0x3C9430);

    RegisterFunction(rfg::havok_body_force_activate, 0x417730);
    RegisterFunction(rfg::havok_body_set_movable, 0x423DA0);
    RegisterFunction(rfg::havok_body_get_mass, 0x423DD0);

    RegisterFunction(rfg::objective_highlight_add, 0x73A790);
    RegisterFunction(rfg::objective_highlight_remove, 0x73A840);
    RegisterFunction(rfg::objective_highlight_remove_all, 0x73A8B0);

    RegisterFunction(rfg::world_load_territory, 0x541430);

    RegisterFunction(rfg::can_drop_vehicle, 0x756000);

    RegisterFunction(rfg::mission_get_name, 0x39DA30);
    RegisterFunction(rfg::mission_get_description, 0x39DA60);

    RegisterFunction(rfg::vehicle_interaction_request_enter, 0x7B81F0);
    RegisterFunction(rfg::vehicle_interaction_request_exit, 0x7B6060);
    RegisterFunction(rfg::vehicle_engine_start, 0x777540);
    RegisterFunction(rfg::vehicle_engine_stop, 0x777690);
    RegisterFunction(rfg::flyer_engine_start, 0x77E4B0);
    RegisterFunction(rfg::flyer_engine_stop, 0x77E4F0);

    RegisterFunction(rfg::havok_body_get_linear_velocity, 0x4237A0);
    RegisterFunction(rfg::havok_body_get_linear_dampening, 0x423990);
    RegisterFunction(rfg::havok_body_set_linear_velocity, 0x4237E0);
    RegisterFunction(rfg::havok_body_set_linear_dampening, 0x423890);
    RegisterFunction(rfg::havok_body_set_angular_dampening, 0x4238D0);
    RegisterFunction(rfg::havok_body_set_angular_velocity, 0x423910);
    RegisterFunction(rfg::havok_body_get_angular_velocity, 0x417510);
    RegisterFunction(rfg::havok_body_get_angular_dampening, 0x4239D0);

    RegisterFunction(rfg::cf_open, 0x1C27F0);

    RegisterFunction(rfg::effects_template_find, 0x3478B0);
    RegisterFunction(rfg::vfx_effect_create, 0x8BA700);
    RegisterFunction(rfg::vfx_effect_enable_emission, 0x8A3D80);
    RegisterFunction(rfg::vfx_effect_enable_coronas, 0x89EE70);
    RegisterFunction(rfg::vfx_effect_update, 0x8B8210);

    RegisterFunction(rfg::effects_play, 0x347910);

    RegisterFunction(rfg::squad_definition_from_name, 0x670BA0);
    RegisterFunction(rfg::squad_spawn_parameters_spawn_squad, 0x3B0E00);
    RegisterFunction(rfg::squad_spawn_parameters_constructor, 0x20CCA0);
    RegisterFunction(rfg::squad_spawn_parameters_create_squad, 0x3755E0);

    RegisterFunction(rfg::find_local_spawn_region, 0x37FED0);
    RegisterFunction(rfg::find_local_building, 0x390AE0);
    RegisterFunction(rfg::object_squad_spawn_members, 0x694C20);

    RegisterFunction(rfg::gem_post_event, 0x737C10);
    RegisterFunction(rfg::world_create_object_general_mover, 0x318FF0);
    RegisterFunction(rfg::player_create_player_squad, 0x633DD0);
    RegisterFunction(rfg::rfg_snap_to_ground, 0x6EB8D0);
    RegisterFunction(rfg::automobile_honk_horn, 0x775F50);

    RegisterFunction(rfg::chunk_get_base_by_name, 0x528A00);
    RegisterFunction(rfg::object_mover_create_from_chunk, 0x65FA00);

    RegisterFunction(rfg::object_debris_create_havok_body, 0x6172F0);

    RegisterFunction(rfg::obj_prop_block_constructor, 0x638B00);
    RegisterFunction(rfg::rfg_prop_block_set_internal, 0x51A6E0);
    RegisterFunction(rfg::world_create_object_internal, 0x53E6B0);


    RegisterFunction(rfg::obj_auto_props_constructor, 0x368CC0);
    RegisterFunction(rfg::obj_projectile_props_constructor, 0x2058C0);
    RegisterFunction(rfg::str_hash_string, 0x1937D0);
    RegisterFunction(rfg::amb_prop_create, 0x746DB0);
    RegisterFunction(rfg::weapon_fire, 0x7EB270);
}