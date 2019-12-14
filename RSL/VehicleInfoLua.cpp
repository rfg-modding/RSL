#include "VehicleInfoLua.h"
#include "Functions.h"

void Lua::BindVehicleCameraSettings(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_camera_settings>();
    Utype.set("new", sol::no_constructor);
    Utype.set("LookatOffset", &vehicle_camera_settings::lookat_offset);
    Utype.set("LookatVehicleOffset", &vehicle_camera_settings::lookat_vehicle_offset);
    Utype.set("LookatVehicleEnterOffset", &vehicle_camera_settings::lookat_vehicle_enter_offset);
    Utype.set("LookfromHeight", &vehicle_camera_settings::lookfrom_height);
    Utype.set("EnterDistance", &vehicle_camera_settings::enter_distance);
    Utype.set("FollowDist", &vehicle_camera_settings::follow_dist);
    Utype.set("FollowHeight", &vehicle_camera_settings::follow_height);
    Utype.set("YAxisRotationSpeed", &vehicle_camera_settings::y_axis_rotation_speed);
    Utype.set("CameraSteerAngle", &vehicle_camera_settings::camera_steer_angle);
    Utype.set("CameraSteerSpeed", &vehicle_camera_settings::camera_steer_speed);
    Utype.set("TurretCamera", &vehicle_camera_settings::turret_camera);
    Utype.set("ForceTurretCam", &vehicle_camera_settings::force_turret_cam);
    RfgTable.set_usertype("VehicleCameraSettings", Utype);
#endif
}

void Lua::BindVehicleInfoTransmissionInfo(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_info_transmission_info>();
    Utype.set("new", sol::no_constructor);
    Utype.set("NumGears", &vehicle_info_transmission_info::num_gears);
    Utype.set("GearRatios[6]", sol::property([](vehicle_info_transmission_info& Self) {return std::ref(Self.gear_ratios); }));
    Utype.set("DownshiftRpms[5]", sol::property([](vehicle_info_transmission_info& Self) {return std::ref(Self.downshift_rpms); }));
    Utype.set("UpshiftRpms[5]", sol::property([](vehicle_info_transmission_info& Self) {return std::ref(Self.upshift_rpms); }));
    Utype.set("DifferentialGearRatio", &vehicle_info_transmission_info::differential_gear_ratio);
    Utype.set("ReverseGearRatio", &vehicle_info_transmission_info::reverse_gear_ratio);
    Utype.set("ClutchDelay", &vehicle_info_transmission_info::clutch_delay);
    Utype.set("ClutchDelayPreShift", &vehicle_info_transmission_info::clutch_delay_pre_shift);
    Utype.set("ForwardToReverseDelay", &vehicle_info_transmission_info::forward_to_reverse_delay);
    Utype.set("ReverseToForwardDelay", &vehicle_info_transmission_info::reverse_to_forward_delay);
    RfgTable.set_usertype("VehicleInfoTransmissionInfo", Utype);
#endif
}

void Lua::BindVehicleInfoAxleWheelInfo(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_info_axle_wheel_info>();
    Utype.set("new", sol::no_constructor);
    Utype.set("DoesSteer", &vehicle_info_axle_wheel_info::does_steer);
    Utype.set("DoesHandbrake", &vehicle_info_axle_wheel_info::does_handbrake);
    Utype.set("EngineTorqueFactor", &vehicle_info_axle_wheel_info::engine_torque_factor);
    Utype.set("Mass", &vehicle_info_axle_wheel_info::mass);
    Utype.set("Friction", &vehicle_info_axle_wheel_info::friction);
    Utype.set("AiFriction", &vehicle_info_axle_wheel_info::ai_friction);
    Utype.set("BrakingTorque", &vehicle_info_axle_wheel_info::braking_torque);
    Utype.set("SpringCompression", &vehicle_info_axle_wheel_info::spring_compression);
    Utype.set("SpringExtension", &vehicle_info_axle_wheel_info::spring_extension);
    Utype.set("SpringStrength", &vehicle_info_axle_wheel_info::spring_strength);
    Utype.set("SpringPower", &vehicle_info_axle_wheel_info::spring_power);
    Utype.set("CompressionDamping", &vehicle_info_axle_wheel_info::compression_damping);
    Utype.set("ExpansionDamping", &vehicle_info_axle_wheel_info::expansion_damping);
    RfgTable.set_usertype("VehicleInfoAxleWheelInfo", Utype);
#endif
}

