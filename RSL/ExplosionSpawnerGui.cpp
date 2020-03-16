#include "ExplosionSpawnerGui.h"

ExplosionSpawnerGui::ExplosionSpawnerGui(std::string Title_)
{
    Title = Title_;
}

void ExplosionSpawnerGui::Draw()
{
    if (!Visible)
        return;
    ImGui::SetNextWindowSize(ImVec2(850.0f, 600.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(Title.c_str(), &Visible))
    {
        ImGui::End();
        return;
    }

    if (!DrawnOnce)
    {
        std::optional<explosion_info*> NewInfo = Globals::GetExplosionInfo("mine"); //Set default values to the land mine
        if (NewInfo)
            CustomExplosionInfo = *NewInfo.value();

        DrawnOnce = true;
    }

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Explosion spawner:");
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::Checkbox("Spawn explosion with middle mouse?", &MiddleMouseBoomActive);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Middle mouse explosions per second limit", &MiddleMouseExplosionsPerSecond);
    ImGui::SameLine();
    Gui::ShowHelpMarker("Used to prevent lag from 100s of explosions per second since the script loader thread is currently uncapped.");
    if (ImGui::Button("Boom"))
        rfg::ExplosionCreate(&CustomExplosionInfo, Globals::PlayerPtr, Globals::PlayerPtr, &Globals::PlayerPtr->aim_pos, &Globals::PlayerPtr->Orientation, &Globals::PlayerPtr->aim_pos, NULL, false);

    ImGui::SameLine();
    Gui::ShowHelpMarker("Spawns an explosion with the values entered below where the player is aiming. The middle mouse button option is much more convenient.");
    ImGui::Separator();
    if (ImGui::TreeNode("Spawn settings"))
    {
        ImGui::Separator();
        ImGui::PushFont(Globals::FontBig);
        ImGui::Text("Explosion info:");
        ImGui::PopFont();
        ImGui::Separator();
        
        ImGui::PushItemWidth(250.0f);

        ImGui::InputText("Name", (char*)&CustomExplosionInfo.m_name, 32);
        ImGui::InputInt("Unique ID", &CustomExplosionInfo.m_unique_id);
        ImGui::SameLine();
        Gui::ShowHelpMarker("Make sure that you use a unique value for the unique id variable or you might get behavior not matching \
the variables you've set. I believe that all of the games explosions use the lower unique id values. So if you just use a value larger than \
1000 you shouldn't have an issue.");
        ImGui::InputInt("Name CRC", (int*)&CustomExplosionInfo.m_name_crc_str); //Todo: Need to switch these to use the proper types with ImGui::InputScalar
        ImGui::SameLine();
        Gui::ShowHelpMarker("You also need to be careful that this value is unique. Currently there's no easy way to check that, but the default value never seems to have issues.");
        ImGui::InputFloat("Radius", &CustomExplosionInfo.m_radius);
        ImGui::InputFloat("Secondary radius", &CustomExplosionInfo.m_secondary_radius);
        ImGui::InputFloat("Knockdown radius", &CustomExplosionInfo.m_knockdown_radius);
        ImGui::InputFloat("Flinch radius", &CustomExplosionInfo.m_flinch_radius);
        ImGui::InputFloat("AI sound radius", &CustomExplosionInfo.m_ai_sound_radius);
        ImGui::InputInt("Human min damage hitpoints", (int*)& CustomExplosionInfo.m_human_min_damage_hitpoints);
        ImGui::InputInt("Human max damage hitpoints", (int*)& CustomExplosionInfo.m_human_max_damage_hitpoints);
        ImGui::InputInt("Vehicle min damage hitpoints", (int*)& CustomExplosionInfo.m_vehicle_min_damage_hitpoints);
        ImGui::InputInt("Vehicle max damage hitpoints", (int*)& CustomExplosionInfo.m_vehicle_max_damage_hitpoints);
        ImGui::InputFloat("Player damage multiplier", &CustomExplosionInfo.player_damage_mult);
        ImGui::InputFloat("Player vehicle damage multiplier", &CustomExplosionInfo.player_veh_damage_mult);
        ImGui::InputFloat("Player vehicle impulse multiplier", &CustomExplosionInfo.player_vehicle_impulse_mult);
        ImGui::InputFloat("Impulse magnitude", &CustomExplosionInfo.m_impulse_magnitude);
        ImGui::InputInt("Structural damage", &CustomExplosionInfo.m_structural_damage);

        ImGui::InputInt("Expanding explosion duration", (int*)& CustomExplosionInfo.expanding_explosion_duration);
        ImGui::InputInt("Expanding explosion delay", (int*)& CustomExplosionInfo.expanding_explosion_delay);
        ImGui::InputInt("Number of effects", (int*)& CustomExplosionInfo.m_num_effects);
        ImGui::InputInt("Effect 0", (int*)& CustomExplosionInfo.m_effects[0]);
        ImGui::SameLine();
        Gui::ShowHelpMarker("Try some of the values up in the hundreds. You can try checking the values in EffectsInfo.txt, but they don't seem to match up with these values. I'll try to figure out a better way to choose an explosion effect other than guessing.");
        ImGui::InputInt("Effect 1", (int*)& CustomExplosionInfo.m_effects[1]);
        ImGui::InputInt("Effect 2", (int*)& CustomExplosionInfo.m_effects[2]);
        ImGui::InputInt("Effect 3", (int*)& CustomExplosionInfo.m_effects[3]);
        ImGui::InputInt("Number of material effects", (int*)& CustomExplosionInfo.m_num_material_effects);
        ImGui::InputInt("Material effect 0", (int*)& CustomExplosionInfo.m_material_effects[0]);
        ImGui::InputInt("Material effect 1", (int*)& CustomExplosionInfo.m_material_effects[1]);
        ImGui::InputInt("Material effect 2", (int*)& CustomExplosionInfo.m_material_effects[2]);
        ImGui::InputInt("Material effect 3", (int*)& CustomExplosionInfo.m_material_effects[3]);
        ImGui::InputInt("Material effect 4", (int*)& CustomExplosionInfo.m_material_effects[4]);
        ImGui::InputInt("Material effect 5", (int*)& CustomExplosionInfo.m_material_effects[5]);
        ImGui::InputInt("Material effect 6", (int*)& CustomExplosionInfo.m_material_effects[6]);
        ImGui::InputInt("Material effect 7", (int*)& CustomExplosionInfo.m_material_effects[7]);

        ImGui::Text("Salvage material type:");
        ImGui::RadioButton("Invalid Material", (int*)& CustomExplosionInfo.salvage_material, INVALID_SALVAGE_MATERIAL);
        ImGui::SameLine();
        ImGui::RadioButton("Metal", (int*)& CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_METAL);
        ImGui::SameLine();
        ImGui::RadioButton("Ore", (int*)& CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_ORE);
        ImGui::SameLine();
        ImGui::RadioButton("Chemical", (int*)& CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_CHEMICAL);

        ImGui::InputInt("Salvage max pieces", &CustomExplosionInfo.salvage_max_pieces);
        ImGui::InputFloat("Salvage probability", &CustomExplosionInfo.salvage_probability);
        ImGui::InputInt("Time between breaks", &CustomExplosionInfo.time_between_breaks);
        ImGui::InputFloat("Half angle dot", &CustomExplosionInfo.half_angle_dot);
        ImGui::InputFloat("Blast decal radius", &CustomExplosionInfo.blast_decal_radius);
        //camera_shake_type[32]
        ImGui::InputFloat("Camera shake multiplier", &CustomExplosionInfo.camera_shake_multiplier);
        ImGui::InputFloat("Camera shake falloff", &CustomExplosionInfo.camera_shake_falloff);
        ImGui::PopItemWidth();
        ImGui::Checkbox("Ignore orientation", &CustomExplosionInfo.ignore_orientation);
        ImGui::Checkbox("Always ragdoll", &CustomExplosionInfo.always_ragdoll);
        ImGui::TreePop();
    }

    if(Globals::ExplosionInfos.Initialized() && ImGui::TreeNode("Preset explosions"))
    {
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 260.0f);
        for(int i = 0; i < Globals::ExplosionInfos.Size(); i++)
        {
            ImGui::BulletText("%s", Globals::CharArrayToString(Globals::ExplosionInfos[i].m_name, 32).c_str());
            ImGui::SameLine();
            ImGui::NextColumn();
            ImGui::SetColumnWidth(1, 180.0f);

            if(ImGui::Button(fmt::format("Copy values##{}", i)))
                CustomExplosionInfo = Globals::ExplosionInfos[i];

            if(Globals::CharArrayToString(Globals::ExplosionInfos[i].m_name, 32) == "edf_power_core")
            {
                ImGui::SameLine();
                Gui::ShowHelpMarker("Note that this explosion has no visual effect unless you've entered \
                    the free fire zone, and is not guaranteed to work outside of it. It still damages the environment, \
                    just does not have a vfx.", "(Bug note)");
            }
            ImGui::NextColumn();
        }
        ImGui::TreePop();
    }
    ImGui::Columns(1);

    if (Globals::EffectInfos.Initialized() && ImGui::TreeNode("Effects"))
    {
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 350.0f);
        for(int i = 0; i < Globals::EffectInfos.Size(); i++)
        {
            ImGui::BulletText("%s, ID: %i", Globals::CharArrayToString(Globals::EffectInfos[i].name, 65).c_str(), i); ImGui::SameLine();
            ImGui::NextColumn();
            ImGui::SetColumnWidth(1, 500.0f);
            if (ImGui::Button(fmt::format("Effect 0##{}", i))) { CustomExplosionInfo.m_effects[0] = i; } ImGui::SameLine();
            if (ImGui::Button(fmt::format("Effect 1##{}", i))) { CustomExplosionInfo.m_effects[1] = i; } ImGui::SameLine();
            if (ImGui::Button(fmt::format("Effect 2##{}", i))) { CustomExplosionInfo.m_effects[2] = i; } ImGui::SameLine();
            if (ImGui::Button(fmt::format("Effect 3##{}", i))) { CustomExplosionInfo.m_effects[3] = i; }
            ImGui::NextColumn();
        }
        ImGui::TreePop();
    }
    ImGui::Columns(1);
    ImGui::End();
}
