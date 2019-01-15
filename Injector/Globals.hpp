#pragma once
#define PublicMode false
#define ColorLogMessages false
#include "PCH.hpp"

/*RFGR Extended Camera Injector*/

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

static json InjectorConfig;
static bool ForceInjectorConsoleToTop = true;
static bool AutoStartRFG = true;

static PCONSOLE_SCREEN_BUFFER_INFO InitialConsoleScreenInfo = { 0 };
static HANDLE ConsoleHandle = { 0 };

enum LogType
{
	LOGMESSAGE,
	LOGWARNING,
	LOGERROR,
	LOGSUCCESS
};

static WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
static WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
static WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
static WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
static WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
static WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

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

	if (Minutes.size() == 1) //Changes time values such as 1:6 to 1:06
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