void Lua::BindRfgFarrayVehicleInfo163(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<rfg::farray<vehicle_info, 163>>();
    Utype.set("new", sol::no_constructor);
    Utype.set("Size", &rfg::farray<vehicle_info, 163>::Size);
    Utype.set("Length", &rfg::farray<vehicle_info, 163>::Length);
    Utype.set("Capacity", &rfg::farray<vehicle_info, 163>::Capacity);
    Utype.set(sol::meta_function::index, &rfg::farray<vehicle_info, 163>::operator[]);
    RfgTable.set_usertype("RfgFarrayVehicleInfo163", Utype);
#endif
}

void Lua::BindBbox(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<bbox>();
    Utype.set("new", sol::constructors<bbox(vector&, vector&), bbox(const bbox&)>());
    Utype.set("Min", &bbox::min);
    Utype.set("Max", &bbox::max);
    RfgTable.set_usertype("Bbox", Utype);
#endif
}

void Lua::BindAnimlibBonesUsedInfo(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<animlib_bones_used_info>();
    Utype.set("new", sol::no_constructor);
    Utype.set("UniqueId", &animlib_bones_used_info::unique_id);
    Utype.set("NumBones", &animlib_bones_used_info::num_bones);
    Utype.set("BoneIndices", &animlib_bones_used_info::bone_indices);
    RfgTable.set_usertype("AnimlibBonesUsedInfo", Utype);
#endif
}

void Lua::BindVehicleInfoFlags(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_info_flags>();
    Utype.set("Preload", sol::property(
        [](vehicle_info_flags& Self)->bool {return Self.preload; },
        [](vehicle_info_flags& Self, bool Value) {Self.preload = Value; }
    ));
    Utype.set("CanBlockRoads", sol::property(
        [](vehicle_info_flags& Self)->bool {return Self.can_block_roads; },
        [](vehicle_info_flags& Self, bool Value) {Self.can_block_roads = Value; }
    ));
    Utype.set("ForceBreakLinks", sol::property(
        [](vehicle_info_flags& Self)->bool {return Self.force_break_links; },
        [](vehicle_info_flags& Self, bool Value) {Self.force_break_links = Value; }
    ));
    Utype.set("SeatCountWarning", sol::property(
        [](vehicle_info_flags& Self)->bool {return Self.seat_count_warning; },
        [](vehicle_info_flags& Self, bool Value) {Self.seat_count_warning = Value; }
    ));
    Utype.set("IsWalkerFlamer", sol::property(
        [](vehicle_info_flags& Self)->bool {return Self.is_walker_flamer; },
        [](vehicle_info_flags& Self, bool Value) {Self.is_walker_flamer = Value; }
    ));
    RfgTable.set_usertype("VehicleInfoFlags", Utype);
#endif
}

void Lua::BindLodInfo(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<lod_info>();
    Utype.set("Min", &lod_info::dist);
    RfgTable.set_usertype("LodInfo", Utype);
#endif
}

