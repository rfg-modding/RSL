#include "HkpRigidBodyLua.h"
#include "Functions.h"

void Lua::BindHkpMaterial(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<hkpMaterial>
    (
        "hkpMaterial",
        "new", sol::no_constructor,
        //"ResponseType", &hkpMaterial::m_responseType);
        "RollingFrictionMultiplier", sol::property([](hkpMaterial& Self)->__int16& {return Self.m_rollingFrictionMultiplier.m_value; }),
        "Friction", &hkpMaterial::m_friction,
        "Restitution", &hkpMaterial::m_restitution
    );
}

//Todo: Bind the rest of the values for this
//Todo: Bind the base class for this
void Lua::BindHkpEntity(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<hkpEntity>
    (
        "hkpEntity",
        "new", sol::no_constructor,
        "Material", &hkpEntity::m_material//,
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
        //"", &hkpEntity::
    );
}

void Lua::BindHkpRigidBody(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<hkpRigidBody>
    (
        "hkpRigidBody",
        "new", sol::no_constructor,
        sol::base_classes, sol::bases<hkpEntity>(),
        "ApplyLinearImpulse", [](hkpRigidBody& Self, vector& Impulse) { HavokBodyApplyLinearImpulseA(&Self, &Impulse); }
    );
}
