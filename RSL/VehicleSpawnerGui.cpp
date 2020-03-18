#include "VehicleSpawnerGui.h"

VehicleSpawnerGui::VehicleSpawnerGui(std::string Title_)
{
    Title = Title_;

    CustomVehicleSpawnParams.veh_info = nullptr;
    CustomVehicleSpawnParams.spawn_pos = vector(0.0f, 0.0f, 0.0f);
    CustomVehicleSpawnParams.osrp = nullptr;
    //CustomVehicleSpawnParams.osrp = ;
    CustomVehicleSpawnParams.zone_id_xy = 0;
    vector rvec = { 0.896f, 0.0f, 0.445f };
    vector uvec = { 0.0f, 1.0f, 0.0f };
    vector fvec = { -0.445f, 0.0f, 0.896f };
    CustomVehicleSpawnParams.spawn_orient = matrix(rvec, uvec, fvec);
    CustomVehicleSpawnParams.forward_speed = 0.0f;
    CustomVehicleSpawnParams.parent_handle = 0xFFFFFFFF;
    CustomVehicleSpawnParams.building_handle = 3435973836;
    CustomVehicleSpawnParams.spawn_priority = SPAWN_PRIORITY_HIGH;
    //CustomVehicleSpawnParams.vflags = ;
    //CustomVehicleSpawnParams.veh_spawn_flags = ;
    CustomVehicleSpawnParams.vp = nullptr;

    uint temp = (uint)0 & 4294729732 | 24580;
    projItemFlags = *(obj_item_flags*)&temp;
}

