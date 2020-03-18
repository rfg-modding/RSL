/* Functions.h/.cpp contain function pointers for many of rfg's functions. They can be used
 * to call rfg's functions for our own use, and also to hook these functions and expand their
 * behavior. These function pointers are initialized in FunctionManager.cpp. The declarations
 * here are only used to define the inputs, calling conventions, and returns of these functions.
 */

#pragma once
#include "ItsyBitsy.h"

//Todo: Organize these more into sub-files & maybe sub-namespaces

namespace rfg
{
    extern void HideHud(bool Hide);
    extern void HideFog(bool Hide);
    extern void ToggleHud();
    extern void ToggleFog();

    using F_Camera_Start_Slew_Mode = void(__cdecl*)();
    extern F_Camera_Start_Slew_Mode CameraStartSlewMode;

    using F_Camera_Stop_Slew_Mode = void(__cdecl*)();
    extern F_Camera_Stop_Slew_Mode CameraStopSlewMode;

    using F_Interface_Debug_Mode_Activate = void(__cdecl*)();
    extern F_Interface_Debug_Mode_Activate InterfaceDebugModeActivate;

    using F_Keen_Debug_WriteToLogFile = void(__cdecl*)(char* String);
    extern F_Keen_Debug_WriteToLogFile KeenDebugWriteToLogFile;

    using F_Hud_Display_Distance = void(__cdecl*)(bool Value);
    extern F_Hud_Display_Distance HudDisplayDistance;

    using F_HookDoFrame = void(__cdecl*)();
    extern F_HookDoFrame HookDoFrame;

    //.text:009BCD30 rfg.exe:$18CD30 #18C130 <ConsoleSetConsoleMode>
    using F_console_set_console_mode = void(__cdecl*)(vconsole_mode);
    extern F_console_set_console_mode ConsoleSetConsoleMode;

    //.text:009BCD50 rfg.exe:$18CD50 #18C150 <ConsoleGetConsoleMode>
    using F_console_get_console_mode = vconsole_mode(__cdecl*)();
    extern F_console_get_console_mode ConsoleGetConsoleMode;

    using F_Console_Init = void(__cdecl*)(vconsole_config* ConsoleInit);
    extern F_Console_Init ConsoleInit;

    using F_Console_Activate = void(__cdecl*)();
    extern F_Console_Activate ConsoleActivate;

    using F_Console_Deactivate = void(__cdecl*)();
    extern F_Console_Deactivate ConsoleDeactivate;

    using F_Console_Printf = void(__cdecl*)(const char* String);
    extern F_Console_Printf ConsolePrintf;

    using F_Console_Display_Help = void(__cdecl*)();
    extern F_Console_Display_Help ConsoleDisplayHelp;

    using F_Console_Command_Enable = void(__cdecl*)(const char* String, bool Activate);
    extern F_Console_Command_Enable ConsoleCommandEnable;

    using F_Console_Do_Command = void(__cdecl*)(const char* String);
    extern F_Console_Do_Command ConsoleDoCommand;

    using F_Camera_First_Person_Pre_Process = void(__cdecl*)();
    extern F_Camera_First_Person_Pre_Process CameraFirstPersonPreProcess;

    using F_Camera_Start_Third_Person = void(__cdecl*)();
    extern F_Camera_Start_Third_Person CameraStartThirdPerson;

    using F_Game_Print_Screen = void(__cdecl*)(char* String);
    extern F_Game_Print_Screen GamePrintScreen;

    using F_camera_free_system_init = void(__cdecl* )();
    extern F_camera_free_system_init CameraFreeSystemInit;

    using F_camera_free_mode_init = void(__cdecl*)();
    extern F_camera_free_mode_init CameraFreeModeInit;

    using F_console_chat_printf = void(__cdecl*)(const char* String);
    extern F_console_chat_printf ConsoleChatPrintf;

    using F_unused_dcf_r_show_mem_usage = void(__cdecl*)();
    extern F_unused_dcf_r_show_mem_usage UnusedDcfRShowMemUsage;

    using F_rfg_dyn_get_active_destruction_frame = unsigned __int16(__cdecl*)();
    extern F_rfg_dyn_get_active_destruction_frame RfgDynGetActiveDestructionFrame;

    using F_rfg_dyn_reset_destruction_frame = void(__cdecl*)(unsigned __int16 Frame);
    extern F_rfg_dyn_reset_destruction_frame RfgDynResetDestructionFrame;

    using F_rfg_dyn_system_shutdown = void(__cdecl*)();
    extern F_rfg_dyn_system_shutdown RfgDynSystemShutdown;

    using F_get_screen_width = int(__cdecl*)();
    extern F_get_screen_width GetScreenWidth;

    using F_console_is_active = bool(__cdecl*)();
    extern F_console_is_active ConsoleIsActive;

    using F_debug_spew_projectile = void(__cdecl*)(const char* Format);
    extern F_debug_spew_projectile DebugSpewProjectile;

    using F_debug_spew_game_io = void(__cdecl*)(const char* Format);
    extern F_debug_spew_game_io DebugSpewGameIo;

    using F_rl_render_lib_get_metrics = rl_renderer_metrics*(__cdecl* )();
    extern F_rl_render_lib_get_metrics RlRenderLibGetMetrics;

    using F_profile_dump_info = void(__cdecl*)();
    extern F_profile_dump_info ProfileDumpInfo;

    using F_vint_render_text = void(__cdecl*)(int _handle, const unsigned int* _text, unsigned int _first_char, unsigned int _num_chars, matrix23* _xform, 
                                              vector2* _pos, bool reversed, vint_res_offset _res_offset_x, vint_res_offset _res_offset_y, vint_res_scale _res_scale_x, vint_res_scale _res_scale_y);
    extern F_vint_render_text VintRenderText;

    using F_xray_effect_start = void(__cdecl*)(xray_effect_types xray_effect_type);
    extern F_xray_effect_start XrayEffectStart;

    using F_xray_effect_stop = void(__cdecl*)(xray_effect_types xray_effect_type);
    extern F_xray_effect_stop XrayEffectStop;

    using F_InvertDataItem = void(__cdecl*)(void* Item);
    extern F_InvertDataItem InvertDataItem;

    using F_camera_start_first_person = void(__cdecl*)(bool Smooth);
    extern F_camera_start_first_person CameraStartFirstPerson;

    using F_camera_stop_first_person = void(__cdecl*)(bool Smooth);
    extern F_camera_stop_first_person CameraStopFirstPerson;

    using F_key_down = void(__cdecl*)(unsigned int Scancode);
    extern F_key_down KeyDown;

    using F_game_render_set_bloom_exposure_factor = void(__cdecl*)(float ExposureFactor);
    extern F_game_render_set_bloom_exposure_factor GameRenderSetBloomExposureFactor;

    using F_game_render_set_hdr_state = void(__cdecl*)(rl_hdr_state* hdr_state);
    extern F_game_render_set_hdr_state GameRenderSetHdrState;

    using F_game_render_2d_text = void(__cdecl*)(const char* str, vector* text_pos);
    extern F_game_render_2d_text GameRender2dText;

    using F_ui_add_debug_text = unsigned int(__cdecl*)(const char *text, debug_text_posn type);
    extern F_ui_add_debug_text UiAddDebugText;

    using F_get_depth_of_field_enabled = bool(__thiscall*)(rl_camera* ThisCamera); //bool __thiscall rl_camera::GetDepthOfFieldEnabled(rl_camera *this)
    extern F_get_depth_of_field_enabled GetDepthOfFieldEnabled;

    using F_set_depth_of_field_enabled = void(__thiscall*)(rl_camera* ThisCamera, bool Enabled); //void __thiscall rl_camera::SetDepthOfFieldEnabled(rl_camera *this, bool depth_of_field_enabled)
    extern F_set_depth_of_field_enabled SetDepthOfFieldEnabled;

    using F_fog_of_war_clear = void(__cdecl*)();
    extern F_fog_of_war_clear FogOfWarClear;

    using F_Hud_Hide = void(__cdecl*)(bool HideHud);
    extern F_Hud_Hide HudHide;

    using F_game_render_set_fog_enabled = void(__cdecl*)(bool Enabled);
    extern F_game_render_set_fog_enabled GameRenderSetFogEnabled;

    //typedef void (__cdecl* explosion_create)(explosion_info* ExplosionInfo, object* Source, object* Owner, vector* Position, matrix* Orientation, vector* Directiom, weapon_info* WeaponInfo, bool FromServer)
    using F_explosion_create = void(__cdecl*)(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position,
                                              matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer);
    extern F_explosion_create ExplosionCreate;

    //.text:0129DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame>
    using F_keen_graphics_beginframe = void(__cdecl*)(keen::GraphicsSystem* GraphicsSystem);
    extern F_keen_graphics_beginframe GraphicsBeginFrame;

    //.text:00B992B0 rfg.exe:$1692B0 #1686B0 <mouse_generic_auto_centering>
    using F_MouseGenericAutoCentering = void(__cdecl*)(bool AutoCentering);
    extern F_MouseGenericAutoCentering MouseGenericAutoCentering;

    //.text:00D00290 rfg.exe:$2D0290 #2CF690 <camera_view_data::set_view>
    using F_CameraViewDataSetView = void(__cdecl*)(CameraViewData* ViewData, CameraViewTableEntry* ViewTableEntry, bool SkipTransition);
    extern F_CameraViewDataSetView CameraViewDataSetView;

    //.text:00A65A80 rfg.exe:$6D5A80 #6D4E80 <player::do_frame>
    using F_PlayerDoFrame = void(__fastcall*)(Player* PlayerPtr);
    extern F_PlayerDoFrame PlayerDoFrame;

    //.text:00A6ECA0 rfg.exe:$6DECA0 #6DE0A0 <player::player>
    using F_PlayerConstructor = void(__fastcall*)(Player* PlayerPtr);
    extern F_PlayerConstructor PlayerConstructor;

