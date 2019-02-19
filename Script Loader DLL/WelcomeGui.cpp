#include "WelcomeGui.h"
#include "ScriptManager.h"

WelcomeGui::WelcomeGui()
{

}

WelcomeGui::~WelcomeGui()
{

}

void WelcomeGui::Initialize(bool* _OpenState)
{
	OpenState = _OpenState;

	MainOverlayWindowFlags = 0;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_MenuBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoMove;
	MainOverlayWindowFlags |= ImGuiWindowFlags_NoResize;
	MainOverlayWindowFlags |= ImGuiWindowFlags_NoCollapse;
	MainOverlayWindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoNav;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBackground;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void WelcomeGui::Draw(const char* Title)
{
	if (!*OpenState)
	{
		return;
	}
	if (!ImGui::Begin(Title, OpenState, MainOverlayWindowFlags))
	{
		ImGui::End();
		return;
	}

	if (Gui.ShowAppMetrics) { ImGui::ShowMetricsWindow(&Gui.ShowAppMetrics); }
	if (Gui.ShowAppAbout) { ShowAboutWindow(&Gui.ShowAppAbout); }

	//ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
	ImGui::PushFont(FontHuge);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_CODE) + u8"##CodeIcon").c_str()))
	{
		Gui.ShowAppScriptsMenu = !Gui.ShowAppScriptsMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu displays all the scripts detected in the scripts folder and lets you run, edit, and stop them on command. If the script isn't using event hooks then stopping it does nothing, since it stops after running once.", FontNormal);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.357f, 0.659f, 0.863f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_TERMINAL) + u8"##TerminalIcon").c_str()))
	{
		Gui.ToggleLuaConsole();
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("The console is useful for quickly setting values or calling functions without writing a script. Anything that scripts have access to, the console does too. The console is just running your input into it as a script.", FontNormal);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.808f, 0.267f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8"##EditIcon").c_str()))
	{
		Gui.ShowAppScriptEditor = !Gui.ShowAppScriptEditor;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("The script editor allows you to save, load, edit, and run lua scripts in game, and provides basic lua syntax highlighting.", FontNormal);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.404f, 0.416f, 0.435f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_SLIDERS_H) + u8"##SlidersIcon").c_str()))
	{
		Gui.ShowAppTweaksMenu = !Gui.ShowAppTweaksMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu has settings for invulnerability, infinite jetpack, player move speed, player jump height, xray vision, and more.", FontNormal);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.961f, 0.753f, 0.698f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_MAP_MARKED) + u8"##MapMarkedIcon").c_str()))
	{
		Gui.ShowAppTeleportMenu = !Gui.ShowAppTeleportMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu allows you to teleport around the map. There are many preset locations, and you may create your own. Any of your custom locations are saved in TeleportLocations.json. You don't need to edit it by hand as you can do all the editing you need in the gui.", FontNormal);
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.361f, 0.129f, 1.0f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_PAINT_BRUSH) + u8"##PaintBrushIcon").c_str()))
	{
		Gui.ShowAppThemeEditor = !Gui.ShowAppThemeEditor;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("You can use the theme editor to change the color scheme and style of the overlay gui. It allows you to save your settings to GUIConfig.json and share that with others so they can use it. This release only supports a having a single theme, but a later release will have a themes folder so you can easily switch between them.", FontNormal);
	ImGui::PopFont();
	ImGui::PopStyleColor();
	//ImGui::PopStyleColor(3);
	//ImGui::PopStyleVar();

	ImGui::PushItemWidth(225.0f);
	ImGui::TextWrapped("Welcome to the RFGR Script Loader overlay. Above are \
some buttons for menus which you might find useful. Tooltips with more info \
appear if you hover over them. You can also access all of these menus with \
the top menu bar above.");
	//ImGui::Text("");
	ImGui::Text("\nUseful shortcuts:");
	ImGui::Text("Toggle overlay: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "F1");
	ImGui::Text("Toggle lua console: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Tilde (~)");
	ImGui::Text("Disable hud & fog: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Numpad 1");
	ImGui::Text("Enable hud & fog: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Numpad 2");

	/*if (ImGui::CollapsingHeader("Notes:"))
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
	}*/

	ImGui::End();
}

void WelcomeGui::ShowAboutWindow(bool* p_open)
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