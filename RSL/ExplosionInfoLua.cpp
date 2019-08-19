#include "ExplosionInfoLua.h"
#include "Functions.h"

void Lua::BindFixedArrayWrapperExplosionInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<FixedArrayWrapper<explosion_info>>
    (
        "FixedArrayWrapperExplosionInfo",
        "new", sol::no_constructor,
        "Size", &FixedArrayWrapper<explosion_info>::Size,
        "Length", &FixedArrayWrapper<explosion_info>::Length,
        "Capacity", &FixedArrayWrapper<explosion_info>::Capacity,
        "Initialized", &FixedArrayWrapper<explosion_info>::Initialized,
        sol::meta_function::index, &FixedArrayWrapper<explosion_info>::operator[]
    );
}

void Lua::BindExplosionInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<explosion_info>
    (
        "ExplosionInfo",
        "new", sol::constructors<explosion_info(), explosion_info(const explosion_info&)>(),
        "Name", sol::property([](explosion_info& Self) {return Globals::CharArrayToString(Self.m_name, 32); }),
        "UniqueId", &explosion_info::m_unique_id,
        "NameCrcStr", &explosion_info::m_name_crc_str,
        "Flags", &explosion_info::flags,
        "Radius", &explosion_info::m_radius,
        "SecondaryRadius", &explosion_info::m_secondary_radius,
        "KnockdownRadius", &explosion_info::m_knockdown_radius,
        "FlinchRadius", &explosion_info::m_flinch_radius,
        "AiSoundRadius", &explosion_info::m_ai_sound_radius,
        "HumanMinDamageHitpoints", &explosion_info::m_human_min_damage_hitpoints,
        "HumanMaxDamageHitpoints", &explosion_info::m_human_max_damage_hitpoints,
        "VehicleMinDamageHitpoints", &explosion_info::m_vehicle_min_damage_hitpoints,
        "VehicleMaxDamageHitpoints", &explosion_info::m_vehicle_max_damage_hitpoints,
        "PlayerDamageMult", &explosion_info::player_damage_mult,
        "PlayerVehDamageMult", &explosion_info::player_veh_damage_mult,
        "PlayerVehicleImpulseMult", &explosion_info::player_vehicle_impulse_mult,
        "ImpulseMagnitude", &explosion_info::m_impulse_magnitude,
        "StructuralDamage", &explosion_info::m_structural_damage,
        "ExpandingExplosionDuration", &explosion_info::expanding_explosion_duration,
        "ExpandingExplosionDelay", &explosion_info::expanding_explosion_delay,
        "NumEffects", &explosion_info::m_num_effects,
        "Effects", sol::property([](explosion_info& Self) {return std::ref(Self.m_effects); }),
        "NumMaterialEffects", &explosion_info::m_num_material_effects,
        "MaterialEffects", sol::property([](explosion_info& Self) {return std::ref(Self.m_material_effects); }),
        "MaterialReference", sol::property([](explosion_info& Self) {return std::ref(Self.m_material_reference); }),
        "SalvageMaterial", &explosion_info::salvage_material,
        "SalvageMaxPieces", &explosion_info::salvage_max_pieces,
        "SalvageProbability", &explosion_info::salvage_probability,
        "TimeBetweenBreaks", &explosion_info::time_between_breaks,
        "HalfAngleDot", &explosion_info::half_angle_dot,
        "BlastDecalRadius", &explosion_info::blast_decal_radius,
        "CameraShakeType", sol::property([](explosion_info& Self) {return Globals::CharArrayToString(Self.camera_shake_type, 32); }),
        "CameraShakeMultiplier", &explosion_info::camera_shake_multiplier,
        "CameraShakeFalloff", &explosion_info::camera_shake_falloff,
        "IgnoreOrientation", &explosion_info::ignore_orientation,
        "AlwaysRagdoll", &explosion_info::always_ragdoll
    );
}