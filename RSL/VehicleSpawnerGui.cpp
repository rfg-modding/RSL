#include "VehicleSpawnerGui.h"

VehicleSpawnerGui::VehicleSpawnerGui(bool* OpenState_, std::string Title_)
{
    OpenState = OpenState_;
    Title = Title_;

    CustomVehicleSpawnParams.veh_info = nullptr;
    CustomVehicleSpawnParams.spawn_pos = vector(0.0f, 0.0f, 0.0f);
    CustomVehicleSpawnParams.osrp = nullptr;
    //CustomVehicleSpawnParams.osrp = ;
    CustomVehicleSpawnParams.zone_id_xy = 0;
    CustomVehicleSpawnParams.spawn_orient = matrix(0.0f);
    CustomVehicleSpawnParams.forward_speed = 0.0f;
    CustomVehicleSpawnParams.parent_handle = 0xFFFFFFFF;
    CustomVehicleSpawnParams.building_handle = 0xFFFFFFFF;
    CustomVehicleSpawnParams.spawn_priority = SPAWN_PRIORITY_HIGH;
    //CustomVehicleSpawnParams.vflags = ;
    //CustomVehicleSpawnParams.veh_spawn_flags = ;
    CustomVehicleSpawnParams.vp = nullptr;
}

void VehicleSpawnerGui::Draw()
{
    if (!*OpenState)
    {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(850.0f, 600.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(Title.c_str(), OpenState))
    {
        ImGui::End();
        return;
    }

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Vehicle spawner:");
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputFloat3("Spawn pos", (float*)& CustomVehicleSpawnParams.spawn_pos);
    ImGui::SameLine();
    if(ImGui::Button("Above player"))
    {
        if(Globals::PlayerPtr)
        {
            CustomVehicleSpawnParams.spawn_pos = Globals::PlayerPtr->Position;
            CustomVehicleSpawnParams.spawn_pos.y += 7.0f;
        }
    }
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputFloat("Forward speed", &CustomVehicleSpawnParams.forward_speed);

    //Can't take an address of bitfield so need to use secondary bool for this.
    static bool ForceToGround = false;
    ImGui::Checkbox("ForceToGround", &ForceToGround);
    static bool ImmediateSpawn = false;
    ImGui::Checkbox("ImmediateSpawn", &ImmediateSpawn);
    static bool IsPlayerCar = false;
    ImGui::Checkbox("IsPlayerCar", &IsPlayerCar);

    if(CustomVehicleSpawnParams.veh_info)
    {
        ImGui::Text("Vehicle info name: %s", CustomVehicleSpawnParams.veh_info->name);
    }

    ImGui::Separator();

    if (ImGui::TreeNode("Preset vehicles"))
    {
        if (Globals::VehicleInfos)
        {
            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, 260.0f);
            for (int i = 0; i < Globals::VehicleInfos->Size(); i++)
            {
                ImGui::BulletText("%s", (*Globals::VehicleInfos)[i].name);
                ImGui::SameLine();
                ImGui::NextColumn();
                ImGui::SetColumnWidth(1, 120.0f);
                if(ImGui::Button(std::string("Spawn##" + std::to_string(i)).c_str()))
                {
                    //Todo: Print custom params address (with adn without modulebase) as hex and compare with x32dbg values
                    std::cout << "ModuleBase, decimal: " << Globals::ModuleBase << "\n";
                    std::cout << "ModuleBase, hex: " << std::hex << Globals::ModuleBase << "\n";
                    std::cout << "&CustomVehicleSpawnParams, decimal: " << &CustomVehicleSpawnParams << "\n";
                    std::cout << "&CustomVehicleSpawnParams, hex: " << std::hex << &CustomVehicleSpawnParams << "\n";
                    std::cout << "ModuleBase + &CustomVehicleSpawnParams, decimal: " << Globals::ModuleBase + (DWORD)&CustomVehicleSpawnParams << "\n";
                    std::cout << "ModuleBase + &CustomVehicleSpawnParams, hex: " << std::hex << Globals::ModuleBase + (DWORD)&CustomVehicleSpawnParams << "\n";
                    auto a = 1;
                    auto b = 2;
                    CustomVehicleSpawnParams.vp = nullptr;
                    CustomVehicleSpawnParams.osrp = nullptr;
                    //CustomVehicleSpawnParams.vp = new vehicle();
                    //CustomVehicleSpawnParams.vp->info = const_cast<vehicle_info*>(&(*Globals::VehicleInfos)[i]);
                    if (ForceToGround)
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.force_to_ground = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.force_to_ground = 0;
                    }
                    if (ImmediateSpawn)
                    {
                        CustomVehicleSpawnParams.vflags.immediate_spawn = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.vflags.immediate_spawn = 0;
                    }
                    if (IsPlayerCar)
                    {
                        CustomVehicleSpawnParams.vflags.m_is_player_car = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.vflags.m_is_player_car = 0;
                    }
                    CustomVehicleSpawnParams.veh_info = const_cast<vehicle_info*>(&(*Globals::VehicleInfos)[i]);

                    bool Result = CreateNewVehicle(&CustomVehicleSpawnParams);
                    //bool Result = SpSpawnVehicle(&CustomVehicleSpawnParams);
                    //auto Result = ObjectSpawnVehicle(&CustomVehicleSpawnParams);
                    auto c = 2;
                    auto d = 3;
                }
                //if (ImGui::Button(std::string("Copy values##" + std::to_string(i)).c_str()))
                //{
                //    CustomVehicleInfo = (*Globals::VehicleInfos)[i];
                //}
                ImGui::NextColumn();
            }
        }
        ImGui::TreePop();
    }
    ImGui::Columns(1);

    ImGui::End();
}
