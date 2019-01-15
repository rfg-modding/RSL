#include "PCH.hpp"
#include "Globals.hpp"

float ProgramVersion = 1.0;

DWORD GetProcessID(std::string ProcessName);
bool InjectDLL(int PID, std::string DLLPath, double Dummy1, double Dummy2, bool Dummy3); 
bool LoadDataFromConfig();
std::string GetEXEPath(bool IncludeExeInPath);
void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel = false, bool PrintTypeLabel = true);
void SetConsoleAttributes(WORD Attributes);
void ResetConsoleAttributes();
void TestConsoleOutput();

int main()
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	LoadDataFromConfig();

	ConsoleLog("RFGR script loader injector started\n", LOGMESSAGE, true, true);

	std::string ProgramPath = fs::current_path().string();
	SetConsoleAttributes(ConsoleMessageTextAttributes);
	ResetConsoleAttributes();

	while (true)
	{
		DWORD PID = GetProcessID("rfg.exe");
		if (PID != 0)
		{
			BringWindowToTop(GetConsoleWindow());
			SetConsoleAttributes(ConsoleMessageTextAttributes);
			ResetConsoleAttributes();

			float Dummy1 = ProgramVersion + 32.3f + (rand() % (int)(ProgramVersion + 372.3f));
			double Dummy2 = (8000.0 / ((double)ProgramVersion)) + 8.2 * ProgramVersion + (rand() % (int)(2 + pow(2, ProgramVersion)));
			bool Dummy3 = (bool)ProgramVersion & (bool)(rand() % 222);
			if (!InjectDLL(PID, ProgramPath + "/RFGR Script Loader.dll", Dummy1, Dummy2, Dummy3)) //Todo: Add msg box forcing people to agree that I take no responsibility for any bugs / vac bans
			{
				ConsoleLog("Failure to inject dll. Closing injector in 5 seconds.\n", LOGERROR, false, true);
			}
			else
			{
				ConsoleLog("DLL injected succesfully. Closing injector in 5 seconds.\n", LOGSUCCESS, false, true);
			}
			break;
		}
		else
		{
			if (AutoStartRFG)
			{
				ConsoleLog("Auto starting RFGR for injection...\n", LOGMESSAGE, false, true);
				system("start steam://rungameid/667720"); //Todo: Consider using ShellExecuteA() instead.
				ConsoleLog("Injecting...\n", LOGMESSAGE, false, true);
				Sleep(50); //Todo: Consider adding option for this time length.
			}
		}
		
		Sleep(800UL + (DWORD)rand() % 410UL);
		ConsoleLog("Searching for Red Faction: Guerilla Re-mars-tered", LOGMESSAGE, false, true);
		Sleep(400);
		ConsoleLog(".", LOGMESSAGE, false, false);
		Sleep(400);
		ConsoleLog(".", LOGMESSAGE, false, false);
		Sleep(400);
		ConsoleLog(".\n", LOGMESSAGE, false, false);
	}
#if PublicMode
	Sleep(3000 + rand() % 400);
#else
	Sleep(3000 + rand() % 422);
#endif
	
	FreeConsole();
	return 0;
}

DWORD GetProcessID(std::string ProcessName)
{
	PROCESSENTRY32 ProcessSnapshotStructure = { 0 };
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	ProcessSnapshotStructure.dwSize = sizeof(PROCESSENTRY32);

	if (Snapshot == INVALID_HANDLE_VALUE) 
	{
		return 0;
	}
	if (Process32First(Snapshot, &ProcessSnapshotStructure) == FALSE)
	{
		return 0;
	}

	while (Process32Next(Snapshot, &ProcessSnapshotStructure))
	{
		if (!strcmp(ProcessSnapshotStructure.szExeFile, ProcessName.c_str()))
		{
			CloseHandle(Snapshot);
			return ProcessSnapshotStructure.th32ProcessID;
		}
	}
	CloseHandle(Snapshot);

	return 0;
}

