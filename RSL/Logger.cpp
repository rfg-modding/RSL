#include "Logger.h"
#include "Globals.h"
#include <map>

// Instantiate static variables
std::map<std::string, LogFile> Logger::LogFiles;
std::deque<LogEntry> Logger::LogCache;
int Logger::ConsoleLogFlags = LogAll;
std::string Logger::DefaultLogPath;
unsigned int Logger::MaximumLogCount;

void Logger::Init(int _ConsoleLogFlags, std::string _DefaultLogPath, unsigned int _MaximumLogCount)
{
	ConsoleLogFlags = _ConsoleLogFlags;
	DefaultLogPath = _DefaultLogPath;
	MaximumLogCount = _MaximumLogCount;

	Globals::CreateDirectoryIfNull(DefaultLogPath);
}

void Logger::OpenLogFile(std::string FileName, int LogFlags, std::ios_base::openmode Mode, std::string CustomFilePath)
{
	try
	{
        std::string path = CustomFilePath == "DEFAULT" ? DefaultLogPath : CustomFilePath;
	    for (auto& i : LogFiles)
		{
			if (i.first == FileName)
			{
                LogError("{} already exists. New log file not created.", FileName);
				return;
			}
		}
		std::ofstream& outStream = LogFiles.insert_or_assign(FileName, LogFile(path + FileName, LogFlags, Mode)).first->second.File;
		outStream.exceptions(std::ios::failbit | std::ios::badbit);
		outStream.open(path + FileName, Mode);
		outStream << GetTimeString(false) << "[Info] " << "Start of " << FileName << "\n";
		outStream << std::flush;
	}
	catch (std::exception& Ex)
	{
		std::string ExceptionInfo = fmt::format("Exception caught while opening {}: \"{}\". File: {}, Function: {}\n",
			FileName, Ex.what(), __FILE__, __FUNCSIG__);

		throw std::exception(ExceptionInfo.c_str());
	}
}

void Logger::CloseLogFile(const const std::string& FileName)
{
	LogFiles[FileName].File.close();
	LogFiles.erase(FileName);
}

void Logger::CloseAllLogFiles()
{
	for (auto& i : LogFiles)
        i.second.File.close();

    LogFiles.erase(LogFiles.begin(), LogFiles.end());
}

void Logger::LogInternal(string Message, int LogFlags, bool LogTime, bool NewLine)
{
	std::string timeString = GetTimeString(false);
	std::string flagString = GetFlagString(LogFlags);
	//Add message to front of log cache
	LogCache.insert(LogCache.begin(), LogEntry(flagString, Message, LogFlags));

	//Write to console
	WriteToConsoleInternal(Message, LogFlags, LogTime, NewLine, timeString);
	//Write to log files
	WriteToLogFilesInternal(Message, LogFlags, LogTime, NewLine, timeString, flagString);

	//Remove entry from end of cache if it's full
	if (LogCache.size() > MaximumLogCount && MaximumLogCount > 0)
        LogCache.pop_back();
}

void Logger::WriteToConsoleInternal(string& Message, int LogFlags, bool LogTime, bool NewLine, string& timeString)
{
	if (!(ConsoleLogFlags & LogFlags))
        return;

    try
    {
        LogFlagWithColor(LogFlags);
        if (LogTime)
            std::cout << timeString;

        std::cout << " ";
        std::cout << Message;
        if (NewLine)
            std::cout << "\n";
    }
    catch (std::exception & Ex)
    {
        std::string ExceptionInfo = fmt::format("Exception caught while logging to external console: \"{}\". File: {}, Function: {}\n",
                                                Ex.what(), __FILE__, __FUNCSIG__);

        LogError("{}\n", ExceptionInfo);
        MessageBoxA(Globals::FindRfgTopWindow(), ExceptionInfo.c_str(), "Failed to log to external console!", MB_OK);
    }
}