    //.text:007A53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>
    using F_CharacterControllerSetPos = void(__fastcall*)(CharacterController* CharController, vector* Position);
    extern F_CharacterControllerSetPos CharacterControllerSetPos;

    //.text:00A1C310 rfg.exe:$68C310 #68B710 <object::update_pos_and_orient> //void __thiscall object::update_pos_and_orient(object *this, vector *update_pos, matrix *update_orient, bool set_havok_data)
    using F_ObjectUpdatePosAndOrient = void(__fastcall*)(Object*, void*, vector*, matrix*, bool); //2nd arg is edx, needed for __thiscall functions.
    extern F_ObjectUpdatePosAndOrient ObjectUpdatePosAndOrient;

    //.text:009A4DC0 rfg.exe:$614DC0 #6141C0 <object::update_render> //void __thiscall object::update_render(object *this, rl_renderer *__formal)
    //.text:009A4D00 rfg.exe:$614D00 #614100 <object::update_streaming_box> //void __thiscall object::update_streaming_box(object *this)

    //.text:007E9530 rfg.exe:$429530 #428930 <havok_body_get_pos_orient>
    using F_HavokBodyGetPositionAndOrient = void(__cdecl*)(unsigned int Handle, vector& Position, matrix& Orient);
    extern F_HavokBodyGetPositionAndOrient HavokBodyGetPositionAndOrient;

    //.text:007D6EA0 rfg.exe:$416EA0 #4162A0 <havok_body_set_position> //void __cdecl havok_body_set_position(unsigned int handle, vector *pos)
    using F_HavokBodySetPosition = void(__cdecl*)(unsigned int Handle, vector& Position);
    extern F_HavokBodySetPosition HavokBodySetPosition;

    //.text:007D6E10 rfg.exe:$416E10 #416210 <havok_body_set_pos_orient>

    //.text:007E3700 rfg.exe:$423700 #422B00 <havok_body_set_pos_orient>
    using F_HavokBodySetPositionAndOrient = void(__cdecl*)(unsigned int Handle, vector& Position, matrix& Orient);
    extern F_HavokBodySetPositionAndOrient HavokBodySetPositionAndOrient;

    //.text:00A5AF70 rfg.exe:$69AF70 #69A370 <human::update_pos_and_orient> //void __thiscall human::update_pos_and_orient(human *this, vector *update_pos, matrix *update_orient, bool set_havok_data)
    using F_HumanUpdatePosAndOrient = void(__fastcall*)(Human*, void*, vector*, matrix*, bool); //2nd arg is edx, needed for __thiscall functions.
    extern F_HumanUpdatePosAndOrient HumanUpdatePosAndOrient;

    //.text:00A3C660 rfg.exe:$67C660 #67BA60 <human_teleport_unsafe> //void __cdecl human_teleport_unsafe(human *hp, vector pos, matrix orient)
    using F_HumanTeleportUnsafe = void(__cdecl*)(Human* HumanPtr, vector Position, matrix Orientation);
    extern F_HumanTeleportUnsafe HumanTeleportUnsafe;

    //.text:00A5A7A0 rfg.exe:$69A7A0 #699BA0 <human_teleport>
    /*typedef void(__cdecl* F_HumanTeleport)(Human* HumanPtr, vector* Position, matrix* Orientation, float PlacementRange, bool AllowFail);
extern F_HumanTeleport HumanTeleport;*/

    using F_CsWrapSlice = void(__cdecl*)();
    extern F_CsWrapSlice CsWrapSlice;

    //bool __cdecl keen::graphics::resizeRenderSwapChain(keen::RenderSwapChain *pSwapChain, unsigned int newWidth, unsigned int newHeight)
    //Can map out keen::RenderSwapChain later if data is needed from it, currently just hooking this as a signal init the D3D11 pointers again.
    //.text:00C2AB20 rfg.exe:$86AB20 #869F20 <keen::graphics::resizeRenderSwapChain>
    using F_KeenGraphicsResizeRenderSwapchain = bool(__cdecl*)(keen::RenderSwapChain* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight);
    extern F_KeenGraphicsResizeRenderSwapchain KeenGraphicsResizeRenderSwapchain;

    //.text:0122FCF0 rfg.exe:$3BFCF0 #3BF0F0 <gameseq_get_state>
    using F_GameseqGetState = GameState(__cdecl*)();
    extern F_GameseqGetState GameseqGetState;

    //.text:00718710 rfg.exe:$3D8710 #3D7B10 <gameseq_set_state> //void __cdecl gameseq_set_state(game_state state, bool uninterruptible)
    using F_GameseqSetState = void(__cdecl*)(GameState state, bool uninterruptible);
    extern F_GameseqSetState GameseqSetState;

    //.text:007187C0 rfg.exe:$3D87C0 #3D7BC0 <gameseq_push_state> //void __cdecl gameseq_push_state(game_state new_state, bool transparent, bool pause_beneath)
    using F_GameseqPushState = void(__cdecl*)(GameState new_state, bool transparent, bool pause_beneath);
    extern F_GameseqPushState GameseqPushState;

    //.text:01270C50 rfg.exe:$310C50 #310050 <object::enable_object_outline>
    using F_ObjectEnableOutline = void(__thiscall*)(Object* This, int Layer);
    extern F_ObjectEnableOutline ObjectEnableOutline;

    //.text:01270C60 rfg.exe:$310C60 #310060 <object::disable_object_outline>
    using F_ObjectDisableOutline = void(__thiscall*)(Object* This);
    extern F_ObjectDisableOutline ObjectDisableOutline;

    //.text:0158EE80 rfg.exe:$62EE80 #62E280 <human::enable_object_outline>
    using F_HumanEnableOutline = void(__thiscall*)(Human* This, int Layer);
    extern F_HumanEnableOutline HumanEnableOutline;

    //.text:0158EF00 rfg.exe:$62EF00 #62E300 <human::disable_object_outline>
    using F_HumanDisableOutline = void(__thiscall*)(Human* This);
    extern F_HumanDisableOutline HumanDisableOutline;

    //.text:01695390 rfg.exe:$735390 #734790 <target_outline_add_object>
    using F_TargetOutlineAddObject = void(__cdecl*)(unsigned int Handle);
    extern F_TargetOutlineAddObject TargetOutlineAddObject;

    //.text:00D0A4F0 rfg.exe:$4DA4F0 #4D98F0 <ui_tool_tips_add_tip> //void __cdecl ui_tool_tips_add_tip(const char *name, const int delay_ms, const char *icon_image)
    using F_ui_tool_tips_add_tip = void(__cdecl*)(const char* Name, const int DelayMs, const char* IconImage);
    extern F_ui_tool_tips_add_tip UiToolTipsAddTip;

    //.text:0093DDA0 rfg.exe:$10DDA0 #10D1A0 <rl_draw::tristrip_2d_begin>
    using F_rl_draw_tristrip_2d_begin = void(__fastcall*)(void*, void*, rl_primitive_state*); //2nd arg is edx, needed for __thiscall functions.
    extern F_rl_draw_tristrip_2d_begin RlDrawTristrip2dBegin;

    //.text:00985BC0 rfg.exe:$155BC0 #154FC0 <rl_draw::string>
    //void __thiscall rl_draw::string(rl_draw *this, float sx, float sy, const char *s, bool centered, int fontnum, rl_primitive_state *state)
    using F_rl_draw_string = void(__fastcall*)(void* This, void* edx, float sx, float sy, const char* s, bool centered, int fontnum, rl_primitive_state* state); //2nd arg is edx, needed for __thiscall functions.
    extern F_rl_draw_string RlDrawString;

    //.text:015C1690 rfg.exe:$3C1690 #3C0A90 <game_is_paused>
    using F_is_game_paused = bool(__cdecl*)();
    extern F_is_game_paused IsGamePaused;

    //.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame> //bool __thiscall world::do_frame(world *this, bool hard_load)
    using F_world_do_frame = void(__fastcall*)(World* This, void* edx, bool HardLoad); //2nd arg is edx, needed for __thiscall functions.
    extern F_world_do_frame WorldDoFrame;

    //.text:0171C8A0 rfg.exe:$51C8A0 #51BCA0 <world::get_object_name> //const char *__thiscall world::get_object_name(world *this, object *objp)
    using F_world_get_object_name = const char*(__fastcall*)(World* This, void* edx, Object* ObjectPtr); //2nd arg is edx, needed for __thiscall functions.
    extern F_world_get_object_name WorldGetObjectName;



    //.text:0171D9F0 rfg.exe:$51D9F0 #51CDF0 <world::get_object_zone_by_index> //obj_zone *__thiscall world::get_object_zone_by_index(world *this, int index)
    using F_world_get_object_zone_by_index = obj_zone*(__fastcall*)(World* This, void* edx, int Index); //2nd arg is edx, needed for __thiscall functions.
    extern F_world_get_object_zone_by_index WorldGetObjectZoneByIndex;
    //.text:0171DA20 rfg.exe:$51DA20 #51CE20 <world::get_object_zone_by_grid_id> //obj_zone *__thiscall world::get_object_zone_by_grid_id(world *this, unsigned __int16 id)
    using F_world_get_object_zone_by_grid_id = obj_zone*(__fastcall*)(World* This, void* edx, unsigned __int16 id); //2nd arg is edx, needed for __thiscall functions.
    extern F_world_get_object_zone_by_grid_id WorldGetObjectZoneByGridId;

    //.text:010DD610 rfg.exe:$35D610 #35CA10 <GsmGetAlertLevel> //gfm_alert_levels __cdecl GsmGetAlertLevel()
    using F_gsm_get_alert_level = gfm_alert_levels(__cdecl*)();
    extern F_gsm_get_alert_level GsmGetAlertLevel;
    //.text:0112A740 rfg.exe:$3AA740 #3A9B40 <GsmSetAlertLevel> //void __cdecl GsmSetAlertLevel(gfm_alert_levels new_alert_level)
    using F_gsm_set_alert_level = void(__cdecl*)(gfm_alert_levels new_alert_level);
    extern F_gsm_set_alert_level GsmSetAlertLevel;

