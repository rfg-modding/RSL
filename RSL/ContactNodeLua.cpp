#include "ContactNodeLua.h"
#include "Functions.h"

void Lua::BindContactNode(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<ContactNode>
	(
		"ContactNode",
		"new", sol::constructors<ContactNode(), ContactNode(const ContactNode&)>(),
		"ContactedObject", &ContactNode::m_contacted_object,
		"NumberOfContacts", &ContactNode::m_num_contacts,
		"Previous", &ContactNode::prev,
		"Next", &ContactNode::next
	);
}
