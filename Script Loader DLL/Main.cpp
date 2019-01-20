///#include "Globals.h"
///#include "SnippetManager.h"
#include "ProgramManager.h"
///#include "CameraWrapper.h"

/*Fix these in RFGR_Types.h and RFGR_Types_Player.h
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
*/

DWORD WINAPI MainThread(HMODULE hModule)
{
	Logger::Init(LOGSUCCESS, GetEXEPath(false) + "RFGR Script Loader/Logs/");
	Logger::OpenLogFile("Load Log.txt", LOGSUCCESS, std::ios_base::trunc);
	//Logger::OpenLogFile("General Log.txt", LOGMESSAGE, std::ios_base::trunc);
	//Logger::Log("You should only see this in General Log.txt", LOGMESSAGE, false);
	//Logger::Log("You should see this everywhere", LOGFATALERROR, false);

	Logger::Log("Before ProgramManager::ProgramManager()", LOGMESSAGE);
	ProgramManager Program(hModule);
	Logger::Log("Before Program.LoadDataFromConfig()", LOGMESSAGE);
	if (!Program.LoadDataFromConfig())
	{
		FreeLibraryAndExitThread(hModule, 0);
		return 0;
	}
	Logger::Log("Before Program.OpenConsole()", LOGMESSAGE);
	Program.OpenConsole();
	Logger::Log("RFGR Script Loader attached to external console", LOGSUCCESS, true);
	Logger::Log("Before Program.SetMemoryLocations()", LOGMESSAGE);
	Program.SetMemoryLocations();
	Logger::Log("Before Program.Initialize()", LOGMESSAGE);
	Program.Initialize();

	Logger::Log("RFGR script loader successfully activated.", LOGSUCCESS, true);
	Logger::CloseLogFile("Load Log.txt");
	Logger::OpenLogFile("General Log.txt", LOGSUCCESS, std::ios_base::trunc);
	Logger::Log("Start of General Log.txt", LOGSUCCESS, true);
	Logger::OpenLogFile("Error Log.txt", LOGERROR, std::ios_base::trunc);
	Logger::Log("Start of Error Log.txt", LOGERROR, true);

	GameState RFGRState;
	while (!Program.ShouldClose()) //Todo: Change to respond to PostQuitMessage(0) in WndProc;
	{
		RFGRState = GameseqGetState();
		if (RFGRState == 0x13 || RFGRState == 0x14 || RFGRState == 0x15 || RFGRState == 0x16 || RFGRState == 0x3B || RFGRState == 0x3C || RFGRState == 0x3F) //See GameState enum is RFGR_Types_Player.h for values.
		{
			//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			Logger::Log("MP detected. Crashing now!", LOGFATALERROR, true);
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		if (*(bool*)InMultiplayer)
		{
			//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			Logger::Log("MP detected. Crashing now!", LOGFATALERROR, true);
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		if (MultiplayerHookTriggered)
		{
			//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			Logger::Log("MP detected. Crashing now!", LOGFATALERROR, true);
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		Program.ProcessInput();
		Program.Update();
	}
	Program.CloseConsole();
	Program.Exit();

	Logger::Log("RFGR script loader deactivated", LOGSUCCESS, true);
	Logger::CloseAllLogFiles();

	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	//DisableThreadLibraryCalls(hModule);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
		break;
	default:
		break;
	}
	return TRUE;
}