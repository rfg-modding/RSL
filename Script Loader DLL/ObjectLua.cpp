#include "ObjectLua.h"
#include "Functions.h"

void Lua::BindObject(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<Object>
	(
		"Object",
		"new", sol::constructors<Object(), Object(const Object&)>(),
		"Position", &Object::Position,
		"ChildPtr", &Object::ChildPtr,
		"ChildNext", &Object::ChildNext,
		"ChildPrevious", &Object::ChildPrevious,
		"AttachInfo", &Object::AttachInfo,
		"HavokHandle", &Object::HavokHandle,
		"ContactInfo", &Object::ContactInfo,
		"ObjFlags", &Object::ObjFlags,
		//"RemoteObjFlags", &Object::RemoteObjFlags,
		//"MPDcmoIndex", &Object::MPDcmoIndex,
		"CheckingReset", &Object::CheckingReset,
		"NameIndex", &Object::NameIndex,
		"FlaggedNext", &Object::FlaggedNext,
		"FlaggedPrevious", &Object::FlaggedPrevious,
		"Handle", &Object::Handle,
		"Parent", &Object::Parent,
		"BPOHandle", &Object::BPOHandle,
		"AllIndex", &Object::AllIndex,
		"TypeIndex", &Object::TypeIndex,
		"SubtypeIndex", &Object::SubtypeIndex,
		"ObjectType", &Object::ObjectType,
		"SubType", &Object::SubType,
		"LastKnownBMin", &Object::LastKnownBMin,
		"LastKnownBMax", &Object::LastKnownBMax,
		"SRID", &Object::SRID
	);
}
