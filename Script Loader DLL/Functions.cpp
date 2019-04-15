#include "Functions.h"

Player* GlobalPlayerPtr;
World* GlobalRfgWorldPtr = nullptr;
rl_light* GlobalTODLightPtr = nullptr;
rl_camera* GlobalRlCameraPtr = nullptr;
rl_renderer* GlobalRlRendererPtr = nullptr;
rl_render_lib* GlobalRlRenderLibPtr = nullptr;
rl_state_manager* GlobalRlStateManagerPtr = nullptr;
rl_scene* GlobalMainScenePtr = nullptr;
rl_scene_renderer* GlobalMainSceneRendererPtr = nullptr;
rl_camera* GlobalMainSceneCameraPtr = nullptr;
hkpWorld* GlobalhkpWorldPtr = nullptr;

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
	Hud_Hide(Hide);
	if (Hide)
	{
		HudVisible = false;
	}
	else
	{
		HudVisible = true;
	}
}

void HideFog(bool Hide)
{
	game_render_set_fog_enabled(!Hide);
	//FogVisible = !Hide;
	if (Hide)
	{
		FogVisible = false;
	}
	else
	{
		FogVisible = true;
	}
}

void ToggleHud()
{
	if (HudVisible)
	{
		HideHud(true);
		HudVisible = false;
	}
	else
	{
		HideHud(false);
		HudVisible = true;
	}
	//HudVisible = !HudVisible; //This wasn't working for some odd reason so I just set them manually.
}

void ToggleFog()
{
	if (FogVisible)
	{
		HideFog(true);
		FogVisible = false;
	}
	else
	{
		HideFog(false);
		FogVisible = true;
	}
	//FogVisible = !FogVisible; //This wasn't working for some odd reason so I just set them manually.
}

F_Camera_Start_Slew_Mode Camera_Start_Slew_Mode;
F_Camera_Stop_Slew_Mode Camera_Stop_Slew_Mode;
F_Interface_Debug_Mode_Activate Interface_Debug_Mode_Activate;
F_Keen_Debug_WriteToLogFile Keen_Debug_WriteToLogFile;
F_Hud_Display_Distance Hud_Display_Distance;

F_console_set_console_mode console_set_console_mode;
F_console_get_console_mode console_get_console_mode;
F_Console_Init Console_Init;
F_Console_Activate Console_Activate;
F_Console_Deactivate Console_Deactivate;

F_Console_Printf Console_Printf;
F_Console_Display_Help Console_Display_Help;
F_Console_Command_Enable Console_Command_Enable;
F_Console_Do_Command Console_Do_Command;
F_Camera_First_Person_Pre_Process Camera_First_Person_Pre_Process;
F_Camera_Start_Third_Person Camera_Start_Third_Person;
F_Game_Print_Screen Game_Print_Screen;
F_camera_free_system_init camera_free_system_init;
F_camera_free_mode_init camera_free_mode_init;
F_console_chat_printf console_chat_printf;
F_unused_dcf_r_show_mem_usage unused_dcf_r_show_mem_usage;
F_rfg_dyn_get_active_destruction_frame rfg_dyn_get_active_destruction_frame;
F_rfg_dyn_reset_destruction_frame rfg_dyn_reset_destruction_frame;
F_rfg_dyn_system_shutdown rfg_dyn_system_shutdown;
F_get_screen_width get_screen_width;
F_console_is_active console_is_active;
F_debug_spew_projectile debug_spew_projectile;
F_debug_spew_game_io debug_spew_game_io;
F_rl_render_lib_get_metrics rl_render_lib_get_metrics;
F_profile_dump_info profile_dump_info;
F_vint_render_text vint_render_text;
F_xray_effect_start xray_effect_start;
F_xray_effect_stop xray_effect_stop;
F_camera_start_first_person camera_start_first_person;
F_camera_stop_first_person camera_stop_first_person;
F_key_down key_down;
F_game_render_set_bloom_exposure_factor game_render_set_bloom_exposure_factor;
F_game_render_set_hdr_state game_render_set_hdr_state;
F_game_render_2d_text game_render_2d_text;
F_ui_add_debug_text ui_add_debug_text;
F_get_depth_of_field_enabled get_depth_of_field_enabled;
F_set_depth_of_field_enabled set_depth_of_field_enabled;
F_character_controller_set_pos character_controller_set_pos; //IDA shows this as using __thiscall, but using that causes the game to immediately crash
F_fog_of_war_clear fog_of_war_clear;

F_Hud_Hide Hud_Hide;
F_game_render_set_fog_enabled game_render_set_fog_enabled;

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

