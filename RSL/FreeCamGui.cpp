#include "FreeCamGui.h"

FreeCamGui::FreeCamGui(std::string Title_)
{
    Title = Title_;
    Camera = IocContainer->resolve<ICameraManager>();
}

void FreeCamGui::Draw()
{
	if (!Visible)
        return;

    ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), &Visible))
	{
		ImGui::End();
		return;
	}
	if (!Camera)
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
    ImGui::InputFloat("Far clip distance", Camera->FarClipDistance, 3);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("High LOD far clip distance", Camera->HighLodFarClipDistance, 3);

    ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Free cam settings:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Toggle free cam"))
        Camera->ToggleFreeCamera();

    ImGui::Checkbox("Return player to original position?", &ReturnPlayerToOriginalPosition);
	ImGui::SameLine();
	Util::Gui::ShowHelpMarker("If this is on the player will be teleported back to their original position after the free cam is disabled. If it's off then the player will be dropped wherever the free cam deactivates. So be careful.");
    ImGui::Checkbox("Use wasd movement", &Camera->FreeCamUseWasdMovement);
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("If unchecked, uses arrow keys for movement");

    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Max speed", &Camera->MaxSpeed, 0.1, 5.0, 3);
	ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("First person camera settings [Experimental]:");
	ImGui::PopFont();
	ImGui::Separator();
    if(ImGui::Button("Toggle first person camera"))
        Camera->ToggleFirstPersonCamera();

    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat3("Camera offset", (float*)&Camera->FirstPersonCameraOffset, 3);
    ImGui::Checkbox("Use direction offset", &Camera->UseFirstPersonDirectionOffset);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Direction offset multiplier", &Camera->FirstPersonDirectionOffsetMultiplier, 3);

    ImGui::Checkbox("Use auto player direction", &Camera->UseFirstPersonAutoPlayerDirection);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Min angle difference for autorotation (degrees)", &Camera->MinAngleDifferenceForRotation);
    ImGui::Checkbox("Use third person view for vehicles", &Camera->UseThirdPersonForVehicles);

	ImGui::End();
}
