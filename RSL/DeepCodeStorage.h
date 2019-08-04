#pragma once
/*Random snippets of code which may be useful in the future go here. Mostly
experimental stuff that was removed for better code clarity.*/




/* Content removed from the tweaks menu starts here: */

    //Doesn't work quite yet, couldn't properly grab the players rigid body.
    //ImGui::Separator();
    //ImGui::Text("Player rigid body");
    //ImGui::Separator();
    //ImGui::PushItemWidth(230.0f);
    //ImGui::InputFloat3("Linear impulse to apply", (float*)&CustomPlayerImpulseApply, 3);
    //if(GlobalPlayerRigidBody)
    //{
    //	ImGui::PushItemWidth(230.0f);
    //	ImGui::InputFloat("Friction", &GlobalPlayerRigidBody->m_material.m_friction);
    //	ImGui::PushItemWidth(230.0f);
    //	ImGui::InputFloat("Restitution", &GlobalPlayerRigidBody->m_material.m_restitution);
    //	if (ImGui::Button("Apply impulse by hkpRigidBody*"))
    //	{
    //		HavokBodyApplyLinearImpulseA(GlobalPlayerRigidBody, &CustomPlayerImpulseApply);
    //	}
    //}
    //else
    //{
    //	ImGui::Text("Player rigid body pointer is null! Can't display gui section.");
    //}
    //if (ImGui::Button("Apply impulse by handle"))
    //{
    //	HavokBodyApplyLinearImpulseB(PlayerPtr->Handle, &CustomPlayerImpulseApply);
    //}
    //if (ImGui::Button("Apply impulse by havok handle"))
    //{
    //	HavokBodyApplyLinearImpulseB(PlayerPtr->HavokHandle, &CustomPlayerImpulseApply);
    //}
    //ImGui::Separator();

/*
    ImGui::InputInt("Unlimited ammo", &CustomUnlimitedAmmo);
    ImGui::InputFloat("Stealth percent", &CustomStealthPercent);
    ImGui::InputFloat("Render alpha", &CustomRenderAlpha);
    ImGui::Checkbox("Temp use customs", &TempUseCustoms);*/
    /*if (ImGui::Checkbox("Unlimited ammo", &UnlimitedAmmo))
    {
        PlayerPtr->PFlags.UnlimitedAmmo = true;
    }
    else
    {
        PlayerPtr->PFlags.UnlimitedAmmo = false;
    }*/

    //ImGui::InputInt("District hash", (int*)&PlayerPtr->Metadata.DistrictHash);
    //ImGui::InputInt("District time", &PlayerPtr->Metadata.DistrictTime);
    //ImGui::InputInt("Upgrades array", &PlayerPtr->Metadata.upgrades);
    //ImGui::InputInt("Play time", &PlayerPtr->Metadata.PlayTime);
    //ImGui::InputInt("Last death time", &PlayerPtr->Metadata.LastDeathTime);
