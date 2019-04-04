#include "VectorLua.h"
#include "Functions.h"

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
