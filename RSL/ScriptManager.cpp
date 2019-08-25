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
#include "TimerLua.h"
#include "WeaponInfoLua.h"
#include "CameraWrapper.h"
#include "ApiTables.h"
#include "VehicleInfoLua.h"

ScriptManager::~ScriptManager()
{
    delete LuaState;
}

//Resets the script loader lua state and reloads the core libraries including the scripts in the Core folder.
void ScriptManager::Reset()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);
    delete LuaState;

    for(auto& Event : Events)
    {
        Event.Reset(); //Todo: See if there's a cleaner way to do this while also being thread safe. This is a bit obtuse.
    }

    Initialize();
    UpdateRfgPointers();
    RunStartupScripts();
}

//Initializes the lua state and calls all necessary functions and scripts needed to setup the scripting system.
void ScriptManager::Initialize()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);
    LuaState = new sol::state();
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

//Contains all of the binding code for rfg types and functions and any helper functions.
void ScriptManager::SetupLua()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

	RunScript(Globals::GetEXEPath(false) + "RSL/Core/CoreInit.lua");
    sol::state& LuaStateRef = *LuaState;

    Lua::BindApiFunctions(LuaStateRef);

	#pragma warning(push)
	#pragma warning(disable : C4172)
	Lua::BindRfgBaseArrayObjectPtr(LuaStateRef);
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
	Lua::BindHavokBPO(LuaStateRef);
	Lua::BindHkpMaterial(LuaStateRef);
	Lua::BindHkpEntity(LuaStateRef);
	Lua::BindHkpRigidBody(LuaStateRef);
    Lua::BindHkpSolverInfo(LuaStateRef);
	Lua::BindHumanFlags(LuaStateRef); 
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
    Lua::BindTimer(LuaStateRef);
    Lua::BindFixedArrayWrapperWeaponInfo(LuaStateRef);
    Lua::BindWeaponProjectileInfo(LuaStateRef);
    Lua::BindDamageScalingInfo(LuaStateRef);
    Lua::BindWeaponInfoFlags(LuaStateRef);
    Lua::BindWeaponInfo(LuaStateRef);

    Lua::BindBbox(LuaStateRef);
    Lua::BindVehicleInfoAxleWheelInfo(LuaStateRef);
    Lua::BindRfgFarrayVehicleInfo163(LuaStateRef);
    Lua::BindVehicleInfoTransmissionInfo(LuaStateRef);
    Lua::BindVehicleCameraSettings(LuaStateRef);
    Lua::BindAnimlibBonesUsedInfo(LuaStateRef);
    Lua::BindVehicleInfo(LuaStateRef);

	#pragma warning(pop) 

    UpdateRfgPointers();
}

void ScriptManager::RegisterEvent(std::string EventTypeName, const sol::function& EventFunction, const std::string& EventName)
{
    const std::string TypeNameLower = Util::General::ToLower(EventTypeName); //Don't want case to matter for event names
    for(auto& Event : Events)
    {
        if(TypeNameLower == Event.Name)
        {
            Event.Hooks.emplace_back(EventName, EventFunction);
            return;
        }
    }
    throw std::exception(fmt::format("\"{}\" is not a valid event name!", EventTypeName).c_str());
}

/* Used to ensure a few important game pointers are always up to date. Since these can sometimes change
 * when doing things like loading a save it's necessary to update them in the lua state. This function is
 * called by several hooks when they detect that one of these pointers has changed. If you're hooking 
 * something that changes often and needs global state, you should probably update it here as well when 
 * it changes.
 */
void ScriptManager::UpdateRfgPointers()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);
    sol::state& LuaStateRef = *LuaState;
	auto RfgTable = LuaStateRef["rfg"].get_or_create<sol::table>();

    RfgTable["ActivePlayer"] = Globals::PlayerPtr;
	RfgTable["ActiveWorld"] = Globals::RfgWorldPtr; 
	RfgTable["ActivePhysicsWorld"] = Globals::hkpWorldPtr; 
    RfgTable["PhysicsSolver"] = &Globals::hkpWorldPtr->m_dynamicsStepInfo.m_solverInfo;
    RfgTable["ExplosionInfos"] = &Globals::ExplosionInfos;
    RfgTable["WeaponInfos"] = Globals::WeaponInfos;
    RfgTable["PlayerMaxMovementSpeedOverride"] = Globals::PlayerMaxMovementSpeedOverride;
    RfgTable["VehicleInfos"] = Globals::VehicleInfos;
    
    LuaStateRef["Player"] = Globals::PlayerPtr;
	LuaStateRef["World"] = Globals::RfgWorldPtr;
	LuaStateRef["PhysicsWorld"] = Globals::hkpWorldPtr;
}

