#include "TeleportGui.h"

TeleportGui::TeleportGui(bool* OpenState_, std::string Title_)
{
	OpenState = OpenState_;
	Title = Title_;

	LoadTeleportLocations();

	WindowFlags = 0;
	//WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	///WindowFlags |= ImGuiWindowFlags_MenuBar;
	//WindowFlags |= ImGuiWindowFlags_NoMove;
	//WindowFlags |= ImGuiWindowFlags_NoResize;
	///WindowFlags |= ImGuiWindowFlags_NoCollapse;
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

void TeleportGui::Draw()
{
	if (!*OpenState)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(700.0f, 800.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), OpenState, WindowFlags))
	{
		ImGui::End();
		return;
	}
	if (!PlayerPtr)
	{
		ImGui::Text("Player pointer is null. Please load a save and try to re-opening this.");
		ImGui::End();
		return;
	}

	//ImGui::Text("Teleport:"); 
	//ImGui::SameLine(); ShowHelpMarker("Works in vehicles and out.");
	//ImGui::Checkbox("Use unsafe teleport", &UseUnsafeTeleport);
	//ImGui::Checkbox("Allow safe teleport fail", &AllowSafeTeleportFail);
	//ImGui::InputFloat("Safe teleport placement range: ", &SafeTeleportPlacementRange, 1.0, 5.0, 3);
	static bool NameAlreadyUsedWarning = false;

	//ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Manual:");
	ImGui::PopFont();
	ImGui::Separator();

	//ImGui::Separator();
	ImGui::Text("Current player position: ");
	ImGui::SameLine();
	std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
	ImGui::TextColored(Globals::SecondaryTextColor, PlayerPositionString.c_str());

	ImGui::Text("New player position:"); ImGui::SameLine();
	ImGui::SetNextItemWidth(232.0f);
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
	Util::Gui::TooltipOnPrevious("This will teleport the player to the value's you've typed, even if they are out of bounds. When setting TP points for later, try to set the y value a bit higher. If the game doesn't load quick enough your player will fall through the map. Usually the game will pull them back up, but sometimes it fails.");
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
			ImGui::TextColored(Globals::ColorRed, "Name already used!");
		}
		ImGui::Text("Position:");
		ImGui::SetNextItemWidth(232.0f);
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
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Saved locations:");
	ImGui::PopFont();
	ImGui::Separator();
	ImGui::Text("Credit to TimeFlier for many of the default locations.");
	try
	{
		for (auto i : TeleportLocations)
		{
			if (ImGui::Button(i["Name"].get<std::string>().c_str()))
			{
				HumanTeleportUnsafe(PlayerPtr, vector(i["Position"][0].get<float>(), i["Position"][1].get<float>(), i["Position"][2].get<float>()), PlayerPtr->Orientation);
			}
			Util::Gui::TooltipOnPrevious(std::string(i["TooltipDescription"].get<std::string>() 
				+ std::string(" Position: (") + Globals::to_string_precise(i["Position"][0].get<float>())
				+ std::string(", ") + Globals::to_string_precise(i["Position"][1].get<float>())
				+ std::string(", ") + Globals::to_string_precise(i["Position"][2].get<float>()) + std::string(")")).c_str());
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
				ImGui::SetNextItemWidth(232.0f);
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
				std::cout << "Name after exiting modal: " << i["Name"] << "\n";
				i["Name"] = NewTeleportName;
				ShowName = false;
			}*/
		}
	}
	catch (std::exception& Exception)
	{
		Logger::Log("Exception while drawing teleport menu!", LogFatalError);
		Logger::Log(Exception.what(), LogFatalError);
	}
	catch (...)
	{
		Logger::Log("Unknown exception while drawing teleport menu!", LogFatalError);
	}
	
	Util::Gui::TooltipOnPrevious("Manual and preset teleport controls for the player. Works in vehicles.");
	ImGui::End();
}

