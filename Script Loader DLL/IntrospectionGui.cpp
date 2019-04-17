#include "IntrospectionGui.h"

IntrospectionGui::IntrospectionGui(bool* _OpenState, std::string _Title)
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

IntrospectionGui::~IntrospectionGui()
{

}

void IntrospectionGui::Draw()
{
	DrawPlayerIntrospectionGui(Title.c_str()); //DrawPlayerIntrospectionGui("Player Introspection Menu");
}

void IntrospectionGui::DrawPlayerIntrospectionGui(const char * Title)
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

	ImGui::PushFont(FontBig);
	ImGui::Text("Player variables (WIP): ");
	ImGui::PopFont();
	ImGui::Separator();

	ImGui::PushStyleColor(ImGuiCol_Text, ColorRed);
	ImGui::PushItemWidth(230.0f);
	ImGui::Text("Note: This menu is some of the oldest code in the script loader, and as such hasn't been worked on in a while. I've left it in case it's useful to someone but won't likely make anything like this that's fully working until GUIs can be coded with lua. Will make it much quicker and easier.");
	ImGui::PopStyleColor();
	ImGui::Separator();
		
	if (PlayerPtr != nullptr)
	{
		if (ImGui::TreeNode("Useful info"))
		{
			ImGui::PushItemWidth(230.0f);
			ImGui::TextWrapped("Some select values that are important. Most of them can't be edited here since the game will fight you to keep the correct value. Need to force them every frame sometimes.");
			ImGui::PushItemWidth(230.0f);
			ImGui::Text("Player velocity magnitude:"); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Velocity.Magnitude()).c_str());
			ImGui::InputFloat3("Player velocity: ", (float*)&PlayerPtr->Velocity);

			ImGui::InputFloat3("Player aim position", (float*)&PlayerPtr->aim_pos, 3);
			ImGui::InputScalar("Player aim target", ImGuiDataType_U32, &PlayerPtr->aim_target);
			ImGui::InputScalar("Player aim target duration", ImGuiDataType_U32, &PlayerPtr->aim_target_duration);
			ImGui::InputFloat3("Player penetrating aim pos", (float*)&PlayerPtr->penetrating_aim_pos, 3);
			ImGui::InputScalar("Player penetrating aim target", ImGuiDataType_U32, &PlayerPtr->penetrating_aim_target);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Object values"))
		{
			//ImGui::Text("Object values");
			//ImGui::Separator();

			//Vftptr

			ImGui::Text("Position vector: "); ImGui::SameLine();
			std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
			ImGui::TextColored(SecondaryTextColor, PlayerPositionString.c_str());

			if (ImGui::TreeNode("Orientation matrix"))
			{
				std::string RightVectorString("(" + std::to_string(PlayerPtr->Orientation.rvec.x) + ", " + std::to_string(PlayerPtr->Orientation.rvec.y) + ", " + std::to_string(PlayerPtr->Orientation.rvec.z) + ")");
				std::string UpVectorString("(" + std::to_string(PlayerPtr->Orientation.uvec.x) + ", " + std::to_string(PlayerPtr->Orientation.uvec.y) + ", " + std::to_string(PlayerPtr->Orientation.uvec.z) + ")");
				std::string DirectionVectorString("(" + std::to_string(PlayerPtr->Orientation.fvec.x) + ", " + std::to_string(PlayerPtr->Orientation.fvec.y) + ", " + std::to_string(PlayerPtr->Orientation.fvec.z) + ")");
				//ImGui::Text("Orientation Matrix:");
				ImGui::Text("Right vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RightVectorString.c_str());
				ImGui::Text("Up vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, UpVectorString.c_str());
				ImGui::Text("Direction vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, DirectionVectorString.c_str());

				ImGui::TreePop();
			}

			//ChildPtr
			//ChildNext
			//ChildPrevious
			//ChildConstraintPtr
			//HostConstraintPtr
			if (ImGui::TreeNode("Attach info"))
			{
				if (PlayerPtr->AttachInfo != nullptr)
				{
					ImGui::Text("Parent handle: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->parent_handle).c_str());
					ImGui::Text("Parent prop point: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->parent_prop_point).c_str());
					ImGui::Text("Child prop point: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->child_prop_point).c_str());
					if (ImGui::CollapsingHeader("Transform matrix"))
					{
						std::string RotationRow1("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.z) + ")");
						std::string RotationRow2("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.z) + ")");
						std::string RotationRow3("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.z) + ")");
						ImGui::Text("Rotation:");
						ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow1.c_str());
						ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow2.c_str());
						ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow3.c_str());
						ImGui::Text("Translation:");
						std::string TranslationString("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.x) + ", "
							+ std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.y) + ", "
							+ std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.z) + ")");
						ImGui::TextColored(SecondaryTextColor, TranslationString.c_str());
					}

					ImGui::Text("Use relative transform: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->use_relative_transform).c_str());
					ImGui::Text("Update physics: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->update_physics).c_str());
					ImGui::Text("Updated: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->updated).c_str());
				}
				else
				{
					ImGui::Text("\tAttach info is a null pointer. Cannot view");
				}
				ImGui::TreePop();
			}

			ImGui::Text("Havok handle: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->HavokHandle).c_str());

			if (ImGui::TreeNode("Contact info"))
			{
				if (PlayerPtr->ContactInfo.m_contact_list != nullptr)
				{
					ImGui::Text("Contact node: ##Player.Object.ContactInfo");
					ImGui::Text("Contacted objects: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ContactInfo.m_contact_list->m_contacted_object).c_str());
					ImGui::Text("Number of contacts: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ContactInfo.m_contact_list->m_num_contacts).c_str());
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
				ImGui::Text("Flagged list state: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.flagged_list_state).c_str());
				ImGui::Text("Lighting set once: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.lighting_set_once).c_str());
				ImGui::Text("Destroyed: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.destroyed).c_str());
				ImGui::Text("No save: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.no_save).c_str());
				ImGui::Text("Force full save: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.force_full_save).c_str());
				ImGui::Text("Destroy on stream: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.destroy_on_stream).c_str());
				ImGui::Text("Created by mission or activity: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.created_by_mission_or_activity).c_str());
				ImGui::Text("Don't transform: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.dont_transform).c_str());
				ImGui::Text("World free: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.world_free).c_str());
				ImGui::Text("Streaming: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.streaming).c_str());
				ImGui::Text("Streamed: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.streamed).c_str());
				ImGui::Text("Persistent: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.persistent).c_str());
				ImGui::Text("Original: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.original).c_str());
				ImGui::Text("Stub: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.stub).c_str());
				ImGui::Text("Preserve handle: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.preserve_handle).c_str());
				ImGui::Text("BPO index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.bpo_index).c_str());
				ImGui::Text("Is dependent: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.is_dependent).c_str());
				ImGui::Text("Visited: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.visited).c_str());
				ImGui::Text("Special lifetime: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.special_lifetime).c_str());
				ImGui::Text("Serialize protected: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.serialize_protected).c_str());
				ImGui::Text("Dont use me: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags._dont_use_me).c_str());
				ImGui::Text("Streaming fixed: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.streaming_fixed).c_str());
				ImGui::Text("Render flags: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjFlags.render_flags).c_str());
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Remote object flags"))
			{
				ImGui::Text("Remote object: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjFlags.remote_object).c_str());
				ImGui::Text("Client sync: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjFlags.client_sync).c_str());
				ImGui::Text("Client destroy permission: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjFlags.client_destroy_permission).c_str());
				ImGui::Text("No destroy packet: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjFlags.no_destroy_packet).c_str());
				ImGui::Text("Common create: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjFlags.common_create).c_str());
				ImGui::TreePop();
			}

			ImGui::Text("MP dcmo index: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MPDcmoIndex).c_str());
			ImGui::Text("Checking reset: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CheckingReset).c_str());
			ImGui::Text("Name index: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->NameIndex).c_str());

			//Todo: Eventually have linked list traversal, or object menu. Try adding names to menu as well if possible.
			//FlaggedNext
			//FlaggedPrevious

			ImGui::Text("Handle: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Handle).c_str());
			ImGui::Text("Parent: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Parent).c_str());

			if (ImGui::TreeNode("Havok BPO"))
			{
				if (PlayerPtr->BPOHandle != nullptr)
				{
					ImGui::Text("Flags: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->flags).c_str());
					ImGui::Text("State: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->state).c_str());
					ImGui::Text("BPO Index: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->bpo_index).c_str());
					ImGui::Text("State Index: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->state_index).c_str());
					ImGui::Text("Owner: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->owner).c_str());
					ImGui::Text("Next: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->next).c_str());
					ImGui::Text("Previous: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->prev).c_str());
					//user_data
				}
				else
				{
					ImGui::Text("\tHavok BPO is a null pointer. Cannot view");
				}
				ImGui::TreePop();
			}

			ImGui::Text("All index: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AllIndex).c_str());
			ImGui::Text("Type index: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->TypeIndex).c_str());
			ImGui::Text("Subtype index: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SubtypeIndex).c_str());
			ImGui::Text("Object type: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectType).c_str());
			ImGui::Text("Subtype: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SubType).c_str());

			ImGui::Text("Last known bmin: "); ImGui::SameLine();
			std::string LastKnownBminString("(" + std::to_string(PlayerPtr->LastKnownBMin.x) + ", " + std::to_string(PlayerPtr->LastKnownBMin.y) + ", " + std::to_string(PlayerPtr->LastKnownBMin.z) + ")");
			ImGui::TextColored(SecondaryTextColor, LastKnownBminString.c_str());

			ImGui::Text("Last known bmax: "); ImGui::SameLine();
			std::string LastKnownBmaxString("(" + std::to_string(PlayerPtr->LastKnownBMax.x) + ", " + std::to_string(PlayerPtr->LastKnownBMax.y) + ", " + std::to_string(PlayerPtr->LastKnownBMax.z) + ")");
			ImGui::TextColored(SecondaryTextColor, LastKnownBmaxString.c_str());

			ImGui::Text("SRID: "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SRID).c_str());

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Human values"))
		{
			//ImGui::Separator();
			//ImGui::Text("Human values");

			/*if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//Info

			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector
			//vector
			//vector

			if (ImGui::CollapsingHeader(""))
			{

			}

			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			if (ImGui::CollapsingHeader(""))
			{

			}

			//vector
			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector

			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine(); //Timestamp
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			if (ImGui::CollapsingHeader(""))
			{
				//check nullptr
			}

			//ClothSim

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine(); //Timestamp
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			//vector

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

			if (ImGui::CollapsingHeader(""))
			{
				//Check nullptr
			}
			if (ImGui::CollapsingHeader(""))
			{

			}
			if (ImGui::CollapsingHeader(""))
			{

			}

			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine(); //Timestamp
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			ImGui::Text(": "); ImGui::SameLine(); //Timestamp
			ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
			//Previous value is Timestamp TurretHoldAnimations. Still several dozen values left.*/
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Player values"))
		{
			//ImGui::Separator();
			//ImGui::Text("Player values");
			ImGui::TreePop();
		}
	}
	else
	{
		ImGui::Text("Player pointer is null. Cannot view");
	}
	ImGui::End();
}
