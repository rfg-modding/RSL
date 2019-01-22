#include "Globals.hpp"
//#include "PCH.hpp"

json InjectorConfig;
bool ForceInjectorConsoleToTop = true;
bool AutoStartRFG = true;

PCONSOLE_SCREEN_BUFFER_INFO InitialConsoleScreenInfo = { 0 };
HANDLE ConsoleHandle = { 0 };

const WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
const WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD ConsoleFatalErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
const WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

std::string GetEXEPath(bool IncludeExeInPath)
{
	char result[MAX_PATH];
	std::string PathString = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));

	if (IncludeExeInPath)
	{
		return PathString;
	}
	else
	{
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
}

void SetConsoleAttributes(WORD Attributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

void ResetConsoleAttributes()
{
	SetConsoleTextAttribute(ConsoleHandle, ConsoleDefaultTextAttributes);
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
			return ProcessSnapshotStructure.th32ProcessID;
		}
	}
	CloseHandle(Snapshot);

	return 0;
}

//Source of the next three functions: https://stackoverflow.com/a/21767578
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