#include "BaseTypeLua.h"
#include "Functions.h"

void Lua::BindRfgBaseArray(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<rfg::base_array<Object*>>
    (
        "RfgBaseArray",
        "new", sol::no_constructor,
        "Size", &rfg::base_array<Object*>::Size,
        "Length", &rfg::base_array<Object*>::Length,
        "Capacity", &rfg::base_array<Object*>::Capacity,
        sol::meta_function::index, &rfg::base_array<Object*>::operator[]
    );
}

void Lua::BindRfgFArray(sol::state& LuaState)
{
	//auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	//auto Utype = RfgTable.create_simple_usertype<rfg::farray>();
	//Utype.set("new", sol::no_constructor);
	//Utype.set("", &rfg::farray::);
	//LuaState.set_usertype("RfgFArray", Utype);
}

void Lua::BindTimestampRealtime(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<timestamp_realtime>
    (
        "TimestampRealtime",
        "new", sol::no_constructor,
        "Value", &timestamp_realtime::value
    );
}

void Lua::BindColor(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<color>
    (
        "Color",
        "new", sol::constructors<color(), color(char), color(const color&), color(char, char, char, char)>(),
        "SetAll", &color::SetAll,
        "Red", sol::property([](color& Self) -> int {return static_cast<int>(Self.red); }, [](color& Self, int Value) {Self.red = static_cast<char>(Value); }),
        "Green", sol::property([](color& Self) -> int {return static_cast<int>(Self.green); }, [](color& Self, int Value) {Self.green = static_cast<char>(Value); }),
        "Blue", sol::property([](color& Self) -> int {return static_cast<int>(Self.blue); }, [](color& Self, int Value) {Self.blue = static_cast<char>(Value); }),
        "Alpha", sol::property([](color& Self) -> int {return static_cast<int>(Self.alpha); }, [](color& Self, int Value) {Self.alpha = static_cast<char>(Value); })
    );
}

void Lua::BindNanoCallbackInfo(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<nano_callback_info>
    (
        "NanoCallbackInfo",
        "TargetHandle", &nano_callback_info::target_handle,
        "KilledByNano", &nano_callback_info::killed_by_nano,
        "HumanNanoIndex", &nano_callback_info::human_nano_index
    );
}

void Lua::BindTimestamp(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<Timestamp>
    (
        "Timestamp",
        "new", sol::no_constructor,
        "Value", &Timestamp::value
    );
}

void Lua::BindTimestampPercent(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<TimestampPercent>
    (
        "TimestampPercent",
        "new", sol::no_constructor,
        sol::base_classes, sol::bases<Timestamp>(),
        "SetMilliseconds", &TimestampPercent::set_milliseconds
    );
}
