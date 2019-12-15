#include "Globals.h"
#include "SnippetManager.h"

std::shared_ptr<Hypodermic::Container> IocContainer = nullptr;

namespace Globals
{
    //Keeps track of how long someone has held down the deactivation key. Currently F3.
    extern uint ExitKeysPressCount = 0;

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
    stream_grid* MainStreamGrid = nullptr;
    GraphicsStateWrapper GraphicsState;

    keen::ImmediateRenderer* ImmediateRenderer = nullptr;
    
    FixedArrayWrapper<explosion_info> ExplosionInfos;
    uint* NumExplosionInfos = nullptr;

    FixedArrayWrapper<material_effect_info> MaterialEffectInfos;
    uint* NumMaterialEffectInfos;

    FixedArrayWrapper<effect_info> EffectInfos;
    uint* NumEffectInfos;

    rfg::farray<vehicle_info, 163> * VehicleInfos;

    FixedArrayWrapper<int> ShadowMapSizes; 

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

	const ImVec4 SecondaryTextColor(0.2f, 0.7f, 1.0f, 1.00f); //Light blue
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
    bool DumpTexturesWhenLoading = false;
    bool DisableNumpadWhileOverlayVisible = true;
	nlohmann::json MainConfig;
	float DefaultFreeCameraSpeed = 0.3f;
	float DefaultRotationSpeed = 0.7f;

	IDXGISwapChain* D3D11SwapchainPtr = nullptr;
	ID3D11Device* D3D11Device = nullptr;
	ID3D11DeviceContext* D3D11Context = nullptr;
	ID3D11RenderTargetView* MainRenderTargetView = nullptr;
	HWND GameWindowHandle = nullptr;
	RECT WindowRect = { 0, 0, 0, 0 };
    keen::GraphicsSystem* GraphicsSystemPtr = nullptr;

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
	bool HookDidFrame = false;

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

    bool ReadyForImGuiInit = false;

    bool* UnlimitedAmmo = nullptr;
    bool* UnlimitedMagazineAmmo = nullptr;
    bool* UnlimitedAiThrownWeapons = nullptr;
    float* VehicleMaxSpeed = nullptr;
    bool* SsaoVisionEnabled = nullptr;
    int* RfgMaxCharges = nullptr;
    bool* TodEnabled = nullptr;
    //float* TodOverride = nullptr;
    float* CurrentTimeOfDay = nullptr;

    bool LockoutModeEnabled = false;

    int* ChargeExplosionDelay = nullptr;

    rfg::farray<ui_menu*, 8>* RfgMenusList = nullptr;

    bool DisableDebrisDeletion = false;
    bool FindGmOverride = false;
    bool UseFindGmOverride = false;

    FixedArrayWrapper<weapon_info> WeaponInfos;
    uint* NumWeaponInfos = nullptr;

    float* SpeedScale = nullptr;
    float* Frametime;
    float* PlayerMaxMovementSpeedOverride;

    bool CanTriggerOnLoadEvent = true;
    bool ForceVehicleDrops = false;

    vehicle_spawn_params VehicleSpawnCache;

    bool PlayerNeedsTeleport = false;
    vector PlayerTeleportPos {0.0f};

    namespace Launcher
    {
        bool ShouldRunRsl = false;
        bool LauncherRan = false;
    }

	const char* GetScriptLoaderVersion()
	{
		return RSL_VERSION;
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
		catch (std::exception& Ex)
		{
			std::string ExceptionInfo = Ex.what();
			ExceptionInfo += " \nstd::exception, Additional info: ";
			ExceptionInfo += "File: ";
			ExceptionInfo += __FILE__;
			ExceptionInfo += ", Function: ";
			ExceptionInfo += __FUNCSIG__;
			ExceptionInfo += ", Line: ";
			ExceptionInfo += __LINE__;
			throw(std::exception(ExceptionInfo.c_str()));
		}
	}

	float FloatConvertDegreesToRadians(float AngleInDegrees)
	{
		return (Globals::pi / 180.0f) * AngleInDegrees;
	}