//Scans all files in the Scripts folder and places valid script files in the scripts list (this->Scripts)
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
                SubFolders.emplace_back(SubFolder.path().string(), GetScriptNameFromPath(SubFolder.path().string()));
                for(auto& File : fs::directory_iterator(SubFolder.path()))
                {
                    if (IsValidScriptExtensionFromPath(File.path().string()))
                    {
                        const std::string ThisScriptPath = File.path().string();
                        const std::string ThisScriptFolderPath = GetScriptFolderFromPath(File.path().string());
                        const std::string ThisScriptName = GetScriptNameFromPath(File.path().string());
                        SubFolders.back().Scripts.emplace_back(ThisScriptPath, ThisScriptFolderPath, ThisScriptName);
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
    std::lock_guard<std::recursive_mutex> Lock(Mutex);
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

bool ScriptManager::RunScript(const std::string& FullPath)                     
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    if (!std::filesystem::path(FullPath).has_filename()) return false;

    std::string ScriptName = std::filesystem::path(FullPath).filename().string();
    std::string Buffer = Util::General::LoadFileToString(FullPath);
    auto Result = RunStringAsScript(Buffer, ScriptName);
    return !Result.Failed;
}

bool ScriptManager::RunScript(const size_t Index)
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    auto& Script = SubFolders[Index];
    std::string Buffer = Util::General::LoadFileToString(Script.FullPath);
    auto Result = RunStringAsScript(Buffer, Script.Name);
    return !Result.Failed;
}

/* Tries to the provided string as a lua script. Uses the name for 
 * error logging. Includes error detection and handling code
 * for convenience. If an exception occurs an the script should be
 * stopped and the exception should be safely contained and logged.
 */
ScriptResult ScriptManager::RunStringAsScript(std::string Buffer, const std::string& Name)
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

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
                if(Util::CharIsDigit(NextChar))
                {
                    int NumberStartIndex = i + 1;
                    int Index = i;
                    do
                    {
                        Index++;
                        CurrentChar = ErrorString[Index];
                    } 
                    while (Util::CharIsDigit(CurrentChar) && i < ErrorString.length());

                    return std::stoi(ErrorString.substr(NumberStartIndex, Index - NumberStartIndex));
                }
            }
        }
    }
    return {}; //Return empty if no line number found
}

void ScriptManager::TriggerInputEvent(uint Message, uint KeyCode, KeyState& Keys)
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    if (game_is_paused()) return;
    if (!LuaState) return;

    ScriptEvent& InputEvents = Events[0];
    InputEvents.Update();

    if (InputEvents.Enabled())
    {
        for (auto& EventHook : InputEvents.Hooks)
        {
            if (EventHook.Enabled)
            {
                sol::table EventData = LuaState->create_table();
                EventData["KeyDown"] = static_cast<bool>(Message == WM_KEYDOWN);
                EventData["KeyUp"] = static_cast<bool>(Message == WM_KEYUP);
                EventData["KeyCode"] = KeyCode;
                EventData["ControlDown"] = Keys.ControlDown;
                EventData["ShiftDown"] = Keys.ShiftDown;
                EventData["AltDown"] = Keys.AltDown;
                EventData["WindowsDown"] = Keys.WindowsDown;

                //Todo: Make a function that safely calls sol::functions like this, and wraps it in logging and error reporting code
                sol::protected_function_result Result = EventHook.Hook(EventData);
                if (!Result.valid())
                {
                    sol::error Error = Result;
                    std::string What(Error.what());
                    Logger::LogError("{} encountered an error! Message: {}", EventHook.HookName, What);
                }
            }
        }
    }
}

void ScriptManager::TriggerDoFrameEvent()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    if (game_is_paused()) return;
    if (!LuaState) return;

    ScriptEvent& DoFrameEvents = Events[1];
    DoFrameEvents.Update();

    if (DoFrameEvents.Enabled())
    {
        for (auto& EventHook : DoFrameEvents.Hooks)
        {
            if (EventHook.Enabled)
            {
                sol::table EventData = LuaState->create_table();
                if(Globals::Frametime)
                {
                    EventData["Frametime"] = *Globals::Frametime;
                }
                else
                {
                    EventData["Frametime"] = 0.0f;
                }

                //Todo: Make a function that safely calls sol::functions like this, and wraps it in logging and error reporting code
                sol::protected_function_result Result = EventHook.Hook(EventData);
                if (!Result.valid())
                {
                    sol::error Error = Result;
                    std::string What(Error.what());
                    Logger::LogError("{} encountered an error! Message: {}", EventHook.HookName, What);
                }
            }
        }
    }
}

