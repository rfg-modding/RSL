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
    if(NewDrawFunc != sol::nil)
    {
        DrawFunc = NewDrawFunc;
        NewDrawFunc = sol::nil;
    }

    if(DrawFunc == sol::nil)
        return;

    if(ImGui::Begin(Title, &Visible, Flags))
    {
        const sol::table GuiData = Scripts->GetLuaState().create_table();
        Scripts->RunFunctionSafe(DrawFunc, FunctionName, GuiData);
    }
    ImGui::End();
}

void LuaGui::SetDrawFunction(sol::function& NewDrawFunc_)
{
    //Set NewDrawFunc. DrawFunc will be set to this on the next Draw() call.
    //Done this way to avoid changing the function mid draw and having errors.
    NewDrawFunc = NewDrawFunc_;
}
