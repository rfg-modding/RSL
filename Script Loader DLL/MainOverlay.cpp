#include "MainOverlay.h"
#include "ScriptManager.h"

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
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoCollapse;
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

	if (*ShowAppMetrics) { ImGui::ShowMetricsWindow(ShowAppMetrics); }
	if (*ShowAppAbout) { ShowAboutWindow(ShowAppAbout); }

	// Menu
	if (ImGui::BeginMenuBar())
	{
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
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
	ImGui::PushFont(FontLarge);
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
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_EXCLAMATION_CIRCLE) + u8"##ExclamationCircleIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_EXCLAMATION_TRIANGLE) + u8"##ExclamationTriangleIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_VIAL) + u8"##ExclamationTriangleIcon").c_str()))
	{

	}
	ImGui::PopFont();
	ImGui::PopStyleColor();
	//ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();

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

	ImGui::End();
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