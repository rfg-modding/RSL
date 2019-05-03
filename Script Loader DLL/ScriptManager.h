#pragma once
#include "LuaFunctions.h"

/* Contains basic information about a script to avoid duplicate calculations.
 * This includes it's full path, folder path, and file name. Currently does 
 * not buffer the script itself. Scripts are only loaded at the moment that
 * they are run.
 */
class Script
{
public:
	Script() = default;;
	Script(std::string FullPath_, std::string FolderPath_, std::string Name_) : FullPath(FullPath_), FolderPath(FolderPath_), Name(Name_) { };
	~Script() = default;;

	std::string FullPath; //Full path with file name.
	std::string FolderPath; //Full path without file name.
	std::string Name; //Script file name.
};

/* This class manages the script loader lua state and scripting. This includes binding
 * rfg structures and functions to lua, and finding and running lua scripts. It contains
 * functions for detecting valid scripts in folders, and safely running scripts without 
 * worry of crashing the game (generally). See ScriptManager.cpp for more information
 * about individual member functions.
 */
class ScriptManager
{
public:
	ScriptManager() = default;
    ~ScriptManager();

    void Reset();
	void Initialize();
	void UpdateRfgPointers();

	void ScanScriptsFolder();

	bool RunScript(const std::string& FullPath);
	bool RunScript(size_t Index);

	bool RunStringAsScript(std::string Buffer, std::string Name);

	sol::state* LuaState = nullptr; //Uses a pointer for easy LuaState resets.
	std::vector <Script> Scripts; //List of scripts detected in Scripts folder on the last scan.

private:
	std::string GetScriptNameFromPath(std::string FullPath) const;
	std::string GetScriptFolderFromPath(std::string FullPath) const;
	std::string GetScriptExtensionFromPath(std::string FullPath) const;
	bool IsValidScriptExtensionFromPath(std::string FullPath);
	bool IsValidScriptExtension(std::string Extension) const;

	void SetupLua();
};