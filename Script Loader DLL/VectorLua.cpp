#include "VectorLua.h"
#include "Functions.h"

void Lua::BindVector(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	RfgTable.new_usertype<vector>
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
	);
}
