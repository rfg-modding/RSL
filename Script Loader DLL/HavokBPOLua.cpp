#include "HavokBPOLua.h"
#include "Functions.h"

void Lua::BindHavokBPO(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<HavokBPO>
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
	);
}
