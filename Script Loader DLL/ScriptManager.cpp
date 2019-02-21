#include "ScriptManager.h"

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

void ScriptManager::Initialize()
{
	Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::jit);
	Lua["HideHud"] = HideHud;
	Lua["HideFog"] = HideFog;

	std::string ExePath = GetEXEPath(false);
	fs::remove(ExePath + "RFGR Script Loader/Logs/Script Log.txt");
}

void ScriptManager::RunTestScript()
{
	std::string Script;
	std::string ExePath = GetEXEPath(false);

	std::cout << "Trying Test.lua\n";
	try 
	{
		auto CodeResult = Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test.lua", [](lua_State*, sol::protected_function_result pfr) {
			// pfr will contain things that went wrong, for either loading or executing the script
			// Can throw your own custom error
			// You can also just return it, and let the call-site handle the error if necessary.
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
		//std::cout << "Exception caught when running Test.lua: " << Exception.what() << "\n";
		Logger::Log(std::string("Exception caught when running Test.lua: " +  std::string(Exception.what())), LogError);
		LogFile.close();
	}
	catch (...)
	{
		std::cout << "General exception...\n";
	}
	/*catch (sol::protected_function_result& pfrExcept)
	{
		std::cout << "pfr exception: " << pfrExcept.what() << "\n";
	}*/


	//std::cout << "Script Path: " << ExePath + "RFGR Script Loader/Scripts/Test.script\n";

	//std::ifstream ScriptFile(ExePath + "RFGR Script Loader/Scripts/Test.script");
	//Script.assign((std::istreambuf_iterator<char>(ScriptFile)), (std::istreambuf_iterator<char>()));
	//ScriptFile.close();
	
	//std::cout << "Test.script: " << Script << "\n\n";
	
	///ChaiScriptVM.eval(Script);
	
	//std::ifstream LuaTestScript(ExePath + "RFGR Script Loader/Scripts/Test.lua");
	//Lua.do_file(std::string(ExePath + "RFGR Script Loader/Scripts/Test.lua"), sol::load_mode::text);
	
	//Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test.lua", sol::load_mode::text);
}

void ScriptManager::RunTestScript2()
{
	std::string Script;
	std::string ExePath = GetEXEPath(false);

	try
	{
		auto CodeResult = Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test2.lua", [](lua_State*, sol::protected_function_result pfr) {
			// pfr will contain things that went wrong, for either loading or executing the script
			// Can throw your own custom error
			// You can also just return it, and let the call-site handle the error if necessary.
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
		//std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Script Log.txt");
		//LogFile << "Exception caught when running Test2.lua: " << Exception.what() << "\n";
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

			Logger::Log(i.path().string(), LogInfo);
			Logger::Log("Script Name: " + ThisScriptName, LogInfo);
			Logger::Log("Script Folder: " + ThisScriptFolderPath, LogInfo);
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
			//Logger::Log("Script extension: " + FullPath.substr(i + 1, FullPath.length() - i), LogInfo);
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

