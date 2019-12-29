#include "ScriptSelectGui.h"
#include "TextEditorWrapper.h"

ScriptSelectGui::ScriptSelectGui(std::string Title_)
{
    Title = Title_;
    ScriptManager = IocContainer->resolve<IScriptManager>();
    GuiManager = IocContainer->resolve<IGuiManager>();
}

void ScriptSelectGui::Draw()
{
	if (!Visible)
        return;

    ImGui::SetNextWindowSize(ImVec2(450.0f, 500.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), &Visible))
	{
		ImGui::End();
		return;
	}

    static auto ScriptEditorRef = GuiManager->GetGuiReference<TextEditorWrapper>("Script editor").value();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Scripts folder:");
	ImGui::PopFont();
	ImGui::Separator();
	if (ImGui::Button("Rescan"))
        ScriptManager->ScanScriptsFolder();

    ImGui::Separator();
	for (const auto& SubFolder : ScriptManager->GetSubFolders())
	{
        if(!ImGui::TreeNode(SubFolder.Name.c_str()))
            continue;

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 300.0f);
        ImGui::SetColumnWidth(1, 200.0f);
        for (auto& Script : SubFolder.Scripts)
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
                ScriptManager->RunScript(Script.FullPath);

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
        ImGui::Columns();
	}
	ImGui::End();
}
