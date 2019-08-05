#include "ScriptManager.h"
#include "BaseTypeLua.h"
#include "VectorLua.h"
#include "MatrixLua.h"
#include "Matrix43Lua.h"
#include "AttachInfoDataLua.h"
#include "ContactNodeLua.h"
#include "ObjectFlagsLua.h"
#include "HavokBPOLua.h"
#include "HkpRigidBodyLua.h"
#include "HkpSolverInfoLua.h"
#include "HumanFlagsLua.h"
#include "HumanMPFlagsLua.h"
#include "InvItemInfoLua.h"
#include "ObjectRenderDistanceLua.h"
#include "HumanRaycastHitInfoLua.h"
#include "CharacterInstanceLua.h"
#include "HumanInfoLua.h"
#include "ObjectLua.h"
#include "HumanLua.h"
#include "PlayerLua.h"
#include "WorldLua.h"
#include "ExplosionInfoLua.h"

ScriptManager::~ScriptManager()
{
    delete LuaState;
}

/* Resets the script loader lua state and reloads the core libraries.
 * This includes the scripts in the Core folder.
 */
void ScriptManager::Reset()
{
    delete LuaState;
    Initialize();
    UpdateRfgPointers();
}

/* Initializes the lua state and calls all necessary functions and scripts 
 * needed to setup the scripting system. No inputs or outputs. Uses new
 * to allocate a new sol::state at ScriptManager::LuaState
 */
void ScriptManager::Initialize()
{
    LuaState = new sol::state();
    /* Opens the listed lua core libraries
	 * See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	 * and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	 * For now there is no Lua sandboxing in place to remove as many barriers for creativity that modders might have had otherwise.
	 */
	LuaState->open_libraries
	(
		sol::lib::base,
		sol::lib::package,
		sol::lib::coroutine,
		sol::lib::string,
		sol::lib::os,
		sol::lib::math,
		sol::lib::table,
		sol::lib::debug,
		sol::lib::bit32,
		sol::lib::io,
		sol::lib::ffi,
		sol::lib::jit
	);
	SetupLua();
}

/* Contains all of the binding code for rfg types and functions and any helper functions.
 * Note that many pieces of binding code are in other files. For example, the binding code for Player
 * is in PlayerLua.h/.cpp. This is intended to speed up compilation by splitting up the files 
 * (not sure if that is really accomplished) and also to keep this function from becoming a several 
 * thousand line behemoth.
 */
