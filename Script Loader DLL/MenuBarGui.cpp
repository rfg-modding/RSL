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
			if (ImGui::MenuItem("Deactivate Script Loader", "Hold ctrl+alt for 5s")) { ShowDeactivationConfirmationPopup = true; }
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Tweaks", NULL, ShowAppTweaksMenu)) {}
			if (ImGui::MenuItem("Teleport", NULL, ShowAppTeleportMenu)) {}
			if (ImGui::MenuItem("Logger", NULL, ShowAppLogWindow)) {}
			if (ImGui::MenuItem("Player View", NULL, ShowAppIntrospectionMenu)) {}
			if (ImGui::MenuItem("Theme Editor", NULL, ShowAppThemeEditor)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scripting"))
		{
			if (ImGui::MenuItem("Scripts", NULL, ShowAppScriptsMenu)) {}
			if (ImGui::MenuItem("Lua Console", NULL, ShowAppConsole)) 
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
			if (ImGui::MenuItem("Script Editor", NULL, ShowAppScriptEditor)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Welcome", NULL, ShowAppMainWindow)) {}
			if (ImGui::MenuItem("About", NULL, ShowAppAbout)) {}
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
		if (ImGui::Button("Exit"))
		{
			ScriptLoaderCloseRequested = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}
	}
}