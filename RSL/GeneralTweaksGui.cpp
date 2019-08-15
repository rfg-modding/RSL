#include "GeneralTweaksGui.h"

GeneralTweaksGui::GeneralTweaksGui(std::string Title_)
{
	Title = Title_;

	CustomTimeOfDayLightColor.red = 0.0f;
	CustomTimeOfDayLightColor.green = 0.0f;
	CustomTimeOfDayLightColor.blue = 0.0f;
	CustomTimeOfDayLightColor.alpha = 0.0f;

	CustomAlertLevel = ALERT_LEVEL_GREEN;
}

void GeneralTweaksGui::Draw()
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

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("General tweaks:");
	ImGui::PopFont();
	ImGui::Separator();

    //if(Globals::RfgMenusList)
    //{
    //    if(ImGui::Button("Log rfg menu info"))
    //    {
    //        auto length = Globals::RfgMenusList->Length();
    //        auto size = Globals::RfgMenusList->Size();
    //        Logger::Log("\n\nLogging rfg menu info:\n");
    //        for (int i = 0; i < Globals::RfgMenusList->Size(); i++)
    //        {
    //            ui_menu& Menu = *(*Globals::RfgMenusList)[i];
    //            Logger::Log("\n\n\tLogging menu info at index {}:\n", i);
    //            Logger::Log("\t\tTitle: {}\n", Menu.m_title);
    //            Logger::Log("\t\tSupress accept sounds?: {}\n", Menu.m_surpress_accept_sounds);
    //            Logger::Log("\t\tShould tween out?: {}\n", Menu.m_should_tween_out);
    //            Logger::Log("\t\tAwaiting tween on select end?: {}\n", Menu.m_awaiting_tween_on_select_end);
    //            Logger::Log("\t\tAwaiting tween fade in end?: {}\n", Menu.m_awaiting_tween_fade_in_end);
    //            Logger::Log("\t\tForce update?: {}\n", Menu.m_force_update);
    //            Logger::Log("\t\tChoose on enter: {}\n", Menu.m_choose_on_enter);
    //            Logger::Log("\t\tHandle: {}\n", Menu.m_handle);
    //            Logger::Log("\t\tDoc handle: {}\n", Menu.m_doc_handle);
    //            Logger::Log("\t\tInput id: {}\n", Menu.m_input_id);
    //            Logger::Log("\t\tSelected?: {}\n", Menu.m_selected);
    //            Logger::Log("\t\tNum items: {}\n", Menu.m_num_items);

    //            Logger::Log("\t\tLogging ui_menu_items:\n");
    //            for(int j = 0; j < 15; j++)
    //            {
    //                if(Menu.m_items[j])
    //                {
    //                    Logger::Log("\n\t\t\tLogging menu item at index {}\n", j);
    //                    //Todo: Check the type of each item, and cast to it's derived type such as ui_menu_item_func or ui_menu_item_bool
    //                    ui_menu_item_base& Item = *Menu.m_items[j];
    //                    Logger::Log("\t\t\tCaption: {}\n", Item.m_caption);
    //                    Logger::Log("\t\t\tPlay change sound?: {}\n", Item.m_play_change_sound);
    //                    Logger::Log("\t\t\tSelected?: {}\n", Item.m_selected);
    //                    Logger::Log("\t\t\tEnabled?: {}\n", Item.m_enabled);
    //                    Logger::Log("\t\t\tVisible?: {}\n", Item.m_visible);
    //                    Logger::Log("\t\t\tHandle: {}\n", Item.m_handle);
    //                    Logger::Log("\t\t\tType: {}\n", Item.m_type);
    //                    //Logger::Log("\t\t\t: {}", Item.m_parent);
    //                }
    //            }

    //            //Log document_info
    //            //Log hint_info

    //            //Logger::Log("\t\t: {}\n", Menu.m_num_items);
    //            //Logger::Log("\t\t: {}\n", Menu.m_num_items);
    //            //Logger::Log("\t\t: {}\n", Menu.m_num_items);
    //        }
    //    }
    //}
    //else
    //{
    //    ImGui::Text("RfgMenusList is a nullptr, cannot display it's values.");
    //}

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
        Globals::PlayerPtr->HitPoints = Globals::PlayerPtr->MaxHitPoints;
	}
	if (!Invulnerable)
	{
        Globals::PlayerPtr->Flags.invulnerable = false;
	}
	if (ImGui::Checkbox("Ignored by AI", &AiIgnore))
	{
		//Have to manually set rather than sticking in checkbox call because bitfields addresses can't be captured.
        Globals::PlayerPtr->Flags.ai_ignore = !Globals::PlayerPtr->Flags.ai_ignore;
		AiIgnore = Globals::PlayerPtr->Flags.ai_ignore;
	}
	if(ImGui::Checkbox("Disable player ragdoll", &DisablePlayerRagdoll))
	{
        Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls = !Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls;
		DisablePlayerRagdoll = Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls;
	}
    ImGui::Separator();

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

    ImGui::Checkbox("Unlimited ammo", Globals::UnlimitedAmmo);
    ImGui::Checkbox("Unlimited magazine ammo", Globals::UnlimitedMagazineAmmo);
    ImGui::Checkbox("Unlimited AI thrown weapons", Globals::UnlimitedAiThrownWeapons); 
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("Unsure what exactly this does. Added it in case anyone figures it out.");
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Max vehicle speed", Globals::VehicleMaxSpeed);
    ImGui::SameLine();
    if(ImGui::Button("Reset"))
    {
        *Globals::VehicleMaxSpeed = 40.233601f;
    }
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Charge explosion delay", Globals::ChargeExplosionDelay);
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("Delay between each remote charge being detonated, in milliseconds (1000ms = 1s). Default is 250ms.");
    ImGui::Checkbox("SSAO Vision", Globals::SsaoVisionEnabled);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Max remote charges placed", Globals::RfgMaxCharges);
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("The default value might be lower than your current amount. Just set it to whatever value you want, and it'll override your upgrade level.");
    ImGui::Checkbox("Time of day change enabled", Globals::TodEnabled);

    ImGui::Separator();

    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Salvage", &Globals::PlayerPtr->Metadata.Salvage);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Mining count", &Globals::PlayerPtr->Metadata.MiningCount);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Supply crate count", &Globals::PlayerPtr->Metadata.SupplyCrateCount);
    ImGui::Separator();
    ImGui::Text("Current time of day:");
    ImGui::SameLine();
    ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(*Globals::CurrentTimeOfDay));
    ImGui::SetNextItemWidth(230.0f);
    ImGui::SliderFloat("Custom time of day", &CustomTodOverride, 0.00f, 23.99f);
    ImGui::SameLine();
    ImGui::Checkbox("Use custom value (Locks time change)", &UseCustomTodOverride);
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