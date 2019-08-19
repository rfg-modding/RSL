#include "Functions.h"

void DisableCameraCode(DWORD AddressY, DWORD AddressZ) //Takes addresses for instructions affecting y and z. Alternatively x and z may work, since one piece seems to be shared between two coords.
{
	SnippetManager::BackupSnippet("CameraWriteY", AddressY, 8, true);
	SnippetManager::BackupSnippet("CameraWriteZ", AddressZ, 6, true);
}

void RestoreCameraCode()
{
	SnippetManager::RestoreSnippet("CameraWriteY", true);
	SnippetManager::RestoreSnippet("CameraWriteZ", true);
}

void DisableCameraDirectionCode(DWORD Address1, DWORD Address2, DWORD Address3, DWORD Address4, DWORD Address5)
{
	SnippetManager::BackupSnippet("CameraRealOrient1", Address1, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient2", Address2, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient3", Address3, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient4", Address4, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient5", Address5, 6, true);
}

void RestoreCameraDirectionCode()
{
	SnippetManager::RestoreSnippet("CameraRealOrient1", true);
	SnippetManager::RestoreSnippet("CameraRealOrient2", true);
	SnippetManager::RestoreSnippet("CameraRealOrient3", true);
	SnippetManager::RestoreSnippet("CameraRealOrient4", true);
	SnippetManager::RestoreSnippet("CameraRealOrient5", true);
}

void HideHud(bool Hide)
{
	//HudVisible = !HudVisible; //This wasn't working for some odd reason so I just set them manually. Same for HideFog.
	HudHide(Hide);
	if (Hide)
	{
		Globals::HudVisible = false;
	}
	else
	{
		Globals::HudVisible = true;
	}
}

void HideFog(bool Hide)
{
	GameRenderSetFogEnabled(!Hide);
	//FogVisible = !Hide;
	if (Hide)
	{
		Globals::FogVisible = false;
	}
	else
	{
		Globals::FogVisible = true;
	}
}

void ToggleHud()
{
	if (Globals::HudVisible)
	{
		HideHud(true);
		Globals::HudVisible = false;
	}
	else
	{
		HideHud(false);
		Globals::HudVisible = true;
	}
	//HudVisible = !HudVisible; //This wasn't working for some odd reason so I just set them manually.
}

void ToggleFog()
{
	if (Globals::FogVisible)
	{
		HideFog(true);
		Globals::FogVisible = false;
	}
	else
	{
		HideFog(false);
		Globals::FogVisible = true;
	}
	//FogVisible = !FogVisible; //This wasn't working for some odd reason so I just set them manually.
}

F_Camera_Start_Slew_Mode CameraStartSlewMode;
F_Camera_Stop_Slew_Mode CameraStopSlewMode;
F_Camera_Start_Third_Person CameraStartThirdPerson;
F_camera_start_first_person CameraStartFirstPerson;
F_camera_stop_first_person CameraStopFirstPerson;

F_Camera_First_Person_Pre_Process CameraFirstPersonPreProcess;
F_camera_free_system_init CameraFreeSystemInit;
F_camera_free_mode_init CameraFreeModeInit;

F_Interface_Debug_Mode_Activate InterfaceDebugModeActivate;
F_Keen_Debug_WriteToLogFile KeenDebugWriteToLogFile;
F_Hud_Display_Distance HudDisplayDistance;

F_console_set_console_mode ConsoleSetConsoleMode;
F_console_get_console_mode ConsoleGetConsoleMode;
F_Console_Init ConsoleInit;
F_Console_Activate ConsoleActivate;
F_Console_Deactivate ConsoleDeactivate;

F_InvertDataItem InvertDataItem;
F_Console_Printf ConsolePrintf;
F_Console_Display_Help ConsoleDisplayHelp;
F_Console_Command_Enable ConsoleCommandEnable;
F_Console_Do_Command ConsoleDoCommand;

F_Game_Print_Screen GamePrintScreen;

F_console_chat_printf ConsoleChatPrintf;
F_unused_dcf_r_show_mem_usage UnusedDcfRShowMemUsage;
F_rfg_dyn_get_active_destruction_frame RfgDynGetActiveDestructionFrame;
F_rfg_dyn_reset_destruction_frame RfgDynResetDestructionFrame;
F_rfg_dyn_system_shutdown RfgDynSystemShutdown;
F_get_screen_width GetScreenWidth;
F_console_is_active ConsoleIsActive;
F_AllocatorStillValid AllocatorStillValid;
F_debug_spew_projectile DebugSpewProjectile;
F_debug_spew_game_io DebugSpewGameIo;
F_rl_render_lib_get_metrics RlRenderLibGetMetrics;
F_profile_dump_info ProfileDumpInfo;
F_vint_render_text VintRenderText;
F_xray_effect_start XrayEffectStart;
F_xray_effect_stop XrayEffectStop;

