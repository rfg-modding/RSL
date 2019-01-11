#pragma once
#define PublicMode true
#define ColorLogMessages false
#define EnableSpectatorMode false 
#include "Includes.hpp"

/*RFGR Script Loader DLL*/

//using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

static const ImVec4 ColorTransparent = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
static const ImVec4 ColorRed = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
static const ImVec4 ColorGreen = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
static const ImVec4 ColorBlue = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
static const ImVec4 ColorBlack = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
static const ImVec4 ColorWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
static const ImVec4 ColorPurple = ImVec4(0.227f, 0.0f, 0.6588f, 1.0f);
static const ImVec4 ColorOrange = ImVec4(1.0f, 0.4157f, 0.0f, 1.0f);
static const ImVec4 ColorYellow = ImVec4(1.0f, 0.8902f, 0.0666f, 1.0f);

static const ImVec4 SecondaryTextColor(0.20f, 0.55f, 0.83f, 1.00f); //Light blue
static const ImVec4 ColorBlue2 = ImVec4(0.10f, 0.40f, 0.75f, 1.0f);

static const float pi = 3.14159265f;

extern bool OpenDebugConsole;
extern nlohmann::json MainConfig;
extern float DefaultFreeCameraSpeed;
extern float DefaultRotationSpeed;
//static bool UseConsole = false;

extern IDXGISwapChain* D3D11SwapchainPtr;
extern ID3D11Device* D3D11Device;
extern ID3D11DeviceContext* D3D11Context;
extern ID3D11RenderTargetView* MainRenderTargetView;
extern HWND hwnd;
extern ImVec4* Colors;

//extern MainOverlay Overlay;
extern bool ShowMainOverlay;

extern float OverlayFontSize;
extern bool show_demo_window;
extern bool ImGuiInitialized;
extern ImGuiIO io;
extern bool OverlayActive;
extern WNDPROC OriginalWndProc;
extern bool FirstPersonModeActive;

extern float GlobalExplosionStrengthMultiplier;
extern bool UseGlobalExplosionStrengthMultiplier;
extern bool UseExplosionRadiusLimits;
extern float MinimumExplosionRadius;
extern float MaximumExplosionRadius;
extern DWORD* GlobalPlayerPtr;

extern bool InfiniteJetpack;

extern sol::state Lua;

extern HANDLE ConsoleHandle;
extern DWORD* InMultiplayer;
extern bool MultiplayerHookTriggered;

enum LogType
{
	LOGMESSAGE,
	LOGWARNING,
	LOGERROR,
	LOGFATALERROR,
	LOGSUCCESS
};

static WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
static WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
static WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
static WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
static WORD ConsoleFatalErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
static WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
static WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

//void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true);
//void SetConsoleAttributes(WORD Attributes);
//void ResetConsoleAttributes();

static void ShowHelpMarker(const char* desc)
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

static bool DirectoryExists(std::string Directory)
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

static void CreateDirectoryIfNull(std::string Directory)
{
	if (!DirectoryExists(Directory))
	{
		fs::create_directory(Directory);
	}
}

static float FloatConvertDegreesToRadians(float AngleInDegrees)
{
	return (pi / 180.0f) * AngleInDegrees;
}

static float sind(float AngleInDegrees)
{
	return sin(FloatConvertDegreesToRadians(AngleInDegrees));
}

static float cosd(float AngleInDegrees)
{
	return cos(FloatConvertDegreesToRadians(AngleInDegrees));
}

static float tand(float AngleInDegrees)
{
	return tan(FloatConvertDegreesToRadians(AngleInDegrees));
}

static HWND FindTopWindow(DWORD pid)
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

static DWORD GetProcessID(std::string ProcessName)
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

static void EnforceFloatRange(float& Value, float& Minimum, float& Maximum)
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