/*
    if (ImGui::CollapsingHeader("Upgrades array"))
    {
        for (int i = 0; i < 128; i++)
        {
            ImGui::Text(std::string("Index" + std::to_string(i)).c_str());
            ImGui::PushItemWidth(300.0f);
            ImGui::InputInt("Current level (0 to 255)", (int*)&PlayerPtr->Metadata.upgrades[i].current_level);
            ImGui::PushItemWidth(300.0f);
            ImGui::InputInt("Availability bitfield (0 to 65,535)", (int*)&PlayerPtr->Metadata.upgrades[i].availability_bitfield);
            ImGui::PushItemWidth(300.0f);
            ImGui::InputInt("Unlocked notified bitfield (0 to 65,535)", (int*)&PlayerPtr->Metadata.upgrades[i].unlocked_notified_bitfield);
            ImGui::PushItemWidth(300.0f);
            ImGui::InputInt("New notified bitfield (0 to 65,535)", (int*)&PlayerPtr->Metadata.upgrades[i].new_notified_bitfield);
        }
    }*/

    //ImGui::Text("Code driven jump height:"); ImGui::SameLine();
    //ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CodeDrivenJumpHeight).c_str());

        /*if (ImGui::CollapsingHeader("Repair sphere"))
    {
        ImGui::Checkbox("Spawn repair sphere with middle mouse?", &MiddleMouseRepairSphereActive);
        ImGui::InputFloat("Radius", &RepairRadius);
        ImGui::InputInt("Duration", &RepairDuration);

        ImGui::Text("Spawn position:");
        ImGui::RadioButton("Player position", &RepairPosition, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Aim position", &RepairPosition, 1);
    }
    ImGui::Separator();*/

    /*
     *
     * 	ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Experimental settings:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Info dumps"))
	{
		//all_zones and global_zone_grid in rfg::world are always empty. 
		static int ZoneScanRange = 2000;
		ImGui::InputInt("Zone scan range", &ZoneScanRange);
		ImGui::SameLine();
		Util::Gui::ShowHelpMarker("Only used by the first 2 buttons below this. A working list of zones in the games memory hasn't been found yet, so instead, a function that grabs zones by index is used to check every zone in this range. 2000 seems to be a good default, and setting it higher I never found any more zones.");
		static float CustomMinWindSpeed = 0.0f;
		static float CustomMaxWindSpeed = 0.0f;
		ImGui::InputFloat("Custom min wind speed", &CustomMinWindSpeed);
		ImGui::InputFloat("Custom max wind speed", &CustomMaxWindSpeed);
		if (ImGui::Button("Set all zone wind speeds"))
		{
			if (Globals::RfgWorldPtr)
			{
				int ValidWorldZoneCount = 0;
				int ValidObjectZoneCount = 0;
				for (int i = 0; i < ZoneScanRange; i++)
				{
					world_zone* CurrentWorldZone = GetWorldZoneByIndex(Globals::RfgWorldPtr, NULL, i);
					if (CurrentWorldZone)
					{
						ValidWorldZoneCount++;
						if (CurrentWorldZone->zone_objp)
						{
							ValidObjectZoneCount++;
							CurrentWorldZone->zone_objp->wind_min_speed = CustomMinWindSpeed;
							CurrentWorldZone->zone_objp->wind_max_speed = CustomMaxWindSpeed;
						}
					}
				}
				Logger::Log("Done setting zone wind speeds\n");
				Logger::Log("# of valid world zones: {}\n", ValidWorldZoneCount);
				Logger::Log("# of valid object zones: {}\n", ValidObjectZoneCount);
			}
		}
		ImGui::SameLine();
		Util::Gui::ShowHelpMarker("Sets the min and max wind speed values you've chosen in any zones it finds in the range you've chosen. Added for experimentation. I haven't see any changes from this.");

		if (ImGui::Button("Dump zone info"))
		{
			if (Globals::RfgWorldPtr)
			{
				int NumberOfWorldZonesFound = 0;
				int NumberOfObjectZonesFound = 0;
				std::ofstream ZoneDump(Globals::GetEXEPath(false) + "RSL/ZoneInfoDump.txt", std::ios_base::trunc);
				ZoneDump << "\nPrinting all world zone names...\n";
				Logger::Log("\nPrinting all world zone names...\n");
				for (int i = 0; i < ZoneScanRange; i++)
				{
					world_zone* CurrentWorldZone = GetWorldZoneByIndex(Globals::RfgWorldPtr, NULL, i);
					if (CurrentWorldZone)
					{
						NumberOfWorldZonesFound++;
						ZoneDump << "Index: " << i << "\n";
						ZoneDump << "Zone name: " << CurrentWorldZone->name << "\n";
						ZoneDump << "srid: " << CurrentWorldZone->srid << "\n";
						ZoneDump << "gid: " << CurrentWorldZone->gid << "\n";
						ZoneDump << "Border zone: " << CurrentWorldZone->is_border_zone << "\n";
						if (CurrentWorldZone->zone_objp)
						{
							NumberOfObjectZonesFound++;
							ZoneDump << "Object zone:\n";
							ZoneDump << "    All index: " << CurrentWorldZone->zone_objp->AllIndex << "\n";
							ZoneDump << "    Min wind speed: " << CurrentWorldZone->zone_objp->wind_min_speed << "\n";
							ZoneDump << "    Max wind speed: " << CurrentWorldZone->zone_objp->wind_max_speed << "\n";
							ZoneDump << "    Handle: " << CurrentWorldZone->zone_objp->Handle << "\n";
							ZoneDump << "    Havok handle: " << CurrentWorldZone->zone_objp->HavokHandle << "\n";
							ZoneDump << "    Terrain filename: " << CurrentWorldZone->zone_objp->terrain->filename << "\n\n";
						}
						else
						{
							ZoneDump << "--Invalid object zone--\n\n";
						}
					}
				}
				Logger::Log("Done printing all world zone info. Check ZoneInfoDump.txt in the script loader folder.\n");
				Logger::Log("Number of world zones found: {}\n", NumberOfWorldZonesFound);
				Logger::Log("Number of object zones found: {}\n", NumberOfObjectZonesFound);
				ZoneDump << "Done printing all world zone info\n";
				ZoneDump << "Number of zones found: " << NumberOfWorldZonesFound;
				ZoneDump << "Number of zones found: " << NumberOfObjectZonesFound;
			}
			else
			{
				Logger::LogError("Could not print zone names, the world pointer is null!\n");
			}
		}
		ImGui::SameLine();
		Util::Gui::ShowHelpMarker("Prints info about the any world_zones it finds to ZoneInfoDump.txt. Many zone indices don't have a valid zone, and so the range set above is scanned through and only valid zones are printed to the file.");
		ImGui::Separator();

		if (ImGui::Button("Print misc world values"))
		{
			std::cout << "\nPrinting all misc world values...\n";
			std::ofstream WorldDump(Globals::GetEXEPath(false) + "RSL/WorldInfoDump.txt", std::ios_base::trunc);
			if (Globals::RfgWorldPtr)
			{
				WorldDump << "Max world objects: " << Globals::RfgWorldPtr->max_world_objects << "\n";
				WorldDump << "Tech level: " << Globals::RfgWorldPtr->tech_level << "\n";
				WorldDump << "Tech level max: " << Globals::RfgWorldPtr->tech_level_max << "\n";
				WorldDump << "Pending filename: " << Globals::RfgWorldPtr->pending_filename << "\n";
				WorldDump << "Object list capacity: " << Globals::RfgWorldPtr->all_objects.Capacity() << "\n";
				WorldDump << "Object list size: " << Globals::RfgWorldPtr->all_objects.Size() << "\n";
				WorldDump << "Num territory zones: " << Globals::RfgWorldPtr->num_territory_zones << "\n";
			}
			else
			{
				WorldDump << "Could not print misc world values, the world pointer is null!\n";
				Logger::LogError("Could not print misc world values, the world pointer is null!\n");
			}
			std::cout << "Done!\n";
		}
		ImGui::SameLine();
		Util::Gui::ShowHelpMarker("Prints info about the rfg world to WorldInfoDump.txt. Much shorter than the other info dumps.");

        static bool OnlyDumpNamedObjects = false;
        ImGui::Checkbox("Only dump named objects", &OnlyDumpNamedObjects);
		if (ImGui::Button("Dump all object info"))
		{
			if (Globals::RfgWorldPtr)
			{
				Globals::CreateDirectoryIfNull(Globals::GetEXEPath(false) + "RSL/Info dumps/");
				Globals::CreateDirectoryIfNull(Globals::GetEXEPath(false) + "RSL/Info dumps/Object info dumps/");
				/*std::string DumpFileName = Logger::GetTimeString(false);
				DumpFileName = DumpFileName.substr(1, DumpFileName.size() - 2);
				DumpFileName += ".txt";
				for (auto& i : DumpFileName)
				{
					if (i == '/' || i == '\\')
					{
						i = '-';
					}
					if (i == ':')
					{
						i = '\0';
					}
				}*/
