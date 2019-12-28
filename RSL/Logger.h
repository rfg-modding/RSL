#pragma once
#include "Util.h"

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
	static void Init(int _ConsoleLogFlags, std::string _DefaultLogPath, unsigned int _MaximumLogCount);

	static void OpenLogFile(std::string FileName, int LogFlags, std::ios_base::openmode Mode = std::ios_base::out, std::string CustomFilePath = "DEFAULT");
	static void CloseLogFile(const std::string& FileName);
	static void CloseAllLogFiles();
	
	static void LogInternal(string Message, int LogFlags = LogType::LogInfo, bool LogTime = false, bool NewLine = false);
	static void WriteToConsoleInternal(string& Message, int LogFlags, bool LogTime, bool NewLine, string& timeString);
	static void WriteToLogFilesInternal(string& Message, int LogFlags, bool LogTime, bool NewLine, string& timeString, string& flagString);

    template <typename... Args>
    static void Log(std::string fmt, const Args&... args)
    {
        LogInternal(fmt::format(fmt, args...));
    }

    template <typename... Args>
    static void LogNone(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogNone);
    }

    template <typename... Args>
    static void LogInfo(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogInfo);
    }

    template <typename... Args>
    static void LogWarning(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogWarning);
    }

    template <typename... Args>
    static void LogError(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogError);
    }

    template <typename... Args>
    static void LogFatalError(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogFatalError);
    }

    template <typename... Args>
    static void LogLua(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogLua);
    }

    template <typename... Args>
    static void LogJson(std::string fmt, const Args& ... args)
    {
        LogInternal(fmt::format(fmt, args...), LogType::LogJson);
    }

	static void LogFlagWithColor(int LogFlags);
	static std::string GetFlagString(int LogFlags);
	static void LogToFile(const std::string& FileName, const std::string& Message, int LogFlags, bool LogTime = false, bool BypassFlagCheck = false);

	static std::string GetTimeString(bool MilitaryTime);

	static std::map<std::string, LogFile> LogFiles;
	static std::deque<LogEntry> LogCache;

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
        Logger::LogFatalError("Parse exception caught while {0} \"{1}\"! Message: {2}\n", ActionConjugated, FileName, Exception.what());

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json parse exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
	catch (nlohmann::json::basic_json::invalid_iterator& Exception)
	{
        Logger::LogFatalError("Invalid iterator exception caught while {0} \"{1}\"! Message: {2}\n", ActionConjugated, FileName, Exception.what());

		std::string ExceptionMessage("Invalid iterator exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json invalid iterator exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
	catch (nlohmann::json::basic_json::type_error& Exception)
	{
        Logger::LogFatalError("Type error exception caught while {0} \"{1}\"! Message: {2}\n", ActionConjugated, FileName, Exception.what());

		std::string ExceptionMessage("Type error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json type error exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
	catch (nlohmann::json::basic_json::out_of_range& Exception)
	{
        Logger::LogFatalError("Out of range exception caught while {0} \"{1}\"! Message: {2}\n", ActionConjugated, FileName, Exception.what());

		std::string ExceptionMessage("Parse exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json out of range exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
	catch (nlohmann::json::basic_json::other_error& Exception)
	{
        Logger::LogFatalError("Other exception caught while {0} \"{1}\"! Message: {2}\n", ActionConjugated, FileName, Exception.what());

		std::string ExceptionMessage("Other error exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json other error exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
	catch (std::exception& Exception)
	{
        Logger::LogFatalError("General exception caught while {0} \"{1}\"! Message: {2}\n", ActionConjugated, FileName, Exception.what());

		std::string ExceptionMessage("General exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		ExceptionMessage += "Message: ";
		ExceptionMessage += Exception.what();

		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json general exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
	catch (...)
	{
        Logger::LogFatalError("Default exception caught while {0} \"{1}\"!\n", ActionConjugated, FileName);

		std::string ExceptionMessage("Default exception caught while " + ActionConjugated + " \"" + FileName + "\"! See logs. ");
		MessageBoxA(Globals::FindRfgTopWindow(), ExceptionMessage.c_str(), "Json default exception caught", MB_OK);
        Logger::LogFatalError("Failed to {0} \"{1}\", exiting.\n", Action, FileName);
		return false;
	}
}