#include "HumanRaycastHitInfoLua.h"
#include "Functions.h"

void Lua::BindHumanRaycastHitInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<HumanRaycastHitInfo>
    (
        "HumanRaycastHitInfo",
        "new", sol::no_constructor,
        "FirePosition", &HumanRaycastHitInfo::FirePosition,
        "TargetPosition", &HumanRaycastHitInfo::TargetPos,
        "HitPoint", &HumanRaycastHitInfo::HitPoint,
        "HitLocation", &HumanRaycastHitInfo::hit_location,
        "HitBone", &HumanRaycastHitInfo::hit_bone
    );
}
