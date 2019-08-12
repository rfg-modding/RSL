#include "ScriptSelectGui.h"
#include "TextEditorWrapper.h"
#include "ScriptManager.h"
#include "GuiSystem.h"

void ScriptSelectGui::Draw()
{
	if (!Visible)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(450.0f, 500.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), &Visible, WindowFlags))
	{
		ImGui::End();
		return;
	}

    static auto ScriptEditorRef = Globals::Gui->GetGuiReference<TextEditorWrapper>("Script editor").value();

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Scripts folder:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Rescan"))
	{
        Globals::Scripts->ScanScriptsFolder();
	}
    ImGui::Separator();

	for (const auto& SubFolder : Globals::Scripts->SubFolders)
	{
        if(ImGui::TreeNode(SubFolder.Name.c_str()))
        {
            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, 300.0f);
            ImGui::SetColumnWidth(1, 200.0f);
            for(auto& Script : SubFolder.Scripts)
            {
                ImGui::Text("\t%s", Script.Name.c_str());
                ImGui::SameLine();
                ImGui::NextColumn();
            
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
                if (ImGui::Button(std::string(std::string(ICON_FA_PLAY) + u8"##" + Script.FullPath).c_str()))
                {
                    bool Result = Globals::Scripts->RunScript(Script.FullPath);
                }
                ImGui::PopStyleColor();
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
                ImGui::SameLine();
                if (ImGui::Button(std::string(std::string(ICON_FA_STOP) + u8"##" + Script.FullPath).c_str()))
                {

                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
                if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8"##" + Script.FullPath).c_str()))
                {
                    ScriptEditorRef.Get().LoadScript(Script.FullPath, Script.Name);
                    ScriptEditorRef.Get().Visible = true;
                }
                ImGui::PopStyleColor(3);
                ImGui::PopStyleVar();
                ImGui::NextColumn();
            }
            ImGui::TreePop();
        }
        ImGui::Columns();


		//ImGui::Columns(2);
		//ImGui::Text(i.Name.c_str()); ImGui::SameLine();
		//ImGui::NextColumn();
		//ImGui::SetColumnWidth(1, 200.0f);

		////ImGui::PushID(0);
		//ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
		//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
		//ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
		////ImGui::Columns(2);
		//if (ImGui::Button(std::string(std::string(ICON_FA_PLAY) + u8"##" + i.FullPath).c_str()))
		//{
		//	bool Result = Scripts->RunScript(i.FullPath);
		//	//Logger::Log("Result from running " + Scripts->SubFolders[ScriptIndex].Name + ": " + std::to_string(Result), LogInfo);
		//}
		//ImGui::PopStyleColor(1);
		//ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
		//ImGui::SameLine();
		//if (ImGui::Button(std::string(std::string(ICON_FA_STOP) + u8"##" + i.FullPath).c_str()))
		//{

		//}
		//ImGui::PopStyleColor();
		//ImGui::SameLine();
		//if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8"##" + i.FullPath).c_str()))
		//{
		//	Gui->ScriptEditor->LoadScript(i.FullPath, i.Name);
		//	Gui->ShowAppScriptEditor = true;
		//}
		//ImGui::PopStyleColor(3);
		//ImGui::PopStyleVar();
		//ImGui::NextColumn();
		////ImGui::PopID();
	}
	ImGui::End();
}