void VehicleSpawnerGui::Draw()
{
    if (!Visible)
    {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(850.0f, 600.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(Title.c_str(), &Visible))
    {
        ImGui::End();
        return;
    }

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Vehicle spawner:");
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::Checkbox("Force vehicle drops", &Globals::ForceVehicleDrops);

    if(ImGui::Button("Copy vehicle spawn cache"))
    {
        CustomVehicleSpawnParams = Globals::VehicleSpawnCache;
    }
    if(ImGui::Button("Spawn with current params (SpSpawnVehicle)"))
    {
        CustomVehicleSpawnParams.vp = nullptr;
        CustomVehicleSpawnParams.osrp = nullptr;
        bool Result = rfg::SpSpawnVehicle(CustomVehicleSpawnParams);
        Logger::Log("SpSpawnVehicle result: {}\n", Result);
    }
    if (ImGui::Button("Spawn with current params(ObjectSpawnVehicle)"))
    {
        CustomVehicleSpawnParams.vp = nullptr;
        CustomVehicleSpawnParams.osrp = nullptr;
        spawn_status_result Result = rfg::object_spawn_vehicle(CustomVehicleSpawnParams);
        Logger::Log("object_spawn_vehicle result: {}\n", (int)Result);
    }

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

    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputScalar("Building handle", ImGuiDataType_U32, &CustomVehicleSpawnParams.building_handle);
    ImGui::SameLine();
    if(ImGui::Button("Reset##BuildingHandleReset"))
    {
        CustomVehicleSpawnParams.building_handle = 3435973836;
    }
    ImGui::SameLine();
    if(ImGui::Button("Max##BuildingHandleReset"))
    {
        CustomVehicleSpawnParams.building_handle = 0xFFFFFFFF;
    }

    //Can't take an address of bitfield so need to use secondary bool for this.
    static bool ForceToGround = false;
    ImGui::Checkbox("ForceToGround", &ForceToGround);
    static bool ImmediateSpawn = false;
    ImGui::Checkbox("ImmediateSpawn", &ImmediateSpawn);
    static bool IsPlayerCar = false;
    ImGui::Checkbox("IsPlayerCar", &IsPlayerCar);
    static bool InteriorSpawn = false;
    ImGui::Checkbox("InteriorSpawn", &InteriorSpawn);
    static bool RoadSpawn = false;
    ImGui::Checkbox("RoadSpawn", &RoadSpawn);
    static bool AmbientSpawn = false;
    ImGui::Checkbox("AmbientSpawn", &AmbientSpawn);
    static bool MobileVehicleSpawn = false;
    ImGui::Checkbox("MobileVehicleSpawn", &MobileVehicleSpawn);

    ImGui::Text("Spawn priority:");
    ImGui::SameLine();
    ImGui::RadioButton("Low", reinterpret_cast<int*>(&CustomVehicleSpawnParams.spawn_priority), SPAWN_PRIORITY_LOW);
    ImGui::SameLine();
    ImGui::RadioButton("Medium", reinterpret_cast<int*>(&CustomVehicleSpawnParams.spawn_priority), SPAWN_PRIORITY_MEDIUM);
    ImGui::SameLine();
    ImGui::RadioButton("High", reinterpret_cast<int*>(&CustomVehicleSpawnParams.spawn_priority), SPAWN_PRIORITY_HIGH);
    ImGui::SameLine();
    ImGui::RadioButton("Special", reinterpret_cast<int*>(&CustomVehicleSpawnParams.spawn_priority), SPAWN_PRIORITY_SPECIAL);
    

    if(CustomVehicleSpawnParams.veh_info)
    {
        ImGui::Text("Vehicle info name: %s", CustomVehicleSpawnParams.veh_info->name);
    }

    ImGui::Separator();

    if (ImGui::TreeNode("Preset vehicles"))
    {
        if (Globals::VehicleInfos)
        {
            ImGui::Columns(3);
            ImGui::SetColumnWidth(0, 260.0f);
            for (int i = 0; i < Globals::VehicleInfos->Size(); i++)
            {
                ImGui::BulletText("%s", (*Globals::VehicleInfos)[i].name);
                ImGui::SameLine();
                ImGui::NextColumn();
                ImGui::SetColumnWidth(1, 120.0f);
                if(ImGui::Button(std::string("Spawn##" + std::to_string(i)).c_str()))
                {
                    ////Todo: Print custom params address (with adn without modulebase) as hex and compare with x32dbg values
                    //std::cout << "ModuleBase, decimal: " << Globals::ModuleBase << "\n";
                    //std::cout << "ModuleBase, hex: " << std::hex << Globals::ModuleBase << "\n";
                    //std::cout << "&CustomVehicleSpawnParams, decimal: " << &CustomVehicleSpawnParams << "\n";
                    //std::cout << "&CustomVehicleSpawnParams, hex: " << std::hex << &CustomVehicleSpawnParams << "\n";
                    //std::cout << "ModuleBase + &CustomVehicleSpawnParams, decimal: " << Globals::ModuleBase + (DWORD)&CustomVehicleSpawnParams << "\n";
                    //std::cout << "ModuleBase + &CustomVehicleSpawnParams, hex: " << std::hex << Globals::ModuleBase + (DWORD)&CustomVehicleSpawnParams << "\n";
                    //auto a = 1;
                    //auto b = 2;
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
                    if(InteriorSpawn)
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.interior_spawn = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.interior_spawn = 0;
                    }
                    if(RoadSpawn)
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.road_spawn = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.road_spawn = 0;
                    }
                    if(AmbientSpawn)
                    {
                        CustomVehicleSpawnParams.vflags.ambient_spawn = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.vflags.ambient_spawn = 0;
                    }
                    if(MobileVehicleSpawn)
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.mobile_vehicle_spawn = 1;
                    }
                    else
                    {
                        CustomVehicleSpawnParams.veh_spawn_flags.mobile_vehicle_spawn = 0;
                    }

                    CustomVehicleSpawnParams.veh_info = &(*Globals::VehicleInfos)[i];

                    //spawn_status_result Result = object_spawn_vehicle(CustomVehicleSpawnParams);
                    //Logger::Log("object_spawn_vehicle result: {}\n", (int)Result);

                    bool Result = rfg::SpSpawnVehicle(CustomVehicleSpawnParams);
                    Logger::Log("SpSpawnVehicle result: {}\n", Result);

                    //bool Result = CreateNewVehicle(&CustomVehicleSpawnParams);
                    //bool Result = SpSpawnVehicle(&CustomVehicleSpawnParams);
                    //auto Result = ObjectSpawnVehicle(&CustomVehicleSpawnParams);
                    auto c = 2;
                    auto d = 3;
                }
                ImGui::SameLine();
                ImGui::NextColumn();
                ImGui::SetColumnWidth(2, 250.0f);
                if(ImGui::Button(std::string("Alt spawn (obj_auto_prop)##" + std::to_string(i)).c_str()))
                {
                    obj_auto_props auto_props;
                    rfg::obj_auto_props_constructor(&auto_props, nullptr, i, CustomVehicleSpawnParams.spawn_pos, Globals::PlayerPtr->Orientation, ForceToGround);
                    object* result = rfg::world_create_object_internal(Globals::RfgWorldPtr, nullptr, rfg::str_hash_string("automobile"), auto_props, nullptr, 0xFFFFFFFF);
                    if (result)
                        Logger::Log("Successfully created custom vehicle object at pos {}\n", result->Position.GetDataString(true, false));
                    else
                        Logger::LogError("Failed to create custom object from zone object binary!\n");
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

    ImGui::Separator();
    ImGui::Separator();

    ImGui::Text("Projectile spawning");

    //Todo: pos, orient, velocity, target, create_id, owner_handle, obj_item_flags
    static bool offsetPosFromPlayer = true;
    static bool usePlayerAimAsTarget = false;

    Gui::LabelAndValue("Weapon info name", projWeaponInfo ? (projWeaponInfo->name ? projWeaponInfo->name : "not set") : "no weapon_info chosen");
    Gui::LabelAndValue("Item info name", projItemInfo ? (projItemInfo->name ? projItemInfo->name : "not set") : "no item_info chosen");

    ImGui::InputFloat3("Projectile pos/offset", (float*)&projPos);
    ImGui::InputFloat3("Projectile velocity", (float*)&projVelocity);
    ImGui::InputFloat3("Projectile target", (float*)&projTarget);
    ImGui::InputScalar("Create ID", ImGuiDataType_U32, &projCreateId);
    ImGui::InputScalar("Owner handle", ImGuiDataType_U32, &projOwnerHandle);
    ImGui::Separator();
    ImGui::Checkbox("Projectile pos is offset from player", &offsetPosFromPlayer);
    ImGui::Checkbox("Use player aim as target", &usePlayerAimAsTarget);

    DrawProjItemFlagsGui();

    //weapon_info list
    if (ImGui::TreeNode("Weapon infos"))
    {
        if (Globals::WeaponInfos.Initialized())
        {
            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, 260.0f);
            for (int i = 0; i < Globals::WeaponInfos.Length(); i++)
            {
                ImGui::BulletText("%s", Globals::WeaponInfos[i].name);
                ImGui::SameLine();
                ImGui::NextColumn();
                ImGui::SetColumnWidth(1, 250.0f);
                if (ImGui::Button(std::string("Set weapon info##" + std::to_string(i)).c_str()))
                {
                    projWeaponInfo = &Globals::WeaponInfos[i];
                }
                ImGui::NextColumn();
            }
        }
        ImGui::TreePop();
    }

    //item_info list
    if (ImGui::TreeNode("Item infos"))
    {
        if (Globals::ItemInfos.Initialized())
        {
            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, 260.0f);
            for (int i = 0; i < Globals::ItemInfos.Length(); i++)
            {
                ImGui::BulletText("%s", Globals::ItemInfos[i].name);
                ImGui::SameLine();
                ImGui::NextColumn();
                ImGui::SetColumnWidth(1, 250.0f);
                if (ImGui::Button(std::string("Set item info##" + std::to_string(i)).c_str()))
                {
                    projItemInfo = &Globals::ItemInfos[i];
                }
                ImGui::NextColumn();
            }
        }
        ImGui::TreePop();
    }

    if(ImGui::Button("Spawn projectile"))
    {
        bool canProceed = true;
        if (!projWeaponInfo)
            canProceed = false;
        if (!projItemInfo)
            canProceed = false;

        if(canProceed)
        {
            vector finalPos = offsetPosFromPlayer ? Globals::PlayerPtr->Position + projPos : projPos;
            vector finalTarget = usePlayerAimAsTarget ? Globals::PlayerPtr->aim_pos : projTarget;

            obj_projectile_props projProps;
            rfg::obj_projectile_props_constructor(&projProps, nullptr, projOwnerHandle, projItemInfo, projItemFlags,
                projWeaponInfo, finalPos, projOrient, projVelocity, finalTarget, projCreateId);

            const uint projClassnameHash = rfg::str_hash_string("projectile");
            object* result = rfg::world_create_object_internal(Globals::RfgWorldPtr, nullptr, projClassnameHash, projProps, nullptr, 0xFFFFFFFF);

            if (result)
                Logger::Log("Successfully created projectile at pos {}\n", result->Position.GetDataString(true, false));
            else
                Logger::LogError("Failed to create custom projectile!\n");
        }
        else
        {
            Logger::LogError("Failed to create custom projectile! projWeaponInfo or projItemInfo is a nullptr!\n");
        }
    }

    ImGui::End();
}

