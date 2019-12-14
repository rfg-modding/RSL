#include "AttachInfoDataLua.h"
#include "Functions.h"

void Lua::BindAttachInfoData(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<AttachInfoData>();
	Utype.set("new", sol::constructors<AttachInfoData(), AttachInfoData(const AttachInfoData&)>());
	Utype.set("ParentHandle", &AttachInfoData::parent_handle);
	Utype.set("ParentPropPoint", &AttachInfoData::parent_prop_point);
	Utype.set("ChildPropPoint", &AttachInfoData::child_prop_point);
	Utype.set("RelativeTransform", &AttachInfoData::relative_transform);
	Utype.set("UseRelativeTransform", sol::property(itsy_bitsy::read<AttachInfoData, 60>, itsy_bitsy::write<AttachInfoData, 60>)); //uint32 - 1
	Utype.set("UpdatePhysics", sol::property(itsy_bitsy::read<AttachInfoData, 61>, itsy_bitsy::write<AttachInfoData, 61>)); //uint32 - 1 
	Utype.set("Updated", sol::property(itsy_bitsy::read<AttachInfoData, 62>, itsy_bitsy::write<AttachInfoData, 62>)); //uint32 - 1
	RfgTable.set_usertype("AttachInfoData", Utype);
#endif
}
