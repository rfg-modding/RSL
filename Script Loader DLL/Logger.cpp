#include "Logger.h"

// Instantiate static variables
HANDLE ConsoleHandle;
std::vector <std::string> Logger::LogData;
std::string Logger::FileName;
std::ofstream Logger::LogFile;
int Logger::ErrorCount;

WORD ConsoleMessageLabelTextAttributes;
WORD ConsoleMessageTextAttributes;
WORD ConsoleWarningTextAttributes;
WORD ConsoleErrorTextAttributes;
WORD ConsoleFatalErrorTextAttributes;
WORD ConsoleSuccessTextAttributes;
WORD ConsoleDefaultTextAttributes;

void Logger::Open(std::string FileName_)
{
#if EnableLogging
	FileName = FileName_;
	LogFile.open(FileName, std::ios::app | std::ofstream::out); //Second bitmask flag is needed or else the file is not created if it is missing.

	if (!LogFile)
	{
		std::cerr << "Unable to open file: '" << FileName << "'." << std::endl; //Todo: Throw an error / exception here.
	}

	LogFile << "******  START OF LOG  ******" << std::endl;
	LogFile << "Start Time: " << GetTimeString(0) << "\n" << std::endl;
#endif
}

void Logger::Log(std::string LogEntry)
{
#if EnableLogging
	LogFile << "[" << GetTimeString(0) << "]: " << LogEntry << std::endl;
	ErrorCount++;
#endif
}

void Logger::Close()
{
#if EnableLogging
	LogFile << "\n" << ErrorCount << " errors logged during this session." << std::endl;
	LogFile << "End Time: " << GetTimeString(0) << std::endl;
	LogFile << "******  END OF LOG  ******\n\n\n" << std::endl;

	LogFile.close();//Todo: Check if log file still exists. If not, save the stored log data.
					//Todo: Figure out if the vector is using too much RAM
#endif
}

void Logger::SaveToFile()
{
#if EnableLogging
	std::ofstream LogFile;
	LogFile.open(FileName, std::ios::app);

	if (!LogFile)
	{
		std::cerr << "Unable to open file: '" << FileName << "'." << std::endl; //Todo: Throw an error / exception here.
	}

	LogFile << "******  START OF LOG  ******\n" << std::endl;

	for (int i = 0; i < LogData.size(); i++)
	{
		LogFile << "[" << GetTimeString(0) << "]: " << LogData[i] << std::endl;
	}

	LogFile << "******  END OF LOG  ******\n" << std::endl;

	LogFile.close();
#endif
}

void Logger::SaveToFile(std::string FileName_)
{
#if EnableLogging
	FileName = FileName_;
#endif
}

void Logger::SetConsoleAttributes(WORD Attributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

void Logger::ResetConsoleAttributes()
{
	SetConsoleAttributes(ConsoleDefaultTextAttributes);
}

void Logger::ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true, bool NewLine = false)
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