    //.text:010DD630 rfg.exe:$35D630 #35CA30 <GsmGetAlertValue> //float __cdecl GsmGetAlertValue()
    using F_gsm_get_alert_value = float(__cdecl*)();
    extern F_gsm_get_alert_value GsmGetAlertValue;
    //.text:011244B0 rfg.exe:$3A44B0 #3A38B0 <GsmSetAlertValue> //void __cdecl GsmSetAlertValue(float new_alert_value)
    using F_gsm_set_alert_value = void(__cdecl*)(float new_alert_value);
    extern F_gsm_set_alert_value GsmSetAlertValue;

    //.text:010DD680 rfg.exe:$35D680 #35CA80 <GsmGetAlertLevelCap> //void __cdecl GsmGetAlertLevelCap(gfm_alert_levels *min, gfm_alert_levels *max)
    using F_gsm_get_alert_level_cap = void(__cdecl*)(gfm_alert_levels* min, gfm_alert_levels* max);
    extern F_gsm_get_alert_level_cap GsmGetAlertLevelCap;
    //.text:0112A770 rfg.exe:$3AA770 #3A9B70 <GsmSetAlertLevelCap> //void __cdecl GsmSetAlertLevelCap(gfm_alert_levels min, gfm_alert_levels max)
    using F_gsm_set_alert_level_cap = void(__cdecl*)(gfm_alert_levels min, gfm_alert_levels max);
    extern F_gsm_set_alert_level_cap GsmSetAlertLevelCap;

    //.text:01142960 rfg.exe:$3C2960 #3C1D60 <GameRenderGetTodLight> //rl_light *__cdecl fav::GameRenderGetTodLight()
    using F_game_render_get_TOD_light = rl_light*(__cdecl*)();
    extern F_game_render_get_TOD_light GameRenderGetTodLight;
    //.text:01142930 rfg.exe:$3C2930 #3C1D30 <GameRenderSetTodLight> //void __cdecl fav::GameRenderSetTodLight(rl_light *light_p)
    using F_game_render_set_TOD_light = void(__cdecl*)(rl_light* light_p);
    extern F_game_render_set_TOD_light GameRenderSetTodLight;

    //.text:01143000 rfg.exe:$3C3000 #3C2400 <GameRenderGetTodOnOffValue> //void __cdecl fav::GameRenderGetTodOnOffValue(float *val)
    using F_game_render_get_tod_on_off_value = void(__cdecl*)(float* Value);
    extern F_game_render_get_tod_on_off_value GameRenderGetTodOnOffValue;
    //.text:01142FF0 rfg.exe:$3C2FF0 #3C23F0 <GameRenderSetTodOnOffValue> //void __cdecl fav::GameRenderSetTodOnOffValue(float val)
    using F_game_render_set_tod_on_off_value = void(__cdecl*)(float Value);
    extern F_game_render_set_tod_on_off_value GameRenderSetTodOnOffValue;

    using F_AllocatorStillValid = void(__cdecl*)(void* ref_address);
    extern F_AllocatorStillValid AllocatorStillValid;

    //.text:01142990 rfg.exe:$3C2990 #3C1D90 <GameRenderSetTodLightColor> //void __cdecl fav::GameRenderSetTodLightColor(rl_color_float *color)
    using F_game_render_set_TOD_light_color = void(__cdecl*)(rl_color_float* color);
    extern F_game_render_set_TOD_light_color GameRenderSetTodLightColor;

    //.text:011415C0 rfg.exe:$3C15C0 #3C09C0 <GameClockGetTodPartitioned> //game_clock_tod_partitioned __cdecl fav::GameClockGetTodPartitioned()
    using F_game_clock_get_tod_partitioned = game_clock_tod_partitioned(__cdecl*)();
    extern F_game_clock_get_tod_partitioned GameClockGetTodPartitioned;

    //.text:011415E0 rfg.exe:$3C15E0 #3C09E0 <GameClockGetTimeOfDay> //game_clock_time_of_day __cdecl fav::GameClockGetTimeOfDay()
    using F_game_clock_get_time_of_day = game_clock_time_of_day(__cdecl*)();
    extern F_game_clock_get_time_of_day GameClockGetTimeOfDay;
    //.text:01141770 rfg.exe:$3C1770 #3C0B70 <GameClockSetTime> //void __cdecl fav::GameClockSetTime(int hours, int minutes, int seconds)
    using F_game_clock_set_time = void(__cdecl*)(int hours, int minutes, int seconds);
    extern F_game_clock_set_time GameClockSetTime;

    //.text:0115FA10 rfg.exe:$3DFA10 #3DEE10 <GameTimeOfDayGetSkyboxTodColors> //void __cdecl GameTimeOfDayGetSkyboxTodColors(rl_color_float *colors)
    using F_game_time_of_day_get_skybox_tod_colors = void(__cdecl*)(rl_color_float* Colors);
    extern F_game_time_of_day_get_skybox_tod_colors GameTimeOfDayGetSkyboxTodColors;
    //.text:01145880 rfg.exe:$3C5880 #3C4C80 <GameTimeOfDayGetWeatherSettings> //void __cdecl fav::GameTimeOfDayGetWeatherSettings(vector4 *horizon_strengths, vector4 *overhead_strengths)
    using F_game_time_of_day_get_weather_settings = void(__cdecl*)(vector4* horizon_strengths, vector4* overhead_strengths);
    extern F_game_time_of_day_get_weather_settings GameTimeOfDayGetWeatherSettings;
    //.text:011458C0 rfg.exe:$3C58C0 #3C4CC0 <GameTimeOfDayGetCloudScrollValues> //void __cdecl fav::GameTimeOfDayGetCloudScrollValues(float *layer01_scroll, float *layer23_scroll)
    using F_game_time_of_day_get_cloud_scroll_values = void(__cdecl*)(float* layer01_scroll, float* layer23_scroll);
    extern F_game_time_of_day_get_cloud_scroll_values GameTimeOfDayGetCloudScrollValues;
    //.text:011520C0 rfg.exe:$3D20C0 #3D14C0 <GameTimeOfDayGetNumOrbitals> //int __cdecl fav::GameTimeOfDayGetNumOrbitals()
    using F_game_time_of_day_get_num_orbitals = int(__cdecl*)();
    extern F_game_time_of_day_get_num_orbitals GameTimeOfDayGetNumOrbitals;
    //.text:011631B0 rfg.exe:$3E31B0 #3E25B0 <GameTimeOfDayGetCloudLighting> //void __cdecl GameTimeOfDayGetCloudLighting(rl_color_float *horizon_front_ambient, rl_color_float *horizon_back_ambient, rl_color_float *overhead_front_ambient, rl_color_float *overhead_back_ambient, float *backlight_strength, float *backlight_power, vector *light_direction)
    using F_game_time_of_day_get_cloud_lighting = void(__cdecl*)(rl_color_float* horizon_front_ambient, rl_color_float* horizon_back_ambient, rl_color_float* overhead_front_ambient, rl_color_float* overhead_back_ambient, float* backlight_strength, float* backlight_power, vector* light_direction);
    extern F_game_time_of_day_get_cloud_lighting GameTimeOfDayGetCloudLighting;
    //.text:01165400 rfg.exe:$3E5400 #3E4800 <GameTimeOfDayGetOrbitalParams> //void __cdecl GameTimeOfDayGetOrbitalParams(int idx, rl_skybox_orbital_params *params)
    using F_game_time_of_day_get_orbital_params = void(__cdecl*)(int Index, rl_skybox_orbital_params* Params);
    extern F_game_time_of_day_get_orbital_params GameTimeOfDayGetOrbitalParams;

    //.text:011EC4D0 rfg.exe:$46C4D0 #46B8D0 <DistrictFromName> //district *__cdecl DistrictFromName(const char *name)
    using F_district_from_name = district*(__cdecl*)(const char *name);
    extern F_district_from_name DistrictFromName;

    //.text:0129D950 rfg.exe:$51D950 #51CD50 <world::GetWorldZoneByIndex> //world_zone *__thiscall world::GetWorldZoneByIndex(world *this, int index)
    using F_get_world_zone_by_index = world_zone*(__fastcall*)(World* This, void* edx, int Index); //2nd arg is edx, needed for __thiscall functions.
    extern F_get_world_zone_by_index GetWorldZoneByIndex;
    //.text:0129D970 rfg.exe:$51D970 #51CD70 <world::GetWorldZoneByGridId> //world_zone *__thiscall world::GetWorldZoneByGridId(world *this, unsigned __int16 id)
    using F_get_world_zone_by_grid_id = world_zone*(__fastcall*)(World* This, void* edx, unsigned __int16 id); //2nd arg is edx, needed for __thiscall functions.
    extern F_get_world_zone_by_grid_id GetWorldZoneByGridId;
    //.text:0129D9A0 rfg.exe:$51D9A0 #51CDA0 <world::GetWorldZoneByName> //world_zone *__thiscall world::GetWorldZoneByName(world *this, const char *name)
    using F_get_world_zone_by_name = world_zone*(__fastcall*)(World* This, void* edx, const char* name); //2nd arg is edx, needed for __thiscall functions.
    extern F_get_world_zone_by_name GetWorldZoneByName;
    //.text:012A3BA0 rfg.exe:$523BA0 #522FA0 <world::GetWorldZoneByPos> //world_zone *__thiscall world::GetWorldZoneByPos(world *this, vector *pos)
    using F_get_world_zone_by_pos = world_zone*(__fastcall*)(World* This, void* edx, vector* Position); //2nd arg is edx, needed for __thiscall functions.
    extern F_get_world_zone_by_pos GetWorldZoneByPos;
    //.text:012A3C00 rfg.exe:$523C00 #523000 <world::GetWorldZoneByObjectHandle> //world_zone *__thiscall world::GetWorldZoneByObjectHandle(world *this, unsigned int handle)
    using F_get_world_zone_by_object_handle = world_zone*(__fastcall*)(World* This, void* edx, unsigned int handle); //2nd arg is edx, needed for __thiscall functions.
    extern F_get_world_zone_by_object_handle GetWorldZoneByObjectHandle;

