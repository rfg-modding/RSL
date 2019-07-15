#include "GeneralTweaksGui.h"

GeneralTweaksGui::GeneralTweaksGui(bool* OpenState_, std::string Title_)
{
	OpenState = OpenState_;
	Title = Title_;

	CustomTimeOfDayLightColor.red = 0.0f;
	CustomTimeOfDayLightColor.green = 0.0f;
	CustomTimeOfDayLightColor.blue = 0.0f;
	CustomTimeOfDayLightColor.alpha = 0.0f;

	CustomAlertLevel = ALERT_LEVEL_GREEN;
}

void GeneralTweaksGui::Draw()
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

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("General tweaks:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Toggle Hud"))
	{
		ToggleHud();
	}
	if (ImGui::Button("Toggle Fog"))
	{
		ToggleFog();
	}
	ImGui::Separator();


	//ImGui::Separator();
	
	ImGui::Text("Alert level: ");
	ImGui::SameLine();
	gfm_alert_levels AlertCheck = GsmGetAlertLevel();
	if (AlertCheck == ALERT_LEVEL_GREEN)
	{
		ImGui::TextColored(Globals::ColorGreen, std::string(std::string(ICON_FA_SMILE_BEAM) + u8" Green").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_YELLOW)
	{
		ImGui::TextColored(Globals::ColorYellow, std::string(std::string(ICON_FA_MEH) + u8" Yellow").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_ORANGE)
	{
		ImGui::TextColored(Globals::ColorOrange, std::string(std::string(ICON_FA_FROWN) + u8" Orange").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_RED)
	{
		ImGui::TextColored(Globals::ColorRed, std::string(std::string(ICON_FA_DUMPSTER_FIRE) + u8" Red").c_str());
	}
	else
	{
		ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::string(ICON_FA_QUESTION) + u8" Invalid").c_str());
	}
	ImGui::RadioButton("Green", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_GREEN);
	ImGui::SameLine();
	ImGui::RadioButton("Yellow", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_YELLOW);
	ImGui::SameLine();
	ImGui::RadioButton("Orange", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_ORANGE);
	ImGui::SameLine();
	ImGui::RadioButton("Red", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_RED);
	ImGui::SameLine();
	if (ImGui::Button("Set alert level"))
	{
		GsmSetAlertLevel(CustomAlertLevel);
	}
	ImGui::SameLine();
	ImGui::Checkbox("Lock", &LockAlertLevel);
	ImGui::Separator();

	ImGui::Text("Xray Effect Mode: ");
	ImGui::SameLine(); ImGui::RadioButton("Backpack", &XrayEffectMode, 0);
	ImGui::SameLine(); ImGui::RadioButton("Rail Driver", &XrayEffectMode, 1);
	ImGui::Text("Selected mode value: "); ImGui::SameLine();
	ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(XrayEffectMode).c_str());
	if (ImGui::Button("Toggle Selected Xray Mode"))
	{
		if (XrayEffectMode == 0)
		{
			if (XrayModeOn)
			{
				XrayEffectStop(XET_VISION_BACKPACK);
				XrayModeOn = false;
			}
			else
			{
				XrayEffectStart(XET_VISION_BACKPACK);
				XrayModeOn = true;
			}
		}
		else if (XrayEffectMode == 1)
		{
			if (XrayModeOn)
			{
				XrayEffectStop(XET_RAIL_DRIVER);
				XrayModeOn = false;
			}
			else
			{
				XrayEffectStart(XET_RAIL_DRIVER);
				XrayModeOn = true;
			}
		}
	}
    ImGui::Separator();

	ImGui::Checkbox("Infinite jetpack", &Globals::InfiniteJetpack);
	if (ImGui::Checkbox("Invulnerability", &Invulnerable))
	{
		PlayerPtr->HitPoints = PlayerPtr->MaxHitPoints;
	}
	if (!Invulnerable)
	{
		PlayerPtr->Flags.invulnerable = false;
	}
	if (ImGui::Checkbox("Ignored by AI", &AiIgnore))
	{
		//Have to manually set rather than sticking in checkbox call because bitfields addresses can't be captured.
		PlayerPtr->Flags.ai_ignore = !PlayerPtr->Flags.ai_ignore;
		AiIgnore = PlayerPtr->Flags.ai_ignore;
	}
	if(ImGui::Checkbox("Disable player ragdoll", &DisablePlayerRagdoll))
	{
		PlayerPtr->Flags.disallow_flinches_and_ragdolls = !PlayerPtr->Flags.disallow_flinches_and_ragdolls;
		DisablePlayerRagdoll = PlayerPtr->Flags.disallow_flinches_and_ragdolls;
	}
    ImGui::Separator();

    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputInt("Salvage", &PlayerPtr->Metadata.Salvage);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputInt("Mining count", &PlayerPtr->Metadata.MiningCount);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputInt("Supply crate count", &PlayerPtr->Metadata.SupplyCrateCount);


    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Custom player jump height", &CustomJumpHeight, 0.5f, 2.0f, 3); ImGui::SameLine();
	ImGui::Checkbox("##Custom Player Jump Height", &NeedCustomJumpHeightSet);

    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Player move speed", &CustomPlayerMoveSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player move speed checkbox", &NeedCustomMoveSpeedSet);
	
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Player max speed", &CustomPlayerMaxSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player max move speed checkbox", &NeedCustomMaxMoveSpeedSet);
	ImGui::Separator();

	if (!UseCustomLevelAmbientLight)
	{
		CustomLevelAmbientLight.x = Globals::RfgWorldPtr->level_ambient.x;
		CustomLevelAmbientLight.y = Globals::RfgWorldPtr->level_ambient.y;
		CustomLevelAmbientLight.z = Globals::RfgWorldPtr->level_ambient.z;
	}
	if (!UseCustomLevelBackgroundAmbientLight)
	{
		CustomLevelBackgroundAmbientLight.x = Globals::RfgWorldPtr->level_back_ambient.x;
		CustomLevelBackgroundAmbientLight.y = Globals::RfgWorldPtr->level_back_ambient.y;
		CustomLevelBackgroundAmbientLight.z = Globals::RfgWorldPtr->level_back_ambient.z;
	}
	if (!UseCustomTimeOfDayLight)
	{
		CustomTimeOfDayLightColor.red = Globals::TODLightPtr->m_color.red;
		CustomTimeOfDayLightColor.green = Globals::TODLightPtr->m_color.green;
		CustomTimeOfDayLightColor.blue = Globals::TODLightPtr->m_color.blue;
		CustomTimeOfDayLightColor.alpha = Globals::TODLightPtr->m_color.alpha;
	}

    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat3("Level ambient light", (float*)&CustomLevelAmbientLight, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##ToggleLevelAmbientLight", &UseCustomLevelAmbientLight);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat3("Level background ambient light", (float*)&CustomLevelBackgroundAmbientLight, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##ToggleLevelBackgroundAmbientLight", &UseCustomLevelBackgroundAmbientLight);

	ImGui::End();
}