#include "IntrospectionGui.h"
#include "LuaFunctions.h"

void IntrospectionGui::Draw()
{
	DrawPlayerIntrospectionGui(Title.c_str()); //DrawPlayerIntrospectionGui("Player Introspection Menu");
}

void IntrospectionGui::DrawPlayerIntrospectionGui(const char* Title)
{
	if (!Visible)
        return;

    ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title, &Visible))
	{
		ImGui::End();
		return;
	}

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Object introspection");
	ImGui::PopFont();
	ImGui::Separator();
    
    ImGui::SetNextItemWidth(300.0f);
    ImGui::TextWrapped("Aim at an object and press numpad 4 to view it's info in this menu. Alternatively, \
search for an object using one of the following criteria. You can only search by one criteria at a time.");
    ImGui::Separator();

    static std::string NameSearchBuffer;
    ImGui::Text("Search by name:"); ImGui::SameLine();
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputText("##ObjectNameSearchInput", &NameSearchBuffer); ImGui::SameLine();
    if(ImGui::Button("Search##ObjectNameSearchButton"))
    {
        Object* NewObject = Lua::GetObjectByName(NameSearchBuffer);
        if(NewObject)
            SavedTargetObjectHandle = NewObject->Handle;
    }

    static uint HandleSearchBuffer = 0;
    ImGui::Text("Search by handle (unsigned):"); ImGui::SameLine();
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputScalar("##ObjectHandleSearchInput", ImGuiDataType_U32, &HandleSearchBuffer); ImGui::SameLine(); //Todo: Need to update imgui to get stuff like ImGui::InputUint
    if (ImGui::Button("Search##ObjectHandleSearchButton"))
    {
        if(rfg::WorldObjectFromHandle(Globals::RfgWorldPtr, NULL, HandleSearchBuffer))
            SavedTargetObjectHandle = HandleSearchBuffer;
    }
    
    static uint IndexSearchBuffer = 0;
    ImGui::Text("Search by index (unsigned):"); ImGui::SameLine();
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputScalar("##ObjectIndexSearchInput", ImGuiDataType_U32, &IndexSearchBuffer); ImGui::SameLine(); //Todo: Need to update imgui to get stuff like ImGui::InputUint
    if (ImGui::Button("Search##ObjectIndexSearchButton"))
    {
        if(Globals::RfgWorldPtr && IndexSearchBuffer < Globals::RfgWorldPtr->all_objects.Size())
            SavedTargetObjectHandle = Globals::RfgWorldPtr->all_objects[IndexSearchBuffer]->Handle;
    }

    ImGui::Separator();
    ImGui::Text("Saved target object handle:");
    ImGui::SameLine();
    ImGui::Text(std::to_string(SavedTargetObjectHandle).c_str());
    if(!Globals::RfgWorldPtr)
    {
        ImGui::SetNextItemWidth(300.0f);
        ImGui::TextWrapped("Invalid world pointer. Please load a save if you haven't already. If you've loaded a game and you see this, please report this to the RSL maintainer.");
        ImGui::End();
        return;
    }

    Object* TargetObject = rfg::WorldObjectFromHandle(Globals::RfgWorldPtr, NULL, SavedTargetObjectHandle);
    if(!TargetObject)
    {
        ImGui::SetNextItemWidth(300.0f);
        ImGui::TextWrapped("Invalid target object. Please lock a target object with numpad 4 or search for a targer to see it's information.");
        ImGui::End();
        return;
    }

    Gui::LabelAndValue("Name:", rfg::WorldGetObjectName(Globals::RfgWorldPtr, nullptr, TargetObject));
    Gui::LabelAndValue("Position:", TargetObject->Position.GetDataString(false, false));
    if (ImGui::TreeNode("Orientation matrix"))
    {
        Gui::LabelAndValue("Right vector:", TargetObject->Orientation.rvec.GetDataString(false, false));
        Gui::LabelAndValue("Up vector:", TargetObject->Orientation.uvec.GetDataString(false, false));
        Gui::LabelAndValue("Forward vector:", TargetObject->Orientation.fvec.GetDataString(false, false));
        ImGui::TreePop();
    }

    Gui::LabelAndValue("ChildPtr*", TargetObject->ChildPtr ? std::to_string((DWORD)TargetObject->ChildPtr) : "nullptr");
    Gui::LabelAndValue("ChildNext*", TargetObject->ChildNext ? std::to_string((DWORD)TargetObject->ChildNext) : "nullptr");
    Gui::LabelAndValue("ChildPrevious*", TargetObject->ChildPrevious ? std::to_string((DWORD)TargetObject->ChildPrevious) : "nullptr");
    //ChildConstraintPtr
    //HostConstraintPtr
    const std::string AttachInfoStatus = TargetObject->AttachInfo ? " (Valid)" : " (nullptr)";
    if (ImGui::TreeNode(fmt::format("AttachInfo{}", AttachInfoStatus).c_str()))
    {
        if (TargetObject->AttachInfo != nullptr)
        {
            Gui::LabelAndValue("Parent handle", std::to_string(TargetObject->AttachInfo->parent_handle));
            Gui::LabelAndValue("Parent prop point", std::to_string(TargetObject->AttachInfo->parent_prop_point));
            Gui::LabelAndValue("Child prop point", std::to_string(TargetObject->AttachInfo->child_prop_point));

            if (ImGui::CollapsingHeader("Transform matrix"))
            {
                ImGui::Text("Rotation:");
                ImGui::Text("    "); ImGui::SameLine(); 
                ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_rotation.rvec.GetDataString(false, false).c_str());
                ImGui::Text("    "); ImGui::SameLine(); 
                ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_rotation.uvec.GetDataString(false, false).c_str());
                ImGui::Text("    "); ImGui::SameLine(); 
                ImGui::TextColored(Globals::SecondaryTextColor, TargetObject->AttachInfo->relative_transform.m_rotation.fvec.GetDataString(false, false).c_str());
                Gui::LabelAndValue("Translation:", TargetObject->AttachInfo->relative_transform.m_translation.GetDataString(false, false));
            }

            Gui::LabelAndValue("Use relative transform:", std::to_string(TargetObject->AttachInfo->use_relative_transform));
            Gui::LabelAndValue("Update physics:", std::to_string(TargetObject->AttachInfo->update_physics));
            Gui::LabelAndValue("Updated:", std::to_string(TargetObject->AttachInfo->updated));
        }
        else
            ImGui::Text("\tAttach info is a null pointer. Cannot view");

        ImGui::TreePop();
    }

    Gui::LabelAndValue("Havok handle:", std::to_string(TargetObject->HavokHandle));
    const std::string ContactInfoStatus = TargetObject->ContactInfo.m_contact_list ? " (Valid)" : " (nullptr)";
    if (ImGui::TreeNode(fmt::format("Contact info{}", ContactInfoStatus).c_str()))
    {
        if (TargetObject->ContactInfo.m_contact_list != nullptr)
        {
            ImGui::Text("Contact node:");
            Gui::LabelAndValue("Contacted objects", std::to_string(TargetObject->ContactInfo.m_contact_list->m_contacted_object));
            Gui::LabelAndValue("Number of contacts:", std::to_string(TargetObject->ContactInfo.m_contact_list->m_num_contacts));
            //Todo: Iterate through linked list, give the user control over how far to do so. Note that it is a linked list to the user.
            //prev
            //next
        }
        else
            ImGui::Text("\tContact info is a null pointer. Cannot view.");

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Object flags"))
    {
        Gui::LabelAndValue("FlaggedListState:", std::to_string(TargetObject->ObjFlags.flagged_list_state));
        Gui::LabelAndValue("LightingSetOnce:", std::to_string(TargetObject->ObjFlags.lighting_set_once));
        Gui::LabelAndValue("Destroyed:", std::to_string(TargetObject->ObjFlags.destroyed));
        Gui::LabelAndValue("NoSave:", std::to_string(TargetObject->ObjFlags.no_save));
        Gui::LabelAndValue("ForceFullSave:", std::to_string(TargetObject->ObjFlags.force_full_save));
        Gui::LabelAndValue("DestroyOnStream:", std::to_string(TargetObject->ObjFlags.destroy_on_stream));
        Gui::LabelAndValue("CreatedByMissionOrActivity:", std::to_string(TargetObject->ObjFlags.created_by_mission_or_activity));
        Gui::LabelAndValue("DontTransform:", std::to_string(TargetObject->ObjFlags.dont_transform));
        Gui::LabelAndValue("WorldFree:", std::to_string(TargetObject->ObjFlags.world_free));
        Gui::LabelAndValue("Streaming:", std::to_string(TargetObject->ObjFlags.streaming));
        Gui::LabelAndValue("Streamed:", std::to_string(TargetObject->ObjFlags.streamed));
        Gui::LabelAndValue("Persistent:", std::to_string(TargetObject->ObjFlags.persistent));
        Gui::LabelAndValue("Original:", std::to_string(TargetObject->ObjFlags.original));
        Gui::LabelAndValue("Stub:", std::to_string(TargetObject->ObjFlags.stub));
        Gui::LabelAndValue("PreserveHandle:", std::to_string(TargetObject->ObjFlags.preserve_handle));
        Gui::LabelAndValue("BpoIndex:", std::to_string(TargetObject->ObjFlags.bpo_index));
        Gui::LabelAndValue("IsDependent:", std::to_string(TargetObject->ObjFlags.is_dependent));
        Gui::LabelAndValue("Visited:", std::to_string(TargetObject->ObjFlags.visited));
        Gui::LabelAndValue("SpecialLifetime:", std::to_string(TargetObject->ObjFlags.special_lifetime));
        Gui::LabelAndValue("SerializeProtected:", std::to_string(TargetObject->ObjFlags.serialize_protected));
        Gui::LabelAndValue("DontUseMe:", std::to_string(TargetObject->ObjFlags._dont_use_me));
        Gui::LabelAndValue("StreamingFixed:", std::to_string(TargetObject->ObjFlags.streaming_fixed));
        Gui::LabelAndValue("RenderFlags:", std::to_string(TargetObject->ObjFlags.render_flags));
        ImGui::TreePop();
    }
    //RemoteObjFlags //Currently not bound to lua or displayed here since it seems to be for MP
    //MPDcmoIndex
    
    Gui::LabelAndValue("Checking reset:", std::to_string(TargetObject->CheckingReset));
    Gui::LabelAndValue("Name index:", std::to_string(TargetObject->NameIndex));
    Gui::LabelAndValue("FlaggedNext*", TargetObject->FlaggedNext ? std::to_string((DWORD)TargetObject->FlaggedNext) : "nullptr");
    Gui::LabelAndValue("FlaggedPrevious*", TargetObject->FlaggedPrevious ? std::to_string((DWORD)TargetObject->FlaggedPrevious) : "nullptr");
    Gui::LabelAndValue("Handle", std::to_string(TargetObject->Handle));
    Gui::LabelAndValue("Parent handle", std::to_string(TargetObject->Parent));
    const std::string BpoHandleStatus = TargetObject->BPOHandle ? " (Valid)" : " (nullptr)";
    if (ImGui::TreeNode(std::string(std::string("BpoHandle") + BpoHandleStatus).c_str()))
    {
        if (TargetObject->BPOHandle != nullptr)
        {
            Gui::LabelAndValue("Flags:", std::to_string(TargetObject->BPOHandle->flags));
            Gui::LabelAndValue("State:", std::to_string(TargetObject->BPOHandle->state));
            Gui::LabelAndValue("BPO index:", std::to_string(TargetObject->BPOHandle->bpo_index));
            Gui::LabelAndValue("State index:", std::to_string(TargetObject->BPOHandle->state_index));
            Gui::LabelAndValue("Owner:", std::to_string(TargetObject->BPOHandle->owner));
            Gui::LabelAndValue("Next", std::to_string(TargetObject->BPOHandle->next));
            Gui::LabelAndValue("Previous", std::to_string(TargetObject->BPOHandle->prev));
            //void* user_data
        }
        else
            ImGui::Text("\tBpoHandle is a null pointer. Cannot view.");

        ImGui::TreePop();
    }

    Gui::LabelAndValue("All index", fmt::format("{} (Index of this object in rfg.ActiveWorld.AllObjects)", std::to_string(TargetObject->AllIndex)));
    Gui::LabelAndValue("Type index", std::to_string(TargetObject->TypeIndex));
    Gui::LabelAndValue("Subtype index", std::to_string(TargetObject->SubtypeIndex));
    Gui::LabelAndValue("Object type", fmt::format("{} ({})", std::to_string(TargetObject->ObjectType), Rfg::GetObjectTypeString(TargetObject->ObjectType)));
    Gui::LabelAndValue("Object subtype", fmt::format("{} ({})", std::to_string(TargetObject->SubType), Rfg::GetObjectSubTypeString(TargetObject->SubType)));
    Gui::LabelAndValue("Last known bmin", TargetObject->LastKnownBMin.GetDataString(false, false));
    Gui::LabelAndValue("Last known bmax", TargetObject->LastKnownBMax.GetDataString(false, false));
    Gui::LabelAndValue("SRID", std::to_string(TargetObject->SRID));
    ImGui::End();
}