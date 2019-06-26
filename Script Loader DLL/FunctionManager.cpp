#include "FunctionManager.h"

/* Initializes rfg function pointers. */
void FunctionManager::Initialize()
{
    RegisterFunction(Camera_Start_Slew_Mode, 0x2D09B0);
    RegisterFunction(Camera_Stop_Slew_Mode, 0x2D09C0);
    RegisterFunction(Camera_Start_Third_Person, 0x2CF0C0);
    RegisterFunction(camera_start_first_person, 0x2C9AC0);
    RegisterFunction(camera_stop_first_person, 0x2C9B60);

    RegisterFunction(Hud_Hide, 0x441A90);

    RegisterFunction(game_render_set_fog_enabled, 0x3C2C70);

    RegisterFunction(ExplosionCreate, 0x2EC720);
    RegisterFunction(GraphicsBeginFrame, 0x86DD00);

    RegisterFunction(fog_of_war_clear, 0x43F7F0);
    RegisterFunction(MouseGenericAutoCentering, 0x1692B0);
    RegisterFunction(CameraViewDataSetView, 0x2D0290);
    RegisterFunction(PlayerDoFrame, 0x6D5A80);
    RegisterFunction(PlayerConstructor, 0x6DECA0);
    RegisterFunction(CharacterControllerSetPos, 0x4153D0);

    RegisterFunction(ObjectUpdatePosAndOrient, 0x68C310);

    RegisterFunction(HavokBodyGetPositionAndOrient, 0x429530);
    RegisterFunction(HavokBodySetPosition, 0x416EA0);

    RegisterFunction(HavokBodySetPositionAndOrient, 0x423700);

    RegisterFunction(HumanUpdatePosAndOrient, 0x69AF70);
    RegisterFunction(HumanTeleportUnsafe, 0x67C660);

    /*Start of MP Detection Hooks*/
    RegisterFunction(IsValidGameLinkLobbyKaiko, 0x1D0DD0);
    RegisterFunction(GameMusicMultiplayerStart, 0x3CC750);
    RegisterFunction(InitMultiplayerDataItemRespawn, 0x497740);
    RegisterFunction(HudUiMultiplayerProcess, 0x4F50B0);
    RegisterFunction(HudUiMultiplayerEnter, 0x516D80);
    /*End of MP Detection Hooks*/

    RegisterFunction(KeenGraphicsResizeRenderSwapchain, 0x86AB20);

    RegisterFunction(GameseqGetState, 0x3BFCF0);

    RegisterFunction(ObjectEnableOutline, 0x310C50);
    RegisterFunction(ObjectDisableOutline, 0x310C60);
    RegisterFunction(HumanEnableOutline, 0x62EE80);
    RegisterFunction(HumanDisableOutline, 0x62EF00);

    RegisterFunction(TargetOutlineAddObject, 0x735390);

    RegisterFunction(xray_effect_start, 0x2E4E30);
    RegisterFunction(xray_effect_stop, 0x2E4E50);

    RegisterFunction(UiToolTipsAddTip, 0x4DA4F0);

    RegisterFunction(console_set_console_mode, 0x18CD30);
    RegisterFunction(console_get_console_mode, 0x18CD50);
    RegisterFunction(Console_Init, 0x1CD150);
    RegisterFunction(Console_Activate, 0x18CAC0);
    RegisterFunction(Console_Deactivate, 0x1AF950);

    RegisterFunction(rl_draw_tristrip_2d_begin, 0x10DDA0);
    RegisterFunction(rl_draw_string, 0x155BC0);

    RegisterFunction(IsGamePaused, 0x3C1690);
    RegisterFunction(world_do_frame, 0x540AB0);
    RegisterFunction(world_get_object_name, 0x51C8A0);
    
    RegisterFunction(world_get_object_zone_by_index, 0x1D9F0);
    RegisterFunction(world_get_object_zone_by_grid_id, 0x51DA20);

    RegisterFunction(gsm_get_alert_level, 0x35D610);
    RegisterFunction(gsm_set_alert_level, 0x3AA740);
    RegisterFunction(gsm_get_alert_value, 0x35D630);
    RegisterFunction(gsm_set_alert_value, 0x3A44B0);
    RegisterFunction(gsm_get_alert_level_cap, 0x35D680);
    RegisterFunction(gsm_set_alert_level_cap, 0x3AA770);
    
    RegisterFunction(game_render_get_TOD_light, 0x3C2960);
    RegisterFunction(game_render_set_TOD_light, 0x3C2930);
    
    RegisterFunction(game_render_get_tod_on_off_value, 0x3C3000);
    RegisterFunction(game_render_set_tod_on_off_value, 0x3C2FF0);
    
    RegisterFunction(game_render_set_TOD_light_color, 0x3C2990);
    RegisterFunction(game_clock_get_tod_partitioned, 0x3C15C0);
    
    RegisterFunction(game_clock_get_time_of_day, 0x3C15E0);
    RegisterFunction(game_clock_set_time, 0x3C1770);
    
    RegisterFunction(game_time_of_day_get_skybox_tod_colors, 0x3DFA10);
    RegisterFunction(game_time_of_day_get_weather_settings, 0x3C5880);
    RegisterFunction(game_time_of_day_get_cloud_scroll_values, 0x3C58C0);
    RegisterFunction(game_time_of_day_get_num_orbitals, 0x3D20C0);
    RegisterFunction(game_time_of_day_get_cloud_lighting, 0x3E31B0);
    RegisterFunction(game_time_of_day_get_orbital_params, 0x3E5400);
    
    RegisterFunction(district_from_name, 0x46C4D0);
    
    RegisterFunction(get_world_zone_by_index, 0x51D950);
    RegisterFunction(get_world_zone_by_grid_id, 0x51D970);
    RegisterFunction(get_world_zone_by_name, 0x51D9A0);
    RegisterFunction(get_world_zone_by_pos, 0x523BA0);
    RegisterFunction(get_world_zone_by_object_handle, 0x523C00);
    
    RegisterFunction(rfg_dyn_apply_point_impulse, 0x3124D0);
    RegisterFunction(rfg_dyn_repair_sphere, 0x314820);
    
    RegisterFunction(rl_camera_render_begin, 0x137660);

    RegisterFunction(game_render_set_far_clip_distance, 0x3C2C40);
    RegisterFunction(game_render_get_far_clip_distance, 0x3C2C50);
    RegisterFunction(game_render_get_main_scene, 0x3C2920);

    RegisterFunction(hkpWorld_stepDeltaTime, 0x9E1A70);
    
    RegisterFunction(ApplicationUpdateTime, 0x5A880);
    
    RegisterFunction(hkpWorldGetGravity, 0x40D040);
    RegisterFunction(hkpWorldSetGravity, 0x9E0E20);
    
    RegisterFunction(VintGetLuaState, 0x620F0);
    RegisterFunction(LuaDoBuffer, 0x82FD20);
    
    RegisterFunction(HavokBodyGetPointer, 0x40E870);
    RegisterFunction(HavokBodyApplyLinearImpulseA, 0x4177A0);
    RegisterFunction(HavokBodyApplyLinearImpulseB, 0x423C20);
    
    RegisterFunction(KeenGraphicsBeginFrame, 0x86DD00);
    
    RegisterFunction(KeenGetBuildVersionString, 0x58740);
    
    RegisterFunction(WorldObjectFromHandle, 0x53C050);
}