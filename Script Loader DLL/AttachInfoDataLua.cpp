#include "AttachInfoDataLua.h"
#include "Functions.h"

void Lua::BindAttachInfoData(sol::state& LuaState)
{
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

	/*RfgTable.new_usertype<AttachInfoData> //Note: I have no idea if the last 3 vars are correct yet. Bit fields are odd with sol2.
	(
		"AttachInfoData",
		"new", sol::constructors<AttachInfoData(), AttachInfoData(const AttachInfoData&)>(),
		"ParentHandle", &AttachInfoData::parent_handle,
		"ParentPropPoint", &AttachInfoData::parent_prop_point,
		"ChildPropPoint", &AttachInfoData::child_prop_point,
		"RelativeTransform", &AttachInfoData::relative_transform,
		"UseRelativeTransform", sol::property(itsy_bitsy::read<AttachInfoData, 60>, itsy_bitsy::write<AttachInfoData, 60>), //uint32 - 1
		"UpdatePhysics", sol::property(itsy_bitsy::read<AttachInfoData, 61>, itsy_bitsy::write<AttachInfoData, 61>),//uint32 - 1 
		"Updated", sol::property(itsy_bitsy::read<AttachInfoData, 62>, itsy_bitsy::write<AttachInfoData, 62>) //uint32 - 1
	);*/
}
