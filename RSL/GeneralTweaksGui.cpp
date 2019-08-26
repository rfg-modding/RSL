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
    if(!GameClock)
    {
        Logger::LogWarning("Updating GeneralTweaksGui::GameClock!\n");
        GameClock = game_clock_get();
    }

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("General tweaks:");
	ImGui::PopFont();
	ImGui::Separator();

    //if(ImGui::Button("Enable penetration on all weapons"))
    //{
    //    if(Globals::WeaponInfos.Initialized())
    //    {
    //        Logger::Log("WeaponInfos:: Capacity: {}, Length: {}, Size: {}\n", Globals::WeaponInfos.Capacity(), Globals::WeaponInfos.Length(), Globals::WeaponInfos.Size());
    //        Logger::Log("Applying edits on all weapons (weapon_info test1)\n");
    //        for(int i = 0; i < Globals::WeaponInfos.Length(); i++)
    //        {
    //            weapon_info& Info = Globals::WeaponInfos[i];
    //            if(Info.name) Logger::Log("\n\nEditing {}, alternative {}\n", Info.name, std::string(Info.name));
    //            if(Info.icon_name) Logger::Log("icon_name: {}\n", Info.icon_name);
    //            if(Info.small_icon_name) Logger::Log("small_icon_name: {}\n", Info.small_icon_name);
    //            if(Info.reticule_name) Logger::Log("reticule_name: {}\n", Info.reticule_name);
    //            if(Info.fine_aim_reticule_name) Logger::Log("fine_aim_reticule_name: {}\n", Info.fine_aim_reticule_name);
    //            if(Info.mp_kill_phrase) Logger::Log("mp_kill_phrase: {}\n", Info.mp_kill_phrase);
    //            Logger::Log("muzzle_flash_effect: {}\n", Info.muzzle_flash_effect);
    //            Logger::Log("muzzle_smoke_effect: {}\n", Info.muzzle_smoke_effect);
    //            Logger::Log("special_hit_effect: {}\n", Info.special_hit_effect);
    //            Logger::Log("special_effect: {}\n", Info.special_effect);
    //            Logger::Log("secondary_special_effect: {}\n", Info.secondary_special_effect);
    //            Logger::Log("overheated_effect: {}\n", Info.overheated_effect);
    //            Logger::Log("tracer_effect: {}\n", Info.tracer_effect);
    //            Logger::Log("max_range: {}\n", Info.max_range);
    //            Logger::Log("red_range: {}\n", Info.red_range);
    //            Logger::Log("aim_assist: {}\n", Info.aim_assist);
    //            Logger::Log("alert_multiplier: {}\n", Info.alert_multiplier);
    //            Logger::Log("fire_sound: {}\n", Info.fire_sound);
    //            Logger::Log("reload_sound: {}\n", Info.reload_sound);
    //            Info.flags.never_in_cabinet = false;
    //            Info.flags.armor_piercing = true;
    //            Info.flags.shatter = true;
    //            Info.flags.penetrating_bullets = true;
    //        }
    //    }
    //}

    //static float DisplayTime = 10.0f;
    //static bool UseSecondaryAnim = false;
    //static bool ForceRedisplay = false;
    //if(ImGui::Button("Add secondary gui message"))
    //{
    //    ui_add_secondary_message(L"Meow meow", DisplayTime, UseSecondaryAnim, ForceRedisplay);
    //}
    
    static bool Transparent = true;
    static bool PauseBeneath = false;
    //ImGui::Checkbox("Transparent", &Transparent);
    //ImGui::Checkbox("Pause beneath", &PauseBeneath);
    if(ImGui::Button("Open weapons locker menu"))
    {
        GameseqPushState(GS_INGAME_WEAPON_CABINET, Transparent, PauseBeneath);
    }
    if (ImGui::Button("Open upgrades menu"))
    {
        GameseqPushState(GS_INGAME_UPGRADES_HUD, Transparent, PauseBeneath);
    }
	if (ImGui::Button("Toggle Hud"))
	{
		ToggleHud();
	}
	if (ImGui::Button("Toggle Fog"))
	{
		ToggleFog();
	}
	ImGui::Separator();
	
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
	ImGui::InputFloat("Player move speed override", Globals::PlayerMaxMovementSpeedOverride, 1.0f, 5.0f, 3);
	ImGui::SameLine();
    if(ImGui::Button("Reset##ResetPlayerMaxMoveSpeedOverride"))
    {
        *Globals::PlayerMaxMovementSpeedOverride = 0.0f;
    }
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("If this is set to 0.0, you'll move at the vanilla speed. If you set it to any other value, you'll move at that speed.");
	
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Player max speed", &Globals::PlayerPtr->MaxSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	if(ImGui::Button("Reset##PlayerMaxSpeedCustomReset"))
	{
        Globals::PlayerPtr->MaxSpeed = 0.0f;
	}
	ImGui::Separator();

    if (Globals::SpeedScale)
    {
        ImGui::SetNextItemWidth(230.0f);
        ImGui::InputFloat("Game speed scale", Globals::SpeedScale);
        ImGui::SameLine();
        if (ImGui::Button("Reset##ResetButtonSpeedScale"))
        {
            *Globals::SpeedScale = 1.0f;
        }
        ImGui::SameLine();
        Util::Gui::ShowHelpMarker("1.0 = vanilla, # < 1.0 = slo-mo, # > 1.0 = \"fast-mo\"");
    }

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

    ImGui::Separator();

    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Salvage", &Globals::PlayerPtr->Metadata.Salvage);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Mining count", &Globals::PlayerPtr->Metadata.MiningCount);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Supply crate count", &Globals::PlayerPtr->Metadata.SupplyCrateCount);
    ImGui::Separator();

    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Game clock:");
    ImGui::PopFont();
    ImGui::Separator();
    if(GameClock)
    {
        static uint CurrentTicksMin = 0;
        static uint CurrentTicksMax = std::numeric_limits<uint>::max();
        ImGui::PushItemWidth(230.0f);
        ImGui::InputScalar("Year", ImGuiDataType_U16, &GameClock->m_year);
        ImGui::InputScalar("Month", ImGuiDataType_U8, &GameClock->m_month);
        ImGui::InputScalar("Day", ImGuiDataType_U8, &GameClock->m_day);
        ImGui::InputScalar("Hour", ImGuiDataType_U8, &GameClock->m_hour);
        ImGui::InputScalar("Minutes", ImGuiDataType_U8, &GameClock->m_minutes);
        ImGui::InputScalar("Seconds", ImGuiDataType_U8, &GameClock->m_seconds);
        ImGui::InputScalar("Day of the week", ImGuiDataType_U8, &GameClock->m_day_of_week);
        ImGui::SliderFloat("Time scale", &GameClock->m_time_scale, 0.0f, 1000.0f);
        ImGui::SameLine();
        if(ImGui::Button("Reset##GameClockTimeScale"))
        {
            GameClock->m_time_scale = 48.0f;
        }
        ImGui::InputScalar("Current day ticks", ImGuiDataType_U32, &GameClock->m_curr_day_ticks);
        ImGui::PopItemWidth();
        ImGui::SliderScalar("Current day ticks", ImGuiDataType_U32, &GameClock->m_curr_day_ticks, &CurrentTicksMin, &CurrentTicksMax);
        if(ImGui::Checkbox("Lock time of day change", &LockTodTicksChange))
        {
            if(LockTodTicksChange)
            {
                PreTodPauseTimescale = GameClock->m_time_scale;
                GameClock->m_time_scale = 0.0f;
            }
            else
            {
                GameClock->m_time_scale = PreTodPauseTimescale;
            }
        }
    }
    else
    {
        ImGui::Text("GameClock == nullptr, cannot display settings");
    }
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
    ImGui::Separator();

    //Experimental settings
    ImGui::PushFont(Globals::FontBig);
    ImGui::Text("Experimental tweaks:");
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::Checkbox("Disable debris deletion", &Globals::DisableDebrisDeletion);
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("Disables the deleting of debris. Doesn't work 100% of the time. When it does you'll note that at some point, additional debris will stop spawning. This is due to some internal limit of debris being hit (believed to be ~500 pieces of debris). This likely won't be easy to raise. Note that this may have other unintended effects which are currently not known, which is why this is marked as experimental.");
    ImGui::Checkbox("find_gm override", &Globals::FindGmOverride);
    ImGui::SameLine();
    ImGui::Checkbox("Use override", &Globals::UseFindGmOverride);
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("NOTE: DOES NOT DO ANYTHING IF DEBRIS DELETION IS DISABLED. Specify an override to the find_gm value passed to rfgl_find_and_delete_object_mover. The effect of this is unknown, and this has been included in case anyone finds a specific effect of it.");

	ImGui::End();
}