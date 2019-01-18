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
}