static std::string GetTimeString(bool MilitaryTime)
{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);

	std::string DateTime;
	std::string Year = std::to_string(now.tm_year + 1900);
	std::string Month = std::to_string(now.tm_mon + 1);
	std::string Day = std::to_string(now.tm_mday);
	std::string Hour;
	std::string Minutes = std::to_string(now.tm_min);

	if (Minutes.size() == 1) //Changes things like 1:6 to 1:06
	{
		Minutes.insert(0, 1, '0');
	}

	if (MilitaryTime)
	{
		Hour = std::to_string(now.tm_hour);
	}
	else
	{
		if (now.tm_hour > 11) //PM
		{
			Hour = std::to_string(now.tm_hour - 12);
			DateTime += Hour + ":" + Minutes + " PM, ";
		}
		else //AM
		{
			if (now.tm_hour == 0)
			{
				Hour = "12";
				DateTime += Hour + ":" + Minutes + " AM, ";
			}
			else
			{
				Hour = std::to_string(now.tm_hour);
				DateTime += Hour + ":" + Minutes + " AM, ";
			}
		}
	}

	DateTime += Month + "/" + Day + "/" + Year;

	//std::cout << DateTime << std::endl;

	//std::cout << "Date & Time:" << now.tm_year + 1900 << "/" << now.tm_mon + 1 << "/" << now.tm_mday << " - " << now.tm_hour << ":" << now.tm_min << std::endl;

	return DateTime;
}

static void SetConsoleAttributes(WORD Attributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

static void ResetConsoleAttributes()
{
	SetConsoleAttributes(ConsoleDefaultTextAttributes);
}

static void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true, bool NewLine = false)
{
	/*HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO InitialConsoleScreenInfo = NULL;
	GetConsoleScreenBufferInfo(ConsoleHandle, InitialConsoleScreenInfo); //Returns bool if error checking is needed later.*/

	if (Type == LOGMESSAGE)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleMessageLabelTextAttributes);
			printf("+");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleMessageTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (Type == LOGWARNING)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleWarningTextAttributes);
			printf("Warning");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleWarningTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (Type == LOGERROR)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleErrorTextAttributes);
			printf("Error");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleErrorTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (Type == LOGFATALERROR)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleFatalErrorTextAttributes);
			printf("Fatal Error");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleFatalErrorTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (Type == LOGSUCCESS)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleSuccessTextAttributes);
			printf("Success");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleSuccessTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else
	{
		//Invalid log type
	}
	SetConsoleTextAttribute(ConsoleHandle, ConsoleDefaultTextAttributes);// InitialConsoleScreenInfo->wAttributes);
}

static void ChangeMemoryFloat(DWORD BaseAddress, float Value, DWORD Offset1, DWORD Offset2, bool PrintMessage)
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

static std::string GetEXEPath(bool IncludeExeInPath)
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

//Print our pattern scan results if necessary
static void MsgBoxAddy(DWORD addy)
{
	char szBuffer[1024];
	//sprintf_s(szBuffer, "Addy: %02x", addy);
	MessageBox(NULL, szBuffer, "Title", MB_OK);
}

/*Credits to InSaNe on MPGH for the original function*/
//We make Length at the end optional as most jumps will be 5 or less bytes
static void PlaceJMP(BYTE *Address, DWORD jumpTo, DWORD length = 5)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;

	//give that address read and write permissions and store the old permissions at oldProtection
	VirtualProtect(Address, length, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	// Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
	dwRelAddr = (DWORD)(jumpTo - (DWORD)Address) - 5;

	// Write the JMP opcode @ our jump position...
	*Address = 0xE9;

	// Write the offset to where we're gonna jump
   //The instruction will then become JMP ff002123 for example
	*((DWORD *)(Address + 0x1)) = dwRelAddr;

	// Overwrite the rest of the bytes with NOPs
	//ensuring no instruction is Half overwritten(To prevent any crashes)
	for (DWORD x = 0x5; x < length; x++)
		*(Address + x) = 0x90;

	// Restore the default permissions
	VirtualProtect(Address, length, dwOldProtect, &dwBkup);
}

static void PlaceNOP(BYTE* Address, DWORD Length = 1)
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
static MODULEINFO GetModuleInfo(char *szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

static DWORD FindPattern(char *module, char *pattern, char *mask)
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
	ConsoleLog("FindPattern() returning NULL", LOGERROR, false, true);
	return NULL;
}

//Source of the next three functions: https://stackoverflow.com/a/21767578
HWND find_main_window(unsigned long process_id);
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
BOOL is_main_window(HWND handle);

struct handle_data 
{
	unsigned long process_id;
	HWND window_handle;
};

static HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.window_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.window_handle;
}

static BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle))
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}

static BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}