bool InjectDLL(int PID, std::string DLLPath, double Dummy1, double Dummy2, bool Dummy3)
{
	long DLLSize = DLLPath.length() + 1;
	HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	if (ProcessHandle == NULL)
	{
		ConsoleLog("Failed to open target process!\n", LOGERROR, false, true);
		return false;
	}
	ConsoleLog("Target process opened.\n", LOGMESSAGE, false, true);

	LPVOID MyAlloc = VirtualAllocEx(ProcessHandle, NULL, DLLSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (MyAlloc == NULL)
	{
		ConsoleLog("Failed to allocate memory in target process.\n", LOGERROR, false, true);
		return false;
	}
	ConsoleLog("Allocating memory in target process.\n", LOGMESSAGE, false, true);

	int IsWriteOK = WriteProcessMemory(ProcessHandle, MyAlloc, DLLPath.c_str(), DLLSize, 0);
	if (IsWriteOK == 0)
	{
		ConsoleLog("Failed to write in target process memory.\n", LOGERROR, false, true);
		return false;
	}
	ConsoleLog("Creating remote thread in target process.\n", LOGMESSAGE, false, true);

	DWORD dWord;
	LPTHREAD_START_ROUTINE addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibraryA("kernel32"), "LoadLibraryA");
	HANDLE ThreadReturn = CreateRemoteThread(ProcessHandle, NULL, 0, addrLoadLibrary, MyAlloc, 0, &dWord);
	if (ThreadReturn == NULL)
	{
		ConsoleLog("Failed to create remote thread.\n", LOGERROR, false, true);
		return false;
	}

	if ((ProcessHandle != NULL) && (MyAlloc != NULL) && (IsWriteOK != ERROR_INVALID_HANDLE) && (ThreadReturn != NULL))
	{
		return true;
	}

	return false;
}

bool LoadDataFromConfig()
{
	std::string ExePath = GetEXEPath(false);
	fs::remove(ExePath + "Logs/Injector Load Log.txt");
	std::ofstream LogFile(ExePath + "Logs/Injector Load Log.txt");

	if (fs::exists(ExePath + "Settings/InjectorSettings.txt"))
	{
		std::ifstream Config(ExePath + "Settings/InjectorSettings.txt");

		try
		{
			LogFile << "Parsing InjectorSettings.txt" << std::endl;
			Config >> InjectorConfig;
			Config.close();
		}
		catch (nlohmann::json::parse_error& Exception)
		{
			LogFile << "Exception while parsing InjectorSettings.txt!" << std::endl;
			LogFile << Exception.what() << std::endl;
			std::string ExceptionMessage("Exception when parsing InjectorSettings.txt!\n");
			ExceptionMessage += "Message: ";
			ExceptionMessage += Exception.what();

			MessageBoxA(find_main_window(GetProcessID("rfg.exe")), ExceptionMessage.c_str(), "Json parsing exception", MB_OK);
			LogFile << "Failed parse Settings.txt, exiting." << std::endl;
			return false;
		}
		LogFile << "No parse exceptions detected." << std::endl;
	}
	else
	{
		//CreateDirectoryIfNull(ExePath + "/RFGR Camera Extender");
		//std::cout << "InjectorSettings.txt not found. Creating from default values." << std::endl;
		ConsoleLog("InjectorSettings.txt not found. Creating from default values.\n", LOGWARNING);

		InjectorConfig["ForceInjectorConsoleToTop"] = false;
		InjectorConfig["AutoStartRFG"] = true;

		std::ofstream ConfigOutput(ExePath + "Settings/InjectorSettings.txt");
		ConfigOutput << std::setw(4) << InjectorConfig << std::endl;
		ConfigOutput.close();
	}

	ForceInjectorConsoleToTop = InjectorConfig["ForceInjectorConsoleToTop"].get<bool>();
	AutoStartRFG = InjectorConfig["AutoStartRFG"].get<bool>();

	return true;
}

std::string GetEXEPath(bool IncludeExeInPath)
{
	char result[MAX_PATH];
	std::string PathString = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));

	if (IncludeExeInPath)
	{
		return PathString;
	}
	else
	{
		unsigned int ExeNameStart = PathString.length();
		for (unsigned int i = PathString.length(); i > 0; i--)
		{
			if (PathString.compare(i, 1, "\\") == 0 || PathString.compare(i, 1, "/") == 0)
			{
				ExeNameStart = i;
				break;
			}
		}
		PathString = PathString.substr(0, ExeNameStart + 1);
		return PathString;
	}
}

void ConsoleLog(const char* Message, LogType Type, bool PrintTimeLabel, bool PrintTypeLabel)
{
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
	}
	else
	{
		//Invalid log type
	}
	SetConsoleTextAttribute(ConsoleHandle, ConsoleDefaultTextAttributes);
}

void SetConsoleAttributes(WORD Attributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

void ResetConsoleAttributes()
{
	SetConsoleTextAttribute(ConsoleHandle, ConsoleDefaultTextAttributes);
}

void TestConsoleOutput()
{
	ConsoleLog("Message Test\n", LOGMESSAGE, false, true);
	ConsoleLog("Warning Test\n", LOGWARNING, false, true);
	ConsoleLog("Error Test\n", LOGERROR, false, true);
	ConsoleLog("Success Test\n", LOGSUCCESS, false, true);
}