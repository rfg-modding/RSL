#include "HavokBPOLua.h"
#include "Functions.h"

void Lua::BindHavokBPO(sol::state & LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<HavokBPO>();
	Utype.set("new", sol::constructors<HavokBPO(), HavokBPO(const HavokBPO&)>());
	Utype.set("Flags", sol::property([](HavokBPO& Self) -> int {return static_cast<int>(Self.flags); }, [](HavokBPO& Self, int Value) {Self.flags = static_cast<char>(Value); }));
	Utype.set("State", sol::property([](HavokBPO& Self) -> int {return static_cast<int>(Self.state); }, [](HavokBPO& Self, int Value) {Self.state = static_cast<char>(Value); }));
	Utype.set("BpoIndex", &HavokBPO::bpo_index);
	Utype.set("StateIndex", &HavokBPO::state_index);
	Utype.set("Owner", &HavokBPO::owner);
	Utype.set("Next", &HavokBPO::next);
	Utype.set("Prev", &HavokBPO::prev);
	//Utype.set("Userdata", &HavokBPO::user_data);
	RfgTable.set_usertype("HavokBPO", Utype);
#endif
}
