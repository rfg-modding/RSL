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
	Lua["HideHUD"] = HideHUD;
	Lua["HideFog"] = HideFog;

	std::string ExePath = GetEXEPath(false);
	fs::remove(ExePath + "RFGR Script Loader/Logs/Script Log.txt");
}

void ScriptManager::RunTestScript()
{
	std::string Script;
	std::string ExePath = GetEXEPath(false);

	std::cout << "Trying Test.lua" << std::endl;
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
			std::cout << "Test.lua not valid. Throwing exception." << std::endl;
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
	}
	catch (std::exception& Exception)
	{
		std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Script Log.txt");
		LogFile << "Exception caught when running Test.lua: " << Exception.what() << std::endl;
		//std::cout << "Exception caught when running Test.lua: " << Exception.what() << std::endl;
		ConsoleLog(std::string("Exception caught when running Test.lua: " +  std::string(Exception.what())).c_str(), LOGERROR, false, true, true);
		LogFile.close();
	}
	catch (...)
	{
		std::cout << "General exception..." << std::endl;
	}
	/*catch (sol::protected_function_result& pfrExcept)
	{
		std::cout << "pfr exception: " << pfrExcept.what() << std::endl;
	}*/


	//std::cout << "Script Path: " << ExePath + "RFGR Script Loader/Scripts/Test.script" << std::endl;

	//std::ifstream ScriptFile(ExePath + "RFGR Script Loader/Scripts/Test.script");
	//Script.assign((std::istreambuf_iterator<char>(ScriptFile)), (std::istreambuf_iterator<char>()));
	//ScriptFile.close();
	
	//std::cout << "Test.script: " << Script << std::endl << std::endl;
	
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
		std::ofstream LogFile(ExePath + "RFGR Script Loader/Logs/Script Log.txt");
		LogFile << "Exception caught when running Test2.lua: " << Exception.what() << std::endl;
		ConsoleLog(std::string("Exception caught when running Test2.lua: ", Exception.what()).c_str(), LOGERROR, false, true, true);
	}
}
