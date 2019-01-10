#include "ScriptManager.h"

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

void ScriptManager::Initialize()
{
	ChaiScriptVM.add(chaiscript::fun(&HideHUD), "HideHUD");
	ChaiScriptVM.add(chaiscript::fun(&HideFog), "HideFog");

	Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::jit);
	Lua["HideHUD"] = HideHUD;
	Lua["HideFog"] = HideFog;
	//Lua["Print"] = printf;
}

void ScriptManager::RunTestScript()
{
	std::string Script;
	std::string ExePath = GetEXEPath(false);

	//std::cout << "Script Path: " << ExePath + "RFGR Script Loader/Scripts/Test.script" << std::endl;

	//std::ifstream ScriptFile(ExePath + "RFGR Script Loader/Scripts/Test.script");
	//Script.assign((std::istreambuf_iterator<char>(ScriptFile)), (std::istreambuf_iterator<char>()));
	//ScriptFile.close();

	//std::cout << "Test.script: " << Script << std::endl << std::endl;

	///ChaiScriptVM.eval(Script);

	//std::ifstream LuaTestScript(ExePath + "RFGR Script Loader/Scripts/Test.lua");
	//Lua.do_file(std::string(ExePath + "RFGR Script Loader/Scripts/Test.lua"), sol::load_mode::text);
	Lua.script_file(ExePath + "RFGR Script Loader/Scripts/Test.lua", sol::load_mode::text);
}

/*int main() {
	chaiscript::ChaiScript chai;
	chai.add(chaiscript::fun(&helloWorld), "helloWorld");

	chai.eval(R"(
    puts(helloWorld("Bob"));
  )");
}*/
