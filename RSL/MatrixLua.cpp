#include "MatrixLua.h"
#include "Functions.h"

void Lua::BindMatrix(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<matrix>
    (
        "Matrix",
        "new", sol::constructors<matrix(), matrix(const matrix&), matrix(float), matrix(vector, vector, vector)>(),
        sol::meta_function::addition, &matrix::operator+,
        sol::meta_function::subtraction, &matrix::operator-,
        sol::meta_function::equal_to, &matrix::operator==,
        "SetAll", &matrix::SetAll,
        "rvec", &matrix::rvec,
        "uvec", &matrix::uvec,
        "fvec", &matrix::fvec,
        "ToString", sol::overload(
            [](matrix& Self) {return Self.ToString(false, false); },
            [](matrix& Self, bool Parentheses) {return Self.ToString(Parentheses, true); },
            [](matrix& Self, bool Parentheses, bool Labels) {return Self.ToString(Parentheses, Labels); })
    );
}
