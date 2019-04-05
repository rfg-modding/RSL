#include "HavokBPOLua.h"
#include "Functions.h"

void Lua::BindHavokBPO(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<HavokBPO>();
	Utype.set("new", sol::constructors<HavokBPO(), HavokBPO(const HavokBPO&)>());
	Utype.set("Flags", &HavokBPO::flags);
	Utype.set("State", &HavokBPO::state);
	Utype.set("BpoIndex", &HavokBPO::bpo_index);
	Utype.set("StateIndex", &HavokBPO::state_index);
	Utype.set("Owner", &HavokBPO::owner);
	Utype.set("Next", &HavokBPO::next);
	Utype.set("Prev", &HavokBPO::prev);
	//Utype.set("Userdata", &HavokBPO::user_data);
	LuaState.set_usertype("HavokBPO", Utype);

	/*RfgTable.new_usertype<HavokBPO>
	(
		"HavokBPO",
		"new", sol::constructors<HavokBPO(), HavokBPO(const HavokBPO&)>(),
		"Flags", &HavokBPO::flags,
		"State", &HavokBPO::state,
		"BpoIndex", &HavokBPO::bpo_index,
		"StateIndex", &HavokBPO::state_index,
		"Owner", &HavokBPO::owner,
		"Next", &HavokBPO::next,
		"Prev", &HavokBPO::prev
		//"Userdata", &HavokBPO::user_data
	);*/
}