//std::string DumpFileName = "ObjectInfoDump - ";
//DumpFileName += std::to_string(time(NULL));
//DumpFileName += ".txt";
//std::cout << "Dump file name: " << DumpFileName << "\n";
//std::cout << "Dump file path: " << Globals::GetEXEPath(false) + "RSL/Info dumps/Object info dumps/" + DumpFileName << "\n";
//Logger::Log("\nDumping all object info to /RSL/Info dumps/Object info dumps/{}.\n", DumpFileName);
//std::ofstream PositionsDump(Globals::GetEXEPath(false) + "RSL/Info dumps/Object info dumps/" + DumpFileName.c_str(), std::ios_base::trunc);
//PositionsDump << "Start of object info dump...\n";
//PositionsDump << "Objects array capacity: " << Globals::RfgWorldPtr->all_objects.Capacity() << "\n";
//PositionsDump << "Objects array objects contained: " << Globals::RfgWorldPtr->all_objects.Size() << "\n";
////PositionsDump << "Sector name: " << Globals::RfgWorldPtr->territory_name << "\n\n";
//
//for (int i = 0; i < Globals::RfgWorldPtr->all_objects.Size(); i++)
//{
//    if (Globals::RfgWorldPtr->all_objects[i])
//    {
//        const char* TempName = WorldGetObjectName(Globals::RfgWorldPtr, NULL, Globals::RfgWorldPtr->all_objects[i]);
//        std::string ObjectName(TempName);
//        if (OnlyDumpNamedObjects)
//        {
//            if (TempName == nullptr || ObjectName.length() < 3)
//            {
//                break;
//            }
//        }
//        PositionsDump << "Index: " << i << "\n";
//        PositionsDump << "Name: " << ObjectName << "\n";
//        PositionsDump << "Type: " << (int)(*Globals::RfgWorldPtr->all_objects[i]).ObjectType << "\n"; //Todo: Add type name string
//        PositionsDump << "Subtype: " << (int)(*Globals::RfgWorldPtr->all_objects[i]).SubType << "\n"; //Todo: Add subtype name string
//        PositionsDump << "Position:\n";
//        PositionsDump << "    x: " << (*Globals::RfgWorldPtr->all_objects[i]).Position.x << "\n";
//        PositionsDump << "    y: " << (*Globals::RfgWorldPtr->all_objects[i]).Position.y << "\n";
//        PositionsDump << "    z: " << (*Globals::RfgWorldPtr->all_objects[i]).Position.z << "\n";
//
//        world_zone* ObjectWorldZone = GetWorldZoneByObjectHandle(Globals::RfgWorldPtr, NULL, (*Globals::RfgWorldPtr->all_objects[i]).Handle);
//        if (ObjectWorldZone)
//        {
//            PositionsDump << "Zone:\n";
//            PositionsDump << "    Name: " << ObjectWorldZone->name << "\n\n";
//        }
//        else
//        {
//            PositionsDump << "--Invalid world zone--\n\n";
//        }
//    }
//    else
//    {
//        PositionsDump << "Skipping object at index " << i << ", invalid pointer.\n\n";
//    }
//}
//PositionsDump << "End of object info dump.";
//Logger::Log("Finished dumped all object into to ObjectInfoDump.txt!\n");
//PositionsDump.close();
//            }
//            else
//            {
//            Logger::Log("Could not print zone names, the world pointer is null!\n");
//            }
//        }
//        ImGui::SameLine();
//        Util::Gui::ShowHelpMarker("Prints info about all rfg objects into ObjectInfoDump.txt. Overwrites data from the previous write each time.");
//    }
//
//    if (ImGui::CollapsingHeader("Time of day light")) //Todo: Add rl_scene_entity and rl_3d_entity info to this.
//    {
//        if (Globals::TODLightPtr)
//        {
//            ImGui::Text("Light type:");
//            ImGui::RadioButton("Directional", (int*)& Globals::TODLightPtr->m_light_type, LIGHT_TYPE_DIRECTIONAL);
//            ImGui::SameLine();
//            ImGui::RadioButton("Point", (int*)& Globals::TODLightPtr->m_light_type, LIGHT_TYPE_POINT);
//            ImGui::SameLine();
//            ImGui::RadioButton("Spot light", (int*)& Globals::TODLightPtr->m_light_type, LIGHT_TYPE_SPOT_LIGHT);
//            ImGui::SameLine();
//            ImGui::RadioButton("Force size of int", (int*)& Globals::TODLightPtr->m_light_type, LIGHT_TYPE_FORCE_SIZEOF_INT);
//
//            ImGui::Text("Color:");
//            ImGui::Checkbox("Use custom color", &UseCustomTimeOfDayLight);
//            Util::Gui::TooltipOnPrevious("This needs to be checked for your values to be properly set");
//            ImGui::InputFloat("Red", &CustomTimeOfDayLightColor.red, 0.01, 0.1, 3);
//            ImGui::InputFloat("Green", &CustomTimeOfDayLightColor.green, 0.01, 0.1, 3);
//            ImGui::InputFloat("Blue", &CustomTimeOfDayLightColor.blue, 0.01, 0.1, 3);
//            ImGui::InputFloat("Alpha", &CustomTimeOfDayLightColor.alpha, 0.01, 0.1, 3);
//
//            ImGui::InputFloat("Attenuation start", &Globals::TODLightPtr->m_attenuation_start, 0.01, 0.1, 3);
//            ImGui::InputFloat("Attenuation end", &Globals::TODLightPtr->m_attenuation_end, 0.01, 0.1, 3);
//            ImGui::InputFloat("Hotspot falloff size", &Globals::TODLightPtr->m_hotspot_falloff_size, 0.01, 0.1, 3);
//            ImGui::InputFloat("Hotspot size", &Globals::TODLightPtr->m_hotspot_size, 0.01, 0.1, 3);
//
//            ImGui::Text("Clip minimum:");
//            ImGui::InputFloat("x", &Globals::TODLightPtr->m_clip_min.x, 0.01, 0.1, 3);
//            ImGui::InputFloat("y", &Globals::TODLightPtr->m_clip_min.y, 0.01, 0.1, 3);
//            ImGui::InputFloat("z", &Globals::TODLightPtr->m_clip_min.z, 0.01, 0.1, 3);
//
//            ImGui::Text("Clip maximum:");
//            ImGui::InputFloat("x", &Globals::TODLightPtr->m_clip_max.x, 0.01, 0.1, 3);
//            ImGui::InputFloat("y", &Globals::TODLightPtr->m_clip_max.y, 0.01, 0.1, 3);
//            ImGui::InputFloat("z", &Globals::TODLightPtr->m_clip_max.z, 0.01, 0.1, 3);
//
//            ImGui::Text("Light direction:");
//            ImGui::InputFloat("x", &Globals::TODLightPtr->m_light_direction.x, 0.01, 0.1, 3);
//            ImGui::InputFloat("y", &Globals::TODLightPtr->m_light_direction.y, 0.01, 0.1, 3);
//            ImGui::InputFloat("z", &Globals::TODLightPtr->m_light_direction.z, 0.01, 0.1, 3);
//
//            //Todo: Add the following vars:
//            //rl_renderable_instance *m_clip_mesh;
//            //unsigned __int16 m_vis_pass_index;
//            //unsigned __int16 m_shadow_vis_pass_index;
//        }
//        else
//        {
//            ImGui::Text("TOD Light pointer is null");
//        }
//    }
//    else
//    {
//        ImGui::SameLine();
//        ImGui::TextColored(Globals::ColorRed, "[Experimental]");
//    }
//
//    if (Globals::MainScenePtr)
//    {
//        //Todo: Mess with main scene settings
//        if (Globals::MainSceneRendererPtr)
//        {
//            //ImGui::PushFont(FontBig);
//            ImGui::Text("Main scene renderer settings:");
//            //ImGui::PopFont();
//            ImGui::Separator();
//
//            ImGui::InputInt("Shadow map width", &Globals::MainSceneRendererPtr->m_shadow_map_width);
//            ImGui::InputInt("Shadow map height", &Globals::MainSceneRendererPtr->m_shadow_map_height);
//
//            //None of the options in this are changeable.
//            /*if (GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params)
//            {
//                ImGui::InputInt("Shadows enabled", (int*)&GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadows_enabled);
//                ImGui::InputInt("Use clb shadows", (int*)&GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->use_clb_shadows);
//                ImGui::InputInt("Shadow AA enabled", (int*)&GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_aa_enabled);
//
//                ImGui::InputFloat("Shadow max distance", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_max_dist, 10.0f, 100.0f, 3);
//                ImGui::InputFloat("Shadow fade start", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_fade_start, 10.0f, 100.0f, 3);
//                ImGui::InputFloat("Shadow percent", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_percent, 10.0f, 100.0f, 3);
//                ImGui::InputFloat("Shadow percent bias", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_percent_bias, 10.0f, 100.0f, 3);
//            }*/
//        }
//    }
//     */


