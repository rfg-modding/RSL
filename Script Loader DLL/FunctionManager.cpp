#include "FunctionManager.h"

FunctionManager::FunctionManager()
{

}

FunctionManager::~FunctionManager()
{

}

void FunctionManager::Initialize()
{
	ModuleBase = (uintptr_t)GetModuleHandle(NULL);
	//std::cout << "ModuleBase, hex: " << std::hex << std::uppercase << ModuleBase << std::dec << ", decimal: " << ModuleBase << "\n";
	Camera_Start_Slew_Mode = (F_Camera_Start_Slew_Mode)(ModuleBase + 0x2D09B0); //483B60
	Camera_Stop_Slew_Mode = (F_Camera_Stop_Slew_Mode)(ModuleBase + 0x2D09C0);

	Hud_Hide = (F_Hud_Hide)(ModuleBase + 0x441A90);

	game_render_set_fog_enabled = (F_game_render_set_fog_enabled)(ModuleBase + 0x3C2C70);

	ExplosionCreate = (F_explosion_create)(ModuleBase + 0x2EC720); //.text:0035C720 rfg.exe:$2EC720 #2EBB20 <explosion_create>
	GraphicsBeginFrame = (F_keen_graphics_beginframe)(ModuleBase + 0x86DD00); //.text:0129DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame>

	fog_of_war_clear = (F_fog_of_war_clear)(ModuleBase + 0x43F7F0); //.text:00E6F7F0 rfg.exe:$43F7F0 #43EBF0 <fog_of_war_clear>
	MouseGenericAutoCentering = (F_MouseGenericAutoCentering)(ModuleBase + 0x1692B0); //.text:00B992B0 rfg.exe:$1692B0 #1686B0 <mouse_generic_auto_centering>
	CameraViewDataSetView = (F_CameraViewDataSetView)(ModuleBase + 0x2D0290); //.text:00D00290 rfg.exe:$2D0290 #2CF690 <camera_view_data::set_view>
	PlayerDoFrame = (F_PlayerDoFrame)(ModuleBase + 0x6D5A80); //.text:00A65A80 rfg.exe:$6D5A80 #6D4E80 <player::do_frame>
	PlayerConstructor = (F_PlayerConstructor)(ModuleBase + 0x6DECA0); //.text:00A6ECA0 rfg.exe:$6DECA0 #6DE0A0 <player::player>
	CharacterControllerSetPos = (F_CharacterControllerSetPos)(ModuleBase + 0x4153D0); //.text:007A53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

	ObjectUpdatePosAndOrient = (F_ObjectUpdatePosAndOrient)(ModuleBase + 0x68C310);

	HavokBodyGetPositionAndOrient = (F_HavokBodyGetPositionAndOrient)(ModuleBase + 0x429530);
	HavokBodySetPosition = (F_HavokBodySetPosition)(ModuleBase + 0x416EA0);

	//.text:007D6E10 rfg.exe:$416E10 #416210 <havok_body_set_pos_orient> //*** Alternative Address: 423700
	HavokBodySetPositionAndOrient = (F_HavokBodySetPositionAndOrient)(ModuleBase + 0x423700);

	HumanUpdatePosAndOrient = (F_HumanUpdatePosAndOrient)(ModuleBase + 0x69AF70);
	HumanTeleportUnsafe = (F_HumanTeleportUnsafe)(ModuleBase + 0x67C660);
	//HumanTeleport = (F_HumanTeleport)(ModuleBase + 0x69A7A0);

	/*Start of MP Detection Hooks*/
	IsValidGameLinkLobbyKaiko = (F_IsValidGameLinkLobbyKaiko)(ModuleBase + 0x1D0DD0);
	GameMusicMultiplayerStart = (F_GameMusicMultiplayerStart)(ModuleBase + 0x3CC750);
	InitMultiplayerDataItemRespawn = (F_InitMultiplayerDataItemRespawn)(ModuleBase + 0x497740);
	HudUiMultiplayerProcess = (F_HudUiMultiplayerProcess)(ModuleBase + 0x4F50B0);
	HudUiMultiplayerEnter = (F_HudUiMultiplayerEnter)(ModuleBase + 0x516D80);
	/*End of MP Detection Hooks*/

	KeenGraphicsResizeRenderSwapchain = (F_KeenGraphicsResizeRenderSwapchain)(ModuleBase + 0x86AB20); //.text:00C2AB20 rfg.exe:$86AB20 #869F20 <keen::graphics::resizeRenderSwapChain>
	
	//typedef GameState(__cdecl* F_GameseqGetState)(void);
	GameseqGetState = (F_GameseqGetState)(ModuleBase + 0x3BFCF0); //.text:0122FCF0 rfg.exe:$3BFCF0 #3BF0F0 <gameseq_get_state>

	ObjectEnableOutline = (F_ObjectEnableOutline)(ModuleBase + 0x310C50); //.text:01270C50 rfg.exe:$310C50 #310050 <object::enable_object_outline>
	ObjectDisableOutline = (F_ObjectDisableOutline)(ModuleBase + 0x310C60); //.text:01270C60 rfg.exe:$310C60 #310060 <object::disable_object_outline>
	HumanEnableOutline = (F_HumanEnableOutline)(ModuleBase + 0x62EE80); //.text:0158EE80 rfg.exe:$62EE80 #62E280 <human::enable_object_outline>
	HumanDisableOutline = (F_HumanDisableOutline)(ModuleBase + 0x62EF00); //.text:0158EF00 rfg.exe:$62EF00 #62E300 <human::disable_object_outline>

	TargetOutlineAddObject = (F_TargetOutlineAddObject)(ModuleBase + 0x735390);	//.text:01695390 rfg.exe:$735390 #734790 <target_outline_add_object>

	xray_effect_start = (F_xray_effect_start)(ModuleBase + 0x2E4E30); //.text:00694E30 rfg.exe:$2E4E30 #2E4230 <xray_effect_start>
	xray_effect_stop = (F_xray_effect_stop)(ModuleBase + 0x2E4E50); //.text:00694E50 rfg.exe:$2E4E50 #2E4250 <xray_effect_stop>

	UiToolTipsAddTip = (F_ui_tool_tips_add_tip)(ModuleBase + 0x4DA4F0);	//.text:00D0A4F0 rfg.exe:$4DA4F0 #4D98F0 <ui_tool_tips_add_tip>

	console_set_console_mode = (F_console_set_console_mode)(ModuleBase + 0x18CD30); //.text:009BCD30 rfg.exe:$18CD30 #18C130 <console_set_console_mode>
	console_get_console_mode = (F_console_get_console_mode)(ModuleBase + 0x18CD50); //.text:009BCD50 rfg.exe:$18CD50 #18C150 <console_get_console_mode>
	Console_Init = (F_Console_Init)(ModuleBase + 0x1CD150); //.text:003CD150 rfg.exe:$1CD150 #1CC550 <console_init>
	Console_Activate = (F_Console_Activate)(ModuleBase + 0x18CAC0); //.text:0038CAC0 rfg.exe:$18CAC0 #18BEC0 <console_activate>
	Console_Deactivate = (F_Console_Deactivate)(ModuleBase + 0x1AF950); //.text:003AF950 rfg.exe:$1AF950 #1AED50 <console_deactivate>

	rl_draw_tristrip_2d_begin = (F_rl_draw_tristrip_2d_begin)(ModuleBase + 0x10DDA0);
	rl_draw_string = (F_rl_draw_string)(ModuleBase + 0x155BC0); //.text:00985BC0 rfg.exe:$155BC0 #154FC0 <rl_draw::string>

	IsGamePaused = (F_is_game_paused)(ModuleBase + 0x3C1690); //.text:015C1690 rfg.exe:$3C1690 #3C0A90 <game_is_paused>
	world_do_frame = (F_world_do_frame)(ModuleBase + 0x540AB0); //.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame>
	world_get_object_name = (F_world_get_object_name)(ModuleBase + 0x51C8A0); //.text:0171C8A0 rfg.exe:$51C8A0 #51BCA0 <world::get_object_name>


	
	world_get_object_zone_by_index = (F_world_get_object_zone_by_index)(ModuleBase + 0x1D9F0); //.text:0171D9F0 rfg.exe:$51D9F0 #51CDF0 <world::get_object_zone_by_index>
	world_get_object_zone_by_grid_id = (F_world_get_object_zone_by_grid_id)(ModuleBase + 0x51DA20); //.text:0171DA20 rfg.exe:$51DA20 #51CE20 <world::get_object_zone_by_grid_id>

	gsm_get_alert_level = (F_gsm_get_alert_level)(ModuleBase + 0x35D610); //.text:010DD610 rfg.exe:$35D610 #35CA10 <gsm_get_alert_level>
	gsm_set_alert_level = (F_gsm_set_alert_level)(ModuleBase + 0x3AA740); //.text:0112A740 rfg.exe:$3AA740 #3A9B40 <gsm_set_alert_level>
	gsm_get_alert_value = (F_gsm_get_alert_value)(ModuleBase + 0x35D630); //.text:010DD630 rfg.exe:$35D630 #35CA30 <gsm_get_alert_value>
	gsm_set_alert_value = (F_gsm_set_alert_value)(ModuleBase + 0x3A44B0); //.text:011244B0 rfg.exe:$3A44B0 #3A38B0 <gsm_set_alert_value>
	gsm_get_alert_level_cap = (F_gsm_get_alert_level_cap)(ModuleBase + 0x35D680); //.text:010DD680 rfg.exe:$35D680 #35CA80 <gsm_get_alert_level_cap>
	gsm_set_alert_level_cap = (F_gsm_set_alert_level_cap)(ModuleBase + 0x3AA770); //.text:0112A770 rfg.exe:$3AA770 #3A9B70 <gsm_set_alert_level_cap>

	game_render_get_TOD_light = (F_game_render_get_TOD_light)(ModuleBase + 0x3C2960); //.text:01142960 rfg.exe:$3C2960 #3C1D60 <game_render_get_TOD_light>
	game_render_set_TOD_light = (F_game_render_set_TOD_light)(ModuleBase + 0x3C2930); //.text:01142930 rfg.exe:$3C2930 #3C1D30 <game_render_set_TOD_light>

	game_render_get_tod_on_off_value = (F_game_render_get_tod_on_off_value)(ModuleBase + 0x3C3000); //.text:01143000 rfg.exe:$3C3000 #3C2400 <game_render_get_tod_on_off_value>
	game_render_set_tod_on_off_value = (F_game_render_set_tod_on_off_value)(ModuleBase + 0x3C2FF0); //.text:01142FF0 rfg.exe:$3C2FF0 #3C23F0 <game_render_set_tod_on_off_value>

	game_render_set_TOD_light_color = (F_game_render_set_TOD_light_color)(ModuleBase + 0x3C2990); //.text:01142990 rfg.exe:$3C2990 #3C1D90 <game_render_set_TOD_light_color>
	game_clock_get_tod_partitioned = (F_game_clock_get_tod_partitioned)(ModuleBase + 0x3C15C0); //.text:011415C0 rfg.exe:$3C15C0 #3C09C0 <game_clock_get_tod_partitioned>

	game_clock_get_time_of_day = (F_game_clock_get_time_of_day)(ModuleBase + 0x3C15E0); //.text:011415E0 rfg.exe:$3C15E0 #3C09E0 <game_clock_get_time_of_day>
	game_clock_set_time = (F_game_clock_set_time)(ModuleBase + 0x3C1770); //.text:01141770 rfg.exe:$3C1770 #3C0B70 <game_clock_set_time>

	game_time_of_day_get_skybox_tod_colors = (F_game_time_of_day_get_skybox_tod_colors)(ModuleBase + 0x3DFA10); //.text:0115FA10 rfg.exe:$3DFA10 #3DEE10 <game_time_of_day_get_skybox_tod_colors>
	game_time_of_day_get_weather_settings = (F_game_time_of_day_get_weather_settings)(ModuleBase + 0x3C5880); //.text:01145880 rfg.exe:$3C5880 #3C4C80 <game_time_of_day_get_weather_settings>
	game_time_of_day_get_cloud_scroll_values = (F_game_time_of_day_get_cloud_scroll_values)(ModuleBase + 0x3C58C0); //.text:011458C0 rfg.exe:$3C58C0 #3C4CC0 <game_time_of_day_get_cloud_scroll_values>
	game_time_of_day_get_num_orbitals = (F_game_time_of_day_get_num_orbitals)(ModuleBase + 0x3D20C0); //.text:011520C0 rfg.exe:$3D20C0 #3D14C0 <game_time_of_day_get_num_orbitals>
	game_time_of_day_get_cloud_lighting = (F_game_time_of_day_get_cloud_lighting)(ModuleBase + 0x3E31B0); //.text:011631B0 rfg.exe:$3E31B0 #3E25B0 <game_time_of_day_get_cloud_lighting>
	game_time_of_day_get_orbital_params = (F_game_time_of_day_get_orbital_params)(ModuleBase + 0x3E5400); //.text:01165400 rfg.exe:$3E5400 #3E4800 <game_time_of_day_get_orbital_params>

	district_from_name = (F_district_from_name)(ModuleBase + 0x46C4D0); //.text:011EC4D0 rfg.exe:$46C4D0 #46B8D0 <district_from_name>

	
	get_world_zone_by_index = (F_get_world_zone_by_index)(ModuleBase + 0x51D950); //.text:0129D950 rfg.exe:$51D950 #51CD50 <world::get_world_zone_by_index>
	get_world_zone_by_grid_id = (F_get_world_zone_by_grid_id)(ModuleBase + 0x51D970); //.text:0129D970 rfg.exe:$51D970 #51CD70 <world::get_world_zone_by_grid_id>
	get_world_zone_by_name = (F_get_world_zone_by_name)(ModuleBase + 0x51D9A0); //.text:0129D9A0 rfg.exe:$51D9A0 #51CDA0 <world::get_world_zone_by_name>
	get_world_zone_by_pos = (F_get_world_zone_by_pos)(ModuleBase + 0x523BA0); //.text:012A3BA0 rfg.exe:$523BA0 #522FA0 <world::get_world_zone_by_pos>
	get_world_zone_by_object_handle = (F_get_world_zone_by_object_handle)(ModuleBase + 0x523C00); //.text:012A3C00 rfg.exe:$523C00 #523000 <world::get_world_zone_by_object_handle>

	rfg_dyn_apply_point_impulse = (F_rfg_dyn_apply_point_impulse)(ModuleBase + 0x3124D0); //.text:010924D0 rfg.exe:$3124D0 #3118D0 <rfg_dyn_apply_point_impulse>
	rfg_dyn_repair_sphere = (F_rfg_dyn_repair_sphere)(ModuleBase + 0x314820); //.text:01094820 rfg.exe:$314820 #313C20 <rfg_dyn_repair_sphere>
}
