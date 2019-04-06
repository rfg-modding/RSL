#include "PlayerLua.h"
#include "Functions.h"

void Lua::BindPlayer(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Player>();
	Utype.set(sol::base_classes, sol::bases<Human, Object>());

	LuaState.set_usertype("Player", Utype);
}