#pragma once
#include "LuaFunctions.h"

class Script
{
public:
	Script() = default;;
	Script(std::string FullPath_, std::string FolderPath_, std::string Name_) : FullPath(FullPath_), FolderPath(FolderPath_), Name(Name_) { };
	~Script() = default;;

	std::string FullPath; //Full path with name.
	std::string FolderPath; //Full path without name.
	std::string Name; //Script name.
};

class ScriptManager
{
public:
	ScriptManager() = default;
    ~ScriptManager();

	void Initialize();
	void UpdateRfgPointers();
    void Reset();

	void ScanScriptsFolder();

	bool RunScript(const std::string& FullPath);
	bool RunScript(size_t Index);

	bool RunStringAsScript(std::string Buffer, std::string Name);

	sol::state* LuaState = nullptr; //Use a pointer for easy LuaState resets.
	std::vector <Script> Scripts;

private:
	std::string GetScriptNameFromPath(std::string FullPath) const;
	std::string GetScriptFolderFromPath(std::string FullPath) const;
	std::string GetScriptExtensionFromPath(std::string FullPath) const;
	bool IsValidScriptExtensionFromPath(std::string FullPath);
	bool IsValidScriptExtension(std::string Extension) const;

	void SetupLua();
};