F_key_down KeyDown;
F_game_render_set_bloom_exposure_factor GameRenderSetBloomExposureFactor;
F_game_render_set_hdr_state GameRenderSetHdrState;
F_game_render_2d_text GameRender2dText;
F_ui_add_debug_text UiAddDebugText;
F_get_depth_of_field_enabled GetDepthOfFieldEnabled;
F_set_depth_of_field_enabled SetDepthOfFieldEnabled;
//F_character_controller_set_pos CharacterControllerSetPos; //IDA shows this as using __thiscall, but using that causes the game to immediately crash
F_fog_of_war_clear FogOfWarClear;

F_Hud_Hide HudHide;
F_game_render_set_fog_enabled GameRenderSetFogEnabled;

F_explosion_create ExplosionCreate;
F_keen_graphics_beginframe GraphicsBeginFrame;
F_MouseGenericAutoCentering MouseGenericAutoCentering;
F_CameraViewDataSetView CameraViewDataSetView;
F_PlayerDoFrame PlayerDoFrame;
F_PlayerConstructor PlayerConstructor;
F_CharacterControllerSetPos CharacterControllerSetPos;

F_ObjectUpdatePosAndOrient ObjectUpdatePosAndOrient;

F_HavokBodySetPosition HavokBodySetPosition;
F_HavokBodyGetPositionAndOrient HavokBodyGetPositionAndOrient;

F_HavokBodySetPositionAndOrient HavokBodySetPositionAndOrient;

F_HumanUpdatePosAndOrient HumanUpdatePosAndOrient;
F_HumanTeleportUnsafe HumanTeleportUnsafe;
//F_HumanTeleport HumanTeleport;

F_HookDoFrame HookDoFrame;

F_KeenGraphicsResizeRenderSwapchain KeenGraphicsResizeRenderSwapchain;
F_GameseqGetState GameseqGetState;
F_GameseqSetState GameseqSetState;
F_GameseqPushState GameseqPushState;

F_ObjectEnableOutline ObjectEnableOutline;
F_ObjectDisableOutline ObjectDisableOutline;
F_HumanEnableOutline HumanEnableOutline;
F_HumanDisableOutline HumanDisableOutline;
F_TargetOutlineAddObject TargetOutlineAddObject;

F_ui_tool_tips_add_tip UiToolTipsAddTip;

F_rl_draw_tristrip_2d_begin RlDrawTristrip2dBegin;
F_rl_draw_string RlDrawString;

F_is_game_paused IsGamePaused;
F_world_do_frame WorldDoFrame;
F_world_get_object_name WorldGetObjectName;

F_world_get_object_zone_by_index WorldGetObjectZoneByIndex;
F_world_get_object_zone_by_grid_id WorldGetObjectZoneByGridId;

F_gsm_get_alert_level GsmGetAlertLevel;
F_gsm_set_alert_level GsmSetAlertLevel;

F_gsm_get_alert_value GsmGetAlertValue;
F_gsm_set_alert_value GsmSetAlertValue;

F_gsm_get_alert_level_cap GsmGetAlertLevelCap;
F_gsm_set_alert_level_cap GsmSetAlertLevelCap;

F_game_render_get_TOD_light GameRenderGetTodLight;
F_game_render_set_TOD_light GameRenderSetTodLight;

F_game_render_get_tod_on_off_value GameRenderGetTodOnOffValue;
F_game_render_set_tod_on_off_value GameRenderSetTodOnOffValue;

F_game_render_set_TOD_light_color GameRenderSetTodLightColor;

F_game_clock_get_tod_partitioned GameClockGetTodPartitioned;

F_game_clock_get_time_of_day GameClockGetTimeOfDay;
F_game_clock_set_time GameClockSetTime;

F_game_time_of_day_get_skybox_tod_colors GameTimeOfDayGetSkyboxTodColors;
F_game_time_of_day_get_weather_settings GameTimeOfDayGetWeatherSettings;
F_game_time_of_day_get_cloud_scroll_values GameTimeOfDayGetCloudScrollValues;
F_game_time_of_day_get_num_orbitals GameTimeOfDayGetNumOrbitals;
F_game_time_of_day_get_cloud_lighting GameTimeOfDayGetCloudLighting;
F_game_time_of_day_get_orbital_params GameTimeOfDayGetOrbitalParams;

F_district_from_name DistrictFromName;