void Lua::BindVehicleInfo(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<vehicle_info>();
    Utype.set("new", sol::constructors<vehicle_info(const vehicle_info&)>());
    Utype.set("Name", &vehicle_info::name);
    Utype.set("DisplayName", &vehicle_info::display_name);
    Utype.set("MeshName", &vehicle_info::mesh_name);
    Utype.set("VehicleClass", &vehicle_info::vehicle_class);
    Utype.set("SpawnSize", &vehicle_info::spawn_size);
    Utype.set("SpawnBox", &vehicle_info::spawn_box);
    Utype.set("SlotId", &vehicle_info::slot_id);
    Utype.set("Srid", &vehicle_info::srid);
    Utype.set("VariantFamily", &vehicle_info::variant_family);
    Utype.set("VehicleClassification", &vehicle_info::vehicle_classification);
    Utype.set("DefaultTeam", &vehicle_info::default_team);
    //vi_info
    Utype.set("MaxHitpoints", &vehicle_info::m_max_hitpoints);
    Utype.set("AbandonHitpoints", &vehicle_info::m_abandon_hitpoints);
    Utype.set("ChassisMass", &vehicle_info::chassis_mass);
    Utype.set("Value", &vehicle_info::m_value);
    Utype.set("ChopShopProps", &vehicle_info::m_chop_shop_props);
    Utype.set("NumLods", &vehicle_info::m_num_lods);
    Utype.set("LodInfo", sol::property([](vehicle_info& Self) {return std::ref(Self.m_lod_info);}));
    Utype.set("NumTurretMounts", &vehicle_info::num_turret_mounts);
    //Utype.set("TurretMounts", sol::property([](vehicle_info& Self) {return std::ref(Self.turret_mounts); })); //Todo: Bind type
    Utype.set("RoadPreference", &vehicle_info::m_road_preference);
    Utype.set("EngineTorque", &vehicle_info::engine_torque);
    Utype.set("AiEngineTorque", &vehicle_info::ai_engine_torque);
    Utype.set("MinRpm", &vehicle_info::min_rpm);
    Utype.set("OptimalRpm", &vehicle_info::optimal_rpm);
    Utype.set("MaxRpm", &vehicle_info::max_rpm);
    Utype.set("MinRpmTorqueFactor", &vehicle_info::min_rpm_torque_factor);
    Utype.set("MaxRpmTorqueFactor", &vehicle_info::max_rpm_torque_factor);
    Utype.set("MinRpmResistance", &vehicle_info::min_rpm_resistance);
    Utype.set("OptRpmResistance", &vehicle_info::opt_rpm_resistance);
    Utype.set("MaxRpmResistance", &vehicle_info::max_rpm_resistance);
    Utype.set("ReverseTorqueMultiplier", &vehicle_info::reverse_torque_multiplier);
    Utype.set("ClutchSlipRpm", &vehicle_info::clutch_slip_rpm);
    Utype.set("EnlargedWheelRadius", &vehicle_info::enlarged_wheel_radius);
    Utype.set("AutobrakeSpeed", &vehicle_info::autobrake_speed);
    Utype.set("EnforcedMaxSpeed", &vehicle_info::enforced_max_speed);
    Utype.set("AiEnforcedMaxSpeed", &vehicle_info::ai_enforced_max_speed);
    Utype.set("EnforcedMaxRspeed", &vehicle_info::enforced_max_rspeed);
    Utype.set("PowerslideFriction", &vehicle_info::powerslide_friction);
    Utype.set("PowerslidePower", &vehicle_info::powerslide_power);
    Utype.set("ForceAssist", &vehicle_info::force_assist);
    Utype.set("NumAxles", &vehicle_info::m_num_axles);
    Utype.set("AxleWheelInfos", sol::property([](vehicle_info& Self) {return std::ref(Self.m_axle_wheel_infos); })); 
    Utype.set("ExhaustTagId", sol::property([](vehicle_info& Self) {return std::ref(Self.m_exhaust_tag_id); }));
    Utype.set("TransInfo", &vehicle_info::trans_info); 
    Utype.set("MaxSteeringAngle", &vehicle_info::max_steering_angle);
    Utype.set("MaxSpeedSteeringAngle", &vehicle_info::max_speed_steering_angle);
    Utype.set("AiMaxSpeedSteeringAngle", &vehicle_info::ai_max_speed_steering_angle);
    Utype.set("SteeringWheelMaxSpeed", &vehicle_info::m_steering_wheel_max_speed);
    Utype.set("SteeringWheelMaxReturnSpeed", &vehicle_info::m_steering_wheel_max_return_speed);
    Utype.set("SteeringWheelDampAngle", &vehicle_info::m_steering_wheel_damp_angle);
    Utype.set("SteeringWheelReturnDampAngle", &vehicle_info::m_steering_wheel_return_damp_angle);
    Utype.set("CounterSteerMinSpeed", &vehicle_info::counter_steer_min_speed);
    Utype.set("CounterSteerMaxSpeed", &vehicle_info::counter_steer_max_speed);
    Utype.set("AirSteerRollMaxVel", &vehicle_info::air_steer_roll_max_vel);
    Utype.set("AirSteerRollMaxAngleRad", &vehicle_info::air_steer_roll_max_angle_rad);
    Utype.set("AirSteerPitchMaxVel", &vehicle_info::air_steer_pitch_max_vel);
    Utype.set("AirSteerPitchMaxAngleRad", &vehicle_info::air_steer_pitch_max_angle_rad);
    Utype.set("MinPedalInputToBlock", &vehicle_info::min_pedal_input_to_block);
    Utype.set("MinTimeToBlock", &vehicle_info::min_time_to_block);
    Utype.set("AiMinTimeToBlock", &vehicle_info::ai_min_time_to_block);
    Utype.set("AirDensity", &vehicle_info::air_density);
    Utype.set("FrontalArea", &vehicle_info::frontal_area);
    Utype.set("DragCoefficient", &vehicle_info::drag_coefficient);
    Utype.set("LiftCoefficient", &vehicle_info::lift_coefficient);
    Utype.set("ExtraGravity", &vehicle_info::extra_gravity);
    Utype.set("CenterOfMassY", &vehicle_info::center_of_mass_y);
    Utype.set("CenterOfMassZ", &vehicle_info::center_of_mass_z);
    Utype.set("CameraSettings", sol::property([](vehicle_info& Self) {return std::ref(Self.camera_settings); }));
    Utype.set("CameraSettingsCount", &vehicle_info::camera_settings_count);
    Utype.set("EnergyScale", &vehicle_info::m_energy_scale);
    Utype.set("CollisionMassScalar", &vehicle_info::m_collision_mass_scalar);
    Utype.set("CollisionDamageScale", &vehicle_info::m_collision_damage_scale);
    Utype.set("TerrainDamageScale", &vehicle_info::m_terrain_damage_scale);
    Utype.set("BulletDamageScale", &vehicle_info::m_bullet_damage_scale);
    Utype.set("VehicleDamageScale", &vehicle_info::m_vehicle_damage_scale);
    Utype.set("FrictionEqualizer", &vehicle_info::m_friction_equalizer);
    Utype.set("AiFrictionEqualizer", &vehicle_info::m_ai_friction_equalizer);
    Utype.set("TorqueRollFactor", &vehicle_info::m_torque_roll_factor);
    Utype.set("TorquePitchFactor", &vehicle_info::m_torque_pitch_factor);
    Utype.set("TorqueYawFactor", &vehicle_info::m_torque_yaw_factor);
    Utype.set("TorqueYawScalar", &vehicle_info::m_torque_yaw_scalar);
    Utype.set("ExtraTorqueFactor", &vehicle_info::m_extra_torque_factor);
    Utype.set("ChassisUnitInertiaRoll", &vehicle_info::m_chassis_unit_inertia_roll);
    Utype.set("ChassisUnitInertiaPitch", &vehicle_info::m_chassis_unit_inertia_pitch);
    Utype.set("ChassisUnitInertiaYaw", &vehicle_info::m_chassis_unit_inertia_yaw);
    Utype.set("AiChassisUnitInertiaYaw", &vehicle_info::m_ai_chassis_unit_inertia_yaw);
    Utype.set("ViscosityFriction", &vehicle_info::m_viscosity_friction);
    Utype.set("AiMaxBrakingDecel", &vehicle_info::m_ai_max_braking_decel);
    Utype.set("AiMaxRadialAccel", &vehicle_info::m_ai_max_radial_accel);
    Utype.set("AlertMultiplier", &vehicle_info::m_alert_multiplier);
    Utype.set("FoleyStart", &vehicle_info::foley_start);
    Utype.set("EngineId", &vehicle_info::engine_id);
    Utype.set("EngineWavebankId", &vehicle_info::engine_wavebank_id);
    Utype.set("FoleyOff", &vehicle_info::foley_off);
    Utype.set("FoleyEnginePeel", &vehicle_info::foley_engine_peel);
    Utype.set("FoleyShift", &vehicle_info::foley_shift);
    Utype.set("FoleyGrind", &vehicle_info::foley_grind);
    Utype.set("FoleyHonk", &vehicle_info::foley_honk);
    Utype.set("FoleyImpactId", sol::property([](vehicle_info& Self) {return std::ref(Self.m_foley_impact_id); }));
    Utype.set("FoleyScrapingId", &vehicle_info::m_foley_scraping_id);
    Utype.set("FoleyCorpseImpactId", &vehicle_info::m_foley_corpse_impact_id);
    Utype.set("FoleyComponentImpactId", &vehicle_info::m_foley_component_impact_id);
    Utype.set("FoleyWheelImpactId", &vehicle_info::m_foley_wheel_impact_id);
    Utype.set("FoleyChassisLandId", sol::property([](vehicle_info& Self) {return std::ref(Self.m_foley_chassis_land_id); }));
    Utype.set("FoleyPassBy", &vehicle_info::m_foley_pass_by);
    Utype.set("FoleyDoorOpenId", &vehicle_info::m_foley_door_open_id);
    Utype.set("FoleyDoorCloseId", &vehicle_info::m_foley_door_close_id);
    Utype.set("EffectEngineFire", &vehicle_info::m_effect_engine_fire);
    Utype.set("EffectEngineSmoke", &vehicle_info::m_effect_engine_smoke);
    Utype.set("EffectCorpseSmoke", &vehicle_info::m_effect_corpse_smoke);
    Utype.set("EffectComponentFire", &vehicle_info::m_effect_component_fire);
    Utype.set("EffectExhaustNormal", &vehicle_info::m_effect_exhaust_normal);
    Utype.set("EffectExhaustBurst", &vehicle_info::m_effect_exhaust_burst);
    Utype.set("EffectCollision", &vehicle_info::m_effect_collision);
    Utype.set("EffectScrape", &vehicle_info::m_effect_scrape);
    Utype.set("EffectComponentDetach", &vehicle_info::m_effect_component_detach);
    Utype.set("EffectHeadLightPrimary", &vehicle_info::m_effect_head_light_primary);
    Utype.set("EffectHeadLightSecondary", &vehicle_info::m_effect_head_light_secondary);
    Utype.set("EffectFogLight", &vehicle_info::m_effect_fog_light);
    Utype.set("EffectTailLight", &vehicle_info::m_effect_tail_light);
    Utype.set("EffectBrakeLight", &vehicle_info::m_effect_brake_light);
    Utype.set("EffectReverseLight", &vehicle_info::m_effect_reverse_light);
    Utype.set("EffectEmergencyLight", &vehicle_info::m_effect_emergency_light);
    Utype.set("EffectStrobeLight", &vehicle_info::m_effect_strobe_light);
    Utype.set("ExplosionInfo", &vehicle_info::m_explosion_info);
    Utype.set("BombExplosionInfo", &vehicle_info::m_bomb_explosion_info);
    Utype.set("NumVariants", &vehicle_info::m_num_variants);
    Utype.set("NormalSpinDamping", &vehicle_info::m_normal_spin_damping);
    Utype.set("NormalSpinDampingAi", &vehicle_info::m_normal_spin_damping_ai);
    Utype.set("CollisionSpinDamping", &vehicle_info::m_collision_spin_damping);
    Utype.set("CollisionSpinThreshold", &vehicle_info::m_collision_spin_threshold);
    Utype.set("CameraFovMultiplier", &vehicle_info::m_camera_fov_multiplier);
    Utype.set("CameraFovMinSpeed", &vehicle_info::m_camera_fov_min_speed);
    Utype.set("CameraShakeMinSpeed", &vehicle_info::m_camera_shake_min_speed);
    Utype.set("RadialBlurMax", &vehicle_info::m_radial_blur_max);
    Utype.set("RadialBlurMinSpeed", &vehicle_info::m_radial_blur_min_speed);
    Utype.set("TrailerChance", &vehicle_info::m_trailer_chance);
    Utype.set("RigName", &vehicle_info::rig_name);
    Utype.set("AnimSetName", &vehicle_info::anim_set_name);
    Utype.set("FootstepEffects", &vehicle_info::footstep_effects);
    //Utype.set("BonesUsedInfo", &vehicle_info::bones_used_info); //Has ptr array, need wrapper to handle those
    Utype.set("FlyerMaxUpThrust", &vehicle_info::flyer_max_up_thrust);
    Utype.set("FlyerMaxTurnAngVel", &vehicle_info::flyer_max_turn_angvel);
    Utype.set("FlyerMaxTurnAngAccel", &vehicle_info::flyer_max_turn_angaccl);
    Utype.set("FlyerMaxThrustOffsetX", &vehicle_info::flyer_max_thrust_offset_x);
    Utype.set("FlyerMaxThrustOffsetZ", &vehicle_info::flyer_max_thrust_offset_z);
    Utype.set("FlyerMaxTiltAngvel", &vehicle_info::flyer_max_tilt_angvel);
    Utype.set("FlyerMaxTiltAngaccl", &vehicle_info::flyer_max_tilt_angaccl);
    Utype.set("FlyerSpinBankScalar", &vehicle_info::flyer_spin_bank_scalar);
    Utype.set("FlyerThrustTiltScalar", &vehicle_info::flyer_thrust_tilt_scalar);
    Utype.set("FlyerBankTiltScalar", &vehicle_info::flyer_bank_tilt_scalar);
    Utype.set("FlyerDefLookatYScalar", &vehicle_info::flyer_def_lookat_y_scalar);
    Utype.set("FlyerWingtipEffect", &vehicle_info::flyer_wingtip_effect);
    Utype.set("FlyerThrusterEffect", &vehicle_info::flyer_thruster_effect);
    Utype.set("FlyerMainEngineEffect", &vehicle_info::flyer_mainengine_effect);
    Utype.set("FlyerJetwashEffect", &vehicle_info::flyer_jetwash_effect);
    Utype.set("Flags", &vehicle_info::flags);
    RfgTable.set_usertype("VehicleInfo", Utype);
#endif
}
