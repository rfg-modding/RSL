#pragma once
#include "BaseGui.h"
#include "IScriptManager.h"

//Todo: Add way to set visibility / title / size / etc in lua
//Todo: Add way to toggle if visibility is handled by F1 or is independently controlled
//Todo: Add way to mark gui for removal
//Todo: Bind this shit and BaseGui to lua, make lua function that makes a LuaGui and returns a ptr to it
//Class used for guis whose behavior are written in lua
class LuaGui : public BaseGui
{
public:
    LuaGui(std::string Title_, sol::function DrawFunc_);
    ~LuaGui() = default;

    void Draw() override;
    void SetDrawFunction(sol::function& NewDrawFunc);

    ImGuiWindowFlags Flags = 0;

private:
    sol::function DrawFunc = sol::nil;

    std::shared_ptr<IScriptManager> Scripts = nullptr;
    std::string FunctionName = "";

    bool BeingDrawn = false;
};