/* Content removed from the tweaks menu ends here */
























/*void __stdcall D3D11CreateQueryHook(ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery)
{
	std::call_once(HookD3D11CreateQueryInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11CreateQuery() hook.\n", LogInfo, false, true);
		g_pd3dDevice = pDevice;
		D3D11DeviceFound = true;
	});
	//std::cout << "10 CREATEQUERYHOOK" << "\n";
	return D3D11CreateQueryObject(pDevice, pQueryDesc, ppQuery);
}

void __stdcall D3D11DrawIndexedHook(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	std::call_once(HookD3D11DrawIndexedInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11DrawIndexed() hook.\n", LogInfo, false, true);
		g_pd3dDeviceContext = pContext;
		D3D11DeviceContextFound = true;
	});
	std::cout << "11 DRAWINDEXEDHOOK" << "\n";
	return D3D11DrawIndexedObject(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

HRESULT __stdcall D3D11CheckFeatureSupportHook(ID3D11Device* pDevice, D3D11_FEATURE Feature, void* FeatureSupportData, UINT FeatureSupportDataSize)
{
	std::call_once(HookD3D11CheckFeatureSupportInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11CheckFeatureSupport() hook.\n", LogInfo, false, true);
		g_pd3dDevice = pDevice;
		D3D11DeviceFound = true;
	});
	std::cout << "12 CHECKFEATURESUPPORTHOOK" << "\n";
	return D3D11CheckFeatureSupportObject(pDevice, Feature, FeatureSupportData, FeatureSupportDataSize);
}

void __stdcall D3D11GetDeviceHook(ID3D11DeviceChild* Child, ID3D11Device** Device)
{
	std::call_once(HookD3D11GetDeviceInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11CheckFeatureSupport() hook.\n", LogInfo, false, true);
		g_pd3dDevice = *Device;
		D3D11DeviceFound = true;
	});
	std::cout << "13 GETDEVICEHOOK" << "\n";
	return D3D11GetDeviceObject(Child, Device);
}

void __stdcall D3D11BeginHook(ID3D11DeviceContext* Context, ID3D11Asynchronous* Async)
{
	std::call_once(HookD3D11BeginInitialMessage, [&]()
	{
		ConsoleLog("First time in D3D11Begin() hook.\n", LogInfo, false, true);
		g_pd3dDeviceContext = Context;
		D3D11DeviceContextFound = true;
	});
	//std::cout << "14 BEGINHOOK" << "\n";
	return D3D11BeginObject(Context, Async);
}*/

/*	
ConsoleLog("Hooking GraphicsBeginFrame().\n", LogInfo, false, true);
if (MH_CreateHook((DWORD*)(ModuleBase + 0x86DD00), GraphicsBeginFrameHook, (LPVOID*)&GraphicsBeginFrame) != MH_OK)
{
	ConsoleLog("Failed to create GraphicsBeginFrame() hook. RFGR Script loader deactivating.", LogError, false, true, true);
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}
ConsoleLog("Successfully created GraphicsBeginFrame() hook.", LogInfo, false, true, true);
if (MH_EnableHook((DWORD*)(ModuleBase + 0x86DD00)) != MH_OK)
{
	ConsoleLog("Failed to enable GraphicsBeginFrame() hook. RFGR Script loader deactivating.", LogError, false, true, true);
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}
ConsoleLog("Sucessfully enabled GraphicsBeginFrame() hook.", LogInfo, false, true, true);
ConsoleLog("Sucessfully hooked GraphicsBeginFrame().\n", LogInfo, false, true);*/



