#include "ObjectContactInfoLua.h"
#include "Functions.h"

void Lua::BindObjectContactInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<ObjectContactInfo>
	(
		"ObjectContactInfo",
		"new", sol::constructors<ObjectContactInfo(), ObjectContactInfo(const ObjectContactInfo&)>(),
		"ContactList", &ObjectContactInfo::m_contact_list
	);
}
