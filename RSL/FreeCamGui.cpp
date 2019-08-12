#include "FreeCamGui.h"
#include "CameraWrapper.h"

void FreeCamGui::Draw()
{
	if (!Visible)
	{
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), &Visible))
	{
		ImGui::End();
		return;
	}
	if (!Globals::Camera)
	{
		ImGui::Text(u8"Camera pointer not set. What do? " + std::string(ICON_FA_FROWN_OPEN));
		ImGui::End();
		return;
	}

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("General camera settings:");
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Far clip distance", &Globals::Camera->GameData->m_far_clip_dist, 3);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("High LOD far clip distance", &Globals::Camera->GameData->m_high_lod_far_clip_dist, 3);


    ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Free cam settings:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Toggle free cam"))
	{
        Globals::Camera->ToggleFreeCamera();
	}
	ImGui::Checkbox("Return player to original position?", &ReturnPlayerToOriginalPosition);
	ImGui::SameLine();
	Util::Gui::ShowHelpMarker("If this is on the player will be teleported back to their original position after the free cam is disabled. If it's off then the player will be dropped wherever the free cam deactivates. So be careful.");
    ImGui::Checkbox("Use wasd movement", &Globals::Camera->FreeCamUseWasdMovement);
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("If unchecked, uses arrow keys for movement");

    ImGui::InputFloat("Max speed", &Globals::Camera->MaxSpeed, 0.1, 5.0, 3);
	if (Globals::Camera->SmoothCamera)
	{
		ImGui::InputFloat("Acceleration rate", &Globals::Camera->AccelerationRate, 0.1, 5.0, 3);
		ImGui::InputFloat("Deceleration rate", &Globals::Camera->DecelerationRate, 0.1, 5.0, 3);

		ImGui::Text("Current velocity: ");
		ImGui::SameLine();
		ImGui::TextColored(Globals::SecondaryTextColor, Globals::Camera->Velocity.GetDataString(true, true).c_str());
	}


	ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("First person camera settings [Experimental]:");
	ImGui::PopFont();
	ImGui::Separator();

	if(ImGui::Button("Toggle first person camera"))
	{
        Globals::Camera->ToggleFirstPersonCamera();
	}
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat3("Camera offset", (float*)&Globals::Camera->FirstPersonCameraOffset, 3);
	ImGui::Checkbox("Use direction offset", &Globals::Camera->UseFirstPersonDirectionOffset);
	ImGui::InputFloat("Direction offset multiplier", &Globals::Camera->FirstPersonDirectionOffsetMultiplier, 3);

	ImGui::Checkbox("Use auto player direction", &Globals::Camera->UseFirstPersonAutoPlayerDirection);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Min angle difference for autorotation (degrees)", &Globals::Camera->MinAngleDifferenceForRotation);
    ImGui::Checkbox("Use third person view for vehicles", &Globals::Camera->UseThirdPersonForVehicles);


	ImGui::End();
}