    //.text:010924D0 rfg.exe:$3124D0 #3118D0 <RfgDynApplyPointImpulse> //void __usercall RfgDynApplyPointImpulse(int havok_handle, vector *impulse@<eax>, vector *impulse_pos, float mass@<xmm10>)
    using F_rfg_dyn_apply_point_impulse = void(__cdecl*)(int havok_handle, vector* impulse, vector* impulse_pos, float mass); ///Figure out the proper calling convention...
    extern F_rfg_dyn_apply_point_impulse RfgDynApplyPointImpulse;
    //.text:01094820 rfg.exe:$314820 #313C20 <RfgDynRepairSphere> //void __cdecl RfgDynRepairSphere(vector *pos, const float radius, const int duration, human *hp)
    using F_rfg_dyn_repair_sphere = void(__cdecl*)(vector* pos, float radius, int duration, Human* hp);
    extern F_rfg_dyn_repair_sphere RfgDynRepairSphere;

    //.text:00F78A10 rfg.exe:$1F8A10 #1F7E10 <world::object_cast<human>> //human *__thiscall world::object_cast<human>(world *this, object *objp)
    //.text:00F78C10 rfg.exe:$1F8C10 #1F8010 <world::object_cast<human>> //human *__thiscall world::object_cast<human>(world *this, object *objp)

    extern Human* CastObjectToHuman(Object* ObjectPtr);
    extern Player* CastObjectToPlayer(Object* ObjectPtr);
    extern obj_zone* CastObjectToObjZone(Object* ObjectPtr);
    extern district* CastObjectToDistrict(Object* ObjectPtr);


    //void __thiscall rl_camera::render_begin(rl_camera *this, rl_renderer *renderer)
    //.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>
    using F_rl_camera_render_begin = void(__fastcall*)(rl_camera* This, void* edx, void* Renderer); //2nd arg is edx, needed for __thiscall functions.
    extern F_rl_camera_render_begin RlCameraRenderBegin;

    //.text:012B2C40 rfg.exe:$3C2C40 #3C2040 <game_render_set_far_clip_distance> //void __cdecl fav::game_render_set_far_clip_distance(float distance)
    using F_game_render_set_far_clip_distance = void(__cdecl*)(float Distance);
    extern F_game_render_set_far_clip_distance GameRenderSetFarClipDistance;

    //.text:012B2C50 rfg.exe:$3C2C50 #3C2050 <game_render_get_far_clip_distance> //float __cdecl fav::game_render_get_far_clip_distance()
    using F_game_render_get_far_clip_distance = float(__cdecl*)();
    extern F_game_render_get_far_clip_distance GameRenderGetFarClipDistance;

    //.text:012B2920 rfg.exe:$3C2920 #3C1D20 <game_render_get_main_scene> //rl_scene *__cdecl fav::game_render_get_main_scene()
    using F_game_render_get_main_scene = rl_scene*(__cdecl*)();
    extern F_game_render_get_main_scene GameRenderGetMainScene;

    //hkpStepResult __thiscall fav::hkpWorld::stepDeltaTime(hkpWorld *this, float physicsDeltaTime) //0x9E1A70
    using F_hkpWorld_stepDeltaTime = void(__fastcall*)(hkpWorld* This, void* edx, float PhysicsDeltaTime); //2nd arg is edx, needed for __thiscall functions.
    extern F_hkpWorld_stepDeltaTime hkpWorldStepDeltaTime;

    //.text:0117A880 rfg.exe:$5A880 #59C80 <keen::rfg::Application::updateTime> //void __thiscall fav::keen::rfg::Application::updateTime(keen::rfg::Application *this, float timeStep)
    //rfg::Application
    using F_ApplicationUpdateTime = void(__fastcall*)(void* This, void* edx, float TimeStep); //2nd arg is edx, needed for __thiscall functions.
    extern F_ApplicationUpdateTime ApplicationUpdateTime;

    using F_IsValidEigenGradient = bool(__fastcall*)(void* This); //2nd arg is edx, needed for __thiscall functions.
    extern F_IsValidEigenGradient IsValidEigenGradient;

    //.text:0152D040 rfg.exe:$40D040 #40C440 <hkpWorld::getGravity> //hkVector4f *__thiscall fav::hkpWorld::getGravity(hkpWorld* this)
    using F_hkpWorldGetGravity = hkVector4f*(__fastcall*)(hkpWorld* This, void* edx); //2nd arg is edx, needed for __thiscall functions.
    extern F_hkpWorldGetGravity hkpWorldGetGravity;

    //.text:01B00E20 rfg.exe:$9E0E20 #9E0220 <hkpWorld::setGravity> //void __thiscall fav::hkpWorld::setGravity(hkpWorld* this, hkVector4f* gravity)
    using F_hkpWorldSetGravity = void(__fastcall* )(hkpWorld* This, void* edx, hkVector4f* Gravity); //2nd arg is edx, needed for __thiscall functions.
    extern F_hkpWorldSetGravity hkpWorldSetGravity;

    //.text:014306A0 rfg.exe:$3106A0 #30FAA0 <hkVector4f::set> //void __thiscall hkVector4f::set(hkVector4f *this, float a, float b, float c, float d)

    //.text:00C720F0 rfg.exe:$620F0 #614F0 <vint_lua_get_state> //lua_State *__cdecl vint_lua_get_state()
    using F_vint_lua_get_state = lua_State*(__cdecl*)();
    extern F_vint_lua_get_state VintGetLuaState;

    //.text:0143FD20 rfg.exe:$82FD20 #82F120 <lua_dobuffer> //int __cdecl lua_dobuffer(lua_State *L, const char *buff, unsigned int size, const char *name)
    using F_lua_dobuffer = int(__cdecl*)(lua_State *L, const char *buff, unsigned int size, const char *name);
    extern F_lua_dobuffer LuaDoBuffer;

    //.text:0125E870 rfg.exe:$40E870 #40DC70 <havok_body_get_pointer> //hkpRigidBody *__cdecl havok_body_get_pointer(unsigned int handle)
    using F_havok_body_get_pointer = hkpRigidBody*(__cdecl*)(unsigned int handle);
    extern F_havok_body_get_pointer HavokBodyGetPointer;

    //.text:012677A0 rfg.exe:$4177A0 #416BA0 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(hkpRigidBody *rb, vector *linear_impulse)
    using F_havok_body_apply_linear_impulse_A = void(__cdecl*)(hkpRigidBody* rb, vector& linear_impulse);
    extern F_havok_body_apply_linear_impulse_A HavokBodyApplyLinearImpulseA;

    //.text:01273C20 rfg.exe:$423C20 #423020 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(unsigned int handle, vector *linear_impulse)
    using F_havok_body_apply_linear_impulse_B = void(__cdecl*)(uint handle, vector& linear_impulse);
    extern F_havok_body_apply_linear_impulse_B HavokBodyApplyLinearImpulseB;

    //.text:015C3CA0 rfg.exe:$423CA0 #4230A0 <havok_body_apply_point_impulse> //void __cdecl havok_body_apply_point_impulse(unsigned int handle, vector *point_impulse, vector *pos)
    using F_havok_body_apply_point_impulse = void(__cdecl*)(unsigned int handle, vector& point_impulse, vector& pos);
    extern F_havok_body_apply_point_impulse havok_body_apply_point_impulse;

    //.text:0181DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame> //keen::GraphicsCommandBuffer *__cdecl keen::graphics::beginFrame(keen::GraphicsSystem *pGraphicsSystem, keen::RenderSwapChain *pSwapChain)
    using F_keen_graphics_beginFrame = keen::GraphicsCommandBuffer*(__cdecl*)(keen::GraphicsSystem* pGraphicsSystem, keen::RenderSwapChain* pSwapChain);
    extern F_keen_graphics_beginFrame KeenGraphicsBeginFrame;

    //.text:00C38740 rfg.exe:$58740 #57B40 <keen::getBuildVersionString>
    using F_keen_get_build_version_string = const char* (__cdecl*)();
    extern F_keen_get_build_version_string KeenGetBuildVersionString;


    //.text:0189C050 rfg.exe:$53C050 #53B450 <world::object_from_handle> //object *__thiscall world::object_from_handle(world *this, unsigned int handle)
    using F_WorldObjectFromHandle = Object* (__fastcall*)(World* This, void* edx, uint Handle); //2nd arg is edx, needed for __thiscall functions.
    extern F_WorldObjectFromHandle WorldObjectFromHandle;

    //.text:00F54F30 rfg.exe:$6D4F30 #6D4330 <unused_dcf_ragdoll_player>
    using F_unused_dcf_ragdoll_player =  void(__cdecl*)();
    extern F_unused_dcf_ragdoll_player UnusedDcfRagdollPlayer;

    //.text:00D9AEB0 rfg.exe:$51AEB0 #51A2B0 <stream_grid::set_stream_radius> //void __thiscall stream_grid::set_stream_radius(stream_grid *this, layout_layer layer, float radius)
    using F_StreamGridSetStreamRadius = void(__fastcall*)(stream_grid* This, void* edx, layout_layer Layer, float Radius); //2nd arg is edx, needed for __thiscall functions.
    extern F_StreamGridSetStreamRadius StreamGridSetStreamRadius;

    //.text:00D9AFB0 rfg.exe:$51AFB0 #51A3B0 <stream_grid::get_stream_radius> //float __thiscall stream_grid::get_stream_radius(stream_grid *this, layout_layer layer)
    using F_StreamGridGetStreamRadius = float(__fastcall*)(stream_grid* This, void* edx, layout_layer Layer); //2nd arg is edx, needed for __thiscall functions.
    extern F_StreamGridGetStreamRadius StreamGridGetStreamRadius;

