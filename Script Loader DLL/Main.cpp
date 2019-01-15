#include "Globals.h"
#include "SnippetManager.h"
#include "ProgramManager.h"
#include "CameraWrapper.h"

/*Fix these in RFGR_Types.h and RFGR_Types_Player.h
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
*/

DWORD WINAPI MainThread(HMODULE hModule)
{
	ProgramManager Program(hModule);
	if (!Program.LoadDataFromConfig())
	{
		FreeLibraryAndExitThread(hModule, 0);
		return 0;
	}
	Program.OpenConsole();
	ConsoleLog("Script loader attached to console", LOGSUCCESS, false, true, true);
	Program.SetMemoryLocations();
	Program.Initialize();

	ConsoleLog("RFGR script loader activated.\n", LOGSUCCESS, true, true);
	GameState RFGRState;
	while (!Program.ShouldClose()) //Todo: Change to respond to PostQuitMessage(0) in WndProc;
	{
		RFGRState = GameseqGetState();
		if (RFGRState == 0x13 || RFGRState == 0x14 || RFGRState == 0x15 || RFGRState == 0x16 || RFGRState == 0x3B || RFGRState == 0x3C || RFGRState == 0x3F) //See GameState enum is RFGR_Types_Player.h for values.
		{
			MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			std::cout << "MP detected. Crashing now!" << std::endl;
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		if (*(bool*)InMultiplayer)
		{
			MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			std::cout << "MP detected. Crashing now!" << std::endl;
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		if (MultiplayerHookTriggered)
		{
			MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
			std::cout << "MP detected. Crashing now!" << std::endl;
			FreeLibraryAndExitThread(hModule, 0);
			return 0;
		}
		Program.ProcessInput();
		Program.Update();
	}
	ConsoleLog("RFGR script loader deactivated.\n\n", LOGSUCCESS, true, true);

	Program.CloseConsole();
	Program.Exit();

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