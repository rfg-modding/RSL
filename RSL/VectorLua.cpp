#include "VectorLua.h"
#include "Functions.h"

void Lua::BindVector2(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<vector2>
    (
        "Vector2",
        "new", sol::constructors<vector2(), vector2(const vector2&), vector2(float), vector2(float, float)>(),
        sol::meta_function::addition, &vector2::operator+,
        sol::meta_function::subtraction, &vector2::operator-,
        sol::meta_function::multiplication, &vector2::operator*,
        sol::meta_function::equal_to, &vector2::operator==,
        "Magnitude", &vector2::Magnitude,
        "Scale", &vector2::Scale,
        "SetAll", &vector2::SetAll,
        "x", &vector2::x,
        "y", &vector2::y,
        "Print", [](vector2& Self) { Logger::LogNone("x: {}, y: {}", Self.x, Self.y); },
        "GetDataString", sol::overload(
            [](vector2& Self) {return Self.GetDataString(false, true); },
            [](vector2& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
            [](vector2& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); }),
        "ToString", sol::overload(
            [](vector2& Self) {return Self.GetDataString(false, true); },
            [](vector2& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
            [](vector2& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); })
    );
}

void Lua::BindVector(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<vector>
    (
        "Vector",
        "new", sol::constructors<vector(), vector(const vector&), vector(float), vector(float, float, float)>(),
        sol::meta_function::addition, &vector::operator+,
        sol::meta_function::subtraction, &vector::operator-,
        sol::meta_function::multiplication, &vector::operator*,
        sol::meta_function::equal_to, &vector::operator==,
        "Cross", &vector::Cross,
        "Magnitude", &vector::Magnitude,
        "Scale", &vector::Scale,
        "SetAll", &vector::SetAll,
        "x", &vector::x,
        "y", &vector::y,
        "z", &vector::z,
        "UnitVector", &vector::UnitVector,
        "GetDataString", sol::overload(
            [](vector& Self) {return Self.GetDataString(false, true); },
            [](vector& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
            [](vector& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); }),
        "ToString", sol::overload(
            [](vector& Self) {return Self.GetDataString(false, true); },
            [](vector& Self, bool Parentheses) {return Self.GetDataString(Parentheses, true); },
            [](vector& Self, bool Parentheses, bool Labels) {return Self.GetDataString(Parentheses, Labels); })
    );
}