    float FloatConvertRadiansToDegrees(float AngleInRadians)
    {
        return (180.0f / Globals::pi) * AngleInRadians;
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
		std::string PathString = std::string(result, GetModuleFileName(0, result, MAX_PATH));

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

    void SetFloat(float* Address, float NewValue)
    {
        DWORD OriginalProtectionPermissions;
        DWORD Backup;
        VirtualProtect(Address, sizeof(float), PAGE_EXECUTE_READWRITE, &OriginalProtectionPermissions);
        *Address = NewValue;
        VirtualProtect(Address, sizeof(float), OriginalProtectionPermissions, &Backup);
    }

    void EnableMemoryRegionReadWrite(void* RegionAddress, ulong RegionSize)
    {
        DWORD OriginalProtectionPermissions;
        VirtualProtect(RegionAddress, RegionSize, PAGE_READWRITE, &OriginalProtectionPermissions);
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

    std::string CharArrayToString(char* Array, int Size)
    {
        std::string String;
        for(int i = 0; i < Size; i++)
        {
            if(Array[i] == '\0')
            {
                break; //Stop at null terminator. Including null characters can mess up string comparisons elsewhere.
            }
            String += Array[i];
        }
        return String;
    }

    std::string CharArrayToString(const char* Array, int Size)
	{
        return CharArrayToString(const_cast<char*>(Array), Size);
	}

    //Attempts to disable the main menu buttons for disabled features such as MP, LAN, and Wrecking Crew.
    void TryHideInvalidMainMenuOptions()
    {
        if(RfgMenusList)
        {
            if((*RfgMenusList)[0])
            {
                ui_menu& Menu = *(*RfgMenusList)[0];
                if(Menu.m_num_items == 9)
                {
                    if(Menu.m_items[0])
                    {
                        if(CharArrayToString(Menu.m_items[0]->m_caption, 128) == "MENU_NEW_GAME") //The main menu doesn't have a title, so we have to look for it's buttons
                        {                   
                            ui_menu_item_base& WreckingCrewButton = *Menu.m_items[2];
                            WreckingCrewButton.m_enabled = false;
                            WreckingCrewButton.m_visible = false;

                            ui_menu_item_base& MultiplayerButton = *Menu.m_items[3];
                            MultiplayerButton.m_enabled = false;
                            MultiplayerButton.m_visible = false;

                            ui_menu_item_base& LanCrewButton = *Menu.m_items[5];
                            LanCrewButton.m_enabled = false;
                            LanCrewButton.m_visible = false;
                        }
                    }
                }
            }
        }
    }

    //Logs information about the currently loaded native game menus
    void LogGameMenuInfo()
    {
        if (!RfgMenusList)
        {
            Logger::LogWarning("RfgMenusList is a nullptr, cannot log it's values.\n");
        }
        Logger::Log("\n\nLogging rfg menu info:\n");
        for (int i = 0; i < Globals::RfgMenusList->Capacity(); i++)
        {
            if ((*Globals::RfgMenusList)[i])
            {
                ui_menu& Menu = *(*Globals::RfgMenusList)[i];
                Logger::Log("\n\n\tLogging menu info at index {}:\n", i);
                Logger::Log("\t\tTitle: {}\n", Globals::CharArrayToString(Menu.m_title, 192));
                Logger::Log("\t\tSupress accept sounds?: {}\n", Menu.m_surpress_accept_sounds);
                Logger::Log("\t\tShould tween out?: {}\n", Menu.m_should_tween_out);
                Logger::Log("\t\tAwaiting tween on select end?: {}\n", Menu.m_awaiting_tween_on_select_end);
                Logger::Log("\t\tAwaiting tween fade in end?: {}\n", Menu.m_awaiting_tween_fade_in_end);
                Logger::Log("\t\tForce update?: {}\n", Menu.m_force_update);
                Logger::Log("\t\tChoose on enter: {}\n", Menu.m_choose_on_enter);
                Logger::Log("\t\tHandle: {}\n", Menu.m_handle);
                Logger::Log("\t\tDoc handle: {}\n", Menu.m_doc_handle);
                Logger::Log("\t\tInput id: {}\n", Menu.m_input_id);
                Logger::Log("\t\tSelected?: {}\n", Menu.m_selected);
                Logger::Log("\t\tNum items: {}\n", Menu.m_num_items);

                Logger::Log("\t\tLogging ui_menu_items:\n");
                for (int j = 0; j < 15; j++)
                {
                    if (Menu.m_items[j])
                    {
                        Logger::Log("\n\t\t\tLogging menu item at index {}\n", j);
                        //Todo: Check the type of each item, and cast to it's derived type such as ui_menu_item_func or ui_menu_item_bool
                        ui_menu_item_base& Item = *Menu.m_items[j];
                        Logger::Log("\t\t\tCaption: {}\n", Globals::CharArrayToString(Item.m_caption, 128));
                        Logger::Log("\t\t\tPlay change sound?: {}\n", Item.m_play_change_sound);
                        Logger::Log("\t\t\tSelected?: {}\n", Item.m_selected);
                        Logger::Log("\t\t\tEnabled?: {}\n", Item.m_enabled);
                        Logger::Log("\t\t\tVisible?: {}\n", Item.m_visible);
                        Logger::Log("\t\t\tHandle: {}\n", Item.m_handle);
                        Logger::Log("\t\t\tType: {}\n", Item.m_type);
                        //Logger::Log("\t\t\t: {}", Item.m_parent);
                    }
                    else
                    {
                        Logger::Log("ui_menu_item at index {} is a nullptr, reached end of menu items list.\n", j);
                        break;
                    }
                }

                //Log document_info
                //Log hint_info

                //Logger::Log("\t\t: {}\n", Menu.m_num_items);
                //Logger::Log("\t\t: {}\n", Menu.m_num_items);
                //Logger::Log("\t\t: {}\n", Menu.m_num_items);
            }
            else
            {
                Logger::Log("ui_menu at index {} is a nullptr, reached end of menus list.\n", i);
                break;
            }
        }
    }

    std::string GetLastWin32ErrorAsString()
    {
        //Get the error message, if any.
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0)
            return std::string(); //No error message has been recorded

        LPSTR messageBuffer = nullptr;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)& messageBuffer, 0, NULL);

