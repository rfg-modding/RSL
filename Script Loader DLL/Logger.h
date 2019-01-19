#pragma once
#include "Globals.h"
#define EnableLogging true

enum LogType
{
	LOGMESSAGE,
	LOGWARNING,
	LOGERROR,
	LOGFATALERROR,
	LOGSUCCESS
};

class Logger
{
public:
	static void Open(std::string FileName_);
	static void Log(std::string LogEntry);
	static void Close();

	static void SaveToFile();
	static void SaveToFile(std::string FileName_);

	static void SetConsoleAttributes(WORD Attributes);
	static void ResetConsoleAttributes();
	static void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true, bool NewLine = false);

	static std::string GetTimeString(bool MilitaryTime);

	static HANDLE ConsoleHandle;

	static std::vector <std::string> LogData;
	static std::string FileName;
	static std::ofstream LogFile;
	static int ErrorCount;

	static const WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	static const WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	static const WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
	static const WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
	static const WORD ConsoleFatalErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
	static const WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	static const WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

private:
	Logger() { }
};
