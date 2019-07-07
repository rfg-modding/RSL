#pragma once
#include "LuaFunctions.h"

class ScriptResult
{
public:
    ScriptResult(bool Failed_, std::optional<uint> ErrorLineNumber_, std::string ErrorString_)
    : Failed(Failed_), ErrorLineNumber(ErrorLineNumber_), ErrorString(ErrorString_){}
    ~ScriptResult() = default;

    bool Failed = false;
    std::optional<uint> ErrorLineNumber = 0;
    std::string ErrorString = {};
};

/* Contains basic information about a script to avoid duplicate calculations.
 * This includes it's full path, folder path, and file name. Currently does 
 * not buffer the script itself. Scripts are only loaded at the moment that
 * they are run.
 */
class Script
{
public:
	Script() = default;;
	Script(std::string FullPath_, std::string FolderPath_, std::string Name_) : FullPath(FullPath_), FolderPath(FolderPath_), Name(Name_) { }
	~Script() = default;;

	std::string FullPath; //Full path with file name.
	std::string FolderPath; //Full path without file name.
	std::string Name; //Script file name.
};

class ScriptFolder
{
public:
    ScriptFolder() = default;
    ScriptFolder(std::string FullPath_, std::string Name_) : FullPath(FullPath_), Name(Name_) { }

    std::string FullPath;
    std::string Name;
    std::vector<Script> Scripts;
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
    void RunStartupScripts();

	bool RunScript(const std::string& FullPath);
	bool RunScript(const size_t Index);

	ScriptResult RunStringAsScript(std::string Buffer, std::string Name);
    std::optional<uint> GetLineFromErrorString(const std::string& ErrorString) const;
    [[nodiscard]] bool CharIsDigit(const char& Character) const;

	sol::state* LuaState = nullptr; //Uses a pointer for easy LuaState resets.
	std::vector <ScriptFolder> SubFolders; //List of scripts detected in SubFolders folder on the last scan.

private:
    [[nodiscard]] std::string GetScriptNameFromPath(std::string FullPath) const;
    [[nodiscard]] std::string GetScriptFolderFromPath(const std::string& FullPath) const;
    [[nodiscard]] std::string GetScriptExtensionFromPath(const std::string& FullPath) const;
	[[nodiscard]] bool IsValidScriptExtensionFromPath(std::string FullPath) const;
    [[nodiscard]] bool IsValidScriptExtension(std::string Extension) const;

	void SetupLua();
};