    //.text:00DB0FB0 rfg.exe:$530FB0 #5303B0 <stream_grid::do_frame> //void __thiscall stream_grid::do_frame(stream_grid *this, vector *stream_pos, bool single_zone_mode)
    using F_StreamGridDoFrame = void(__fastcall*)(stream_grid* This, void* edx, vector* StreamPos, bool SingleZoneMode); //2nd arg is edx, needed for __thiscall functions.
    extern F_StreamGridDoFrame StreamGridDoFrame;

    //.text:00345D70 rfg.exe:$305D70 #305170 <cutscene_spawn_vehicle> //vehicle *__cdecl cutscene_spawn_vehicle(vehicle_info *v_info, vector *pos, matrix *orient)
    using F_cutscene_spawn_vehicle = vehicle*(__cdecl*)(vehicle_info* v_info, vector* pos, matrix* orient);
    extern F_cutscene_spawn_vehicle CutsceneSpawnVehicle;

    //.text:00797F40 rfg.exe:$757F40 #757340 <object_spawn_vehicle> //spawn_status_result __cdecl object_spawn_vehicle(vehicle_spawn_params *spawn_param)
    //using F_object_spawn_vehicle = spawn_status_result(__cdecl*)(vehicle_spawn_params* spawn_param);
    //extern F_object_spawn_vehicle ObjectSpawnVehicle;

    //.text:007A8E40 rfg.exe:$768E40 #768240 <vehicle_info_get_master_list> //farray<vehicle_info,163> *__cdecl fav_vehicle_info_get_master_list()
    using F_vehicle_info_get_master_list = rfg::farray<vehicle_info, 163>*(__cdecl*)();
    extern F_vehicle_info_get_master_list VehicleInfoGetMasterList;

    //.text:00796420 rfg.exe:$756420 #755820 <sp_spawn_vehicle> //bool __cdecl sp_spawn_vehicle(vehicle_spawn_params& spawn_param)
    using F_sp_spawn_vehicle = bool(__cdecl*)(vehicle_spawn_params& spawn_param);
    extern F_sp_spawn_vehicle SpSpawnVehicle;

    //.text:00788960 rfg.exe:$748960 #747D60 <create_new_vehicle> //bool __usercall create_new_vehicle@<al>(vehicle_spawn_params *spawn_param@<eax>)
    using F_create_new_vehicle = bool(__cdecl*)();//(vehicle_spawn_params* spawn_param);
    extern F_create_new_vehicle create_new_vehicle_raw;

    inline bool CreateNewVehicle(vehicle_spawn_params& spawn_params)
    {
        __asm
            {
            mov eax, spawn_params
            }
        return create_new_vehicle_raw();
    }

    //.text:00EF95F0 rfg.exe:$4895F0 #4889F0 <load_level_internal> //void __usercall load_level_internal(const char *filename@<esi>, bool new_game, bool single_zone)
    using F_load_level_internal = void(__cdecl*)(bool NewGame, bool SingleZone);
    extern F_load_level_internal load_level_internal;

    extern void LoadLevelWrapper(std::string Filename, bool NewGame, bool SingleZone);

    //bool __thiscall world::set_pending_territory_load(world *this, const char *filename, bool new_game, bool single_zone, bool player_start_at_safehouse, int dlc_id, bool reset_destruction)
    //.text:00F8C4A0 rfg.exe:$51C4A0 #51B8A0 <world::set_pending_territory_load>
    using F_WorldSetPendingTerritoryLoad = void(__fastcall*)(World* worldptr, void* edx, const char* filename, bool new_game, bool single_zone, bool player_start_at_safehouse, int dlc_id, bool reset_destruction); //2nd arg is edx, needed for __thiscall functions.
    extern F_WorldSetPendingTerritoryLoad WorldSetPendingTerritoryLoad;

    //.text:00B41F10 rfg.exe:$1D1F10 #1D1310 <peg_load_wrapper> //bool __cdecl peg_load_wrapper(const char *fname, unsigned int srid, char *cpu_preload, int cpu_size, char *gpu_preload, int gpu_size)
    using F_peg_load_wrapper = bool(__cdecl*)(const char* filename, unsigned int srid, char* cpu_preload, int cpu_size, char* gpu_preload, int gpu_size);
    extern F_peg_load_wrapper peg_load_wrapper;

    //.text:00A8FE90 rfg.exe:$18FE90 #18F290 <string_hash> //unsigned int __cdecl string_hash(const char *key, unsigned int hash_size)
    using F_string_hash = uint(__cdecl*)(const char* key, unsigned int hash_size);
    extern F_string_hash string_hash;

    //.text:01317F40 rfg.exe:$757F40 #757340 <object_spawn_vehicle> //spawn_status_result __cdecl object_spawn_vehicle(vehicle_spawn_params *spawn_param)
    using F_object_spawn_vehicle = spawn_status_result(__cdecl*)(vehicle_spawn_params& spawn_param);
    extern F_object_spawn_vehicle object_spawn_vehicle;

    //.text:0125B5D0 rfg.exe:$69B5D0 #69A9D0 <human_get_head_pos_orient> //void __cdecl human_get_head_pos_orient(human *hp, vector& head_pos, matrix& head_orient)
    using F_human_get_head_pos_orient = void(__cdecl*)(Human* hp, vector& head_pos, matrix& head_orient);
    extern F_human_get_head_pos_orient human_get_head_pos_orient;

    //.text:0125B8C0 rfg.exe:$69B8C0 #69ACC0 <human_set_render> //void __cdecl human_set_render(human *hp, bool render)
    using F_human_set_render = void(__cdecl*)(Human* hp, bool render);
    extern F_human_set_render human_set_render;

    //.text:0125B7E0 rfg.exe:$69B7E0 #69ABE0 <human_hide> //void __cdecl human_hide(human *hp, bool hide)
    using F_human_hide = void(__cdecl*)(Human* hp, bool hide);
    extern F_human_hide human_hide;

    //.text:0123E1D0 rfg.exe:$67E1D0 #67D5D0 <human::set_opacity_plus_child_items> //void __thiscall human::set_opacity_plus_child_items(human *this, float alpha)
    using F_human_set_opacity_plus_child_items = void(__fastcall*)(Human* this_ptr, void* edx, float alpha); //2nd arg is edx, needed for __thiscall functions.
    extern F_human_set_opacity_plus_child_items human_set_opacity_plus_child_items;

    //.text:00D64370 rfg.exe:$1A4370 #1A3770 <matrix::rotate_around_local_vector> //void __thiscall matrix::rotate_around_local_vector(matrix *this, vector *axis, float ang_rad)
    using F_matrix_rotate_around_local_vector = void(__fastcall*)(matrix* this_ptr, void* edx, vector& axis, float angle_radians); //2nd arg is edx, needed for __thiscall functions.
    extern F_matrix_rotate_around_local_vector matrix_rotate_around_local_vector;

    //.text:008AC810 rfg.exe:$86C810 #86BC10 <keen::ImmediateRenderer::beginRenderPass> //void __thiscall keen::ImmediateRenderer::beginRenderPass(keen::ImmediateRenderer *this, keen::RenderTarget *pRenderTarget, keen::Camera *pCamera)
    using F_keen_ImmediateRenderer_beginRenderPass = void(__fastcall*)(keen::ImmediateRenderer* this_ptr, void* edx, keen::RenderTarget* pRenderTarget, keen::Camera* pCamera); //2nd arg is edx, needed for __thiscall functions.
    extern F_keen_ImmediateRenderer_beginRenderPass keen_ImmediateRenderer_beginRenderPass;

    //.text:00818270 rfg.exe:$4D8270 #4D7670 <ui_add_secondary_message> //hud_message_handle __cdecl ui_add_secondary_message(const wchar_t *text, float display_time, bool use_secondary_anim, bool force_redisplay)
    using F_ui_add_secondary_message = void(__cdecl*)(const wchar_t* text, float display_time, bool use_secondary_anim, bool force_redisplay);
    extern F_ui_add_secondary_message ui_add_secondary_message;

    //.text:00DD83D0 rfg.exe:$4D83D0 #4D77D0 <ui_add_user_message> //hud_message_handle __cdecl ui_add_user_message(const wchar_t *text, hud_user_message_types type, float position_x, float position_y, bool outlined, float lifespan)
    using F_ui_add_user_message = hud_message_handle(__cdecl*)(const wchar_t* text, hud_user_message_types type, float position_x, float position_y, bool outlined, float lifespan);
    extern F_ui_add_user_message ui_add_user_message;

    //.text:00DF6C70 rfg.exe:$4F6C70 #4F6070 <ui_add_msgbox> //int __cdecl ui_add_msgbox(msgbox_type type, const char *title, const char *description, bool (__cdecl *callback_fn)(int, int, msgbox_choice), bool surpress_accept_sounds, bool ignore_save_load_status, const char *button1_override, const char *button2_override, bool pause_music)
    using F_ui_add_msgbox = int(__cdecl*)(msgbox_type type, const char* title, const char* description, bool(__cdecl* callback_fn)(int, int, msgbox_choice), bool surpress_accept_sounds, bool ignore_save_load_status, const char* button1_override, const char* button2_override, bool pause_music);
    extern F_ui_add_msgbox ui_add_msgbox;

    //.text:00D55EE0 rfg.exe:$455EE0 #4552E0 <hud_message_change_minor_message> hud_message_handle __cdecl hud_message_change_minor_message(hud_message_handle handle, const char *str, float duration)
    using F_hud_message_change_minor_message = hud_message_handle(__cdecl*)(hud_message_handle handle, const char* str, float duration);
    extern F_hud_message_change_minor_message hud_message_change_minor_message;