void ScriptManager::SetupLua()
{
	RunScript(Globals::GetEXEPath(false) + "RSL/Core/CoreInit.lua");
    sol::state& LuaStateRef = *LuaState; //Used for easier access instead of doing weird ass pointer syntax.

    LuaStateRef["print"] = sol::nil;
    //LuaStateRef.set_function("tostring", sol::overload(
    //    [](int Value) {return std::to_string(Value); },
    //    [](long Value) {return std::to_string(Value); },
    //    [](long long Value) {return std::to_string(Value); },
    //    [](unsigned int Value) {return std::to_string(Value); },
    //    [](unsigned long Value) {return std::to_string(Value); },
    //    [](unsigned long long Value) {return std::to_string(Value); },
    //    [](float Value) {return std::to_string(Value); },
    //    [](double Value) {return std::to_string(Value); },
    //    [](long double Value) {return std::to_string(Value); },
    //    [](char Value) {return std::to_string(Value); },
    //    [](const char* Value) {return std::string(Value); },
    //    [](std::string Value) {return Value; }
    //));

	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	auto RslTable = LuaStateRef["rsl"].get_or_create<sol::table>();
	RslTable["GetVersion"] = Globals::GetScriptLoaderVersion;
	RslTable["LogModuleBase"] = Lua::LogModuleBase;

    //LogType enums defined in lua
    //auto LoggerTable = LuaStateRef["Logger"].get_or_create<sol::table>();
    RslTable["OpenLogFile"] = Logger::OpenLogFile;
    RslTable["CloseLogFile"] = Logger::CloseLogFile;
    RslTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles; //Todo: Probably should document this func and the previous two in lua

    RslTable["Log"] = Lua::Log;
    RslTable["LogNone"] = Lua::LogNone;
    RslTable["LogInfo"] = Lua::LogInfo;
    RslTable["LogWarning"] = Lua::LogWarning;
    RslTable["LogError"] = Lua::LogError;
    RslTable["LogFatalError"] = Lua::LogFatalError;
    RslTable["LogLua"] = Lua::LogLua;
    RslTable["LogJson"] = Lua::LogJson;

    RslTable["LogFlagWithColor"] = Logger::LogFlagWithColor; //Todo: Probably should document these 4 funcs at some point in lua.
    RslTable["GetFlagString"] = Logger::GetFlagString;
    RslTable["LogToFile"] = Logger::LogToFile;
    RslTable["GetTimeString"] = Logger::GetTimeString;

    //RslTable["Beep"] = [](DWORD Frequency, DWORD Duration) {std::async((std::launch::async), [&] {Beep(Frequency, Duration); }); };
    //RslTable["Beep"] = Util::General::ThreadedBeep;

    RslTable.set_function("CharArrayToString", sol::overload(
        [](char* Array, int Size) { return Globals::CharArrayToString(Array, Size); },
        [](const char* Array, int Size) { return Globals::CharArrayToString(Array, Size); }
    ));

	auto RfgTable = LuaStateRef["rfg"].get_or_create<sol::table>();
	RfgTable["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;
	RfgTable["ToggleFog"] = ToggleFog;
    RfgTable["ToggleHud"] = ToggleHud;
	RfgTable["SetFarClip"] = GameRenderSetFarClipDistance;
	RfgTable["GetFarClip"] = GameRenderGetFarClipDistance;
	RfgTable["SetAlertLevel"] = GsmSetAlertLevel;
	RfgTable["GetAlertLevel"] = GsmGetAlertLevel;
	//RfgTable["TeleportHuman"] = HumanTeleportUnsafe;
    RfgTable.set_function("TeleportHuman", sol::overload(
        [](Human* Target, vector Position, matrix Orientation) { HumanTeleportUnsafe(Target, Position, Orientation); },
        [](Human* Target, vector Position) { HumanTeleportUnsafe(Target, Position, Target->Orientation); }
    ));
	RfgTable["GetPlayer"] = Lua::GetPlayer; //Didn't document these "get" functions online since we have "rfg.ActiveXXX". Probably can just remove these.
	RfgTable["GetWorld"] = Lua::GetWorld;
	RfgTable["GetPhysicsWorld"] = Lua::GetPhysicsWorld;
    RfgTable.set_function("GetObject", sol::overload( //Documented
        Lua::GetObjectByName,
        Lua::GetObjectByHandle
    ));

    RfgTable["GetGravity"] = Lua::GetGravity;
    RfgTable.set_function("SetGravity", sol::overload(
        [](vector& NewGravity) {Lua::SetGravity(NewGravity); },
        [](float x, float y, float z) {Lua::SetGravity(x, y, z); }));
    RfgTable["ResetGravity"] = Lua::ResetGravity;

	RfgTable["HavokBodyGetPointer"] = HavokBodyGetPointer;
	RfgTable.set_function("ApplyLinearImpulse", sol::overload(HavokBodyApplyLinearImpulseA, HavokBodyApplyLinearImpulseB));

	RfgTable.set_function("TeleportPlayer", sol::overload(
        [](vector Position, matrix Orientation) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Orientation); }, 
		[](vector Position) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Globals::PlayerPtr->Orientation); },
		[](float x, float y, float z) {HumanTeleportUnsafe(Globals::PlayerPtr, vector(x, y, z), Globals::PlayerPtr->Orientation); }
    ));

    RfgTable["GetVersion"] = KeenGetBuildVersionString;
    RfgTable["StringHash"] = Lua::RfgStringHashWrapper;

    RfgTable.set_function("ExplosionCreate", sol::overload( //Todo: Maybe rename this to SpawnExplosion. //Todo: Add overload that just takes preset name and position.
        [](explosion_info* Info, Object* Source, Object* Owner, vector* Position, matrix* Orientation, vector* Direction)// , weapon_info* WeaponInfo) //Todo: Add WeaponInfo once that's bound to lua
        {ExplosionCreate(Info, Source, Owner, Position, Orientation, Direction, nullptr, false); }, //Todo: remember to replace this nullptr with WeaponInfo once bound
        [](explosion_info* Info, vector* Position) {ExplosionCreate(Info, nullptr, nullptr, Position, new matrix(0.0f), new vector(0.0f, 1.0f, 0.0f), nullptr, false); },
        [](explosion_info* Info, float x, float y, float z)
        {
            vector Position(x, y, z); 
            ExplosionCreate(Info, nullptr, nullptr, &Position, new matrix(0.0f), new vector(0.0f, 1.0f, 0.0f), nullptr, false);
        }
    ));
    RfgTable["GetExplosionInfo"] = Lua::GetExplosionInfo;

    //explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position, matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer
	//This warning appears hundreds of times in a row during binding unless disabled. Is harmless due to some lambdas used to grab usertype variables.
	#pragma warning(push)
	#pragma warning(disable : C4172)
	//Use separate files for these so that if one is edited they don't all need to be recompiled.
	//Not necessarily at huge benefit at first, but it'll grow as more usertypes are added.
	Lua::BindRfgBaseArray(LuaStateRef);
	Lua::BindRfgFArray(LuaStateRef);
	Lua::BindTimestamp(LuaStateRef);
	Lua::BindTimestampPercent(LuaStateRef);
	Lua::BindTimestampRealtime(LuaStateRef);
	Lua::BindColor(LuaStateRef);
	Lua::BindVector(LuaStateRef);
	Lua::BindMatrix(LuaStateRef);
	Lua::BindMatrix43(LuaStateRef);
	Lua::BindAttachInfoData(LuaStateRef);
	Lua::BindContactNode(LuaStateRef);
	Lua::BindObjectContactInfo(LuaStateRef);
	Lua::BindObjectFlags(LuaStateRef);
	//Lua::BindRemoteObjectFlags(LuaStateRef);
	Lua::BindHavokBPO(LuaStateRef);
	Lua::BindHkpMaterial(LuaStateRef);
	Lua::BindHkpEntity(LuaStateRef);
	Lua::BindHkpRigidBody(LuaStateRef);
    Lua::BindHkpSolverInfo(LuaStateRef);
	Lua::BindHumanFlags(LuaStateRef); 
	//Lua::BindHumanMPFlags(LuaStateRef);
	Lua::BindHumanInfoFlags(LuaStateRef);
	Lua::BindHumanPropGeneralInfo(LuaStateRef);
	Lua::BindInventoryItem(LuaStateRef);
	Lua::BindChecksumStri(LuaStateRef);
	Lua::BindInvItemInfo(LuaStateRef);
	Lua::BindFootGroundEffects(LuaStateRef);
	Lua::BindCharDefHead(LuaStateRef);
	Lua::BindObjectRenderDistance(LuaStateRef);
	Lua::BindHumanRaycastHitInfo(LuaStateRef);
	Lua::BindCharacterInstance(LuaStateRef);
	Lua::BindWeaponAnimationFlags(LuaStateRef);
	Lua::BindIKJoint(LuaStateRef);
	Lua::BindNanoCallbackInfo(LuaStateRef);
	Lua::BindHumanInfo(LuaStateRef);
	Lua::BindUsableObject(LuaStateRef);
	Lua::BindPlayerFlags(LuaStateRef);
	Lua::BindScriptSpecificData(LuaStateRef);
	Lua::BindVehicleEnterStruct(LuaStateRef);
	Lua::BindPathfindNavInfo(LuaStateRef);
	Lua::BindUpgradeItem(LuaStateRef);
	Lua::BindPlayerMetadata(LuaStateRef);
	Lua::BindObject(LuaStateRef);
	Lua::BindHuman(LuaStateRef);
	Lua::BindPlayer(LuaStateRef);

	//World & dependent types
	Lua::BindStreamGridCell(LuaStateRef);
	Lua::BindStreamLayerMaskedCell(LuaStateRef);
	Lua::BindStreamLayer(LuaStateRef);
	Lua::BindDistrictFlags(LuaStateRef);
	Lua::BindTDistrict(LuaStateRef);
	Lua::BindTerritory(LuaStateRef);
	Lua::BindStreamGrid(LuaStateRef);
	Lua::BindGameSaveInfoNewData(LuaStateRef);
	Lua::BindGameSaveInfo(LuaStateRef);
	Lua::BindSaveLoadInfo(LuaStateRef);
	Lua::BindWorldStateBuf(LuaStateRef);
	Lua::BindZoneHeader(LuaStateRef);
	Lua::BindWorldZone(LuaStateRef);
	Lua::BindWorld(LuaStateRef);

    Lua::BindFixedArrayWrapperExplosionInfo(LuaStateRef);
    Lua::BindExplosionInfo(LuaStateRef);
	#pragma warning(pop) 

    UpdateRfgPointers();
    //Todo: Add binding func for rfg lua state and see if I can't add other functions to it to use in rfg scripts. Might be complicated by the fact that it uses a different lua version
}

