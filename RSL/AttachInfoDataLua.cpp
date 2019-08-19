#include "AttachInfoDataLua.h"
#include "Functions.h"

void Lua::BindAttachInfoData(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<AttachInfoData> 
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
	);
}
