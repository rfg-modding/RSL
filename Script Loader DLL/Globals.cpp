#include "Globals.h"

namespace Globals
{
	ProgramManager* Program = nullptr;
	GuiSystem* Gui = nullptr;
	ScriptManager* Scripts = nullptr;
	CameraWrapper* Camera = nullptr;

	Player* PlayerPtr;
	World* RfgWorldPtr = nullptr;
	rl_light* TODLightPtr = nullptr;
	rl_camera* RlCameraPtr = nullptr;
	rl_renderer* RlRendererPtr = nullptr;
	rl_render_lib* RlRenderLibPtr = nullptr;
	rl_state_manager* RlStateManagerPtr = nullptr;
	rl_scene* MainScenePtr = nullptr;
	rl_scene_renderer* MainSceneRendererPtr = nullptr;
	rl_camera* MainSceneCameraPtr = nullptr;
	hkpWorld* hkpWorldPtr = nullptr;
	lua_State* RfgVintLuaState = nullptr;
	hkpRigidBody* PlayerRigidBody = nullptr;
    keen::GraphicsSystem* KeenGraphicsSystemPtr = nullptr;

	DWORD MouseGenericPollMouseVisible = 0;
	DWORD CenterMouseCursorCall = 0;

	const ImVec4 ColorTransparent = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	const ImVec4 ColorRed = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	const ImVec4 ColorGreen = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	const ImVec4 ColorBlue = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
	const ImVec4 ColorBlack = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	const ImVec4 ColorWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	const ImVec4 ColorPurple = ImVec4(0.227f, 0.0f, 0.6588f, 1.0f);
	const ImVec4 ColorOrange = ImVec4(1.0f, 0.4157f, 0.0f, 1.0f);
	const ImVec4 ColorYellow = ImVec4(1.0f, 0.8902f, 0.0666f, 1.0f);

	const ImVec4 SecondaryTextColor(0.20f, 0.55f, 0.83f, 1.00f); //Light blue
	const ImVec4 ColorBlue2 = ImVec4(0.10f, 0.40f, 0.75f, 1.0f);

	const float pi = 3.14159265f;

	HMODULE ScriptLoaderModule = nullptr;
	uintptr_t ModuleBase = 0;
	DWORD PID = 0;

	ImFont* FontNormal = nullptr;
	ImFont* FontBig = nullptr;
	ImFont* FontLarge = nullptr;
	ImFont* FontHuge = nullptr;

	bool OpenDebugConsole = false;
	nlohmann::json MainConfig;
	float DefaultFreeCameraSpeed = 0.3f;
	float DefaultRotationSpeed = 0.7f;

	IDXGISwapChain* D3D11SwapchainPtr = nullptr;
	ID3D11Device* D3D11Device = nullptr;
	ID3D11DeviceContext* D3D11Context = nullptr;
	ID3D11RenderTargetView* MainRenderTargetView = nullptr;
	HWND GameWindowHandle = nullptr;
	RECT WindowRect = { 0, 0, 0, 0 };

	RenderInterfaceD3D11* DebugDrawRenderInterface = nullptr;
    matrix44 vpMatrix;

	bool ShowMainOverlay = true;

	float OverlayFontSize = 16.0f;
	bool show_demo_window = false;
	bool ImGuiInitialized = false;
	ImGuiIO io;
	bool OverlayActive = false;
	WNDPROC OriginalWndProc = nullptr;
	bool FirstPersonModeActive = false;

	float GlobalExplosionStrengthMultiplier = 2.0f;
	bool UseGlobalExplosionStrengthMultiplier = false;
	bool UseExplosionRadiusLimits = true;
	float MinimumExplosionRadius = 0.0f;
	float MaximumExplosionRadius = 12.0f;

	bool InfiniteJetpack = false;

	HANDLE ConsoleHandle = nullptr;
	bool* InMultiplayer = nullptr;
	bool MultiplayerHookTriggered = false;

	const WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	const WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	const WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
	const WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
	const WORD ConsoleFatalErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
	const WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	const WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	bool BlockNextTildeInput = false;
	bool ScriptLoaderCloseRequested = false;

	bool HudVisible = true;
	bool FogVisible = true;

