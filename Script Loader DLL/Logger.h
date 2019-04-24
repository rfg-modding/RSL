#pragma once
//#include "Globals.h"
#include "Utilities.h"
#define EnableLogging true

/*Uses bitflags to allow for multiple log types. For example,
LogSuccess | LogLua would be a lua success message, while
LogError | LogLua would be a lua error message. The Logger class makes use
of these flags to sort which log files the messages are sent to, that way
logs for lua, json, and general messages can be separate. Also allows for
easy sorting in the overlay console and logging windows.*/
enum LogType
{
	LogNone = 0, //0
	LogInfo = 1 << 0, //1
	LogWarning = 1 << 1,  //2
	LogError = 1 << 2, //4
	LogFatalError = 1 << 3, //8
	LogLua = 1 << 4, //16
	LogJson = 1 << 5, //32
	LogAll = 63
};

class LogFile
{
public:
	LogFile() { }
	LogFile(std::string Path, int Flags, std::ios_base::openmode Mode = std::ios_base::out) : LogFlags(Flags), OpenMode(Mode), FilePath(Path) {}

	std::ofstream File;
	int LogFlags = LogAll;
	std::ios_base::openmode OpenMode = std::ios_base::out;
	std::string FilePath;
};

class LogEntry
{
public:
	LogEntry(std::string& _FlagString, std::string& _Message, int& _Flags) : FlagString(_FlagString), Message(_Message), Flags(_Flags) { }
	std::string FlagString;
	std::string Message;
	int Flags;
};

/*General logging class which automatically sorts messages and sends them to
the right log files and the console depending on their log type.*/
class Logger
{
public:
	static void Init(int _ConsoleLogLevel, std::string _DefaultLogPath, unsigned int _MaximumLogCount);

	static void OpenLogFile(std::string FileName, int LogFlags, std::ios_base::openmode Mode = std::ios_base::out, std::string CustomFilePath = "DEFAULT");
	static void CloseLogFile(const std::string& FileName);
	static void CloseAllLogFiles();
	
	static void Log(std::string Message, int LogFlags = LogInfo, bool LogTime = false, bool NewLine = true);

	static void LogFlagWithColor(int LogFlags);
	static std::string GetFlagString(int LogFlags);
	static void LogToFile(const std::string& FileName, const std::string& Message, int LogFlags, bool LogTime = false, bool BypassFlagCheck = false);

	static std::string GetTimeString(bool MilitaryTime);

	static std::map <std::string, LogFile> LogFileMap;
	static std::vector <LogEntry> LogData;

	static int ConsoleLogFlags;
	static std::string DefaultLogPath;
	static unsigned int MaximumLogCount;

private:
	Logger() { }
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
		Logger::Log("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::invalid_iterator& Exception)
	{
		Logger::Log("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::type_error& Exception)
	{
		Logger::Log("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::out_of_range& Exception)
	{
		Logger::Log("Out of range exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (nlohmann::json::basic_json::other_error& Exception)
	{
		Logger::Log("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json other error exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (std::exception& Exception)
	{
		Logger::Log("General exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);
		Logger::Log(std::string(Exception.what()), LogFatalError);

		std::string ExceptionMessage("General exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json general exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
	catch (...)
	{
		Logger::Log("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"!", LogFatalError);

		std::string ExceptionMessage("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json default exception caught", MB_OK);
		Logger::Log("Failed to " + Action + " \"" + FileName + "\", exiting.", LogFatalError);
		return false;
	}
}