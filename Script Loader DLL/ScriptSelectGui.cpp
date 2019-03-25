#include "ScriptSelectGui.h"
#include "TextEditor.h"
#include "ScriptManager.h"

ScriptSelectGui::ScriptSelectGui(bool* _OpenState, std::string _Title)
{
	OpenState = _OpenState;
	Title = _Title;

	WindowFlags = 0;
	//WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	//WindowFlags |= ImGuiWindowFlags_MenuBar;
	//WindowFlags |= ImGuiWindowFlags_NoMove;
	//WindowFlags |= ImGuiWindowFlags_NoResize;
	//WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

ScriptSelectGui::~ScriptSelectGui()
{

}

void ScriptSelectGui::Draw()
{
	if (!*OpenState)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(400.0f, 500.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), OpenState, WindowFlags))
	{
		ImGui::End();
		return;
	}

	ImGui::PushFont(FontBig);
	ImGui::Text("Scripts folder:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Rescan"))
	{
		Scripts->ScanScriptsFolder();
	}
	for (auto i : Scripts->Scripts)
	{
		ImGui::Columns(2);
		ImGui::Text(i.Name.c_str()); ImGui::SameLine();
		ImGui::NextColumn();
		ImGui::SetColumnWidth(-1, 200.0f);

		//ImGui::PushID(0);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
		//ImGui::Columns(2);
		if (ImGui::Button(std::string(std::string(ICON_FA_PLAY) + u8"##" + i.FullPath).c_str()))
		{
			bool Result = Scripts->RunScript(i.FullPath);
			//Logger::Log("Result from running " + Scripts->Scripts[ScriptIndex].Name + ": " + std::to_string(Result), LogInfo);
		}
		ImGui::PopStyleColor(1);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
		ImGui::SameLine();
		if (ImGui::Button(std::string(std::string(ICON_FA_STOP) + u8"##" + i.FullPath).c_str()))
		{

		}
		ImGui::PopStyleColor();
		ImGui::SameLine();
		if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8"##" + i.FullPath).c_str()))
		{
			Gui->ScriptEditor->LoadScript(i.FullPath, i.Name);
			Gui->ShowAppScriptEditor = true;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar();
		ImGui::NextColumn();
		//ImGui::PopID();
	}
	ImGui::End();
}
