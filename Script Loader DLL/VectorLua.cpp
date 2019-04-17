#include "VectorLua.h"
#include "Functions.h"

void Lua::BindVector2(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<vector2>();
	Utype.set("new", sol::constructors<vector2(), vector2(const vector2&), vector2(float), vector2(float, float)>());
	Utype.set(sol::meta_function::addition, &vector2::operator+);
	Utype.set(sol::meta_function::subtraction, &vector2::operator-);
	Utype.set(sol::meta_function::multiplication, &vector2::operator*);
	Utype.set(sol::meta_function::equal_to, &vector2::operator==);
	Utype.set("Magnitude", &vector2::Magnitude);
	Utype.set("SetAll", &vector2::SetAll);
	Utype.set("x", &vector2::x);
	Utype.set("y", &vector2::y);
	Utype.set("Print", [](vector2& Self) { Logger::Log(std::string("x: " + std::to_string(Self.x) + ", y: " + std::to_string(Self.y)), LogNone); });
	Utype.set("GetDataString", &vector2::GetDataString);
	RfgTable.set_usertype("Vector2", Utype);
}

void Lua::BindVector(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<vector>();
	Utype.set("new", sol::constructors<vector(), vector(const vector&), vector(float), vector(float, float, float)>());
	Utype.set(sol::meta_function::addition, &vector::operator+);
	Utype.set(sol::meta_function::subtraction, &vector::operator-);
	Utype.set(sol::meta_function::multiplication, &vector::operator*);
	Utype.set(sol::meta_function::equal_to, &vector::operator==);
	Utype.set("Cross", &vector::Cross);
	Utype.set("Magnitude", &vector::Magnitude);
	Utype.set("SetAll", &vector::SetAll);
	Utype.set("x", &vector::x);
	Utype.set("y", &vector::y);
	Utype.set("z", &vector::z);
	Utype.set("Print", [](vector& Self) { Logger::Log(std::string("x: " + std::to_string(Self.x) + ", y: " + std::to_string(Self.y) + ", z: " + std::to_string(Self.z)), LogNone); });
	Utype.set("GetDataString", &vector::GetDataString);
	RfgTable.set_usertype("Vector", Utype);

	/*RfgTable.new_usertype<vector>
	(
		"vector",
		"new", sol::constructors<vector(), vector(const vector&), vector(float), vector(float, float, float)>(),
		sol::meta_function::addition, &vector::operator+,
		sol::meta_function::subtraction, &vector::operator-,
		sol::meta_function::multiplication, &vector::operator*,
		sol::meta_function::equal_to, &vector::operator==,
		"Cross", &vector::Cross,
		"Magnitude", &vector::Magnitude,
		"SetAll", &vector::SetAll,
		"x", &vector::x,
		"y", &vector::y,
		"z", &vector::z
	);*/
}
