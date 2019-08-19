
/* Functions.h/.cpp contain function pointers for many of rfg's functions. They can be used
 * to call rfg's functions for our own use, and also to hook these functions and expand their
 * behavior. These function pointers are initialized in FunctionManager.cpp. The declarations
 * here are only used to define the inputs, calling conventions, and returns of these functions.
 */

#pragma once
#include "ItsyBitsy.h"
//#include "RFGR Structs/KeenNamespace.h"

extern void DisableCameraCode(DWORD AddressY, DWORD AddressZ); //Takes addresses for instructions affecting y and z. Alternatively x and z may work, since one piece seems to be shared between two coords.
extern void RestoreCameraCode();
extern void DisableCameraDirectionCode(DWORD Address1, DWORD Address2, DWORD Address3, DWORD Address4, DWORD Address5);
extern void RestoreCameraDirectionCode();

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
using F_HavokBodyGetPositionAndOrient = void(__cdecl*)(unsigned int Handle, vector* Position, matrix* Orient);
extern F_HavokBodyGetPositionAndOrient HavokBodyGetPositionAndOrient;

//.text:007D6EA0 rfg.exe:$416EA0 #4162A0 <havok_body_set_position> //void __cdecl havok_body_set_position(unsigned int handle, vector *pos)
using F_HavokBodySetPosition = void(__cdecl*)(unsigned int Handle, vector* Position);
extern F_HavokBodySetPosition HavokBodySetPosition;

//.text:007D6E10 rfg.exe:$416E10 #416210 <havok_body_set_pos_orient>

//.text:007E3700 rfg.exe:$423700 #422B00 <havok_body_set_pos_orient>
using F_HavokBodySetPositionAndOrient = void(__cdecl*)(unsigned int Handle, vector* Position, matrix* Orient);
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



/*Many of the funcs below were defined above when the code style was different.*/

//.text:00679AC0 rfg.exe:$2C9AC0 #2C8EC0 <CameraStartFirstPerson>
//.text:00679B60 rfg.exe:$2C9B60 #2C8F60 <CameraStopFirstPerson>

//.text:00694E30 rfg.exe:$2E4E30 #2E4230 <XrayEffectStart>
//.text:00694E50 rfg.exe:$2E4E50 #2E4250 <XrayEffectStop>

//.text:00E18AC0 rfg.exe:$168AC0 #167EC0 <KeyDown>
//.text:01072F10 rfg.exe:$3C2F10 #3C2310 <GameRenderSetBloomExposureFactor>

//.text:0107F210 rfg.exe:$3CF210 #3CE610 <__Game_render_stats::__Game_render_stats>
//.text:01072BB0 rfg.exe:$3C2BB0 #3C1FB0 <GameRenderSetHdrState>

//.text:01232500 rfg.exe:$3C2500 #3C1900 <GameRender2dText>
//.text:01311C00 rfg.exe:$4A1C00 #4A1000 <UiAddDebugText>

//.text:00F28B40 rfg.exe:$B8B40 #B7F40 <rl_camera::GetDepthOfFieldEnabled>
//.text:01231820 rfg.exe:$3C1820 #3C0C20 <rl_camera::SetDepthOfFieldEnabled>

//.text:00FA53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

//.text:00EEF7F0 rfg.exe:$43F7F0 #43EBF0 <FogOfWarClear>






///POSSIBLE DUPLICATES BELOW

//.text:0075BA80 rfg.exe:$55BA80 #55AE80 <DebugSpewProjectile> //Did nothing
//.text:00755EB0 rfg.exe:$555EB0 #5552B0 <DebugSpewGameIo>
//.text:01267B60 rfg.exe:$B7B60 #B6F60 <rl_render_lib::get_metrics>

//.text:00684760 rfg.exe:$484760 #483B60 <interface_debug_mode_activate> //Did nothing
//.text:009F48D0 rfg.exe:$7F48D0 #7F3CD0 <keen::debug::writeToLogFile>
//.text:00641A90 rfg.exe:$441A90 #440E90 <hud_hide>
//.text:00641AC0 rfg.exe:$441AC0 #440EC0 <hud_is_hidden>
//.text:00642D80 rfg.exe:$442D80 #442180 <hud_display_distance>
//.text:0038CDB0 rfg.exe:$18CDB0 #18C1B0 <console_enable_chat_window>

