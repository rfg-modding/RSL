#include "BaseTypeLua.h"
#include "Functions.h"

void Lua::BindTimestampRealtime(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<timestamp_realtime>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Value", &timestamp_realtime::value);
	LuaState.set_usertype("TimestampRealtime", Utype);
}

void Lua::BindColor(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<color>();
	Utype.set("new", sol::constructors<color(), color(char), color(const color&), color(char, char, char, char)>());
	Utype.set("SetAll", &color::SetAll);
	Utype.set("Red", &color::red);
	Utype.set("Green", &color::green);
	Utype.set("Blue", &color::blue);
	Utype.set("Alpha", &color::alpha);
	LuaState.set_usertype("Color", Utype);
}

void Lua::BindNanoCallbackInfo(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<nano_callback_info>();
	Utype.set("TargetHandle", &nano_callback_info::target_handle);
	Utype.set("KilledByNano", &nano_callback_info::killed_by_nano);
	Utype.set("HumanNanoIndex", &nano_callback_info::human_nano_index);
	LuaState.set_usertype("NanoCallbackInfo", Utype);
}

void Lua::BindTimestamp(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Timestamp>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Value", &Timestamp::value);
	LuaState.set_usertype("Timestamp", Utype);
}

void Lua::BindTimestampPercent(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<TimestampPercent>();
	Utype.set("new", sol::no_constructor);
	Utype.set(sol::base_classes, sol::bases<Timestamp>());
	Utype.set("SetMilliseconds", &TimestampPercent::set_milliseconds);
	LuaState.set_usertype("TimestampPercent", Utype);
}