    //.text:00D55F50 rfg.exe:$455F50 #455350 <hud_message_change_user> //hud_message_handle __cdecl hud_message_change_user(hud_message_handle handle, const char *str)
    using F_hud_message_change_user = hud_message_handle(__cdecl*)(hud_message_handle handle, const char* str);
    extern F_hud_message_change_user hud_message_change_user;

    //.text:00D44BB0 rfg.exe:$444BB0 #443FB0 <hud_message_remove_user> //void __cdecl hud_message_remove_user(hud_message_handle handle)
    using F_hud_message_remove_user = void(__cdecl*)(hud_message_handle handle);
    extern F_hud_message_remove_user hud_message_remove_user;

    //.text:00664A60 rfg.exe:$324A60 #323E60 <rfgl_find_and_delete_object_mover> //int __cdecl rfgl_find_and_delete_object_mover(int objects_to_delete, bool find_gm)
    using F_rfgl_find_and_delete_object_mover = int(__cdecl*)(int objects_to_delete, bool find_gm);
    extern F_rfgl_find_and_delete_object_mover rfgl_find_and_delete_object_mover;

    //.text:00664B90 rfg.exe:$324B90 #323F90 <rfgl_find_and_delete_debris_object> //int __cdecl rfgl_find_and_delete_debris_object(int objects_to_delete)
    using F_rfgl_find_and_delete_debris_object = int(__cdecl*)(int objects_to_delete);
    extern F_rfgl_find_and_delete_debris_object rfgl_find_and_delete_debris_object;

    //.text:00701480 rfg.exe:$3C1480 #3C0880 <game_clock_get> //game_clock *__cdecl fav::game_clock_get()
    using F_game_clock_get = game_clock*(__cdecl*)();
    extern F_game_clock_get game_clock_get;


    //int dc_play_sound_foley_info //Todo: Get this and pass it as caller_cue_id maybe?
    //.text:003CDC50 rfg.exe:$8DC50 #8D050 <audiolib_cue_get_id> //audiolib_result __cdecl audiolib_cue_get_id(const char *cue_name, int *caller_cue_id)
    using F_audiolib_cue_get_id = audiolib_result(__cdecl*)(const char* cue_name, int* caller_cue_id);
    extern F_audiolib_cue_get_id audiolib_cue_get_id;

    //.text:003DF0F0 rfg.exe:$9F0F0 #9E4F0 <audiolib_cue_is_id_valid> //bool __cdecl audiolib_cue_is_id_valid(int caller_cue_id)
    using F_audiolib_cue_is_id_valid = bool(__cdecl*)(int caller_cue_id);
    extern F_audiolib_cue_is_id_valid audiolib_cue_is_id_valid;

    //.text:003DF120 rfg.exe:$9F120 #9E520 <audiolib_cue_play> //int __cdecl audiolib_cue_play(int cue_id, audiolib_params *passed_params, audiolib_result *error)
    using F_audiolib_cue_play = int(__cdecl*)(int cue_id, audiolib_params* passed_params, audiolib_result* error);
    extern F_audiolib_cue_play audiolib_cue_play;

    //3D sounds shit

    //.text:003C3460 rfg.exe:$83460 #82860 <audiolib_get_listener_pos> //audiolib_result __cdecl audiolib_get_listener_pos(vector* position, vector* orient, vector* velocity)
    using F_audiolib_get_listener_pos = audiolib_result(__cdecl*)(vector* position, vector* orient, vector* velocity);
    extern F_audiolib_get_listener_pos audiolib_get_listener_pos;

    //.text:003DFD60 rfg.exe:$9FD60 #9F160 <audiolib_cue_play_3d> //int __cdecl audiolib_cue_play_3d(int cue_id, vector *pos, vector *orient, vector *velocity, audiolib_result *error)
    using F_audiolib_cue_play_3d = int(__cdecl*)(int cue_id, vector* pos, vector* orient, vector* velocity, audiolib_result* error);
    extern F_audiolib_cue_play_3d audiolib_cue_play_3d;



    //.text:00CEE450 rfg.exe:$3EE450 #3ED850 <gamestate_gp_process> //void __cdecl gamestate_gp_process()
    using F_gamestate_gp_process = void(__cdecl*)();
    extern F_gamestate_gp_process gamestate_gp_process;

    //.text:00CC1690 rfg.exe:$3C1690 #3C0A90 <game_is_paused> //bool __cdecl game_is_paused()
    using F_game_is_paused = bool(__cdecl*)();
    extern F_game_is_paused game_is_paused;

    //.text:018746F0 rfg.exe:$6D46F0 #6D3AF0 <human_fire_ignite> //bool __cdecl human_fire_ignite(human *hp_to_ignite, human *killer_hp)
    using F_human_fire_ignite = bool(__cdecl*)(Human* hp_to_ignite, Human* killer_hp);
    extern F_human_fire_ignite human_fire_ignite;

    //.text:017F5B20 rfg.exe:$655B20 #654F20 <human_fire_stop> //void __cdecl human_fire_stop(unsigned int object_handle)
    using F_human_fire_stop = void(__cdecl*)(unsigned int object_handle);
    extern F_human_fire_stop human_fire_stop;

    //unsigned int __cdecl effects_play(unsigned int effect_handle, vector *pos, matrix *orient, bool looping, unsigned int host_handle, int host_tag, 
    //unsigned int source_handle, float effect_volume, bool attach_to_camera, object_effect_category category)

    //unsigned int __cdecl effects_play(effect_info *info, vector *pos, matrix *orient, bool looping, unsigned int host_handle, int host_tag,
    //unsigned int source_handle, float effect_volume, bool attach_to_camera, object_effect_category category)

    //.text:013756A0 rfg.exe:$1D56A0 #1D4AA0 <rfg_init_stage_2_done> //void __cdecl rfg_init_stage_2_done(keen::SoundSystem::System *pSoundSystem)
    using F_rfg_init_stage_2_done = void(__cdecl*)(void* pSoundSystem); //keen::SoundSystem::System
    extern F_rfg_init_stage_2_done rfg_init_stage_2_done;

    //.text:01372480 rfg.exe:$1D2480 #1D1880 <rfg_init_stage_2_done_2> //void __cdecl rfg_init_stage_2_done_2()
    using F_rfg_init_stage_2_done_2 = void(__cdecl*)();
    extern F_rfg_init_stage_2_done_2 rfg_init_stage_2_done_2;

    //.text:01569430 rfg.exe:$3C9430 #3C8830 <verify_gamesave_exit_notify> //bool __cdecl verify_gamesave_exit_notify(game_state new_state)
    using F_verify_gamesave_exit_notify = bool(__cdecl*)(GameState new_state);
    extern F_verify_gamesave_exit_notify verify_gamesave_exit_notify;

    //.text:015B7730 rfg.exe:$417730 #416B30 <havok_body_force_activate> //void __cdecl havok_body_force_activate(unsigned int handle)
    using F_havok_body_force_activate = void(__cdecl*)(uint handle);
    extern F_havok_body_force_activate havok_body_force_activate;

    //.text:015C3DA0 rfg.exe:$423DA0 #4231A0 <havok_body_set_movable> //void __cdecl havok_body_set_movable(unsigned int handle, bool movable)
    using F_havok_body_set_movable = void(__cdecl*)(uint handle, bool movable);
    extern F_havok_body_set_movable havok_body_set_movable;

    //.text:015C3DD0 rfg.exe:$423DD0 #4231D0 <havok_body_get_mass> //float __cdecl havok_body_get_mass(unsigned int handle)
    using F_havok_body_get_mass = float(__cdecl*)(uint handle);
    extern F_havok_body_get_mass havok_body_get_mass;

    //.text:018DA790 rfg.exe:$73A790 #739B90 <objective_highlight_add> //void __cdecl objective_highlight_add(unsigned int handle, highlight_purpose color_hint, highlight_style style)
    using F_objective_highlight_add = void(__cdecl*)(unsigned int handle, highlight_purpose color_hint, highlight_style style);
    extern F_objective_highlight_add objective_highlight_add;

    //.text:018DA840 rfg.exe:$73A840 #739C40 <objective_highlight_remove> //void __cdecl objective_highlight_remove(unsigned int handle)
    using F_objective_highlight_remove = void(__cdecl*)(unsigned int handle);
    extern F_objective_highlight_remove objective_highlight_remove;

    //.text:018DA8B0 rfg.exe:$73A8B0 #739CB0 <objective_highlight_remove_all> //void __cdecl objective_highlight_remove_all()
    using F_objective_highlight_remove_all = void(__cdecl*)();
    extern F_objective_highlight_remove_all objective_highlight_remove_all;

    //.text:016E1430 rfg.exe:$541430 #540830 <world::load_territory> //bool __thiscall world::load_territory(world *this)
    using F_world_load_territory = bool(__fastcall*)(World* this_ptr, void* edx); //2nd arg is edx, needed for __thiscall functions.
    extern F_world_load_territory world_load_territory;

    //.text:018F6000 rfg.exe:$756000 #755400 <can_drop_vehicle> //bool __cdecl can_drop_vehicle(vehicle_info *v_info, farray<object *,256> *delete_object_list, vector *position, matrix *orient, unsigned int ignore_object, bool high_priority)
    using F_can_drop_vehicle = bool(__cdecl*)(vehicle_info* v_info, rfg::farray<object*, 256>* delete_object_list, vector* position, matrix* orient, unsigned int ignore_object, bool high_priority);
    extern F_can_drop_vehicle can_drop_vehicle;

    //.text:005BDA30 rfg.exe:$39DA30 #39CE30 <mission_get_name> //const char *__cdecl mission_get_name()
    using F_mission_get_name = const char*(__cdecl*)();
    extern F_mission_get_name mission_get_name;

    //.text:005BDA60 rfg.exe:$39DA60 #39CE60 <mission_get_description> //const char *__cdecl mission_get_description()
    using F_mission_get_description = const char*(__cdecl*)();
    extern F_mission_get_description mission_get_description;



