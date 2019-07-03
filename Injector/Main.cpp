//#include "PCH.hpp"
#include "Logger.hpp"
//#include "Globals.hpp"

float ProgramVersion = 0.20f;

bool InjectDLL(int PID, std::string DLLPath, double Dummy1, double Dummy2, bool Dummy3); 
bool LoadDataFromConfig();
void TestConsoleOutput();

int main()
{
	Logger::Init(LOGSUCCESS, GetEXEPath(false) + "RSL/Logs/");
	Logger::OpenLogFile("Injector Log.txt", LOGSUCCESS, std::ios_base::trunc);
	Logger::Log("RSL injector started", LOGMESSAGE, true);
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!LoadDataFromConfig())
	{
		Logger::Log("Failed to load settings. \"Check Injector Log.txt\". Closing in 3 seconds.", LOGMESSAGE, true);
		Sleep(3175);
		return -1;
	}
	
	std::string ProgramPath = fs::current_path().string();
	SetConsoleAttributes(ConsoleMessageTextAttributes);
	ResetConsoleAttributes();

	//Testing code to see different windows console output colors.
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//for (int k = 1; k < 255; k++)
	//{
	//	SetConsoleTextAttribute(hConsole, k);
	//	std::cout << k << " Output test" << std::endl;
	//}

	while (true)
	{
		DWORD PID = GetProcessID("rfg.exe");
		if (PID != 0)
		{
			BringWindowToTop(GetConsoleWindow());
			SetConsoleAttributes(ConsoleMessageTextAttributes);
			ResetConsoleAttributes();

			/*
			While the injector is completely safe, some dummy variables were added to help trick virus scanners. Some of
			them think this program is a common virus since we must use the same common DLL injection code. I've also read
			that the use of system() as seen below can cause them to flag programs, so that should be replaced at some point too.
			The injector will likely be fazed out for normal use in favor of a proxy dll. It will likely not be picked up by antivirus
			software and should be less finicky for users and automatically load when the game runs.
			*/
			float Dummy1 = ProgramVersion + 77.912f + (rand() % (int)(ProgramVersion + 641.9f));
			double Dummy2 = (3730.0 / ((double)ProgramVersion)) + 2.93 * ProgramVersion + (rand() % (int)(2 + pow(2, ProgramVersion)));
			bool Dummy3 = (bool)ProgramVersion & (bool)(rand() % 222);
			if (!InjectDLL(PID, ProgramPath + "/RSL.dll", Dummy1, Dummy2, Dummy3))
			{
				Logger::Log("Failure to inject dll. Closing injector in 5 seconds.", LOGERROR);
			}
			else
			{
				Logger::Log("DLL injected succesfully. Closing injector in 5 seconds.", LOGSUCCESS);
			}
			break;
		}
		else
		{
			if (AutoStartRFG)
			{
				Logger::Log("Auto starting RFGR for injection...", LOGMESSAGE);
				system("start steam://rungameid/667720"); //Todo: Consider using ShellExecuteA() instead.
				Logger::Log("Injecting...", LOGMESSAGE);
				Sleep(50); 
			}
		}
		
		Sleep(1600UL + (DWORD)rand() % 410UL);
		Logger::Log("Searching for Red Faction: Guerilla Re-mars-tered", LOGMESSAGE);
		Sleep(423);
		Logger::Log(".", LOGMESSAGE, false, false);
		Sleep(423);
		Logger::Log(".", LOGMESSAGE, false, false);
		Sleep(423);
		Logger::Log(".", LOGMESSAGE, false, false);
	}
#if PublicMode
	Sleep(3000 + rand() % 434);
#else
	Sleep(3000 + rand() % 419);
#endif
	
	Logger::CloseAllLogFiles();
	FreeConsole();
	return 0;
}

bool InjectDLL(int PID, std::string DLLPath, double Dummy1, double Dummy2, bool Dummy3)
{
	long DLLSize = DLLPath.length() + 1;
	HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	if (ProcessHandle == NULL)
	{
		Logger::Log("Failed to open target process!", LOGERROR);
		return false;
	}
	Logger::Log("Target process opened.", LOGMESSAGE);

	LPVOID MyAlloc = VirtualAllocEx(ProcessHandle, NULL, DLLSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (MyAlloc == NULL)
	{
		Logger::Log("Failed to allocate memory in target process.", LOGERROR);
		return false;
	}
	Logger::Log("Allocating memory in target process.", LOGMESSAGE);

	int IsWriteOK = WriteProcessMemory(ProcessHandle, MyAlloc, DLLPath.c_str(), DLLSize, 0);
	if (IsWriteOK == 0)
	{
		Logger::Log("Failed to write in target process memory.", LOGERROR);
		return false;
	}
	Logger::Log("Creating remote thread in target process.", LOGMESSAGE);

	DWORD dWord;
	LPTHREAD_START_ROUTINE addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibraryA("kernel32"), "LoadLibraryA");
	HANDLE ThreadReturn = CreateRemoteThread(ProcessHandle, NULL, 0, addrLoadLibrary, MyAlloc, 0, &dWord);
	if (ThreadReturn == NULL)
	{
		Logger::Log("Failed to create remote thread.", LOGERROR);
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
	Logger::Log("Started loading \"Injector Settings.json\".", LOGSUCCESS);
	std::string ExePath = GetEXEPath(false);

	if (fs::exists(ExePath + "Settings/Injector Settings.json"))
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("Parsing \"Injector Settings.json\"", LOGMESSAGE);
			std::ifstream Config(ExePath + "Settings/Injector Settings.json");
			Config >> InjectorConfig;
			Config.close();
			return true;
		}, "Injector Settings.json", "parse", "parsing"))
		{
			return false;
		}
		Logger::Log("No parse exceptions detected.", LOGSUCCESS);
	}
	else
	{
		if (!JsonExceptionHandler([&]
		{
			CreateDirectoryIfNull(ExePath + "/Settings/");
			Logger::Log("\"Injector Settings.json\" not found. Creating from default values.", LOGWARNING);

			InjectorConfig["ForceInjectorConsoleToTop"] = false;
			InjectorConfig["AutoStartRFG"] = true;

			std::ofstream ConfigOutput(ExePath + "Settings/Injector Settings.json");
			ConfigOutput << std::setw(4) << InjectorConfig << std::endl;
			ConfigOutput.close();
			return true;
		}, "Injector Settings.json", "write", "writing"))
		{
			return false;
		}
		Logger::Log("No write exceptions detected.", LOGSUCCESS);
	}

	if (!JsonExceptionHandler([&]
	{
		ForceInjectorConsoleToTop = InjectorConfig["ForceInjectorConsoleToTop"].get<bool>();
		AutoStartRFG = InjectorConfig["AutoStartRFG"].get<bool>();
		return true;
	}, "Injector Settings.json", "read", "reading"))
	{
		return false;
	}
	Logger::Log("No read exceptions detected.", LOGSUCCESS);

	Logger::Log("Done loading \"Injector Settings.json\".", LOGSUCCESS);
	return true;
}

void TestConsoleOutput()
{
	Logger::Log("Message Test\n", LOGMESSAGE, false);
	Logger::Log("Warning Test\n", LOGWARNING, false);
	Logger::Log("Error Test\n", LOGERROR, false);
	Logger::Log("Success Test\n", LOGSUCCESS, false);
}