#include "IntrospectionGui.h"
#include "LuaFunctions.h"

void IntrospectionGui::Draw()
{
	DrawPlayerIntrospectionGui(Title.c_str()); //DrawPlayerIntrospectionGui("Player Introspection Menu");
}

void IntrospectionGui::DrawPlayerIntrospectionGui(const char* Title)
{
	if (!*OpenState)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title, OpenState, WindowFlags))
	{
		ImGui::End();
		return;
	}

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Object introspection");
	ImGui::PopFont();
	ImGui::Separator();
    
    ImGui::SetNextItemWidth(300.0f);
    ImGui::TextWrapped("Aim at an object and press numpad 4 to view it's info in this menu. Alternatively, search for an object using one of the following criteria. You can only search by one criteria at a time.");
    ImGui::Separator();

    static std::string NameSearchBuffer;
    ImGui::Text("Search by name:"); ImGui::SameLine();
    ImGui::InputText("##ObjectNameSearchInput", &NameSearchBuffer); ImGui::SameLine();
    if(ImGui::Button("Search##ObjectNameSearchButton"))
    {
        Object* NewObject = Lua::GetObjectByName(NameSearchBuffer);
        if(NewObject)
        {
            SavedTargetObjectHandle = NewObject->Handle;
        }
    }

    static uint HandleSearchBuffer = 0;
    ImGui::Text("Search by handle (unsigned):"); ImGui::SameLine();
    ImGui::InputScalar("##ObjectHandleSearchInput", ImGuiDataType_U32, &HandleSearchBuffer); ImGui::SameLine(); //Todo: Need to update imgui to get stuff like ImGui::InputUint
    if (ImGui::Button("Search##ObjectHandleSearchButton"))
    {
        if(WorldObjectFromHandle(Globals::RfgWorldPtr, NULL, HandleSearchBuffer))
        {
            SavedTargetObjectHandle = HandleSearchBuffer;
        }
    }
    
    static uint IndexSearchBuffer = 0;
    ImGui::Text("Search by index (unsigned):"); ImGui::SameLine();
    ImGui::InputScalar("##ObjectIndexSearchInput", ImGuiDataType_U32, &IndexSearchBuffer); ImGui::SameLine(); //Todo: Need to update imgui to get stuff like ImGui::InputUint
    if (ImGui::Button("Search##ObjectIndexSearchButton"))
    {
        if(Globals::RfgWorldPtr)
        {
            if (IndexSearchBuffer < Globals::RfgWorldPtr->all_objects.Size())
            {
                SavedTargetObjectHandle = Globals::RfgWorldPtr->all_objects[IndexSearchBuffer]->Handle;
            }
        }
    }

    ImGui::Separator();

    ImGui::Text("Saved target object handle:");
    ImGui::SameLine();
    ImGui::Text(std::to_string(SavedTargetObjectHandle).c_str());

    if(Globals::RfgWorldPtr)
    {
        Object* TargetObject = WorldObjectFromHandle(Globals::RfgWorldPtr, NULL, SavedTargetObjectHandle);
        if(TargetObject)
        {
            ImGui::Text("Name:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, WorldGetObjectName(Globals::RfgWorldPtr, NULL, TargetObject));
            ImGui::Text("Position:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->Position.GetDataString(false, false).c_str());

            if (ImGui::TreeNode("Orientation matrix"))
            {
                ImGui::Text("Right vector:"); ImGui::SameLine(); 
                ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->Orientation.rvec.GetDataString(false, false).c_str());
                ImGui::Text("Up vector:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->Orientation.uvec.GetDataString(false, false).c_str());
                ImGui::Text("Forward vector:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->Orientation.fvec.GetDataString(false, false).c_str());

                ImGui::TreePop();
            }

            ImGui::Text("ChildPtr address:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->ChildPtr ? std::to_string((DWORD)TargetObject->ChildPtr).c_str() : "nullptr");
            ImGui::Text("ChildNext address:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->ChildNext ? std::to_string((DWORD)TargetObject->ChildNext).c_str() : "nullptr");
            ImGui::Text("ChildPrevious address:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->ChildPrevious ? std::to_string((DWORD)TargetObject->ChildPrevious).c_str() : "nullptr");
            //ChildConstraintPtr
            //HostConstraintPtr

            const std::string AttachInfoStatus = TargetObject->AttachInfo ? " (Valid)" : " (nullptr)";
            if (ImGui::TreeNode(std::string(std::string("AttachInfo") + AttachInfoStatus).c_str()))
            {
                if (TargetObject->AttachInfo != nullptr)
                {
                    ImGui::Text("Parent handle:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->AttachInfo->parent_handle).c_str());
                    ImGui::Text("Parent prop point:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->AttachInfo->parent_prop_point).c_str());
                    ImGui::Text("Child prop point:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->AttachInfo->child_prop_point).c_str());
                    if (ImGui::CollapsingHeader("Transform matrix"))
                    {
                        ImGui::Text("Rotation:");
                        ImGui::Text("    "); ImGui::SameLine(); 
                        ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_rotation.rvec.GetDataString(false, false).c_str());
                        ImGui::Text("    "); ImGui::SameLine(); 
                        ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_rotation.uvec.GetDataString(false, false).c_str());
                        ImGui::Text("    "); ImGui::SameLine(); 
                        ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_rotation.fvec.GetDataString(false, false).c_str());
                        ImGui::Text("Translation:");
                        ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_translation.GetDataString(false, false).c_str());
                    }

                    ImGui::Text("Use relative transform:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->AttachInfo->use_relative_transform).c_str());
                    ImGui::Text("Update physics:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->AttachInfo->update_physics).c_str());
                    ImGui::Text("Updated:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->AttachInfo->updated).c_str());
                }
                else
                {
                    ImGui::Text("\tAttach info is a null pointer. Cannot view");
                }
                ImGui::TreePop();
            }

            ImGui::Text("HavokHandle:"); ImGui::SameLine();
            ImGui::Text(std::to_string(TargetObject->HavokHandle).c_str());

            const std::string ContactInfoStatus = TargetObject->ContactInfo.m_contact_list ? " (Valid)" : " (nullptr)";
            if (ImGui::TreeNode(std::string(std::string("ContactInfo") + ContactInfoStatus).c_str()))
            {
                if (TargetObject->ContactInfo.m_contact_list != nullptr)
                {
                    ImGui::Text("Contact node:##Player.Object.ContactInfo");
                    ImGui::Text("Contacted objects:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ContactInfo.m_contact_list->m_contacted_object).c_str());
                    ImGui::Text("Number of contacts:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ContactInfo.m_contact_list->m_num_contacts).c_str());
                    //Todo: Iterate through linked list, give the user control over how far to do so. Note that it is a linked list to the user.
                    //prev
                    //next
                }
                else
                {
                    ImGui::Text("\tContact info is a null pointer. Cannot view.");
                }
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Object flags"))
            {
                ImGui::Text("FlaggedListState:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.flagged_list_state).c_str());
                ImGui::Text("LightingSetOnce:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.lighting_set_once).c_str());
                ImGui::Text("Destroyed:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.destroyed).c_str());
                ImGui::Text("NoSave:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.no_save).c_str());
                ImGui::Text("ForceFullSave:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.force_full_save).c_str());
                ImGui::Text("DestroyOnStream:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.destroy_on_stream).c_str());
                ImGui::Text("CreatedByMissionOrActivity:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.created_by_mission_or_activity).c_str());
                ImGui::Text("DontTransform:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.dont_transform).c_str());
                ImGui::Text("WorldFree:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.world_free).c_str());
                ImGui::Text("Streaming:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.streaming).c_str());
                ImGui::Text("Streamed:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.streamed).c_str());
                ImGui::Text("Persistent:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.persistent).c_str());
                ImGui::Text("Original:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.original).c_str());
                ImGui::Text("Stub:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.stub).c_str());
                ImGui::Text("PreserveHandle:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.preserve_handle).c_str());
                ImGui::Text("BpoIndex:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.bpo_index).c_str());
                ImGui::Text("IsDependent:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.is_dependent).c_str());
                ImGui::Text("Visited:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.visited).c_str());
                ImGui::Text("SpecialLifetime:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.special_lifetime).c_str());
                ImGui::Text("SerializeProtected:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.serialize_protected).c_str());
                ImGui::Text("DontUseMe:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags._dont_use_me).c_str());
                ImGui::Text("StreamingFixed:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.streaming_fixed).c_str());
                ImGui::Text("RenderFlags:"); ImGui::SameLine();
                ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->ObjFlags.render_flags).c_str());
                ImGui::TreePop();
            }
            //RemoteObjFlags //Currently not bound to lua or displayed here since it seems to be for MP
            //MPDcmoIndex
            ImGui::Text("CheckingReset:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->CheckingReset).c_str());
            ImGui::Text("NameIndex:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->NameIndex).c_str());
            ImGui::Text("FlaggedNext address:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->FlaggedNext ? std::to_string((DWORD)TargetObject->FlaggedNext).c_str() : "nullptr");
            ImGui::Text("FlaggedPrevious address:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->FlaggedPrevious ? std::to_string((DWORD)TargetObject->FlaggedPrevious).c_str() : "nullptr");
            ImGui::Text("Handle:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->Handle).c_str());
            ImGui::Text("Parent Handle:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->Parent).c_str());

            const std::string BpoHandleStatus = TargetObject->BPOHandle ? " (Valid)" : " (nullptr)";
            if (ImGui::TreeNode(std::string(std::string("BpoHandle") + BpoHandleStatus).c_str()))
            {
                if (TargetObject->BPOHandle != nullptr)
                {
                    ImGui::Text("Flags:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->flags).c_str());
                    ImGui::Text("State:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->state).c_str());
                    ImGui::Text("BPO Index:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->bpo_index).c_str());
                    ImGui::Text("State Index:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->state_index).c_str());
                    ImGui::Text("Owner:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->owner).c_str());
                    ImGui::Text("Next:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->next).c_str());
                    ImGui::Text("Previous:"); ImGui::SameLine();
                    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->BPOHandle->prev).c_str());
                    //void* user_data
                }
                else
                {
                    ImGui::Text("\tBpoHandle is a null pointer. Cannot view.");
                }
                ImGui::TreePop();
            }

            ImGui::Text("AllIndex:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::to_string(TargetObject->AllIndex) + " (Index of this object in rfg.ActiveWorld.AllObjects)").c_str());
            ImGui::Text("TypeIndex:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->TypeIndex).c_str());
            ImGui::Text("SubtypeIndex:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->SubtypeIndex).c_str());
            ImGui::Text("ObjectType:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::to_string(TargetObject->ObjectType) + " (" + GetObjectTypeString(TargetObject->ObjectType) + ")").c_str());
            ImGui::Text("Subtype:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::to_string(TargetObject->SubType) + " (" + GetObjectSubTypeString(TargetObject->SubType) + ")").c_str());
            ImGui::Text("LastKnownBMin:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->LastKnownBMin.GetDataString(false, false).c_str());
            ImGui::Text("LastKnownBMax:"); ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->LastKnownBMax.GetDataString(false, false).c_str());
            ImGui::Text("SRID:");ImGui::SameLine();
            ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(TargetObject->SRID).c_str());

        }
        else
        {
            ImGui::SetNextItemWidth(300.0f);
            ImGui::TextWrapped("Invalid target object. Please lock a target object with numpad 4 or search for a targer to see it's information.");
        }
    }
    else
    {
        ImGui::SetNextItemWidth(300.0f);
        ImGui::TextWrapped("Invalid world pointer. Please load a save if you haven't already. If you've loaded a game and you see this, please report this to the RSL maintainer.");
    }

	ImGui::End();
}

std::string IntrospectionGui::GetObjectTypeString(char ObjectType)
{
    switch(ObjectType)
    {
    case 0:
        return "Human";
    case 1:
        return "Item";
    case 2:
        return "Mover";
    case 3:
        return "Vehicle";
    case 4:
        return "Effect";
    case 5:
        return "Debris";
    case 6:
        return "Turret";
    case 7:
        return "Light";
    case 8:
        return "PlayerStart";
    case 9:
        return "CoverNode";
    case 10:
        return "NavPoint";
    case 11:
        return "Squad";
    case 12:
        return "Convoy";
    case 13:
        return "ConvoyEnd";
    case 14:
        return "Patrol";
    case 15:
        return "GuardNode";
    case 16:
        return "Skybox";
    case 17:
        return "Ladder";
    case 18:
        return "Constraint";
    case 19:
        return "Zone";
    case 20:
        return "TriggerRegion";
    case 21:
        return "MarauderAmbushRegion";
    case 22:
        return "RestrictedArea";
    case 23:
        return "SpawnRegion";
    case 24:
        return "AmbientSpawnRegion";
    case 25:
        return "VehicleSpawnNode";
    case 26:
        return "NpcSpawnNode";
    case 27:
        return "TurretSpawnNode";
    case 28:
        return "ActionNode";
    case 29:
        return "SquadSpawnNode";
    case 30:
        return "RoadblockNode";
    case 31:
        return "ShapeCutter";
    case 32:
        return "District";
    case 33:
        return "MultiMarker";
    case 34:
        return "PathRoad";
    case 35:
        return "LightParams";
    case 36:
        return "Dummy";
    case 37:
        return "ActivitySpawn";
    case 38:
        return "RaidNode";
    case 39:
        return "Subzone";
    case 40:
        return "HouseArrestNode";
    case 41:
        return "DemolitionsMasterNode";
    case 42:
        return "RidingShotgunNode";
    case 43:
        return "DeliveryNode";
    case 44:
        return "BoundingBox";
    case 45:
        return "MissionStartNode";
    case 46:
        return "Courier";
    case 47:
        return "CourierEnd";
    case 48:
        return "Safehouse";
    case 49:
        return "BftpNode";
    case 50:
        return "AirstrikeDefenseNode";
    case 51:
        return "UpgradeNode";
    case 52:
        return "AreaDefenseNode";
    case 4294967295:
        return "Undefined";
    default:
        return "Invalid object type";
    }
}

std::string IntrospectionGui::GetObjectSubTypeString(char ObjectSubType)
{
    switch (ObjectSubType)
    {
    case 4294967295:
        return "Undefined";
    case 0:
        return "MoverGeneral";
    case 1:
        return "MoverRfg";
    case 2:
        return "HumanNpc";
    case 3:
        return "HumanPlayer";
    case 4:
        return "VehicleAuto";
    case 5:
        return "VehicleFlyer";
    case 6:
        return "VehicleWalker";
    case 7:
        return "ItemWeapon";
    case 8:
        return "ItemProjectile";
    case 9:
        return "ItemMultiFlag";
    case 10:
        return "ItemMultiBackpack";
    case 11:
        return "NumObjectSubTypes (You probably shouldn't be seeing this...)";
    default:
        return "Invalid object subtype";
    }
}
