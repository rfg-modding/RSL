#pragma once
#include "ScriptEventHook.h"

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
