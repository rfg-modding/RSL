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

	if (ImGui::Button("Toggle Hud"))
	{
		ToggleHud();
	}
	if (ImGui::Button("Toggle Fog"))
	{
		ToggleFog();
	}

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
	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat("Player max speed", &CustomPlayerMaxSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player max move speed checkbox", &NeedCustomMaxMoveSpeedSet);

	if (ImGui::Button("Print all zone names"))
	{
		if (GlobalRfgWorldPtr)
		{
			std::cout << "\nPrinting all world zone names...";
			for (int i = 0; i < GlobalRfgWorldPtr->num_territory_zones; i++)
			{
				if (GlobalRfgWorldPtr->global_zone_grid[i] != nullptr && GlobalRfgWorldPtr->global_zone_grid[i] != NULL)
				{
					std::cout << "Index: " << i << ", Zone name: " << GlobalRfgWorldPtr->global_zone_grid[i]->name << "\n";
				}
				else
				{
					std::cout << "The zone pointer at index " << i << " is null\n";
				}
			}
		}
		else
		{
			Logger::Log("Could not print zone names, the world pointer is null!", LogError);
		}
	}
	if (ImGui::Button("Print misc world values"))
	{
		std::cout << "\nPrinting all misc world values...";
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
			Logger::Log("Could not print misc world values, the world pointer is null!", LogError);
		}
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
	ImGui::End();
}