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
	Logger::Init(LogAll, GetEXEPath(false) + "RFGR Script Loader/Logs/", 10000);
	Logger::OpenLogFile("Load Log.txt", LogAll, std::ios_base::trunc);
	Logger::Log("RFGR Script Loader started. Activating.", LogInfo, true);

	ProgramManager Program(hModule);
	if (!Program.LoadDataFromConfig())
	{
		FreeLibraryAndExitThread(hModule, 0);
		return 0;
	}
	Program.OpenConsole();
	Program.SetMemoryLocations();
	Program.Initialize();

	Logger::Log("RFGR script loader successfully activated.", LogInfo, true);
	Logger::CloseLogFile("Load Log.txt");

	Logger::OpenLogFile("General Log.txt", LogInfo, std::ios_base::trunc);
	Logger::OpenLogFile("Error Log.txt", LogWarning | LogError | LogFatalError, std::ios_base::trunc);
	Logger::OpenLogFile("Json Log.txt", LogJson, std::ios_base::trunc);
	Logger::OpenLogFile("Lua Log.txt", LogLua, std::ios_base::trunc);

	Program.Scripts.ScanScriptsFolder();

	GameState RFGRState;
	while (!Program.ShouldClose()) //Todo: Change to respond to PostQuitMessage(0) in WndProc;
	{
		/*The error messages in the next three if statements are BS. They really
		detect if the player has entered a multiplayer mode. I changed them to 
		hopefully thwart anyone trying to disable multiplayer checks with binary
		patches. It likely won't slow down people who know what they are doing, 
		but I figure it's worth a go.*/
		RFGRState = GameseqGetState();
		if (RFGRState == GS_WRECKING_CREW_MAIN_MENU || 
			RFGRState == GS_WRECKING_CREW_CHARACTER_SELECT || 
			RFGRState == GS_WRECKING_CREW_SCOREBOARD || 
			RFGRState == GS_MULTIPLAYER_LIVE || 
			RFGRState == GS_WC_INIT || 
			RFGRState == GS_WC_SHUTDOWN || 
			RFGRState == GS_MULTIPLAYER_LIVE_FIND_SERVERS)
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