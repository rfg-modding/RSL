#include "ObjectFlagsLua.h"
#include "Functions.h"

void Lua::BindObjectFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<ObjectFlags>();
	Utype.set("new", sol::constructors<ObjectFlags(), ObjectFlags(const ObjectFlags&)>());
	Utype.set("FlaggedListState", sol::property(itsy_bitsy::read<ObjectFlags, 0, 3>, itsy_bitsy::write<ObjectFlags, 0, 3>)); //int8 - 3
	Utype.set("LightingSetOnce", sol::property(itsy_bitsy::read<ObjectFlags, 3>, itsy_bitsy::write<ObjectFlags, 3>)); //int8 - 1
	Utype.set("Destroyed", sol::property(itsy_bitsy::read<ObjectFlags, 4>, itsy_bitsy::write<ObjectFlags, 4>)); //int8 - 1
	Utype.set("NoSave", sol::property(itsy_bitsy::read<ObjectFlags, 5>, itsy_bitsy::write<ObjectFlags, 5>)); //int8 - 1
	Utype.set("ForceFullSave", sol::property(itsy_bitsy::read<ObjectFlags, 6>, itsy_bitsy::write<ObjectFlags, 6>)); //int8 - 1
	Utype.set("DestroyOnSave", sol::property(itsy_bitsy::read<ObjectFlags, 7>, itsy_bitsy::write<ObjectFlags, 7>)); //int8 - 1
	Utype.set("CreatedByMissionOrActivity", sol::property(itsy_bitsy::read<ObjectFlags, 8>, itsy_bitsy::write<ObjectFlags, 8>)); //int8 - 1
	Utype.set("DontTransform", sol::property(itsy_bitsy::read<ObjectFlags, 9>, itsy_bitsy::write<ObjectFlags, 9>)); //int8 - 1
	Utype.set("WorldFree", sol::property(itsy_bitsy::read<ObjectFlags, 10>, itsy_bitsy::write<ObjectFlags, 10>)); //int8 - 1
	Utype.set("Streaming", sol::property(itsy_bitsy::read<ObjectFlags, 11>, itsy_bitsy::write<ObjectFlags, 11>)); //int8 - 1
	Utype.set("Streamed", sol::property(itsy_bitsy::read<ObjectFlags, 12>, itsy_bitsy::write<ObjectFlags, 12>)); //int8 - 1
	Utype.set("Persistent", sol::property(itsy_bitsy::read<ObjectFlags, 13>, itsy_bitsy::write<ObjectFlags, 13>)); //int8 - 1
	Utype.set("Original", sol::property(itsy_bitsy::read<ObjectFlags, 14>, itsy_bitsy::write<ObjectFlags, 14>)); //int8 - 1
	Utype.set("Stub", sol::property(itsy_bitsy::read<ObjectFlags, 15>, itsy_bitsy::write<ObjectFlags, 15>)); //int8 - 1
	Utype.set("PreserveHandle", sol::property(itsy_bitsy::read<ObjectFlags, 16>, itsy_bitsy::write<ObjectFlags, 16>)); //int8 - 1
	Utype.set("BpoIndex", sol::property(itsy_bitsy::read<ObjectFlags, 17, 2>, itsy_bitsy::write<ObjectFlags, 17, 2>)); //int8 - 2
	Utype.set("IsDependent", sol::property(itsy_bitsy::read<ObjectFlags, 19>, itsy_bitsy::write<ObjectFlags, 19>)); //int8 - 1
	Utype.set("Visited", sol::property(itsy_bitsy::read<ObjectFlags, 20>, itsy_bitsy::write<ObjectFlags, 20>)); //int8 - 1
	Utype.set("SpecialLifetime", sol::property(itsy_bitsy::read<ObjectFlags, 21>, itsy_bitsy::write<ObjectFlags, 21>)); //int8 - 1
	Utype.set("SerializeProtected", sol::property(itsy_bitsy::read<ObjectFlags, 22>, itsy_bitsy::write<ObjectFlags, 22>)); //int8 - 1
	Utype.set("DontUseMe", sol::property(itsy_bitsy::read<ObjectFlags, 23>, itsy_bitsy::write<ObjectFlags, 23>)); //int8 - 1
	Utype.set("StreamingFixed", sol::property(itsy_bitsy::read<ObjectFlags, 24>, itsy_bitsy::write<ObjectFlags, 24>)); //int8 - 1
	Utype.set("RenderFlags", sol::property(itsy_bitsy::read<ObjectFlags, 25, 4>, itsy_bitsy::write<ObjectFlags, 25, 4>)); //int8 - 4 
	RfgTable.set_usertype("ObjectFlags", Utype);

	/*RfgTable.new_usertype<ObjectFlags>
	(
		"ObjectFlags",
		"new", sol::constructors<ObjectFlags(), ObjectFlags(const ObjectFlags&)>(),
		"FlaggedListState", sol::property(itsy_bitsy::read<ObjectFlags, 0, 3>, itsy_bitsy::write<ObjectFlags, 0, 3>), //int8 - 3
		"LightingSetOnce", sol::property(itsy_bitsy::read<ObjectFlags, 3>, itsy_bitsy::write<ObjectFlags, 3>), //int8 - 1
		"Destroyed", sol::property(itsy_bitsy::read<ObjectFlags, 4>, itsy_bitsy::write<ObjectFlags, 4>), //int8 - 1
		"NoSave", sol::property(itsy_bitsy::read<ObjectFlags, 5>, itsy_bitsy::write<ObjectFlags, 5>), //int8 - 1
		"ForceFullSave", sol::property(itsy_bitsy::read<ObjectFlags, 6>, itsy_bitsy::write<ObjectFlags, 6>), //int8 - 1
		"DestroyOnSave", sol::property(itsy_bitsy::read<ObjectFlags, 7>, itsy_bitsy::write<ObjectFlags, 7>), //int8 - 1
		"CreatedByMissionOrActivity", sol::property(itsy_bitsy::read<ObjectFlags, 8>, itsy_bitsy::write<ObjectFlags, 8>), //int8 - 1
		"DontTransform", sol::property(itsy_bitsy::read<ObjectFlags, 9>, itsy_bitsy::write<ObjectFlags, 9>), //int8 - 1
		"WorldFree", sol::property(itsy_bitsy::read<ObjectFlags, 10>, itsy_bitsy::write<ObjectFlags, 10>), //int8 - 1
		"Streaming", sol::property(itsy_bitsy::read<ObjectFlags, 11>, itsy_bitsy::write<ObjectFlags, 11>), //int8 - 1
		"Streamed", sol::property(itsy_bitsy::read<ObjectFlags, 12>, itsy_bitsy::write<ObjectFlags, 12>), //int8 - 1
		"Persistent", sol::property(itsy_bitsy::read<ObjectFlags, 13>, itsy_bitsy::write<ObjectFlags, 13>), //int8 - 1
		"Original", sol::property(itsy_bitsy::read<ObjectFlags, 14>, itsy_bitsy::write<ObjectFlags, 14>), //int8 - 1
		"Stub", sol::property(itsy_bitsy::read<ObjectFlags, 15>, itsy_bitsy::write<ObjectFlags, 15>), //int8 - 1
		"PreserveHandle", sol::property(itsy_bitsy::read<ObjectFlags, 16>, itsy_bitsy::write<ObjectFlags, 16>), //int8 - 1
		"BpoIndex", sol::property(itsy_bitsy::read<ObjectFlags, 17, 2>, itsy_bitsy::write<ObjectFlags, 17, 2>), //int8 - 2
		"IsDependent", sol::property(itsy_bitsy::read<ObjectFlags, 19>, itsy_bitsy::write<ObjectFlags, 19>), //int8 - 1
		"Visited", sol::property(itsy_bitsy::read<ObjectFlags, 20>, itsy_bitsy::write<ObjectFlags, 20>), //int8 - 1
		"SpecialLifetime", sol::property(itsy_bitsy::read<ObjectFlags, 21>, itsy_bitsy::write<ObjectFlags, 21>), //int8 - 1
		"SerializeProtected", sol::property(itsy_bitsy::read<ObjectFlags, 22>, itsy_bitsy::write<ObjectFlags, 22>), //int8 - 1
		"DontUseMe", sol::property(itsy_bitsy::read<ObjectFlags, 23>, itsy_bitsy::write<ObjectFlags, 23>),//int8 - 1
		"StreamingFixed", sol::property(itsy_bitsy::read<ObjectFlags, 24>, itsy_bitsy::write<ObjectFlags, 24>), //int8 - 1
		"RenderFlags", sol::property(itsy_bitsy::read<ObjectFlags, 25, 4>, itsy_bitsy::write<ObjectFlags, 25, 4>) //int8 - 4 
	);*/
}