    //.text:019D81F0 rfg.exe:$7B81F0 #7B75F0 <vehicle_interaction_request_enter> //bool __cdecl vehicle_interaction_request_enter(human *hp, vehicle *vp, vi_enter_data *parameters)
    using F_vehicle_interaction_request_enter = bool(__cdecl*)(Human* hp, vehicle* vp, vi_enter_data* parameters);
    extern F_vehicle_interaction_request_enter vehicle_interaction_request_enter;

    //.text:019D6060 rfg.exe:$7B6060 #7B5460 <vehicle_interaction_request_exit> //void __cdecl vehicle_interaction_request_exit(human *hp, vi_exit_data *parameters)
    using F_vehicle_interaction_request_exit = void(__cdecl*)(Human* hp, vi_exit_data* parameters);
    extern F_vehicle_interaction_request_exit vehicle_interaction_request_exit;

    //.text:01997540 rfg.exe:$777540 #776940 <vehicle::engine_start> //void __thiscall vehicle::engine_start(vehicle *this, bool player)
    using F_vehicle_engine_start = void(__fastcall*)(vehicle* this_ptr, void* edx, bool player); //2nd arg is edx, needed for __thiscall functions.
    extern F_vehicle_engine_start vehicle_engine_start;

    //.text:01997690 rfg.exe:$777690 #776A90 <vehicle::engine_stop> //void __thiscall vehicle::engine_stop(vehicle *this, bool player, bool streamout)
    using F_vehicle_engine_stop = bool(__fastcall*)(vehicle* this_ptr, void* edx, bool player, bool streamout); //2nd arg is edx, needed for __thiscall functions.
    extern F_vehicle_engine_stop vehicle_engine_stop;

    //.text:0199E4B0 rfg.exe:$77E4B0 #77D8B0 <flyer::engine_start> //void __thiscall flyer::engine_start(flyer *this, bool is_player)
    using F_flyer_engine_start = bool(__fastcall*)(flyer* this_ptr, void* edx, bool is_player); //2nd arg is edx, needed for __thiscall functions.
    extern F_flyer_engine_start flyer_engine_start;

    //.text:0199E4F0 rfg.exe:$77E4F0 #77D8F0 <flyer::engine_stop> //void __thiscall flyer::engine_stop(flyer *this, bool is_player, bool unused)
    using F_flyer_engine_stop = bool(__fastcall*)(flyer* this_ptr, void* edx, bool unused); //2nd arg is edx, needed for __thiscall functions.
    extern F_flyer_engine_stop flyer_engine_stop;

    ////.text:019A8B50 rfg.exe:$788B50 #787F50 <automobile::engine_start> //void __thiscall automobile::engine_start(automobile *this, bool player)
    //using F_world_load_territory = bool(__fastcall*)(World* this_ptr, void* edx); //2nd arg is edx, needed for __thiscall functions.
    //extern F_world_load_territory world_load_territory;
    //
    ////.text:019A8BC0 rfg.exe:$788BC0 #787FC0 <automobile::engine_stop> //void __thiscall automobile::engine_stop(automobile *this, bool player, bool unused)
    //using F_world_load_territory = bool(__fastcall*)(World* this_ptr, void* edx); //2nd arg is edx, needed for __thiscall functions.
    //extern F_world_load_territory world_load_territory;


    //.text:017237A0 rfg.exe:$4237A0 #422BA0 <havok_body_get_linear_velocity> //void __cdecl havok_body_get_linear_velocity(unsigned int handle, vector& vel)
    using F_havok_body_get_linear_velocity = void(__cdecl*)(uint handle, vector& vel);
    extern F_havok_body_get_linear_velocity havok_body_get_linear_velocity;

    //.text:01723990 rfg.exe:$423990 #422D90 <havok_body_get_linear_dampening> //float __cdecl havok_body_get_linear_dampening(unsigned int handle)
    using F_havok_body_get_linear_dampening = float(__cdecl*)(uint handle);
    extern F_havok_body_get_linear_dampening havok_body_get_linear_dampening;

    //.text:017237E0 rfg.exe:$4237E0 #422BE0 <havok_body_set_linear_velocity> //void __cdecl havok_body_set_linear_velocity(unsigned int handle, vector& velocity)
    using F_havok_body_set_linear_velocity = void(__cdecl*)(uint handle, vector& velocity);
    extern F_havok_body_set_linear_velocity havok_body_set_linear_velocity;

    //.text:01723890 rfg.exe:$423890 #422C90 <havok_body_set_linear_dampening> //void __cdecl havok_body_set_linear_dampening(unsigned int handle, float linear_dampening)
    using F_havok_body_set_linear_dampening = void(__cdecl*)(uint handle, float linear_dampening);
    extern F_havok_body_set_linear_dampening havok_body_set_linear_dampening;

    //.text:017238D0 rfg.exe:$4238D0 #422CD0 <havok_body_set_angular_dampening> //void __cdecl havok_body_set_angular_dampening(unsigned int handle, float angular_dampening)
    using F_havok_body_set_angular_dampening = void(__cdecl*)(uint handle, float angular_dampening);
    extern F_havok_body_set_angular_dampening havok_body_set_angular_dampening;

    //.text:01723910 rfg.exe:$423910 #422D10 <havok_body_set_angular_velocity> //void __cdecl havok_body_set_angular_velocity(unsigned int handle, vector& ang_velocity)
    using F_havok_body_set_angular_velocity = void(__cdecl*)(uint handle, vector& ang_velocity);
    extern F_havok_body_set_angular_velocity havok_body_set_angular_velocity;

    //.text:01717510 rfg.exe:$417510 #416910 <havok_body_get_angular_velocity> //void __cdecl havok_body_get_angular_velocity(unsigned int handle, vector& vel)
    using F_havok_body_get_angular_velocity = void(__cdecl*)(uint handle, vector& vel);
    extern F_havok_body_get_angular_velocity havok_body_get_angular_velocity;

    //.text:017239D0 rfg.exe:$4239D0 #422DD0 <havok_body_get_angular_dampening> //float __cdecl havok_body_get_angular_dampening(unsigned int handle)
    using F_havok_body_get_angular_dampening = float(__cdecl*)(uint handle);
    extern F_havok_body_get_angular_dampening havok_body_get_angular_dampening;


    //.text:00B727F0 rfg.exe:$1C27F0 #1C1BF0 <cf_open> cfile* __cdecl cf_open(const char *filename_in, const char *mode, vlib_platform disk_platform, bool async)
    using F_cf_open = cfile*(__cdecl*)(const char* filename_in, const char* mode, vlib_platform disk_platform, bool async);
    extern F_cf_open cf_open;


    //.text:00CF78B0 rfg.exe:$3478B0 #346CB0 <effects_template_find> //vfx_effect_template *__cdecl effects_template_find(const char *name)
    using F_effects_template_find = vfx_effect_template*(__cdecl*)(const char* name);
    extern F_effects_template_find effects_template_find;
    
    //.text:0126A700 rfg.exe:$8BA700 #8B9B00 <vfx_effect_create> //vfx_effect *__cdecl vfx_effect_create(vfx_effect_template *effect_template_p)
    using F_vfx_effect_create = vfx_effect*(__cdecl*)(vfx_effect_template* effect_template_p);
    extern F_vfx_effect_create vfx_effect_create;

    //.text:01253D80 rfg.exe:$8A3D80 #8A3180 <vfx_effect::enable_emission> //void __thiscall vfx_effect::enable_emission(vfx_effect *this, bool enabled)
    using F_vfx_effect_enable_emission = void(__fastcall*)(vfx_effect* this_ptr, void* edx, bool enabled);
    extern F_vfx_effect_enable_emission vfx_effect_enable_emission;

    //.text:0124EE70 rfg.exe:$89EE70 #89E270 <vfx_effect::enable_coronas> //void __thiscall vfx_effect::enable_coronas(vfx_effect *this, bool enabled)
    using F_vfx_effect_enable_coronas = void(__fastcall*)(vfx_effect* this_ptr, void* edx, bool enabled);
    extern F_vfx_effect_enable_coronas vfx_effect_enable_coronas;

    //.text:01268210 rfg.exe:$8B8210 #8B7610 <vfx_effect::update> //void __thiscall vfx_effect::update(vfx_effect *this, float delta_time)
    using F_vfx_effect_update = void(__fastcall*)(vfx_effect* this_ptr, void* edx, float delta_time);
    extern F_vfx_effect_update vfx_effect_update;

    //.text:00CF7910 rfg.exe:$347910 #346D10 <effects_play>
    //unsigned int __cdecl effects_play(unsigned int effect_handle, vector *pos, matrix *orient, bool looping, unsigned int host_handle, int host_tag,
    //unsigned int source_handle, float effect_volume, bool attach_to_camera, object_effect_category category)
    using F_effects_play = uint(__cdecl*)(uint effect_handle, vector* pos, matrix* orient, bool looping, uint host_handle, int host_tag, uint source_handle, float effect_volume, bool attach_to_camera, object_effect_category category);
    extern F_effects_play effects_play;


    //.text:01020BA0 rfg.exe:$670BA0 #66FFA0 <squad_definition_from_name> squad_definition *__cdecl squad_definition_from_name(const char *name)
    using F_squad_definition_from_name =  squad_definition*(__cdecl*)(const char* name);
    extern F_squad_definition_from_name squad_definition_from_name;

    //.text:00D60E00 rfg.exe:$3B0E00 #3B0200 <squad_spawn_parameters::spawn_squad> //object_squad*__thiscall fav::squad_spawn_parameters::spawn_squad(squad_spawn_parameters *this)
    using F_squad_spawn_parameters_spawn_squad = object_squad*(__fastcall*)(squad_spawn_parameters* this_ptr, void* edx);
    extern F_squad_spawn_parameters_spawn_squad squad_spawn_parameters_spawn_squad;

