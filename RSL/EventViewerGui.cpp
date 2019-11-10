#include "EventViewerGui.h"

EventViewerGui::EventViewerGui(std::string Title_)
{
    Title = Title_;
    ScriptManager = IocContainer->resolve<IScriptManager>();
}

void EventViewerGui::Draw()
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

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Event viewer:");
    ImGui::PopFont();
    ImGui::Separator();

    for(auto& Event : ScriptManager->GetEvents())
    {
        if (ImGui::TreeNode(Event.Name.c_str()))
        {
            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, 350.0f);
            ImGui::SetColumnWidth(1, 200.0f);

            int i = 0;
            for (auto& Hook : Event.Hooks)
            {
                auto& HookNonConst = const_cast<ScriptEventHook&>(Hook);
                if (Hook.DeleteOnNextUpdate)
                {
                    continue;
                }
                ImGui::Text(Hook.HookName.c_str());
                ImGui::SameLine();
                ImGui::NextColumn();

                ImGui::Checkbox(fmt::format("Enabled##{}{}", Event.Name, i).c_str(), &HookNonConst.Enabled);
                ImGui::SameLine();
                if (ImGui::Button(fmt::format("Disable##{}{}", Event.Name, i).c_str()))
                {
                    HookNonConst.DeleteOnNextUpdate = true;
                }
                ImGui::NextColumn();
                i++;
            }
            ImGui::TreePop();
        }
        ImGui::Columns(1);
    }

    ImGui::End();
}