        std::string message(messageBuffer, size);

        //Free the buffer.
        LocalFree(messageBuffer);

        return message;
    }

    std::string RemoveFileExtension(const std::string& Filename)
    {
        return Filename.substr(0, Filename.find_last_of('.'));
    }

    std::array<std::string, 2> SplitFilename(const std::string& Filename)
    {
        return
        {
            Filename.substr(0, Filename.find_last_of('.')),
            Filename.substr(Filename.find_last_of('.'), Filename.length() - 1)
        };
    }

    std::optional<explosion_info*> GetExplosionInfo(std::string Name)
    {
        if(ExplosionInfos.Initialized())
        {
            for(int i = 0; i < ExplosionInfos.Size(); i++)
            {
                if(CharArrayToString(ExplosionInfos[i].m_name, 32) == Name)
                {
                    return const_cast<explosion_info*>(&ExplosionInfos[i]);
                }
            }
        }
        return {};
    }

    std::vector<HANDLE> RfgThreadHandles;

    /*Be VERY VERY careful with this function or else you might crash your PC or other programs.
     * Mainly since I don't know if it could pause the threads of all other programs if edited.
     */
    void SuspendAllThreadsExceptLauncher(HANDLE LauncherThreadHandle)
    {
        const DWORD LauncherThreadID = GetThreadId(LauncherThreadHandle);
        HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (h != INVALID_HANDLE_VALUE)
        {
            THREADENTRY32 te;
            te.dwSize = sizeof(te);
            if (Thread32First(h, &te))
            {
                do
                {
                    if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID))
                    {
                        if (te.th32OwnerProcessID == Globals::PID)
                        {
                            if (te.th32ThreadID != LauncherThreadID)
                            {
                                HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
                                RfgThreadHandles.push_back(ThreadHandle);
                                if (ThreadHandle)
                                {
                                    SuspendThread(ThreadHandle);
                                }
                            }
                            //printf("Process 0x%04x Thread 0x%04x\n", te.th32OwnerProcessID, te.th32ThreadID);
                            //if(te.th32ThreadID == LauncherThreadID)
                            //{
                            //    printf("^^^That's the launcher thread!\n");
                            //}
                        }
                    }
                    te.dwSize = sizeof(te);
                } while (Thread32Next(h, &te));
            }
            CloseHandle(h);
        }
    }

    void ResumeAllThreads()
    {
        for (auto& i : RfgThreadHandles)
        {
            ResumeThread(i);
        }
    }
}
