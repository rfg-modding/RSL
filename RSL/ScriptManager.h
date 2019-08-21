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

class ScriptEventHook
{
public:
    ScriptEventHook(std::string _HookName, sol::function _Hook) : HookName(_HookName), Hook(_Hook) {}
    ScriptEventHook() = default;
    ~ScriptEventHook() = default;

    std::string HookName; //Todo: Figure out if this is really needed
    sol::function Hook;
    bool Enabled = true;
    bool DeleteOnNextUpdate = false;
};

class ScriptEvent
{
public:
    ScriptEvent(std::string _Name) : Name(Util::General::ToLower(_Name)) {}
    ScriptEvent() = default;
    ~ScriptEvent() = default;

    void Enable() { _Enabled = true; };
    void Disable() { _Enabled = false; }
    [[nodiscard]] bool Enabled() const { return _Enabled; }

    void MarkForReset() { _ResetOnNextUpdate = true; };
    [[nodiscard]] bool MarkedForReset() const { return _ResetOnNextUpdate; };
    void Reset()
    {
        Hooks.clear();
        _ResetOnNextUpdate = false;
    }
    void Update()
    {
        if (MarkedForReset())
        {
            Reset();
        }

        //Remove hooks that were marked for deletion. Can't delete immediately since it might not be thread safe. Do it this way for safety
        Hooks.erase(std::remove_if(Hooks.begin(), Hooks.end(),
            [](ScriptEventHook& Hook)
            {
                return Hook.DeleteOnNextUpdate;
            }),
            Hooks.end());
    }

    std::string Name;
    std::vector<ScriptEventHook> Hooks;

    bool ResetOnNextUpdate = false;

private:
    bool _Enabled = true;
    bool _ResetOnNextUpdate = false;
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
    [[nodiscard]] std::optional<uint> GetLineFromErrorString(const std::string& ErrorString) const;
    [[nodiscard]] bool CharIsDigit(const char& Character) const;

    void TriggerInputEvent(uint Message, uint KeyCode, KeyState& Keys);
    void TriggerDoFrameEvent();

	sol::state* LuaState = nullptr; //Uses a pointer for easy LuaState resets.
	std::vector <ScriptFolder> SubFolders; //List of scripts detected in SubFolders folder on the last scan.

    std::array<ScriptEvent, 2> Events = { {ScriptEvent("Keypress"), ScriptEvent("FrameUpdate")} };

    std::unordered_map<int, sol::function> MessageBoxCallbacks;

private:
    [[nodiscard]] std::string GetScriptNameFromPath(const std::string& FullPath) const;
    [[nodiscard]] std::string GetScriptFolderFromPath(const std::string& FullPath) const;
    [[nodiscard]] std::string GetScriptExtensionFromPath(const std::string& FullPath) const;
	[[nodiscard]] bool IsValidScriptExtensionFromPath(const std::string& FullPath) const;
    [[nodiscard]] bool IsValidScriptExtension(std::string Extension) const;

	void SetupLua();
    void RegisterEvent(std::string EventTypeName, sol::function EventFunction, std::string EventName = "GenericEvent");

    //std::vector<ScriptEvent> Events;

    std::recursive_mutex Mutex;
};