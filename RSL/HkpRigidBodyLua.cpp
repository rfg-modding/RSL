#include "HkpRigidBodyLua.h"
#include "Functions.h"

void Lua::BindHkpMaterial(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<hkpMaterial>();
	Utype.set("new", sol::no_constructor);
	//Utype.set("ResponseType", &hkpMaterial::m_responseType);
	Utype.set("RollingFrictionMultiplier", sol::property([](hkpMaterial& Self)->__int16& {return Self.m_rollingFrictionMultiplier.m_value; }));
	Utype.set("Friction", &hkpMaterial::m_friction);
	Utype.set("Restitution", &hkpMaterial::m_restitution);
	RfgTable.set_usertype("hkpMaterial", Utype);
#endif
}

void Lua::BindHkpEntity(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<hkpEntity>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Material", &hkpEntity::m_material);
	//Utype.set("ApplyLinearImpulse", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	//Utype.set("", &hkpEntity::);
	RfgTable.set_usertype("hkpEntity", Utype);
#endif
}

void Lua::BindHkpRigidBody(sol::state& LuaState)
{
#if LUA_ENABLED
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<hkpRigidBody>();
	Utype.set("new", sol::no_constructor);
	Utype.set(sol::base_classes, sol::bases<hkpEntity>());
	Utype.set("ApplyLinearImpulse", [](hkpRigidBody& Self, vector& Impulse) { rfg::HavokBodyApplyLinearImpulseA(&Self, Impulse); });
	//Utype.set("", &hkpRigidBody::);
	//Utype.set("", &hkpRigidBody::);
	//Utype.set("", &hkpRigidBody::);
	//Utype.set("", &hkpRigidBody::);
	//Utype.set("", &hkpRigidBody::);
	RfgTable.set_usertype("hkpRigidBody", Utype);
#endif
}
