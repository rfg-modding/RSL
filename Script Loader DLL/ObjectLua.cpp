#include "ObjectLua.h"
#include "Functions.h"

void Lua::BindObject(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Object>();
	Utype.set("new", sol::constructors<Object(), Object(const Object&)>());
	Utype.set("Position", &Object::Position);
	Utype.set("ChildPtr", &Object::ChildPtr);
	Utype.set("ChildNext", &Object::ChildNext);
	Utype.set("ChildPrevious", &Object::ChildPrevious);
	Utype.set("AttachInfo", &Object::AttachInfo);
	Utype.set("HavokHandle", &Object::HavokHandle);
	Utype.set("ContactInfo", &Object::ContactInfo);
	Utype.set("ObjFlags", &Object::ObjFlags);
	//Utype.set("RemoteObjFlags", &Object::RemoteObjFlags);
	//Utype.set("MPDcmoIndex", &Object::MPDcmoIndex);
	Utype.set("CheckingReset", &Object::CheckingReset);
	Utype.set("NameIndex", &Object::NameIndex);
	Utype.set("FlaggedNext", &Object::FlaggedNext);
	Utype.set("FlaggedPrevious", &Object::FlaggedPrevious);
	Utype.set("Handle", &Object::Handle);
	Utype.set("Parent", &Object::Parent);
	Utype.set("BPOHandle", &Object::BPOHandle);
	Utype.set("AllIndex", &Object::AllIndex);
	Utype.set("TypeIndex", &Object::TypeIndex);
	Utype.set("SubtypeIndex", &Object::SubtypeIndex);
	Utype.set("ObjectType", &Object::ObjectType);
	Utype.set("SubType", &Object::SubType);
	Utype.set("LastKnownBMin", &Object::LastKnownBMin);
	Utype.set("LastKnownBMax", &Object::LastKnownBMax);
	Utype.set("SRID", &Object::SRID);

	/*RfgTable.new_usertype<Object>
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
	);*/
}
