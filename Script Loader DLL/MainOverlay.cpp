#include "MainOverlay.h"

nlohmann::json GUIConfig;
nlohmann::json TeleportLocations;

static void ShowExampleMenuFile()
{
	ImGui::MenuItem("(dummy menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}
	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		static bool b = true;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::Checkbox("Check", &b);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Colors"))
	{
		float sz = ImGui::GetTextLineHeight();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			ImVec2 p = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			ImGui::Dummy(ImVec2(sz, sz));
			ImGui::SameLine();
			ImGui::MenuItem(name);
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

static void ShowExampleAppConsole(bool* p_open)
{
	static ExampleAppConsole console;
	console.Draw("Example: Console", p_open);
}


static void ShowExampleAppLog(bool* p_open)
{
	static ExampleAppLog log;

	// Demo: add random items (unless Ctrl is held)
	static double last_time = -1.0;
	double time = ImGui::GetTime();
	if (time - last_time >= 0.20f && !ImGui::GetIO().KeyCtrl)
	{
		const char* random_words[] = { "system", "info", "warning", "error", "fatal", "notice", "log" };
		log.AddLog("[%s] Hello, time is %.1f, frame count is %d\n", random_words[rand() % IM_ARRAYSIZE(random_words)], time, ImGui::GetFrameCount());
		last_time = time;
	}

	log.Draw("Example: Log", p_open);
}

static void TooltipOnPrevious(const char* Description)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(Description);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

bool HumanTeleportSafe(float x, float y, float z, int TimeToHover = 5000)
{
	if (GlobalPlayerPtr)
	{
		Sleep(1000);
		int TimeHovered = 0;
		Player* TempPlayerPtr = (Player*)GlobalPlayerPtr;
		while (TimeHovered < TimeToHover)
		{
			HumanTeleportUnsafe(TempPlayerPtr, vector(x, y, z), TempPlayerPtr->Orientation);
			Sleep(200);
			TimeHovered += 200;
		}
		return true;
	}
	return false;
}

void HumanTeleportSafe(vector NewPosition, int TimeToHover = 5000)
{

}

void SetJsonFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, float r, float g, float b, float a)
{
	Json[FirstKey][SecondKey][0] = r;
	Json[FirstKey][SecondKey][1] = g;
	Json[FirstKey][SecondKey][2] = b;
	Json[FirstKey][SecondKey][3] = a;
}

void SetJsonFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, ImVec4 Color)
{
	Json[FirstKey][SecondKey][0] = Color.x;
	Json[FirstKey][SecondKey][1] = Color.y;
	Json[FirstKey][SecondKey][2] = Color.z;
	Json[FirstKey][SecondKey][3] = Color.w;
}

ImVec2 JsonGetFloat2(nlohmann::json& Json, const char* FirstKey, const char* SecondKey)
{
	return ImVec2(Json[FirstKey][SecondKey][0], Json[FirstKey][SecondKey][1]);
}

ImVec4 JsonGetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey)
{
	return ImVec4(Json[FirstKey][SecondKey][0], Json[FirstKey][SecondKey][1], Json[FirstKey][SecondKey][2], Json[FirstKey][SecondKey][3]);
}

void SetTeleportLocation(std::string Name, float x, float y, float z, std::string Description)
{
	TeleportLocations[Name]["Position"][0] = x;
	TeleportLocations[Name]["Position"][1] = y;
	TeleportLocations[Name]["Position"][2] = z;
	TeleportLocations[Name]["TooltipDescription"] = "Tutorial area at the start of the game. Position: (-2328.29, 30.0, -2317.9)";
}

bool LoadTeleportLocations()
{
	std::string ExePath = GetEXEPath(false);
	std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Load Log.txt");

	if (fs::exists(ExePath + "RFGR Script Loader/Settings/Teleport Locations.json"))
	{
		try
		{
			std::ifstream Config(ExePath + "RFGR Script Loader/Settings/Teleport Locations.json");
			LogFile << "Parsing \"Teleport Locations.json\"..." << std::endl;
			Config >> TeleportLocations;
			Config.close();
		}
		catch (nlohmann::json::parse_error& Exception)
		{
			LogFile << "Parse error while parsing \"Teleport Locations.json\"!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("Parse error while parsing \"Teleport Locations.json\"\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed to parse \"Teleport Locations.json\", exiting." << std::endl;
			return false;
		}
		catch (std::exception& Exception)
		{
			LogFile << "General exception when parsing \"Teleport Locations.json\"!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("General exception when parsing \"Teleport Locations.json\"\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed to parse \"Teleport Locations.json\", exiting." << std::endl;
			return false;
		}
		catch (...)
		{
			LogFile << "Default exception when parsing \"Teleport Locations.json\"!" << std::endl;

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception while parsing \"Teleport Locations.json\"", "Json parsing exception", MB_OK);
			LogFile << "Failed to parse \"Teleport Locations.json\", exiting." << std::endl;
			return false;
		}
		LogFile << "No parse exceptions detected." << std::endl;
	}
	else
	{
		CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");
		//std::cout << "Settings.txt not found. Creating from default values." << std::endl;
		std::ofstream LogFile;
		LogFile.open(ExePath + "RFGR Script Loader/Logs/Start errors.txt");
		LogFile << "\"Teleport Locations.json\" not found. Creating from default values." << std::endl;

		SetTeleportLocation("Tutorial Area Hilltop", -2328.29f, 30.0f, -2317.9f, "Tutorial area at the start of the game. Position: (-2328.29, 30.0, -2317.9)");
		SetTeleportLocation("Parker - Safehouse", -1877.77f, 27.0f, -1452.0f, "Game starting safehouse. Near ore processing plant. Position: (-1877.77, 27.0, -1452.0)");
		SetTeleportLocation("Dust - Northern Safehouse", -387.0f, 38.0f, -820.0f, "Near tharsis wind farm and Dust town hall. Position: (-387.0, 38.0, -820.0)");
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
		LogFile.close();
	}

	return true;
}

