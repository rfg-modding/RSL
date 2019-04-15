#include "ObjectRenderDistanceLua.h"
#include "Functions.h"

void Lua::BindObjectRenderDistance(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<ObjectRenderDistance>();
	Utype.set("new", sol::no_constructor);
	Utype.set("ApparentDistance", &ObjectRenderDistance::apparent_distance);
	Utype.set("LastFrameProcessed", &ObjectRenderDistance::last_frame_processed);
	RfgTable.set_usertype("ObjectRenderDistance", Utype);
}