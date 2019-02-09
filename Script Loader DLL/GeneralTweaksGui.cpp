#include "GeneralTweaksGui.h"

GeneralTweaksGui::GeneralTweaksGui()
{

}

GeneralTweaksGui::~GeneralTweaksGui()
{

}

void GeneralTweaksGui::Initialize(bool* _OpenState)
{
	OpenState = _OpenState;
}

void GeneralTweaksGui::Draw(const char* Title)
{
	if (!*OpenState)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title, OpenState))
	{
		ImGui::End();
		return;
	}

	/*if (ImGui::Button("Test Tooltips 1"))
	{
		UiToolTipsAddTip("Salvage", 200, 0);
	}*/

	ImGui::Text("Xray Effect Mode: ");
	ImGui::SameLine(); ImGui::RadioButton("Backpack", &XrayEffectMode, 0);
	ImGui::SameLine(); ImGui::RadioButton("Rail Driver", &XrayEffectMode, 1);
	ImGui::Text("Selected mode value: "); ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string(XrayEffectMode).c_str());
	if (ImGui::Button("Toggle Selected Xray Mode"))
	{
		if (XrayEffectMode == 0)
		{
			if (XrayModeOn)
			{
				xray_effect_stop(XET_VISION_BACKPACK);
				XrayModeOn = false;
			}
			else
			{
				xray_effect_start(XET_VISION_BACKPACK);
				XrayModeOn = true;
			}
		}
		else if (XrayEffectMode == 1)
		{
			if (XrayModeOn)
			{
				xray_effect_stop(XET_RAIL_DRIVER);
				XrayModeOn = false;
			}
			else
			{
				xray_effect_start(XET_RAIL_DRIVER);
				XrayModeOn = true;
			}
		}
	}

	ImGui::Text("Code driven jump height:"); ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CodeDrivenJumpHeight).c_str());
	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Custom code driven jump height", &CustomJumpHeight, 0.5, 2.0, 3); ImGui::SameLine();
	ImGui::Checkbox("Active", &NeedCustomJumpHeightSet);
	ImGui::Checkbox("Infinite jetpack", &InfiniteJetpack);
	//ImGui::Checkbox("Invulnerability", (bool*)(PlayerPtr->Flags.invulnerable));
	ImGui::Checkbox("Invulnerability", &Invulnerable);
	if (!Invulnerable)
	{
		PlayerPtr->Flags.invulnerable = false;
	}
	ImGui::Text("Player move speed:"); ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MoveSpeed).c_str());
	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Player move speed", &CustomPlayerMoveSpeed, 1.0f, 5.0f, 3);
	ImGui::Text("Player max speed:"); ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MaxSpeed).c_str());
	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Player max speed", &CustomPlayerMaxSpeed, 1.0f, 5.0f, 3);
	ImGui::PushItemWidth(232.0f);
	ImGui::Text("Player velocity:"); ImGui::SameLine();
	ImGui::InputFloat3("##Player velocity: ", (float*)&PlayerPtr->Velocity); ImGui::SameLine();
	//ImGui::InputFloat("Player cash", &PlayerPtr->Cash, 10.0f, 50.0f, 3);
	//ImGui::InputFloat("Player hit points", &PlayerPtr->HitPoints, 10.0f, 100.0f, 3);
	//ImGui::InputInt("Player max hit points", &PlayerPtr->MaxHitPoints);
	//ImGui::InputInt("Player initial max hit points", &PlayerPtr->InitialMaxHitPoints);
	//ImGui::PushItemWidth(232.0f);
	//ImGui::InputFloat3("Player look at position", (float*)&PlayerPtr->LookAtPos, 3);
	ImGui::InputFloat3("Player aim position", (float*)&PlayerPtr->aim_pos, 3);
	ImGui::InputScalar("Player aim target", ImGuiDataType_U32, &PlayerPtr->aim_target);
	ImGui::InputScalar("Player aim target duration", ImGuiDataType_U32, &PlayerPtr->aim_target_duration);
	ImGui::InputFloat3("Player penetrating aim pos", (float*)&PlayerPtr->penetrating_aim_pos, 3);
	ImGui::InputScalar("Player penetrating aim target", ImGuiDataType_U32, &PlayerPtr->penetrating_aim_target);
	//ImGui::Text("Player frametime multiplier: ");
	//ImGui::SameLine();
	//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->FrametimeMultiplier).c_str());
	//ImGui::InputFloat("Target player frametime multiplier", &PlayerPtr->FrametimeMultiplier);

	ImGui::End();
}