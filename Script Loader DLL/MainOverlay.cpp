#include "MainOverlay.h"
#include "ScriptManager.h"

void ShowStyleEditor(ImGuiStyle* ref);

static void ShowExampleMenuFile()
{
	ImGui::MenuItem("(dummy menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}
	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		static bool b = true;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::Checkbox("Check", &b);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Colors"))
	{
		float sz = ImGui::GetTextLineHeight();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			ImVec2 p = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			ImGui::Dummy(ImVec2(sz, sz));
			ImGui::SameLine();
			ImGui::MenuItem(name);
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

static void ShowExampleAppConsole(bool* p_open)
{
	static ExampleAppConsole console;
	console.Draw("Example: Console", p_open);
}


static void ShowExampleAppLog(bool* p_open)
{
	static ExampleAppLog log;

	// Demo: add random items (unless Ctrl is held)
	static double last_time = -1.0;
	double time = ImGui::GetTime();
	if (time - last_time >= 0.20f && !ImGui::GetIO().KeyCtrl)
	{
		const char* random_words[] = { "system", "info", "warning", "error", "fatal", "notice", "log" };
		log.AddLog("[%s] Hello, time is %.1f, frame count is %d\n", random_words[rand() % IM_ARRAYSIZE(random_words)], time, ImGui::GetFrameCount());
		last_time = time;
	}

	log.Draw("Example: Log", p_open);
}

bool HumanTeleportSafe(float x, float y, float z, int TimeToHover = 5000)
{
	if (GlobalPlayerPtr)
	{
		Sleep(1000);
		int TimeHovered = 0;
		Player* TempPlayerPtr = (Player*)GlobalPlayerPtr;
		while (TimeHovered < TimeToHover)
		{
			HumanTeleportUnsafe(TempPlayerPtr, vector(x, y, z), TempPlayerPtr->Orientation);
			Sleep(200);
			TimeHovered += 200;
		}
		return true;
	}
	return false;
}

void HumanTeleportSafe(vector NewPosition, int TimeToHover = 5000)
{

}

MainOverlay::MainOverlay()
{

}

MainOverlay::~MainOverlay()
{

}

void MainOverlay::Initialize(bool* _OpenState)
{
	OpenState = _OpenState;

	MainOverlayWindowFlags = 0;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	MainOverlayWindowFlags |= ImGuiWindowFlags_MenuBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoMove;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoResize;
	MainOverlayWindowFlags |= ImGuiWindowFlags_NoCollapse;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoNav;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBackground;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	MainOverlayPopupFlags = 0;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	//MainOverlayPopupFlags |= ImGuiWindowFlags_MenuBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoMove;
	MainOverlayPopupFlags |= ImGuiWindowFlags_NoResize;
	MainOverlayPopupFlags |= ImGuiWindowFlags_NoCollapse;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoNav;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBackground;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	MainOverlayTeleportEditTextFlags = 0;
	MainOverlayTeleportEditTextFlags |= ImGuiInputTextFlags_AllowTabInput;
	MainOverlayTeleportEditTextFlags |= ImGuiInputTextFlags_CharsHexadecimal;

	//LoadGUIConfig();
	//LoadTeleportLocations();
}

void MainOverlay::Draw(const char* Title)
{
	if (!PlayerPtrTargetsInitialized)
	{
		if (PlayerPtr)
		{
			PlayerPositionTargetArray[0] = PlayerPtr->Position.x;
			PlayerPositionTargetArray[1] = PlayerPtr->Position.y;
			PlayerPositionTargetArray[2] = PlayerPtr->Position.z;

			PlayerVelocityTargetArray[0] = PlayerPtr->Velocity.x;
			PlayerVelocityTargetArray[1] = PlayerPtr->Velocity.y;
			PlayerVelocityTargetArray[2] = PlayerPtr->Velocity.z;

			PlayerPtrTargetsInitialized = true;
			Logger::Log("PlayerPtrTargetsInitialized = true", LogWarning);
		}
	}

	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin(Title, OpenState, MainOverlayWindowFlags))
	{
		ImGui::End();
		return;
	}

	if (!PlayerPtr) //Same thing as if(PlayerPtr == nullptr)
	{
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("You must load a save first before this gui is useable.");
		ImGui::End();
		return;
	}

	if (*ShowAppMainMenuBar)       ShowExampleAppMainMenuBar();
	//if (*ShowAppConsole)             ShowExampleAppConsole(ShowAppConsole);
	if (*ShowAppLog)                 ShowExampleAppLog(ShowAppLog);
	if (*ShowAppLongText)           ShowExampleAppLongText(ShowAppLongText);
	if (*ShowAppSimpleOverlay)      ShowExampleAppSimpleOverlay(ShowAppLongText);

	if (*ShowAppMetrics) { ImGui::ShowMetricsWindow(ShowAppMetrics); }
	//if (*ShowAppStyleEditor) { ImGui::Begin("Theme editor", ShowAppStyleEditor); ShowStyleEditor(&ImGui::GetStyle()); ImGui::End(); }
	if (*ShowAppAbout) { ShowAboutWindow(ShowAppAbout); }

	// Menu
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Examples"))
		{
			//ImGui::Text(std::to_string(*ShowAppMainMenuBar).c_str());
			ImGui::MenuItem("Main menu bar", NULL, ShowAppMainMenuBar);
			ImGui::MenuItem("Console", NULL, ShowAppConsole);
			ImGui::MenuItem("Log", NULL, ShowAppLog);
			ImGui::MenuItem("Long text display", NULL, ShowAppLongText);
			ImGui::MenuItem("Simple overlay", NULL, ShowAppSimpleOverlay);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Metrics", NULL, ShowAppMetrics);
			ImGui::MenuItem("Theme Editor", NULL, ShowAppStyleEditor);
			ImGui::MenuItem("About", NULL, ShowAppAbout);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::Separator();
	
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
	if(ImGui::Button(std::string(std::string(ICON_FA_CODE) + u8"##CodeIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if(ImGui::Button(std::string(std::string(ICON_FA_FILE_CODE) + u8"##CodeFileIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if(ImGui::Button(std::string(std::string(ICON_FA_MOUNTAIN) + u8"##AudioFileIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_COG) + u8"##CogIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_COGS) + u8"##CogsIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_SLIDERS_H) + u8"##SlidersIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TASKS) + u8"##TasksIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TOOLS) + u8"##ToolsIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TOOLBOX) + u8"##ToolboxIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_SPIDER) + u8"##SpiderIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TERMINAL) + u8"##TerminalIcon").c_str()))
	{

	}
	ImGui::PopStyleColor(3);

	/*Test of rl_draw::string(). Currently this just freezes the game. Will
	probably end up just using an external lib to render text for now.*/
	/*if (ImGui::Button("Test draw string"))
	{
		rl_primitive_state* PrimitiveState;
		PrimitiveState = new rl_primitive_state;
		PrimitiveState->d.v.m_alpha_mode = 5;
		PrimitiveState->d.v.m_clamp_mode = 0;
		PrimitiveState->d.v.m_color_write_mode = 0;
		PrimitiveState->d.v.m_const_alpha = 0xFF;
		PrimitiveState->d.v.m_cull_mode = 0;
		PrimitiveState->d.v.m_msaa = 0;
		PrimitiveState->d.v.m_scissor = 0;
		PrimitiveState->d.v.m_stencil_mode = 0;
		PrimitiveState->d.v.m_valid = 1;
		PrimitiveState->d.v.m_zbias_mode = 0;
		PrimitiveState->d.v.m_zbuf_mode = 0;

		rl_draw_string(GlobalRlDrawPtr, nullptr, 100.0f, 100.0f, "Test string draw!!!", true, 0, PrimitiveState);
	}*/

	/*This is experimental code meant to manipulate the remnants of the games
	debug console. Currently just tries to activate it. Later on I'll try to
	manually add commands to it and run them. If that works, then I'll add them
	to the lua system and port them through the overlay lua console.*/
	/*ImGui::Text("Console Mode: "); ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string((int)console_get_console_mode).c_str());
	if (ImGui::Button("VCM_NORMAL (0)"))
	{
		console_set_console_mode(VCM_NORMAL);
	}
	if (ImGui::Button("VCM_CHAT (1)"))
	{
		console_set_console_mode(VCM_CHAT);
	}
	if (ImGui::Button("VCM_TEAMCHAT (2)"))
	{
		console_set_console_mode(VCM_TEAMCHAT);
	}

	if (ImGui::Button("Console init"))
	{
		vconsole_config* ConsoleConfig;
		ConsoleConfig = new vconsole_config; //Todo: Fix this if actually using. This is for testing purposes only and will cause a memory leak.
		ConsoleConfig->screen_width = 1680;
		ConsoleConfig->screen_height = 1050;
		ConsoleConfig->save_history = true;
		ConsoleConfig->safe_area_left = 0;
		Console_Init(ConsoleConfig);
	}
	if (ImGui::Button("Console activate"))
	{
		Console_Activate();
	}
	if (ImGui::Button("Console deactivate"))
	{
		Console_Deactivate();
	}*/

	if (ImGui::CollapsingHeader("Notes:"))
	{
		ImGui::Text("Notes");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Please keep in mind that this is a very early version of this tool. Expect there to be bugs and incomplete features. If you encounter a bug that is not in the known bugs section, please let me know. I'd appreciate that. Some issues only pop up for certain people and I can only test on so many computers myself.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The menu above has some example menus that came with the gui library I'm using. They will be customized for the game later on.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- I've not implemented scripts yet so that section is empty.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Globals has a few values you can modify, later on you'll there will be more values and they will be accesible to scripts.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Teleport has both manual and preset teleportation options. Try not to move for at least 5 seconds after teleporting to allow for assets to load in. Sometimes you'll fall through the world with TP. Either wait or repeatedly press the teleport button in this case. Usually if you wait the game will bring you back to the surface after a few seconds.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Player variables is a list of some of the values in memory that define the player. I've only added a 1/4th to 1/3rd of the values so far and I haven't mapped some of them out yet, so it isn't very useful immediately. Once I have all values added to the gui and figure out which ones you can safely change I'll add the option to edit these values as well.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Try hovering your mouse over different gui elements. Many of them, especially in the teleport section, have useful tooltips.");
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Known bugs / issues"))
	{
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Having this tool activated causes opening weapons lockers not to work. Weapon crates still work. This is an odd bug since none of my code affects weapon lockers in a direct way. It's something unexpected which I will work on fixing soon.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The game will crash if you try to switch either to or from plain windowed mode. Using the maximize button visible in windowed mode should not cause crashes. Switching between exclusive fullscreen and fullscreen windowed should not cause any crashes. I suggest using fullscreen windowed if you expect yourself to be alt-tabbing out of the game.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- I recommend using the tool with the debug console disabled. It's an exterior window and can sometimes cause issues with the tool loading. It is off by default, so if you haven't turned it on, don't worry about it. Eventually I'll replace it completely with the in game console in the examples menu. Which is a dummy console that came with this gui library for now.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The \"Global explosion modifiers\" section is completely broken and will make explosions stupidly overpowered rapidly. Use at your own risk. You must restart the game to revert it's effects.");
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Scripts##ScriptsCollapsingHeaderMain"))
	{
		if (ImGui::Button("Rescan"))
		{
			Scripts->ScanScriptsFolder();
		}
		for (auto i = Scripts->Scripts.begin(); i != Scripts->Scripts.end(); ++i)
		{
			ImGui::Text(i->Name.c_str()); ImGui::SameLine();
			
			
			//ImGui::PushID(0);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
			if (ImGui::Button(std::string(std::string(ICON_FA_PLAY) + u8"##" + i->FullPath).c_str()))
			{
				size_t ScriptIndex = std::distance(Scripts->Scripts.begin(), i);
				bool Result = Scripts->RunScript(ScriptIndex);
				Logger::Log("Result from running " + Scripts->Scripts[ScriptIndex].Name + ": " + std::to_string(Result), LogInfo);
			}
			ImGui::PopStyleColor(1);
			ImGui::SameLine();
			if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8"##" + i->FullPath).c_str()))
			{

			}
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
			ImGui::SameLine();
			if (ImGui::Button(std::string(std::string(ICON_FA_BAN) + u8"##" + i->FullPath).c_str()))
			{

			}
			ImGui::PopStyleColor(4);
			ImGui::PopStyleVar();
			//ImGui::PopID();
			
		}
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Globals"))
	{
		if (ImGui::Button("Test Tooltips 1"))
		{
			UiToolTipsAddTip("Salvage", 200, 0);
		}

		ImGui::Text("Xray Effect Mode: ");
		ImGui::SameLine(); ImGui::RadioButton("Backpack", &XrayEffectMode, 0);
		ImGui::SameLine(); ImGui::RadioButton("Rail Driver", &XrayEffectMode, 1);
		ImGui::Text("Selected mode value: "); ImGui::SameLine();
		ImGui::TextColored(SecondaryTextColor, std::to_string(XrayEffectMode).c_str());
		if (ImGui::Button("Toggle Selected Xray Mode"))
		{
			if (XrayEffectMode == 0)
			{
				if (XrayModeOn)
				{
					xray_effect_stop(XET_VISION_BACKPACK);
					XrayModeOn = false;
				}
				else
				{
					xray_effect_start(XET_VISION_BACKPACK);
					XrayModeOn = true;
				}
			}
			else if (XrayEffectMode == 1)
			{
				if (XrayModeOn)
				{
					xray_effect_stop(XET_RAIL_DRIVER);
					XrayModeOn = false;
				}
				else
				{
					xray_effect_start(XET_RAIL_DRIVER);
					XrayModeOn = true;
				}
			}
		}

		ImGui::Text("Code driven jump height:"); ImGui::SameLine();
		ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CodeDrivenJumpHeight).c_str());
		ImGui::PushItemWidth(232.0f);
		ImGui::InputFloat("Custom code driven jump height", &CustomJumpHeight, 0.5, 2.0, 3); ImGui::SameLine();
		ImGui::Checkbox("Active", &NeedCustomJumpHeightSet);
		ImGui::Checkbox("Infinite jetpack", &InfiniteJetpack);
		//ImGui::Checkbox("Invulnerability", (bool*)(PlayerPtr->Flags.invulnerable));
		ImGui::Checkbox("Invulnerability", &Invulnerable);
		if (!Invulnerable)
		{
			PlayerPtr->Flags.invulnerable = false;
		}
		ImGui::Text("Player move speed:"); ImGui::SameLine();
		ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MoveSpeed).c_str());
		ImGui::PushItemWidth(232.0f);
		ImGui::InputFloat("Player move speed", &CustomPlayerMoveSpeed, 1.0f, 5.0f, 3);
		ImGui::Text("Player max speed:"); ImGui::SameLine();
		ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MaxSpeed).c_str());
		ImGui::PushItemWidth(232.0f);
		ImGui::InputFloat("Player max speed", &CustomPlayerMaxSpeed, 1.0f, 5.0f, 3);
		ImGui::PushItemWidth(232.0f);
		ImGui::Text("Player velocity:"); ImGui::SameLine();
		ImGui::InputFloat3("##Player velocity: ", (float*)&PlayerPtr->Velocity); ImGui::SameLine();
		//ImGui::InputFloat("Player cash", &PlayerPtr->Cash, 10.0f, 50.0f, 3);
		//ImGui::InputFloat("Player hit points", &PlayerPtr->HitPoints, 10.0f, 100.0f, 3);
		//ImGui::InputInt("Player max hit points", &PlayerPtr->MaxHitPoints);
		//ImGui::InputInt("Player initial max hit points", &PlayerPtr->InitialMaxHitPoints);
		//ImGui::PushItemWidth(232.0f);
		//ImGui::InputFloat3("Player look at position", (float*)&PlayerPtr->LookAtPos, 3);
		ImGui::InputFloat3("Player aim position", (float*)&PlayerPtr->aim_pos, 3);
		ImGui::InputScalar("Player aim target", ImGuiDataType_U32, &PlayerPtr->aim_target);
		ImGui::InputScalar("Player aim target duration", ImGuiDataType_U32, &PlayerPtr->aim_target_duration);
		ImGui::InputFloat3("Player penetrating aim pos", (float*)&PlayerPtr->penetrating_aim_pos, 3);
		ImGui::InputScalar("Player penetrating aim target", ImGuiDataType_U32, &PlayerPtr->penetrating_aim_target);
		//ImGui::Text("Player frametime multiplier: ");
		//ImGui::SameLine();
		//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->FrametimeMultiplier).c_str());
		//ImGui::InputFloat("Target player frametime multiplier", &PlayerPtr->FrametimeMultiplier);
	}
	ImGui::Separator();

	//ImGui::Text("FPS: ");
	//ImGui::Separator();
	
	if (ImGui::CollapsingHeader("Global explosion modifiers##GlobalExplosionModifiersMain"))
	{
		if (ImGui::Button("Reset to defaults##GlobalExplosionModifiersMain"))
		{
			GlobalExplosionStrengthMultiplier = 1.0f;
			UseGlobalExplosionStrengthMultiplier = false;
			UseExplosionRadiusLimits = true;
			MinimumExplosionRadius = 0.0f;
			MaximumExplosionRadius = 12.0f;
		}
		ImGui::PushItemWidth(232.0f);
		ImGui::SliderFloat("Global explosion strength multiplier", &GlobalExplosionStrengthMultiplier, 0.01f, 10.0f);
		ImGui::SameLine(); ImGui::Checkbox("Use", &UseGlobalExplosionStrengthMultiplier);
		ImGui::Checkbox("Use explosion radius limits", &UseExplosionRadiusLimits);
		Utilities::GUI::TooltipOnPrevious("If you turn this off be very very careful with the explosion multipliers. Too high and it's very easy to freeze/crash the game. My game froze at 4x explosions with no radius limits.");
		ImGui::InputFloat("Minimum explosion radius", &MinimumExplosionRadius, 0.1f, 1.0f, 3);
		ImGui::InputFloat("Maximum explosion radius", &MaximumExplosionRadius, 0.1f, 1.0f, 3);
	}
	else
	{
		ImGui::SameLine(); ImGui::TextColored(ColorRed, " [Experimental]");
	}
	ImGui::Separator();

	//DrawTeleportGui(false, "Teleport", &TeleportWindowOpen, MainOverlayWindowFlags);
	ImGui::Separator();
	
	DrawPlayerVariablesGui(false, "Player variables", &PlayerVariablesGuiOpen, MainOverlayWindowFlags);
	ImGui::Separator();

	ImGui::Text("Misc Program Values:");

	ImGui::End();
}

