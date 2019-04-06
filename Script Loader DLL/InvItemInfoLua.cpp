#include "InvItemInfoLua.h"
#include "Functions.h"

void Lua::BindInventoryItem(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<InventoryItem>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Next", &InventoryItem::next);
	Utype.set("Prev", &InventoryItem::prev);
	Utype.set("Info", &InventoryItem::info);
	Utype.set("Count", &InventoryItem::count);
	Utype.set("SelectionSlot", &InventoryItem::selection_slot);
	Utype.set("AttachmentProp", &InventoryItem::attachment_prop);
	Utype.set("WeaponHandle", &InventoryItem::weapon_handle);
	LuaState.set_usertype("InventoryItem", Utype);
}

void Lua::BindChecksumStri(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<checksum_stri>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Checksum", &checksum_stri::checksum);
	LuaState.set_usertype("ChecksumStri", Utype);
}

void Lua::BindInvItemInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<inv_item_info>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Name", &inv_item_info::name);
	Utype.set("NameChecksum", &inv_item_info::name_checksum);
	Utype.set("DisplayName", &inv_item_info::display_name);
	Utype.set("Cost", &inv_item_info::cost);
	Utype.set("DefaultCount", &inv_item_info::default_count);
	Utype.set("MaxItem", &inv_item_info::max_item);
	Utype.set("Description", &inv_item_info::description);
	//Utype.set("WeaponInfo", &inv_item_info::w_info);
	Utype.set("ItemOrder", &inv_item_info::item_order);
	//Utype.set("UseFunc", &inv_item_info::use);
	LuaState.set_usertype("InvItemInfo", Utype);
}
