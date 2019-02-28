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

	strcpy_s(CustomExplosionInfo.m_name, "Custom Explosion");
	CustomExplosionInfo.m_unique_id = 268; //A value of 255 caused explosions to cause no damage.
	CustomExplosionInfo.m_name_crc_str = 1234535;
	CustomExplosionInfo.flags = 1;
	CustomExplosionInfo.m_radius = 4.0f;
	CustomExplosionInfo.m_secondary_radius = 6.0f;
	CustomExplosionInfo.m_knockdown_radius = 3.0f;
	CustomExplosionInfo.m_flinch_radius = 4.0f;
	CustomExplosionInfo.m_ai_sound_radius = 2.0f;
	CustomExplosionInfo.m_human_min_damage_hitpoints = 30;
	CustomExplosionInfo.m_human_max_damage_hitpoints = 40;
	CustomExplosionInfo.m_vehicle_min_damage_hitpoints = 40;
	CustomExplosionInfo.m_vehicle_max_damage_hitpoints = 50;
	CustomExplosionInfo.player_damage_mult = 0.1f;
	CustomExplosionInfo.player_veh_damage_mult = 0.1f;
	CustomExplosionInfo.player_vehicle_impulse_mult = 1.0f;
	CustomExplosionInfo.m_impulse_magnitude = 40000.0f;
	CustomExplosionInfo.m_structural_damage = 12000;
	CustomExplosionInfo.expanding_explosion_duration = 0;
	CustomExplosionInfo.expanding_explosion_delay = 0;
	CustomExplosionInfo.m_num_effects = 1;
	CustomExplosionInfo.m_effects[0] = 1;
	CustomExplosionInfo.m_effects[1] = 0;
	CustomExplosionInfo.m_effects[2] = 0;
	CustomExplosionInfo.m_effects[3] = 0;
	CustomExplosionInfo.m_num_material_effects = 0;
	CustomExplosionInfo.m_material_effects[0] = 0;
	CustomExplosionInfo.m_material_effects[1] = 0;
	CustomExplosionInfo.m_material_effects[2] = 0;
	CustomExplosionInfo.m_material_effects[3] = 0;
	CustomExplosionInfo.m_material_effects[4] = 0;
	CustomExplosionInfo.m_material_effects[5] = 0;
	CustomExplosionInfo.m_material_effects[6] = 0;
	CustomExplosionInfo.m_material_effects[7] = 0;
	CustomExplosionInfo.m_material_referenece[0] = 0;
	CustomExplosionInfo.m_material_referenece[1] = 0;
	CustomExplosionInfo.m_material_referenece[2] = 0;
	CustomExplosionInfo.m_material_referenece[3] = 0;
	CustomExplosionInfo.m_material_referenece[4] = 0;
	CustomExplosionInfo.m_material_referenece[5] = 0;
	CustomExplosionInfo.m_material_referenece[6] = 0;
	CustomExplosionInfo.m_material_referenece[7] = 0;
	CustomExplosionInfo.salvage_material = SALVAGE_MATERIAL_METAL;
	CustomExplosionInfo.salvage_max_pieces = 0;
	CustomExplosionInfo.salvage_probability = 1.0f;
	CustomExplosionInfo.time_between_breaks = 1;
	CustomExplosionInfo.half_angle_dot = 0.8f;
	CustomExplosionInfo.blast_decal_radius = 2.0f;
	strcpy_s(CustomExplosionInfo.camera_shake_type, "");
	CustomExplosionInfo.camera_shake_multiplier = 1.0f;
	CustomExplosionInfo.camera_shake_falloff = 1.0f;
	CustomExplosionInfo.ignore_orientation = false;
	CustomExplosionInfo.always_ragdoll = false;

	CustomTimeOfDayLightColor.red = 0.0f;
	CustomTimeOfDayLightColor.green = 0.0f;
	CustomTimeOfDayLightColor.blue = 0.0f;
	CustomTimeOfDayLightColor.alpha = 0.0f;

	CustomAlertLevel = ALERT_LEVEL_GREEN;
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
	gfm_alert_levels AlertCheck = gsm_get_alert_level();
	if (AlertCheck == ALERT_LEVEL_GREEN)
	{
		ImGui::TextColored(ColorGreen, std::string(std::string(ICON_FA_SMILE_BEAM) + u8" Green").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_YELLOW)
	{
		ImGui::TextColored(ColorYellow, std::string(std::string(ICON_FA_MEH) + u8" Yellow").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_ORANGE)
	{
		ImGui::TextColored(ColorOrange, std::string(std::string(ICON_FA_FROWN) + u8" Orange").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_RED)
	{
		ImGui::TextColored(ColorRed, std::string(std::string(ICON_FA_DUMPSTER_FIRE) + u8" Red").c_str());
	}
	else
	{
		ImGui::TextColored(SecondaryTextColor, std::string(std::string(ICON_FA_QUESTION) + u8" Invalid").c_str());
	}
	ImGui::RadioButton("Green", (int*)&CustomAlertLevel, ALERT_LEVEL_GREEN);
	ImGui::SameLine();
	ImGui::RadioButton("Yellow", (int*)&CustomAlertLevel, ALERT_LEVEL_YELLOW);
	ImGui::SameLine();
	ImGui::RadioButton("Orange", (int*)&CustomAlertLevel, ALERT_LEVEL_ORANGE);
	ImGui::SameLine();
	ImGui::RadioButton("Red", (int*)&CustomAlertLevel, ALERT_LEVEL_RED);
	ImGui::SameLine();
	if (ImGui::Button("Set alert level"))
	{
		gsm_set_alert_level(CustomAlertLevel);
	}
	ImGui::Separator();

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

	ImGui::Checkbox("Infinite jetpack", &InfiniteJetpack);
	ImGui::Checkbox("Invulnerability", &Invulnerable);
	if (!Invulnerable)
	{
		PlayerPtr->Flags.invulnerable = false;
	}

	//ImGui::Text("Code driven jump height:"); ImGui::SameLine();
	//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CodeDrivenJumpHeight).c_str());
	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Custom player jump height", &CustomJumpHeight, 0.5f, 2.0f, 3); ImGui::SameLine();
	ImGui::Checkbox("##Custom Player Jump Height", &NeedCustomJumpHeightSet);

	//ImGui::Text("Player move speed:"); ImGui::SameLine();
	//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MoveSpeed).c_str());
	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Player move speed", &CustomPlayerMoveSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player move speed checkbox", &NeedCustomMoveSpeedSet);
	
	//ImGui::Text("Player max speed:"); ImGui::SameLine();
	//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MaxSpeed).c_str());
	if (!UseCustomLevelAmbientLight)
	{
		CustomLevelAmbientLight.x = GlobalRfgWorldPtr->level_ambient.x;
		CustomLevelAmbientLight.y = GlobalRfgWorldPtr->level_ambient.y;
		CustomLevelAmbientLight.z = GlobalRfgWorldPtr->level_ambient.z;
	}
	if (!UseCustomLevelBackgroundAmbientLight)
	{
		CustomLevelBackgroundAmbientLight.x = GlobalRfgWorldPtr->level_back_ambient.x;
		CustomLevelBackgroundAmbientLight.y = GlobalRfgWorldPtr->level_back_ambient.y;
		CustomLevelBackgroundAmbientLight.z = GlobalRfgWorldPtr->level_back_ambient.z;
	}
	if (!UseCustomTimeOfDayLight)
	{
		CustomTimeOfDayLightColor.red = GlobalTODLightPtr->m_color.red;
		CustomTimeOfDayLightColor.green = GlobalTODLightPtr->m_color.green;
		CustomTimeOfDayLightColor.blue = GlobalTODLightPtr->m_color.blue;
		CustomTimeOfDayLightColor.alpha = GlobalTODLightPtr->m_color.alpha;
	}

	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Player max speed", &CustomPlayerMaxSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player max move speed checkbox", &NeedCustomMaxMoveSpeedSet);
	ImGui::Separator();

	ImGui::InputFloat3("Level ambient light", (float*)&CustomLevelAmbientLight, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##ToggleLevelAmbientLight", &UseCustomLevelAmbientLight);
	ImGui::InputFloat3("Level background ambient light", (float*)&CustomLevelBackgroundAmbientLight, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##ToggleLevelBackgroundAmbientLight", &UseCustomLevelBackgroundAmbientLight);
	ImGui::Separator();

	//all_zones and global_zone_grid in rfg::world are always empty. 
	static int ZoneScanRange = 2000;
	ImGui::InputInt("Zone scan range", &ZoneScanRange);
	if (ImGui::Button("Print all zone names"))
	{
		//std::cout << "Address of globalzonegrid[]: " << GlobalRfgWorldPtr->all_zones << "\n";
		if (GlobalRfgWorldPtr)
		{
			int NumberOfZonesFound = 0;
			Logger::Log("\nPrinting all world zone names...\n", LogInfo);
			for (int i = 0; i < ZoneScanRange; i++)//GlobalRfgWorldPtr->num_territory_zones; i++)
			{
				world_zone* CurrentWorldZone = get_world_zone_by_index(GlobalRfgWorldPtr, NULL, i);
				if (CurrentWorldZone)
				{
					NumberOfZonesFound++;
					Logger::Log("\nPrinting all world zone names...\n", LogInfo);
					Logger::Log(std::string("Index: " + std::to_string(i)), LogInfo);
					Logger::Log(std::string("Zone name: " + std::string(CurrentWorldZone->name)), LogInfo);
					Logger::Log(std::string("srid: " + std::to_string(CurrentWorldZone->srid)), LogInfo);
					Logger::Log(std::string("gid: " + std::to_string(CurrentWorldZone->gid)), LogInfo);
					Logger::Log(std::string("Border zone: " + std::to_string(CurrentWorldZone->is_border_zone) + std::string("\n")), LogInfo);
				}
				else
				{
					//std::cout << "The zone pointer at index " << i << " is null. Stopping.\n";
					//break;
				}
				/*if (&*GlobalRfgWorldPtr->all_zones[i] != nullptr && &*GlobalRfgWorldPtr->all_zones[i] != NULL)
				{
					std::cout << "Index: " << i << ", Zone name: " << *GlobalRfgWorldPtr->all_zones[i]->name << "\n";
				}
				else
				{
					std::cout << "The zone pointer at index " << i << " is null\n";
				}*/
			}
			Logger::Log("Done printing all world zone info", LogInfo);
			Logger::Log(std::string("Number of zones found: " + std::to_string(NumberOfZonesFound)), LogInfo);
		}
		else
		{
			Logger::Log("Could not print zone names, the world pointer is null!\n", LogError);
		}
	}

	if (ImGui::Button("Print misc world values"))
	{
		std::cout << "\nPrinting all misc world values...\n";
		if (GlobalRfgWorldPtr)
		{
			std::cout << "Max world objects: " << GlobalRfgWorldPtr->max_world_objects << "\n";
			std::cout << "Tech level: " << GlobalRfgWorldPtr->tech_level << "\n";
			std::cout << "Tech level max: " << GlobalRfgWorldPtr->tech_level_max << "\n";
			std::cout << "Pending filename: " << GlobalRfgWorldPtr->pending_filename << "\n";
			std::cout << "GlobalRfgWorldPtr->all_objects.array_size: " << GlobalRfgWorldPtr->all_objects.array_size << "\n";
			std::cout << "GlobalRfgWorldPtr->all_objects.num: " << GlobalRfgWorldPtr->all_objects.num << "\n";
			std::cout << "Num territory zones: " << GlobalRfgWorldPtr->num_territory_zones << "\n";
		}
		else
		{
			Logger::Log("Could not print misc world values, the world pointer is null!\n", LogError);
		}
		std::cout << "Done!\n";
	}
	if (ImGui::Button("Dump all object info"))
	{
		if (GlobalRfgWorldPtr)
		{
			std::cout << "\nDumping all object info to ObjectInfoDump.txt...\n";
			std::ofstream PositionsDump(GetEXEPath(false) + "RFGR Script Loader/ObjectInfoDump.txt", std::ios_base::trunc);
			PositionsDump << "Start of object info dump...\n";
			PositionsDump << "Objects array capacity: " << GlobalRfgWorldPtr->all_objects.array_size << "\n";
			PositionsDump << "Objects array objects contained: " << GlobalRfgWorldPtr->all_objects.num << "\n\n";
			for (int i = 0; i < GlobalRfgWorldPtr->all_objects.num; i++)
			{
				if (&*GlobalRfgWorldPtr->all_objects.elt[i] != NULL && &*GlobalRfgWorldPtr->all_objects.elt[i] != nullptr)
				{
					PositionsDump << "Index: " << i << "\n";
					PositionsDump << "Name: " << world_get_object_name(GlobalRfgWorldPtr, NULL, &*GlobalRfgWorldPtr->all_objects.elt[i]) << "\n";
					PositionsDump << "Type: " << (int)(*GlobalRfgWorldPtr->all_objects.elt[i]).ObjectType << "\n";
					PositionsDump << "Subtype: " << (int)(*GlobalRfgWorldPtr->all_objects.elt[i]).SubType << "\n";
					PositionsDump << "Position:\n";
					PositionsDump << "    x: " << (*GlobalRfgWorldPtr->all_objects.elt[i]).Position.x << "\n";
					PositionsDump << "    y: " << (*GlobalRfgWorldPtr->all_objects.elt[i]).Position.y << "\n";
					PositionsDump << "    z: " << (*GlobalRfgWorldPtr->all_objects.elt[i]).Position.z << "\n\n";
				}
				else
				{
					PositionsDump << "Skipping object at index " << i << ", invalid pointer.\n";
				}
			}
			PositionsDump << "End of object info dump.";
			std::cout << "Finished dumped all object into to ObjectInfoDump.txt!\n";
			PositionsDump.close();
		}
		else
		{
			Logger::Log("Could not print zone names, the world pointer is null!", LogError);
		}
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Time of day light")) //Todo: Add rl_scene_entity and rl_3d_entity info to this.
	{
		if (GlobalTODLightPtr)
		{
			ImGui::Text("Light type:");
			ImGui::RadioButton("Directional", (int*)&GlobalTODLightPtr->m_light_type, LIGHT_TYPE_DIRECTIONAL);
			ImGui::SameLine();
			ImGui::RadioButton("Point", (int*)&GlobalTODLightPtr->m_light_type, LIGHT_TYPE_POINT);
			ImGui::SameLine();
			ImGui::RadioButton("Spot light", (int*)&GlobalTODLightPtr->m_light_type, LIGHT_TYPE_SPOT_LIGHT);
			ImGui::SameLine();
			ImGui::RadioButton("Force size of int", (int*)&GlobalTODLightPtr->m_light_type, LIGHT_TYPE_FORCE_SIZEOF_INT);

			ImGui::Text("Color:");
			ImGui::Checkbox("Use custom color", &UseCustomTimeOfDayLight);
			Utilities::GUI::TooltipOnPrevious("This needs to be checked for your values to be properly set");
			ImGui::InputFloat("Red", &CustomTimeOfDayLightColor.red, 0.01, 0.1, 3);
			ImGui::InputFloat("Green", &CustomTimeOfDayLightColor.green, 0.01, 0.1, 3);
			ImGui::InputFloat("Blue", &CustomTimeOfDayLightColor.blue, 0.01, 0.1, 3);
			ImGui::InputFloat("Alpha", &CustomTimeOfDayLightColor.alpha, 0.01, 0.1, 3);

			ImGui::InputFloat("Attenuation start", &GlobalTODLightPtr->m_attenuation_start, 0.01, 0.1, 3);
			ImGui::InputFloat("Attenuation end", &GlobalTODLightPtr->m_attenuation_end, 0.01, 0.1, 3);
			ImGui::InputFloat("Hotspot falloff size", &GlobalTODLightPtr->m_hotspot_falloff_size, 0.01, 0.1, 3);
			ImGui::InputFloat("Hotspot size", &GlobalTODLightPtr->m_hotspot_size, 0.01, 0.1, 3);

			ImGui::Text("Clip minimum:");
			ImGui::InputFloat("x", &GlobalTODLightPtr->m_clip_min.x, 0.01, 0.1, 3);
			ImGui::InputFloat("y", &GlobalTODLightPtr->m_clip_min.y, 0.01, 0.1, 3);
			ImGui::InputFloat("z", &GlobalTODLightPtr->m_clip_min.z, 0.01, 0.1, 3);

			ImGui::Text("Clip maximum:");
			ImGui::InputFloat("x", &GlobalTODLightPtr->m_clip_max.x, 0.01, 0.1, 3);
			ImGui::InputFloat("y", &GlobalTODLightPtr->m_clip_max.y, 0.01, 0.1, 3);
			ImGui::InputFloat("z", &GlobalTODLightPtr->m_clip_max.z, 0.01, 0.1, 3);

			ImGui::Text("Light direction:");
			ImGui::InputFloat("x", &GlobalTODLightPtr->m_light_direction.x, 0.01, 0.1, 3);
			ImGui::InputFloat("y", &GlobalTODLightPtr->m_light_direction.y, 0.01, 0.1, 3);
			ImGui::InputFloat("z", &GlobalTODLightPtr->m_light_direction.z, 0.01, 0.1, 3);

			//Todo: Add the following vars:
			//rl_renderable_instance *m_clip_mesh;
			//unsigned __int16 m_vis_pass_index;
			//unsigned __int16 m_shadow_vis_pass_index;
		}
		else
		{
			ImGui::Text("TOD Light pointer is null");
		}
	}
	else
	{
		ImGui::SameLine();
		ImGui::TextColored(ColorRed, "[Experimental]");
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Custom explosion info"))
	{
		ImGui::Text("Explosion create info:");
		ImGui::Checkbox("Allow explosion spawn with middle mouse?", &MiddleMouseBoomActive);
		ImGui::InputInt("Middle mouse explosions per second", &MiddleMouseExplosionsPerSecond);
		if (ImGui::Button("Boom"))
		{
			ExplosionCreate(&CustomExplosionInfo, PlayerPtr, PlayerPtr, &PlayerPtr->aim_pos, &PlayerPtr->Orientation, &PlayerPtr->aim_pos, NULL, false);
		}
		ImGui::Separator();

		ImGui::InputText("Name", (char*)&CustomExplosionInfo.m_name, 32);
		ImGui::InputInt("Unique ID", &CustomExplosionInfo.m_unique_id);
		ImGui::InputInt("Name CRC", (int*)&CustomExplosionInfo.m_name_crc_str); //Todo: Need to make a wrapper for this so the range isn't limited to the signed range.
		ImGui::InputFloat("Radius", &CustomExplosionInfo.m_radius);
		ImGui::InputFloat("Secondary radius", &CustomExplosionInfo.m_secondary_radius);
		ImGui::InputFloat("Knockdown radius", &CustomExplosionInfo.m_knockdown_radius);
		ImGui::InputFloat("Flinch radius", &CustomExplosionInfo.m_flinch_radius);
		ImGui::InputFloat("AI sound radius", &CustomExplosionInfo.m_ai_sound_radius);
		ImGui::InputInt("Human min damage hitpoints", (int*)&CustomExplosionInfo.m_human_min_damage_hitpoints);
		ImGui::InputInt("Human max damage hitpoints", (int*)&CustomExplosionInfo.m_human_max_damage_hitpoints);
		ImGui::InputInt("Vehicle min damage hitpoints", (int*)&CustomExplosionInfo.m_vehicle_min_damage_hitpoints);
		ImGui::InputInt("Vehicle max damage hitpoints", (int*)&CustomExplosionInfo.m_vehicle_max_damage_hitpoints);
		ImGui::InputFloat("Player damage multiplier", &CustomExplosionInfo.player_damage_mult);
		ImGui::InputFloat("Player vehicle damage multiplier", &CustomExplosionInfo.player_veh_damage_mult);
		ImGui::InputFloat("Player vehicle impulse multiplier", &CustomExplosionInfo.player_vehicle_impulse_mult);
		ImGui::InputFloat("Impulse magnitude", &CustomExplosionInfo.m_impulse_magnitude);
		ImGui::InputInt("Structural damage", &CustomExplosionInfo.m_structural_damage);

		ImGui::InputInt("Expanding explosion duration", (int*)&CustomExplosionInfo.expanding_explosion_duration);
		ImGui::InputInt("Expanding explosion delay", (int*)&CustomExplosionInfo.expanding_explosion_delay);
		ImGui::InputInt("Number of effects", (int*)&CustomExplosionInfo.m_num_effects);
		ImGui::InputInt("Effect 0", (int*)&CustomExplosionInfo.m_effects[0]);
		ImGui::InputInt("Effect 1", (int*)&CustomExplosionInfo.m_effects[1]);
		ImGui::InputInt("Effect 2", (int*)&CustomExplosionInfo.m_effects[2]);
		ImGui::InputInt("Effect 3", (int*)&CustomExplosionInfo.m_effects[3]);
		ImGui::InputInt("Number of material effects", (int*)&CustomExplosionInfo.m_num_material_effects);
		ImGui::InputInt("Material effect 0", (int*)&CustomExplosionInfo.m_material_effects[0]);
		ImGui::InputInt("Material effect 1", (int*)&CustomExplosionInfo.m_material_effects[1]);
		ImGui::InputInt("Material effect 2", (int*)&CustomExplosionInfo.m_material_effects[2]);
		ImGui::InputInt("Material effect 3", (int*)&CustomExplosionInfo.m_material_effects[3]);
		ImGui::InputInt("Material effect 4", (int*)&CustomExplosionInfo.m_material_effects[4]);
		ImGui::InputInt("Material effect 5", (int*)&CustomExplosionInfo.m_material_effects[5]);
		ImGui::InputInt("Material effect 6", (int*)&CustomExplosionInfo.m_material_effects[6]);
		ImGui::InputInt("Material effect 7", (int*)&CustomExplosionInfo.m_material_effects[7]);
		//Material reference array

		ImGui::Text("Salvage material type:");
		ImGui::RadioButton("Invalid Material", (int*)&CustomExplosionInfo.salvage_material, INVALID_SALVAGE_MATERIAL);
		ImGui::SameLine();
		ImGui::RadioButton("Metal", (int*)&CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_METAL);
		ImGui::SameLine();
		ImGui::RadioButton("Ore", (int*)&CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_ORE);
		ImGui::SameLine();
		ImGui::RadioButton("Chemical", (int*)&CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_CHEMICAL);

		ImGui::InputInt("Salvage max pieces", &CustomExplosionInfo.salvage_max_pieces);
		ImGui::InputFloat("Salvage probability", &CustomExplosionInfo.salvage_probability);
		ImGui::InputInt("Time between breaks", &CustomExplosionInfo.time_between_breaks);
		ImGui::InputFloat("Half angle dot", &CustomExplosionInfo.half_angle_dot);
		ImGui::InputFloat("Blast decal radius", &CustomExplosionInfo.blast_decal_radius);
		//camera_shake_type[32]
		ImGui::InputFloat("Camera shake multiplier", &CustomExplosionInfo.camera_shake_multiplier);
		ImGui::InputFloat("Camera shake falloff", &CustomExplosionInfo.camera_shake_falloff);
		ImGui::Checkbox("Ignore orientation", &CustomExplosionInfo.ignore_orientation);
		ImGui::Checkbox("Always ragdoll", &CustomExplosionInfo.always_ragdoll);
	}

	ImGui::End();
}