/* Used to ensure a few important game pointers are always up to date.
 * Since these can sometimes change when doing things like loading a save
 * it's necessary to update them in the lua state. This function is called
 * by several hooks when they detect that one of these pointers has changed.
 * If you're hooking something that changes often and needs global state, you
 * should probably update it here as well when it changes.
 */
void ScriptManager::UpdateRfgPointers()
{
    sol::state& LuaStateRef = *LuaState;
	auto RfgTable = LuaStateRef["rfg"].get_or_create<sol::table>();

	RfgTable["ActivePlayer"] = Globals::PlayerPtr;
	RfgTable["ActiveWorld"] = Globals::RfgWorldPtr;
	RfgTable["ActivePhysicsWorld"] = Globals::hkpWorldPtr;
    RfgTable["PhysicsSolver"] = &Globals::hkpWorldPtr->m_dynamicsStepInfo.m_solverInfo;
    RfgTable["ExplosionInfos"] = &Globals::ExplosionInfos;
}

/* Scans all files in the Scripts folder. Creates a new script object and adds it to
 * the script vector (ScriptManager::Scripts) if a file is a valid script. 
 */
void ScriptManager::ScanScriptsFolder()
{
	try 
	{
		SubFolders.clear();
		const std::string ScriptFolderPath(Globals::GetEXEPath(false) + "RSL/Scripts/");
		for (auto& SubFolder : fs::directory_iterator(ScriptFolderPath))
		{
            if(SubFolder.is_directory())
            {
                SubFolders.push_back(ScriptFolder(SubFolder.path().string(), GetScriptNameFromPath(SubFolder.path().string())));
                for(auto& File : fs::directory_iterator(SubFolder.path()))
                {
                    if (IsValidScriptExtensionFromPath(File.path().string()))
                    {
                        const std::string ThisScriptPath = File.path().string();
                        const std::string ThisScriptFolderPath = GetScriptFolderFromPath(File.path().string());
                        const std::string ThisScriptName = GetScriptNameFromPath(File.path().string());
                        SubFolders.back().Scripts.push_back(Script(ThisScriptPath, ThisScriptFolderPath, ThisScriptName));

                        //Logger::Log(i.path().string(), LogInfo);
                        //Logger::Log("Script Name: " + ThisScriptName, LogInfo);
                        //Logger::Log("Script Folder: " + ThisScriptFolderPath, LogInfo);
                    }
                }
                if(SubFolders.back().Scripts.empty())
                {
                    SubFolders.pop_back(); //Ignore empty sub folders
                }
            }
		}
	}
	catch(std::exception& Ex)
	{
		std::string ExceptionInfo = Ex.what();
		ExceptionInfo += " \nstd::exception when scanning scripts folder, Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		Logger::LogFatalError("{}\n", ExceptionInfo);
	}
}

