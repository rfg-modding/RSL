#include "ScriptManager.h"

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
	Lua["TestFunc"] = TestFunc;
	//Lua.set_function("TestFunc", TestFunc);
	//Lua["GetScriptLoaderVersion"] = GetScriptLoaderVersion;
	//Lua.set_function("HideHud", HideHud);
	//SetupLua();
}

void ScriptManager::SetupLua()
{
	//RunScript(GetEXEPath(false) + "RFGR Script Loader/Core/CoreInit.lua");

	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	//auto RslTable = Lua["rsl"].get_or_create<sol::table>();
	
	//auto RfgTable = Lua["rfg"].get_or_create<sol::table>();
	//Lua["GetScriptLoaderVersion"] = &GetScriptLoaderVersion;
	//Lua["HideHud"] = &HideHud;
	//RfgTable["HideFog"] = HideFog;

	/*auto LoggerTable = Lua["Logger"].get_or_create<sol::table>(); //Todo: Add to RSL table.
	LoggerTable["OpenLogFile"] = Logger::OpenLogFile;
	LoggerTable["CloseLogFile"] = Logger::CloseLogFile;
	LoggerTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles;
	LoggerTable["Log"] = Logger::Log;
	LoggerTable["LogFlagWithColor"] = Logger::LogFlagWithColor;
	LoggerTable["GetFlagString"] = Logger::GetFlagString;
	LoggerTable["LogToFile"] = Logger::LogToFile;
	LoggerTable["GetTimeString"] = Logger::GetTimeString;

	/*auto LogTypeTable = Lua["LogType"].get_or_create<sol::table>(); //Todo: Add to RSL table.
LogTypeTable["None"] = LogNone;
LogTypeTable["Info"] = LogInfo;
LogTypeTable["Warning"] = LogWarning;
LogTypeTable["Error"] = LogError;
LogTypeTable["FatalError"] = LogFatalError;
LogTypeTable["Lua"] = LogLua;
LogTypeTable["Json"] = LogJson;
LogTypeTable["All"] = LogAll;*/

	/*RfgTable.new_usertype<vector>
	(
		"vector",
		"new", sol::constructors< sol::types<float>, sol::types<float, float, float>>(),
		sol::meta_function::addition, &vector::operator+,
		sol::meta_function::subtraction, &vector::operator-,
		sol::meta_function::multiplication, &vector::operator*,
		sol::meta_function::equal_to, &vector::operator==,
		"Cross", &vector::Cross,
		"Magnitude", &vector::Magnitude,
		"x", &vector::x,
		"y", &vector::y,
		"z", &vector::z
	);*/
}

/*struct A {
	int a = 10;
	virtual int call() { return 0; }
};
struct B : A {
	int b = 11;
	virtual int call() override { return 20; }
};

int main (int, char*[]) {

	sol::state lua;

	lua.new_usertype<B>( "A",
		"call", &A::call
	);

	lua.new_usertype<B>( "B",
		"call", &B::call,
		sol::base_classes, sol::bases<A>()
	);

	return 0;
}*/


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