//.text:003CD150 rfg.exe:$1CD150 #1CC550 <console_init>
//.text:0038CAC0 rfg.exe:$18CAC0 #18BEC0 <console_activate>
//.text:003AF950 rfg.exe:$1AF950 #1AED50 <console_deactivate>

//.text:003AF470 rfg.exe:$1AF470 #1AE870 <console_printf>
//.text:003C4B50 rfg.exe:$1C4B50 #1C3F50 <console_display_help>
//.text:003C54B0 rfg.exe:$1C54B0 #1C48B0 <console_command_enable>
//.text:003C5000 rfg.exe:$1C5000 #1C4400 <console_do_command>

//.text:004CCB90 rfg.exe:$2CCB90 #2CBF90 <camera_start_satellite_mode> //Caused crash
//.text:00469C80 rfg.exe:$2C9C80 #2C9080 <camera_first_person_pre_process>
//.text:004C9AC0 rfg.exe:$2C9AC0 #2C8EC0 <CameraStartFirstPerson> //Set at masons feet, perhaps could work with some edits
//.text:004CF0C0 rfg.exe:$2CF0C0 #2CE4C0 <camera_start_third_person> //Works
//.text:004D3FE0 rfg.exe:$2D3FE0 #2D33E0 <camera_start_lookaround_mode> //Third person viewed in, not very useful
//.text:77121812 kernelbase.dll:$111812 #110C12 //Camera_first_person_offset. Not sure if this is a function or what

//.text:00560A90 rfg.exe:$3C0A90 #3BFE90 <game_print_screen>
//.text:004705D0 rfg.exe:$2D05D0 #2CF9D0 <camera_set_view_player>
//.text:004645B0 rfg.exe:$2C45B0 #2C39B0 <CameraFreeSystemInit>
//.text:00475610 rfg.exe:$2D5610 #2D4A10 <CameraFreeModeInit>
//.text:00464DE0 rfg.exe:$2C4DE0 #2C41E0 <camera_free_render_debug>
//.text:0034F4B0 rfg.exe:$1AF4B0 #1AE8B0 <ConsoleChatPrintf>
//.text:0056F220 rfg.exe:$3CF220 #3CE620 <UnusedDcfRShowMemUsage>
//.text:004B4C40 rfg.exe:$314C40 #314040 <RfgDynGetActiveDestructionFrame>
//.text:004B4C30 rfg.exe:$314C30 #314030 <RfgDynResetDestructionFrame>
//.text:004B3750 rfg.exe:$313750 #312B50 <RfgDynSystemShutdown>
//.text:001F8AE0 rfg.exe:$58AE0 #57EE0 <rl_screen_info::GetScreenWidth>
//.text:0032CAD0 rfg.exe:$18CAD0 #18BED0 <ConsoleIsActive>
//.text:01898690 rfg.exe:$6E8690 #6E7A90 <ProfileDumpInfo>

//.text:01034FE0 rfg.exe:$64FE0 #643E0 <VintRenderText>


//.text:01390450 rfg.exe:$3C0450 #3BF850 <rl_scene::set_time_of_day_value>

//.text:006866E0 rfg.exe:$2D66E0 #2D5AE0 <camera_move>

//.text:0068D250 rfg.exe:$2DD250 #2DC650 <camera_third_person_process>

//.text:00679AC0 rfg.exe:$2C9AC0 #2C8EC0 <CameraStartFirstPerson>
//.text:00679B60 rfg.exe:$2C9B60 #2C8F60 <CameraStopFirstPerson>
//.text:00679C80 rfg.exe:$2C9C80 #2C9080 <camera_first_person_pre_process>
//.text:0067AA00 rfg.exe:$2CAA00 #2C9E00 <camera_first_person_process>

//.text:0067CB40 rfg.exe:$2CCB40 #2CBF40 <camera_stop_satellite_mode_internal>
//.text:0067CB90 rfg.exe:$2CCB90 #2CBF90 <camera_start_satellite_mode>
//.text:0067CDB0 rfg.exe:$2CCDB0 #2CC1B0 <camera_stop_satellite_mode>
//.text:0068A650 rfg.exe:$2DA650 #2D9A50 <camera_satellite_get_base_height>
//.text:0068A7A0 rfg.exe:$2DA7A0 #2D9BA0 <camera_satellite_process>

