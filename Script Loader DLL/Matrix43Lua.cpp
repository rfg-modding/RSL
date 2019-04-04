#include "Matrix43Lua.h"
#include "Functions.h"

void Lua::BindMatrix43(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<matrix43>();
	Utype.set("new", sol::constructors<matrix43(), matrix43(const matrix43&), matrix43(float), matrix43(matrix, vector)>());
	Utype.set(sol::meta_function::addition, &matrix43::operator+);
	Utype.set(sol::meta_function::subtraction, &matrix43::operator-);
	Utype.set(sol::meta_function::equal_to, &matrix43::operator==);
	Utype.set("SetAll", &matrix43::SetAll);
	Utype.set("Rotation", &matrix43::m_rotation);
	Utype.set("Translation", &matrix43::m_translation);

	/*RfgTable.new_usertype<matrix43>
	(
		"matrix43",
		"new", sol::constructors<matrix43(), matrix43(const matrix43&), matrix43(float), matrix43(matrix, vector)>(),
		sol::meta_function::addition, &matrix43::operator+,
		sol::meta_function::subtraction, &matrix43::operator-,
		sol::meta_function::equal_to, &matrix43::operator==,
		"SetAll", &matrix43::SetAll,
		"Rotation", &matrix43::m_rotation,
		"Translation", &matrix43::m_translation
	);*/
}