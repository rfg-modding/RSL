#pragma once
#include <string>
#include <optional>
#include "Functions.h"
#include "ScriptFolder.h"
#include "ScriptEvent.h"
#include "ScriptResult.h"

using uint = unsigned int;
class ScriptResult;
class KeyState;

class IScriptManager
{
public:
    IScriptManager(const IScriptManager&) = delete;
    IScriptManager& operator=(const IScriptManager&) = delete;
    virtual ~IScriptManager() noexcept = default;

    virtual void Reset() = 0;
    virtual void Initialize() = 0;
    virtual void UpdateRfgPointers() = 0;

    virtual void ScanScriptsFolder() = 0;
    virtual void RunStartupScripts() = 0;

    virtual bool RunScript(const std::string& FullPath) = 0;
    virtual bool RunScript(const size_t Index) = 0;

    virtual ScriptResult RunStringAsScript(std::string Buffer, const std::string& Name) = 0;
    virtual bool RunFunctionSafe(sol::function& Func, const std::string& Name, const sol::table& Args = sol::nil) = 0;
    [[nodiscard]] virtual std::optional<uint> GetLineFromErrorString(const std::string& ErrorString) const = 0;

    //Todo: See if this can be done with a single function without using strings
    virtual void TriggerInputEvent(uint Message, uint KeyCode, KeyState& Keys) = 0;
    virtual void TriggerDoFrameEvent() = 0;
    virtual void TriggerInitializedEvent() = 0;
    virtual void TriggerMouseEvent(uint Message, uint wParam, uint lParam, KeyState& Keys) = 0;
    virtual void TriggerLoadEvent() = 0;

    virtual void RegisterEvent(std::string EventTypeName, const sol::function& EventFunction) = 0;
    virtual void RegisterEvent(std::string EventTypeName, const sol::function& EventFunction, const std::string& EventName) = 0;

    virtual const std::vector<ScriptFolder>& GetSubFolders() = 0;
    virtual std::unordered_map<int, sol::function>& GetMessageBoxCallbacks() = 0;

    [[nodiscard]] virtual bool Ready() = 0;
    [[nodiscard]] virtual sol::state_view GetLuaState() = 0;

    virtual const std::array<ScriptEvent, 5>& GetEvents() = 0;

protected:
    IScriptManager() = default;
};