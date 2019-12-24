#include "GuiConstants.h"
#include "Functions.h"

void Lua::BindGuiConstants(sol::state& LuaStateRef)
{
#if LUA_ENABLED
    sol::table GuiTable = LuaStateRef["gui"].get_or_create<sol::table>();
    sol::table ColorsTable = GuiTable["colors"].get_or_create<sol::table>();
    sol::table FontsTable = GuiTable["fonts"].get_or_create<sol::table>();

    //Bind colors
    ColorsTable["Transparent"] = Globals::ColorTransparent;
    ColorsTable["Red"] = Globals::ColorRed;
    ColorsTable["Green"] = Globals::ColorGreen;
    ColorsTable["Blue"] = Globals::ColorBlue;
    ColorsTable["Black"] = Globals::ColorBlack;
    ColorsTable["White"] = Globals::ColorWhite;
    ColorsTable["Purple"] = Globals::ColorPurple;
    ColorsTable["Orange"] = Globals::ColorOrange;
    ColorsTable["Yellow"] = Globals::ColorYellow;
    ColorsTable["TextSecondary"] = Globals::SecondaryTextColor;
    ColorsTable["Blue2"] = Globals::ColorBlue2;

    //Bind fonts
    //Todo: Come up with a better way of handling font sizes. This is dumb
    FontsTable["Normal"] = Globals::FontNormal;
    FontsTable["Big"] = Globals::FontBig;
    FontsTable["Large"] = Globals::FontLarge;
    FontsTable["Huge"] = Globals::FontHuge;

    //Todo: Add support for FontAwesome fonts/icons

#endif
}
