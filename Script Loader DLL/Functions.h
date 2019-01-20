#pragma once
///#include "Globals.h"
#include "SnippetManager.h"
#include "RFGR_Types_Player.h"

static void DisableCameraCode(DWORD AddressY, DWORD AddressZ) //Takes addresses for instructions affecting y and z. Alternatively x and z may work, since one piece seems to be shared between two coords.
{
	SnippetManager::BackupSnippet("CameraWriteY", AddressY, 8, true);
	SnippetManager::BackupSnippet("CameraWriteZ", AddressZ, 6, true);
	//PlaceNOP((BYTE*)AddressY, 8);
	//PlaceNOP((BYTE*)AddressZ, 6);
}

static void RestoreCameraCode()
{
	SnippetManager::RestoreSnippet("CameraWriteY", true);
	SnippetManager::RestoreSnippet("CameraWriteZ", true);
}

static void DisableCameraDirectionCode(DWORD Address1, DWORD Address2, DWORD Address3, DWORD Address4, DWORD Address5)
{
	SnippetManager::BackupSnippet("CameraRealOrient1", Address1, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient2", Address2, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient3", Address3, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient4", Address4, 8, true);
	SnippetManager::BackupSnippet("CameraRealOrient5", Address5, 6, true);
}

static void RestoreCameraDirectionCode()
{
	SnippetManager::RestoreSnippet("CameraRealOrient1", true);
	SnippetManager::RestoreSnippet("CameraRealOrient2", true);
	SnippetManager::RestoreSnippet("CameraRealOrient3", true);
	SnippetManager::RestoreSnippet("CameraRealOrient4", true);
	SnippetManager::RestoreSnippet("CameraRealOrient5", true);
}

typedef void(__cdecl* F_Camera_Start_Slew_Mode)(void);
extern F_Camera_Start_Slew_Mode Camera_Start_Slew_Mode;

typedef void(__cdecl* F_Camera_Stop_Slew_Mode)(void);
extern F_Camera_Stop_Slew_Mode Camera_Stop_Slew_Mode;

typedef void(__cdecl* F_Interface_Debug_Mode_Activate)(void);
extern F_Interface_Debug_Mode_Activate Interface_Debug_Mode_Activate;

typedef void(__cdecl* F_Keen_Debug_WriteToLogFile)(char* String);
extern F_Keen_Debug_WriteToLogFile Keen_Debug_WriteToLogFile;

typedef void(__cdecl* F_Hud_Display_Distance)(bool Value);
extern F_Hud_Display_Distance Hud_Display_Distance;

typedef void(__cdecl* F_Console_Init)(void);
extern F_Console_Init Console_Init;

typedef void(__cdecl* F_Console_Activate)(void);
extern F_Console_Activate Console_Activate;

typedef void(__cdecl* F_Console_Deactivate)(void);
extern F_Console_Deactivate Console_Deactivate;

typedef void(__cdecl* F_Console_Printf)(const char* String);
extern F_Console_Printf Console_Printf;

typedef void(__cdecl* F_Console_Display_Help)(void);
extern F_Console_Display_Help Console_Display_Help;

typedef void(__cdecl* F_Console_Command_Enable)(const char* String, bool Activate);
extern F_Console_Command_Enable Console_Command_Enable;

typedef void(__cdecl* F_Console_Do_Command)(const char* String);
extern F_Console_Do_Command Console_Do_Command;

typedef void(__cdecl* F_Camera_First_Person_Pre_Process)(void);
extern F_Camera_First_Person_Pre_Process Camera_First_Person_Pre_Process;

typedef void(__cdecl* F_Camera_Start_Third_Person)(void);
extern F_Camera_Start_Third_Person Camera_Start_Third_Person;

typedef void(__cdecl* F_Game_Print_Screen)(char* String);
extern F_Game_Print_Screen Game_Print_Screen;

typedef void(__cdecl* F_camera_free_system_init)(void);
extern F_camera_free_system_init camera_free_system_init;

typedef void(__cdecl* F_camera_free_mode_init)(void);
extern F_camera_free_mode_init camera_free_mode_init;

typedef void(__cdecl* F_console_chat_printf)(const char* String);
extern F_console_chat_printf console_chat_printf;

typedef void(__cdecl* F_unused_dcf_r_show_mem_usage)(void);
extern F_unused_dcf_r_show_mem_usage unused_dcf_r_show_mem_usage;

typedef unsigned __int16(__cdecl* F_rfg_dyn_get_active_destruction_frame)(void);
extern F_rfg_dyn_get_active_destruction_frame rfg_dyn_get_active_destruction_frame;

typedef void(__cdecl* F_rfg_dyn_reset_destruction_frame)(unsigned __int16 Frame);
extern F_rfg_dyn_reset_destruction_frame rfg_dyn_reset_destruction_frame;

typedef void(__cdecl* F_rfg_dyn_system_shutdown)(void);
extern F_rfg_dyn_system_shutdown rfg_dyn_system_shutdown;

typedef int(__cdecl* F_get_screen_width)(void);
extern F_get_screen_width get_screen_width;

typedef bool(__cdecl* F_console_is_active)(void);
extern F_console_is_active console_is_active;

typedef void(__cdecl* F_debug_spew_projectile)(const char* Format);
extern F_debug_spew_projectile debug_spew_projectile;

typedef void(__cdecl* F_debug_spew_game_io)(const char* Format);
extern F_debug_spew_game_io debug_spew_game_io;

typedef rl_renderer_metrics*(__cdecl* F_rl_render_lib_get_metrics)(void);
extern F_rl_render_lib_get_metrics rl_render_lib_get_metrics;

typedef void(__cdecl* F_profile_dump_info)(void);
extern F_profile_dump_info profile_dump_info;

typedef void(__cdecl* F_vint_render_text)(int _handle, const unsigned int* _text, unsigned int _first_char, unsigned int _num_chars, matrix23* _xform, 
	vector2* _pos, bool reversed, vint_res_offset _res_offset_x, vint_res_offset _res_offset_y, vint_res_scale _res_scale_x, vint_res_scale _res_scale_y);
extern F_vint_render_text vint_render_text;

typedef void(__cdecl* F_xray_effect_start)(xray_effect_types xray_effect_type);
extern F_xray_effect_start xray_effect_start;

typedef void(__cdecl* F_xray_effect_stop)(xray_effect_types xray_effect_type);
extern F_xray_effect_stop xray_effect_stop;

typedef void(__cdecl* F_camera_start_first_person)(bool Smooth);
extern F_camera_start_first_person camera_start_first_person;

typedef void(__cdecl* F_camera_stop_first_person)(bool Smooth);
extern F_camera_stop_first_person camera_stop_first_person;

typedef void(__cdecl* F_key_down)(unsigned int Scancode);
extern F_key_down key_down;

typedef void(__cdecl* F_game_render_set_bloom_exposure_factor)(float ExposureFactor);
extern F_game_render_set_bloom_exposure_factor game_render_set_bloom_exposure_factor;

typedef void(__cdecl* F_game_render_set_hdr_state)(rl_hdr_state* hdr_state);
extern F_game_render_set_hdr_state game_render_set_hdr_state;

typedef void(__cdecl* F_game_render_2d_text)(const char* str, vector* text_pos);
extern F_game_render_2d_text game_render_2d_text;

typedef unsigned int(__cdecl* F_ui_add_debug_text)(const char *text, debug_text_posn type);
extern F_ui_add_debug_text ui_add_debug_text;

typedef bool(__thiscall* F_get_depth_of_field_enabled)(void* ThisCamera); //bool __thiscall rl_camera::get_depth_of_field_enabled(rl_camera *this)
extern F_get_depth_of_field_enabled get_depth_of_field_enabled;

typedef void(__thiscall* F_set_depth_of_field_enabled)(void* ThisCamera, bool Enabled); //void __thiscall rl_camera::set_depth_of_field_enabled(rl_camera *this, bool depth_of_field_enabled)
extern F_set_depth_of_field_enabled set_depth_of_field_enabled;

typedef void(__thiscall* F_character_controller_set_pos)(void* ThisController, vector* Position); //void __thiscall character_controller::set_pos(character_controller *this, vector *pos)																			   
extern F_character_controller_set_pos character_controller_set_pos; //IDA shows this as using __thiscall, but using that causes the game to immediately crash

typedef void(__cdecl* F_fog_of_war_clear)(void);
extern F_fog_of_war_clear fog_of_war_clear;

typedef void(__cdecl* F_Hud_Hide)(bool HideHud);
extern F_Hud_Hide Hud_Hide;

typedef void(__cdecl* F_game_render_set_fog_enabled)(bool Enabled);
extern F_game_render_set_fog_enabled game_render_set_fog_enabled;

static void HideHUD(bool Hide)
{
	Hud_Hide(Hide);
}

static void HideFog(bool Hide)
{
	game_render_set_fog_enabled(!Hide);
}

//typedef void (__cdecl* explosion_create)(explosion_info* ExplosionInfo, object* Source, object* Owner, vector* Position, matrix* Orientation, vector* Directiom, weapon_info* WeaponInfo, bool FromServer)
typedef void(__cdecl* F_explosion_create)(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position, matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer);
extern F_explosion_create ExplosionCreate;

//.text:0129DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame>
typedef void(__cdecl* F_keen_graphics_beginframe)(void* GraphicsSystem);
extern F_keen_graphics_beginframe GraphicsBeginFrame;

//.text:00B992B0 rfg.exe:$1692B0 #1686B0 <mouse_generic_auto_centering>
typedef void(__cdecl* F_MouseGenericAutoCentering)(bool AutoCentering);
extern F_MouseGenericAutoCentering MouseGenericAutoCentering;

//.text:00D00290 rfg.exe:$2D0290 #2CF690 <camera_view_data::set_view>
typedef void(__cdecl* F_CameraViewDataSetView)(CameraViewData* ViewData, CameraViewTableEntry* ViewTableEntry, bool SkipTransition);
extern F_CameraViewDataSetView CameraViewDataSetView;

//.text:00A65A80 rfg.exe:$6D5A80 #6D4E80 <player::do_frame>
typedef void(__fastcall* F_PlayerDoFrame)(Player* PlayerPtr);
extern F_PlayerDoFrame PlayerDoFrame;

//.text:00A6ECA0 rfg.exe:$6DECA0 #6DE0A0 <player::player>
typedef void(__fastcall* F_PlayerConstructor)(Player* PlayerPtr);
extern F_PlayerConstructor PlayerConstructor;

//.text:007A53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>
typedef void(__fastcall* F_CharacterControllerSetPos)(CharacterController* CharController, vector* Position);
extern F_CharacterControllerSetPos CharacterControllerSetPos;

//.text:00A1C310 rfg.exe:$68C310 #68B710 <object::update_pos_and_orient> //void __thiscall object::update_pos_and_orient(object *this, vector *update_pos, matrix *update_orient, bool set_havok_data)
typedef void(__fastcall* F_ObjectUpdatePosAndOrient)(Object*, void*, vector*, matrix*, bool); //2nd arg is edx, needed for __thiscall functions.
extern F_ObjectUpdatePosAndOrient ObjectUpdatePosAndOrient;

//.text:009A4DC0 rfg.exe:$614DC0 #6141C0 <object::update_render> //void __thiscall object::update_render(object *this, rl_renderer *__formal)
//.text:009A4D00 rfg.exe:$614D00 #614100 <object::update_streaming_box> //void __thiscall object::update_streaming_box(object *this)

//.text:007E9530 rfg.exe:$429530 #428930 <havok_body_get_pos_orient>
typedef void(__cdecl* F_HavokBodyGetPositionAndOrient)(unsigned int Handle, vector* Position, matrix* Orient);
extern F_HavokBodyGetPositionAndOrient HavokBodyGetPositionAndOrient;

//.text:007D6EA0 rfg.exe:$416EA0 #4162A0 <havok_body_set_position> //void __cdecl havok_body_set_position(unsigned int handle, vector *pos)
typedef void(__cdecl* F_HavokBodySetPosition)(unsigned int Handle, vector* Position);
extern F_HavokBodySetPosition HavokBodySetPosition;

//.text:007D6E10 rfg.exe:$416E10 #416210 <havok_body_set_pos_orient>

//.text:007E3700 rfg.exe:$423700 #422B00 <havok_body_set_pos_orient>
typedef void(__cdecl* F_HavokBodySetPositionAndOrient)(unsigned int Handle, vector* Position, matrix* Orient);
extern F_HavokBodySetPositionAndOrient HavokBodySetPositionAndOrient;

//.text:00A5AF70 rfg.exe:$69AF70 #69A370 <human::update_pos_and_orient> //void __thiscall human::update_pos_and_orient(human *this, vector *update_pos, matrix *update_orient, bool set_havok_data)
typedef void(__fastcall* F_HumanUpdatePosAndOrient)(Human*, void*, vector*, matrix*, bool); //2nd arg is edx, needed for __thiscall functions.
extern F_HumanUpdatePosAndOrient HumanUpdatePosAndOrient;

//.text:00A3C660 rfg.exe:$67C660 #67BA60 <human_teleport_unsafe> //void __cdecl human_teleport_unsafe(human *hp, vector pos, matrix orient)
typedef void(__cdecl* F_HumanTeleportUnsafe)(Human* HumanPtr, vector Position, matrix Orientation);
extern F_HumanTeleportUnsafe HumanTeleportUnsafe;

//.text:00A5A7A0 rfg.exe:$69A7A0 #699BA0 <human_teleport>
/*typedef void(__cdecl* F_HumanTeleport)(Human* HumanPtr, vector* Position, matrix* Orientation, float PlacementRange, bool AllowFail);
extern F_HumanTeleport HumanTeleport;*/



/*Start of MP Detection Hooks*/

//.text:00590DD0 rfg.exe:$1D0DD0 #1D01D0 <kaiko::GameLinkLobby::is_valid>
typedef bool(__fastcall* F_IsValidGameLinkLobbyKaiko)(void* This); //2nd arg is edx, needed for __thiscall functions.
extern F_IsValidGameLinkLobbyKaiko IsValidGameLinkLobbyKaiko;

//.text:0078C750 rfg.exe:$3CC750 #3CBB50 <gamemusic_multiplayer_start>
typedef void(__cdecl* F_GameMusicMultiplayerStart)(void);
extern F_GameMusicMultiplayerStart GameMusicMultiplayerStart;

//.text:00857740 rfg.exe:$497740 #496B40 <init_multiplayer_data_item_respawn>
typedef void(__cdecl* F_InitMultiplayerDataItemRespawn)(void* Item);
extern F_InitMultiplayerDataItemRespawn InitMultiplayerDataItemRespawn;

//.text:008B50B0 rfg.exe:$4F50B0 #4F44B0 <hud_ui_multiplayer_process>
typedef void(__cdecl* F_HudUiMultiplayerProcess)(float DeltaTime);
extern F_HudUiMultiplayerProcess HudUiMultiplayerProcess;

//.text:008D6D80 rfg.exe:$516D80 #516180 <hud_ui_multiplayer_enter>
typedef void(__cdecl* F_HudUiMultiplayerEnter)(void);
extern F_HudUiMultiplayerEnter HudUiMultiplayerEnter;

/*End of MP Detection Hooks*/


//bool __cdecl keen::graphics::resizeRenderSwapChain(keen::RenderSwapChain *pSwapChain, unsigned int newWidth, unsigned int newHeight)
//Can map out keen::RenderSwapChain later if data is needed from it, currently just hooking this as a signal init the D3D11 pointers again.
//.text:00C2AB20 rfg.exe:$86AB20 #869F20 <keen::graphics::resizeRenderSwapChain>
typedef bool(__cdecl* F_KeenGraphicsResizeRenderSwapchain)(void* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight);
extern F_KeenGraphicsResizeRenderSwapchain KeenGraphicsResizeRenderSwapchain;

//.text:0122FCF0 rfg.exe:$3BFCF0 #3BF0F0 <gameseq_get_state>
typedef GameState(__cdecl* F_GameseqGetState)(void);
extern F_GameseqGetState GameseqGetState;

//.text:01270C50 rfg.exe:$310C50 #310050 <object::enable_object_outline>
typedef void(__thiscall *F_ObjectEnableOutline)(Object* This, int Layer);
extern F_ObjectEnableOutline ObjectEnableOutline;

//.text:01270C60 rfg.exe:$310C60 #310060 <object::disable_object_outline>
typedef void(__thiscall* F_ObjectDisableOutline)(Object* This);
extern F_ObjectDisableOutline ObjectDisableOutline;

//.text:0158EE80 rfg.exe:$62EE80 #62E280 <human::enable_object_outline>
typedef void(__thiscall* F_HumanEnableOutline)(Human* This, int Layer);
extern F_HumanEnableOutline HumanEnableOutline;

//.text:0158EF00 rfg.exe:$62EF00 #62E300 <human::disable_object_outline>
typedef void(__thiscall* F_HumanDisableOutline)(Human* This);
extern F_HumanDisableOutline HumanDisableOutline;

//.text:01695390 rfg.exe:$735390 #734790 <target_outline_add_object>
typedef void(__cdecl* F_TargetOutlineAddObject)(unsigned int Handle);
extern F_TargetOutlineAddObject TargetOutlineAddObject;


//.text:00679AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person>
//.text:00679B60 rfg.exe:$2C9B60 #2C8F60 <camera_stop_first_person>

//.text:00694E30 rfg.exe:$2E4E30 #2E4230 <xray_effect_start>
//.text:00694E50 rfg.exe:$2E4E50 #2E4250 <xray_effect_stop>

//.text:00E18AC0 rfg.exe:$168AC0 #167EC0 <key_down>
//.text:01072F10 rfg.exe:$3C2F10 #3C2310 <game_render_set_bloom_exposure_factor>

//.text:0107F210 rfg.exe:$3CF210 #3CE610 <__Game_render_stats::__Game_render_stats>
//.text:01072BB0 rfg.exe:$3C2BB0 #3C1FB0 <game_render_set_hdr_state>

//.text:01232500 rfg.exe:$3C2500 #3C1900 <game_render_2d_text>
//.text:01311C00 rfg.exe:$4A1C00 #4A1000 <ui_add_debug_text>

//.text:00F28B40 rfg.exe:$B8B40 #B7F40 <rl_camera::get_depth_of_field_enabled>
//.text:01231820 rfg.exe:$3C1820 #3C0C20 <rl_camera::set_depth_of_field_enabled>

//.text:00FA53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

//.text:00EEF7F0 rfg.exe:$43F7F0 #43EBF0 <fog_of_war_clear>






///POSSIBLE DUPLICATES BELOW

//.text:0075BA80 rfg.exe:$55BA80 #55AE80 <debug_spew_projectile> //Did nothing
//.text:00755EB0 rfg.exe:$555EB0 #5552B0 <debug_spew_game_io>
//.text:01267B60 rfg.exe:$B7B60 #B6F60 <rl_render_lib::get_metrics>

//.text:00684760 rfg.exe:$484760 #483B60 <interface_debug_mode_activate> //Did nothing
//.text:009F48D0 rfg.exe:$7F48D0 #7F3CD0 <keen::debug::writeToLogFile>
//.text:00641A90 rfg.exe:$441A90 #440E90 <hud_hide>
//.text:00641AC0 rfg.exe:$441AC0 #440EC0 <hud_is_hidden>
//.text:00642D80 rfg.exe:$442D80 #442180 <hud_display_distance>
//.text:003CD150 rfg.exe:$1CD150 #1CC550 <console_init>
//.text:0038CDB0 rfg.exe:$18CDB0 #18C1B0 <console_enable_chat_window>
//.text:0038CAC0 rfg.exe:$18CAC0 #18BEC0 <console_activate>
//.text:003AF950 rfg.exe:$1AF950 #1AED50 <console_deactivate>
//.text:003AF470 rfg.exe:$1AF470 #1AE870 <console_printf>
//.text:003C4B50 rfg.exe:$1C4B50 #1C3F50 <console_display_help>
//.text:003C54B0 rfg.exe:$1C54B0 #1C48B0 <console_command_enable>
//.text:003C5000 rfg.exe:$1C5000 #1C4400 <console_do_command>

//.text:004CCB90 rfg.exe:$2CCB90 #2CBF90 <camera_start_satellite_mode> //Caused crash
//.text:00469C80 rfg.exe:$2C9C80 #2C9080 <camera_first_person_pre_process>
//.text:004C9AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person> //Set at masons feet, perhaps could work with some edits
//.text:004CF0C0 rfg.exe:$2CF0C0 #2CE4C0 <camera_start_third_person> //Works
//.text:004D3FE0 rfg.exe:$2D3FE0 #2D33E0 <camera_start_lookaround_mode> //Third person viewed in, not very useful
//.text:77121812 kernelbase.dll:$111812 #110C12 //Camera_first_person_offset. Not sure if this is a function or what

//.text:00560A90 rfg.exe:$3C0A90 #3BFE90 <game_print_screen>
//.text:004705D0 rfg.exe:$2D05D0 #2CF9D0 <camera_set_view_player>
//.text:004645B0 rfg.exe:$2C45B0 #2C39B0 <camera_free_system_init>
//.text:00475610 rfg.exe:$2D5610 #2D4A10 <camera_free_mode_init>
//.text:00464DE0 rfg.exe:$2C4DE0 #2C41E0 <camera_free_render_debug>
//.text:0034F4B0 rfg.exe:$1AF4B0 #1AE8B0 <console_chat_printf>
//.text:0056F220 rfg.exe:$3CF220 #3CE620 <unused_dcf_r_show_mem_usage>
//.text:004B4C40 rfg.exe:$314C40 #314040 <rfg_dyn_get_active_destruction_frame>
//.text:004B4C30 rfg.exe:$314C30 #314030 <rfg_dyn_reset_destruction_frame>
//.text:004B3750 rfg.exe:$313750 #312B50 <rfg_dyn_system_shutdown>
//.text:001F8AE0 rfg.exe:$58AE0 #57EE0 <rl_screen_info::get_screen_width>
//.text:0032CAD0 rfg.exe:$18CAD0 #18BED0 <console_is_active>
//.text:01898690 rfg.exe:$6E8690 #6E7A90 <profile_dump_info>

//.text:01034FE0 rfg.exe:$64FE0 #643E0 <vint_render_text>


//.text:01390450 rfg.exe:$3C0450 #3BF850 <rl_scene::set_time_of_day_value>

//.text:006866E0 rfg.exe:$2D66E0 #2D5AE0 <camera_move>

//.text:0068D250 rfg.exe:$2DD250 #2DC650 <camera_third_person_process>

//.text:00679AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person>
//.text:00679B60 rfg.exe:$2C9B60 #2C8F60 <camera_stop_first_person>
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
//.text:00772C70 rfg.exe:$3C2C70 #3C2070 <game_render_set_fog_enabled>

//.text:00694E30 rfg.exe:$2E4E30 #2E4230 <xray_effect_start>
//.text:00694E50 rfg.exe:$2E4E50 #2E4250 <xray_effect_stop>
//.text:00694E70 rfg.exe:$2E4E70 #2E4270 <xray_effect_is_enabled>

//.text:00E18AC0 rfg.exe:$168AC0 #167EC0 <key_down>

//.text:01072F10 rfg.exe:$3C2F10 #3C2310 <game_render_set_bloom_exposure_factor>

//.text:01232500 rfg.exe:$3C2500 #3C1900 <game_render_2d_text>
//.text:01311C00 rfg.exe:$4A1C00 #4A1000 <ui_add_debug_text>

//.text:00F28B40 rfg.exe:$B8B40 #B7F40 <rl_camera::get_depth_of_field_enabled>
//.text:01231820 rfg.exe:$3C1820 #3C0C20 <rl_camera::set_depth_of_field_enabled>

//.text:00FA53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

//.text:00EEF7F0 rfg.exe:$43F7F0 #43EBF0 <fog_of_war_clear>

//.text:005B09C0 rfg.exe:$2D09C0 #2CFDC0 <camera_stop_slew_mode>
//.text:005A9AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person>