void ScriptManager::RunStartupScripts()
{
    for(auto& Folder : SubFolders)
    {
        for(auto& Script : Folder.Scripts)
        {
            if(Util::General::ToLower(Script.Name) == "main.lua")
            {
                RunScript(Script.FullPath);
            }
        }
    }
}

/* Tries to run the file at the given path as a lua script. Includes error 
 * detection and handling code for convenience. If an exception occurs an the 
 * script should be stopped and the exception should be safely contained and
 * logged.
 */
bool ScriptManager::RunScript(const std::string& FullPath)                     
{
    sol::load_result LoadResult = LuaState->load(Util::General::LoadFileToString(FullPath));
    std::string Name = GetScriptNameFromPath(FullPath);

    if (!LoadResult.valid())
    {
        sol::error Error = LoadResult;
        std::string What(Error.what());
        Logger::LogError("{} failed the syntax check! Message: {}", Name, What);
        return true;
    }

    sol::protected_function_result Result = LoadResult();
    if (!Result.valid())
    {
        sol::error Error = Result;
        std::string What(Error.what());
        Logger::LogError("{} encountered an error! Message: {}", Name, What);
        return true;
    }

    return false;
}

/* Tries to an already loaded script at the given index of
 * ScriptManager::Scripts. Includes error detection and handling code 
 * for convenience. If an exception occurs an the script should be 
 * stopped and the exception should be safely contained and logged.
 */
