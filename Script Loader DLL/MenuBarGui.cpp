#include "MenuBarGui.h"
#include "GuiSystem.h"

MenuBarGui::MenuBarGui(bool* _OpenState, std::string _Title)
{
	OpenState = _OpenState;
	Title = _Title;

	WindowFlags = 0;
	WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	WindowFlags |= ImGuiWindowFlags_MenuBar;
	WindowFlags |= ImGuiWindowFlags_NoMove;
	WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

MenuBarGui::~MenuBarGui()
{

}

void MenuBarGui::Draw()
{
	static bool ShowDeactivationConfirmationPopup = false;
	if (!*OpenState)
	{
		return;
	}
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_POWER_OFF) + u8" Deactivate script loader").c_str(), "Hold ctrl+alt for 5s")) 
			{
				ShowDeactivationConfirmationPopup = true;
			}
			ImGui::PopStyleColor();
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_SLIDERS_H) + u8" Tweaks").c_str(), NULL, &Gui->ShowAppTweaksMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_MAP_MARKED) + u8" Teleport").c_str(), NULL, &Gui->ShowAppTeleportMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_LIST) + u8" Logger").c_str(), NULL, &Gui->ShowAppLogWindow)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_SEARCH) + u8" Player view").c_str(), NULL, &Gui->ShowAppIntrospectionMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_PALETTE) + u8" Theme editor").c_str(), NULL, &Gui->ShowAppThemeEditor)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_CAMERA) + u8" Free cam settings").c_str(), NULL, &Gui->ShowAppFreeCamSettings)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scripting"))
		{
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_CODE) + u8" Scripts").c_str(), NULL, &Gui->ShowAppScriptsMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_TERMINAL) + u8" Lua console").c_str(), NULL, &Gui->ShowAppConsole)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_EDIT) + u8" Script editor").c_str(), NULL, &Gui->ShowAppScriptEditor)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_HOME) + u8" Welcome").c_str(), NULL, &Gui->ShowAppWelcome)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_INFO) + u8" Metrics").c_str(), NULL, &Gui->ShowAppMetrics)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_INFO) + u8" About").c_str(), NULL, &Gui->ShowAppAbout)) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (ShowDeactivationConfirmationPopup)
	{
		ImGui::OpenPopup("Confirm Deactivation");
		ShowDeactivationConfirmationPopup = false;
	}
	ConfirmScriptLoaderDeactivation();

	if (Gui->ShowAppMetrics)
	{
		ImGui::ShowMetricsWindow(&Gui->ShowAppMetrics);
	}
	if (Gui->ShowAppAbout)
	{
		ShowAboutWindow(&Gui->ShowAppAbout);
	}
}

void MenuBarGui::ConfirmScriptLoaderDeactivation()
{
	if (ImGui::BeginPopupModal("Confirm Deactivation"))
	{
		ImGui::Text("Are you sure you'd like to deactivate the script loader?");
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
		if (ImGui::Button("Exit"))
		{
			ScriptLoaderCloseRequested = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::PopStyleColor();
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void MenuBarGui::ShowAboutWindow(bool* p_open)
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