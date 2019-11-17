#include "LuaGui.h"

LuaGui::LuaGui(std::string Title_, sol::function DrawFunc_)
{
    Title = Title_;
    DrawFunc = DrawFunc_;
    Scripts = IocContainer->resolve<IScriptManager>();
    FunctionName = fmt::format("LuaGui(Title: {})", Title);
}

void LuaGui::Draw()
{
    if(DrawFunc == sol::nil)
        return;

    BeingDrawn = true;
    if(ImGui::Begin(Title, &Visible, Flags))
    {
        const sol::table GuiData = Scripts->GetLuaState().create_table();
        Scripts->RunFunctionSafe(DrawFunc, FunctionName, GuiData);
    }
    ImGui::End();
    BeingDrawn = false;
}

void LuaGui::SetDrawFunction(sol::function& NewDrawFunc)
{
    if (!BeingDrawn)
        DrawFunc = NewDrawFunc;
}
