#pragma once
//#include "Globals.h"
//#include <chaiscript/chaiscript.hpp>
//#include "Functions.h"
#include "CameraWrapper.h"
#include "FunctionManager.h"
#include "HookManager.h"
//#include "Hooks.h"

class Script
{
public:
	Script() { };
	Script(std::string _FullPath, std::string _FolderPath, std::string _Name) : FullPath(_FullPath), FolderPath(_FolderPath), Name(_Name) { };
	~Script() { };

	std::string FullPath; //Full path with name.
	std::string FolderPath; //Full path without name.
	std::string Name; //Script name.
};

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void Initialize();
	void RunTestScript();
	void RunTestScript2();

	void ScanScriptsFolder();
	void ScanScriptsSubFolders();

	bool RunScript(std::string FullPath);
	bool RunScript(size_t Index);

	bool RunStringAsScript(std::string Buffer, std::string Name);

	std::vector <Script> Scripts;

private:
	std::string GetScriptNameFromPath(std::string FullPath);
	std::string GetScriptFolderFromPath(std::string FullPath);
	std::string GetScriptExtensionFromPath(std::string FullPath);
	bool IsValidScriptExtensionFromPath(std::string FullPath);
	bool IsValidScriptExtension(std::string Extension);
};