bool TeleportGui::LoadTeleportLocations()
{
	std::string ExePath = Globals::GetEXEPath(false);
	Logger::Log("Started loading \"Teleport Locations.json\".", LogInfo);

	if (fs::exists(ExePath + "RSL/Settings/Teleport Locations.json"))
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("Parsing \"Teleport Locations.json\"...", LogInfo);
			std::ifstream Config(ExePath + "RSL/Settings/Teleport Locations.json");
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
			Globals::CreateDirectoryIfNull(ExePath + "RSL/Settings/");

			SetTeleportLocation("Parker - Tutorial Area", -2328.29f, 30.0f, -2317.9f, "Tutorial area at the start of the game.");
			SetTeleportLocation("Parker - Safehouse", -1877.77f, 23.0f, -1452.0f, "Game starting safehouse. Near ore processing plant.");
			SetTeleportLocation("Parker - Abandoned Safehouse", -1813.3, 22.0, -1159.4, "Abandoned red faction safehouse in Parker.");
			SetTeleportLocation("Parker - Sand Sifter Factory", -1833.5, 21.0, -1250.1, "Next to an ore collecting funnel and across the road from several large gas tanks.");
			SetTeleportLocation("Parker - Ore Processing Plant", -1625.1, 38.0, -1178.3, "A restricted EDF target with two smokestacks and a building. EDF vehicles are usually parked here.");
			SetTeleportLocation("Parker - Mountain", -1736.6, 90.0, -1323.6, "On top of a mountain in Dust overlooking the small town of Red Rock.");
			SetTeleportLocation("Dust - Safehouse (North)", -387.0f, 38.0f, -820.0f, "Near tharsis point wind farm and Dust town hall.");
			SetTeleportLocation("Dust - Safehouse (South)", -113.59f, 30.0f, -2449.58f, "Near chemical plant.");
			SetTeleportLocation("Dust - Quarry", -887.1f, -20.0f, -1249.2f, "Inside the quarry. Includes several storage buildings with explosions and a large mining excavator.");
			SetTeleportLocation("Dust - Town of Dust", 211.5f, 33.0f, -1428.8f, "On a hill overlooking the town of Dust. Has several stores, a bar, a prison, and medical clinic.");
			SetTeleportLocation("Dust - Windfarm", -244.5f, 74.0f, -224.5f, "The center of the Windfarm in northern Dust. Several windmills and EDF guard towers.");
			SetTeleportLocation("Dust - Town Hall", 206.2f, 55.0f, -695.4f, "Outside of the EDF controlled Dust Town Hall.");
			SetTeleportLocation("Dust - EDF Executive Housing", 0.770f, 70.0f, -1196.61f, "On a hill overlooking a housing complex used by EDF officers. The area below is restricted.");
			SetTeleportLocation("Dust - Chemical Depot", -208.6f, 3.0f, -2298.3f, "Entrance of the chemical depot in Dust. Has several offices, a workers apartment, and many gas tanks.");
			SetTeleportLocation("Dust - Mohole", -801.7f, 71.0f, -589.6f, "Next to the small mohole in dust. In a restricted area.");
			SetTeleportLocation("Dust - Mountain", -125.3f, 135.0f, -1147.4f, "Top of a large mountain/ridge in Dust.");
			SetTeleportLocation("Badlands - Safehouse (RF HQ)", 2411.90f, 58.0f, -239.77f, "Main safehouse in Badlands. Also the HQ of the Red Faction.");
			SetTeleportLocation("Badlands - Safehouse (Marauder)", 2458.47f, 58.0f, -1210.17f, "Safehouse in marauder territory. Unless you want hostile marauders, wait until you've completed certain missions to go here.");
			SetTeleportLocation("Badlands - EDF Outpost", 1133.3f, -3.0f, -313.6f, "The big one.");
			SetTeleportLocation("Badlands - Mohole", 1420.27f, -32.0f, -734.28f, "Big 'ol hole in the ground used to pull heat from Mars' core for terraforming purposes. There's a smaller one in Dust.");
			SetTeleportLocation("Badlands - Harrington Memorial Bridge", 948.14f, -5.0f, -417.68f, "The big one.");
			SetTeleportLocation("Badlands - EDF Barracks", 899.91f, 2.0f, -885.64f, "EDF Barracks sitting in a hilly area south of the EDF airbase in Badlands.");
			SetTeleportLocation("Badlands - Marauder Territory", 1072.0f, 3.0f, -1366.0f, "Entrance to a Marauder base.");
			SetTeleportLocation("Badlands - Ultor Ruins", 1279.9f, 20.0f, -1448.6f, "Large abandoned Ultor ruins in Marauder territory.");
			SetTeleportLocation("Badlands - Irradiated Zone", 1685.5f, 28.0f, -1093.9f, "In the middle of the irradiated zone.");
			SetTeleportLocation("Badlands - Old Coot", 1496.9f, -12.0f, -766.7f, "Old coots shack next to the Mohole.");
			SetTeleportLocation("Badlands - Mars Rover", 2100.8f, 29.0f, -484.8f, "The mars rover easter egg.");
			SetTeleportLocation("Oasis - Safehouse", 1434.29f, 18.0f, 691.65f, "Near EDF vehicle depot.");
			SetTeleportLocation("Oasis - Residential District", 1728.2f, 17.0f, 211.38f, "Residential area of Oasis. Has several apartment buildings and gas stations.");
			SetTeleportLocation("Oasis - Industrial District", 176.5f, 33.0f, 777.0f, "In the middle of the Industrial District of Oasis. Has several smokestacks and factories.");
			SetTeleportLocation("Oasis - EDF Barracks", 916.2f, 23.0f, 240.7f, "Outside of an EDF Barracks in Oasis, near the Arc Reactor.");
			SetTeleportLocation("Oasis - Reactor Core", 640.4f, 50.0f, 384.7f, "On a hillside overlooking the Arc Reactor.");
			SetTeleportLocation("Free Fire Zone - Minor Safehouse", -1908.5f, 25.0f, -779.2f, "Abandoned EDF base in the free fire zone. Manned by guerrilla fighters.");
			SetTeleportLocation("Free Fire Zone - Artillery Border (South)", -1606.6f, 0.0f, -785.9f, "Southern border of the artillery kill zone. Next to the EDF border checkpoint.");
			SetTeleportLocation("Free Fire Zone - Artillery Border (North)", -1813.5f, 5.0f, -250.2f, "Northern border of the artillery kill zone. Next to the bridge.");
			SetTeleportLocation("Free Fire Zone - Artillery Base", -1752.03f, 9.0f, -132.59f, "Base which runs and protects the EDF Artillery Gun. Deadly to be here until the FFZ has been liberated.");
			SetTeleportLocation("Free Fire Zone - Artillery Gun", -1944.92f, 38.0f, -65.49f, "Bottom of the EDF Artillery Gun. Deadly to be here until the FFZ has been liberated.");
			SetTeleportLocation("EOS - Safehouse (West)", -1726.0f, 44.0f, 438.0f, "Near FFZ entrance/exit and Eos Memorial Bridge.");
			SetTeleportLocation("EOS - Safehouse (East)", -1390.95f, 30.0f, 561.08f, "Near construction site.");
			SetTeleportLocation("EOS - South Border", -1714.9f, 18.0f, 22.8f, "Border of EOS and the Free Fire Zone");
			SetTeleportLocation("EOS - Residential District", -1753.4f, -2.0f, 764.0f, "Residential area north of the western EOS safehouse. Has two apartment buildings, two bridges, and a EDF monument.");
			SetTeleportLocation("EOS - Martian Council", -1174.7f, 17.0f, 1386.5f, "Martian Council building in northern EOS. The EDF are hostile here.");
			SetTeleportLocation("EOS - Outside EDF Central Command", -1428.61f, 5.0f, 2013.5f, "Right outside the defense shield.");
			SetTeleportLocation("EOS - Inside EDF Central Command", -1458.75f, 5.0f, 2050.16f, "Right inside past the defense shield.");
			SetTeleportLocation("EOS - EDF Central Command Main Building", -1474.53f, 27.0f, 2397.49f, "The final building at the peak of the inner valley / cliffsides.");
			SetTeleportLocation("Mount Vogel - Border", -1017.1f, 6.0f, 2474.3f, "Border of Mount Vogel and EOS");
			SetTeleportLocation("Mount Vogel - Base", -670.37f, 47.0f, 2423.75f, "Bottom of Mount Vogel and mass accelerator. Several old buildings.");
			SetTeleportLocation("Mount Vogel - Peak", -285.77f, 183.0f, 2423.4f, "Peak of Mount Vogel with mass accelerator exit.");
			SetTeleportLocation("Map Center (OUT OF BOUNDS)", -1.719f, 117.0f, -1.348f, "Center of the game map. Out of bounds, so make sure that you have infinite jetpack on so you don't fall through the map.");
			SetTeleportLocation("Dust - Crater Grounds (OUT OF BOUNDS)", -1.677f, 60.0f, -2386.9f, "Area south of dust overlooking the crater grounds. Be careful not to fall out of the map.");

			std::ofstream ConfigOutput(ExePath + "RSL/Settings/Teleport Locations.json");
			ConfigOutput << std::setw(4) << TeleportLocations << "\n";
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
		const std::string ExePath = Globals::GetEXEPath(false);
		Globals::CreateDirectoryIfNull(ExePath + "RSL/Settings/");

		std::ofstream ConfigOutput(ExePath + "RSL/Settings/Teleport Locations.json");
		ConfigOutput << std::setw(4) << TeleportLocations << "\n";
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
	for (auto& TeleportLocation : TeleportLocations)
	{
		if (TeleportLocation["Name"] == Name)
		{
			return false;
			break;
		}
	}
	const size_t Index = TeleportLocations.size();
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