//.text:006809B0 rfg.exe:$2D09B0 #2CFDB0 <camera_start_slew_mode>
//.text:006809C0 rfg.exe:$2D09C0 #2CFDC0 <camera_stop_slew_mode>

//.text:006809D0 rfg.exe:$2D09D0 #2CFDD0 <camera_start_cursor_mode>
//.text:006809E0 rfg.exe:$2D09E0 #2CFDE0 <camera_stop_cursor_mode>

//.text:006809F0 rfg.exe:$2D09F0 #2CFDF0 <camera_start_dumb_mode>
//.text:00680A00 rfg.exe:$2D0A00 #2CFE00 <camera_stop_dumb_mode>

//.text:00680A10 rfg.exe:$2D0A10 #2CFE10 <camera_start_turret_mode>
//.text:00680B00 rfg.exe:$2D0B00 #2CFF00 <camera_stop_turret_mode>

//.text:00772C60 rfg.exe:$3C2C60 #3C2060 <game_render_get_fog_enabled>
//.text:00772C70 rfg.exe:$3C2C70 #3C2070 <GameRenderSetFogEnabled>

//.text:00694E30 rfg.exe:$2E4E30 #2E4230 <XrayEffectStart>
//.text:00694E50 rfg.exe:$2E4E50 #2E4250 <XrayEffectStop>
//.text:00694E70 rfg.exe:$2E4E70 #2E4270 <xray_effect_is_enabled>

//.text:00E18AC0 rfg.exe:$168AC0 #167EC0 <KeyDown>

//.text:01072F10 rfg.exe:$3C2F10 #3C2310 <GameRenderSetBloomExposureFactor>

//.text:01232500 rfg.exe:$3C2500 #3C1900 <GameRender2dText>
//.text:01311C00 rfg.exe:$4A1C00 #4A1000 <UiAddDebugText>

//.text:00F28B40 rfg.exe:$B8B40 #B7F40 <rl_camera::GetDepthOfFieldEnabled>
//.text:01231820 rfg.exe:$3C1820 #3C0C20 <rl_camera::SetDepthOfFieldEnabled>

//.text:00FA53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

//.text:00EEF7F0 rfg.exe:$43F7F0 #43EBF0 <FogOfWarClear>

//.text:005B09C0 rfg.exe:$2D09C0 #2CFDC0 <camera_stop_slew_mode>
//.text:005A9AC0 rfg.exe:$2C9AC0 #2C8EC0 <CameraStartFirstPerson>


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
using F_havok_body_apply_linear_impulse_A = void(__cdecl*)(hkpRigidBody* rb, vector* linear_impulse);
extern F_havok_body_apply_linear_impulse_A HavokBodyApplyLinearImpulseA;

//.text:01273C20 rfg.exe:$423C20 #423020 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(unsigned int handle, vector *linear_impulse)
using F_havok_body_apply_linear_impulse_B = void(__cdecl*)(uint handle, vector* linear_impulse);
extern F_havok_body_apply_linear_impulse_B HavokBodyApplyLinearImpulseB;

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
using F_vehicle_info_get_master_list =  rfg::farray<vehicle_info, 163>*(__cdecl*)();
extern F_vehicle_info_get_master_list VehicleInfoGetMasterList;

//.text:00796420 rfg.exe:$756420 #755820 <sp_spawn_vehicle> //bool __cdecl sp_spawn_vehicle(vehicle_spawn_params *spawn_param)
using F_sp_spawn_vehicle = bool(__cdecl*)(vehicle_spawn_params* spawn_param);
extern F_sp_spawn_vehicle SpSpawnVehicle;

//.text:00788960 rfg.exe:$748960 #747D60 <create_new_vehicle> //bool __usercall create_new_vehicle@<al>(vehicle_spawn_params *spawn_param@<eax>)
using F_create_new_vehicle = bool(__cdecl*)();//(vehicle_spawn_params* spawn_param);
extern F_create_new_vehicle create_new_vehicle_raw;

inline bool CreateNewVehicle(vehicle_spawn_params* spawn_params)
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