	const std::string ScriptLoaderVersion("0.4.0-Alpha");

	const char* GetScriptLoaderVersion()
	{
		return Globals::ScriptLoaderVersion.c_str();
	}

	bool DirectoryExists(const std::string& Directory)
	{
		return !(!fs::is_directory(Directory) || !fs::exists(Directory));
	}

	void CreateDirectoryIfNull(const std::string& Directory)
	{
		try
		{
			if (!DirectoryExists(Directory))
			{
				fs::create_directory(Directory);
			}
		}
		catch (fs::filesystem_error& Ex)
		{
			std::string ExceptionInfo = Ex.what();
			ExceptionInfo += " \nstd::filesystem::filesystem_error, Additional info: ";
			ExceptionInfo += "File: ";
			ExceptionInfo += __FILE__;
			ExceptionInfo += ", Function: ";
			ExceptionInfo += __func__;
			ExceptionInfo += ", Line: ";
			ExceptionInfo += __LINE__;
			throw(std::exception(ExceptionInfo.c_str()));
		}
		catch (std::exception& Ex)
		{
			std::string ExceptionInfo = Ex.what();
			ExceptionInfo += " \nstd::exception, Additional info: ";
			ExceptionInfo += "File: ";
			ExceptionInfo += __FILE__;
			ExceptionInfo += ", Function: ";
			ExceptionInfo += __func__;
			ExceptionInfo += ", Line: ";
			ExceptionInfo += __LINE__;
			throw(std::exception(ExceptionInfo.c_str()));
		}
		catch (...)
		{
			std::string ExceptionInfo;
			ExceptionInfo += " \nDefault exception detected caught! Additional info: ";
			ExceptionInfo += "File: ";
			ExceptionInfo += __FILE__;
			ExceptionInfo += ", Function: ";
			ExceptionInfo += __func__;
			ExceptionInfo += ", Line: ";
			ExceptionInfo += __LINE__;
			throw std::exception(ExceptionInfo.c_str());
		}
	}

	float FloatConvertDegreesToRadians(float AngleInDegrees)
	{
		return (Globals::pi / 180.0f) * AngleInDegrees;
	}

	float sind(float AngleInDegrees)
	{
		return sin(FloatConvertDegreesToRadians(AngleInDegrees));
	}

	float cosd(float AngleInDegrees)
	{
		return cos(FloatConvertDegreesToRadians(AngleInDegrees));
	}

	float tand(float AngleInDegrees)
	{
		return tan(FloatConvertDegreesToRadians(AngleInDegrees));
	}

