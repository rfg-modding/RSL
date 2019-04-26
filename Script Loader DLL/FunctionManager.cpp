#include "FunctionManager.h"

void FunctionManager::Initialize()
{
	Camera_Start_Slew_Mode = reinterpret_cast<F_Camera_Start_Slew_Mode>(Globals::ModuleBase + 0x2D09B0); //483B60
	Camera_Stop_Slew_Mode = reinterpret_cast<F_Camera_Stop_Slew_Mode>(Globals::ModuleBase + 0x2D09C0);
	Camera_Start_Third_Person = reinterpret_cast<F_Camera_Start_Third_Person>(Globals::ModuleBase + 0x2CF0C0);
	camera_start_first_person = reinterpret_cast<F_camera_start_first_person>(Globals::ModuleBase + 0x2C9AC0);
	camera_stop_first_person = reinterpret_cast<F_camera_stop_first_person>(Globals::ModuleBase + 0x2C9B60);

	Hud_Hide = reinterpret_cast<F_Hud_Hide>(Globals::ModuleBase + 0x441A90);

	game_render_set_fog_enabled = reinterpret_cast<F_game_render_set_fog_enabled>(Globals::ModuleBase + 0x3C2C70);

	ExplosionCreate = reinterpret_cast<F_explosion_create>(Globals::ModuleBase + 0x2EC720); //.text:0035C720 rfg.exe:$2EC720 #2EBB20 <explosion_create>
	GraphicsBeginFrame = reinterpret_cast<F_keen_graphics_beginframe>(Globals::ModuleBase + 0x86DD00); //.text:0129DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame>

	fog_of_war_clear = reinterpret_cast<F_fog_of_war_clear>(Globals::ModuleBase + 0x43F7F0); //.text:00E6F7F0 rfg.exe:$43F7F0 #43EBF0 <fog_of_war_clear>
	MouseGenericAutoCentering = reinterpret_cast<F_MouseGenericAutoCentering>(Globals::ModuleBase + 0x1692B0); //.text:00B992B0 rfg.exe:$1692B0 #1686B0 <mouse_generic_auto_centering>
	CameraViewDataSetView = reinterpret_cast<F_CameraViewDataSetView>(Globals::ModuleBase + 0x2D0290); //.text:00D00290 rfg.exe:$2D0290 #2CF690 <camera_view_data::set_view>
	PlayerDoFrame = reinterpret_cast<F_PlayerDoFrame>(Globals::ModuleBase + 0x6D5A80); //.text:00A65A80 rfg.exe:$6D5A80 #6D4E80 <player::do_frame>
	PlayerConstructor = reinterpret_cast<F_PlayerConstructor>(Globals::ModuleBase + 0x6DECA0); //.text:00A6ECA0 rfg.exe:$6DECA0 #6DE0A0 <player::player>
	CharacterControllerSetPos = reinterpret_cast<F_CharacterControllerSetPos>(Globals::ModuleBase + 0x4153D0); //.text:007A53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

	ObjectUpdatePosAndOrient = reinterpret_cast<F_ObjectUpdatePosAndOrient>(Globals::ModuleBase + 0x68C310);

	HavokBodyGetPositionAndOrient = reinterpret_cast<F_HavokBodyGetPositionAndOrient>(Globals::ModuleBase + 0x429530);
	HavokBodySetPosition = reinterpret_cast<F_HavokBodySetPosition>(Globals::ModuleBase + 0x416EA0);

	//.text:007D6E10 rfg.exe:$416E10 #416210 <havok_body_set_pos_orient> //*** Alternative Address: 423700
	HavokBodySetPositionAndOrient = reinterpret_cast<F_HavokBodySetPositionAndOrient>(Globals::ModuleBase + 0x423700);

	HumanUpdatePosAndOrient = reinterpret_cast<F_HumanUpdatePosAndOrient>(Globals::ModuleBase + 0x69AF70);
	HumanTeleportUnsafe = reinterpret_cast<F_HumanTeleportUnsafe>(Globals::ModuleBase + 0x67C660);
	//HumanTeleport = (F_HumanTeleport)(ModuleBase + 0x69A7A0);

	/*Start of MP Detection Hooks*/
	IsValidGameLinkLobbyKaiko = reinterpret_cast<F_IsValidGameLinkLobbyKaiko>(Globals::ModuleBase + 0x1D0DD0);
	GameMusicMultiplayerStart = reinterpret_cast<F_GameMusicMultiplayerStart>(Globals::ModuleBase + 0x3CC750);
	InitMultiplayerDataItemRespawn = reinterpret_cast<F_InitMultiplayerDataItemRespawn>(Globals::ModuleBase + 0x497740);
	HudUiMultiplayerProcess = reinterpret_cast<F_HudUiMultiplayerProcess>(Globals::ModuleBase + 0x4F50B0);
	HudUiMultiplayerEnter = reinterpret_cast<F_HudUiMultiplayerEnter>(Globals::ModuleBase + 0x516D80);
	/*End of MP Detection Hooks*/

	KeenGraphicsResizeRenderSwapchain = reinterpret_cast<F_KeenGraphicsResizeRenderSwapchain>(Globals::ModuleBase + 0x86AB20); //.text:00C2AB20 rfg.exe:$86AB20 #869F20 <keen::graphics::resizeRenderSwapChain>
	
	//typedef GameState(__cdecl* F_GameseqGetState)(void);
	GameseqGetState = reinterpret_cast<F_GameseqGetState>(Globals::ModuleBase + 0x3BFCF0); //.text:0122FCF0 rfg.exe:$3BFCF0 #3BF0F0 <gameseq_get_state>

	ObjectEnableOutline = reinterpret_cast<F_ObjectEnableOutline>(Globals::ModuleBase + 0x310C50); //.text:01270C50 rfg.exe:$310C50 #310050 <object::enable_object_outline>
	ObjectDisableOutline = reinterpret_cast<F_ObjectDisableOutline>(Globals::ModuleBase + 0x310C60); //.text:01270C60 rfg.exe:$310C60 #310060 <object::disable_object_outline>
	HumanEnableOutline = reinterpret_cast<F_HumanEnableOutline>(Globals::ModuleBase + 0x62EE80); //.text:0158EE80 rfg.exe:$62EE80 #62E280 <human::enable_object_outline>
	HumanDisableOutline = reinterpret_cast<F_HumanDisableOutline>(Globals::ModuleBase + 0x62EF00); //.text:0158EF00 rfg.exe:$62EF00 #62E300 <human::disable_object_outline>

	TargetOutlineAddObject = reinterpret_cast<F_TargetOutlineAddObject>(Globals::ModuleBase + 0x735390);	//.text:01695390 rfg.exe:$735390 #734790 <target_outline_add_object>

	xray_effect_start = reinterpret_cast<F_xray_effect_start>(Globals::ModuleBase + 0x2E4E30); //.text:00694E30 rfg.exe:$2E4E30 #2E4230 <xray_effect_start>
	xray_effect_stop = reinterpret_cast<F_xray_effect_stop>(Globals::ModuleBase + 0x2E4E50); //.text:00694E50 rfg.exe:$2E4E50 #2E4250 <xray_effect_stop>

	UiToolTipsAddTip = reinterpret_cast<F_ui_tool_tips_add_tip>(Globals::ModuleBase + 0x4DA4F0);	//.text:00D0A4F0 rfg.exe:$4DA4F0 #4D98F0 <ui_tool_tips_add_tip>

	console_set_console_mode = reinterpret_cast<F_console_set_console_mode>(Globals::ModuleBase + 0x18CD30); //.text:009BCD30 rfg.exe:$18CD30 #18C130 <console_set_console_mode>
	console_get_console_mode = reinterpret_cast<F_console_get_console_mode>(Globals::ModuleBase + 0x18CD50); //.text:009BCD50 rfg.exe:$18CD50 #18C150 <console_get_console_mode>
	Console_Init = reinterpret_cast<F_Console_Init>(Globals::ModuleBase + 0x1CD150); //.text:003CD150 rfg.exe:$1CD150 #1CC550 <console_init>
	Console_Activate = reinterpret_cast<F_Console_Activate>(Globals::ModuleBase + 0x18CAC0); //.text:0038CAC0 rfg.exe:$18CAC0 #18BEC0 <console_activate>
	Console_Deactivate = reinterpret_cast<F_Console_Deactivate>(Globals::ModuleBase + 0x1AF950); //.text:003AF950 rfg.exe:$1AF950 #1AED50 <console_deactivate>

	rl_draw_tristrip_2d_begin = reinterpret_cast<F_rl_draw_tristrip_2d_begin>(Globals::ModuleBase + 0x10DDA0);
	rl_draw_string = reinterpret_cast<F_rl_draw_string>(Globals::ModuleBase + 0x155BC0); //.text:00985BC0 rfg.exe:$155BC0 #154FC0 <rl_draw::string>

	IsGamePaused = reinterpret_cast<F_is_game_paused>(Globals::ModuleBase + 0x3C1690); //.text:015C1690 rfg.exe:$3C1690 #3C0A90 <game_is_paused>
	world_do_frame = reinterpret_cast<F_world_do_frame>(Globals::ModuleBase + 0x540AB0); //.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame>
	world_get_object_name = reinterpret_cast<F_world_get_object_name>(Globals::ModuleBase + 0x51C8A0); //.text:0171C8A0 rfg.exe:$51C8A0 #51BCA0 <world::get_object_name>


	
	world_get_object_zone_by_index = reinterpret_cast<F_world_get_object_zone_by_index>(Globals::ModuleBase + 0x1D9F0); //.text:0171D9F0 rfg.exe:$51D9F0 #51CDF0 <world::get_object_zone_by_index>
	world_get_object_zone_by_grid_id = reinterpret_cast<F_world_get_object_zone_by_grid_id>(Globals::ModuleBase + 0x51DA20); //.text:0171DA20 rfg.exe:$51DA20 #51CE20 <world::get_object_zone_by_grid_id>

	gsm_get_alert_level = reinterpret_cast<F_gsm_get_alert_level>(Globals::ModuleBase + 0x35D610); //.text:010DD610 rfg.exe:$35D610 #35CA10 <gsm_get_alert_level>
	gsm_set_alert_level = reinterpret_cast<F_gsm_set_alert_level>(Globals::ModuleBase + 0x3AA740); //.text:0112A740 rfg.exe:$3AA740 #3A9B40 <gsm_set_alert_level>
	gsm_get_alert_value = reinterpret_cast<F_gsm_get_alert_value>(Globals::ModuleBase + 0x35D630); //.text:010DD630 rfg.exe:$35D630 #35CA30 <gsm_get_alert_value>
	gsm_set_alert_value = reinterpret_cast<F_gsm_set_alert_value>(Globals::ModuleBase + 0x3A44B0); //.text:011244B0 rfg.exe:$3A44B0 #3A38B0 <gsm_set_alert_value>
	gsm_get_alert_level_cap = reinterpret_cast<F_gsm_get_alert_level_cap>(Globals::ModuleBase + 0x35D680); //.text:010DD680 rfg.exe:$35D680 #35CA80 <gsm_get_alert_level_cap>
	gsm_set_alert_level_cap = reinterpret_cast<F_gsm_set_alert_level_cap>(Globals::ModuleBase + 0x3AA770); //.text:0112A770 rfg.exe:$3AA770 #3A9B70 <gsm_set_alert_level_cap>

	game_render_get_TOD_light = reinterpret_cast<F_game_render_get_TOD_light>(Globals::ModuleBase + 0x3C2960); //.text:01142960 rfg.exe:$3C2960 #3C1D60 <game_render_get_TOD_light>
	game_render_set_TOD_light = reinterpret_cast<F_game_render_set_TOD_light>(Globals::ModuleBase + 0x3C2930); //.text:01142930 rfg.exe:$3C2930 #3C1D30 <game_render_set_TOD_light>

	game_render_get_tod_on_off_value = reinterpret_cast<F_game_render_get_tod_on_off_value>(Globals::ModuleBase + 0x3C3000); //.text:01143000 rfg.exe:$3C3000 #3C2400 <game_render_get_tod_on_off_value>
	game_render_set_tod_on_off_value = reinterpret_cast<F_game_render_set_tod_on_off_value>(Globals::ModuleBase + 0x3C2FF0); //.text:01142FF0 rfg.exe:$3C2FF0 #3C23F0 <game_render_set_tod_on_off_value>

	game_render_set_TOD_light_color = reinterpret_cast<F_game_render_set_TOD_light_color>(Globals::ModuleBase + 0x3C2990); //.text:01142990 rfg.exe:$3C2990 #3C1D90 <game_render_set_TOD_light_color>
	game_clock_get_tod_partitioned = reinterpret_cast<F_game_clock_get_tod_partitioned>(Globals::ModuleBase + 0x3C15C0); //.text:011415C0 rfg.exe:$3C15C0 #3C09C0 <game_clock_get_tod_partitioned>

	game_clock_get_time_of_day = reinterpret_cast<F_game_clock_get_time_of_day>(Globals::ModuleBase + 0x3C15E0); //.text:011415E0 rfg.exe:$3C15E0 #3C09E0 <game_clock_get_time_of_day>
	game_clock_set_time = reinterpret_cast<F_game_clock_set_time>(Globals::ModuleBase + 0x3C1770); //.text:01141770 rfg.exe:$3C1770 #3C0B70 <game_clock_set_time>

	game_time_of_day_get_skybox_tod_colors = reinterpret_cast<F_game_time_of_day_get_skybox_tod_colors>(Globals::ModuleBase + 0x3DFA10); //.text:0115FA10 rfg.exe:$3DFA10 #3DEE10 <game_time_of_day_get_skybox_tod_colors>
	game_time_of_day_get_weather_settings = reinterpret_cast<F_game_time_of_day_get_weather_settings>(Globals::ModuleBase + 0x3C5880); //.text:01145880 rfg.exe:$3C5880 #3C4C80 <game_time_of_day_get_weather_settings>
	game_time_of_day_get_cloud_scroll_values = reinterpret_cast<F_game_time_of_day_get_cloud_scroll_values>(Globals::ModuleBase + 0x3C58C0); //.text:011458C0 rfg.exe:$3C58C0 #3C4CC0 <game_time_of_day_get_cloud_scroll_values>
	game_time_of_day_get_num_orbitals = reinterpret_cast<F_game_time_of_day_get_num_orbitals>(Globals::ModuleBase + 0x3D20C0); //.text:011520C0 rfg.exe:$3D20C0 #3D14C0 <game_time_of_day_get_num_orbitals>
	game_time_of_day_get_cloud_lighting = reinterpret_cast<F_game_time_of_day_get_cloud_lighting>(Globals::ModuleBase + 0x3E31B0); //.text:011631B0 rfg.exe:$3E31B0 #3E25B0 <game_time_of_day_get_cloud_lighting>
	game_time_of_day_get_orbital_params = reinterpret_cast<F_game_time_of_day_get_orbital_params>(Globals::ModuleBase + 0x3E5400); //.text:01165400 rfg.exe:$3E5400 #3E4800 <game_time_of_day_get_orbital_params>

	district_from_name = reinterpret_cast<F_district_from_name>(Globals::ModuleBase + 0x46C4D0); //.text:011EC4D0 rfg.exe:$46C4D0 #46B8D0 <district_from_name>

	
	get_world_zone_by_index = reinterpret_cast<F_get_world_zone_by_index>(Globals::ModuleBase + 0x51D950); //.text:0129D950 rfg.exe:$51D950 #51CD50 <world::get_world_zone_by_index>
	get_world_zone_by_grid_id = reinterpret_cast<F_get_world_zone_by_grid_id>(Globals::ModuleBase + 0x51D970); //.text:0129D970 rfg.exe:$51D970 #51CD70 <world::get_world_zone_by_grid_id>
	get_world_zone_by_name = reinterpret_cast<F_get_world_zone_by_name>(Globals::ModuleBase + 0x51D9A0); //.text:0129D9A0 rfg.exe:$51D9A0 #51CDA0 <world::get_world_zone_by_name>
	get_world_zone_by_pos = reinterpret_cast<F_get_world_zone_by_pos>(Globals::ModuleBase + 0x523BA0); //.text:012A3BA0 rfg.exe:$523BA0 #522FA0 <world::get_world_zone_by_pos>
	get_world_zone_by_object_handle = reinterpret_cast<F_get_world_zone_by_object_handle>(Globals::ModuleBase + 0x523C00); //.text:012A3C00 rfg.exe:$523C00 #523000 <world::get_world_zone_by_object_handle>

	rfg_dyn_apply_point_impulse = reinterpret_cast<F_rfg_dyn_apply_point_impulse>(Globals::ModuleBase + 0x3124D0); //.text:010924D0 rfg.exe:$3124D0 #3118D0 <rfg_dyn_apply_point_impulse>
	rfg_dyn_repair_sphere = reinterpret_cast<F_rfg_dyn_repair_sphere>(Globals::ModuleBase + 0x314820); //.text:01094820 rfg.exe:$314820 #313C20 <rfg_dyn_repair_sphere>

	rl_camera_render_begin = reinterpret_cast<F_rl_camera_render_begin>(Globals::ModuleBase + 0x137660); //.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>

	game_render_set_far_clip_distance = reinterpret_cast<F_game_render_set_far_clip_distance>(Globals::ModuleBase + 0x3C2C40); //.text:012B2C40 rfg.exe:$3C2C40 #3C2040 <game_render_set_far_clip_distance>
	game_render_get_far_clip_distance = reinterpret_cast<F_game_render_get_far_clip_distance>(Globals::ModuleBase + 0x3C2C50); //.text:012B2C50 rfg.exe:$3C2C50 #3C2050 <game_render_get_far_clip_distance>
	game_render_get_main_scene = reinterpret_cast<F_game_render_get_main_scene>(Globals::ModuleBase + 0x3C2920); //.text:012B2920 rfg.exe:$3C2920 #3C1D20 <game_render_get_main_scene>

	hkpWorld_stepDeltaTime = reinterpret_cast<F_hkpWorld_stepDeltaTime>(Globals::ModuleBase + 0x9E1A70); //.text:01B01A70 rfg.exe:$9E1A70 #9E0E70 <hkpWorld::stepDeltaTime>

	ApplicationUpdateTime = reinterpret_cast<F_ApplicationUpdateTime>(Globals::ModuleBase + 0x5A880);

	hkpWorldGetGravity = reinterpret_cast<F_hkpWorldGetGravity>(Globals::ModuleBase + 0x40D040);
	hkpWorldSetGravity = reinterpret_cast<F_hkpWorldSetGravity>(Globals::ModuleBase + 0x9E0E20);

	VintGetLuaState = reinterpret_cast<F_vint_lua_get_state>(Globals::ModuleBase + 0x620F0); //.text:00C720F0 rfg.exe:$620F0 #614F0 <vint_lua_get_state> //lua_State *__cdecl vint_lua_get_state()
	LuaDoBuffer = reinterpret_cast<F_lua_dobuffer>(Globals::ModuleBase + 0x82FD20); //.text:0143FD20 rfg.exe:$82FD20 #82F120 <lua_dobuffer> //int __cdecl lua_dobuffer(lua_State *L, const char *buff, unsigned int size, const char *name)

	HavokBodyGetPointer = reinterpret_cast<F_havok_body_get_pointer>(Globals::ModuleBase + 0x40E870); //.text:0125E870 rfg.exe:$40E870 #40DC70 <havok_body_get_pointer> //hkpRigidBody *__cdecl havok_body_get_pointer(unsigned int handle)
	HavokBodyApplyLinearImpulseA = reinterpret_cast<F_havok_body_apply_linear_impulse_A>(Globals::ModuleBase + 0x4177A0); //.text:012677A0 rfg.exe:$4177A0 #416BA0 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(hkpRigidBody *rb, vector *linear_impulse)
	HavokBodyApplyLinearImpulseB = reinterpret_cast<F_havok_body_apply_linear_impulse_B>(Globals::ModuleBase + 0x423C20); //.text:01273C20 rfg.exe:$423C20 #423020 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(unsigned int handle, vector *linear_impulse)
}
