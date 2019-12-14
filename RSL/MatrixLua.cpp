#include "MatrixLua.h"
#include "Functions.h"

void Lua::BindMatrix(sol::state& LuaState)
{
#if LUA_ENABLED
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
    Utype.set("ToString", sol::overload(
        [](matrix& Self) {return Self.ToString(false, false); },
        [](matrix& Self, bool Parentheses) {return Self.ToString(Parentheses, true); },
        [](matrix& Self, bool Parentheses, bool Labels) {return Self.ToString(Parentheses, Labels); }));
    Utype.set("RotateAboutLocalVector", sol::overload(
        [](matrix& Self, vector& Axis, float AngleRadians) { rfg::matrix_rotate_around_local_vector(&Self, nullptr, Axis, AngleRadians); }
    ));
    Utype.set("RotateAboutXAxis", sol::overload(
    [](matrix& Self, float AngleRadians)
    {
        vector XAxis = {1.0f, 0.0f, 0.0f};
        rfg::matrix_rotate_around_local_vector(&Self, nullptr, XAxis, AngleRadians);
    }));
    Utype.set("RotateAboutYAxis", sol::overload(
    [](matrix& Self, float AngleRadians)
    {
        vector YAxis = {0.0f, 1.0f, 0.0f};
        rfg::matrix_rotate_around_local_vector(&Self, nullptr, YAxis, AngleRadians);
    }));
    Utype.set("RotateAboutZAxis", sol::overload(
    [](matrix& Self, float AngleRadians)
    {
        vector ZAxis = {0.0f, 0.0f, 1.0f};
        rfg::matrix_rotate_around_local_vector(&Self, nullptr, ZAxis, AngleRadians);
    }));
	RfgTable.set_usertype("Matrix", Utype);
#endif
}