void MainOverlay::DrawPlayerVariablesGui(bool UseSeparateWindow, const char* Title, bool* Open, ImGuiWindowFlags Flags)
{
	if (UseSeparateWindow)
	{
		if (!ImGui::Begin(Title, Open, Flags))
		{
			ImGui::End();
			return;
		}
	}

	if (ImGui::CollapsingHeader("Player values gui prototype"))
	{
		if (PlayerPtr != nullptr)
		{
			if (ImGui::TreeNode("Object values"))
			{
				//ImGui::Text("Object values");
				//ImGui::Separator();

				//Vftptr

				ImGui::Text("Position vector: "); ImGui::SameLine();
				std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
				ImGui::TextColored(SecondaryTextColor, PlayerPositionString.c_str());

				if (ImGui::TreeNode("Orientation matrix"))
				{
					std::string RightVectorString("(" + std::to_string(PlayerPtr->Orientation.rvec.x) + ", " + std::to_string(PlayerPtr->Orientation.rvec.y) + ", " + std::to_string(PlayerPtr->Orientation.rvec.z) + ")");
					std::string UpVectorString("(" + std::to_string(PlayerPtr->Orientation.uvec.x) + ", " + std::to_string(PlayerPtr->Orientation.uvec.y) + ", " + std::to_string(PlayerPtr->Orientation.uvec.z) + ")");
					std::string DirectionVectorString("(" + std::to_string(PlayerPtr->Orientation.fvec.x) + ", " + std::to_string(PlayerPtr->Orientation.fvec.y) + ", " + std::to_string(PlayerPtr->Orientation.fvec.z) + ")");
					//ImGui::Text("Orientation Matrix:");
					ImGui::Text("Right vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RightVectorString.c_str());
					ImGui::Text("Up vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, UpVectorString.c_str());
					ImGui::Text("Direction vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, DirectionVectorString.c_str());

					ImGui::TreePop();
				}

				//ChildPtr
				//ChildNext
				//ChildPrevious
				//ChildConstraintPtr
				//HostConstraintPtr
				if (ImGui::TreeNode("Attach info"))
				{
					if (PlayerPtr->AttachInfo != nullptr)
					{
						ImGui::Text("Parent handle: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->parent_handle).c_str());
						ImGui::Text("Parent prop point: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->parent_prop_point).c_str());
						ImGui::Text("Child prop point: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->child_prop_point).c_str());
						if (ImGui::CollapsingHeader("Transform matrix"))
						{
							std::string RotationRow1("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.z) + ")");
							std::string RotationRow2("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.z) + ")");
							std::string RotationRow3("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.z) + ")");
							ImGui::Text("Rotation:");
							ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow1.c_str());
							ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow2.c_str());
							ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow3.c_str());
							ImGui::Text("Translation:");
							std::string TranslationString("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.x) + ", "
								+ std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.y) + ", "
								+ std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.z) + ")");
							ImGui::TextColored(SecondaryTextColor, TranslationString.c_str());
						}

						ImGui::Text("Use relative transform: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->use_relative_transform).c_str());
						ImGui::Text("Update physics: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->update_physics).c_str());
						ImGui::Text("Updated: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->updated).c_str());
					}
					else
					{
						ImGui::Text("\tAttach info is a null pointer. Cannot view");
					}
					ImGui::TreePop();
				}

				ImGui::Text("Havok handle: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->HavokHandle).c_str());

				if (ImGui::TreeNode("Contact info"))
				{
					if (PlayerPtr->ContactInfo.m_contact_list != nullptr)
					{
						ImGui::Text("Contact node: ##Player.Object.ContactInfo");
						ImGui::Text("Contacted objects: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ContactInfo.m_contact_list->m_contacted_object).c_str());
						ImGui::Text("Number of contacts: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ContactInfo.m_contact_list->m_num_contacts).c_str());
						//Todo: Iterate through linked list, give the user control over how far to do so. Note that it is a linked list to the user.
						//prev
						//next
					}
					else
					{
						ImGui::Text("\tContact info is a null pointer. Cannot view.");
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Object flags"))
				{
					ImGui::Text("Flagged list state: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.flagged_list_state).c_str());
					ImGui::Text("Lighting set once: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.lighting_set_once).c_str());
					ImGui::Text("Destroyed: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.destroyed).c_str());
					ImGui::Text("No save: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.no_save).c_str());
					ImGui::Text("Force full save: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.force_full_save).c_str());
					ImGui::Text("Destroy on stream: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.destroy_on_stream).c_str());
					ImGui::Text("Created by mission or activity: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.created_by_mission_or_activity).c_str());
					ImGui::Text("Don't transform: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.dont_transform).c_str());
					ImGui::Text("World free: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.world_free).c_str());
					ImGui::Text("Streaming: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.streaming).c_str());
					ImGui::Text("Streamed: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.streamed).c_str());
					ImGui::Text("Persistent: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.persistent).c_str());
					ImGui::Text("Original: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.original).c_str());
					ImGui::Text("Stub: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.stub).c_str());
					ImGui::Text("Preserve handle: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.preserve_handle).c_str());
					ImGui::Text("BPO index: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.bpo_index).c_str());
					ImGui::Text("Is dependent: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.is_dependent).c_str());
					ImGui::Text("Visited: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.visited).c_str());
					ImGui::Text("Special lifetime: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.special_lifetime).c_str());
					ImGui::Text("Serialize protected: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.serialize_protected).c_str());
					ImGui::Text("Dont use me: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags._dont_use_me).c_str());
					ImGui::Text("Streaming fixed: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.streaming_fixed).c_str());
					ImGui::Text("Render flags: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.render_flags).c_str());
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Remote object flags"))
				{
					ImGui::Text("Remote object: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.remote_object).c_str());
					ImGui::Text("Client sync: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.client_sync).c_str());
					ImGui::Text("Client destroy permission: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.client_destroy_permission).c_str());
					ImGui::Text("No destroy packet: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.no_destroy_packet).c_str());
					ImGui::Text("Common create: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.common_create).c_str());
					ImGui::TreePop();
				}

				ImGui::Text("MP dcmo index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MPDcmoIndex).c_str());
				ImGui::Text("Checking reset: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CheckingReset).c_str());
				ImGui::Text("Name index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->NameIndex).c_str());

				//Todo: Eventually haved linked list traversal, or object menu. Try adding names to menu as well if possible.
				//FlaggedNext
				//FlaggedPrevious

				ImGui::Text("Handle: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Handle).c_str());
				ImGui::Text("Parent: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Parent).c_str());

				if (ImGui::TreeNode("Havok BPO"))
				{
					if (PlayerPtr->BPOHandle != nullptr)
					{
						ImGui::Text("Flags: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->flags).c_str());
						ImGui::Text("State: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->state).c_str());
						ImGui::Text("BPO Index: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->bpo_index).c_str());
						ImGui::Text("State Index: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->state_index).c_str());
						ImGui::Text("Owner: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->owner).c_str());
						ImGui::Text("Next: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->next).c_str());
						ImGui::Text("Previous: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->prev).c_str());
						//user_data
					}
					else
					{
						ImGui::Text("\tHavok BPO is a null pointer. Cannot view");
					}
					ImGui::TreePop();
				}

				ImGui::Text("All index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AllIndex).c_str());
				ImGui::Text("Type index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->TypeIndex).c_str());
				ImGui::Text("Subtype index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SubtypeIndex).c_str());
				ImGui::Text("Object type: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectType).c_str());
				ImGui::Text("Subtype: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SubType).c_str());

				ImGui::Text("Last known bmin: "); ImGui::SameLine();
				std::string LastKnownBminString("(" + std::to_string(PlayerPtr->LastKnownBMin.x) + ", " + std::to_string(PlayerPtr->LastKnownBMin.y) + ", " + std::to_string(PlayerPtr->LastKnownBMin.z) + ")");
				ImGui::TextColored(SecondaryTextColor, LastKnownBminString.c_str());

				ImGui::Text("Last known bmax: "); ImGui::SameLine();
				std::string LastKnownBmaxString("(" + std::to_string(PlayerPtr->LastKnownBMax.x) + ", " + std::to_string(PlayerPtr->LastKnownBMax.y) + ", " + std::to_string(PlayerPtr->LastKnownBMax.z) + ")");
				ImGui::TextColored(SecondaryTextColor, LastKnownBmaxString.c_str());

				ImGui::Text("SRID: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SRID).c_str());

				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Human values"))
			{
				//ImGui::Separator();
				//ImGui::Text("Human values");

				/*if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//Info

				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector
				//vector
				//vector

				if (ImGui::CollapsingHeader(""))
				{

				}

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}

				//vector
				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{
					//check nullptr
				}

				//ClothSim

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{
					//Check nullptr
				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				//Previous value is Timestamp TurretHoldAnimations. Still several dozen values left.*/
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Player values"))
			{
				//ImGui::Separator();
				//ImGui::Text("Player values");
				ImGui::TreePop();
			}
		}
		else
		{
			ImGui::Text("Player pointer is null. Cannot view");
		}
	}
	else
	{
		ImGui::SameLine(); ImGui::TextColored(ColorRed, " [Experimental]");
	}
}

void MainOverlay::ShowAboutWindow(bool* p_open)
{
	if (!ImGui::Begin("About RFGR Script Loader", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}
	ImGui::Text("RFGR Script Loader %s", GetScriptLoaderVersion());
	ImGui::Separator();
	ImGui::PushItemWidth(100.0f);
	ImGui::TextWrapped("By moneyl. See it's public wiki repo here:");
	ImGui::PushItemWidth(100.0f);
	ImGui::TextWrapped("https://github.com/Moneyl/RFGR-Script-Loader-Wiki");
	ImGui::PushItemWidth(100.0f);
	ImGui::TextWrapped("If you have any bugs or questions either check the github issues section or contact me on the official RFG discord (https://discord.gg/RDsQKU8), @moneyl. I'd appreciate if you made a github issue and described the steps to reproduce any bug you find.");

	ImGui::Separator();
	ImGui::Text("About libraries used:");
	ImGui::Separator();
	ImGui::Separator();
	ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
	ImGui::Separator();
	ImGui::Text("By Omar Cornut and all dear imgui contributors.");
	ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");

	static bool show_config_info = false;
	ImGui::Checkbox("Config/Build Information", &show_config_info);
	if (show_config_info)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		bool copy_to_clipboard = ImGui::Button("Copy to clipboard");
		ImGui::BeginChildFrame(ImGui::GetID("cfginfos"), ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 18), ImGuiWindowFlags_NoMove);
		if (copy_to_clipboard)
			ImGui::LogToClipboard();

		ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
		ImGui::Separator();
		ImGui::Text("sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
		ImGui::Text("define: __cplusplus=%d", (int)__cplusplus);
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_OBSOLETE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_WIN32_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_MATH_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_MATH_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
		ImGui::Text("define: IMGUI_DISABLE_DEFAULT_ALLOCATORS");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
		ImGui::Text("define: IMGUI_USE_BGRA_PACKED_COLOR");
#endif
#ifdef _WIN32
		ImGui::Text("define: _WIN32");
#endif
#ifdef _WIN64
		ImGui::Text("define: _WIN64");
#endif
#ifdef __linux__
		ImGui::Text("define: __linux__");
#endif
#ifdef __APPLE__
		ImGui::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
		ImGui::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef __MINGW32__
		ImGui::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
		ImGui::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
		ImGui::Text("define: __GNUC__=%d", (int)__GNUC__);
#endif
#ifdef __clang_version__
		ImGui::Text("define: __clang_version__=%s", __clang_version__);
#endif
		ImGui::Separator();
		ImGui::Text("io.BackendPlatformName: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
		ImGui::Text("io.BackendRendererName: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
		ImGui::Text("io.ConfigFlags: 0x%08X", io.ConfigFlags);
		if (io.ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard)        ImGui::Text(" NavEnableKeyboard");
		if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)         ImGui::Text(" NavEnableGamepad");
		if (io.ConfigFlags & ImGuiConfigFlags_NavEnableSetMousePos)     ImGui::Text(" NavEnableSetMousePos");
		if (io.ConfigFlags & ImGuiConfigFlags_NavNoCaptureKeyboard)     ImGui::Text(" NavNoCaptureKeyboard");
		if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)                  ImGui::Text(" NoMouse");
		if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)      ImGui::Text(" NoMouseCursorChange");
		if (io.MouseDrawCursor)                                         ImGui::Text("io.MouseDrawCursor");
		if (io.ConfigMacOSXBehaviors)                                   ImGui::Text("io.ConfigMacOSXBehaviors");
		if (io.ConfigInputTextCursorBlink)                              ImGui::Text("io.ConfigInputTextCursorBlink");
		if (io.ConfigWindowsResizeFromEdges)                            ImGui::Text("io.ConfigWindowsResizeFromEdges");
		if (io.ConfigWindowsMoveFromTitleBarOnly)                       ImGui::Text("io.ConfigWindowsMoveFromTitleBarOnly");
		ImGui::Text("io.BackendFlags: 0x%08X", io.BackendFlags);
		if (io.BackendFlags & ImGuiBackendFlags_HasGamepad)             ImGui::Text(" HasGamepad");
		if (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        ImGui::Text(" HasMouseCursors");
		if (io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         ImGui::Text(" HasSetMousePos");
		ImGui::Separator();
		ImGui::Text("io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexWidth, io.Fonts->TexHeight);
		ImGui::Text("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
		ImGui::Separator();
		ImGui::Text("style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y);
		ImGui::Text("style.WindowBorderSize: %.2f", style.WindowBorderSize);
		ImGui::Text("style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y);
		ImGui::Text("style.FrameRounding: %.2f", style.FrameRounding);
		ImGui::Text("style.FrameBorderSize: %.2f", style.FrameBorderSize);
		ImGui::Text("style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y);
		ImGui::Text("style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

		if (copy_to_clipboard)
			ImGui::LogFinish();
		ImGui::EndChildFrame();
	}
	ImGui::End();
}

/*bool MainOverlay::ShowStyleSelector(const char* label)
{
	static int style_idx = -1;
	if (ImGui::Combo(label, &style_idx, "Classic\0Dark\0Light\0"))
	{
		switch (style_idx)
		{
		case 0: ImGui::StyleColorsClassic(); break;
		case 1: ImGui::StyleColorsDark(); break;
		case 2: ImGui::StyleColorsLight(); break;
		}
		return true;
	}
	return false;
}

void MainOverlay::ShowFontSelector(const char* label)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font_current = ImGui::GetFont();
	if (ImGui::BeginCombo(label, font_current->GetDebugName()))
	{
		for (int n = 0; n < io.Fonts->Fonts.Size; n++)
			if (ImGui::Selectable(io.Fonts->Fonts[n]->GetDebugName(), io.Fonts->Fonts[n] == font_current))
				io.FontDefault = io.Fonts->Fonts[n];
		ImGui::EndCombo();
	}
	ImGui::SameLine();
	ShowHelpMarker(
		"- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
		"- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
		"- Read FAQ and documentation in misc/fonts/ for more details.\n"
		"- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}*/

void MainOverlay::ShowExampleAppMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void MainOverlay::ShowExampleAppPropertyEditor(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Example: Property editor", p_open))
	{
		ImGui::End();
		return;
	}

	ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::Columns(2);
	ImGui::Separator();

	struct funcs
	{
		static void ShowDummyObject(const char* prefix, int uid)
		{
			ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
			ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
			bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
			ImGui::NextColumn();
			ImGui::AlignTextToFramePadding();
			ImGui::Text("my sailor is rich");
			ImGui::NextColumn();
			if (node_open)
			{
				static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
				for (int i = 0; i < 8; i++)
				{
					ImGui::PushID(i); // Use field index as identifier.
					if (i < 2)
					{
						ShowDummyObject("Child", 424242);
					}
					else
					{
						// Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
						ImGui::AlignTextToFramePadding();
						ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
						ImGui::NextColumn();
						ImGui::PushItemWidth(-1);
						if (i >= 5)
							ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
						else
							ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
						ImGui::PopItemWidth();
						ImGui::NextColumn();
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}
			ImGui::PopID();
		}
	};

	// Iterate dummy objects with dummy members (all the same data)
	for (int obj_i = 0; obj_i < 3; obj_i++)
		funcs::ShowDummyObject("Object", obj_i);

	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::PopStyleVar();
	ImGui::End();
}

void MainOverlay::ShowExampleAppLongText(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Example: Long text display", p_open))
	{
		ImGui::End();
		return;
	}

	static int test_type = 0;
	static ImGuiTextBuffer log;
	static int lines = 0;
	ImGui::Text("Printing unusually long amount of text.");
	ImGui::Combo("Test type", &test_type, "Single call to TextUnformatted()\0Multiple calls to Text(), clipped manually\0Multiple calls to Text(), not clipped (slow)\0");
	ImGui::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
	if (ImGui::Button("Clear")) { log.clear(); lines = 0; }
	ImGui::SameLine();
	if (ImGui::Button("Add 1000 lines"))
	{
		for (int i = 0; i < 1000; i++)
			log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines + i);
		lines += 1000;
	}
	ImGui::BeginChild("Log");
	switch (test_type)
	{
	case 0:
		// Single call to TextUnformatted() with a big buffer
		ImGui::TextUnformatted(log.begin(), log.end());
		break;
	case 1:
	{
		// Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		ImGuiListClipper clipper(lines);
		while (clipper.Step())
			for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	case 2:
		// Multiple calls to Text(), not clipped (slow)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		for (int i = 0; i < lines; i++)
			ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	ImGui::EndChild();
	ImGui::End();
}

void MainOverlay::ShowExampleAppSimpleOverlay(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 0;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	if (corner != -1)
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}