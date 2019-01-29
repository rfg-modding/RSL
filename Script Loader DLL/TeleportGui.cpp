#include "TeleportGui.h"

TeleportGui::TeleportGui()
{

}

TeleportGui::~TeleportGui()
{

}

void TeleportGui::Initialize(bool* _OpenState)
{
	OpenState = _OpenState;

	LoadTeleportLocations();

	WindowFlags = 0;
	//WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	WindowFlags |= ImGuiWindowFlags_MenuBar;
	//WindowFlags |= ImGuiWindowFlags_NoMove;
	//WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	ModalFlags = 0;
	//ModalFlags |= ImGuiWindowFlags_NoTitleBar;
	//ModalFlags |= ImGuiWindowFlags_NoScrollbar;
	//ModalFlags |= ImGuiWindowFlags_MenuBar;
	//ModalFlags |= ImGuiWindowFlags_NoMove;
	ModalFlags |= ImGuiWindowFlags_NoResize;
	ModalFlags |= ImGuiWindowFlags_NoCollapse;
	//ModalFlags |= ImGuiWindowFlags_NoNav;
	//ModalFlags |= ImGuiWindowFlags_NoBackground;
	//ModalFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	NewTeleportName = "";
	NewTeleportPosition.x = 0.0f;
	NewTeleportPosition.y = 0.0f;
	NewTeleportPosition.z = 0.0f;
	NewTeleportDescription = "";
}

