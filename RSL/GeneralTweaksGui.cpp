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
        return;

    ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), &Visible))
	{
		ImGui::End();
		return;
	}
    if(!GameClock)
    {
        Logger::LogWarning("Updating GeneralTweaksGui::GameClock!\n");
        GameClock = rfg::game_clock_get();
    }

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("General tweaks:");
	ImGui::PopFont();
	ImGui::Separator();
    
    static bool Transparent = true;
    static bool PauseBeneath = false;
    if(ImGui::Button("Open weapons locker menu"))
        rfg::GameseqPushState(GS_INGAME_WEAPON_CABINET, Transparent, PauseBeneath);
    if (ImGui::Button("Open upgrades menu"))
        rfg::GameseqPushState(GS_INGAME_UPGRADES_HUD, Transparent, PauseBeneath);
    if (ImGui::Button("Toggle Hud"))
        rfg::ToggleHud();
    if (ImGui::Button("Toggle Fog"))
        rfg::ToggleFog();

    ImGui::Separator();
	ImGui::Text("Alert level: ");
	ImGui::SameLine();
	gfm_alert_levels AlertCheck = rfg::GsmGetAlertLevel();
	if (AlertCheck == ALERT_LEVEL_GREEN)
        ImGui::TextColored(Globals::ColorGreen, std::string(std::string(ICON_FA_SMILE_BEAM) + u8" Green").c_str());
    else if (AlertCheck == ALERT_LEVEL_YELLOW)
        ImGui::TextColored(Globals::ColorYellow, std::string(std::string(ICON_FA_MEH) + u8" Yellow").c_str());
    else if (AlertCheck == ALERT_LEVEL_ORANGE)
        ImGui::TextColored(Globals::ColorOrange, std::string(std::string(ICON_FA_FROWN) + u8" Orange").c_str());
    else if (AlertCheck == ALERT_LEVEL_RED)
        ImGui::TextColored(Globals::ColorRed, std::string(std::string(ICON_FA_DUMPSTER_FIRE) + u8" Red").c_str());
    else
        ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::string(ICON_FA_QUESTION) + u8" Invalid").c_str());

    ImGui::RadioButton("Green", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_GREEN);
	ImGui::SameLine();
	ImGui::RadioButton("Yellow", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_YELLOW);
	ImGui::SameLine();
	ImGui::RadioButton("Orange", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_ORANGE);
	ImGui::SameLine();
	ImGui::RadioButton("Red", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_RED);
	ImGui::SameLine();
	if (ImGui::Button("Set alert level"))
        rfg::GsmSetAlertLevel(CustomAlertLevel);

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
                rfg::XrayEffectStop(XET_VISION_BACKPACK);
				XrayModeOn = false;
			}
			else
			{
                rfg::XrayEffectStart(XET_VISION_BACKPACK);
				XrayModeOn = true;
			}
		}
		else if (XrayEffectMode == 1)
		{
			if (XrayModeOn)
			{
                rfg::XrayEffectStop(XET_RAIL_DRIVER);
				XrayModeOn = false;
			}
			else
			{
                rfg::XrayEffectStart(XET_RAIL_DRIVER);
				XrayModeOn = true;
			}
		}
	}

    ImGui::Separator();
	ImGui::Checkbox("Infinite jetpack", &Globals::InfiniteJetpack);
	if (ImGui::Checkbox("Invulnerability", &Invulnerable))
        Globals::PlayerPtr->HitPoints = Globals::PlayerPtr->MaxHitPoints;
    if (!Invulnerable)
        Globals::PlayerPtr->Flags.invulnerable = false;
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
        *Globals::PlayerMaxMovementSpeedOverride = 0.0f;

    ImGui::SameLine();
    Gui::ShowHelpMarker("If this is set to 0.0, you'll move at the vanilla speed. If you set it to any other value, you'll move at that speed.");
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Player max speed", &Globals::PlayerPtr->MaxSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	if(ImGui::Button("Reset##PlayerMaxSpeedCustomReset"))
        Globals::PlayerPtr->MaxSpeed = 0.0f;

    ImGui::Separator();
    if (Globals::SpeedScale)
    {
        ImGui::SetNextItemWidth(230.0f);
        ImGui::InputFloat("Game speed scale", Globals::SpeedScale);
        ImGui::SameLine();
        if (ImGui::Button("Reset##ResetButtonSpeedScale"))
            *Globals::SpeedScale = 1.0f;

        ImGui::SameLine();
        Gui::ShowHelpMarker("1.0 = vanilla, # < 1.0 = slo-mo, # > 1.0 = \"fast-mo\"");
    }

    ImGui::Checkbox("Unlimited ammo", Globals::UnlimitedAmmo);
    ImGui::Checkbox("Unlimited magazine ammo", Globals::UnlimitedMagazineAmmo);
    ImGui::Checkbox("Unlimited AI thrown weapons", Globals::UnlimitedAiThrownWeapons); 
    ImGui::SameLine();
    Gui::ShowHelpMarker("Unsure what exactly this does. Added it in case anyone figures it out.");
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputFloat("Max vehicle speed", Globals::VehicleMaxSpeed);
    ImGui::SameLine();
    if(ImGui::Button("Reset"))
        *Globals::VehicleMaxSpeed = 40.233601f;

    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Charge explosion delay", Globals::ChargeExplosionDelay);
    ImGui::SameLine();
    Gui::ShowHelpMarker("Delay between each remote charge being detonated, in milliseconds (1000ms = 1s). Default is 250ms.");
    ImGui::Checkbox("SSAO Vision", Globals::SsaoVisionEnabled);
    ImGui::SetNextItemWidth(230.0f);
    ImGui::InputInt("Max remote charges placed", Globals::RfgMaxCharges);
    ImGui::SameLine();
    Gui::ShowHelpMarker("The default value might be lower than your current amount. Just set it to whatever value you want, and it'll override your upgrade level.");

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
        Gui::LabelAndValue("Year", std::to_string(GameClock->m_year));
        Gui::LabelAndValue("Month", std::to_string(GameClock->m_month));
        Gui::LabelAndValue("Day", std::to_string(GameClock->m_day));
        Gui::LabelAndValue("Hour", std::to_string(GameClock->m_hour));
        Gui::LabelAndValue("Minutes", std::to_string(GameClock->m_minutes));
        Gui::LabelAndValue("Seconds", std::to_string(GameClock->m_seconds));
        Gui::LabelAndValue("Day of the week", std::to_string(GameClock->m_day_of_week));
        ImGui::SliderFloat("Time scale", &GameClock->m_time_scale, 0.0f, 1000.0f);
        ImGui::SameLine();
        if(ImGui::Button("Reset##GameClockTimeScale"))
            GameClock->m_time_scale = 48.0f;

        ImGui::SliderScalar("Current day ticks", ImGuiDataType_U32, &GameClock->m_curr_day_ticks, &CurrentTicksMin, &CurrentTicksMax);
        ImGui::PopItemWidth();
        if(ImGui::Checkbox("Lock time of day change", &LockTodTicksChange))
        {
            if(LockTodTicksChange)
            {
                PreTodPauseTimescale = GameClock->m_time_scale;
                GameClock->m_time_scale = 0.0f;
            }
            else
                GameClock->m_time_scale = PreTodPauseTimescale;
        }
    }
    else
        ImGui::Text("GameClock == nullptr, cannot display settings");

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
    Gui::ShowHelpMarker("Disables the deleting of debris. Doesn't work 100% of the time. When it does you'll note that at some point, additional debris will stop spawning. This is due to some internal limit of debris being hit (believed to be ~500 pieces of debris). This likely won't be easy to raise. Note that this may have other unintended effects which are currently not known, which is why this is marked as experimental.");
    ImGui::Checkbox("find_gm override", &Globals::FindGmOverride);
    ImGui::SameLine();
    ImGui::Checkbox("Use override", &Globals::UseFindGmOverride);
    ImGui::SameLine();
    Gui::ShowHelpMarker("NOTE: DOES NOT DO ANYTHING IF DEBRIS DELETION IS DISABLED. Specify an override to the find_gm value passed to rfgl_find_and_delete_object_mover. The effect of this is unknown, and this has been included in case anyone finds a specific effect of it.");

    static std::array<std::string, 50> vertexFormatNames = 
    {
        "rlvf_pixlit_vtx_desc_2",
        "No name set",
        "No name set",
        "No name set",
        "rlvf_unlit_desc_5",
        "rlvf_particle_pointsprite_desc_4",
        "rlvf_particle_billboard_desc_9",
        "rlvf_particle_radial_desc_8",
        "rlvf_particle_drop_desc_8",
        "rlvf_particle_ribbon_desc_9",
        "rlvf_particle_oriented_desc_9",
        "rlvf_primitive_3d_desc_3",
        "rlvf_primitive_2d_desc_3",
        "No name set",
        "rlvf_height_mesh_desc_2",
        "rlvf_height_mesh_low_lod_desc_1",
        "rlvf_particle_parametric_desc_7",
        "rlvf_compositor_desc_2",
        "No name set",
        "rlvf_clone_nmap_desc_4",
        "rlvf_clone_clr_desc_8",
        "rlvf_2d_spline_desc_1",
        "rlvf_particle_corona_desc_11",
        "rlvf_particle_ribbon_parametric_desc_6",
        "No name set",
        "rlvf_terrain_road_desc_8",
        "rlvf_height_mesh_landmark_lod_desc_3",
        "rlvf_star_field_point_elements_1",
        "rlvf_star_field_billboard_elements_2",
        "rlvf_meteor_shower_line_elements_3",
        "rlvf_pixlit_vtx_desc_2",
        "rlvf_pixlit_vtx_desc_10",
        "rlvf_pixlit_ca_vtx_desc_11",
        "rlvf_pixlit_nmap_vtx_desc_11",
        "rlvf_pixlit_nmap_ca_vtx_desc_12",
        "rlvf_pixlit_vtx_desc_11",
        "rlvf_pixlit_ca_vtx_desc_12",
        "rlvf_pixlit_nmap_vtx_desc_12",
        "rlvf_pixlit_nmap_ca_vtx_desc_13",
        "rlvf_pixlit_vtx_desc_12",
        "rlvf_pixlit_ca_vtx_desc_13",
        "rlvf_pixlit_nmap_vtx_desc_13",
        "rlvf_pixlit_nmap_ca_vtx_desc_14",
        "rlvf_pixlit_vtx_desc_13", //rlvf_pixlit_vtx_desc
        "rlvf_pixlit_ca_vtx_desc_14",
        "rlvf_pixlit_nmap_vtx_desc_14",
        "rlvf_pixlit_nmap_ca_vtx_desc_15",
        "rlvf_clone_uvs_desc_3",
        "rlvf_clone_uvs_desc_4",
        "rlvf_uncompressed_morph_vtx_des_2",
    };

    if(ImGui::Button("Vertex formats"))
    {
        if(Globals::RlRenderLibPtr)
        {
            Logger::Log("Writing vertex format list...\n");

            for(int i = 0; i < 50; i++)
            {
                keen::VertexFormat* format = Globals::RlRenderLibPtr->m_vertex_formats_p[i];
                Logger::Log("\n\nFormat {}: {}, stride0: {}\n", i, vertexFormatNames[i], format ? format->streamStride[0] : 0);
                if(format)
                {
                    Logger::Log("    attributeCount: {}\n", format->attributeCount);
                    Logger::Log("    instanceDataStreamIndex: {}\n", format->instanceDataStreamIndex);
                    //Write attributes
                    Logger::Log("    attributes:\n");
                    for(int j = 0; j < format->attributeCount; j++)
                    {
                        auto& attribute = format->attributes[j];

                        keen::VertexAttributeId idVal = (keen::VertexAttributeId)attribute.id;
                        keen::VertexAttributeFormat formatVal = (keen::VertexAttributeFormat)attribute.format;
                        auto attributeIdTemp = magic_enum::enum_name(idVal);
                        auto attributeFormatTemp = magic_enum::enum_name(formatVal);
                        std::string attributeIdString = attributeIdTemp.data();
                        std::string attributeFormatString = attributeFormatTemp.data();

                        Logger::Log("\n        {}:\n", j);
                        Logger::Log("            id: {}\n", (uint)attribute.id);
                        Logger::Log("            format: {}\n", (uint)attribute.format);
                        Logger::Log("            idString: {}\n", attributeIdString);
                        Logger::Log("            formatString: {}\n", attributeFormatString);
                        Logger::Log("            inputStreamIndex: {}\n", (uint)attribute.inputStreamIndex);
                        Logger::Log("            instanceStepRate: {}\n", (uint)attribute.instanceStepRate);
                    }
                    //Write attribute offsets, indices, and stream stride values
                    Logger::Log("\n    attributeOffsets:\n");
                    for(int j = 0; j < 17; j++)
                        Logger::Log("        {},\n", format->attributeOffsets[j]);

                    Logger::Log("\n    attributeIndices:\n");
                    for (int j = 0; j < 17; j++)
                        Logger::Log("        {},\n", format->attributeIndices[j]);

                    Logger::Log("\n    streamStride:\n");
                    for (int j = 0; j < 6; j++)
                        Logger::Log("        {},\n", format->streamStride[j]);
                }
                else
                {
                    Logger::Log("    nullptr\n");
                }
            }

            //for (int i = 0; i < 50; i++)
            //{
            //    keen::VertexFormat* format = Globals::RlRenderLibPtr->m_vertex_formats_p[i];
            //    nlohmann::json formatObject = formatArray.object();
            //    if (format)
            //    {
            //        //Todo: Make array of names of format indices and add to json
            //        jsonFile[i]["attributes"]["attributeCount"] = format->attributeCount;
            //        jsonFile[i]["attributes"]["instanceDataStreamIndex"] = format->instanceDataStreamIndex;
            //        //Write attributes
            //        for (int j = 0; j < format->attributeCount; j++)
            //        {
            //            auto& attribute = format->attributes[j];

            //            keen::VertexAttributeId idVal = (keen::VertexAttributeId)attribute.id;
            //            keen::VertexAttributeFormat formatVal = (keen::VertexAttributeFormat)attribute.format;
            //            auto attributeIdTemp = magic_enum::enum_name(idVal);
            //            auto attributeFormatTemp = magic_enum::enum_name(formatVal);
            //            std::string attributeIdString = attributeIdTemp.data();
            //            std::string attributeFormatString = attributeFormatTemp.data();

            //            jsonFile[i]["attributes"][j]["id"] = attribute.id;
            //            jsonFile[i]["attributes"][j]["format"] = attribute.format;
            //            jsonFile[i]["attributes"][j]["idString"] = attributeIdString;
            //            jsonFile[i]["attributes"][j]["formatString"] = attributeFormatString;
            //            jsonFile[i]["attributes"][j]["inputStreamIndex"] = attribute.inputStreamIndex;
            //            jsonFile[i]["attributes"][j]["instanceStepRate"] = attribute.instanceStepRate;
            //        }
            //        //Write attribute offsets, indices, and stream stride values
            //        for (int j = 0; j < 17; j++)
            //        {
            //            jsonFile[i]["attributes"]["attributeOffsets"][j] = format->attributeOffsets[j];
            //        }
            //        for (int j = 0; j < 17; j++)
            //        {
            //            jsonFile[i]["attributes"]["attributeIndices"][j] = format->attributeIndices[j];
            //        }
            //        for (int j = 0; j < 6; j++)
            //        {
            //            jsonFile[i]["attributes"]["streamStride"][j] = format->streamStride[j];
            //        }
            //    }
            //    else
            //    {
            //        jsonFile[i]["name"] = vertexFormatNames[i];
            //        jsonFile[i]["value"] = "nullptr";
            //    }
            //}
            //
            //
            //std::ofstream ConfigOutput(ExePath + "RSL/VertexFormats.json");
            //ConfigOutput << std::setw(4) << jsonFile << "\n";
            //ConfigOutput.close();
        }
        else
        {
            Logger::LogError("Can't dump vertex formats, RlRenderLibPtr = nullptr\n");
        }
    }

	ImGui::End();
}