/*
B BTest;
B* BTestPointer = &BTest;

unsigned char* bytePtr = reinterpret_cast<unsigned char*>(BTestPointer);
bytePtr += 4;

std::cout << "*(int*)(BTestPointer + 0x4): " << *(int*)(bytePtr) << "\n";// *(int*)(BTestPointer + 0x4) << "\n";
*/


/*
void ProgramManager::LoadDataFromConfig()
{
	std::string ExePath = GetEXEPath(false);
	if (fs::exists(ExePath + "RFGR Script Loader/Settings.txt"))
	{
		// read a JSON file
		std::ifstream Config(ExePath + "RFGR Extended Camera/Settings.txt");
		Config >> MainConfig;
		Config.close();
	}
	else
	{
	CreateDirectoryIfNull(ExePath + "RFGR Script Loader/");
	std::cout << "Settings.txt not found. Creating from default values.\n";

	MainConfig["Default free camera speed"] = 0.3;
	//MainConfig["Default rotation speed"] = 0.7;
	//MainConfig["Create output console"] = true;

	//Keybinds
	/*MainConfig["Keybinds"]["Decrease camera speed"] = "q";
	MainConfig["Keybinds"]["Increase camera speed"] = "e";
	MainConfig["Keybinds"]["Toggle free camera"] = "VK_NUMPAD1";
	MainConfig["Keybinds"]["Toggle hud"] = "VK_NUMPAD2";
	MainConfig["Keybinds"]["Toggle fog"] = "VK_NUMPAD3";
	MainConfig["Keybinds"]["Camera forward"] = "VK_UP";
	MainConfig["Keybinds"]["Camera backward"] = "VK_DOWN";
	MainConfig["Keybinds"]["Camera left"] = "VK_LEFT";
	MainConfig["Keybinds"]["Camera right"] = "VK_RIGHT";
	MainConfig["Keybinds"]["Camera up"] = "z";
	MainConfig["Keybinds"]["Camera down"] = "x";

	//Rotation Keybinds
	MainConfig["Keybinds"]["Decrease rotation speed"] = "t";
	MainConfig["Keybinds"]["Increase rotation speed"] = "y";
	MainConfig["Keybinds"]["Toggle manual rotation control"] = "VK_NUMPAD4";
	MainConfig["Keybinds"]["Reset rotation"] = "VK_NUMPAD5";
	MainConfig["Keybinds"]["Lock pitch"] = "VK_NUMPAD7";
	MainConfig["Keybinds"]["Lock yaw"] = "VK_NUMPAD8";
	MainConfig["Keybinds"]["Lock roll"] = "VK_NUMPAD9";
	MainConfig["Keybinds"]["Decrease pitch"] = "VK_INSERT";
	MainConfig["Keybinds"]["Increase pitch"] = "VK_DELETE";
	MainConfig["Keybinds"]["Decrease yaw"] = "VK_END";
	MainConfig["Keybinds"]["Increase yaw"] = "VK_HOME";
	MainConfig["Keybinds"]["Decrease roll"] = "VK_NEXT";
	MainConfig["Keybinds"]["Increase roll"] = "VK_PRIOR";

	// write prettified JSON to another file
	std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings.txt");
	ConfigOutput << std::setw(4) << MainConfig << "\n";
	ConfigOutput.close();
	}

	HKL KeyboardLayout = GetKeyboardLayout(0);
	//VkKeyScanEx(YOUR_CHAR, currentKBL);

	//ConsoleLog("Keyboard layout created", LogWarning, false, true, true);

	DefaultFreeCameraSpeed = MainConfig["Default free camera speed"].get<float>();
	//DefaultRotationSpeed = MainConfig["Default rotation speed"].get<float>();
	//UseConsole = MainConfig["Create output console"].get<bool>();

	ConsoleLog("Loading keybinds", LogWarning, false, true, true);

	KeyDecreaseCameraSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Decrease camera speed"].get<int>(), KeyboardLayout);
	ConsoleLog("KeyDecreaseCameraSpeed Set", LogError, false, true, true);
	KeyIncreaseCameraSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Increase camera speed"].get<char>(), KeyboardLayout);
	KeyToggleFreecamera = VkKeyScanEx(MainConfig["Keybinds"]["Toggle free camera"].get<char>(), KeyboardLayout);
	KeyToggleHud = VkKeyScanEx(MainConfig["Keybinds"]["Toggle hud"].get<char>(), KeyboardLayout);
	KeyToggleFog = VkKeyScanEx(MainConfig["Keybinds"]["Toggle fog"].get<char>(), KeyboardLayout);
	KeyCameraForward = VkKeyScanEx(MainConfig["Keybinds"]["Camera forward"].get<char>(), KeyboardLayout);
	KeyCameraBackward = VkKeyScanEx(MainConfig["Keybinds"]["Camera backward"].get<char>(), KeyboardLayout);
	KeyCameraLeft = VkKeyScanEx(MainConfig["Keybinds"]["Camera left"].get<char>(), KeyboardLayout);
	KeyCameraRight = VkKeyScanEx(MainConfig["Keybinds"]["Camera right"].get<char>(), KeyboardLayout);
	KeyCameraUp = VkKeyScanEx(MainConfig["Keybinds"]["Camera up"].get<char>(), KeyboardLayout);
	KeyCameraDown = VkKeyScanEx(MainConfig["Keybinds"]["Camera down"].get<char>(), KeyboardLayout);

	ConsoleLog("Loading rotation control keybinds", LogWarning, false, true, true);

	KeyDecreaseRotationSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Decrease rotation speed"].get<char>(), KeyboardLayout);
	KeyIncreaseRotationSpeed = VkKeyScanEx(MainConfig["Keybinds"]["Inrease rotation speed"].get<char>(), KeyboardLayout);
	KeyToggleRotationControl = VkKeyScanEx(MainConfig["Keybinds"]["Toggle manual rotation control"].get<char>(), KeyboardLayout);
	KeyResetRotation = VkKeyScanEx(MainConfig["Keybinds"]["Reset rotation"].get<char>(), KeyboardLayout);
	KeyLockPitch = VkKeyScanEx(MainConfig["Keybinds"]["Lock pitch"].get<char>(), KeyboardLayout);
	KeyLockYaw = VkKeyScanEx(MainConfig["Keybinds"]["Lock yaw"].get<char>(), KeyboardLayout);
	KeyLockRoll = VkKeyScanEx(MainConfig["Keybinds"]["Lock roll"].get<char>(), KeyboardLayout);
	KeyDecreasePitch = VkKeyScanEx(MainConfig["Keybinds"]["Decrease pitch"].get<char>(), KeyboardLayout);
	KeyIncreasePitch = VkKeyScanEx(MainConfig["Keybinds"]["Increase pitch"].get<char>(), KeyboardLayout);
	KeyDecreaseYaw = VkKeyScanEx(MainConfig["Keybinds"]["Decrease yaw"].get<char>(), KeyboardLayout);
	KeyIncreaseYaw = VkKeyScanEx(MainConfig["Keybinds"]["Increase yaw"].get<char>(), KeyboardLayout);
	KeyDecreaseRoll = VkKeyScanEx(MainConfig["Keybinds"]["Decrease roll"].get<char>(), KeyboardLayout);
	KeyIncreaseRoll = VkKeyScanEx(MainConfig["Keybinds"]["Increase roll"].get<char>(), KeyboardLayout);
}*/

	/*ISpVoice * pVoice = NULL;

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr))
	{
		hr = pVoice->Speak(L"<pitch middle = '10'>RFGR script loader activated", SPF_IS_XML, NULL);
		pVoice->Release();
		pVoice = NULL;
	}

	::CoUninitialize();*/

