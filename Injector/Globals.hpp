#pragma once
#define PublicMode false
#define ColorLogMessages false
#include "PCH.hpp"

/*RFGR Extended Camera Injector*/

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

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
bool DirectoryExists(std::string Directory);
void CreateDirectoryIfNull(std::string Directory);
DWORD GetProcessID(std::string ProcessName);

//Source of the next three functions: https://stackoverflow.com/a/21767578
struct handle_data
{
	unsigned long process_id;
	HWND window_handle;
};
HWND find_main_window(unsigned long process_id);
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
BOOL is_main_window(HWND handle);