F_get_world_zone_by_index GetWorldZoneByIndex;
F_get_world_zone_by_grid_id GetWorldZoneByGridId;
F_get_world_zone_by_name GetWorldZoneByName;
F_get_world_zone_by_pos GetWorldZoneByPos;
F_get_world_zone_by_object_handle GetWorldZoneByObjectHandle;

F_rfg_dyn_apply_point_impulse RfgDynApplyPointImpulse;
F_rfg_dyn_repair_sphere RfgDynRepairSphere;

F_IsValidEigenGradient IsValidEigenGradient;

Human* CastObjectToHuman(Object* ObjectPtr) { return static_cast<Human*>(ObjectPtr); }
Player* CastObjectToPlayer(Object* ObjectPtr) { return static_cast<Player*>(ObjectPtr); }
obj_zone* CastObjectToObjZone(Object* ObjectPtr) { return static_cast<obj_zone*>(ObjectPtr); }
district* CastObjectToDistrict(Object* ObjectPtr) { return static_cast<district*>(ObjectPtr); }

F_rl_camera_render_begin RlCameraRenderBegin;

F_game_render_set_far_clip_distance GameRenderSetFarClipDistance;
F_game_render_get_far_clip_distance GameRenderGetFarClipDistance;
F_game_render_get_main_scene GameRenderGetMainScene;

F_hkpWorld_stepDeltaTime hkpWorldStepDeltaTime;
F_ApplicationUpdateTime ApplicationUpdateTime;

F_hkpWorldGetGravity hkpWorldGetGravity;
F_hkpWorldSetGravity hkpWorldSetGravity;

F_vint_lua_get_state VintGetLuaState;
F_lua_dobuffer LuaDoBuffer;

F_havok_body_get_pointer HavokBodyGetPointer;
F_havok_body_apply_linear_impulse_A HavokBodyApplyLinearImpulseA;
F_havok_body_apply_linear_impulse_B HavokBodyApplyLinearImpulseB;

F_keen_graphics_beginFrame KeenGraphicsBeginFrame;

F_keen_get_build_version_string KeenGetBuildVersionString;

F_WorldObjectFromHandle WorldObjectFromHandle;

F_unused_dcf_ragdoll_player UnusedDcfRagdollPlayer;

F_StreamGridSetStreamRadius StreamGridSetStreamRadius;
F_StreamGridGetStreamRadius StreamGridGetStreamRadius;
F_StreamGridDoFrame StreamGridDoFrame;
F_CsWrapSlice CsWrapSlice;


F_cutscene_spawn_vehicle CutsceneSpawnVehicle;
//F_object_spawn_vehicle ObjectSpawnVehicle;
F_vehicle_info_get_master_list VehicleInfoGetMasterList;
F_sp_spawn_vehicle SpSpawnVehicle;
F_create_new_vehicle create_new_vehicle_raw;

F_load_level_internal load_level_internal;

void LoadLevelWrapper(std::string Filename, bool NewGame, bool SingleZone)
{
    const char* FilenameAsCharPtr = Filename.c_str();

    __asm mov esi, FilenameAsCharPtr;

    load_level_internal(NewGame, SingleZone);
}

F_WorldSetPendingTerritoryLoad WorldSetPendingTerritoryLoad;

F_peg_load_wrapper peg_load_wrapper;

F_string_hash string_hash;

F_object_spawn_vehicle object_spawn_vehicle;

F_human_get_head_pos_orient human_get_head_pos_orient;
F_human_set_render human_set_render;
F_human_hide human_hide;
F_human_set_opacity_plus_child_items human_set_opacity_plus_child_items;

F_matrix_rotate_around_local_vector matrix_rotate_around_local_vector;

F_keen_ImmediateRenderer_beginRenderPass keen_ImmediateRenderer_beginRenderPass;

F_ui_add_secondary_message ui_add_secondary_message;
F_ui_add_user_message ui_add_user_message;
F_ui_add_msgbox ui_add_msgbox;
F_hud_message_change_minor_message hud_message_change_minor_message;
F_hud_message_change_user hud_message_change_user;
F_hud_message_remove_user hud_message_remove_user;

F_rfgl_find_and_delete_object_mover rfgl_find_and_delete_object_mover;
F_rfgl_find_and_delete_debris_object rfgl_find_and_delete_debris_object;

F_game_clock_get game_clock_get;

F_audiolib_cue_get_id audiolib_cue_get_id;
F_audiolib_cue_is_id_valid audiolib_cue_is_id_valid;
F_audiolib_cue_play audiolib_cue_play;
F_audiolib_get_listener_pos audiolib_get_listener_pos;
F_audiolib_cue_play_3d audiolib_cue_play_3d;