/*typedef void(__stdcall* D3D11CreateQuery) (ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);
D3D11CreateQuery D3D11CreateQueryObject;

typedef void(__stdcall* D3D11DrawIndexed) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
D3D11DrawIndexed D3D11DrawIndexedObject;

typedef HRESULT(__stdcall* D3D11CheckFeatureSupport) (ID3D11Device* pDevice, D3D11_FEATURE Feature, void* FeatureSupportData, UINT FeatureSupportDataSize);
D3D11CheckFeatureSupport D3D11CheckFeatureSupportObject;

typedef void(__stdcall* D3D11GetDevice) (ID3D11DeviceChild* Child, ID3D11Device** Device);
D3D11GetDevice D3D11GetDeviceObject;

typedef void(__stdcall* D3D11Begin) (ID3D11DeviceContext* Context, ID3D11Asynchronous* Async);
D3D11Begin D3D11BeginObject;*/


/*Here we call all our hooks
If you find yourself still not understanding
what each function is doing then I recommend you study some
assembly and try to learn the basic instructions :)
*/


//Setup our infinite ammo by changing an instruction
//You can also ignore the instructions
//Store where we jump back to after our hook
/*DWORD AmmoJmpBack = 0;
__declspec(naked) void InfiniteAmmo()
{
	//here's where ammo would normally be decreased
	//we will overwrite that instruction with something else
	__asm INC[ESI]
		//Make sure all the original instructions also run(within you're set of bytes)
		//this will prevent any crashing
		__asm push edi
	//When copying instructions from cheat engine/olly make sure to change any numbers to
	//0x so the compiler knows that its a hexadecimal value e.g. [esp+14] becomes [esp+0x14]
	__asm mov edi, [esp + 0x14]
		//Jump back to our original code
		__asm jmp[AmmoJmpBack]
}


//Store where we jump back to after our hook
DWORD FlyingJmpBack = 0;
//stores the register's address
DWORD YaxisRegister = 0x0;
DWORD YAxisPtr;

//Store our player's y axis into our dword
__declspec(naked) void GetPlayerYaxis()
{
	//Run the instructions the same as before
	//EXCEPT we take the address within ESI(Our Y axis)
	//AND later on modify it so we can fly
	//The offset of 0x3x tells us that ESI + 3C gives us
	//Y Axis, ESI is likely to point to our player base(unchecked)
	__asm MOV ECX, [ESI + 0x3C]
		//Throw our address into our DWORD YaxisRegister so we can
		//later modify the float value the address points to
		__asm MOV YaxisRegister, ESI
	__asm MOV[ESI + 0x08], EDX
	//Jump back to our original code
	__asm jmp[FlyingJmpBack]
}*/

/*	//ImGui::InputInt("Max FPS", MaxFPS, 1, 10);
	//ImGui::SameLine();

	ImGui::Text("Player.Object.Position: ");
	ImGui::SameLine();
	std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
	ImGui::Text(PlayerPositionString.c_str());

	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat3("Player Position Target", PlayerPositionTargetArray, 3);
	ImGui::SameLine();
	if (ImGui::Button("Sync##PlayerPositionTarget"))
	{
		PlayerPositionTargetArray[0] = PlayerPtr->Position.x;
		PlayerPositionTargetArray[1] = PlayerPtr->Position.y;
		PlayerPositionTargetArray[2] = PlayerPtr->Position.z;
	}
	ImGui::SameLine();
	if (ImGui::Button("Set##PlayerPositionTarget"))
	{
		PlayerPtr->Position.x = PlayerPositionTargetArray[0];
		PlayerPtr->Position.y = PlayerPositionTargetArray[1];
		PlayerPtr->Position.z = PlayerPositionTargetArray[2];
		//NeedPlayerPosSet = true;

		std::cout << "Unsafely teleporting player to (" << PlayerPositionTargetArray[0] << ", " << PlayerPositionTargetArray[1] << ", " << PlayerPositionTargetArray[2] << ")!" << "\n";
		HumanTeleportUnsafe(PlayerPtr, vector(PlayerPositionTargetArray[0], PlayerPositionTargetArray[1], PlayerPositionTargetArray[2]), PlayerPtr->Orientation);
	}

	ImGui::PushItemWidth(232.0f);
	ImGui::InputFloat3("Player velocity: ", (float*)&PlayerPtr->Velocity); //PlayerVelocityTargetArray);
	ImGui::SameLine();
	if (ImGui::Button("Sync##PlayerVelocityTarget"))
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
	}*/





