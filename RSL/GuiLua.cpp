#include "GuiLua.h"
#include "LuaGui.h"

void Lua::BindBaseGui(sol::state& LuaStateRef)
{
#if LUA_ENABLED
    auto GuiTable = LuaStateRef["gui"].get_or_create<sol::table>();
    auto Utype = GuiTable.create_simple_usertype<BaseGui>();

    Utype.set("new", sol::no_constructor);
    Utype.set("Show", &BaseGui::Show);
    Utype.set("Hide", &BaseGui::Hide);
    Utype.set("Toggle", &BaseGui::Toggle);
    Utype.set("IsVisible", &BaseGui::IsVisible);
    Utype.set("Delete", &BaseGui::Delete);
    Utype.set("MarkedForDeletion", &BaseGui::MarkedForDeletion);
    Utype.set("Title", &BaseGui::Title);
    Utype.set("Visible", &BaseGui::Visible);
    Utype.set("IndependentVisibility", &BaseGui::IndependentVisibility); //Todo: Make a shorter, better name for this
    GuiTable.set_usertype("BaseGui", Utype);
#endif
}

void Lua::BindLuaGui(sol::state& LuaStateRef)
{
#if LUA_ENABLED
    auto GuiTable = LuaStateRef["gui"].get_or_create<sol::table>();
    auto Utype = GuiTable.create_simple_usertype<LuaGui>();

    Utype.set("new", sol::no_constructor);
    Utype.set(sol::base_classes, sol::bases<BaseGui>());
    Utype.set("Flags", &LuaGui::Flags);
    Utype.set("SetDrawFunction", &LuaGui::SetDrawFunction);
    GuiTable.set_usertype("LuaGui", Utype);
#endif
}