bool LoadGUIConfig()
{
	std::string ExePath = GetEXEPath(false);
	std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Load Log.txt");

	if (fs::exists(ExePath + "RFGR Script Loader/Settings/GUI Config.json"))
	{
		try
		{
			std::ifstream Config(ExePath + "RFGR Script Loader/Settings/GUI Config.json");
			LogFile << "Parsing GUI Config.json..." << std::endl;
			Config >> GUIConfig;
			Config.close();
		}
		catch (nlohmann::json::parse_error& Exception)
		{
			LogFile << "Parse error while parsing GUI Config.json!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("Parse error while parsing GUI Config.json!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed to parse GUI Config.json, exiting." << std::endl;
			return false;
		}
		catch (std::exception& Exception)
		{
			LogFile << "General exception when parsing GUI Config.json!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("General exception when parsing GUI Config.json!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed to parse GUI Config.json, exiting." << std::endl;
			return false;
		}
		catch (...)
		{
			LogFile << "Default exception when parsing GUI Config.json!" << std::endl;

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), "Default exception while parsing GUI Config.json", "Json parsing exception", MB_OK);
			LogFile << "Failed to parse GUI Config.json, exiting." << std::endl;
			return false;
		}
		LogFile << "No parse exceptions detected." << std::endl;
	}
	else
	{
		CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");
		//std::cout << "Settings.txt not found. Creating from default values." << std::endl;
		std::ofstream LogFile;
		LogFile.open(ExePath + "RFGR Script Loader/Logs/Start errors.txt");
		LogFile << "GUI Settings.json not found. Creating from default values." << std::endl;
		
		GUIConfig["Theme Info"]["Theme name"] = std::string("Default Dark Theme");
		GUIConfig["Theme Info"]["Description"] = std::string("The default dark theme for the script loader.");
		GUIConfig["Theme Info"]["Author"] = std::string("moneyl");
		GUIConfig["Theme Info"]["Readme"] = std::string("When making your own themes you can use this for extra information such as known bugs or optional settings.");

		GUIConfig["Style"]["Alpha"] = 0.95f;
		GUIConfig["Style"]["AntiAliasedFill"] = true;
		GUIConfig["Style"]["ButtonTextAlign"][0] = 0.5f;
		GUIConfig["Style"]["ButtonTextAlign"][1] = 0.5f;
		GUIConfig["Style"]["ChildBorderSize"] = 0.0f; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["ChildRounding"] = 3.0f;
		GUIConfig["Style"]["DisplaySafeAreaPadding"][0] = 3.0f;
		GUIConfig["Style"]["DisplaySafeAreaPadding"][1] = 3.0f;
		GUIConfig["Style"]["FrameBorderSize"] = 0.0f; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["FramePadding"][0] = 4.0f;
		GUIConfig["Style"]["FramePadding"][1] = 3.0f;
		GUIConfig["Style"]["FrameRounding"] = 3.0f;
		GUIConfig["Style"]["GrabMinSize"] = 10.0f;
		GUIConfig["Style"]["GrabRounding"] = 3.0f;
		GUIConfig["Style"]["IndentSpacing"] = 21.0f;
		GUIConfig["Style"]["ItemInnerSpacing"][0] = 4.0f;
		GUIConfig["Style"]["ItemInnerSpacing"][1] = 4.0f;
		GUIConfig["Style"]["ItemSpacing"][0] = 8.0f;
		GUIConfig["Style"]["ItemSpacing"][1] = 4.0f;
		GUIConfig["Style"]["PopupBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["PopupRounding"] = 3.0f;
		GUIConfig["Style"]["ScrollbarRounding"] = 3.0f;
		GUIConfig["Style"]["ScrollbarSize"] = 6.0f;
		GUIConfig["Style"]["TabBorderSize"] = 10.0f;
		GUIConfig["Style"]["TabRounding"] = 3.0f;
		GUIConfig["Style"]["TouchExtraPadding"][0] = 0.0f;
		GUIConfig["Style"]["TouchExtraPadding"][1] = 0.0f;
		GUIConfig["Style"]["WindowBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["WindowPadding"][0] = 8.0f;
		GUIConfig["Style"]["WindowPadding"][1] = 8.0f;
		GUIConfig["Style"]["WindowRounding"] = 3.0f;
		GUIConfig["Style"]["WindowTitleAlign"][0] = 0.0f;
		GUIConfig["Style"]["WindowTitleAlign"][1] = 0.5f;

		SetJsonFloat4(GUIConfig, "Colors", "Text", ImVec4(0.98f, 0.98f, 1.00f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "TextDisabled", ImVec4(0.50f, 0.51f, 0.53f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "WindowBackground", ImVec4(0.14f, 0.15f, 0.16f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "ChildBackground", ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
		SetJsonFloat4(GUIConfig, "Colors", "PopupBackground", ImVec4(0.10f, 0.10f, 0.12f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "Border", ImVec4(0.09f, 0.09f, 0.11f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "BorderShadow", ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
		SetJsonFloat4(GUIConfig, "Colors", "FrameBackground", ImVec4(0.10f, 0.10f, 0.12f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "FrameBackgroundHovered", ImVec4(0.20f, 0.55f, 0.83f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "FrameBackgroundActive", ImVec4(0.20f, 0.55f, 0.83f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "TitleBackground", ImVec4(0.04f, 0.04f, 0.04f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "TitleBackgroundActive", ImVec4(0.10f, 0.40f, 0.75f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "TitleBackgroundCollapsed", ImVec4(0.00f, 0.00f, 0.00f, 0.51f));
		SetJsonFloat4(GUIConfig, "Colors", "MenuBarBackground", ImVec4(0.14f, 0.14f, 0.14f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "ScrollbarBackground", ImVec4(0.02f, 0.02f, 0.02f, 0.53f));
		SetJsonFloat4(GUIConfig, "Colors", "ScrollbarGrab", ImVec4(0.31f, 0.31f, 0.31f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "ScrollbarGrabHovered", ImVec4(0.41f, 0.41f, 0.41f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "ScrollbarGrabActive", ImVec4(0.51f, 0.51f, 0.51f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "CheckMark", ImVec4(0.10f, 0.40f, 0.75f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "SliderGrab", ImVec4(0.20f, 0.55f, 0.83f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "SliderGrabActive", ImVec4(0.20f, 0.55f, 0.83f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "Button", ImVec4(0.10f, 0.40f, 0.75f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "ButtonHovered", ImVec4(0.20f, 0.55f, 0.98f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "ButtonActive", ImVec4(0.06f, 0.53f, 0.98f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "Header", ImVec4(0.26f, 0.59f, 0.98f, 0.31f));
		SetJsonFloat4(GUIConfig, "Colors", "HeaderHovered", ImVec4(0.26f, 0.59f, 0.98f, 0.80f));
		SetJsonFloat4(GUIConfig, "Colors", "HeaderActive", ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "Separator", ImVec4(0.43f, 0.43f, 0.50f, 0.50f));
		SetJsonFloat4(GUIConfig, "Colors", "SeparatorHovered", ImVec4(0.10f, 0.40f, 0.75f, 0.78f));
		SetJsonFloat4(GUIConfig, "Colors", "SeparatorActive", ImVec4(0.10f, 0.40f, 0.75f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "ResizeGrip", ImVec4(0.26f, 0.59f, 0.98f, 0.25f));
		SetJsonFloat4(GUIConfig, "Colors", "ResizeGripHovered", ImVec4(0.26f, 0.59f, 0.98f, 0.67f));
		SetJsonFloat4(GUIConfig, "Colors", "ResizeGripActive", ImVec4(0.26f, 0.59f, 0.98f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "Tab", ImVec4(0.18f, 0.35f, 0.58f, 0.86f));
		SetJsonFloat4(GUIConfig, "Colors", "TabHovered", ImVec4(0.26f, 0.59f, 0.98f, 0.80f));
		SetJsonFloat4(GUIConfig, "Colors", "TabActive", ImVec4(0.20f, 0.41f, 0.68f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "TabUnfocused", ImVec4(0.07f, 0.10f, 0.15f, 0.97f));
		SetJsonFloat4(GUIConfig, "Colors", "TabUnfocusedActive", ImVec4(0.14f, 0.26f, 0.42f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "PlotLines", ImVec4(0.55f, 0.83f, 1.00f, 0.95f));
		SetJsonFloat4(GUIConfig, "Colors", "PlotLinesHovered", ImVec4(1.00f, 0.43f, 0.35f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "PlotHistogram", ImVec4(0.90f, 0.70f, 0.00f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "PlotHistogramHovered", ImVec4(1.00f, 0.60f, 0.00f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "TextSelectedBackground", ImVec4(0.26f, 0.59f, 0.98f, 0.35f));
		SetJsonFloat4(GUIConfig, "Colors", "DragDropTarget", ImVec4(1.00f, 1.00f, 0.00f, 0.90f));
		SetJsonFloat4(GUIConfig, "Colors", "NavHighlight", ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
		SetJsonFloat4(GUIConfig, "Colors", "NavWindowingHighlight", ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
		SetJsonFloat4(GUIConfig, "Colors", "NavWindowingDimBackground", ImVec4(0.80f, 0.80f, 0.80f, 0.20f));
		SetJsonFloat4(GUIConfig, "Colors", "ModalWindowDimBackground", ImVec4(0.80f, 0.80f, 0.80f, 0.35f));

		std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/GUI Config.json");
		ConfigOutput << std::setw(4) << GUIConfig << std::endl;
		ConfigOutput.close();
		LogFile.close();
	}

	//OpenDebugConsole = MainConfig["Open debug console"].get<bool>();

	ImGuiStyle& Style = ImGui::GetStyle(); //Currently 25 items
	Style.Alpha = GUIConfig["Style"]["Alpha"].get<float>();
	Style.AntiAliasedFill = GUIConfig["Style"]["AntiAliasedFill"].get<bool>();
	Style.ButtonTextAlign = JsonGetFloat2(GUIConfig, "Style", "ButtonTextAlign");
	Style.ChildBorderSize = GUIConfig["Style"]["ChildBorderSize"].get<float>();
	Style.ChildRounding = GUIConfig["Style"]["ChildRounding"].get<float>();
	//Style.ColumnsMinSpacing = 1.0f;
	//Style.CurveTessellationTol = 1.25f;
	Style.DisplaySafeAreaPadding = JsonGetFloat2(GUIConfig, "Style", "DisplaySafeAreaPadding");
	//Style.DisplayWindowPadding = ImVec2(1.0, 1.0f);
	Style.FrameBorderSize = GUIConfig["Style"]["FrameBorderSize"].get<float>();
	Style.FramePadding = JsonGetFloat2(GUIConfig, "Style", "FramePadding");
	Style.FrameRounding = GUIConfig["Style"]["FrameRounding"].get<float>();
	Style.GrabMinSize = GUIConfig["Style"]["GrabMinSize"].get<float>();
	Style.GrabRounding = GUIConfig["Style"]["GrabRounding"].get<float>(); 
	Style.IndentSpacing = GUIConfig["Style"]["IndentSpacing"].get<float>(); 
	Style.ItemInnerSpacing = JsonGetFloat2(GUIConfig, "Style", "ItemInnerSpacing");
	Style.ItemSpacing = JsonGetFloat2(GUIConfig, "Style", "ItemSpacing");
	//Style.MouseCursorScale = 1.0f;
	Style.PopupBorderSize = GUIConfig["Style"]["PopupBorderSize"].get<float>(); 
	Style.PopupRounding = GUIConfig["Style"]["PopupRounding"].get<float>(); 
	Style.ScrollbarRounding = GUIConfig["Style"]["ScrollbarRounding"].get<float>(); 
	Style.ScrollbarSize = GUIConfig["Style"]["ScrollbarSize"].get<float>(); 16.0f;
	Style.TabBorderSize = GUIConfig["Style"]["TabBorderSize"].get<float>(); 0.0f;
	Style.TabRounding = GUIConfig["Style"]["TabRounding"].get<float>(); 3.0f;
	Style.TouchExtraPadding = JsonGetFloat2(GUIConfig, "Style", "TouchExtraPadding");
	Style.WindowBorderSize = GUIConfig["Style"]["WindowBorderSize"].get<float>(); 1.0f;
	//Style.WindowMinSize = 1.0f;
	Style.WindowPadding = JsonGetFloat2(GUIConfig, "Style", "WindowPadding");
	Style.WindowRounding = GUIConfig["Style"]["WindowRounding"].get<float>(); 3.0f;
	Style.WindowTitleAlign = JsonGetFloat2(GUIConfig, "Style", "WindowTitleAlign");

	ImVec4* Colors = ImGui::GetStyle().Colors; //48 items
	Colors[ImGuiCol_Text] = JsonGetFloat4(GUIConfig, "Colors", "Text");
	Colors[ImGuiCol_TextDisabled] = JsonGetFloat4(GUIConfig, "Colors", "TextDisabled");
	Colors[ImGuiCol_WindowBg] = JsonGetFloat4(GUIConfig, "Colors", "WindowBackground");
	Colors[ImGuiCol_ChildBg] = JsonGetFloat4(GUIConfig, "Colors", "ChildBackground");
	Colors[ImGuiCol_PopupBg] = JsonGetFloat4(GUIConfig, "Colors", "PopupBackground");
	Colors[ImGuiCol_Border] = JsonGetFloat4(GUIConfig, "Colors", "Border");
	Colors[ImGuiCol_BorderShadow] = JsonGetFloat4(GUIConfig, "Colors", "BorderShadow");
	Colors[ImGuiCol_FrameBg] = JsonGetFloat4(GUIConfig, "Colors", "FrameBackground");
	Colors[ImGuiCol_FrameBgHovered] = JsonGetFloat4(GUIConfig, "Colors", "FrameBackgroundHovered");
	Colors[ImGuiCol_FrameBgActive] = JsonGetFloat4(GUIConfig, "Colors", "FrameBackgroundActive");
	Colors[ImGuiCol_TitleBg] = JsonGetFloat4(GUIConfig, "Colors", "TitleBackground");
	Colors[ImGuiCol_TitleBgActive] = JsonGetFloat4(GUIConfig, "Colors", "TitleBackgroundActive");
	Colors[ImGuiCol_TitleBgCollapsed] = JsonGetFloat4(GUIConfig, "Colors", "TitleBackgroundCollapsed");
	Colors[ImGuiCol_MenuBarBg] = JsonGetFloat4(GUIConfig, "Colors", "MenuBarBackground");
	Colors[ImGuiCol_ScrollbarBg] = JsonGetFloat4(GUIConfig, "Colors", "ScrollbarBackground");
	Colors[ImGuiCol_ScrollbarGrab] = JsonGetFloat4(GUIConfig, "Colors", "ScrollbarGrab");
	Colors[ImGuiCol_ScrollbarGrabHovered] = JsonGetFloat4(GUIConfig, "Colors", "ScrollbarGrabHovered");
	Colors[ImGuiCol_ScrollbarGrabActive] = JsonGetFloat4(GUIConfig, "Colors", "ScrollbarGrabActive");
	Colors[ImGuiCol_CheckMark] = JsonGetFloat4(GUIConfig, "Colors", "CheckMark");
	Colors[ImGuiCol_SliderGrab] = JsonGetFloat4(GUIConfig, "Colors", "SliderGrab");
	Colors[ImGuiCol_SliderGrabActive] = JsonGetFloat4(GUIConfig, "Colors", "SliderGrabActive");
	Colors[ImGuiCol_Button] = JsonGetFloat4(GUIConfig, "Colors", "Button");
	Colors[ImGuiCol_ButtonHovered] = JsonGetFloat4(GUIConfig, "Colors", "ButtonHovered");
	Colors[ImGuiCol_ButtonActive] = JsonGetFloat4(GUIConfig, "Colors", "ButtonActive");
	Colors[ImGuiCol_Header] = JsonGetFloat4(GUIConfig, "Colors", "Header");
	Colors[ImGuiCol_HeaderHovered] = JsonGetFloat4(GUIConfig, "Colors", "HeaderHovered");
	Colors[ImGuiCol_HeaderActive] = JsonGetFloat4(GUIConfig, "Colors", "HeaderActive");
	Colors[ImGuiCol_Separator] = JsonGetFloat4(GUIConfig, "Colors", "Separator");
	Colors[ImGuiCol_SeparatorHovered] = JsonGetFloat4(GUIConfig, "Colors", "SeparatorHovered");
	Colors[ImGuiCol_SeparatorActive] = JsonGetFloat4(GUIConfig, "Colors", "SeparatorActive");
	Colors[ImGuiCol_ResizeGrip] = JsonGetFloat4(GUIConfig, "Colors", "ResizeGrip");
	Colors[ImGuiCol_ResizeGripHovered] = JsonGetFloat4(GUIConfig, "Colors", "ResizeGripHovered");
	Colors[ImGuiCol_ResizeGripActive] = JsonGetFloat4(GUIConfig, "Colors", "ResizeGripActive");
	Colors[ImGuiCol_Tab] = JsonGetFloat4(GUIConfig, "Colors", "Tab");
	Colors[ImGuiCol_TabHovered] = JsonGetFloat4(GUIConfig, "Colors", "TabHovered");
	Colors[ImGuiCol_TabActive] = JsonGetFloat4(GUIConfig, "Colors", "TabActive");
	Colors[ImGuiCol_TabUnfocused] = JsonGetFloat4(GUIConfig, "Colors", "TabUnfocused");
	Colors[ImGuiCol_TabUnfocusedActive] = JsonGetFloat4(GUIConfig, "Colors", "TabUnfocusedActive");
	Colors[ImGuiCol_PlotLines] = JsonGetFloat4(GUIConfig, "Colors", "PlotLines");
	Colors[ImGuiCol_PlotLinesHovered] = JsonGetFloat4(GUIConfig, "Colors", "PlotLinesHovered");
	Colors[ImGuiCol_PlotHistogram] = JsonGetFloat4(GUIConfig, "Colors", "PlotHistogram");
	Colors[ImGuiCol_PlotHistogramHovered] = JsonGetFloat4(GUIConfig, "Colors", "PlotHistogramHovered");
	Colors[ImGuiCol_TextSelectedBg] = JsonGetFloat4(GUIConfig, "Colors", "TextSelectedBackground");
	Colors[ImGuiCol_DragDropTarget] = JsonGetFloat4(GUIConfig, "Colors", "DragDropTarget");
	Colors[ImGuiCol_NavHighlight] = JsonGetFloat4(GUIConfig, "Colors", "NavHighlight");
	Colors[ImGuiCol_NavWindowingHighlight] = JsonGetFloat4(GUIConfig, "Colors", "NavWindowingHighlight");
	Colors[ImGuiCol_NavWindowingDimBg] = JsonGetFloat4(GUIConfig, "Colors", "NavWindowingDimBackground");
	Colors[ImGuiCol_ModalWindowDimBg] = JsonGetFloat4(GUIConfig, "Colors", "ModalWindowDimBackground");

	return true;
}

MainOverlay::MainOverlay()
{

}

MainOverlay::~MainOverlay()
{

}

void MainOverlay::Initialize()
{
	MainOverlayWindowFlags = 0;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	MainOverlayWindowFlags |= ImGuiWindowFlags_MenuBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoMove;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoResize;
	MainOverlayWindowFlags |= ImGuiWindowFlags_NoCollapse;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoNav;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBackground;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	LoadGUIConfig();
	LoadTeleportLocations();
}

void MainOverlay::Draw(const char* title, bool* p_open)
{
	if (!PlayerPtrTargetsInitialized)
	{
		if (PlayerPtr)
		{
			PlayerPositionTargetArray[0] = PlayerPtr->Position.x;
			PlayerPositionTargetArray[1] = PlayerPtr->Position.y;
			PlayerPositionTargetArray[2] = PlayerPtr->Position.z;

			PlayerVelocityTargetArray[0] = PlayerPtr->Velocity.x;
			PlayerVelocityTargetArray[1] = PlayerPtr->Velocity.y;
			PlayerVelocityTargetArray[2] = PlayerPtr->Velocity.z;

			PlayerPtrTargetsInitialized = true;
			ConsoleLog("PlayerPtrTargetsInitialized = true", LOGWARNING, false, true, true);
		}
	}

	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin(title, p_open, MainOverlayWindowFlags))
	{
		ImGui::End();
		return;
	}

	if (!PlayerPtr) //Same thing as if(PlayerPtr == nullptr)
	{
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("Please load a save and unpause the game, and reopen this gui to allow for game data retrieval. Then this gui should be useable.");
		ImGui::End();
		return;
	}

	if (ShowAppMainMenuBar)       ShowExampleAppMainMenuBar();
	if (ShowAppConsole)             ShowExampleAppConsole(&ShowAppConsole);
	if (ShowAppLog)                 ShowExampleAppLog(&ShowAppLog);
	if (ShowAppLongText)           ShowExampleAppLongText(&ShowAppLongText);
	if (ShowAppSimpleOverlay)      ShowExampleAppSimpleOverlay(&ShowAppLongText);

	if (ShowAppMetrics) { ImGui::ShowMetricsWindow(&ShowAppMetrics); }
	if (ShowAppStyleEditor) { ImGui::Begin("Style Editor", &ShowAppStyleEditor); ImGui::ShowStyleEditor(); ImGui::End(); }
	if (ShowAppAbout) { ShowAboutWindow(&ShowAppAbout); }

	// Menu
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Examples"))
		{
			ImGui::MenuItem("Main menu bar", NULL, &ShowAppMainMenuBar);
			ImGui::MenuItem("Console", NULL, &ShowAppConsole);
			ImGui::MenuItem("Log", NULL, &ShowAppLog);
			ImGui::MenuItem("Long text display", NULL, &ShowAppLongText);
			ImGui::MenuItem("Simple overlay", NULL, &ShowAppSimpleOverlay);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Metrics", NULL, &ShowAppMetrics);
			ImGui::MenuItem("Style Editor", NULL, &ShowAppStyleEditor);
			ImGui::MenuItem("About", NULL, &ShowAppAbout);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::Separator();
	
	if (ImGui::CollapsingHeader("Notes:"))
	{
		ImGui::Text("Notes:");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Please keep in mind that this is a very early version of this tool. Expect there to be bugs and incomplete features. If you encounter a bug that is not in the known bugs section, please let me know. I'd appreciate that. Some issues only pop up for certain people and I can only test on so many computers myself.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The menu above has some example menus that came with the gui library I'm using. They will be customized for the game later on.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- I've not implemented scripts yet so that section is empty.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Globals has a few values you can modify, later on you'll there will be more values and they will be accesible to scripts.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Teleport has both manual and preset teleportation options. Try not to move for at least 5 seconds after teleporting to allow for assets to load in. Sometimes you'll fall through the world with TP. Either wait or repeatedly press the teleport button in this case. Usually if you wait the game will bring you back to the surface after a few seconds.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Player variables is a list of some of the values in memory that define the player. I've only added a 1/4th to 1/3rd of the values so far and I haven't mapped some of them out yet, so it isn't very useful immediately. Once I have all values added to the gui and figure out which ones you can safely change I'll add the option to edit these values as well.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Try hovering your mouse over different gui elements. Many of them, especially in the teleport section, have useful tooltips.");
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Known bugs / issues"))
	{
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Having this tool activated causes opening weapons lockers not to work. Weapon crates still work. This is an odd bug since none of my code affects weapon lockers in a direct way. It's something unexpected which I will work on fixing soon.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The game will crash if you try to switch either to or from plain windowed mode. Using the maximize button visible in windowed mode should not cause crashes. Switching between exclusive fullscreen and fullscreen windowed should not cause any crashes. I suggest using fullscreen windowed if you expect yourself to be alt-tabbing out of the game.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- I recommend using the tool with the debug console disabled. It's an exterior window and can sometimes cause issues with the tool loading. It is off by default, so if you haven't turned it on, don't worry about it. Eventually I'll replace it completely with the in game console in the examples menu. Which is a dummy console that came with this gui library for now.");
	}
	ImGui::Separator();

	ImGui::Text("Scripts:");
	ImGui::Separator();

	ImGui::Text("Globals:");
	ImGui::Checkbox("Infinite jetpack", &InfiniteJetpack);
	ImGui::Checkbox("Invulnerable", &Invulnerable);
	if (ImGui::CollapsingHeader("Global explosion modifiers##GlobalExplosionModifiersMain"))
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
		TooltipOnPrevious("If you turn this off be very very careful with the explosion multipliers. Too high and it's very easy to freeze/crash the game. My game froze at 4x explosions with no radius limits.");
		ImGui::InputFloat("Minimum explosion radius", &MinimumExplosionRadius, 0.1f, 1.0f, 3);
		ImGui::InputFloat("Maximum explosion radius", &MaximumExplosionRadius, 0.1f, 1.0f, 3);
	}
	else
	{
		ImGui::SameLine(); ImGui::TextColored(ColorRed, " [Experimental]");
	}

	ImGui::Separator();

	ImGui::InputFloat("Player move speed", &PlayerPtr->MoveSpeed, 1.0f, 5.0f, 3);
	ImGui::InputFloat("Player max speed", &PlayerPtr->MaxSpeed, 1.0f, 5.0f, 3);
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
	ImGui::Text("Player frametime multiplier: ");
	ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->FrametimeMultiplier).c_str());
	ImGui::InputFloat("Target player frametime multiplier", &PlayerPtr->FrametimeMultiplier);
	ImGui::Separator();

	//ImGui::Text("FPS: ");
	//ImGui::Separator();
	
	DrawTeleportGui(false, "Teleport", &TeleportWindowOpen, MainOverlayWindowFlags);
	ImGui::Separator();
	
	DrawPlayerVariablesGui(false, "Player variables", &PlayerVariablesGuiOpen, MainOverlayWindowFlags);
	ImGui::Separator();

	ImGui::Text("Misc Program Values:");

	ImGui::End();
}

void MainOverlay::DrawTeleportGui(bool UseSeparateWindow, const char* Title, bool* Open, ImGuiWindowFlags Flags)
{
	if (UseSeparateWindow)
	{
		if (!ImGui::Begin(Title, Open, Flags))
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

		ImGui::Text("Manual:");
		ImGui::Text("Current player position: ");
		ImGui::SameLine();
		std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
		ImGui::TextColored(SecondaryTextColor, PlayerPositionString.c_str());

		ImGui::PushItemWidth(232.0f);
		ImGui::Text("New player position:"); ImGui::SameLine();
		ImGui::InputFloat3("##Player Position Target", PlayerPositionTargetArray, 3);
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
			HumanTeleportUnsafe(PlayerPtr, vector(PlayerPositionTargetArray[0], PlayerPositionTargetArray[1], PlayerPositionTargetArray[2]), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("This will teleport the player to the value's you've typed, even if they are out of bounds. When setting TP points for later, try to set the y value a bit higher. If the game doesn't load quick enough your player will fall through the map. Usually the game will pull them back up, but sometimes it fails.");

		ImGui::PushItemWidth(232.0f);
		ImGui::Text("Player velocity:"); ImGui::SameLine();
		ImGui::InputFloat3("##Player velocity: ", (float*)&PlayerPtr->Velocity); ImGui::SameLine();
		/*if (ImGui::Button("Sync##PlayerVelocityTarget"))
		{
			PlayerVelocityTargetArray[0] = PlayerPtr->Velocity.x;
			PlayerVelocityTargetArray[1] = PlayerPtr->Velocity.y;
			PlayerVelocityTargetArray[2] = PlayerPtr->Velocity.z;
		}
		ImGui::SameLine();*/
		if (ImGui::Button("Set##PlayerVelocityTarget"))
		{
			PlayerPtr->Velocity.x = PlayerVelocityTargetArray[0];
			PlayerPtr->Velocity.y = PlayerVelocityTargetArray[1];
			PlayerPtr->Velocity.z = PlayerVelocityTargetArray[2];
			NeedPlayerVelocitySet = true;
		}
		ImGui::SameLine(); ShowHelpMarker("This is always equal to the true player velocity. Haven't quite nailed down how objects are moved yet so there's only partial control for now. You can still set the velocity, but once you move out of that edit box it'll go back to the normal values.");

		ImGui::Text("Presets:");
		if (ImGui::Button("Tutorial Area Hilltop"))
		{
			//HumanTeleportSafe(-2328.29f, 30.0f, -2317.9f);
			HumanTeleportUnsafe(PlayerPtr, vector(-2328.29f, 30.0f, -2317.9f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Tutorial area at the start of the game. Position: (-2328.29, 30.0, -2317.9)");
		if (ImGui::Button("Parker - Safehouse"))
		{
			//HumanTeleportSafe(-1877.77f, 27.0f, -1452.0f);
			HumanTeleportUnsafe(PlayerPtr, vector(-1877.77f, 27.0f, -1452.0f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Game starting safehouse. Near ore processing plant. Position: (-1877.77, 27.0, -1452.0)");
		if (ImGui::Button("Dust - Northern Safehouse"))
		{
			//HumanTeleportSafe(-387.0f, 38.0f, -820.0f);
			HumanTeleportUnsafe(PlayerPtr, vector(-387.0f, 38.0f, -820.0f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Near tharsis wind farm and Dust town hall. Position: (-387.0, 38.0, -820.0)");
		if (ImGui::Button("Dust - Southern Safehouse"))
		{
			//HumanTeleportSafe(-113.59f, 30.0f, -2449.58f);
			HumanTeleportUnsafe(PlayerPtr, vector(-113.59f, 30.0f, -2449.58f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Near chemical plant. Position: (-113.59, 30.0, -2449.58)");
		if (ImGui::Button("Badlands - Safehouse / RFHQ"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(2411.90f, 58.0f, -239.77f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Main safehouse in Badlands. Also the HQ of the Red Faction. Position: (2411.90, 58.0, -239.77)");
		if (ImGui::Button("Badlands - Mohole"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(1420.27f, -28.0f, -734.28f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Big 'ol hole in the ground used to pull heat from Mars' core for terraforming purposes. There's a smaller one in Dust. Position: (1420.27, -28.0, -734.28)");
		if (ImGui::Button("Badlands - Harrington Memorial Bridge"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(948.14f, -5.0f, -417.68f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("The big one. Position: (948.14, -5.0, -417.68)");
		if (ImGui::Button("Badlands - EDF Barracks"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(899.91f, 2.0f, -885.64f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("EDF Barracks sitting in a hilly area south of the EDF airbase in Badlands. Position: (899.91, 2.0, -885.64)");
		if (ImGui::Button("Badlands - Marauder Safehouse"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(2458.47f, 58.0f, -1210.17f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Safehouse in marauder territory. Unless you want hostile marauders, wait until you've completed certain missions to go here. Position: (2458.47, 58.0, -1210.17)");
		if (ImGui::Button("Oasis - Safehouse"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(1434.29f, 18.0f, 691.65f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Near EDF vehicle depot. Position: (1434.29, 18.0, 691.65)");
		if (ImGui::Button("Free Fire Zone - Artillery Base"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1752.03f, 9.0f, -132.59f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Base which runs and protects the EDF Artillery Gun. Deadly to be here until the FFZ has been liberated. Position: (-1752.03, 9.0, -132.59)");
		if (ImGui::Button("Free Fire Zone - Artillery Gun"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1944.92f, 38.0f, -65.49f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Bottom of the EDF Artillery Gun. Deadly to be here until the FFZ has been liberated. Position: (-1944.92, 38.0, -65.49)");
		if (ImGui::Button("EOS - Western Safehouse"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1726.0f, 50.0f, 438.0f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Near FFZ entrance/exit and Eos Memorial Bridge. Position: (-1726.0, 50.0, 438.0)");
		if (ImGui::Button("EOS - Eastern Safehouse"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1390.95f, 30.0f, 561.08f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Near construction site. Position: (-1390.95, 30.0, 561.08)");
		if (ImGui::Button("EOS - Outside EDF Central Command"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1428.61f, 8.0f, 2013.5f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Right outside the defense shield. Position: (-1428.61, 8.0, 2013.5)");
		if (ImGui::Button("EOS - Inside EDF Central Command"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1458.75f, 8.0f, 2050.16f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Right inside past the defense shield. Position: (-1458.75, 8.0, 2050.16)");
		if (ImGui::Button("EOS - EDF Central Command Main Building"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-1474.53f, 38.0f, 2397.49f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("The final building at the peak of the inner valley / cliffsides. Position: (-1474.53, 38.0, 2397.49)");
		if (ImGui::Button("Mount Vogel - Base"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-670.37f, 47.0f, 2423.75f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Bottom of Mount Vogel and mass accelerator. Several old buildings. Position: (-670.37, 47.0, 2423.75)");
		if (ImGui::Button("Mount Vogel - Peak"))
		{
			HumanTeleportUnsafe(PlayerPtr, vector(-285.77f, 183.0f, 2423.4f), PlayerPtr->Orientation);
		}
		TooltipOnPrevious("Peak of Mount Vogel with mass accelerator exit. Position: (-285.77, 183.0, 2423.4)");
	}
	TooltipOnPrevious("Manual and preset teleport controls for the player. Works in vehicles.");
}

void MainOverlay::DrawPlayerVariablesGui(bool UseSeparateWindow, const char* Title, bool* Open, ImGuiWindowFlags Flags)
{
	if (UseSeparateWindow)
	{
		if (!ImGui::Begin(Title, Open, Flags))
		{
			ImGui::End();
			return;
		}
	}

	if (ImGui::CollapsingHeader("Player values gui prototype"))
	{
		if (PlayerPtr != nullptr)
		{
			if (ImGui::TreeNode("Object values"))
			{
				//ImGui::Text("Object values");
				//ImGui::Separator();

				//Vftptr

				ImGui::Text("Position vector: "); ImGui::SameLine();
				std::string PlayerPositionString("(" + std::to_string(PlayerPtr->Position.x) + ", " + std::to_string(PlayerPtr->Position.y) + ", " + std::to_string(PlayerPtr->Position.z) + ")");
				ImGui::TextColored(SecondaryTextColor, PlayerPositionString.c_str());

				if (ImGui::TreeNode("Orientation matrix"))
				{
					std::string RightVectorString("(" + std::to_string(PlayerPtr->Orientation.rvec.x) + ", " + std::to_string(PlayerPtr->Orientation.rvec.y) + ", " + std::to_string(PlayerPtr->Orientation.rvec.z) + ")");
					std::string UpVectorString("(" + std::to_string(PlayerPtr->Orientation.uvec.x) + ", " + std::to_string(PlayerPtr->Orientation.uvec.y) + ", " + std::to_string(PlayerPtr->Orientation.uvec.z) + ")");
					std::string DirectionVectorString("(" + std::to_string(PlayerPtr->Orientation.fvec.x) + ", " + std::to_string(PlayerPtr->Orientation.fvec.y) + ", " + std::to_string(PlayerPtr->Orientation.fvec.z) + ")");
					//ImGui::Text("Orientation Matrix:");
					ImGui::Text("Right vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RightVectorString.c_str());
					ImGui::Text("Up vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, UpVectorString.c_str());
					ImGui::Text("Direction vector: "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, DirectionVectorString.c_str());

					ImGui::TreePop();
				}

				//ChildPtr
				//ChildNext
				//ChildPrevious
				//ChildConstraintPtr
				//HostConstraintPtr
				if (ImGui::TreeNode("Attach info"))
				{
					if (PlayerPtr->AttachInfo != nullptr)
					{
						ImGui::Text("Parent handle: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->parent_handle).c_str());
						ImGui::Text("Parent prop point: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->parent_prop_point).c_str());
						ImGui::Text("Child prop point: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->child_prop_point).c_str());
						if (ImGui::CollapsingHeader("Transform matrix"))
						{
							std::string RotationRow1("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.rvec.z) + ")");
							std::string RotationRow2("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.uvec.z) + ")");
							std::string RotationRow3("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.x) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.y) + ", " + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_rotation.fvec.z) + ")");
							ImGui::Text("Rotation:");
							ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow1.c_str());
							ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow2.c_str());
							ImGui::Text("    "); ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, RotationRow3.c_str());
							ImGui::Text("Translation:");
							std::string TranslationString("(" + std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.x) + ", "
								+ std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.y) + ", "
								+ std::to_string(PlayerPtr->AttachInfo->relative_transform.m_translation.z) + ")");
							ImGui::TextColored(SecondaryTextColor, TranslationString.c_str());
						}

						ImGui::Text("Use relative transform: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->use_relative_transform).c_str());
						ImGui::Text("Update physics: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->update_physics).c_str());
						ImGui::Text("Updated: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AttachInfo->updated).c_str());
					}
					else
					{
						ImGui::Text("\tAttach info is a null pointer. Cannot view");
					}
					ImGui::TreePop();
				}

				ImGui::Text("Havok handle: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->HavokHandle).c_str());

				if (ImGui::TreeNode("Contact info"))
				{
					if (PlayerPtr->ContactInfo.m_contact_list != nullptr)
					{
						ImGui::Text("Contact node: ##Player.Object.ContactInfo");
						ImGui::Text("Contacted objects: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ContactInfo.m_contact_list->m_contacted_object).c_str());
						ImGui::Text("Number of contacts: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ContactInfo.m_contact_list->m_num_contacts).c_str());
						//Todo: Iterate through linked list, give the user control over how far to do so. Note that it is a linked list to the user.
						//prev
						//next
					}
					else
					{
						ImGui::Text("\tContact info is a null pointer. Cannot view.");
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Object flags"))
				{
					ImGui::Text("Flagged list state: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.flagged_list_state).c_str());
					ImGui::Text("Lighting set once: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.lighting_set_once).c_str());
					ImGui::Text("Destroyed: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.destroyed).c_str());
					ImGui::Text("No save: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.no_save).c_str());
					ImGui::Text("Force full save: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.force_full_save).c_str());
					ImGui::Text("Destroy on stream: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.destroy_on_stream).c_str());
					ImGui::Text("Created by mission or activity: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.created_by_mission_or_activity).c_str());
					ImGui::Text("Don't transform: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.dont_transform).c_str());
					ImGui::Text("World free: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.world_free).c_str());
					ImGui::Text("Streaming: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.streaming).c_str());
					ImGui::Text("Streamed: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.streamed).c_str());
					ImGui::Text("Persistent: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.persistent).c_str());
					ImGui::Text("Original: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.original).c_str());
					ImGui::Text("Stub: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.stub).c_str());
					ImGui::Text("Preserve handle: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.preserve_handle).c_str());
					ImGui::Text("BPO index: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.bpo_index).c_str());
					ImGui::Text("Is dependent: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.is_dependent).c_str());
					ImGui::Text("Visited: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.visited).c_str());
					ImGui::Text("Special lifetime: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.special_lifetime).c_str());
					ImGui::Text("Serialize protected: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.serialize_protected).c_str());
					ImGui::Text("Dont use me: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags._dont_use_me).c_str());
					ImGui::Text("Streaming fixed: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.streaming_fixed).c_str());
					ImGui::Text("Render flags: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectFlags.render_flags).c_str());
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Remote object flags"))
				{
					ImGui::Text("Remote object: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.remote_object).c_str());
					ImGui::Text("Client sync: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.client_sync).c_str());
					ImGui::Text("Client destroy permission: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.client_destroy_permission).c_str());
					ImGui::Text("No destroy packet: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.no_destroy_packet).c_str());
					ImGui::Text("Common create: "); ImGui::SameLine();
					ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->RemoteObjectFlags.common_create).c_str());
					ImGui::TreePop();
				}

				ImGui::Text("MP dcmo index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MPDcmoIndex).c_str());
				ImGui::Text("Checking reset: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CheckingReset).c_str());
				ImGui::Text("Name index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->NameIndex).c_str());

				//Todo: Eventually haved linked list traversal, or object menu. Try adding names to menu as well if possible.
				//FlaggedNext
				//FlaggedPrevious

				ImGui::Text("Handle: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Handle).c_str());
				ImGui::Text("Parent: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->Parent).c_str());

				if (ImGui::TreeNode("Havok BPO"))
				{
					if (PlayerPtr->BPOHandle != nullptr)
					{
						ImGui::Text("Flags: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->flags).c_str());
						ImGui::Text("State: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->state).c_str());
						ImGui::Text("BPO Index: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->bpo_index).c_str());
						ImGui::Text("State Index: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->state_index).c_str());
						ImGui::Text("Owner: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->owner).c_str());
						ImGui::Text("Next: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->next).c_str());
						ImGui::Text("Previous: "); ImGui::SameLine();
						ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->BPOHandle->prev).c_str());
						//user_data
					}
					else
					{
						ImGui::Text("\tHavok BPO is a null pointer. Cannot view");
					}
					ImGui::TreePop();
				}

				ImGui::Text("All index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->AllIndex).c_str());
				ImGui::Text("Type index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->TypeIndex).c_str());
				ImGui::Text("Subtype index: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SubtypeIndex).c_str());
				ImGui::Text("Object type: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->ObjectType).c_str());
				ImGui::Text("Subtype: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SubType).c_str());

				ImGui::Text("Last known bmin: "); ImGui::SameLine();
				std::string LastKnownBminString("(" + std::to_string(PlayerPtr->LastKnownBMin.x) + ", " + std::to_string(PlayerPtr->LastKnownBMin.y) + ", " + std::to_string(PlayerPtr->LastKnownBMin.z) + ")");
				ImGui::TextColored(SecondaryTextColor, LastKnownBminString.c_str());

				ImGui::Text("Last known bmax: "); ImGui::SameLine();
				std::string LastKnownBmaxString("(" + std::to_string(PlayerPtr->LastKnownBMax.x) + ", " + std::to_string(PlayerPtr->LastKnownBMax.y) + ", " + std::to_string(PlayerPtr->LastKnownBMax.z) + ")");
				ImGui::TextColored(SecondaryTextColor, LastKnownBmaxString.c_str());

				ImGui::Text("SRID: "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->SRID).c_str());

				ImGui::TreePop();
			}
			if (ImGui::CollapsingHeader("Human values"))
			{
				//ImGui::Separator();
				//ImGui::Text("Human values");

				/*if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//Info

				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector
				//vector
				//vector

				if (ImGui::CollapsingHeader(""))
				{

				}

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}

				//vector
				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{
					//check nullptr
				}

				//ClothSim

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				//vector

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());

				if (ImGui::CollapsingHeader(""))
				{
					//Check nullptr
				}
				if (ImGui::CollapsingHeader(""))
				{

				}
				if (ImGui::CollapsingHeader(""))
				{

				}

				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine();
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				ImGui::Text(": "); ImGui::SameLine(); //Timestamp
				ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->).c_str());
				//Previous value is Timestamp TurretHoldAnimations. Still several dozen values left.*/
			}
			if (ImGui::CollapsingHeader("Player values"))
			{
				//ImGui::Separator();
				//ImGui::Text("Player values");
			}




		}
		else
		{
			ImGui::Text("Player pointer is null. Cannot view");
		}
	}
}

void MainOverlay::ShowAboutWindow(bool* p_open)
{
	if (!ImGui::Begin("About Dear ImGui", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}
	ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
	ImGui::Separator();
	ImGui::Text("By Omar Cornut and all dear imgui contributors.");
	ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");

	static bool show_config_info = false;
	ImGui::Checkbox("Config/Build Information", &show_config_info);
	if (show_config_info)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		bool copy_to_clipboard = ImGui::Button("Copy to clipboard");
		ImGui::BeginChildFrame(ImGui::GetID("cfginfos"), ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 18), ImGuiWindowFlags_NoMove);
		if (copy_to_clipboard)
			ImGui::LogToClipboard();

		ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
		ImGui::Separator();
		ImGui::Text("sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
		ImGui::Text("define: __cplusplus=%d", (int)__cplusplus);
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_OBSOLETE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_WIN32_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_MATH_FUNCTIONS
		ImGui::Text("define: IMGUI_DISABLE_MATH_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
		ImGui::Text("define: IMGUI_DISABLE_DEFAULT_ALLOCATORS");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
		ImGui::Text("define: IMGUI_USE_BGRA_PACKED_COLOR");
#endif
#ifdef _WIN32
		ImGui::Text("define: _WIN32");
#endif
#ifdef _WIN64
		ImGui::Text("define: _WIN64");
#endif
#ifdef __linux__
		ImGui::Text("define: __linux__");
#endif
#ifdef __APPLE__
		ImGui::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
		ImGui::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef __MINGW32__
		ImGui::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
		ImGui::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
		ImGui::Text("define: __GNUC__=%d", (int)__GNUC__);
#endif
#ifdef __clang_version__
		ImGui::Text("define: __clang_version__=%s", __clang_version__);
#endif
		ImGui::Separator();
		ImGui::Text("io.BackendPlatformName: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
		ImGui::Text("io.BackendRendererName: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
		ImGui::Text("io.ConfigFlags: 0x%08X", io.ConfigFlags);
		if (io.ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard)        ImGui::Text(" NavEnableKeyboard");
		if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)         ImGui::Text(" NavEnableGamepad");
		if (io.ConfigFlags & ImGuiConfigFlags_NavEnableSetMousePos)     ImGui::Text(" NavEnableSetMousePos");
		if (io.ConfigFlags & ImGuiConfigFlags_NavNoCaptureKeyboard)     ImGui::Text(" NavNoCaptureKeyboard");
		if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)                  ImGui::Text(" NoMouse");
		if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)      ImGui::Text(" NoMouseCursorChange");
		if (io.MouseDrawCursor)                                         ImGui::Text("io.MouseDrawCursor");
		if (io.ConfigMacOSXBehaviors)                                   ImGui::Text("io.ConfigMacOSXBehaviors");
		if (io.ConfigInputTextCursorBlink)                              ImGui::Text("io.ConfigInputTextCursorBlink");
		if (io.ConfigWindowsResizeFromEdges)                            ImGui::Text("io.ConfigWindowsResizeFromEdges");
		if (io.ConfigWindowsMoveFromTitleBarOnly)                       ImGui::Text("io.ConfigWindowsMoveFromTitleBarOnly");
		ImGui::Text("io.BackendFlags: 0x%08X", io.BackendFlags);
		if (io.BackendFlags & ImGuiBackendFlags_HasGamepad)             ImGui::Text(" HasGamepad");
		if (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        ImGui::Text(" HasMouseCursors");
		if (io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         ImGui::Text(" HasSetMousePos");
		ImGui::Separator();
		ImGui::Text("io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexWidth, io.Fonts->TexHeight);
		ImGui::Text("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
		ImGui::Separator();
		ImGui::Text("style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y);
		ImGui::Text("style.WindowBorderSize: %.2f", style.WindowBorderSize);
		ImGui::Text("style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y);
		ImGui::Text("style.FrameRounding: %.2f", style.FrameRounding);
		ImGui::Text("style.FrameBorderSize: %.2f", style.FrameBorderSize);
		ImGui::Text("style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y);
		ImGui::Text("style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

		if (copy_to_clipboard)
			ImGui::LogFinish();
		ImGui::EndChildFrame();
	}
	ImGui::End();
}

bool MainOverlay::ShowStyleSelector(const char* label)
{
	static int style_idx = -1;
	if (ImGui::Combo(label, &style_idx, "Classic\0Dark\0Light\0"))
	{
		switch (style_idx)
		{
		case 0: ImGui::StyleColorsClassic(); break;
		case 1: ImGui::StyleColorsDark(); break;
		case 2: ImGui::StyleColorsLight(); break;
		}
		return true;
	}
	return false;
}

void MainOverlay::ShowFontSelector(const char* label)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font_current = ImGui::GetFont();
	if (ImGui::BeginCombo(label, font_current->GetDebugName()))
	{
		for (int n = 0; n < io.Fonts->Fonts.Size; n++)
			if (ImGui::Selectable(io.Fonts->Fonts[n]->GetDebugName(), io.Fonts->Fonts[n] == font_current))
				io.FontDefault = io.Fonts->Fonts[n];
		ImGui::EndCombo();
	}
	ImGui::SameLine();
	ShowHelpMarker(
		"- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
		"- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
		"- Read FAQ and documentation in misc/fonts/ for more details.\n"
		"- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}

void MainOverlay::ShowExampleAppMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void MainOverlay::ShowExampleAppPropertyEditor(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Example: Property editor", p_open))
	{
		ImGui::End();
		return;
	}

	ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::Columns(2);
	ImGui::Separator();

	struct funcs
	{
		static void ShowDummyObject(const char* prefix, int uid)
		{
			ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
			ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
			bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
			ImGui::NextColumn();
			ImGui::AlignTextToFramePadding();
			ImGui::Text("my sailor is rich");
			ImGui::NextColumn();
			if (node_open)
			{
				static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
				for (int i = 0; i < 8; i++)
				{
					ImGui::PushID(i); // Use field index as identifier.
					if (i < 2)
					{
						ShowDummyObject("Child", 424242);
					}
					else
					{
						// Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
						ImGui::AlignTextToFramePadding();
						ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
						ImGui::NextColumn();
						ImGui::PushItemWidth(-1);
						if (i >= 5)
							ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
						else
							ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
						ImGui::PopItemWidth();
						ImGui::NextColumn();
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}
			ImGui::PopID();
		}
	};

	// Iterate dummy objects with dummy members (all the same data)
	for (int obj_i = 0; obj_i < 3; obj_i++)
		funcs::ShowDummyObject("Object", obj_i);

	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::PopStyleVar();
	ImGui::End();
}

void MainOverlay::ShowExampleAppLongText(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Example: Long text display", p_open))
	{
		ImGui::End();
		return;
	}

	static int test_type = 0;
	static ImGuiTextBuffer log;
	static int lines = 0;
	ImGui::Text("Printing unusually long amount of text.");
	ImGui::Combo("Test type", &test_type, "Single call to TextUnformatted()\0Multiple calls to Text(), clipped manually\0Multiple calls to Text(), not clipped (slow)\0");
	ImGui::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
	if (ImGui::Button("Clear")) { log.clear(); lines = 0; }
	ImGui::SameLine();
	if (ImGui::Button("Add 1000 lines"))
	{
		for (int i = 0; i < 1000; i++)
			log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines + i);
		lines += 1000;
	}
	ImGui::BeginChild("Log");
	switch (test_type)
	{
	case 0:
		// Single call to TextUnformatted() with a big buffer
		ImGui::TextUnformatted(log.begin(), log.end());
		break;
	case 1:
	{
		// Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		ImGuiListClipper clipper(lines);
		while (clipper.Step())
			for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	case 2:
		// Multiple calls to Text(), not clipped (slow)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		for (int i = 0; i < lines; i++)
			ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
		ImGui::PopStyleVar();
		break;
	}
	ImGui::EndChild();
	ImGui::End();
}

void MainOverlay::ShowExampleAppSimpleOverlay(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 0;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	if (corner != -1)
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}