#include "GraphicsTweaksGui.h"

GraphicsTweaksGui::GraphicsTweaksGui(std::string Title_)
{
    Title = Title_;
}

void GraphicsTweaksGui::Draw()
{
    if (!Visible)
        return;

    ImGui::SetNextWindowSize(ImVec2(850.0f, 600.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(Title.c_str(), &Visible))
    {
        ImGui::End();
        return;
    }

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Graphics tweaks:");
    ImGui::PopFont();
    ImGui::Separator();
    if (ImGui::CollapsingHeader("HDR State"))
    {
        if(Globals::GraphicsState.Ready())
        {
            HdrStateBlock& State = Globals::GraphicsState.HdrState;
            ImGui::Checkbox("Override", State.override);
            ImGui::Checkbox("Enable", State.enable);
            ImGui::Checkbox("Bloom soft", State.bloom_soft);
            ImGui::Checkbox("Bloom alternate", State.bloom_alternate);
            ImGui::Checkbox("Tone mapped bloom", State.tone_mapped_bloom);
            ImGui::Checkbox("Use hdr level", State.use_hdr_level);
            ImGui::Checkbox("Bloom new", State.bloom_new);
            ImGui::Checkbox("Bloom super soft", State.bloom_super_soft);
            ImGui::Separator();

            ImGui::PushItemWidth(230.0f);
            ImGui::InputFloat("HDR Level", State.hdr_level);
            ImGui::InputFloat("Brightpass threshold", State.brightpass_threshold);
            ImGui::InputFloat("Brightpass offset", State.brightpass_offset);
            ImGui::Separator();

            ImGui::PushItemWidth(230.0f);
            ImGui::InputFloat("Bloom amount", State.bloom_amount);
            ImGui::InputFloat("Bloom theta", State.bloom_theta);
            ImGui::InputFloat("Bloom slope A", State.bloom_slope_A);
            ImGui::InputFloat("Bloom slope B", State.bloom_slope_B);
            ImGui::PopItemWidth();
            ImGui::Separator();

            ImGui::Checkbox("Eye override", State.eye_override);
            ImGui::PushItemWidth(230.0f);
            ImGui::InputFloat("Luminance range", State.lum_range);
            ImGui::InputFloat("Luminance offset", State.lum_offset);
            ImGui::InputFloat("Luminance min", State.luminance_min);
            ImGui::InputFloat("Luminance max", State.luminance_max);
            ImGui::InputFloat("Luminance mask max", State.luminance_mask_max);
            ImGui::InputFloat3("Luminance conversion", (float*)State.luminance_conversion);
            ImGui::PopItemWidth();
            ImGui::Separator();

            ImGui::PushItemWidth(230.0f);
            ImGui::InputFloat("Iris rate", State.iris_rate);
            ImGui::InputFloat("Eye adaption base", State.eye_adaption_base);
            ImGui::InputFloat("Eye adaption amount", State.eye_adaption_amount);
            ImGui::InputFloat("Eye fade min", State.eye_fade_min);
            ImGui::InputFloat("Eye fade max", State.eye_fade_max);
            ImGui::PopItemWidth();
        }
        else
            ImGui::Text("Globals::GraphicsState has not been initialized! Cannot display hdr state.");
    }

    if(ImGui::CollapsingHeader("Shadows"))
    {
        if(Globals::ShadowMapSizes.Initialized() || !Globals::ShadowMapSizes.GetRawPointer())
        {
            ImGui::SetNextItemWidth(300.0f);
            ImGui::InputInt4("Shadow map sizes", Globals::ShadowMapSizes.GetRawPointer());
            ImGui::SameLine();
            Util::Gui::ShowHelpMarker("The quickest way to get the shadow res to update is to go in the display settings and toggle something like depth of field, apply it, and unpause the game. Then you can change it back if you want.");
        }
        else
            ImGui::Text("Globals::ShadowMapSizes has not been initialized! Cannot display shadow state.");
    }

    //Todo: Add AO settings, values such as g_Intensity and g_edgeSharpness
    //Todo: Add glass settings, values like g_fresnelBias (not sure what this even does)

    ImGui::End();
}

