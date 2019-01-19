#include "Logger.h"
#include "Globals.h"
#include <map>

// Instantiate static variables
std::map <std::string, LogFile> Logger::LogFileMap;
std::vector <LogEntry> Logger::LogData;
LogType Logger::ConsoleLogLevel = LOGMESSAGE;
std::string Logger::DefaultLogPath;

void Logger::Init(LogType _ConsoleLogLevel, std::string _DefaultLogPath)
{
	ConsoleLogLevel = _ConsoleLogLevel;
	DefaultLogPath = _DefaultLogPath;
}

void Logger::OpenLogFile(std::string FileName, LogType LogLevel, std::ios_base::openmode Mode, std::string CustomFilePath)
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
			Log(std::string(FileName + " already exists. New log file not created."), LOGERROR);
			return;
		}
	}
	std::cout << "Opening log file at: " << Path + FileName << std::endl;
	//LogFileMap[FileName] = LogFile(Path, LogLevel, Mode);
	LogFileMap.insert_or_assign(FileName, LogFile(Path + FileName, LogLevel, Mode));
	LogFileMap[FileName].File.open(Path + FileName, Mode);
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

void Logger::Log(std::string Message, LogType LogLevel, bool LogTime)
{
	LogData.push_back(LogEntry(Message, LogLevel));
	if (LogLevel >= ConsoleLogLevel)
	{
		ConsoleLog(Message.c_str(), LogLevel, LogTime, true, true);
	}
	for (auto i = LogFileMap.begin(); i != LogFileMap.end(); i++)
	{
		if (i->second.LogLevel >= LogLevel)
		{
			if (LogTime)
			{
				LogTimeMessageToFile(i->first);
			}
			LogTypeMessageToFile(i->first, LogLevel);
			i->second.File << Message << std::endl;
		}
	}
}

void Logger::LogTypeMessageToFile(std::string FileName, LogType LogLevel)
{
	if (LogLevel == LogType::LOGMESSAGE)
	{
		LogFileMap[FileName].File << "[+] " << std::endl;
	}
	else if (LogLevel == LogType::LOGWARNING)
	{
		LogFileMap[FileName].File << "[Warning] " << std::endl;
	}
	else if (LogLevel == LogType::LOGERROR)
	{
		LogFileMap[FileName].File << "[Error] " << std::endl;
	}
	else if (LogLevel == LogType::LOGFATALERROR)
	{
		LogFileMap[FileName].File << "[Fatal Error] " << std::endl;
	}
	else if (LogLevel == LogType::LOGSUCCESS)
	{
		LogFileMap[FileName].File << "[Success] " << std::endl;
	}
}

void Logger::LogTimeMessageToFile(std::string FileName)
{
	LogFileMap[FileName].File << "[" << GetTimeString(false) << "]" << std::endl;
}

void Logger::LogToFile(std::string FileName, std::string Message, LogType LogLevel, bool LogTime)
{
	if (LogFileMap[FileName].LogLevel >= LogLevel)
	{
		if (LogTime)
		{
			LogTimeMessageToFile(FileName);
		}
		LogTypeMessageToFile(FileName, LogLevel);
		LogFileMap[FileName].File << Message << std::endl;
	}
}

void Logger::ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel, bool PrintTypeLabel, bool NewLine)
{
	/*HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO InitialConsoleScreenInfo = NULL;
	GetConsoleScreenBufferInfo(ConsoleHandle, InitialConsoleScreenInfo); //Returns bool if error checking is needed later.*/

	if (Type == LOGMESSAGE)
	{
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
	else if (Type == LOGWARNING)
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
	else if (Type == LOGERROR)
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
	else if (Type == LOGFATALERROR)
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
	else if (Type == LOGSUCCESS)
	{
		if (PrintTypeLabel)
		{
			printf("[");
			SetConsoleAttributes(ConsoleSuccessTextAttributes);
			printf("Success");
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
		SetConsoleTextAttribute(ConsoleHandle, ConsoleSuccessTextAttributes);
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

	return DateTime;
#endif
}