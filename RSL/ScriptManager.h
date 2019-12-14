#pragma once
#include "ScriptFolder.h"
#include "IScriptManager.h"
#include "ScriptEvent.h"

/* This class manages the script loader lua state and scripting. This includes binding
 * rfg structures and functions to lua, and finding and running lua scripts. It contains
 * functions for detecting valid scripts in folders, and safely running scripts without 
 * worry of crashing the game (generally). See ScriptManager.cpp for more information
 * about individual member functions.
 */
class ScriptManager : public IScriptManager
{
public:
    ScriptManager() { }
    ~ScriptManager();

    void Reset() override;
	void Initialize() override;
	void UpdateRfgPointers() override;

	void ScanScriptsFolder() override;
    void RunStartupScripts() override;

    [[nodiscard]] bool RunScript(const std::string& FullPath) override;
    [[nodiscard]] bool RunScript(const size_t Index) override;

	ScriptResult RunStringAsScript(std::string Buffer, const std::string& Name) override;
    bool RunFunctionSafe(sol::function& Func, const std::string& Name, const sol::table& Args) override;
    [[nodiscard]] std::optional<uint> GetLineFromErrorString(const std::string& ErrorString) const override;

    //Todo: Consider moving these out of this class into the Lua namespace to keep things clean
    void TriggerInputEvent(uint Message, uint KeyCode, KeyState& Keys) override;
    void TriggerDoFrameEvent() override;
    void TriggerInitializedEvent() override;
    void TriggerMouseEvent(uint Message, uint wParam, uint lParam, KeyState& Keys) override;
    void TriggerLoadEvent() override;

    //void RegisterEvent(std::string EventTypeName, const sol::function& EventFunction) override;
    //void RegisterEvent(std::string EventTypeName, const sol::function& EventFunction, const std::string& EventName) override;

    void RegisterEvent(std::string EventTypeName, const sol::function& EventFunction) override;
    void RegisterEvent(std::string EventTypeName, const sol::function& EventFunction, const std::string& EventName) override;

    const std::vector<ScriptFolder>& GetSubFolders() override { return SubFolders; }

    [[nodiscard]] bool Ready() override { return _ready; }
    [[nodiscard]] sol::state_view GetLuaState() override { return sol::state_view(LuaState->lua_state()); }
    const std::array<ScriptEvent, 5>& GetEvents() override { return Events; }
    std::unordered_map<int, sol::function>& GetMessageBoxCallbacks() override
    {
        return MessageBoxCallbacks;
    };

	sol::state* LuaState = nullptr; //Uses a pointer for easy LuaState resets.
	std::vector<ScriptFolder> SubFolders; //List of scripts detected in SubFolders folder on the last scan.

    std::array<ScriptEvent, 5> Events = {
        {
            ScriptEvent("Keypress"), ScriptEvent("FrameUpdate"), ScriptEvent("Initialized"),
            ScriptEvent("Mouse"), ScriptEvent("Load")
        }};

    std::unordered_map<int, sol::function> MessageBoxCallbacks;

private:
    [[nodiscard]] std::string GetScriptNameFromPath(const std::string& FullPath) const;
    [[nodiscard]] std::string GetScriptFolderFromPath(const std::string& FullPath) const;
    [[nodiscard]] std::string GetScriptExtensionFromPath(const std::string& FullPath) const;
	[[nodiscard]] bool IsValidScriptExtensionFromPath(const std::string& FullPath) const;
    [[nodiscard]] bool IsValidScriptExtension(std::string Extension) const;
	void SetupLua();

    std::recursive_mutex Mutex;
    bool _ready = false;
};