#include "MatrixLua.h"
#include "Functions.h"

void Lua::BindMatrix(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<matrix>();
	Utype.set("new", sol::constructors<matrix(), matrix(const matrix&), matrix(float), matrix(vector, vector, vector)>());
	Utype.set(sol::meta_function::addition, &matrix::operator+);
	Utype.set(sol::meta_function::subtraction, &matrix::operator-);
	Utype.set(sol::meta_function::equal_to, &matrix::operator==);
	Utype.set("SetAll", &matrix::SetAll);
	Utype.set("rvec", &matrix::rvec);
	Utype.set("uvec", &matrix::uvec);
	Utype.set("fvec", &matrix::fvec);
	LuaState.set_usertype("Matrix", Utype);

	/*RfgTable.new_usertype<matrix>
	(
		"matrix",
		"new", sol::constructors<matrix(), matrix(const matrix&), matrix(float), matrix(vector, vector, vector)>(),
		sol::meta_function::addition, &matrix::operator+,
		sol::meta_function::subtraction, &matrix::operator-,
		sol::meta_function::equal_to, &matrix::operator==,
		"SetAll", &matrix::SetAll,
		"rvec", &matrix::rvec,
		"uvec", &matrix::uvec,
		"fvec", &matrix::fvec
	);*/
}
