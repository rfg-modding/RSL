#include "VectorLua.h"
#include "Functions.h"

void Lua::BindVector2(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<vector2>();
	Utype.set("new", sol::constructors<vector2(), vector2(const vector2&), vector2(float), vector2(float, float)>());
	Utype.set(sol::meta_function::addition, &vector2::operator+);
	Utype.set(sol::meta_function::subtraction, &vector2::operator-);
	Utype.set(sol::meta_function::multiplication, &vector2::operator*);
	Utype.set(sol::meta_function::equal_to, &vector2::operator==);
	Utype.set("Magnitude", &vector2::Magnitude);
	Utype.set("Scale", &vector2::Scale);
	Utype.set("SetAll", &vector2::SetAll);
	Utype.set("x", &vector2::x);
	Utype.set("y", &vector2::y);
    Utype.set("Print", [](vector2& Self) { Logger::LogNone("x: {}, y: {}", Self.x, Self.y);});
    Utype.set("GetDataString", sol::overload(
        [](vector2& Self) {return Self.GetDataString(false, true); },
        [](vector2& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
        [](vector2& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); }));
    Utype.set("ToString", sol::overload(
        [](vector2& Self) {return Self.GetDataString(false, true); },
        [](vector2& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
        [](vector2& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); }));
	RfgTable.set_usertype("Vector2", Utype);
#endif
}

void Lua::BindVector(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<vector>();
	Utype.set("new", sol::constructors<vector(), vector(const vector&), vector(float), vector(float, float, float)>());
	Utype.set(sol::meta_function::addition, &vector::operator+);
	Utype.set(sol::meta_function::subtraction, &vector::operator-);
	Utype.set(sol::meta_function::multiplication, &vector::operator*);
	Utype.set(sol::meta_function::equal_to, &vector::operator==);
	Utype.set("Cross", &vector::Cross);
	Utype.set("Magnitude", &vector::Magnitude);
	Utype.set("Scale", &vector::Scale);
	Utype.set("SetAll", &vector::SetAll);
	Utype.set("x", &vector::x);
	Utype.set("y", &vector::y);
	Utype.set("z", &vector::z);
    Utype.set("UnitVector", &vector::UnitVector);
	Utype.set("Print", [](vector& Self) { Logger::LogNone("x: {}, y: {}, z: {}", Self.x, Self.y, Self.z); });
	Utype.set("GetDataString", sol::overload(
        [](vector& Self) {return Self.GetDataString(false, true); },
        [](vector& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
        [](vector& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); }));
    Utype.set("ToString", sol::overload(
        [](vector& Self) {return Self.GetDataString(false, true); },
        [](vector& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
        [](vector& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); }));
	RfgTable.set_usertype("Vector", Utype);
#endif
}
