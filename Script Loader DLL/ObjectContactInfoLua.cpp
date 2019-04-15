#include "ObjectContactInfoLua.h"
#include "Functions.h"

void Lua::BindObjectContactInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<ObjectContactInfo>();
	Utype.set("new", sol::constructors<ObjectContactInfo(), ObjectContactInfo(const ObjectContactInfo&)>());
	Utype.set("ContactList", &ObjectContactInfo::m_contact_list);
	RfgTable.set_usertype("ObjectContactInfo", Utype);

	/*RfgTable.new_usertype<ObjectContactInfo>
	(
		"ObjectContactInfo",
		"new", sol::constructors<ObjectContactInfo(), ObjectContactInfo(const ObjectContactInfo&)>(),
		"ContactList", &ObjectContactInfo::m_contact_list
	);*/
}
