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
	//std::cout << "ModuleBase, hex: " << std::hex << std::uppercase << ModuleBase << std::dec << ", decimal: " << ModuleBase << std::endl;
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
}
