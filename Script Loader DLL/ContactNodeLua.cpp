#include "ContactNodeLua.h"
#include "Functions.h"

void Lua::BindContactNode(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<ContactNode>();
	Utype.set("new", sol::constructors<ContactNode(), ContactNode(const ContactNode&)>());
	Utype.set("ContactedObject", &ContactNode::m_contacted_object);
	Utype.set("NumberOfContacts", &ContactNode::m_num_contacts);
	Utype.set("Previous", &ContactNode::prev);
	Utype.set("Next", &ContactNode::next);
	LuaState.set_usertype("ContactNode", Utype);

	/*RfgTable.new_usertype<ContactNode>
	(
		"ContactNode",
		"new", sol::constructors<ContactNode(), ContactNode(const ContactNode&)>(),
		"ContactedObject", &ContactNode::m_contacted_object,
		"NumberOfContacts", &ContactNode::m_num_contacts,
		"Previous", &ContactNode::prev,
		"Next", &ContactNode::next
	);*/
}
