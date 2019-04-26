#include "ScriptManager.h"
#include "BaseTypeLua.h"
#include "VectorLua.h"
#include "MatrixLua.h"
#include "Matrix43Lua.h"
#include "AttachInfoDataLua.h"
#include "ContactNodeLua.h"
#include "ObjectContactInfoLua.h"
#include "ObjectFlagsLua.h"
#include "HavokBPOLua.h"
#include "HkpRigidBodyLua.h"
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

void ScriptManager::Initialize()
{
	//See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	//and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	//For now there is no Lua sandboxing in place to remove as many barriers for creativity that modders might have had otherwise.
	LuaState.open_libraries
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
	//RunMainLua();
}

void ScriptManager::SetupLua()
{
	RunScript(Globals::GetEXEPath(false) + "RFGR Script Loader/Core/CoreInit.lua");

	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	auto RslTable = LuaState["rsl"].get_or_create<sol::table>();
	RslTable["GetScriptLoaderVersion"] = Globals::GetScriptLoaderVersion;
	RslTable["LogModuleBase"] = Lua::LogModuleBase;

	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;
	RfgTable["ToggleFog"] = ToggleFog;
	RfgTable["ToggleHud"] = ToggleHud;
	RfgTable["SetFarClip"] = game_render_set_far_clip_distance;
	RfgTable["GetFarClip"] = game_render_get_far_clip_distance;
	RfgTable["SetAlertLevel"] = gsm_set_alert_level;
	RfgTable["GetAlertLevel"] = gsm_get_alert_level;
	RfgTable["TeleportHuman"] = HumanTeleportUnsafe;
	RfgTable["GetPlayer"] = Lua::GetPlayer;
	RfgTable["GetWorld"] = Lua::GetWorld;
	RfgTable["GetPhysicsWorld"] = Lua::GetPhysicsWorld;

	RfgTable["ActivePlayer"] = Globals::PlayerPtr;
	RfgTable["ActiveWorld"] = Globals::RfgWorldPtr;
	RfgTable["ActivePhysicsWorld"] = Globals::hkpWorldPtr;
	
	RfgTable["HavokBodyGetPointer"] = HavokBodyGetPointer;
	RfgTable.set_function("ApplyLinearImpulse", sol::overload(HavokBodyApplyLinearImpulseA, HavokBodyApplyLinearImpulseB));

	RfgTable.set_function("TeleportPlayer", sol::overload(
 [](vector Position, matrix Orientation) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Orientation); }, 
		[](vector Position) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Globals::PlayerPtr->Orientation); }));

	//LogType enums defined in lua
	auto LoggerTable = LuaState["Logger"].get_or_create<sol::table>(); //Todo: Add to RSL table.
	LoggerTable["OpenLogFile"] = Logger::OpenLogFile;
	LoggerTable["CloseLogFile"] = Logger::CloseLogFile;
	LoggerTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles;
	LoggerTable["Log"] = Logger::Log;
	LoggerTable["LogFlagWithColor"] = Logger::LogFlagWithColor;
	LoggerTable["GetFlagString"] = Logger::GetFlagString;
	LoggerTable["LogToFile"] = Logger::LogToFile;
	LoggerTable["GetTimeString"] = Logger::GetTimeString;

	//This warning appears hundreds of times in a row during binding unless disabled. Is harmless due to some lambdas used to grab usertype variables.
	#pragma warning(push)
	#pragma warning(disable : 4172)
	//Use separate files for these so that if one is edited they don't all need to be recompiled.
	//Not necessarily at huge benefit at first, but it'll grow as more usertypes are added.
	Lua::BindRfgBaseArray(LuaState);
	Lua::BindRfgFArray(LuaState);
	Lua::BindTimestamp(LuaState);
	Lua::BindTimestampPercent(LuaState);
	Lua::BindTimestampRealtime(LuaState);
	Lua::BindColor(LuaState);
	Lua::BindVector(LuaState);
	Lua::BindMatrix(LuaState);
	Lua::BindMatrix43(LuaState);
	Lua::BindAttachInfoData(LuaState);
	Lua::BindContactNode(LuaState);
	Lua::BindObjectContactInfo(LuaState);
	Lua::BindObjectFlags(LuaState);
	//Lua::BindRemoteObjectFlags(LuaState);
	Lua::BindHavokBPO(LuaState);
	Lua::BindHkpMaterial(LuaState);
	Lua::BindHkpEntity(LuaState);
	Lua::BindHkpRigidBody(LuaState);
	Lua::BindHumanFlags(LuaState); //Todo: Fix compile error
	//Lua::BindHumanMPFlags(LuaState); //Todo: Fix compile error
	Lua::BindHumanInfoFlags(LuaState);
	Lua::BindHumanPropGeneralInfo(LuaState);
	Lua::BindInventoryItem(LuaState);
	Lua::BindChecksumStri(LuaState);
	Lua::BindInvItemInfo(LuaState);
	Lua::BindFootGroundEffects(LuaState);
	Lua::BindCharDefHead(LuaState);
	Lua::BindObjectRenderDistance(LuaState);
	Lua::BindHumanRaycastHitInfo(LuaState);
	Lua::BindCharacterInstance(LuaState);
	Lua::BindWeaponAnimationFlags(LuaState);
	Lua::BindIKJoint(LuaState);
	Lua::BindNanoCallbackInfo(LuaState);
	Lua::BindHumanInfo(LuaState);
	Lua::BindUsableObject(LuaState);
	Lua::BindPlayerFlags(LuaState);
	Lua::BindScriptSpecificData(LuaState);
	Lua::BindVehicleEnterStruct(LuaState);
	Lua::BindPathfindNavInfo(LuaState);
	Lua::BindUpgradeItem(LuaState);
	Lua::BindPlayerMetadata(LuaState);
	Lua::BindObject(LuaState);
	Lua::BindHuman(LuaState);
	Lua::BindPlayer(LuaState);
	//Setting these manually to ensure there's no accidently overwrites
	LuaState["rfg"]["Object"]["AsObject"] = [](Object& Self)->Object* {return &Self; };
	LuaState["rfg"]["Human"]["AsObject"] = [](Human& Self)->Object* {return static_cast<Object*>(&Self); };
	LuaState["rfg"]["Human"]["AsHuman"] = [](Human& Self)->Human* {return static_cast<Human*>(&Self); };
	LuaState["rfg"]["Player"]["AsObject"] = [](Player& Self)->Object* {return static_cast<Object*>(&Self); };
	LuaState["rfg"]["Player"]["AsHuman"] = [](Player& Self)->Human* {return static_cast<Human*>(&Self); };
	LuaState["rfg"]["Player"]["AsPlayer"] = [](Player& Self)->Player* {return &Self; };

	//World & dependent types
	Lua::BindStreamGridCell(LuaState);
	Lua::BindStreamLayerMaskedCell(LuaState);
	Lua::BindStreamLayer(LuaState);
	Lua::BindDistrictFlags(LuaState);
	Lua::BindTDistrict(LuaState);
	Lua::BindTerritory(LuaState);
	Lua::BindStreamGrid(LuaState);
	Lua::BindGameSaveInfoNewData(LuaState);
	Lua::BindGameSaveInfo(LuaState);
	Lua::BindSaveLoadInfo(LuaState);
	Lua::BindWorldStateBuf(LuaState);
	Lua::BindZoneHeader(LuaState);
	Lua::BindWorldZone(LuaState);
	Lua::BindWorld(LuaState);
	#pragma warning(pop) 
}

