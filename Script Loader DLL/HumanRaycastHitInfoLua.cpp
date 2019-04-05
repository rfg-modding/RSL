#include "HumanRaycastHitInfoLua.h"
#include "Functions.h"

void Lua::BindHumanRaycastHitInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<HumanRaycastHitInfo>();
	Utype.set("new", sol::no_constructor);
	Utype.set("FirePosition", &HumanRaycastHitInfo::FirePosition);
	Utype.set("TargetPosition", &HumanRaycastHitInfo::TargetPos);
	Utype.set("HitPoint", &HumanRaycastHitInfo::HitPoint);
	Utype.set("HitLocation", &HumanRaycastHitInfo::hit_location);
	Utype.set("HitBone", &HumanRaycastHitInfo::hit_bone);
	LuaState.set_usertype("HumanRaycastHitInfo", Utype);
}
