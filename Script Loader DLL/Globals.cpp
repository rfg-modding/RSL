#include "Globals.h"

ImFont* FontNormal;
ImFont* FontLarge;
ImFont* FontHuge;

bool OpenDebugConsole = false;
nlohmann::json MainConfig;
float DefaultFreeCameraSpeed = 0.3f;
float DefaultRotationSpeed = 0.7f;

IDXGISwapChain* D3D11SwapchainPtr = nullptr;
ID3D11Device* D3D11Device = nullptr;
ID3D11DeviceContext* D3D11Context = nullptr;
ID3D11RenderTargetView* MainRenderTargetView = nullptr;
HWND hwnd = NULL;
ImVec4* Colors = nullptr;

//MainOverlay Overlay;
bool ShowMainOverlay = true;

float OverlayFontSize = 16.0f;
bool show_demo_window = true;
bool ImGuiInitialized = false;
ImGuiIO io;
bool OverlayActive = false;
WNDPROC OriginalWndProc = NULL;
bool FirstPersonModeActive = false;

float GlobalExplosionStrengthMultiplier = 2.0f;
bool UseGlobalExplosionStrengthMultiplier = false;
bool UseExplosionRadiusLimits = true;
float MinimumExplosionRadius = 0.0f;
float MaximumExplosionRadius = 12.0f;
DWORD* GlobalPlayerPtr = nullptr;

bool InfiniteJetpack = false;

sol::state Lua;

HANDLE ConsoleHandle = { 0 };
DWORD* InMultiplayer = nullptr;
bool MultiplayerHookTriggered = false;

const WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
const WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD ConsoleFatalErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
const WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

void* GlobalRlDrawPtr = nullptr;

const char* GetScriptLoaderVersion()
{
	return ScriptLoaderVersion;
}

void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

bool DirectoryExists(std::string Directory)
{
	if (!fs::is_directory(Directory) || !fs::exists(Directory))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CreateDirectoryIfNull(std::string Directory)
{
	if (!DirectoryExists(Directory))
	{
		fs::create_directory(Directory);
	}
}

float FloatConvertDegreesToRadians(float AngleInDegrees)
{
	return (pi / 180.0f) * AngleInDegrees;
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
	SetConsoleAttributes(ConsoleDefaultTextAttributes);
}

HWND FindTopWindow(DWORD pid)
{
	std::pair<HWND, DWORD> params = { 0, pid };

	// Enumerate the windows using a lambda to process each window
	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
	{
		auto pParams = (std::pair<HWND, DWORD>*)(lParam);

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
	}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
	{
		return params.first;
	}

	return 0;
}

DWORD GetProcessID(std::string ProcessName)
{
	PROCESSENTRY32 ProcessSnapshotStructure = { 0 };
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

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
			//std::cout << "[+]Process name is: " << ProcessName << "\n[+]Process ID: " << ProcessSnapshotStructure.th32ProcessID << std::endl;
			//std::cout << "PID: " << ProcessSnapshotStructure.th32ProcessID << std::endl;
			return ProcessSnapshotStructure.th32ProcessID;
		}
	}
	CloseHandle(Snapshot);

	//std::cerr << "[!]Unable to find Process ID" << std::endl;
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
	//DWORD d, ds;
	DWORD* Address = (DWORD*)((*(DWORD*)(BaseAddress + Offset1)) + Offset2);

	if (PrintMessage)
	{
		char szTest[10];
		sprintf_s(szTest, "The final address is : %X", (unsigned int)Address);
		MessageBoxA(NULL, szTest, NULL, NULL);
	}

	//VirtualProtect((LPVOID)adress, sizeof(value), PAGE_EXECUTE_READWRITE, &d);    
	*(float*)Address = Value;
	//VirtualProtect((LPVOID)adress ,sizeof(value),d,&ds);
}

std::string GetEXEPath(bool IncludeExeInPath)
{
	char result[MAX_PATH];
	std::string PathString = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
	//DWORD FirstError = GetLastError();

	//WCHAR PathWide[4096];// = { 0 };
	//DWORD Return = GetModuleFileNameW(NULL, PathWide, 4096);
	//std::cout << "EXE Path Wide: " << PathWide << ", PathString: " << PathString << ", PathString.length: " << PathString.length() << std::endl;
	//std::cout << "Return = " << Return << ", First Error = " << FirstError << std::endl;

	if (IncludeExeInPath)
	{
		return PathString;
	}
	else
	{
		unsigned int ExeNameStart = PathString.length();
		for (unsigned int i = PathString.length(); i > 0; i--)
		{
			//std::cout << "PathString[" << i << "] = " << PathString[i] << std::endl;
			if (PathString.compare(i, 1, "\\") == 0 || PathString.compare(i, 1, "/") == 0)
			{
				//std::cout << "\\ or / found at " << i << ", PathString[i] = " << PathString[i] << std::endl;
				ExeNameStart = i;
				break;
			}
		}
		//std::cout << "EXENameStart = " << ExeNameStart << std::endl;
		PathString = PathString.substr(0, ExeNameStart + 1);
		//std::cout << "Final EXE Path: " << PathString << std::endl;
		return PathString;
	}
}

void PlaceNOP(BYTE* Address, DWORD Length)
{
	DWORD OriginalProtectionPermissions;
	DWORD Backup;
	//DWORD RelativeAddress;
	//std::cout << "1" << std::endl;
	VirtualProtect(Address, Length, PAGE_EXECUTE_READWRITE, &OriginalProtectionPermissions);
	//std::cout << "2" << std::endl;
	for (DWORD i = 0x0; i < Length; i++)
	{
		*(Address + i) = 0x90; //NOP, 144 as int, using int when storing opcodes
	}
	//*(Address) = 0x90;
	//memset(Address, 0x90, 1);
	//std::cout << "3" << std::endl;
	VirtualProtect(Address, Length, OriginalProtectionPermissions, &Backup); //Todo: Try using NULL or nullptr instead of Backup, since it's not needed.
	//std::cout << "4" << std::endl;
}

//Get all module related info, this will include the base DLL. 
//and the size of the module
MODULEINFO GetModuleInfo(char *szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

DWORD FindPattern(char *module, char *pattern, char *mask)
{
	//Get all module related information
	MODULEINFO mInfo = GetModuleInfo(module);

	//Assign our base and module size
	//Having the values right is ESSENTIAL, this makes sure
	//that we don't scan unwanted memory and leading our game to crash
	DWORD base = (DWORD)mInfo.lpBaseOfDll;
	DWORD size = (DWORD)mInfo.SizeOfImage;

	//Get length for our mask, this will allow us to loop through our array
	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			//if we have a ? in our mask then we have true by default, 
			//or if the bytes match then we keep searching until finding it or not
			found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
		}

		//found = true, our entire pattern was found
		//return the memory addy so we can write to it
		if (found)
		{
			return base + i;
		}
	}
	std::cout << "Error! FindPattern() returning NULL" << std::endl;
	//ConsoleLog("FindPattern() returning NULL", LogError, false, true);
	return NULL;
}

//Source of the next three functions: https://stackoverflow.com/a/21767578
struct handle_data
{
	unsigned long process_id;
	HWND window_handle;
};

 HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.window_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.window_handle;
}

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle))
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}

BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}