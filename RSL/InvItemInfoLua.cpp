#include "InvItemInfoLua.h"
#include "Functions.h"

void Lua::BindInventoryItem(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<InventoryItem>
    (
        "InventoryItem",
        "new", sol::no_constructor,
        "Next", &InventoryItem::next,
        "Prev", &InventoryItem::prev,
        "Info", &InventoryItem::info,
        "Count", &InventoryItem::count,
        "SelectionSlot", &InventoryItem::selection_slot,
        "AttachmentProp", &InventoryItem::attachment_prop,
        "WeaponHandle", &InventoryItem::weapon_handle
    );
}

void Lua::BindChecksumStri(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<checksum_stri>
    (
        "ChecksumStri",
        "new", sol::no_constructor,
        "Checksum", &checksum_stri::checksum
    );
}

void Lua::BindInvItemInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<inv_item_info>
    (
        "InvItemInfo",
        "new", sol::no_constructor,
        "Name", &inv_item_info::name,
        "NameChecksum", &inv_item_info::name_checksum,
        "DisplayName", &inv_item_info::display_name,
        "Cost", &inv_item_info::cost,
        "DefaultCount", &inv_item_info::default_count,
        "MaxItem", &inv_item_info::max_item,
        "Description", &inv_item_info::description,
        //"WeaponInfo", &inv_item_info::weapon_info, //Todo: Bind weapon_info, document it here and on it's own page.
        "ItemOrder", sol::property([](inv_item_info& Self) -> int {return static_cast<int>(Self.item_order); }, [](inv_item_info& Self, int Value) {Self.item_order = static_cast<char>(Value); })//,
        //"UseFunc", &inv_item_info::use //Todo: Bind this
    );
}
