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

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

const char* TestFunc()
{
	return "Test";
}

void ScriptManager::Initialize()
{
	//See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	//and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	//For now there is no Lua sand boxing in place to remove as many barriers for creativity that modders might have had otherwise.
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
	RunScript(GetEXEPath(false) + "RFGR Script Loader/Core/CoreInit.lua");

	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	auto RslTable = LuaState["rsl"].get_or_create<sol::table>();
	RslTable["GetScriptLoaderVersion"] = GetScriptLoaderVersion;

	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;
	RfgTable["SetFarClipDistance"] = game_render_set_far_clip_distance;

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
	
	//Use separate files for these so that if one is edited they don't all need to be recompiled.
	//Not necessarily at huge benefit at first, but it'll grow as more usertypes are added.
	Lua::BindTimestamp(LuaState);
	Lua::BindVector(LuaState);
	Lua::BindMatrix(LuaState);
	Lua::BindMatrix43(LuaState);
	Lua::BindAttachInfoData(LuaState);
	Lua::BindContactNode(LuaState);
	Lua::BindObjectContactInfo(LuaState);
	Lua::BindObjectFlags(LuaState);
	//Lua::BindRemoteObjectFlags(LuaState);
	Lua::BindHavokBPO(LuaState);
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
	Lua::BindObject(LuaState);
	Lua::BindHuman(LuaState);
	Lua::BindPlayer(LuaState);
}

void ScriptManager::ScanScriptsFolder()
{
	try 
	{
		Scripts.clear();
		std::string ScriptFolderPath(GetEXEPath(false) + "RFGR Script Loader/Scripts/");

		std::string ThisScriptPath;
		std::string ThisScriptFolderPath;
		std::string ThisScriptName;

		for (auto& i : fs::directory_iterator(ScriptFolderPath))
		{
			if (IsValidScriptExtensionFromPath(i.path().string()))
			{
				ThisScriptPath = i.path().string();
				ThisScriptFolderPath = GetScriptFolderFromPath(i.path().string());
				ThisScriptName = GetScriptNameFromPath(i.path().string());
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
		//strcpy(Ex.what, ExceptionInfo.c_str());
		//throw(Ex);
	}
}

void ScriptManager::ScanScriptsSubFolders()
{

}

bool ScriptManager::RunScript(std::string FullPath)
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
			Logger::Log(std::string("Exception caught when running " + GetScriptNameFromPath(FullPath) + std::string(Exception.what())), LogLua | LogError);
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ScriptManager::RunScript(size_t Index)
{
	std::string FullPath = Scripts[Index].FullPath;
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

std::string ScriptManager::GetScriptNameFromPath(std::string FullPath)
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

std::string ScriptManager::GetScriptFolderFromPath(std::string FullPath)
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

std::string ScriptManager::GetScriptExtensionFromPath(std::string FullPath)
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

bool ScriptManager::IsValidScriptExtension(std::string Extension)
{
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
	if (Extension == "lua")
	{
		return true;
	}
	return false;
}

