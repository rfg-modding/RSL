#include "HavokBPOLua.h"
#include "Functions.h"

void Lua::BindHavokBPO(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<HavokBPO>
    (
        "HavokBPO",
        "new", sol::constructors<HavokBPO(), HavokBPO(const HavokBPO&)>(),
        "Flags", sol::property([](HavokBPO& Self) -> int {return static_cast<int>(Self.flags); }, [](HavokBPO& Self, int Value) {Self.flags = static_cast<char>(Value); }),
        "State", sol::property([](HavokBPO& Self) -> int {return static_cast<int>(Self.state); }, [](HavokBPO& Self, int Value) {Self.state = static_cast<char>(Value); }),
        "BpoIndex", &HavokBPO::bpo_index,
        "StateIndex", &HavokBPO::state_index,
        "Owner", &HavokBPO::owner,
        "Next", &HavokBPO::next,
        "Prev", &HavokBPO::prev//,
        //"Userdata", &HavokBPO::user_data
    );
}