/*#define JsonCatchAll(FileName) \
catch (nlohmann::json::parse_error& Exception) \
{ \
	Logger::Log(std::string("Parse exception caught while parsing " + "\"" + FileName + "\""), LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage(std::string("Parse exception caught while parsing " + "\"" + FileName + "\"")); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::invalid_iterator& Exception) \
{ \
	Logger::Log("Invalid iterator exception caught while parsing" + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Invalid iterator exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::type_error& Exception) \
{ \
	Logger::Log("Type error exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Type error exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::out_of_range& Exception) \
{ \
	Logger::Log("Out of range exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Out of range exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (nlohmann::json::basic_json::other_error& Exception) \
{ \
	Logger::Log("Other error exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("Other error exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Other error parse exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
	return false; \
} \
catch (std::exception& Exception) \
{ \
	Logger::Log("General exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
	Logger::Log(std::string(Exception.what()), LogFatalError); \
 \
	std::string ExceptionMessage("General exception caught while parsing " + "\"" + FileName + "\""); \
	ExceptionMessage += "Message: "; \
	ExceptionMessage += Exception.what(); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
 \
	return false; \
} \
catch (...) \
{ \
	Logger::Log("Default exception caught while parsing " + "\"" + FileName + "\"", LogFatalError); \
 \
	MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception caught while parsing " + "\"" + FileName + "\"", "Json default exception caught", MB_OK); \
	Logger::Log("Failed to parse " + "\"" + FileName + "\", exiting.", LogFatalError); \
 \
	return false; \
} */

/*
template<typename Callable>
auto JsonExceptionHandler(Callable&& Function, std::string FileName, std::string Action, std::string ActionConjugated, std::string Message) -> decltype(Function())
{
	try
	{
		return Function();
	}
	catch (nlohmann::json::parse_error& Exception)
	{
		Logger::Log("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::invalid_iterator& Exception)
	{
		Logger::Log("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::type_error& Exception)
	{
		Logger::Log("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::out_of_range& Exception)
	{
		Logger::Log("Out of range exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::other_error& Exception)
	{
		Logger::Log("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json other error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (std::exception& Exception)
	{
		Logger::Log("General exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("General exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (...)
	{
		Logger::Log("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);

		std::string ExceptionMessage("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs.");
		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json default exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
}
*/



/*Test of rl_draw::string(). Currently this just freezes the game. Will
probably end up just using an external lib to render text for now.*/
/*if (ImGui::Button("Test draw string"))
{
	rl_primitive_state* PrimitiveState;
	PrimitiveState = new rl_primitive_state;
	PrimitiveState->d.v.m_alpha_mode = 5;
	PrimitiveState->d.v.m_clamp_mode = 0;
	PrimitiveState->d.v.m_color_write_mode = 0;
	PrimitiveState->d.v.m_const_alpha = 0xFF;
	PrimitiveState->d.v.m_cull_mode = 0;
	PrimitiveState->d.v.m_msaa = 0;
	PrimitiveState->d.v.m_scissor = 0;
	PrimitiveState->d.v.m_stencil_mode = 0;
	PrimitiveState->d.v.m_valid = 1;
	PrimitiveState->d.v.m_zbias_mode = 0;
	PrimitiveState->d.v.m_zbuf_mode = 0;

	RlDrawString(GlobalRlDrawPtr, nullptr, 100.0f, 100.0f, "Test string draw!!!", true, 0, PrimitiveState);
}*/

/*This is experimental code meant to manipulate the remnants of the games
debug console. Currently just tries to activate it. Later on I'll try to
manually add commands to it and run them. If that works, then I'll add them
to the lua system and port them through the overlay lua console.*/
/*ImGui::Text("Console Mode: "); ImGui::SameLine();
ImGui::TextColored(SecondaryTextColor, std::to_string((int)ConsoleGetConsoleMode).c_str());
if (ImGui::Button("VCM_NORMAL (0)"))
{
	ConsoleSetConsoleMode(VCM_NORMAL);
}
if (ImGui::Button("VCM_CHAT (1)"))
{
	ConsoleSetConsoleMode(VCM_CHAT);
}
if (ImGui::Button("VCM_TEAMCHAT (2)"))
{
	ConsoleSetConsoleMode(VCM_TEAMCHAT);
}

if (ImGui::Button("Console init"))
{
	vconsole_config* ConsoleConfig;
	ConsoleConfig = new vconsole_config; //Todo: Fix this if actually using. This is for testing purposes only and will cause a memory leak.
	ConsoleConfig->screen_width = 1680;
	ConsoleConfig->screen_height = 1050;
	ConsoleConfig->save_history = true;
	ConsoleConfig->safe_area_left = 0;
	ConsoleInit(ConsoleConfig);
}
if (ImGui::Button("Console activate"))
{
	ConsoleActivate();
}
if (ImGui::Button("Console deactivate"))
{
	ConsoleDeactivate();
}*/







/*ImGui::Separator();

if (ImGui::CollapsingHeader("Globals"))
{

}
ImGui::Separator();*/

//ImGui::Text("FPS: ");
//ImGui::Separator();