	void SetConsoleAttributes(WORD Attributes)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
	}

	void ResetConsoleAttributes()
	{
		SetConsoleAttributes(Globals::ConsoleDefaultTextAttributes);
	}

	HWND FindTopWindow(DWORD pid)
	{
		std::pair<HWND, DWORD> params = { nullptr, pid };

		// Enumerate the windows using a lambda to process each window
		const BOOL bResult = EnumWindows([](const HWND hwnd, LPARAM lParam) -> BOOL
		{
				const auto pParams = reinterpret_cast<std::pair<HWND, DWORD>*>(lParam);

				DWORD processId;
				if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second)
				{
					// Stop enumerating
					SetLastError(-1);
					pParams->first = hwnd;
					return FALSE;
				}

				// Continue enumerating
				return TRUE;
		}, reinterpret_cast<LPARAM>(&params));

		if (!bResult && GetLastError() == -1 && params.first)
		{
			return params.first;
		}

		return nullptr;
	}

	HWND FindRfgTopWindow()
	{
		return FindTopWindow(GetProcessID("rfg.exe"));
	}

	DWORD GetProcessID(const std::string& ProcessName)
	{
		PROCESSENTRY32 ProcessSnapshotStructure = { 0 };
		const HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		ProcessSnapshotStructure.dwSize = sizeof(PROCESSENTRY32);

		if (Snapshot == INVALID_HANDLE_VALUE)
		{
			return 0;
		}
		if (Process32First(Snapshot, &ProcessSnapshotStructure) == FALSE)
		{
			return 0;
		}

		while (Process32Next(Snapshot, &ProcessSnapshotStructure))
		{
			if (!strcmp(ProcessSnapshotStructure.szExeFile, ProcessName.c_str()))
			{
				CloseHandle(Snapshot);
				//std::cout << "[+]Process name is: " << ProcessName << "\n[+]Process ID: " << ProcessSnapshotStructure.th32ProcessID << "\n";
				//std::cout << "PID: " << ProcessSnapshotStructure.th32ProcessID << "\n";
				return ProcessSnapshotStructure.th32ProcessID;
			}
		}
		CloseHandle(Snapshot);

		//std::cerr << "[!]Unable to find Process ID\n";
		return 0;
	}

	void EnforceFloatRange(float& Value, float& Minimum, float& Maximum)
	{
		if (Value < Minimum)
		{
			Value = Minimum;
		}
		if (Value > Maximum)
		{
			Value = Maximum;
		}
	}

	void ChangeMemoryFloat(DWORD BaseAddress, float Value, DWORD Offset1, DWORD Offset2, bool PrintMessage)
	{
		DWORD* Address = reinterpret_cast<DWORD*>((*reinterpret_cast<DWORD*>(BaseAddress + Offset1)) + Offset2);

		if (PrintMessage)
		{
			char szTest[10];
			sprintf_s(szTest, "The final address is : %X", (unsigned int)Address);
			MessageBoxA(nullptr, szTest, nullptr, 0);
		}

		//VirtualProtect((LPVOID)Address, sizeof(Value), PAGE_EXECUTE_READWRITE, &d);    
		*(float*)Address = Value;
		//VirtualProtect((LPVOID)adress ,sizeof(value),d,&ds);
	}

	std::string GetEXEPath(bool IncludeExeInPath)
	{
		char result[MAX_PATH];
		std::string PathString = std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));

		if (IncludeExeInPath)
		{
			return PathString;
		}
		unsigned int ExeNameStart = PathString.length();
		for (unsigned int i = PathString.length(); i > 0; i--)
		{
			if (PathString.compare(i, 1, "\\") == 0 || PathString.compare(i, 1, "/") == 0)
			{
				ExeNameStart = i;
				break;
			}
		}
		PathString = PathString.substr(0, ExeNameStart + 1);

		return PathString;
	}

	void PlaceNOP(BYTE* Address, DWORD Length)
	{
		DWORD OriginalProtectionPermissions;
		DWORD Backup;
		VirtualProtect(Address, Length, PAGE_EXECUTE_READWRITE, &OriginalProtectionPermissions);
		for (DWORD i = 0x0; i < Length; i++)
		{
			*(Address + i) = 0x90; //NOP, 144 as int, using int when storing opcodes
		}
		VirtualProtect(Address, Length, OriginalProtectionPermissions, &Backup);
	}

	//Get all module related info, this will include the base DLL and the size of the module
	MODULEINFO GetModuleInfo(const char* ModuleName)
	{
		MODULEINFO ModuleInfo = { nullptr };
		const HMODULE hModule = GetModuleHandle(ModuleName);
		if (hModule == nullptr)
		{
			return ModuleInfo;
		}
		GetModuleInformation(GetCurrentProcess(), hModule, &ModuleInfo, sizeof(MODULEINFO));
		return ModuleInfo;
	}

	DWORD FindPattern(const char* ModuleName, const char* PatternString, const char* MaskString)
	{
		MODULEINFO mInfo = GetModuleInfo(ModuleName);

		const DWORD Base = reinterpret_cast<DWORD>(mInfo.lpBaseOfDll);
		const DWORD Size = static_cast<DWORD>(mInfo.SizeOfImage);
		const DWORD PatternLength = static_cast<DWORD>(strlen(MaskString));

		for (DWORD i = 0; i < Size - PatternLength; i++)
		{
			bool Found = true;
			for (DWORD j = 0; j < PatternLength; j++)
			{
				//if we have a ? in our MaskString then we have true by default, 
				//or if the bytes match then we keep searching until finding it or not
				Found &= MaskString[j] == '?' || PatternString[j] == *reinterpret_cast<char*>(Base + i + j);
			}

			//if Found = true, the entire pattern was found
			if (Found)
			{
				return Base + i;
			}
		}
		std::cout << "Error! Failed to find asm Pattern!\n";
		return 0;
	}
}
