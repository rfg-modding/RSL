#pragma once
#define PublicMode false
#define ColorLogMessages false
#include "PCH.hpp"

/*RFGR Extended Camera Injector*/

#ifdef SCRIPT_LOADER_DLL
#error ./Injector/Globals.hpp was included by one of the Script Loader DLL project files! Find and remove that include. Failing to do so may result in some pesky and hard to find bugs. DO NOT REMOVE THIS ERROR TO MAKE IT COMPILE!
#endif

using json = nlohmann::json;
namespace fs = std::filesystem;

extern json InjectorConfig;
extern bool ForceInjectorConsoleToTop;
extern bool AutoStartRFG;

extern PCONSOLE_SCREEN_BUFFER_INFO InitialConsoleScreenInfo;
extern HANDLE ConsoleHandle;

extern const WORD ConsoleMessageLabelTextAttributes;
extern const WORD ConsoleMessageTextAttributes;
extern const WORD ConsoleWarningTextAttributes;
extern const WORD ConsoleErrorTextAttributes;
extern const WORD ConsoleFatalErrorTextAttributes;
extern const WORD ConsoleSuccessTextAttributes;
extern const WORD ConsoleDefaultTextAttributes;

std::string GetEXEPath(bool IncludeExeInPath);
void SetConsoleAttributes(WORD Attributes);
void ResetConsoleAttributes();
bool DirectoryExists(const std::string& Directory);
void CreateDirectoryIfNull(const std::string& Directory);
DWORD GetProcessID(const std::string& ProcessName);

//Source of the next three functions: https://stackoverflow.com/a/21767578
struct handle_data
{
	unsigned long process_id;
	HWND window_handle;
};
HWND find_main_window(unsigned long process_id);
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
BOOL is_main_window(HWND handle);