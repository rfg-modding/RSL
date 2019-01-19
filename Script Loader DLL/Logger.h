#pragma once
#include "Globals.h"
#define EnableLogging true

enum LogType
{
	LOGSUCCESS,
	LOGMESSAGE,
	LOGWARNING,
	LOGERROR,
	LOGFATALERROR
};

class LogFile
{
public:
	LogFile() { }
	LogFile(std::string Path, LogType Level, std::ios_base::openmode Mode = std::ios_base::out) : LogLevel(Level), OpenMode(Mode), FilePath(Path) {}
	/*~LogFile() 
	{
		File.close();
	}*/

	std::ofstream File;
	LogType LogLevel;
	std::ios_base::openmode OpenMode;
	std::string FilePath;
};

class LogEntry
{
public:
	LogEntry(std::string& _Message, LogType& _LogLevel) : Message(_Message), LogLevel(_LogLevel) { }
	std::string Message;
	LogType LogLevel;
};

class Logger
{
public:
	static void Init(LogType _ConsoleLogLevel, std::string _DefaultLogPath);

	static void OpenLogFile(std::string FileName, LogType LogLevel, std::ios_base::openmode Mode = std::ios_base::out, std::string CustomFilePath = "DEFAULT");
	static void CloseLogFile(std::string FileName);
	static void CloseAllLogFiles();
	
	static void Log(std::string Message, LogType LogLevel, bool LogTime = false);
	static void LogTypeMessageToFile(std::string FileName, LogType LogLevel);
	static void LogTimeMessageToFile(std::string FileName);
	static void LogToFile(std::string FileName, std::string Message, LogType LogLevel, bool LogTime = false);
	static void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true, bool NewLine = false);
	static std::string GetTimeString(bool MilitaryTime);

	static std::map <std::string, LogFile> LogFileMap;
	static std::vector <LogEntry> LogData;

	static LogType ConsoleLogLevel;
	static std::string DefaultLogPath;

private:
	Logger() { }
};
