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
	Globals::ScriptLoaderModule = hModule;

    try
    {
        Logger::Init(LogAll, Globals::GetEXEPath(false) + "RFGR Script Loader/Logs/", 10000);
        Logger::OpenLogFile("Load Log.txt", LogAll, std::ios_base::trunc);
        Logger::Log("RFGR Script Loader started. Activating.", LogInfo, true);
    }
    catch (std::exception& Ex)
    {
        //MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "Exception detected during Logger initialization. Will attempt to use secondary logging location...", "Logger failed to initialize!", MB_OK);
        std::string MessageBoxString = "Exception detected during Logger initialization! Please show this to the current script loader maintainer. It's much harder to fix any further problems which might occur without logs. \n";
        MessageBoxString += Ex.what();
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Logger failed to initialize!", MB_OK);
        Logger::CloseAllLogFiles();
    }

    ProgramManager Program;
    try
    {
        if (!Program.LoadDataFromConfig())
        {
            FreeLibraryAndExitThread(hModule, 0);
            return 0;
        }
        Program.OpenConsole();
        Program.SetMemoryLocations();
        Program.Initialize();
    }
    catch(std::exception& Ex)
    {
        std::string MessageBoxString = "Exception detected during script loader initialization! Please provide this and a zip file with your logs folder (./RFGR Script Loader/Logs/) to the maintainer. \n";
        MessageBoxString += Ex.what();
        Logger::Log(MessageBoxString, LogFatalError, true, true);
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Script loader failed to initialize!", MB_OK);
    }

    try
    {
        Logger::Log("RFGR script loader successfully activated.", LogInfo, true);
        Logger::CloseLogFile("Load Log.txt");

        Logger::OpenLogFile("General Log.txt", LogInfo, std::ios_base::trunc);
        Logger::OpenLogFile("Error Log.txt", LogWarning | LogError | LogFatalError, std::ios_base::trunc);
        Logger::OpenLogFile("Json Log.txt", LogJson, std::ios_base::trunc);
        Logger::OpenLogFile("Lua Log.txt", LogLua, std::ios_base::trunc);
    }
    catch(std::exception& Ex)
    {
        std::string MessageBoxString = "Exception detected when opening the default log files. Please show this to the current script loader maintainer. It's much harder to fix any further problems which might occur without logs. \n";
        MessageBoxString += Ex.what();
        Logger::Log(MessageBoxString, LogFatalError, true, true);
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Logger failed to open default log files!", MB_OK);
    }
    Program.Scripts.ScanScriptsFolder();
	
    const ulong UpdatesPerSecond = 1;
	const ulong MillisecondsPerUpdate = 1000 / UpdatesPerSecond;
    while (!Program.ShouldClose()) //Todo: Change to respond to PostQuitMessage(0) in WndProc
    {
		std::chrono::steady_clock::time_point Begin = std::chrono::steady_clock::now();
        /*Note 1: The error messages in the next three if statements are BS. They really
        detect if the player has entered a multiplayer mode. I changed them to 
        hopefully thwart anyone trying to disable multiplayer checks with binary
        patches. It likely won't slow down people who know what they are doing, 
        but I figure it's worth a go.*/
		/*Note 2: Using a switch statement instead of an if statement since it's slightly more convincing than a bunch of states stuck to an if statement in disasm imo.*/
        const GameState RFGRState = GameseqGetState();
		switch(RFGRState)
		{
		case GS_WRECKING_CREW_MAIN_MENU:
			Logger::Log("Failed to catch exception in UI hook. Script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		case GS_WRECKING_CREW_CHARACTER_SELECT:
			Logger::Log("Null memory access attempted. Script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		case GS_WRECKING_CREW_SCOREBOARD:
			Logger::Log("Rfg deleted something important, script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		case GS_MULTIPLAYER_LIVE:
			Logger::Log("Failed to relocate rfg application struct after patch, script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		case GS_WC_INIT:
			Logger::Log("Free cam init binary patched something it shouldn't have, script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		case GS_WC_SHUTDOWN:
			Logger::Log("Dynamic allocator failure, script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		case GS_MULTIPLAYER_LIVE_FIND_SERVERS:
			Logger::Log("Failed to refresh object hashmap, script loader crashing!", LogFatalError, true);
			FreeLibraryAndExitThread(hModule, 0);
			break;
		default:
			break;
		}
        if (*Globals::InMultiplayer)
        {
            //MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
            Logger::Log("Invalid graphics state in script loader overlay, crashing!", LogFatalError, true);
            FreeLibraryAndExitThread(hModule, 0);
            return 0;
        }
        if (Globals::MultiplayerHookTriggered)
        {
            //MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), "MP usage detected, shutting down!", "Multiplayer mode detected", MB_OK);
            Logger::Log("Null pointer in script loader callback system, crashing!", LogFatalError, true);
            FreeLibraryAndExitThread(hModule, 0);
            return 0;
        }
        //Program.ProcessInput();
        Program.Update();
		std::chrono::steady_clock::time_point End = std::chrono::steady_clock::now();
		Sleep(MillisecondsPerUpdate - std::chrono::duration_cast<std::chrono::milliseconds>(End - Begin).count());
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
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, 0);
        break;
    default:
        break;
    }
    return TRUE;
}