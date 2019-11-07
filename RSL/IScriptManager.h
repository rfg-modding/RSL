#pragma once
#include <string>
#include <optional>

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

    virtual bool RunScript(const std::string& FullPath);
    virtual bool RunScript(const size_t Index);

    virtual ScriptResult RunStringAsScript(std::string Buffer, const std::string& Name);
    [[nodiscard]] virtual std::optional<uint> GetLineFromErrorString(const std::string& ErrorString) const = 0;

    //Todo: See if this can be done with a single function without using strings
    virtual void TriggerInputEvent(uint Message, uint KeyCode, KeyState& Keys) = 0;
    virtual void TriggerDoFrameEvent() = 0;
    virtual void TriggerInitializedEvent() = 0;
    virtual void TriggerMouseEvent(uint Message, uint wParam, uint lParam, KeyState& Keys) = 0;
    virtual void TriggerLoadEvent() = 0;

protected:
    IScriptManager() = default;
};