/*if (ImGui::CollapsingHeader("Global explosion modifiers##GlobalExplosionModifiersMain"))
{
	if (ImGui::Button("Reset to defaults##GlobalExplosionModifiersMain"))
	{
		GlobalExplosionStrengthMultiplier = 1.0f;
		UseGlobalExplosionStrengthMultiplier = false;
		UseExplosionRadiusLimits = true;
		MinimumExplosionRadius = 0.0f;
		MaximumExplosionRadius = 12.0f;
	}
	ImGui::PushItemWidth(232.0f);
	ImGui::SliderFloat("Global explosion strength multiplier", &GlobalExplosionStrengthMultiplier, 0.01f, 10.0f);
	ImGui::SameLine(); ImGui::Checkbox("Use", &UseGlobalExplosionStrengthMultiplier);
	ImGui::Checkbox("Use explosion radius limits", &UseExplosionRadiusLimits);
	Util::GUI::TooltipOnPrevious("If you turn this off be very very careful with the explosion multipliers. Too high and it's very easy to freeze/crash the game. My game froze at 4x explosions with no radius limits.");
	ImGui::InputFloat("Minimum explosion radius", &MinimumExplosionRadius, 0.1f, 1.0f, 3);
	ImGui::InputFloat("Maximum explosion radius", &MaximumExplosionRadius, 0.1f, 1.0f, 3);
}
else
{
	ImGui::SameLine(); ImGui::TextColored(ColorRed, " [Experimental]");
}*/

//ImGui::Separator();

//DrawTeleportGui(false, "Teleport", &TeleportWindowOpen, MainOverlayWindowFlags);
//ImGui::Separator();

//DrawPlayerVariablesGui(false, "Player variables", &PlayerVariablesGuiOpen, MainOverlayWindowFlags);
//ImGui::Separator();

//ImGui::Text("Misc Program Values:");


/*	//ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_COG) + u8"##CogIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_COGS) + u8"##CogsIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TASKS) + u8"##TasksIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TOOLS) + u8"##ToolsIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_TOOLBOX) + u8"##ToolboxIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_EXCLAMATION_TRIANGLE) + u8"##ExclamationTriangleIcon").c_str()))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button(std::string(std::string(ICON_FA_VIAL) + u8"##ExclamationTriangleIcon").c_str()))//Also try the flask icon
	{

	}*/







/*
 *
 *
 *     if(Globals::MainScenePtr)
    {
        ImGui::Checkbox("Diffraction enabled", &Globals::MainScenePtr->m_diffraction_enabled);
        ImGui::InputFloat4("Ambient color", (float*)& Globals::MainScenePtr->m_ambient_color);
        ImGui::InputFloat4("Back ambient color", (float*)& Globals::MainScenePtr->m_back_ambient_color);
        ImGui::InputFloat("Time val", &Globals::MainScenePtr->m_time_val);
        ImGui::InputFloat("Time of day val", &Globals::MainScenePtr->m_time_of_day_val);

        ImGui::Separator();
        ImGui::Text("Hdr state:");
        ImGui::Checkbox("Enabled", &Globals::MainScenePtr->m_hdr_state.m_enable);
        ImGui::InputFloat("Luminance range", &Globals::MainScenePtr->m_hdr_state.m_lum_range);
        ImGui::InputFloat("Luminance offset", &Globals::MainScenePtr->m_hdr_state.m_lum_offset);
        ImGui::InputFloat("Bloom exposure", &Globals::MainScenePtr->m_hdr_state.m_bloom_exposure);
        ImGui::InputFloat3("Luminance conversion", (float*)&Globals::MainScenePtr->m_hdr_state.m_luminance_conversion); //vec
        ImGui::InputFloat("Iris rate", &Globals::MainScenePtr->m_hdr_state.m_iris_rate); 
        ImGui::InputFloat("Luminance max", &Globals::MainScenePtr->m_hdr_state.m_luminance_max); 
        ImGui::InputFloat("Luminance min", &Globals::MainScenePtr->m_hdr_state.m_luminance_min); 
        ImGui::InputFloat("Luminance mask max", &Globals::MainScenePtr->m_hdr_state.m_luminance_mask_max); 
        ImGui::InputFloat("Brightness threshold", &Globals::MainScenePtr->m_hdr_state.m_brightpass_threshold); 
        ImGui::InputFloat("Brightness offset", &Globals::MainScenePtr->m_hdr_state.m_brightpass_offset); 
        ImGui::Checkbox("Bloom soft", &Globals::MainScenePtr->m_hdr_state.m_bloom_soft); //bool
        ImGui::Checkbox("Bloom alternate", &Globals::MainScenePtr->m_hdr_state.m_bloom_alternate); //bool
        ImGui::Checkbox("Tone mapped bloom", &Globals::MainScenePtr->m_hdr_state.m_tone_mapped_bloom); //bool
        ImGui::Checkbox("Use hdr level", &Globals::MainScenePtr->m_hdr_state.m_use_hdr_level); //bool
        ImGui::InputFloat("Eye adaption base", &Globals::MainScenePtr->m_hdr_state.m_eye_adaption_base);
        ImGui::InputFloat("Eye adaption amount", &Globals::MainScenePtr->m_hdr_state.m_eye_adaption_amount);
        ImGui::InputFloat("Eye fade min", &Globals::MainScenePtr->m_hdr_state.m_eye_fade_min);
        ImGui::InputFloat("Eye fade max", &Globals::MainScenePtr->m_hdr_state.m_eye_fade_max);
        ImGui::InputFloat("Bloom amount", &Globals::MainScenePtr->m_hdr_state.m_bloom_amount);
        ImGui::Checkbox("Bloom new", &Globals::MainScenePtr->m_hdr_state.m_bloom_new); //bool
        ImGui::InputFloat("Bloom theta", &Globals::MainScenePtr->m_hdr_state.m_bloom_theta);
        ImGui::InputFloat("Bloom slope A", &Globals::MainScenePtr->m_hdr_state.m_bloom_slope_A);
        ImGui::InputFloat("Bloom slope B", &Globals::MainScenePtr->m_hdr_state.m_bloom_slope_B);
        ImGui::InputFloat3("Sun shafts position", (float*)&Globals::MainScenePtr->m_hdr_state.m_sun_shafts_position); //vec
    }
    else
    {
        ImGui::Text("Globals::MainScenePtr is invalid. Can't display it's vars.");
    }

    ImGui::Separator();

 */