void Logger::WriteToLogFilesInternal(string& Message, int LogFlags, bool LogTime, bool NewLine, string& timeString, string& flagString)
{
	for (auto& i : LogFiles)
	{
		if (!(i.second.LogFlags & LogFlags))
			continue;

		try
		{
			i.second.File << flagString;
			if (LogTime)
				i.second.File << timeString;

			i.second.File << " ";
			i.second.File << Message;
			if (NewLine)
				i.second.File << "\n";

			i.second.File << std::flush;
		}
		catch (std::exception & Ex)
		{
			std::string ExceptionInfo = fmt::format("Exception caught while logging to {}: \"{}\". File: {}, Function: {}\n",
				i.second.FilePath, Ex.what(), __FILE__, __FUNCSIG__);

			LogError("{}\n", ExceptionInfo);
			MessageBoxA(Globals::FindRfgTopWindow(), ExceptionInfo.c_str(), "Failed to log to file!", MB_OK);
		}
	}
}

void Logger::LogFlagWithColor(const int LogFlags)
{
	if (LogFlags & LogType::LogInfo)
	{
		std::cout << "[";
		Globals::SetConsoleAttributes(Globals::ConsoleMessageLabelTextAttributes);
		std::cout << "Info";
		Globals::ResetConsoleAttributes();
		std::cout << "]";
	}
	else if (LogFlags & LogType::LogWarning)
	{
		std::cout << "[";
		Globals::SetConsoleAttributes(Globals::ConsoleWarningTextAttributes);
		std::cout << "Warning";
		Globals::ResetConsoleAttributes();
		std::cout << "]";
	}
	else if (LogFlags & LogType::LogError)
	{
		std::cout << "[";
		Globals::SetConsoleAttributes(Globals::ConsoleErrorTextAttributes);
		std::cout << "Error";
		Globals::ResetConsoleAttributes();
		std::cout << "]";
	}
	else if (LogFlags & LogType::LogFatalError)
	{
		std::cout << "[";
		Globals::SetConsoleAttributes(Globals::ConsoleFatalErrorTextAttributes);
		std::cout << "Fatal Error";
		Globals::ResetConsoleAttributes();
		std::cout << "]";
	}
	else
	{
		//Does nothing if it's LogNone or an undefined value.
	}
	SetConsoleTextAttribute(Globals::ConsoleHandle, Globals::ConsoleDefaultTextAttributes);
}

std::string Logger::GetFlagString(const int LogFlags)
{
	if (LogFlags & LogType::LogInfo)
        return "[Info]";
    if (LogFlags & LogType::LogWarning)
        return "[Warning]";
    if (LogFlags & LogType::LogLua)
        return "[Lua]";
    if (LogFlags & LogType::LogJson)
        return "[Json]";
    if (LogFlags & LogType::LogError)
        return "[Error]";
    if (LogFlags & LogType::LogFatalError)
        return "[Fatal Error]";
	else
        return "";
}

void Logger::LogToFile(const std::string& FileName, const std::string& Message, const int LogFlags, const bool LogTime, const bool BypassFlagCheck)
{
	if (!BypassFlagCheck && !(LogFiles[FileName].LogFlags & LogFlags)) //Allows things such as using LogInfo for the first message in an error log.
        return;

	std::ofstream& outStream = LogFiles[FileName].File;
	outStream << GetFlagString(LogFlags);
	if (LogTime)
		outStream << GetTimeString(false);

	outStream << " " << Message << "\n";
}

std::string Logger::GetTimeString(const bool MilitaryTime)
{
	std::time_t t = std::time(0);
	std::tm now{};
	localtime_s(&now, &t);

	std::string DateTime;
	const std::string Year = std::to_string(now.tm_year + 1900);
	const std::string Month = std::to_string(now.tm_mon + 1);
	const std::string Day = std::to_string(now.tm_mday);
	std::string Hour;
	std::string Minutes = std::to_string(now.tm_min);

	if (Minutes.size() == 1) //Changes values such as 1:6 to 1:06
        Minutes.insert(0, 1, '0');

    if (MilitaryTime)
        Hour = std::to_string(now.tm_hour);
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
	return "[" + DateTime + "]";
}