/*Start of MP Detection Hooks*/
F_IsValidGameLinkLobbyKaiko IsValidGameLinkLobbyKaiko;
F_GameMusicMultiplayerStart GameMusicMultiplayerStart;
F_InitMultiplayerDataItemRespawn InitMultiplayerDataItemRespawn;
F_HudUiMultiplayerProcess HudUiMultiplayerProcess;
F_HudUiMultiplayerEnter HudUiMultiplayerEnter;
/*End of MP Detection Hooks*/

F_KeenGraphicsResizeRenderSwapchain KeenGraphicsResizeRenderSwapchain;
F_GameseqGetState GameseqGetState;

F_ObjectEnableOutline ObjectEnableOutline;
F_ObjectDisableOutline ObjectDisableOutline;
F_HumanEnableOutline HumanEnableOutline;
F_HumanDisableOutline HumanDisableOutline;
F_TargetOutlineAddObject TargetOutlineAddObject;

F_ui_tool_tips_add_tip UiToolTipsAddTip;

F_rl_draw_tristrip_2d_begin rl_draw_tristrip_2d_begin;
F_rl_draw_string rl_draw_string;

F_is_game_paused IsGamePaused;
F_world_do_frame world_do_frame;
F_world_get_object_name world_get_object_name;

F_world_get_object_zone_by_index world_get_object_zone_by_index;
F_world_get_object_zone_by_grid_id world_get_object_zone_by_grid_id;

F_gsm_get_alert_level gsm_get_alert_level;
F_gsm_set_alert_level gsm_set_alert_level;

F_gsm_get_alert_value gsm_get_alert_value;
F_gsm_set_alert_value gsm_set_alert_value;

F_gsm_get_alert_level_cap gsm_get_alert_level_cap;
F_gsm_set_alert_level_cap gsm_set_alert_level_cap;

F_game_render_get_TOD_light game_render_get_TOD_light;
F_game_render_set_TOD_light game_render_set_TOD_light;

F_game_render_get_tod_on_off_value game_render_get_tod_on_off_value;
F_game_render_set_tod_on_off_value game_render_set_tod_on_off_value;

F_game_render_set_TOD_light_color game_render_set_TOD_light_color;

F_game_clock_get_tod_partitioned game_clock_get_tod_partitioned;

F_game_clock_get_time_of_day game_clock_get_time_of_day;
F_game_clock_set_time game_clock_set_time;

F_game_time_of_day_get_skybox_tod_colors game_time_of_day_get_skybox_tod_colors;
F_game_time_of_day_get_weather_settings game_time_of_day_get_weather_settings;
F_game_time_of_day_get_cloud_scroll_values game_time_of_day_get_cloud_scroll_values;
F_game_time_of_day_get_num_orbitals game_time_of_day_get_num_orbitals;
F_game_time_of_day_get_cloud_lighting game_time_of_day_get_cloud_lighting;
F_game_time_of_day_get_orbital_params game_time_of_day_get_orbital_params;

F_district_from_name district_from_name;

F_get_world_zone_by_index get_world_zone_by_index;
F_get_world_zone_by_grid_id get_world_zone_by_grid_id;
F_get_world_zone_by_name get_world_zone_by_name;
F_get_world_zone_by_pos get_world_zone_by_pos;
F_get_world_zone_by_object_handle get_world_zone_by_object_handle;

F_rfg_dyn_apply_point_impulse rfg_dyn_apply_point_impulse;
F_rfg_dyn_repair_sphere rfg_dyn_repair_sphere;



Human* CastObjectToHuman(Object* ObjectPtr) { return (Human*)ObjectPtr; }
Player* CastObjectToPlayer(Object* ObjectPtr) { return (Player*)ObjectPtr; }
obj_zone* CastObjectToObjZone(Object* ObjectPtr) { return (obj_zone*)ObjectPtr; }
district* CastObjectToDistrict(Object* ObjectPtr) { return (district*)ObjectPtr; }

F_rl_camera_render_begin rl_camera_render_begin;

F_game_render_set_far_clip_distance game_render_set_far_clip_distance;
F_game_render_get_far_clip_distance game_render_get_far_clip_distance;
F_game_render_get_main_scene game_render_get_main_scene;

F_hkpWorld_stepDeltaTime hkpWorld_stepDeltaTime;
F_ApplicationUpdateTime ApplicationUpdateTime;

F_hkpWorldGetGravity hkpWorldGetGravity;
F_hkpWorldSetGravity hkpWorldSetGravity;