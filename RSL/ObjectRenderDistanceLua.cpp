#include "ObjectRenderDistanceLua.h"
#include "Functions.h"

void Lua::BindObjectRenderDistance(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<ObjectRenderDistance>
    (
        "ObjectRenderDistance",
        "new", sol::no_constructor,
        "ApparentDistance", &ObjectRenderDistance::apparent_distance,
        "LastFrameProcessed", &ObjectRenderDistance::last_frame_processed
    );
}