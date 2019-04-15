#include "HumanMPFlagsLua.h"
#include "Functions.h"

void Lua::BindHumanMPFlags(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	//RfgTable.set_usertype("HumanMPFlags", Utype);

	/*RfgTable.new_usertype<HumanMPFlags>
	(
		"HumanMPFlags",
		"new", sol::constructors<HumanMPFlags(), HumanMPFlags(const HumanMPFlags&)>(),
		"IsMultiplayer", sol::property(itsy_bitsy::read<ObjectFlags, 0>, itsy_bitsy::write<ObjectFlags, 0>), //int32 - 1
		"MeleePrimaryID", sol::property(itsy_bitsy::read<ObjectFlags, 1, 2>, itsy_bitsy::write<ObjectFlags, 1, 2>), //int32 - 2
		"MeleeSecondaryID", sol::property(itsy_bitsy::read<ObjectFlags, 3, 2>, itsy_bitsy::write<ObjectFlags, 3, 2>), //int32 - 2
		"MeleeTertiaryID", sol::property(itsy_bitsy::read<ObjectFlags, 5, 2>, itsy_bitsy::write<ObjectFlags, 5, 2>), //int32 - 2
		"MeleeFirearmID", sol::property(itsy_bitsy::read<ObjectFlags, 7, 2>, itsy_bitsy::write<ObjectFlags, 7, 2>), //int32 - 2
		"JumpID", sol::property(itsy_bitsy::read<ObjectFlags, 9, 2>, itsy_bitsy::write<ObjectFlags, 9, 2>), //int32 - 2
		"Vehicle", sol::property(itsy_bitsy::read<ObjectFlags, 11>, itsy_bitsy::write<ObjectFlags, 11>), //int32 - 1
		"Turret", sol::property(itsy_bitsy::read<ObjectFlags, 12>, itsy_bitsy::write<ObjectFlags, 12>), //int32 - 1
		"SwapWeapon", sol::property(itsy_bitsy::read<ObjectFlags, 13>, itsy_bitsy::write<ObjectFlags, 13>), //int32 - 1
		"FirearmTriggerDownID", sol::property(itsy_bitsy::read<ObjectFlags, 14, 2>, itsy_bitsy::write<ObjectFlags, 14, 2>), //int32 - 2
		"FirearmTriggerUpID", sol::property(itsy_bitsy::read<ObjectFlags, 16, 2>, itsy_bitsy::write<ObjectFlags, 16, 2>), //int32 - 2
		"ThrowAttackID", sol::property(itsy_bitsy::read<ObjectFlags, 18, 2>, itsy_bitsy::write<ObjectFlags, 18, 2>), //int32 - 2
		"ChargeWeapon", sol::property(itsy_bitsy::read<ObjectFlags, 20, 2>, itsy_bitsy::write<ObjectFlags, 20, 2>), //int32 - 2
		"RunningAttack", sol::property(itsy_bitsy::read<ObjectFlags, 22>, itsy_bitsy::write<ObjectFlags, 22>), //int32 - 1
		"InAirDetonate", sol::property(itsy_bitsy::read<ObjectFlags, 23>, itsy_bitsy::write<ObjectFlags, 23>), //int32 - 1
		"DetonatedCharges", sol::property(itsy_bitsy::read<ObjectFlags, 24>, itsy_bitsy::write<ObjectFlags, 24>), //int32 - 1
		"Jetpack", sol::property(itsy_bitsy::read<ObjectFlags, 25>, itsy_bitsy::write<ObjectFlags, 25>) //int32 - 1
	);*/
}