void ScriptManager::UpdateRfgPointers()
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	RfgTable["ActivePlayer"] = Globals::PlayerPtr;
	RfgTable["ActiveWorld"] = Globals::RfgWorldPtr;
	RfgTable["ActivePhysicsWorld"] = Globals::hkpWorldPtr;
}

void ScriptManager::ScanScriptsFolder()
{
	try 
	{
		Scripts.clear();
		const std::string ScriptFolderPath(Globals::GetEXEPath(false) + "RFGR Script Loader/Scripts/");
		for (auto& i : fs::directory_iterator(ScriptFolderPath))
		{
			if (IsValidScriptExtensionFromPath(i.path().string()))
			{
				const std::string ThisScriptPath = i.path().string();
				const std::string ThisScriptFolderPath = GetScriptFolderFromPath(i.path().string());
				const std::string ThisScriptName = GetScriptNameFromPath(i.path().string());
				Scripts.push_back(Script(ThisScriptPath, ThisScriptFolderPath, ThisScriptName));

				//Logger::Log(i.path().string(), LogInfo);
				//Logger::Log("Script Name: " + ThisScriptName, LogInfo);
				//Logger::Log("Script Folder: " + ThisScriptFolderPath, LogInfo);
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
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogFatalError, true, true);
	}
}

bool ScriptManager::RunScript(const std::string& FullPath)
{
	if (IsValidScriptExtensionFromPath(FullPath))
	{
		try
		{
			auto CodeResult = LuaState.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
			{
				return pfr;
			}, sol::load_mode::text);

			if (!CodeResult.valid())
			{
				sol::error ScriptError = CodeResult;
				std::exception ScriptException(ScriptError.what());
				throw(ScriptException);
			}
			return true;
		}
		catch (std::exception& Exception)
		{
			Logger::Log(std::string("Exception caught when running " + GetScriptNameFromPath(FullPath) + ": " + std::string(Exception.what())), LogLua | LogError);
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ScriptManager::RunScript(const size_t Index)
{
	const std::string& FullPath = Scripts[Index].FullPath;
	try
	{
		auto CodeResult = LuaState.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		}, sol::load_mode::text);

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Scripts[Index].Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

bool ScriptManager::RunStringAsScript(std::string Buffer, std::string Name)
{
	try
	{
		auto CodeResult = LuaState.script(Buffer, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		});

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

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

std::string ScriptManager::GetScriptFolderFromPath(std::string FullPath) const
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

std::string ScriptManager::GetScriptExtensionFromPath(std::string FullPath) const
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

bool ScriptManager::IsValidScriptExtensionFromPath(std::string FullPath)
{
	if (IsValidScriptExtension(GetScriptExtensionFromPath(FullPath)))
	{
		return true;
	}
	return false;
}

bool ScriptManager::IsValidScriptExtension(std::string Extension) const
{
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
	if (Extension == "lua")
	{
		return true;
	}
	return false;
}

