#include "ProgramManager.h"

DWORD WINAPI MainThread(HMODULE hModule);
bool IsFolderPlacementError();

/* This function is the first thing called when the script loader DLL is loaded into rfgr.
 * All it does is start a new thread which runs MainThread. You shouldn't do anything major
 * in DllMain, especially not load other DLLs, as it can apparently cause unstable behavior
 * and crashes due to the way windows handles DLL loading. You should instead place your code
 * in MainThread or some function it calls.
 */
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

/* This function is the main thread of the script loader. It's started by DllMain 
 * when the script loader DLL is loaded. This function performs all the necessary 
 * initialization and error checking for the script loader and then waits for a 
 * reason to close forever. Here's a quick overview of what the thread does:
 * 1. Start logging and open initialization log
 * 2. Check for installation mistakes such as installing the script loader files in the rfg
 *    root folder with rfg.exe. Shuts down and reports detected problems to user if any found.
 * 3. Initializes ProgramManager instance. This sets off all of the real activity of the 
 *    script loader. This includes rfg function hooking, a few binary edits of rfg's code
 *    (runtime only), and initialization of all other parts of the script loader like the 
 *    ScriptManager (handles lua stuff), and the FunctionManager which sets the addresses
 *    of all the function pointers used to call rfg functions.
 * 4. Assuming no errors occured, the script loader now hits it's main loop. This loop simply
 *    checks for requests to close or access to multiplayer at a predefined interval and 
 *    otherwise sleeps most of the time to not be a performance hog. Note that most script loader
 *    code after this point in inside function hooks and therefore is being run by rfgs own 
 *    threads, since function hooks are simply extensions of the games own functions.
 * 5. If the user requests the script loader deactivate, the script loader will try to close 
 *    nicely and leave the game in an unaltered state (as best as possible). If it detects
 *    multiplayer access it'll just shut down it's thread, leaving rfg to crash.
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
        std::string MessageBoxString = R"(Exception detected during Logger initialization! Please show this to the 
        current script loader maintainer. It's much harder to fix any further problems which might occur without logs.)";
        MessageBoxString += Ex.what();
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Logger failed to initialize!", MB_OK);
        Logger::CloseAllLogFiles();
    }

    if(IsFolderPlacementError())
    {
        FreeLibraryAndExitThread(hModule, 0);
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
		Program.Initialize();
        Program.SetMemoryLocations();
    }
    catch(std::exception& Ex)
    {
        std::string MessageBoxString = R"(Exception detected during script loader initialization! Please provide 
        this and a zip file with your logs folder (./RFGR Script Loader/Logs/) to the maintainer.)";
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
        std::string MessageBoxString = R"(Exception detected when opening the default log files. Please show this
        to the current script loader maintainer. It's much harder to fix any further problems which might occur without logs.)";
        MessageBoxString += Ex.what();
        Logger::Log(MessageBoxString, LogFatalError, true, true);
        MessageBoxA(Globals::FindRfgTopWindow(), MessageBoxString.c_str(), "Logger failed to open default log files!", MB_OK);
    }
    Program.Scripts.ScanScriptsFolder();
    /* Initialization complete. After this point the script loader thread simply checks for 
     * close requests or multiplayer access. It spends most of the time sleeping to avoid 
     * performance issues. Any real behavior is in the function hooks and being run by the 
     * game itself at this point.
     */
	
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
            Logger::Log("Invalid graphics state in script loader overlay, crashing!", LogFatalError, true);
            FreeLibraryAndExitThread(hModule, 0);
            return 0;
        }
        if (Globals::MultiplayerHookTriggered)
        {
            Logger::Log("Null pointer in script loader callback system, crashing!", LogFatalError, true);
            FreeLibraryAndExitThread(hModule, 0);
            return 0;
        }
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

/* Tries to find common installation mistakes such as placing it in the rfg root directory rather than it's own 
 * folder. Returns true if errors were found. Returns false if errors were not found.
 */
bool IsFolderPlacementError()
{
    std::string ExePath = Globals::GetEXEPath(false);
    if(!fs::exists(ExePath + "RFGR Script Loader/Core/")) //Detect if the core lua lib folder is missing.
    {
        if (fs::exists(ExePath + "Core/")) //Detect if the user put it in the rfg folder on accident rather than the script loader folder.
        {
            std::string ErrorString = R"(Script Loader Core folder is in the wrong directory! Make sure that it's at 
            "\Red Faction Guerrilla Re-MARS-tered\RFGR Script Loader\Core". It should not be in the same folder as 
            rfg.exe! Shutting down script loader.)";
            Logger::Log(ErrorString, LogFatalError, true, true);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Core folder in wrong root directory!", MB_OK);
        }
        else
        {
            std::string ErrorString = R"(Script Loader Core folder not detected! Make sure that it's at "\Red Faction
            Guerrilla Re-MARS-tered\RFGR Script Loader\Core". Double check the installation guide for an image of how it 
            should look when installed properly. Shutting down script loader.)";
            Logger::Log(ErrorString, LogFatalError, true, true);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Core folder not found!", MB_OK);
        }
        return true;
    } 
    if (!fs::exists(ExePath + "RFGR Script Loader/Fonts/")) //Detect if the fonts folder is missing.
    {
        if (fs::exists(ExePath + "Fonts/")) //Detect if the user put it in the rfg folder on accident rather than the script loader folder.
        {
            std::string ErrorString = R"(Script Loader Fonts folder is in the wrong directory! Make sure that it's at 
            "\Red Faction Guerrilla Re-MARS-tered\RFGR Script Loader\Fonts". It should not be in the same folder as rfg.exe! 
            Shutting down script loader.)";
            Logger::Log(ErrorString, LogFatalError, true, true);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Fonts folder in wrong root directory!", MB_OK);
        }
        else
        {
            std::string ErrorString = R"(Script Loader Fonts folder not detected! Make sure that it's at "\Red Faction
            Guerrilla Re-MARS-tered\RFGR Script Loader\Fonts". Double check the installation guide for an 
            image of how it should look when installed properly. Shutting down script loader.)";
            Logger::Log(ErrorString, LogFatalError, true, true);
            MessageBoxA(Globals::FindRfgTopWindow(), ErrorString.c_str(), "Error! Fonts folder not found.", MB_OK);
        }
        return true;
    }
    return false;
}