    //.text:00D9CCA0 rfg.exe:$20CCA0 #20C0A0 <squad_spawn_parameters::squad_spawn_parameters> //void __thiscall squad_spawn_parameters::squad_spawn_parameters(squad_spawn_parameters *this)
    using F_squad_spawn_parameters_constructor = void(__fastcall*)(squad_spawn_parameters* this_ptr, void* edx);
    extern F_squad_spawn_parameters_constructor squad_spawn_parameters_constructor;

    //.text:00F055E0 rfg.exe:$3755E0 #3749E0 <squad_creation_parameters::create_squad> //object_squad *__thiscall squad_creation_parameters::create_squad(squad_creation_parameters *this)
    using F_squad_spawn_parameters_create_squad = object_squad*(__fastcall*)(squad_spawn_parameters* this_ptr, void* edx);
    extern F_squad_spawn_parameters_create_squad squad_spawn_parameters_create_squad;

    //.text:00D2FED0 rfg.exe:$37FED0 #37F2D0 <find_local_spawn_region> //object_spawn_region *__cdecl find_local_spawn_region(bool ped_only)
    using F_find_local_spawn_region = object_spawn_region*(__cdecl*)(bool ped_only);
    extern F_find_local_spawn_region find_local_spawn_region;

    //.text:00F20AE0 rfg.exe:$390AE0 #38FEE0 <find_local_building> //rfg_mover *__cdecl find_local_building(vector& pos)
    using F_find_local_building = rfg_mover*(__cdecl*)(vector& pos);
    extern F_find_local_building find_local_building;

    //.text:01224C20 rfg.exe:$694C20 #694020 <object_squad::spawn_members> //bool __thiscall object_squad::spawn_members(object_squad *this, bool force_spawn, object_spawn_region *osrp)
    using F_object_squad_spawn_members = void(__fastcall*)(object_squad* this_ptr, void* edx, bool force_spawn, object_spawn_region* osrp);
    extern F_object_squad_spawn_members object_squad_spawn_members;

    //.text:012C7C10 rfg.exe:$737C10 #737010 <gem_post_event> //void __cdecl gem_post_event(event_data& data)
    using F_gem_post_event = void(__cdecl*)(event_data& data);
    extern F_gem_post_event gem_post_event;

    //.text:00EA8FF0 rfg.exe:$318FF0 #3183F0 <world::create_object<general_mover>>
    //general_mover *__thiscall world::create_object<general_mover>(world *this, obj_prop_block *pblock, unsigned int parent)
    using F_world_create_object_general_mover = general_mover*(__fastcall*)(World* this_ptr, void* edx, obj_prop_block* pblock, unsigned int parent);
    extern F_world_create_object_general_mover world_create_object_general_mover;

    //.text:011C3DD0 rfg.exe:$633DD0 #6331D0 <player::create_a_player_squad> //unsigned int __thiscall player::create_a_player_squad(player *this, squad_definition *squad_def)
    using F_player_create_player_squad = uint(__fastcall*)(Player * this_ptr, void* edx, squad_definition * squad_def);
    extern F_player_create_player_squad player_create_player_squad;

    //.text:0127B8D0 rfg.exe:$6EB8D0 #6EACD0 <rfg_snap_to_ground> //bool __cdecl rfg_snap_to_ground(vector& pos)
    using F_rfg_snap_to_ground = bool(__cdecl*)(vector& data);
    extern F_rfg_snap_to_ground rfg_snap_to_ground;

    //.text:01775F50 rfg.exe:$775F50 #775350 <automobile_honk_horn> //void __cdecl automobile_honk_horn(unsigned int a_handle)
    using F_automobile_honk_horn = void(__cdecl*)(uint a_handle);
    extern F_automobile_honk_horn automobile_honk_horn;

    //.text:009A8A00 rfg.exe:$528A00 #527E00 <chunk_get_base_by_name> //c_chunk_base *__cdecl chunk_get_base_by_name(const char *name)
    //using F_chunk_get_base_by_name = c_chunk_base*(__cdecl*)(uint a_handle);
    using F_chunk_get_base_by_name = void*(__cdecl*)(const char* name); //Todo: Bind c_chunk_base and make the return type proper
    extern F_chunk_get_base_by_name chunk_get_base_by_name;

    //.text:00ADFA00 rfg.exe:$65FA00 #65EE00 <object_mover_create_from_chunk> //object_mover *__cdecl object_mover_create_from_chunk(vector& pos, matrix& orient, c_chunk_base *base, unsigned int parent_handle)
    using F_object_mover_create_from_chunk = object_mover*(__cdecl*)(vector& pos, matrix & orient, void* base, uint parent_handle); //Todo: Bind c_chunk_base and base type proper
    extern F_object_mover_create_from_chunk object_mover_create_from_chunk;

    //.text:006872F0 rfg.exe:$6172F0 #6166F0 <object_debris::create_havok_body> //void __thiscall object_debris::create_havok_body(object_debris *this, debris_create_info *dci)
    using F_object_debris_create_havok_body = void(__fastcall*)(object_debris* this_ptr, void* edx, debris_create_info* dci);
    extern F_object_debris_create_havok_body object_debris_create_havok_body;

    //Functions needed:
    //obj_prop_block::obj_prop_block(object_prop_block* this, vector* pos, matrix* orient, char* name (can be null))
        //void __thiscall obj_prop_block::obj_prop_block(obj_prop_block *this, vector *pos, matrix *orient, const char *name)
    //obj_prop* rfg_prop_block::set_internal(rfg_prop_block* this, prop_name* prop_name, int sizeInBytes, int type)
        // obj_prop *__thiscall rfg_prop_block::set_internal(rfg_prop_block *this, prop_name *name, int size, int type)
    //object *__thiscall world::create_object_internal(world *this, unsigned int classname_hash, obj_prop_block *pblock, world_zone *origin_zone, unsigned int parent)
    //Todo: Get all X_PROP_TYPE Addresses so we don't need to make them ourselves.


    //.text:01618B00 rfg.exe:$638B00 #637F00 <obj_prop_block::obj_prop_block>
    //void __thiscall obj_prop_block::obj_prop_block(obj_prop_block *this, vector& pos, matrix& orient, const char *name)
    using F_obj_prop_block_constructor = void(__fastcall*)(obj_prop_block* this_ptr, void* edx, vector& pos, matrix& orient, const char* name);
    extern F_obj_prop_block_constructor obj_prop_block_constructor;

    //.text:014FA6E0 rfg.exe:$51A6E0 #519AE0 <rfg_prop_block::set_internal>
    // obj_prop *__thiscall rfg_prop_block::set_internal(rfg_prop_block *this, prop_name& name, int size, int type)
    using F_rfg_prop_block_set_internal = obj_prop*(__fastcall*)(rfg_prop_block* this_ptr, void* edx, prop_name& name, int size, int type);
    extern F_rfg_prop_block_set_internal rfg_prop_block_set_internal;

    //.text:0151E6B0 rfg.exe:$53E6B0 #53DAB0 <world::create_object_internal>
    //object *__thiscall world::create_object_internal(world *this, unsigned int classname_hash, obj_prop_block& pblock, world_zone *origin_zone, unsigned int parent)
    using F_world_create_object_internal = object*(__fastcall*)(World* this_ptr, void* edx, unsigned int classname_hash, obj_prop_block& pblock, world_zone* origin_zone, unsigned int parent);
    extern F_world_create_object_internal world_create_object_internal;

    extern object* CreateObjectFromZoneObjectBinary(std::string path, vector& pos, matrix& orient, const char* name);

    //.text:01348CC0 rfg.exe:$368CC0 #3680C0 <obj_auto_props::obj_auto_props>
    //void __thiscall obj_auto_props::obj_auto_props(obj_auto_props *this, int type_index, vector *pos, matrix *orient, bool pos_at_ground)
    using F_obj_auto_props_constructor = void(__fastcall*)(obj_auto_props* this_ptr, void* edx, int type_index, vector& pos, matrix& orient, bool pos_at_ground);
    extern F_obj_auto_props_constructor obj_auto_props_constructor;

    //.text:011E58C0 rfg.exe:$2058C0 #204CC0 <obj_projectile_props::obj_projectile_props>
    //void __thiscall obj_projectile_props::obj_projectile_props(obj_projectile_props *this, unsigned int owner_handle, item_info *info, obj_item_flags *flags, weapon_info *w_info, vector *pos, matrix *orient, vector *velocity, vector *target, const unsigned int create_id)
    using F_obj_projectile_props_constructor = void(__fastcall*)(obj_projectile_props* this_ptr, void* edx, uint owner_handle, item_info* info, obj_item_flags& flags, weapon_info* w_info, vector& pos, matrix& orient, vector& velocity, vector& target, uint create_id);
    extern F_obj_projectile_props_constructor obj_projectile_props_constructor;
    //Todo: Get Item_infos list
    //Todo: Start moving class member funcs into relevant classes by having normal funcs wrapping the function ptr. Make sure still works with hooked funcs

    //uint __cdecl str_hash_string(const char *str) //.text:011737D0 rfg.exe:$1937D0 #192BD0 <str_hash_string>
    using F_str_hash_string = uint(__cdecl*)(const char* str);
    extern F_str_hash_string str_hash_string;

    //item *__cdecl amb_prop_create(ambient_prop_info *amb_prop_info, vector& pos, matrix& orient, unsigned int parent_handle) //.text:01726DB0 rfg.exe:$746DB0 #7461B0 <amb_prop_create>
    using F_amb_prop_create = item*(__cdecl*)(ambient_prop_info* amb_prop_info, vector& pos, matrix& orient, unsigned int parent_handle);
    extern F_amb_prop_create amb_prop_create;

    //.text:017CB270 rfg.exe:$7EB270 #7EA670 <weapon::fire> //void __thiscall weapon::fire(weapon *this, vector aim_override)
    using F_weapon_fire = void(__fastcall*)(weapon* this_ptr, void* edx, vector aim_override);
    extern F_weapon_fire weapon_fire;
}
