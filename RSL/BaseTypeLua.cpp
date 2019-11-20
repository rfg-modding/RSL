#include "BaseTypeLua.h"
#include "Functions.h"

void Lua::BindRfgBaseArrayObjectPtr(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<rfg::base_array<Object*>>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Size", &rfg::base_array<Object*>::Size);
	Utype.set("Length", &rfg::base_array<Object*>::Length);
	Utype.set("Capacity", &rfg::base_array<Object*>::Capacity);
	Utype.set(sol::meta_function::index, &rfg::base_array<Object*>::operator[]);
	RfgTable.set_usertype("RfgBaseArrayObjectPtr", Utype);
#endif
}

void Lua::BindRfgFArray(sol::state& LuaState)
{
#if LUA_ENABLED
	//auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	//auto Utype = RfgTable.create_simple_usertype<rfg::farray>();
	//Utype.set("new", sol::no_constructor);
	//Utype.set("", &rfg::farray::);
	//LuaState.set_usertype("RfgFArray", Utype);
#endif
}

void Lua::BindTimestampRealtime(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<timestamp_realtime>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Value", &timestamp_realtime::value);
	RfgTable.set_usertype("TimestampRealtime", Utype);
#endif
}

void Lua::BindColor(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<color>();
	Utype.set("new", sol::constructors<color(), color(char), color(const color&), color(char, char, char, char)>());
	Utype.set("SetAll", &color::SetAll);
	Utype.set("Red", sol::property([](color& Self) -> int {return static_cast<int>(Self.red); }, [](color& Self, int Value) {Self.red = static_cast<char>(Value); }));
	Utype.set("Green", sol::property([](color& Self) -> int {return static_cast<int>(Self.green); }, [](color& Self, int Value) {Self.green = static_cast<char>(Value); }));
	Utype.set("Blue", sol::property([](color& Self) -> int {return static_cast<int>(Self.blue); }, [](color& Self, int Value) {Self.blue = static_cast<char>(Value); }));
	Utype.set("Alpha", sol::property([](color& Self) -> int {return static_cast<int>(Self.alpha); }, [](color& Self, int Value) {Self.alpha = static_cast<char>(Value); }));
	RfgTable.set_usertype("Color", Utype);
#endif
}

void Lua::BindNanoCallbackInfo(sol::state & LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<nano_callback_info>();
	Utype.set("TargetHandle", &nano_callback_info::target_handle);
	Utype.set("KilledByNano", &nano_callback_info::killed_by_nano);
	Utype.set("HumanNanoIndex", &nano_callback_info::human_nano_index);
	RfgTable.set_usertype("NanoCallbackInfo", Utype);
#endif
}

void Lua::BindTimestamp(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Timestamp>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Value", &Timestamp::value);
	RfgTable.set_usertype("Timestamp", Utype);
#endif
}

void Lua::BindTimestampPercent(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<TimestampPercent>();
	Utype.set("new", sol::no_constructor);
	Utype.set(sol::base_classes, sol::bases<Timestamp>());
	Utype.set("SetMilliseconds", &TimestampPercent::set_milliseconds);
	RfgTable.set_usertype("TimestampPercent", Utype);
#endif
}
