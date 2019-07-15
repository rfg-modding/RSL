#include "ExplosionInfoLua.h"
#include "Functions.h"

void Lua::BindFixedArrayWrapperExplosionInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<FixedArrayWrapper<explosion_info>>();
    Utype.set("new", sol::no_constructor);
    Utype.set("Size", &FixedArrayWrapper<explosion_info>::Size);
    Utype.set("Capacity", &FixedArrayWrapper<explosion_info>::Capacity);
    Utype.set("Initialized", &FixedArrayWrapper<explosion_info>::Initialized);
    Utype.set(sol::meta_function::index, &FixedArrayWrapper<explosion_info>::operator[]);
    RfgTable.set_usertype("FixedArrayWrapper", Utype);
}

void Lua::BindExplosionInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<explosion_info>();
    Utype.set("new", sol::constructors<explosion_info(), explosion_info(const explosion_info&)>());
    Utype.set("Name", sol::property([](explosion_info& Self) {return std::ref(Self.m_name); })); 
    Utype.set("UniqueId", &explosion_info::m_unique_id);
    Utype.set("NameCrcStr", &explosion_info::m_name_crc_str);
    Utype.set("Flags", &explosion_info::flags);
    Utype.set("Radius", &explosion_info::m_radius);
    Utype.set("SecondaryRadius", &explosion_info::m_secondary_radius);
    Utype.set("KnockdownRadius", &explosion_info::m_knockdown_radius);
    Utype.set("FlinchRadius", &explosion_info::m_flinch_radius);
    Utype.set("AiSoundRadius", &explosion_info::m_ai_sound_radius);
    Utype.set("HumanMinDamageHitpoints", &explosion_info::m_human_min_damage_hitpoints);
    Utype.set("HumanMaxDamageHitpoints", &explosion_info::m_human_max_damage_hitpoints);
    Utype.set("VehicleMinDamageHitpoints", &explosion_info::m_vehicle_min_damage_hitpoints);
    Utype.set("VehicleMaxDamageHitpoints", &explosion_info::m_vehicle_max_damage_hitpoints);
    Utype.set("PlayerDamageMult", &explosion_info::player_damage_mult);
    Utype.set("PlayerVehDamageMult", &explosion_info::player_veh_damage_mult);
    Utype.set("PlayerVehicleImpulseMult", &explosion_info::player_vehicle_impulse_mult);
    Utype.set("ImpulseMagnitude", &explosion_info::m_impulse_magnitude);
    Utype.set("StructuralDamage", &explosion_info::m_structural_damage);
    Utype.set("ExpandingExplosionDuration", &explosion_info::expanding_explosion_duration);
    Utype.set("ExpandingExplosionDelay", &explosion_info::expanding_explosion_delay);
    Utype.set("NumEffects", &explosion_info::m_num_effects);
    Utype.set("Effects", sol::property([](explosion_info& Self) {return std::ref(Self.m_effects); }));
    Utype.set("NumMaterialEffects", &explosion_info::m_num_material_effects);
    Utype.set("MaterialEffects", sol::property([](explosion_info& Self) {return std::ref(Self.m_material_effects); }));
    Utype.set("MaterialReference", sol::property([](explosion_info& Self) {return std::ref(Self.m_material_reference); }));
    Utype.set("SalvageMaterial", &explosion_info::salvage_material);
    Utype.set("SalvageMaxPieces", &explosion_info::salvage_max_pieces);
    Utype.set("SalvageProbability", &explosion_info::salvage_probability);
    Utype.set("TimeBetweenBreaks", &explosion_info::time_between_breaks);
    Utype.set("HalfAngleDot", &explosion_info::half_angle_dot);
    Utype.set("BlastDecalRadius", &explosion_info::blast_decal_radius);
    Utype.set("CameraShakeType", sol::property([](explosion_info& Self) {return std::ref(Self.camera_shake_type); }));
    Utype.set("CameraShakeMultiplier", &explosion_info::camera_shake_multiplier);
    Utype.set("CameraShakeFalloff", &explosion_info::camera_shake_falloff);
    Utype.set("IgnoreOrientation", &explosion_info::ignore_orientation);
    Utype.set("AlwaysRagdoll", &explosion_info::always_ragdoll);
    RfgTable.set_usertype("ExplosionInfo", Utype);
}