bool ScriptManager::RunScript(const size_t Index)
{
    auto& Script = SubFolders[Index];
    sol::load_result LoadResult = LuaState->load(Util::General::LoadFileToString(Script.FullPath));

    if(!LoadResult.valid())
    {
        sol::error Error = LoadResult;
        std::string What(Error.what());
        Logger::LogError("{} failed the syntax check! Message: {}", Script.Name, What);
        return true;
    }

    sol::protected_function_result Result = LoadResult();
    if (!Result.valid())
    {
        sol::error Error = Result;
        std::string What(Error.what());
        Logger::LogError("{} encountered an error! Message: {}", Script.Name, What);
        return true;
    }

    return false;
}

/* Tries to the provided string as a lua script. Uses the name for 
 * error logging. Includes error detection and handling code
 * for convenience. If an exception occurs an the script should be
 * stopped and the exception should be safely contained and logged.
 */
ScriptResult ScriptManager::RunStringAsScript(std::string Buffer, std::string Name)
{
    sol::load_result LoadResult = LuaState->load(Buffer);

    if(!LoadResult.valid()) //Check script syntax but don't execute
    {
        sol::error Error = LoadResult;
        std::string What(Error.what());
        Logger::LogError("{} failed the syntax check! Message: {}", Name, What);
        return ScriptResult(true, GetLineFromErrorString(What), What);
    }

    sol::protected_function_result Result = LoadResult();
    if(!Result.valid())
    {
        sol::error Error = Result;
        std::string What(Error.what());
        Logger::LogError("{} encountered an error! Message: {}", Name, What);
        return ScriptResult(true, GetLineFromErrorString(What), What);
    }

    return ScriptResult(false, {}, {});
}

// Attempts to get the error line number by parsing a lua error string. 
// Works on the assumption that the number will have a colon in front of it. Such as "[string "rfg.SetGravity(0.0, -2.8, 0...."]:5: attempt to call field 'FakeFunc' (a nil value)..."
// In that example error the line number is :5:
std::optional<uint> ScriptManager::GetLineFromErrorString(const std::string& ErrorString) const
{
    for(int i = 0; i < ErrorString.length(); i++)
    {
        if(i < ErrorString.length() - 2) //Don't bother checking if you can't at least pull a 1-digit number from the rest of the string
        {
            char CurrentChar = ErrorString[i];
            char NextChar = ErrorString[i + 1];

            if (CurrentChar == ':')
            {
                if(CharIsDigit(NextChar))
                {
                    int NumberStartIndex = i + 1;
                    int Index = i;
                    do
                    {
                        Index++;
                        CurrentChar = ErrorString[Index];
                    } 
                    while (CharIsDigit(CurrentChar) && i < ErrorString.length());

                    return std::stoi(ErrorString.substr(NumberStartIndex, Index - NumberStartIndex));
                }
            }
        }
    }
    return {}; //Return empty if no line number found
}

bool ScriptManager::CharIsDigit(const char& Character) const
{
    return Character >= '0' && Character <= '9';
}

/* Gets the name of a file given a path as an input. 
 * Includes file extension in name. Returns an empty
 * string if no forward or backslashes are found.
 */
std::string ScriptManager::GetScriptNameFromPath(std::string FullPath) const
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(i + 1, FullPath.length() - i);
			}
		}
	}
	return std::string();
}

/* Gets the path of the folder for a file. Takes the full path
 * of a file as input. Basically just cuts the file name off 
 * the end of it's path. Returns an empty string if no forward
 * or backslashes are found.
 */
std::string ScriptManager::GetScriptFolderFromPath(const std::string& FullPath) const
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(0, i + 1);
			}
		}
	}
	return std::string();
}

/* Gets the extension of a file given it's full path. Returns
 * an empty string if no period is found in the name.
 */
std::string ScriptManager::GetScriptExtensionFromPath(const std::string& FullPath) const
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (FullPath.compare(i, 1, ".") == 0)
		{
			return FullPath.substr(i + 1, FullPath.length() - i);
		}
	}
	return std::string();
}

/* Checks if the file at the provided path has a valid script
 * file extension. Returns true if so, and false if not.
 */
bool ScriptManager::IsValidScriptExtensionFromPath(std::string FullPath) const
{
	if (IsValidScriptExtension(GetScriptExtensionFromPath(FullPath)))
	{
		return true;
	}
	return false;
}

/* Checks if the provided string is a valid script file extension.
 * Returns true if so, and false if not. Currently "lua" is 
 * considered valid. It converts the inputted string to lowercase
 * before comparison, so case does not matter.
 */
bool ScriptManager::IsValidScriptExtension(std::string Extension) const
{
    //Transform extension to lowercase only for easy comparison.
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
    return Extension == "lua";
}

