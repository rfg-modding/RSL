#include "Logger.h"
#include "Globals.h"
#include <map>

// Instantiate static variables
std::map <std::string, LogFile> Logger::LogFileMap;
std::vector <LogEntry> Logger::LogData;
int Logger::ConsoleLogFlags = LogAll;
std::string Logger::DefaultLogPath;

void Logger::Init(int _ConsoleLogFlags, std::string _DefaultLogPath)
{
	ConsoleLogFlags = _ConsoleLogFlags;
	DefaultLogPath = _DefaultLogPath;

	CreateDirectoryIfNull(DefaultLogPath);
}

void Logger::OpenLogFile(std::string FileName, int LogFlags, std::ios_base::openmode Mode, std::string CustomFilePath)
{
	std::string Path;
	if (CustomFilePath == "DEFAULT")
	{
		Path = DefaultLogPath;
	}
	else
	{
		Path = CustomFilePath;
	}
	for (auto i = LogFileMap.begin(); i != LogFileMap.end(); i++)
	{
		if (i->first == FileName)
		{
			Log(std::string(FileName + " already exists. New log file not created."), LogError);
			return;
		}
	}
	LogFileMap.insert_or_assign(FileName, LogFile(Path + FileName, LogFlags, Mode));
	LogFileMap[FileName].File.open(Path + FileName, Mode);
	LogFileMap[FileName].File << GetTimeString(false) << "[Info] " << "Start of " << FileName << std::endl;
}

void Logger::CloseLogFile(std::string FileName)
{
	LogFileMap[FileName].File.close();
	LogFileMap.erase(FileName);
}

void Logger::CloseAllLogFiles()
{
	for (auto i = LogFileMap.begin(); i != LogFileMap.end(); i++)
	{
		i->second.File.close();
	}
	LogFileMap.erase(LogFileMap.begin(), LogFileMap.end());
}

void Logger::Log(std::string Message, int LogFlags, bool LogTime, bool NewLine)
{
	std::string FlagString = GetFlagString(LogFlags);
	LogData.push_back(LogEntry(FlagString, Message, LogFlags));
	if (ConsoleLogFlags & LogFlags)
	{
		if (NewLine)
		{
			ConsoleLog(Message.c_str(), LogFlags, LogTime, true, true);
		}
		else
		{
			ConsoleLog(Message.c_str(), LogFlags, LogTime, true, false);
		}
	}
	for (auto i = LogFileMap.begin(); i != LogFileMap.end(); i++)
	{
		if (i->second.LogFlags & LogFlags)
		{
			if (LogTime)
			{
				LogTimeMessageToFile(i->first);
			}
			i->second.File << FlagString;
			i->second.File << Message;
			if (NewLine)
			{
				i->second.File << std::endl;
			}
		}
	}
}

std::string Logger::GetFlagString(int LogFlags)
{
	if (LogFlags & LogInfo)
	{
		return "[Info] ";
	}
	else if (LogFlags & LogWarning)
	{
		return "[Warning] ";
	}
	else if (LogFlags & LogLua)
	{
		return "[Lua] ";
	}
	else if (LogFlags & LogJson)
	{
		return "[Json] ";
	}
	else if (LogFlags & LogError)
	{
		return "[Error] ";
	}
	else if (LogFlags & LogFatalError)
	{
		return "[Fatal Error] ";
	}
	else
	{
		return "[+]";
	}
}

void Logger::LogTimeMessageToFile(std::string FileName)
{
	LogFileMap[FileName].File << "[" << GetTimeString(false) << "]";
}

void Logger::LogToFile(std::string FileName, std::string Message, int LogFlags, bool LogTime, bool BypassFlagCheck)
{
	if (!BypassFlagCheck) //Allows things such as using LogInfo for the first message in an error log.
	{
		if (!(LogFileMap[FileName].LogFlags & LogFlags))
		{
			return;
		}
	}
	if (LogTime)
	{
		LogTimeMessageToFile(FileName);
	}
	LogFileMap[FileName].File << GetFlagString(LogFlags);
	LogFileMap[FileName].File << Message << std::endl;
}

/*Only used for debug purposed. Plan to deprecate this and use the overlay console instead.*/
void Logger::ConsoleLog(const char* Message, int LogFlags, bool PrintTimeLabel, bool PrintTypeLabel, bool NewLine)
{
	if (LogFlags & LogInfo)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleMessageLabelTextAttributes);
			printf("Info");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleMessageTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (LogFlags & LogWarning)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleWarningTextAttributes);
			printf("Warning");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleWarningTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (LogFlags & LogError)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleErrorTextAttributes);
			printf("Error");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleErrorTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else if (LogFlags & LogFatalError)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleFatalErrorTextAttributes);
			printf("Fatal Error");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleFatalErrorTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	else
	{
		//Invalid log type
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleMessageLabelTextAttributes);
			printf("+");
			ResetConsoleAttributes();
			if (PrintTimeLabel)
			{
				printf("]");
			}
			else
			{
				printf("] ");
			}
		}
		if (PrintTimeLabel)
		{
			printf("[");
			printf(GetTimeString(false).c_str());
			printf("] ");
		}
#if ColorLogMessages
		SetConsoleTextAttribute(ConsoleHandle, ConsoleMessageTextAttributes);
#endif
		printf(Message);
		if (NewLine)
		{
			printf("\n");
		}
	}
	SetConsoleTextAttribute(ConsoleHandle, ConsoleDefaultTextAttributes);// InitialConsoleScreenInfo->wAttributes);
}

std::string Logger::GetTimeString(bool MilitaryTime)
{
#if EnableLogging
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);

	std::string DateTime;
	std::string Year = std::to_string(now.tm_year + 1900);
	std::string Month = std::to_string(now.tm_mon + 1);
	std::string Day = std::to_string(now.tm_mday);
	std::string Hour;
	std::string Minutes = std::to_string(now.tm_min);

	if (Minutes.size() == 1) //Changes things like 1:6 to 1:06
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

	return "[" + DateTime + "]";
#endif
}