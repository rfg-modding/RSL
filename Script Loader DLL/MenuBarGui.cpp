#include "MenuBarGui.h"
#include "ScriptManager.h"

MenuBarGui::MenuBarGui()
{

}

MenuBarGui::~MenuBarGui()
{

}

void MenuBarGui::Initialize(bool * _OpenState)
{
	OpenState = _OpenState;
	
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

void MenuBarGui::Draw(const char* Title)
{
	static bool ShowDeactivationConfirmationPopup = false;
	if (!OpenState)
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
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_SLIDERS_H) + u8" Tweaks").c_str(), NULL, ShowAppTweaksMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_MAP_MARKED) + u8" Teleport").c_str(), NULL, ShowAppTeleportMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_LIST) + u8" Logger").c_str(), NULL, ShowAppLogWindow)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_SEARCH) + u8" Player view").c_str(), NULL, ShowAppIntrospectionMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_PALETTE) + u8" Theme editor").c_str(), NULL, ShowAppThemeEditor)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scripting"))
		{
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_CODE) + u8" Scripts").c_str(), NULL, ShowAppScriptsMenu)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_TERMINAL) + u8" Lua console").c_str(), NULL, ShowAppConsole))
			{
				if (*ShowAppConsole)
				{
					Gui.ActivateLuaConsole();
				}
				else
				{
					Gui.DeactivateLuaConsole();
				}
			}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_EDIT) + u8" Script editor").c_str(), NULL, ShowAppScriptEditor)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_HOME) + u8" Welcome").c_str(), NULL, ShowAppMainWindow)) {}
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_INFO) + u8" Metrics").c_str(), NULL, Gui.ShowAppMetrics)) { ImGui::ShowMetricsWindow(&Gui.ShowAppMetrics); }
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_INFO) + u8" About").c_str(), NULL, ShowAppAbout)) {}
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