void ScriptManager::TriggerInitializedEvent()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    if (!LuaState) return;

    ScriptEvent& InitializedEvents = Events[2];
    InitializedEvents.Update();

    if (InitializedEvents.Enabled())
    {
        for (auto& EventHook : InitializedEvents.Hooks)
        {
            if (EventHook.Enabled)
            {
                //Todo: Make a function that safely calls sol::functions like this, and wraps it in logging and error reporting code
                sol::protected_function_result Result = EventHook.Hook();
                if (!Result.valid())
                {
                    sol::error Error = Result;
                    std::string What(Error.what());
                    Logger::LogError("{} encountered an error! Message: {}", EventHook.HookName, What);
                }
            }
        }
    }
}

void ScriptManager::TriggerMouseEvent(uint Message, uint wParam, uint lParam, KeyState& Keys)
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    if (game_is_paused()) return;
    if (!LuaState) return;

    ScriptEvent& MouseEvent = Events[3];
    MouseEvent.Update();

    if (MouseEvent.Enabled())
    {
        for (auto& EventHook : MouseEvent.Hooks)
        {
            if (EventHook.Enabled)
            {
                sol::table EventData = LuaState->create_table();
                if(Message == WM_MOUSEWHEEL)
                {
                    EventData["Scrolled"] = true;
                    EventData["ScrollDelta"] = GET_WHEEL_DELTA_WPARAM(wParam);
                }
                else
                {
                    EventData["Scrolled"] = false;
                    EventData["ScrollDelta"] = 0;
                }
                if(Message == WM_MOUSEMOVE)
                {
                    EventData["MouseMove"] = true;
                    EventData["MouseX"] = GET_X_LPARAM(lParam);
                    EventData["MouseY"] = GET_Y_LPARAM(lParam);
                }
                else
                {
                    EventData["MouseMove"] = false;
                    EventData["MouseX"] = 0;
                    EventData["MouseY"] = 0;
                }

                EventData["ControlDown"] = Keys.ControlDown;
                EventData["ShiftDown"] = Keys.ShiftDown;
                EventData["AltDown"] = Keys.AltDown;
                EventData["WindowsDown"] = Keys.WindowsDown;

                //Todo: Make a function that safely calls sol::functions like this, and wraps it in logging and error reporting code
                sol::protected_function_result Result = EventHook.Hook(EventData);
                if (!Result.valid())
                {
                    sol::error Error = Result;
                    std::string What(Error.what());
                    Logger::LogError("{} encountered an error! Message: {}", EventHook.HookName, What);
                }
            }
        }
    }
}

void ScriptManager::TriggerLoadEvent()
{
    std::lock_guard<std::recursive_mutex> Lock(Mutex);

    if (!LuaState) return;

    ScriptEvent& MouseEvent = Events[4];
    MouseEvent.Update();

    if (MouseEvent.Enabled())
    {
        for (auto& EventHook : MouseEvent.Hooks)
        {
            if (EventHook.Enabled)
            {
                sol::protected_function_result Result = EventHook.Hook();
                if (!Result.valid())
                {
                    sol::error Error = Result;
                    std::string What(Error.what());
                    Logger::LogError("{} encountered an error! Message: {}", EventHook.HookName, What);
                }
            }
        }
    }
}

std::string ScriptManager::GetScriptNameFromPath(const std::string& FullPath) const
{
    if (!std::filesystem::path(FullPath).has_filename()) return {};
    return std::filesystem::path(FullPath).filename().string();
}

std::string ScriptManager::GetScriptFolderFromPath(const std::string& FullPath) const
{
    if (!std::filesystem::path(FullPath).has_parent_path()) return {};
    return std::filesystem::path(FullPath).parent_path().string() + "\\";
}

std::string ScriptManager::GetScriptExtensionFromPath(const std::string& FullPath) const
{
    if (!std::filesystem::path(FullPath).has_extension()) return {};
    return std::filesystem::path(FullPath).extension().string();
}

bool ScriptManager::IsValidScriptExtensionFromPath(const std::string& FullPath) const
{
    return IsValidScriptExtension(GetScriptExtensionFromPath(FullPath));
}

bool ScriptManager::IsValidScriptExtension(std::string Extension) const
{
    //Transform extension to lowercase only for easy comparison.
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
    return Extension == ".lua";
}