void VehicleSpawnerGui::DrawProjItemFlagsGui()
{
    static bool respawn = projItemFlags.respawn;
    static bool no_physics = projItemFlags.no_physics;
    static bool simulate = projItemFlags.simulate;
    static bool props_created = projItemFlags.props_created;
    static bool item_held = projItemFlags.item_held;
    static bool no_save = projItemFlags.no_save;
    static bool preplaced = projItemFlags.preplaced;
    static bool update_attach_point = projItemFlags.update_attach_point;
    static bool dropped_by_player = projItemFlags.dropped_by_player;
    static bool touched_last_frame = projItemFlags.touched_last_frame;
    static bool character_prop = projItemFlags.character_prop;
    static bool attached_cloth_sim = projItemFlags.attached_cloth_sim;
    static bool doing_errode = projItemFlags.doing_errode;
    static bool cast_shadows = projItemFlags.cast_shadows;
    static bool cast_drop_shadows = projItemFlags.cast_drop_shadows;
    static bool xray_visible = projItemFlags.xray_visible;
    static bool dont_dampen_impulse = projItemFlags.dont_dampen_impulse;
    static bool shield_initialized = projItemFlags.shield_initialized;

    ImGui::Text("Projectile item flags");
    ImGui::Checkbox("respawn", &respawn);
    ImGui::Checkbox("no_physics", &no_physics);
    ImGui::Checkbox("simulate", &simulate);
    ImGui::Checkbox("props_created", &props_created);
    ImGui::Checkbox("item_held", &item_held);
    ImGui::Checkbox("no_save", &no_save);
    ImGui::Checkbox("preplaced", &preplaced);
    ImGui::Checkbox("update_attach_point", &update_attach_point);
    ImGui::Checkbox("dropped_by_player", &dropped_by_player);
    ImGui::Checkbox("touched_last_frame", &touched_last_frame);
    ImGui::Checkbox("character_prop", &character_prop);
    ImGui::Checkbox("attached_cloth_sim", &attached_cloth_sim);
    ImGui::Checkbox("doing_errode", &doing_errode);
    ImGui::Checkbox("cast_shadows", &cast_shadows);
    ImGui::Checkbox("cast_drop_shadows", &cast_drop_shadows);
    ImGui::Checkbox("xray_visible", &xray_visible);
    ImGui::Checkbox("dont_dampen_impulse", &dont_dampen_impulse);
    ImGui::Checkbox("shield_initialized", &shield_initialized);

    projItemFlags.respawn = respawn;
    projItemFlags.no_physics = no_physics;
    projItemFlags.simulate = simulate;
    projItemFlags.props_created = props_created;
    projItemFlags.item_held = item_held;
    projItemFlags.no_save = no_save;
    projItemFlags.preplaced = preplaced;
    projItemFlags.update_attach_point = update_attach_point;
    projItemFlags.dropped_by_player = dropped_by_player;
    projItemFlags.touched_last_frame = touched_last_frame;
    projItemFlags.character_prop = character_prop;
    projItemFlags.attached_cloth_sim = attached_cloth_sim;
    projItemFlags.doing_errode = doing_errode;
    projItemFlags.cast_shadows = cast_shadows;
    projItemFlags.cast_drop_shadows = cast_drop_shadows;
    projItemFlags.xray_visible = xray_visible;
    projItemFlags.dont_dampen_impulse = dont_dampen_impulse;
    projItemFlags.shield_initialized = shield_initialized;
}