void TeleportGui::Draw(const char* Title, bool UseSeparateWindow)
{
	if (UseSeparateWindow)
	{
		if (!ImGui::Begin(Title, OpenState, WindowFlags))
		{
			ImGui::End();
			return;
		}
	}

	if (ImGui::CollapsingHeader("Teleport"))
	{
		//ImGui::Text("Teleport:"); 
		//ImGui::SameLine(); ShowHelpMarker("Works in vehicles and out.");
		//ImGui::Checkbox("Use unsafe teleport", &UseUnsafeTeleport);
		//ImGui::Checkbox("Allow safe teleport fail", &AllowSafeTeleportFail);
		//ImGui::InputFloat("Safe teleport placement range: ", &SafeTeleportPlacementRange, 1.0, 5.0, 3);
		static bool NameAlreadyUsedWarning = false;
		ImGui::Text("Manual:");
		//ImGui::Separator();
		ImGui::Text("Current player position: ");
		ImGui::SameLine();
		std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
		ImGui::TextColored(SecondaryTextColor, PlayerPositionString.c_str());

		ImGui::Text("New player position:"); ImGui::SameLine();
		ImGui::PushItemWidth(232.0f);
		ImGui::InputFloat3("##Player Position Target", PlayerPositionTargetArray, 3);
		ImGui::SameLine();
		if (ImGui::Button("Sync##PlayerPositionTarget"))
		{
			PlayerPositionTargetArray[0] = PlayerPtr->Position.x;
			PlayerPositionTargetArray[1] = PlayerPtr->Position.y;
			PlayerPositionTargetArray[2] = PlayerPtr->Position.z;
		}
		ImGui::SameLine();
		if (ImGui::Button("Teleport##PlayerPositionTarget"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(PlayerPositionTargetArray[0], PlayerPositionTargetArray[1], PlayerPositionTargetArray[2]), PlayerPtr->Orientation);
		}
		Utilities::GUI::TooltipOnPrevious("This will teleport the player to the value's you've typed, even if they are out of bounds. When setting TP points for later, try to set the y value a bit higher. If the game doesn't load quick enough your player will fall through the map. Usually the game will pull them back up, but sometimes it fails.");
		ImGui::SameLine();
		if (ImGui::Button("Save as new##PlayerPositionTarget"))
		{
			ImGui::OpenPopup("Save teleport location##PlayerPositionTarget");
			NewTeleportName = "";
			NewTeleportPosition.x = PlayerPositionTargetArray[0];
			NewTeleportPosition.y = PlayerPositionTargetArray[1];
			NewTeleportPosition.z = PlayerPositionTargetArray[2];
			NewTeleportDescription = "";
		}
		if (ImGui::BeginPopupModal("Save teleport location##PlayerPositionTarget", NULL, ModalFlags))
		{
			ImGui::Text("Name:");
			ImGui::InputText("##TeleportEditNamePlayerPositionTarget", &NewTeleportName);
			if (NameAlreadyUsedWarning)
			{
				ImGui::SameLine();
				ImGui::TextColored(ColorRed, "Name already used!");
			}
			ImGui::Text("Position:");
			ImGui::PushItemWidth(232.0f);
			ImGui::InputFloat3("##TeleportEditPositionPlayerPositionTarget", (float*)(&NewTeleportPosition), 2);
			ImGui::Text("Tooltip description:");
			ImGui::InputTextMultiline("##TeleportEditTooltip descriptionPlayerPositionTarget", &NewTeleportDescription, ImVec2(500.0f, 350.0f));// , MainOverlayTeleportEditTextFlags);// , ImGuiInputTextFlags_CharsHexadecimal);
			if (ImGui::Button("Save##PlayerPositionTarget"))
			{
				if (SetTeleportLocation(NewTeleportName, NewTeleportPosition.x, NewTeleportPosition.y, NewTeleportPosition.z, NewTeleportDescription))
				{
					NameAlreadyUsedWarning = false;
					SaveTeleportLocations();
					ImGui::CloseCurrentPopup();
				}
				else
				{
					NameAlreadyUsedWarning = true;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel##PlayerPositionTarget"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		/*if (ImGui::Button("Sync##PlayerVelocityTarget"))
		{
			PlayerVelocityTargetArray[0] = PlayerPtr->Velocity.x;
			PlayerVelocityTargetArray[1] = PlayerPtr->Velocity.y;
			PlayerVelocityTargetArray[2] = PlayerPtr->Velocity.z;
		}
		ImGui::SameLine();
		if (ImGui::Button("Set##PlayerVelocityTarget"))
		{
			PlayerPtr->Velocity.x = PlayerVelocityTargetArray[0];
			PlayerPtr->Velocity.y = PlayerVelocityTargetArray[1];
			PlayerPtr->Velocity.z = PlayerVelocityTargetArray[2];
			NeedPlayerVelocitySet = true;
		}
		ImGui::SameLine(); ShowHelpMarker("This is always equal to the true player velocity. Haven't quite nailed down how objects are moved yet so there's only partial control for now. You can still set the velocity, but once you move out of that edit box it'll go back to the normal values.");
		*/

		ImGui::Separator();
		ImGui::Text("Saved locations:");
		try
		{
			for (auto i : TeleportLocations)
			{
				if (ImGui::Button(i["Name"].get<std::string>().c_str()))
				{
					HumanTeleportUnsafe(PlayerPtr, vector(i["Position"][0].get<float>(), i["Position"][1].get<float>(), i["Position"][2].get<float>()), PlayerPtr->Orientation);
				}
				Utilities::GUI::TooltipOnPrevious(i["TooltipDescription"].get<std::string>().c_str());
				ImGui::SameLine();
				if (ImGui::Button(std::string("Edit##" + i["Name"].get<std::string>()).c_str()))
				{
					ImGui::OpenPopup(std::string("Teleport location edit##" + i["Name"].get<std::string>()).c_str());
					TeleportEditPopupOpen = true;
					NewTeleportName = i["Name"].get<std::string>();
					NewTeleportPosition.x = i["Position"][0];
					NewTeleportPosition.y = i["Position"][1];
					NewTeleportPosition.z = i["Position"][2];
					NewTeleportDescription = i["TooltipDescription"].get<std::string>();
				}
				if (ImGui::BeginPopupModal(std::string("Teleport location edit##" + i["Name"].get<std::string>()).c_str(), NULL, ModalFlags))
				{
					ImGui::Text("Name:");
					ImGui::InputText("##TeleportEditName", &NewTeleportName);
					ImGui::Text("Position:");
					ImGui::PushItemWidth(232.0f);
					ImGui::InputFloat3("##TeleportEditPosition", (float*)(&NewTeleportPosition), 2);
					ImGui::Text("Tooltip description:");
					ImGui::InputTextMultiline("##TeleportEditTooltip description", &NewTeleportDescription, ImVec2(500.0f, 350.0f));
					if (ImGui::Button(std::string("Save##" + i["Name"].get<std::string>()).c_str()))
					{
						ChangeTeleportLocation(i["Name"], NewTeleportName, NewTeleportPosition.x, NewTeleportPosition.y, NewTeleportPosition.z, NewTeleportDescription);
						SaveTeleportLocations();
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button(std::string("Cancel##" + i["Name"].get<std::string>()).c_str()))
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				/*if (ShowName)
				{
					std::cout << "Name after exiting modal: " << i["Name"] << std::endl;
					i["Name"] = NewTeleportName;
					ShowName = false;
				}*/
			}
		}
		catch (std::exception& Exception)
		{
			Logger::Log("Exception while drawing teleport menu!", LogFatalError);
			Logger::Log(Exception.what(), LogFatalError);
			Sleep(6000);
		}
		catch (...)
		{
			Logger::Log("Unknown exception while drawing teleport menu!", LogFatalError);
		}
	}
	Utilities::GUI::TooltipOnPrevious("Manual and preset teleport controls for the player. Works in vehicles.");
	ImGui::End();
}

bool TeleportGui::LoadTeleportLocations()
{
	std::string ExePath = GetEXEPath(false);
	Logger::Log("Started loading \"Teleport Locations.json\".", LogInfo);

	if (fs::exists(ExePath + "RFGR Script Loader/Settings/Teleport Locations.json"))
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("Parsing \"Teleport Locations.json\"...", LogInfo);
			std::ifstream Config(ExePath + "RFGR Script Loader/Settings/Teleport Locations.json");
			Config >> TeleportLocations;
			Config.close();
			return true;
		}, "Teleport Locations.json", "parse", "parsing"))
		{
			return false;
		}
		Logger::Log("No parse exceptions detected.", LogInfo);
	}
	else
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("\"Teleport Locations.json\" not found. Creating from default values.", LogWarning);
			CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");

			SetTeleportLocation("Tutorial Area Hilltop", -2328.29f, 30.0f, -2317.9f, "Tutorial area at the start of the game. Position: (-2328.29, 30.0, -2317.9)");
			SetTeleportLocation("Parker - Safehouse", -1877.77f, 27.0f, -1452.0f, "Game starting safehouse. Near ore processing plant. Position: (-1877.77, 27.0, -1452.0)");
			SetTeleportLocation("Dust - Northern Safehouse", -387.0f, 38.0f, -820.0f, "Near tharsis point wind farm and Dust town hall. Position: (-387.0, 38.0, -820.0)");
			SetTeleportLocation("Dust - Southern Safehouse", -113.59f, 30.0f, -2449.58f, "Near chemical plant. Position: (-113.59, 30.0, -2449.58)");
			SetTeleportLocation("Badlands - Safehouse / RFHQ", 2411.90f, 58.0f, -239.77f, "Main safehouse in Badlands. Also the HQ of the Red Faction. Position: (2411.90, 58.0, -239.77)");
			SetTeleportLocation("Badlands - Mohole", 1420.27f, -28.0f, -734.28f, "Big 'ol hole in the ground used to pull heat from Mars' core for terraforming purposes. There's a smaller one in Dust. Position: (1420.27, -28.0, -734.28)");
			SetTeleportLocation("Badlands - Harrington Memorial Bridge", 948.14f, -5.0f, -417.68f, "The big one. Position: (948.14, -5.0, -417.68)");
			SetTeleportLocation("Badlands - EDF Barracks", 899.91f, 2.0f, -885.64f, "EDF Barracks sitting in a hilly area south of the EDF airbase in Badlands. Position: (899.91, 2.0, -885.64)");
			SetTeleportLocation("Badlands - Marauder Safehouse", 2458.47f, 58.0f, -1210.17f, "Safehouse in marauder territory. Unless you want hostile marauders, wait until you've completed certain missions to go here. Position: (2458.47, 58.0, -1210.17)");
			SetTeleportLocation("Oasis - Safehouse", 1434.29f, 18.0f, 691.65f, "Near EDF vehicle depot. Position: (1434.29, 18.0, 691.65)");
			SetTeleportLocation("Free Fire Zone - Artillery Base", -1752.03f, 9.0f, -132.59f, "Base which runs and protects the EDF Artillery Gun. Deadly to be here until the FFZ has been liberated. Position: (-1752.03, 9.0, -132.59)");
			SetTeleportLocation("Free Fire Zone - Artillery Gun", -1944.92f, 38.0f, -65.49f, "Bottom of the EDF Artillery Gun. Deadly to be here until the FFZ has been liberated. Position: (-1944.92, 38.0, -65.49)");
			SetTeleportLocation("EOS - Western Safehouse", -1726.0f, 50.0f, 438.0f, "Near FFZ entrance/exit and Eos Memorial Bridge. Position: (-1726.0, 50.0, 438.0)");
			SetTeleportLocation("EOS - Eastern Safehouse", -1390.95f, 30.0f, 561.08f, "Near construction site. Position: (-1390.95, 30.0, 561.08)");
			SetTeleportLocation("EOS - Outside EDF Central Command", -1428.61f, 8.0f, 2013.5f, "Right outside the defense shield. Position: (-1428.61, 8.0, 2013.5)");
			SetTeleportLocation("EOS - Inside EDF Central Command", -1458.75f, 8.0f, 2050.16f, "Right inside past the defense shield. Position: (-1458.75, 8.0, 2050.16)");
			SetTeleportLocation("EOS - EDF Central Command Main Building", -1474.53f, 38.0f, 2397.49f, "The final building at the peak of the inner valley / cliffsides. Position: (-1474.53, 38.0, 2397.49)");
			SetTeleportLocation("Mount Vogel - Base", -670.37f, 47.0f, 2423.75f, "Bottom of Mount Vogel and mass accelerator. Several old buildings. Position: (-670.37, 47.0, 2423.75)");
			SetTeleportLocation("Mount Vogel - Peak", -285.77f, 183.0f, 2423.4f, "Peak of Mount Vogel with mass accelerator exit. Position: (-285.77, 183.0, 2423.4)");

			std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/Teleport Locations.json");
			ConfigOutput << std::setw(4) << TeleportLocations << std::endl;
			ConfigOutput.close();
			return true;
		}, "Teleport Locations.json", "write", "writing"))
		{
			return false;
		}
		Logger::Log("No write exceptions detected.", LogInfo);
	}

	Logger::Log("Done loading \"Teleport Locations.json\".", LogInfo);
	return true;
}

