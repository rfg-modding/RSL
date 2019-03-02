#pragma once
#include "Globals.hpp"
//#include "PCH.hpp"
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
	std::ios_base::openmode OpenMode = std::ios_base::out;
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
	
	static void Log(std::string Message, LogType LogLevel, bool LogTime = false, bool NewLine = true);
	static void LogTypeMessageToFile(std::string FileName, LogType LogLevel);
	static void LogTimeMessageToFile(std::string FileName);
	static void LogToFile(std::string FileName, std::string Message, LogType LogLevel, bool LogTime = false);
	
	static std::string GetTimeString(bool MilitaryTime);

	static std::map <std::string, LogFile> LogFileMap;
	static std::vector <LogEntry> LogData;

	static LogType ConsoleLogLevel;
	static std::string DefaultLogPath;

private:
	Logger() { }
	static void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true, bool NewLine = false);
};

/*This code is a modified version of this SO answer: https://codereview.stackexchange.com/a/71330 ... Very useful.*/
template<typename Callable>
auto JsonExceptionHandler(Callable&& Function, std::string FileName, std::string Action, std::string ActionConjugated) -> decltype(Function())
{
	try
	{
		return Function();
	}
	catch (nlohmann::json::parse_error& Exception)
	{
		Logger::Log("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);
		Logger::Log(std::string(Exception.what()), LOGFATALERROR);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
	catch (nlohmann::json::basic_json::invalid_iterator& Exception)
	{
		Logger::Log("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);
		Logger::Log(std::string(Exception.what()), LOGFATALERROR);

		std::string ExceptionMessage("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
	catch (nlohmann::json::basic_json::type_error& Exception)
	{
		Logger::Log("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);
		Logger::Log(std::string(Exception.what()), LOGFATALERROR);

		std::string ExceptionMessage("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
	catch (nlohmann::json::basic_json::out_of_range& Exception)
	{
		Logger::Log("Out of range exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);
		Logger::Log(std::string(Exception.what()), LOGFATALERROR);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
	catch (nlohmann::json::basic_json::other_error& Exception)
	{
		Logger::Log("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);
		Logger::Log(std::string(Exception.what()), LOGFATALERROR);

		std::string ExceptionMessage("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json other error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
	catch (std::exception& Exception)
	{
		Logger::Log("General exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);
		Logger::Log(std::string(Exception.what()), LOGFATALERROR);

		std::string ExceptionMessage("General exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
	catch (...)
	{
		Logger::Log("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LOGFATALERROR);

		std::string ExceptionMessage("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json default exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LOGFATALERROR);
		return false;
	}
}