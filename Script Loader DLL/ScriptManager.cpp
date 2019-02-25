#include "ScriptManager.h"

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

void ScriptManager::Initialize()
{
	//See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	//and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	//Excluded the ffi lib for now. Current goal is to sandbox lua for user
	//safety. Might change this later on.
	Lua.open_libraries
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

void ScriptManager::SetupLua()
{
	//If necessary can make variables read-only: sol::readonly(&some_class::variable)
	auto RslTable = Lua["rsl"].get_or_create<sol::table>();
	
	auto RfgTable = Lua["rfg"].get_or_create<sol::table>();
	RfgTable["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;

	auto LogTypeTable = Lua["LogType"].get_or_create<sol::table>(); //Todo: Add to RSL table.
	LogTypeTable["None"] = LogNone;
	LogTypeTable["Info"] = LogInfo;
	LogTypeTable["Warning"] = LogWarning;
	LogTypeTable["Error"] = LogError;
	LogTypeTable["FatalError"] = LogFatalError;
	LogTypeTable["Lua"] = LogLua;
	LogTypeTable["Json"] = LogJson;
	LogTypeTable["All"] = LogAll;

	auto LoggerTable = Lua["Logger"].get_or_create<sol::table>(); //Todo: Add to RSL table
	LoggerTable["OpenLogFile"] = Logger::OpenLogFile;
	LoggerTable["CloseLogFile"] = Logger::CloseLogFile;
	LoggerTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles;
	LoggerTable["Log"] = Logger::Log;
	LoggerTable["LogFlagWithColor"] = Logger::LogFlagWithColor;
	LoggerTable["GetFlagString"] = Logger::GetFlagString;
	LoggerTable["LogToFile"] = Logger::LogToFile;
	LoggerTable["GetTimeString"] = Logger::GetTimeString;
}

void ScriptManager::RunTestScript()
{
	std::string Script;
	std::string ExePath = GetEXEPath(false);

	std::cout << "Trying Test.lua\n";
	try 
	{
		auto CodeResult = Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test.lua", [](lua_State*, sol::protected_function_result pfr) 
		{
			return pfr;
		}, sol::load_mode::text);

		if (!CodeResult.valid())
		{
			std::cout << "Test.lua not valid. Throwing exception.\n";
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
	}
	catch (std::exception& Exception)
	{
		std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Script Log.txt");
		LogFile << "Exception caught when running Test.lua: " << Exception.what() << "\n";
		Logger::Log(std::string("Exception caught when running Test.lua: " +  std::string(Exception.what())), LogError);
		LogFile.close();
	}
	catch (...)
	{
		std::cout << "General exception...\n";
	}
}

void ScriptManager::RunTestScript2()
{
	std::string Script;
	std::string ExePath = GetEXEPath(false);

	try
	{
		auto CodeResult = Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test2.lua", [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		}, sol::load_mode::text);

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running Test2.lua: " + std::string(Exception.what())), LogLua | LogError);
	}
}

void ScriptManager::ScanScriptsFolder()
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

void ScriptManager::ScanScriptsSubFolders()
{

}

bool ScriptManager::RunScript(std::string FullPath)
{
	if (IsValidScriptExtensionFromPath(FullPath))
	{
		try
		{
			auto CodeResult = Lua.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
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
		auto CodeResult = Lua.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
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
		auto CodeResult = Lua.script(Buffer, [](lua_State*, sol::protected_function_result pfr)
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

