#include "MenuBarGui.h"
#include "ScriptManager.h"

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
	if (!OpenState)
	{
		return;
	}
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Deactivate Script Loader", "Hold ctrl+alt for 5s")) { ConfirmScriptLoaderDeactivation(); }
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
}

void MenuBarGui::ConfirmScriptLoaderDeactivation()
{
	ImGui::OpenPopup("Confirm Deactivation");
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