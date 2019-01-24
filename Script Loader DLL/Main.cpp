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
	Logger::Init(LogAll, GetEXEPath(false) + "RFGR Script Loader/Logs/");
	Logger::OpenLogFile("Load Log.txt", LogAll, std::ios_base::trunc);
	Logger::Log("RFGR Script Loader started. Activating.", LogInfo, true);

	//Logger::Log("Before ProgramManager::ProgramManager()", LogInfo);
	ProgramManager Program(hModule);
	//Logger::Log("Before Program.LoadDataFromConfig()", LogInfo);
	if (!Program.LoadDataFromConfig())
	{
		FreeLibraryAndExitThread(hModule, 0);
		return 0;
	}
	//Logger::Log("Before Program.OpenConsole()", LogInfo);
	Program.OpenConsole();
	//Logger::Log("RFGR Script Loader attached to external console", LogInfo, true);
	//Logger::Log("Before Program.SetMemoryLocations()", LogInfo);
	Program.SetMemoryLocations();
	//Logger::Log("Before Program.Initialize()", LogInfo);
	Program.Initialize();

	Logger::Log("RFGR script loader successfully activated.", LogInfo, true);
	Logger::CloseLogFile("Load Log.txt");

	Logger::OpenLogFile("General Log.txt", LogInfo, std::ios_base::trunc);
	Logger::OpenLogFile("Error Log.txt", LogWarning | LogError | LogFatalError, std::ios_base::trunc);
	Logger::OpenLogFile("Json Log.txt", LogJson, std::ios_base::trunc);
	Logger::OpenLogFile("Lua Log.txt", LogLua, std::ios_base::trunc);

	GameState RFGRState;
	while (!Program.ShouldClose()) //Todo: Change to respond to PostQuitMessage(0) in WndProc;
	{
		/*The error messages in the next three if statements are BS. They really
		detect if the player has entered a multiplayer mode. I changed them to 
		hopefully thwart anyone trying to disable multiplayer checks with binary
		patches. It likely won't slow down people who know what they are doing, 
		but I figure it's worth a go.*/
		RFGRState = GameseqGetState();
		if (RFGRState == 0x13 || RFGRState == 0x14 || RFGRState == 0x15 || RFGRState == 0x16 || RFGRState == 0x3B || RFGRState == 0x3C || RFGRState == 0x3F) //See GameState enum is RFGR_Types_Player.h for values.
		{
			//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			Logger::Log("Error in UI hook, script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		if (*(bool*)InMultiplayer)
		{
			//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			Logger::Log("Invalid graphics state in script loader overlay, crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		if (MultiplayerHookTriggered)
		{
			//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			Logger::Log("Null pointer in script loader callback system, crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		Program.ProcessInput();
		Program.Update();
	}
	Program.CloseConsole();
	Program.Exit();

	Logger::Log("RFGR script loader deactivated", LogInfo, true);
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