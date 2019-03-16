#include "FreeCamGui.h"
#include "CameraWrapper.h"

FreeCamGui::FreeCamGui(bool * _OpenState, std::string _Title)
{
	OpenState = _OpenState;
	Title = _Title;

}

FreeCamGui::~FreeCamGui()
{

}

void FreeCamGui::Draw()
{
	if (!*OpenState)
	{
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), OpenState))
	{
		ImGui::End();
		return;
	}
	if (!Camera)
	{
		ImGui::Text(std::string(std::string(u8"Camera pointer not set. What do? ") + std::string(ICON_FA_FROWN_OPEN)).c_str());
		ImGui::End();
		return;
	}
	
	if (ImGui::Button("Toggle free cam"))
	{
		Camera->ToggleFreeCamera();
	}
	ImGui::InputFloat("Move speed", &Camera->CameraSpeed, 0.1, 5.0, 3);
	ImGui::InputFloat("Real FOV", (float*)Camera->RealFOV, 0.1, 5.0, 3);
	ImGui::InputFloat("Ideal FOV", (float*)Camera->IdealFOV, 0.1, 5.0, 3);

	ImGui::End();
}