bool TeleportGui::SaveTeleportLocations()
{
	Logger::Log("Started writing \"Teleport Locations.json\"", LogInfo);
	if (!JsonExceptionHandler([&]
	{
		Logger::Log("\"Teleport Locations.json\" not found. Creating from default values.", LogWarning);
		std::string ExePath = GetEXEPath(false);
		CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");

		std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/Teleport Locations.json");
		ConfigOutput << std::setw(4) << TeleportLocations << std::endl;
		ConfigOutput.close();

		return true;
	}, "Teleport Locations.json", "write", "writing"))
	{
		return false;
	}
	Logger::Log("No write exceptions detected.", LogInfo);

	Logger::Log("Done writing \"Teleport Locations.json\"", LogInfo);
	return true;
}

bool TeleportGui::SetTeleportLocation(std::string Name, float x, float y, float z, std::string Description)
{
	for (size_t i = 0; i < TeleportLocations.size(); i++)
	{
		if (TeleportLocations[i]["Name"] == Name)
		{
			return false;
			break;
		}
	}
	size_t Index = TeleportLocations.size();
	TeleportLocations[Index]["Name"] = Name;
	TeleportLocations[Index]["Position"][0] = x;
	TeleportLocations[Index]["Position"][1] = y;
	TeleportLocations[Index]["Position"][2] = z;
	TeleportLocations[Index]["TooltipDescription"] = Description;
	return true;
}

bool TeleportGui::ChangeTeleportLocation(std::string CurrentName, std::string NewName, float NewX, float NewY, float NewZ, std::string NewDescription)
{
	int Index = -1;
	for (size_t i = 0; i < TeleportLocations.size(); i++)
	{
		if (TeleportLocations[i]["Name"] == CurrentName)
		{
			Index = i;
			break;
		}
	}
	if (Index < 0)
	{
		return false;
	}
	TeleportLocations[Index]["Name"] = NewName;
	TeleportLocations[Index]["Position"][0] = NewX;
	TeleportLocations[Index]["Position"][1] = NewY;
	TeleportLocations[Index]["Position"][2] = NewZ;
	TeleportLocations[Index]["TooltipDescription"] = NewDescription;
	return true;
}