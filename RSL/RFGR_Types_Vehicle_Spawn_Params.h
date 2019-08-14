#pragma once
#include "RFGR_Types_Havok.h"
#include <ostream>

enum object_spawn_priority
{
    SPAWN_PRIORITY_INVALID = 0xFFFFFFFF,
    SPAWN_PRIORITY_LOW = 0x0,
    SPAWN_PRIORITY_MEDIUM = 0x1,
    SPAWN_PRIORITY_HIGH = 0x2,
    SPAWN_PRIORITY_SPECIAL = 0x3,
    NUM_SPAWN_PRIORITIES = 0x4,
};

enum spawn_status_result
{
    INVALID_SPAWN_STATUS_RESULT = 0xFFFFFFFF,
    SPAWN_STATUS_SUCCESS = 0x0,
    SPAWN_STATUS_STREAMING = 0x1,
    SPAWN_STATUS_FAILURE = 0x2,
    NUM_SPAWN_STATUS = 0x3,
};

struct vehicle_spawn_flags
{
    unsigned __int32 high_priority : 1;
    unsigned __int32 mobile_spawn : 1;
    unsigned __int32 static_placement : 1;
    unsigned __int32 snap_to_ground : 1;
    unsigned __int32 road_spawn : 1;
};

struct vehicle_rdd_flags
{
    __int8 m_pos_on_ground_for_create : 1;
    __int8 m_hide_vehicle : 1;
};

struct vehicle_info_turret_mount_info
{
    const char* name;
    const char* prop_point;
    VehicleSeatIndex seat;
    unsigned int flags;
    void* attached_turret_info; //turret_info* attached_turret_info;
};

struct vehicle_info_axle_wheel_info
{
    bool does_steer;
    bool does_handbrake;
    float engine_torque_factor;
    float mass;
    float friction;
    float ai_friction;
    float braking_torque;
    float spring_compression;
    float spring_extension;
    float spring_strength;
    float spring_power;
    float compression_damping;
    float expansion_damping;
};

struct vehicle_info_transmission_info
{
    friend std::ostream& operator<<(std::ostream& os, const vehicle_info_transmission_info& obj)
    {
        return os
            << "num_gears: " << obj.num_gears
            << "differential_gear_ratio: " << obj.differential_gear_ratio
            << "reverse_gear_ratio: " << obj.reverse_gear_ratio
            << "clutch_delay: " << obj.clutch_delay
            << "clutch_delay_pre_shift: " << obj.clutch_delay_pre_shift
            << "forward_to_reverse_delay: " << obj.forward_to_reverse_delay
            << "reverse_to_forward_delay: " << obj.reverse_to_forward_delay;
    }

    unsigned int num_gears;
    float gear_ratios[6];
    float downshift_rpms[5];
    float upshift_rpms[5];
    float differential_gear_ratio;
    float reverse_gear_ratio;
    float clutch_delay;
    float clutch_delay_pre_shift;
    unsigned int forward_to_reverse_delay;
    unsigned int reverse_to_forward_delay;
};

struct  __declspec(align(4)) vehicle_camera_settings
{
    vector lookat_offset;
    vector lookat_vehicle_offset;
    vector lookat_vehicle_enter_offset;
    float lookfrom_height;
    float enter_distance;
    float follow_dist;
    float follow_height;
    float y_axis_rotation_speed;
    float camera_steer_angle;
    float camera_steer_speed;
    bool turret_camera;
    bool force_turret_cam;
};

struct vehicle_info_flags
{
    friend std::ostream& operator<<(std::ostream& os, const vehicle_info_flags& obj)
    {
        return os
            << "\npreload: " << obj.preload
            << "\ncan_block_roads: " << obj.can_block_roads
            << "\nforce_break_links: " << obj.force_break_links
            << "\nseat_count_warning: " << obj.seat_count_warning
            << "\nis_walker_flamer: " << obj.is_walker_flamer;
    }

    __int8 preload : 1;
    __int8 can_block_roads : 1;
    __int8 force_break_links : 1;
    __int8 seat_count_warning : 1;
    __int8 is_walker_flamer : 1;
};

struct animlib_bones_used_info
{
    friend std::ostream& operator<<(std::ostream& os, const animlib_bones_used_info& obj)
    {
        return os
            << "\nunique_id: " << obj.unique_id
            << "\nnum_bones: " << obj.num_bones
            << "\nbone_indices: " << obj.bone_indices;
    }

    int unique_id;
    int num_bones;
    unsigned int* bone_indices;
};

enum vehicle_road_preference
{
    VRP_NONE = 0x0,
    VRP_HIGHWAY = 0x1,
    VRP_NO_HIGHWAY = 0x2,
    NUM_VEHICLE_ROAD_PREFERENCE_TYPES = 0x3,
};

enum vehicle_class_type
{
    VCL_AUTOMOBILE = 0x0,
    VCL_FLYER = 0x1,
    VCL_WALKER = 0x2,
    NUM_VEHICLE_CLASSES = 0x3,
};

enum base_vehicle_types
{
    BVT_INVALID = 0xFFFFFFFF,
    BVT_NONE = 0x0,
    BVT_COURIER = 0x1,
    BVT_AMBULANCE = 0x2,
    BVT_TANK = 0x3,
    BVT_ART_TANK = 0x4,
    BVT_BOMBER = 0x5,
    BVT_SPECIAL = 0x6,
    NUM_BASE_VEHICLE_TYPES = 0x7,
};

struct lod_info
{
    friend std::ostream& operator<<(std::ostream& os, const lod_info& obj)
    {
        return os << "\ndist: " << obj.dist;
    }

    float dist;
};

const struct  __declspec(align(4)) vehicle_info
{
    friend std::ostream& operator<<(std::ostream& os, const vehicle_info& obj)
    {
        return os
            << "\nname: " << obj.name
            << "\ndisplay_name: " << obj.display_name
            << "\nmesh_name: " << obj.mesh_name
            << "\nvehicle_class: " << obj.vehicle_class
            << "\nspawn_size: " << obj.spawn_size
            << "\nspawn_box: " << obj.spawn_box
            << "\ncover_info: " << obj.cover_info
            << "\nslot_id: " << obj.slot_id
            << "\nsrid: " << obj.srid
            << "\nvariant_family: " << obj.variant_family
            << "\nvehicle_classification: " << obj.vehicle_classification
            << "\ndefault_team: " << obj.default_team
            << "\nvi_info: " << obj.vi_info
            << "\nm_max_hitpoints: " << obj.m_max_hitpoints
            << "\nm_abandon_hitpoints: " << obj.m_abandon_hitpoints
            << "\nchassis_mass: " << obj.chassis_mass
            << "\nm_value: " << obj.m_value
            << "\nm_chop_shop_props: " << obj.m_chop_shop_props
            << "\nm_num_lods: " << obj.m_num_lods
            << "\nnum_turret_mounts: " << obj.num_turret_mounts
            << "\nm_road_preference: " << obj.m_road_preference
            << "\nengine_torque: " << obj.engine_torque
            << "\nai_engine_torque: " << obj.ai_engine_torque
            << "\nmin_rpm: " << obj.min_rpm
            << "\noptimal_rpm: " << obj.optimal_rpm
            << "\nmax_rpm: " << obj.max_rpm
            << "\nmin_rpm_torque_factor: " << obj.min_rpm_torque_factor
            << "\nmax_rpm_torque_factor: " << obj.max_rpm_torque_factor
            << "\nmin_rpm_resistance: " << obj.min_rpm_resistance
            << "\nopt_rpm_resistance: " << obj.opt_rpm_resistance
            << "\nmax_rpm_resistance: " << obj.max_rpm_resistance
            << "\nreverse_torque_multiplier: " << obj.reverse_torque_multiplier
            << "\nclutch_slip_rpm: " << obj.clutch_slip_rpm
            << "\nenlarged_wheel_radius: " << obj.enlarged_wheel_radius
            << "\nautobrake_speed: " << obj.autobrake_speed
            << "\nenforced_max_speed: " << obj.enforced_max_speed
            << "\nai_enforced_max_speed: " << obj.ai_enforced_max_speed
            << "\nenforced_max_rspeed: " << obj.enforced_max_rspeed
            << "\npowerslide_friction: " << obj.powerslide_friction
            << "\npowerslide_power: " << obj.powerslide_power
            << "\nforce_assist: " << obj.force_assist
            << "\nm_num_axles: " << obj.m_num_axles
            << "\ntrans_info: " << obj.trans_info
            << "\nmax_steering_angle: " << obj.max_steering_angle
            << "\nmax_speed_steering_angle: " << obj.max_speed_steering_angle
            << "\nai_max_speed_steering_angle: " << obj.ai_max_speed_steering_angle
            << "\nm_steering_wheel_max_speed: " << obj.m_steering_wheel_max_speed
            << "\nm_steering_wheel_max_return_speed: " << obj.m_steering_wheel_max_return_speed
            << "\nm_steering_wheel_damp_angle: " << obj.m_steering_wheel_damp_angle
            << "\nm_steering_wheel_return_damp_angle: " << obj.m_steering_wheel_return_damp_angle
            << "\ncounter_steer_min_speed: " << obj.counter_steer_min_speed
            << "\ncounter_steer_max_speed: " << obj.counter_steer_max_speed
            << "\nair_steer_roll_max_vel: " << obj.air_steer_roll_max_vel
            << "\nair_steer_roll_max_angle_rad: " << obj.air_steer_roll_max_angle_rad
            << "\nair_steer_pitch_max_vel: " << obj.air_steer_pitch_max_vel
            << "\nair_steer_pitch_max_angle_rad: " << obj.air_steer_pitch_max_angle_rad
            << "\nmin_pedal_input_to_block: " << obj.min_pedal_input_to_block
            << "\nmin_time_to_block: " << obj.min_time_to_block
            << "\nai_min_time_to_block: " << obj.ai_min_time_to_block
            << "\nair_density: " << obj.air_density
            << "\nfrontal_area: " << obj.frontal_area
            << "\ndrag_coefficient: " << obj.drag_coefficient
            << "\nlift_coefficient: " << obj.lift_coefficient
            << "\nextra_gravity: " << obj.extra_gravity
            << "\ncenter_of_mass_y: " << obj.center_of_mass_y
            << "\ncenter_of_mass_z: " << obj.center_of_mass_z
            << "\ncamera_settings_count: " << obj.camera_settings_count
            << "\nm_energy_scale: " << obj.m_energy_scale
            << "\nm_collision_mass_scalar: " << obj.m_collision_mass_scalar
            << "\nm_collision_damage_scale: " << obj.m_collision_damage_scale
            << "\nm_terrain_damage_scale: " << obj.m_terrain_damage_scale
            << "\nm_bullet_damage_scale: " << obj.m_bullet_damage_scale
            << "\nm_vehicle_damage_scale: " << obj.m_vehicle_damage_scale
            << "\nm_friction_equalizer: " << obj.m_friction_equalizer
            << "\nm_ai_friction_equalizer: " << obj.m_ai_friction_equalizer
            << "\nm_torque_roll_factor: " << obj.m_torque_roll_factor
            << "\nm_torque_pitch_factor: " << obj.m_torque_pitch_factor
            << "\nm_torque_yaw_factor: " << obj.m_torque_yaw_factor
            << "\nm_torque_yaw_scalar: " << obj.m_torque_yaw_scalar
            << "\nm_extra_torque_factor: " << obj.m_extra_torque_factor
            << "\nm_chassis_unit_inertia_roll: " << obj.m_chassis_unit_inertia_roll
            << "\nm_chassis_unit_inertia_pitch: " << obj.m_chassis_unit_inertia_pitch
            << "\nm_chassis_unit_inertia_yaw: " << obj.m_chassis_unit_inertia_yaw
            << "\nm_ai_chassis_unit_inertia_yaw: " << obj.m_ai_chassis_unit_inertia_yaw
            << "\nm_viscosity_friction: " << obj.m_viscosity_friction
            << "\nm_ai_max_braking_decel: " << obj.m_ai_max_braking_decel
            << "\nm_ai_max_radial_accel: " << obj.m_ai_max_radial_accel
            << "\nm_alert_multiplier: " << obj.m_alert_multiplier
            << "\nfoley_start: " << obj.foley_start
            << "\nengine_id: " << obj.engine_id
            << "\nengine_wavebank_id: " << obj.engine_wavebank_id
            << "\nfoley_off: " << obj.foley_off
            << "\nfoley_engine_peel: " << obj.foley_engine_peel
            << "\nfoley_shift: " << obj.foley_shift
            << "\nfoley_grind: " << obj.foley_grind
            << "\nfoley_honk: " << obj.foley_honk
            << "\nm_foley_scraping_id: " << obj.m_foley_scraping_id
            << "\nm_foley_corpse_impact_id: " << obj.m_foley_corpse_impact_id
            << "\nm_foley_component_impact_id: " << obj.m_foley_component_impact_id
            << "\nm_foley_wheel_impact_id: " << obj.m_foley_wheel_impact_id
            << "\nm_foley_pass_by: " << obj.m_foley_pass_by
            << "\nm_foley_door_open_id: " << obj.m_foley_door_open_id
            << "\nm_foley_door_close_id: " << obj.m_foley_door_close_id
            << "\nm_effect_engine_fire: " << obj.m_effect_engine_fire
            << "\nm_effect_engine_smoke: " << obj.m_effect_engine_smoke
            << "\nm_effect_corpse_smoke: " << obj.m_effect_corpse_smoke
            << "\nm_effect_component_fire: " << obj.m_effect_component_fire
            << "\nm_effect_exhaust_normal: " << obj.m_effect_exhaust_normal
            << "\nm_effect_exhaust_burst: " << obj.m_effect_exhaust_burst
            << "\nm_effect_collision: " << obj.m_effect_collision
            << "\nm_effect_scrape: " << obj.m_effect_scrape
            << "\nm_effect_component_detach: " << obj.m_effect_component_detach
            << "\nm_effect_head_light_primary: " << obj.m_effect_head_light_primary
            << "\nm_effect_head_light_secondary: " << obj.m_effect_head_light_secondary
            << "\nm_effect_fog_light: " << obj.m_effect_fog_light
            << "\nm_effect_tail_light: " << obj.m_effect_tail_light
            << "\nm_effect_brake_light: " << obj.m_effect_brake_light
            << "\nm_effect_reverse_light: " << obj.m_effect_reverse_light
            << "\nm_effect_emergency_light: " << obj.m_effect_emergency_light
            << "\nm_effect_strobe_light: " << obj.m_effect_strobe_light
            << "\nm_explosion_info: " << obj.m_explosion_info
            << "\nm_bomb_explosion_info: " << obj.m_bomb_explosion_info
            << "\nm_num_variants: " << obj.m_num_variants
            << "\nm_normal_spin_damping: " << obj.m_normal_spin_damping
            << "\nm_normal_spin_damping_ai: " << obj.m_normal_spin_damping_ai
            << "\nm_collision_spin_damping: " << obj.m_collision_spin_damping
            << "\nm_collision_spin_threshold: " << obj.m_collision_spin_threshold
            << "\nm_camera_fov_multiplier: " << obj.m_camera_fov_multiplier
            << "\nm_camera_fov_min_speed: " << obj.m_camera_fov_min_speed
            << "\nm_camera_shake_min_speed: " << obj.m_camera_shake_min_speed
            << "\nm_radial_blur_max: " << obj.m_radial_blur_max
            << "\nm_radial_blur_min_speed: " << obj.m_radial_blur_min_speed
            << "\nm_trailer_chance: " << obj.m_trailer_chance
            << "\nrig_name: " << obj.rig_name
            << "\nanim_set_name: " << obj.anim_set_name
            << "\nfootstep_effects: " << obj.footstep_effects
            << "\nbones_used_info: " << obj.bones_used_info
            << "\nflyer_max_up_thrust: " << obj.flyer_max_up_thrust
            << "\nflyer_max_turn_angvel: " << obj.flyer_max_turn_angvel
            << "\nflyer_max_turn_angaccl: " << obj.flyer_max_turn_angaccl
            << "\nflyer_max_thrust_offset_x: " << obj.flyer_max_thrust_offset_x
            << "\nflyer_max_thrust_offset_z: " << obj.flyer_max_thrust_offset_z
            << "\nflyer_max_tilt_angvel: " << obj.flyer_max_tilt_angvel
            << "\nflyer_max_tilt_angaccl: " << obj.flyer_max_tilt_angaccl
            << "\nflyer_spin_bank_scalar: " << obj.flyer_spin_bank_scalar
            << "\nflyer_thrust_tilt_scalar: " << obj.flyer_thrust_tilt_scalar
            << "\nflyer_bank_tilt_scalar: " << obj.flyer_bank_tilt_scalar
            << "\nflyer_def_lookat_y_scalar: " << obj.flyer_def_lookat_y_scalar
            << "\nflyer_wingtip_effect: " << obj.flyer_wingtip_effect
            << "\nflyer_thruster_effect: " << obj.flyer_thruster_effect
            << "\nflyer_mainengine_effect: " << obj.flyer_mainengine_effect
            << "\nflyer_jetwash_effect: " << obj.flyer_jetwash_effect
            << "\nflags: " << obj.flags;
    }

    const char* name;
    const char* display_name;
    const char* mesh_name;
    vehicle_class_type vehicle_class;
    float spawn_size;
    bbox spawn_box;
    void* cover_info; //vehicle_cover_info* cover_info;
    int slot_id;
    unsigned int srid;
    const char* variant_family;
    base_vehicle_types vehicle_classification;
    HumanTeams default_team;
    void* vi_info; //vehicle_interaction_info* vi_info;
    unsigned int m_max_hitpoints;
    int m_abandon_hitpoints;
    float chassis_mass;
    float m_value;
    unsigned int m_chop_shop_props;
    unsigned int m_num_lods;
    lod_info m_lod_info[4];
    int num_turret_mounts;
    vehicle_info_turret_mount_info turret_mounts[2];
    vehicle_road_preference m_road_preference;
    float engine_torque;
    float ai_engine_torque;
    float min_rpm;
    float optimal_rpm;
    float max_rpm;
    float min_rpm_torque_factor;
    float max_rpm_torque_factor;
    float min_rpm_resistance;
    float opt_rpm_resistance;
    float max_rpm_resistance;
    float reverse_torque_multiplier;
    float clutch_slip_rpm;
    float enlarged_wheel_radius;
    float autobrake_speed;
    float enforced_max_speed;
    float ai_enforced_max_speed;
    float enforced_max_rspeed;
    float powerslide_friction;
    float powerslide_power;
    float force_assist;
    unsigned int m_num_axles;
    vehicle_info_axle_wheel_info m_axle_wheel_infos[4];
    int m_exhaust_tag_id[4];
    vehicle_info_transmission_info trans_info;
    float max_steering_angle;
    float max_speed_steering_angle;
    float ai_max_speed_steering_angle;
    float m_steering_wheel_max_speed;
    float m_steering_wheel_max_return_speed;
    float m_steering_wheel_damp_angle;
    float m_steering_wheel_return_damp_angle;
    float counter_steer_min_speed;
    float counter_steer_max_speed;
    float air_steer_roll_max_vel;
    float air_steer_roll_max_angle_rad;
    float air_steer_pitch_max_vel;
    float air_steer_pitch_max_angle_rad;
    float min_pedal_input_to_block;
    float min_time_to_block;
    float ai_min_time_to_block;
    float air_density;
    float frontal_area;
    float drag_coefficient;
    float lift_coefficient;
    float extra_gravity;
    float center_of_mass_y;
    float center_of_mass_z;
    vehicle_camera_settings camera_settings[3];
    int camera_settings_count;
    float m_energy_scale;
    float m_collision_mass_scalar;
    float m_collision_damage_scale;
    float m_terrain_damage_scale;
    float m_bullet_damage_scale;
    float m_vehicle_damage_scale;
    float m_friction_equalizer;
    float m_ai_friction_equalizer;
    float m_torque_roll_factor;
    float m_torque_pitch_factor;
    float m_torque_yaw_factor;
    float m_torque_yaw_scalar;
    float m_extra_torque_factor;
    float m_chassis_unit_inertia_roll;
    float m_chassis_unit_inertia_pitch;
    float m_chassis_unit_inertia_yaw;
    float m_ai_chassis_unit_inertia_yaw;
    float m_viscosity_friction;
    float m_ai_max_braking_decel;
    float m_ai_max_radial_accel;
    float m_alert_multiplier;
    int foley_start;
    int engine_id;
    __int16 engine_wavebank_id;
    int foley_off;
    int foley_engine_peel;
    int foley_shift;
    int foley_grind;
    int foley_honk;
    int m_foley_impact_id[2];
    int m_foley_scraping_id;
    int m_foley_corpse_impact_id;
    int m_foley_component_impact_id;
    int m_foley_wheel_impact_id;
    int m_foley_chassis_land_id[2];
    int m_foley_pass_by;
    int m_foley_door_open_id;
    int m_foley_door_close_id;
    unsigned int m_effect_engine_fire;
    unsigned int m_effect_engine_smoke;
    unsigned int m_effect_corpse_smoke;
    unsigned int m_effect_component_fire;
    unsigned int m_effect_exhaust_normal;
    unsigned int m_effect_exhaust_burst;
    unsigned int m_effect_collision;
    unsigned int m_effect_scrape;
    unsigned int m_effect_component_detach;
    unsigned int m_effect_head_light_primary;
    unsigned int m_effect_head_light_secondary;
    unsigned int m_effect_fog_light;
    unsigned int m_effect_tail_light;
    unsigned int m_effect_brake_light;
    unsigned int m_effect_reverse_light;
    unsigned int m_effect_emergency_light;
    unsigned int m_effect_strobe_light;
    explosion_info* m_explosion_info;
    explosion_info* m_bomb_explosion_info;
    unsigned int m_num_variants;
    float m_normal_spin_damping;
    float m_normal_spin_damping_ai;
    float m_collision_spin_damping;
    float m_collision_spin_threshold;
    float m_camera_fov_multiplier;
    float m_camera_fov_min_speed;
    float m_camera_shake_min_speed;
    float m_radial_blur_max;
    float m_radial_blur_min_speed;
    float m_trailer_chance;
    const char* rig_name;
    const char* anim_set_name;
    foot_ground_effects* footstep_effects;
    animlib_bones_used_info bones_used_info;
    float flyer_max_up_thrust;
    float flyer_max_turn_angvel;
    float flyer_max_turn_angaccl;
    float flyer_max_thrust_offset_x;
    float flyer_max_thrust_offset_z;
    float flyer_max_tilt_angvel;
    float flyer_max_tilt_angaccl;
    float flyer_spin_bank_scalar;
    float flyer_thrust_tilt_scalar;
    float flyer_bank_tilt_scalar;
    float flyer_def_lookat_y_scalar;
    unsigned int flyer_wingtip_effect;
    unsigned int flyer_thruster_effect;
    unsigned int flyer_mainengine_effect;
    unsigned int flyer_jetwash_effect;
    vehicle_info_flags flags;
};

struct vehicle_light_vehicle_light_flags
{
    __int8 is_on : 1;
    __int8 is_broken : 1;
    __int8 broken : 1;
    __int8 dirty : 1;
};

enum vehicle_light_type
{
    VLT_INVALID = 0xFFFFFFFF,
    VLT_HEAD_LIGHT = 0x0,
    VLT_FOG_LIGHT = 0x1,
    VLT_TAIL_LIGHT = 0x2,
    VLT_BRAKE_LIGHT = 0x3,
    VLT_REVERSE_LIGHT = 0x4,
    VLT_EMERGENCY_LIGHT = 0x5,
    VLT_STROBE_LIGHT = 0x6,
    NUM_VEHICLE_LIGHT_TYPES = 0x7,
};

struct __declspec(align(4)) vehicle_light
{
    int tag_index;
    unsigned int effect_handle;
    unsigned int coronas[3];
    unsigned int corona_effect_info_handle;
    int parent_idx;
    void* mesh_light; //vehicle_mesh_light* mesh_light;
    vehicle_light_type type;
    int mesh_index_on;
    int mesh_index_off;
    int component_mesh_index_on;
    int component_mesh_index_off;
    vehicle_light_vehicle_light_flags flags;
};

enum vehicle_component_adi_states
{
    ADI_NOT_ANIMATING = 0x0,
    ADI_BEGIN_OPENING = 0x1,
    ADI_OPENING = 0x2,
    ADI_OPENED = 0x3,
    ADI_BEGIN_CLOSING = 0x4,
    ADI_CLOSING = 0x5,
    ADI_CLOSED = 0x6,
};


struct vehicle_component_door_attr
{
    float m_t_actual;
    float m_t;
    float m_t_velocity;
    vehicle_component_adi_states m_state;
};

/* 6334 */
struct vehicle_component_tread_wheel_attr
{
    int spline_index;
    float wheel_radius;
    float wheel_rotation;
};

/* 6335 */
struct vehicle_component_suspension_attr
{
    int wheel_index;
    float pivot_pos_mag;
    float pivot_pos[3];
    float wheel_bias[3];
};

/* 6336 */
union vehicle_component_m_type_attribute_union
{
    vehicle_component_door_attr door;
    vehicle_component_tread_wheel_attr tread_wheel;
    vehicle_component_suspension_attr suspension;
};

struct  vehicle_component
{
    unsigned int havok_handle;
    hkpConstraintInstance* m_constraint;
    unsigned __int16 m_max_hit_points;
    unsigned __int16 m_hit_points;
    unsigned int m_last_hit_by_handle;
    unsigned int m_debris_object;
    unsigned int m_original_collision_filter;
    void* m_renderable_instance_p; //rl_deformable_mesh_instance* m_renderable_instance_p;
    __int16 m_renderable_instance_refs;
    __int16 m_sub_instance_idx;
    void* m_mesh_deform_pending_list; //mesh_deform_sphere_link* m_mesh_deform_pending_list;
    char m_pos_orient_deform_weight;
    char m_numb_shapes;
    bool m_type_attribute_valid;
    vehicle_component_m_type_attribute_union m_type_attribute;
    void* m_data; //vehicle_component_data* m_data;
    unsigned int m_flags;
    matrix m_ws_rotation;
    vector m_ws_position;
    matrix m_cs_rotation;
    vector m_cs_position;
};

struct vehicle_vehicle_spline_data
{
    float starting_offset_percent;
    int num_treads;
};

struct vehicle_resource_dependent_data
{
    void* sub_info; //vehicle_subinfo* sub_info;
    unsigned int m_num_components;
    vehicle_component m_components[66];
    vehicle_vehicle_spline_data spline_data[4];
    void* spline_render_update; //vehicle_spline_render_update* spline_render_update;
    unsigned int spline_debris[80];
    int track_pad_component_id;
    unsigned int m_wheel_bumper_component;
    unsigned int m_chassis_collision_component;
    unsigned int m_num_vehicle_lights;
    vehicle_light m_vehicle_lights[20];
    unsigned int m_saved_collision_filter;
    void* m_renderable_instance_p; //rl_deformable_mesh_instance* m_renderable_instance_p;
    anim_rig* rig;
    int component_bone_index[74];
};

struct  __declspec(align(8)) vehicle_vehicle_navcell_info
{
    unsigned __int64 last_visited_nav_cell_handle;
    Timestamp last_visited_nav_cell_update_timer;
};

struct cs_wrapper
{
    keen::Mutex m_mutex;
    int debug_handle;
};

struct  __declspec(align(4)) vehicle_damage_event
{
    unsigned int attacker_handle;
    void* attacker_weapon; //weapon_info* attacker_weapon;
    vector damage_position;
    vector damage_normal;
    vector damage_velocity;
    float damage_radius;
    int damage_to_apply;
    damaged_by_types from_type;
    bool from_server;
    bool damage_velocity_valid;
};

struct vehicle_collision_events
{
    __int8 m_collided_with_world : 1;
    __int8 m_collided_with_vehicle : 1;
    __int8 m_collided_with_mover : 1;
};

enum vehicle_bomb_status
{
    VEHICLE_BOMB_NONE = 0x0,
    VEHICLE_BOMB_ARMED = 0x1,
};

struct vehicle_seat_info
{
    unsigned int m_current_occupant_handle;
};

struct vehicle_turret_mount
{
    void* info; //vehicle_info::turret_mount_info* info;
    unsigned int attached_turret;
};

enum vehicle_ai_state
{
    VS_AI_NONE = 0xFFFFFFFF,
    VS_AI_IDLE = 0x0,
    VS_AI_PATHFIND = 0x1,
    NUM_VEHICLE_AI_STATES = 0x2,
};

struct vehicle_ai_flags
{
    __int8 m_ignore_repulsors : 1;
    __int8 m_goal_stop_override : 1;
    __int8 m_override_speed : 1;
    __int8 m_override_stop : 1;
    __int8 m_force_stop_reverse : 1;
    __int8 m_follow_pathfinding : 1;
    __int8 m_lateral_offset : 1;
    __int8 m_road_offset : 1;
    __int8 m_unstick_reverse : 1;
    __int8 m_jumping : 1;
    __int8 m_should_not_swerve : 1;
    __int8 m_ignore_lanes : 1;
    __int8 m_ignore_road_directionality : 1;
    __int8 left_side : 1;
    __int8 middle : 1;
    __int8 fallen_off_navmesh : 1;
    __int8 pull_off : 1;
    __int8 at_end_of_route : 1;
    __int8 use_special_roads : 1;
    __int8 need_to_rise : 1;
    __int8 obstructed_by_player : 1;
    __int8 u_turn_active : 1;
    __int8 slowing_for_u_turn : 1;
    __int8 turning : 1;
    __int8 turning_in_place : 1;
    __int8 backing_up : 1;
    __int8 is_courier : 1;
    __int8 is_riding_shotgun : 1;
};

enum clear_debris_states
{
    CDS_DONT = 0x0,
    CDS_DAMAGE1 = 0x1,
    CDS_DAMAGE2 = 0x2,
    CDS_DAMAGE3 = 0x3,
    CDS_DELETE = 0x4,
    NUM_CLEAR_DEBRIS_STATES = 0x5,
};

struct  stuck_info
{
    timestamp stuck_threshold_time;
    timestamp stuck_active_time;
    timestamp stuck_clear_time;
    vector stuck_pos;
    timestamp extended_stuck_time;
    float stuck_mass;
    timestamp stuck_mass_timer;
    clear_debris_states clear_debris_state;
    timestamp clear_debris_timer;
};

struct  repulsor_lateral_info
{
    plane plane_left;
    plane plane_right;
    plane box_left;
    plane box_right;
    plane box_back;
    float angle_with_fvec;
    float start_width_offset;
};

/* 6344 */
struct  vehicle_repulsor_info
{
    repulsor_lateral_info lateral_info;
    char affected_by_repulsors;
    char num_path_repulsors;
    unsigned int vpath_repulsor_handles[10];
    timestamp vpath_repulsor_time[10];
    timestamp path_repulsors_collection_time;
};

struct  vehicle_steer_info
{
    vector goal_pos;
    float curvature_goal;
    float lookahead_dist;
    float lateral_offset;
    float road_offset;
    float wheelbase;
    float inv_radius_steer;
    float vel;
    float desired_vel;
    float accel_val;
    float brake_val;
};

/* 6347 */
struct vehicle_accel_info
{
    float desired_speed;
    float desired_braking_decel;
};

/* 6348 */
struct vehicle_control_info
{
    float max_braking_decel;
    float max_radial_accel;
    float max_steer_curvature;
};

struct vehicle_route_info_data
{
    __int8 m_route_segment_inited : 1;
};

struct route_segment_route_segment_flags
{
    __int8 terminal : 1;
    __int8 from_ambient_path : 1;
    __int8 from_navmesh_path : 1;
    __int8 signal_processed : 1;
    __int8 stopped_for_sign : 1;
};

struct  cubic_bezier_spline
{
    vector* knots;
    vector* incoming_handles;
    vector* outgoing_handles;
    int num_knots;
};

struct  __declspec(align(2)) route_segment
{
    cubic_bezier_spline cb_spline;
    float length;
    float speed_limit;
    void* base_spline; //lane_spline_base* base_spline;
    __int16 num_knots_minus_one;
    route_segment_route_segment_flags flags;
};

struct vehicle_point_info
{
    int route_index;
    float u;
    float distance_remaining;
};

struct  __declspec(align(2)) vehicle_route_info
{
    route_segment route[5];
    void* last_next_spline; //lane_spline_base* last_next_spline;
    vehicle_point_info center_info;
    vehicle_point_info bumper_info;
    __int16 num_route_segments;
    vehicle_route_info_data flags;
};

struct vehicle_path_info_vehicle_path_flags
{
    __int8 jumping : 1;
    __int8 on_bridge : 1;
    __int8 partial_path : 1;
    __int8 road_spline_path : 1;
    __int8 off_road : 1;
    __int8 use_road_offset : 1;
    __int8 gps_path : 1;
    __int8 next_point_inc : 1;
    __int8 ixc_can_control : 1;
    __int8 ixc_turning : 1;
    __int8 ixc_turning_right : 1;
};

enum path_outcome
{
    PR_UNKNOWN = 0x0,
    PR_OK = 0x1,
    PR_OUT_OF_CHUNK = 0x2,
    PR_ERROR_START_NAVCELL = 0x3,
    PR_ERROR_END_NAVCELL = 0x4,
    PR_ERROR_DEGENERATE = 0x5,
    PR_ERROR_DETOUR_HULL = 0x6,
    PR_ERROR_WATER = 0x7,
    PR_ERROR_UNKNOWN = 0x8,
};

struct  __declspec(align(4)) vehicle_path_info
{
    vector start_pos;
    unsigned __int64 start_nav_cell_handle;
    vector end_pos;
    unsigned __int64 end_nav_cell_handle;
    path_outcome error_code;
    unsigned int closest_road_spline;
    float closest_road_index;
    vehicle_path_info_vehicle_path_flags flags;
};

enum vehicle_pathfind_results
{
    VPF_RESULT_SUCCESS = 0x0,
    VPF_RESULT_DELAYED = 0x1,
    VPF_RESULT_FAILURE_BAD_START = 0x2,
    VPF_RESULT_FAILURE_BAD_DESTINATION = 0x3,
    VPF_RESULT_FAILURE_NO_PATH = 0x4,
    NUM_VEHICLE_PATHFIND_RESULTS = 0x5,
};

struct  vehicle_pathfind_record
{
    vector start;
    vector dest;
    vehicle_pathfind_results result;
};

struct circ_array__vehicle_pathfind_record_5
{
    vehicle_pathfind_record data[5];
    int num;
    int offset;
};

struct  vehicle_ai
{
    vehicle_ai_state ai_state;
    vehicle_ai_state ai_last_state;
    timestamp u_turn_global_delay;
    vehicle_ai_flags vai_flags;
    float target_speed_to_goal;
    float target_decel_to_goal;
    float override_speed;
    float initial_forward_speed;
    vehicle_repulsor_info repulsor_info;
    timestamp navmesh_path_update;
    timestamp swerve_timer;
    timestamp initial_swerve_timer;
    timestamp pull_off_timer;
    stuck_info stuck;
    unsigned int vehicle_handle;
    timestamp checkpoint_timer;
    unsigned int checkpoint_handle;
    unsigned int ambient_wait_object;
    timestamp ambient_wait_timer;
    timestamp change_sides_timer;
    vehicle_steer_info steer_info;
    vehicle_accel_info accel_info;
    vehicle_control_info base_control_info;
    vehicle_control_info active_control_info;
    void* navmesh_path; //navmesh_lane_spline_node* navmesh_path;
    vehicle_route_info route_info;
    __declspec(align(8)) vehicle_path_info current_path_info;
    float flying_offset;
    float building_offset;
    float desired_flying_offset;
    float target_offset;
    float terrain_offset;
    float original_offset;
    float necessary_height;
    int update_failures;
    unsigned __int16 active_intersection_controller;
    circ_array__vehicle_pathfind_record_5 pf_failure_history;
};

enum vi_door_state
{
    VI_DOOR_STATE_CLOSED = 0x0,
    VI_DOOR_STATE_CLOSED_CLIMBING = 0x1,
    VI_DOOR_STATE_CLOSING = 0x2,
    VI_DOOR_STATE_OPEN = 0x3,
    VI_DOOR_STATE_OPENING = 0x4,
    VI_DOOR_STATE_OPEN_FOR_GUNNER = 0x5,
    NUM_VI_DOOR_STATES = 0x6,
};

struct  vi_door
{
    timestamp open_close_ts;
    int component_id;
    vi_door_state state;
    int wpi_check;
};

struct waypoint_usage
{
    __int8 human_ref : 4;
    __int8 reg_on_release : 1;
    __int8 block_type : 3;
};

class vehicle;
struct  vi_vehicle_manager
{
    vehicle* vp;
    rfg::farray<vi_door, 6> doors;
    rfg::farray<waypoint_usage, 44> used_waypoints;
};

struct vi_enter_data_flags
{
    __int8 teleport : 1;
    __int8 walk : 1;
    __int8 minimal_processing : 1;
    __int8 reserve_seat_only : 1;
    __int8 use_pf_path : 1;
    __int8 teleport_to_door : 1;
};

enum vi_seat_selection_method
{
    VI_SEAT_SELECTION_METHOD_NONE = 0xFFFFFFFF,
    VI_SEAT_SELECTION_METHOD_SPECIFIED = 0x0,
    VI_SEAT_SELECTION_METHOD_BEST = 0x1,
    NUM_VI_SEAT_SELECTION_METHODS = 0x2,
};

struct  __declspec(align(4)) vi_enter_data
{
    vehicle_seat_index specified_seat;
    vi_seat_selection_method seat_selection_method;
    vehicle_seat_index destination_seat;
    vi_enter_data_flags flags;
};

struct vi_exit_data_flags
{
    __int8 teleport : 1;
    __int8 maintain_position : 1;
    __int8 reexit : 1;
    __int8 last_exit_failed : 1;
    __int8 force_dive_exit : 1;
};

/* 6378 */
struct  vi_exit_data
{
    vi_exit_data_flags flags;
};

enum vi_interaction
{
    VI_INTERACTION_UNDEFINED = 0xFFFFFFFF,
    VI_INTERACTION_NONE = 0x0,
    VI_INTERACTION_RESERVE = 0x1,
    VI_INTERACTION_ENTER = 0x2,
    VI_INTERACTION_EXIT = 0x3,
    VI_INTERACTION_RIDE = 0x4,
    NUM_VI_INTERACTIONS = 0x5,
};

enum vi_correction_type
{
    VI_POS_CORRECTION_NONE = 0x0,
    VI_POS_CORRECTION_VEHICLE_BASH_POS = 0x1,
    VI_POS_CORRECTION_VEHICLE_VELOCITY = 0x2,
    VI_POS_CORRECTION_HUMAN_PROJECTILE = 0x3,
    NUM_VI_POS_CORRECTION_TYPES = 0x4,
};

enum vi_state_of_logic
{
    VI_STATE_NONE = 0x0,
    VI_STATE_RESERVED_SEAT = 0x1,
    VI_STATE_ENTER_PATHFIND = 0x2,
    VI_STATE_ENTER_TELEPORT_WAIT = 0x3,
    VI_STATE_ENTER_STREAMING_STALL = 0x4,
    VI_STATE_ENTER_COMPLETE = 0x5,
    VI_STATE_EXIT_PATHFIND = 0x6,
    VI_STATE_EXIT_EJECT = 0x7,
    VI_STATE_EXIT_COMPLETE = 0x8,
    NUM_VI_STATES = 0x9,
};

enum vi_state_of_anim
{
    VI_STATE_ANIM_NONE = 0x0,
    VI_STATE_ENTER_PATH_TO_DOOR = 0x1,
    VI_STATE_SHARED_WAIT_WAYPOINT_CLEAR = 0x2,
    VI_STATE_SHARED_OPEN_DOOR = 0x3,
    VI_STATE_SHARED_TRANSITION = 0x4,
    VI_STATE_RIDE_DEFAULT = 0x5,
    VI_STATE_RIDE_CLOSE_DOOR = 0x6,
    VI_STATE_RIDE_CUSTOM_ANIM = 0x7,
    NUM_VI_STATES_OF_ANIM = 0x8,
};

struct  __declspec(align(2)) vi_human_manager
{
    unsigned int handle;
    vi_interaction interaction;
    vi_correction_type pos_correction;
    vector human_motion;
    vi_state_of_logic state;
    rfg::farray<signed char, 6> path_nodes;
    char transition_idx;
    char cur_path_idx;
    char last_path_idx;
    timestamp wait_ts;
    char door_comp_idx;
    vi_state_of_anim state_of_anim;
    char animate_from_wpi;
    char animate_dest_wpi;
    int ride_state_handle;
    VehicleSeatIndex seat;
    timestamp manual_close_door_ts;
    vi_enter_data enter_data;
    vi_exit_data exit_data;
    __int8 door_idx : 4;
    __int8 reserve_next_node_only : 1;
    __int8 freeze_hands_next_frame : 1;
    __int8 being_hijacked : 1;
    __int8 use_vehicle_collision : 1;
    __int8 auto_connect_to_entry : 1;
};

struct  vi_instance
{
    vi_vehicle_manager vvm;
    char num_humans;
    rfg::farray<vi_human_manager, 8> humans;
    timestamp refresh_raycasts_timestamp;
    __int8 reregister_paths : 1;
    __int8 process_state_again : 1;
    __int8 updated_exits : 1;
    __int8 post_stream_init : 1;
    __int8 exit_mode : 4;
    __declspec(align(4)) rfg::farray<unsigned char, 11> exit_costs;
};

struct  __declspec(align(4)) object_stream_resource__vehicle_resource_dependent_data
{
    vehicle_resource_dependent_data m_data;
    bool m_loaded;
};

struct  __declspec(align(8)) vehicle : Object
{
    object_stream_resource__vehicle_resource_dependent_data rdd;
    object_spawn_priority spawn_priority;
    vehicle_info* info;
    vector last_pos;
    matrix last_orient;
    vector last_velocity;
    vector last_angular_velocity;
    float forward_velocity;
    float last_forward_velocity;
    vehicle_ai vai;
    vi_instance vii;
    int aim_handle;
    void* vp; //v_animate* vp;
    matrix43 last_anim_transform;
    Timestamp pf_failure_timeout;
    Timestamp disable_for_npc_drivers_timer;
    Timestamp no_npc_entry_timer;
    ObjectRenderDistance render_distance;
    vehicle_seat_info m_seat_info[11];
    vehicle_damage_area m_damage_areas[1];
    int m_num_turret_mounts;
    vehicle_turret_mount m_turret_mounts[2];
    vehicle_bomb_status m_bomb_status;
    vehicle_collision_events m_collisions_this_frame;
    Timestamp m_walker_velocity_hack;
    Timestamp m_walker_velocity_hack_followup;
    Timestamp m_walker_thrown_energy_scaled;
    float saved_angular_dampening;
    int walker_vehicle_collisions;
    Timestamp m_vehicle_vs_building_damage;
    vehicle_damage_event damage_events[5];
    int num_damage_events;
    cs_wrapper damage_events_cs;
    Timestamp m_corpse_timer;
    Timestamp m_corpse_absolute_longest_timer;
    Timestamp on_fire_timestamp;
    unsigned int m_corpse_effect;
    unsigned int m_exhaust_effect_normal[4];
    unsigned int m_exhaust_effect_burst[4];
    vehicle_flags m_flags;
    int m_turret_autofire_ms;
    unsigned int m_num_sub_pieces;
    vehicle_spawn_flags stream_placement_flags;
    vehicle_rdd_flags m_rdd_flags;
    unsigned int m_killer_handle;
    unsigned int most_recent_driver;
    HumanTeams team_of_most_recent_driver;
    Timestamp most_recent_driver_exit_time;
    Timestamp damage_sound_propagate_timer;
    void* m_killer_weapon; //weapon_info* m_killer_weapon;
    int ramming_damage_taken;
    float m_electrical_damage_percent;
    float damage_percent;
    unsigned __int16 damage_func_handle;
    unsigned __int16 destroy_func_handle;
    unsigned __int16 on_enter_func_handle;
    unsigned __int16 on_exit_func_handle;
    unsigned __int16 on_take_damage_handle;
    unsigned __int16 on_collision_handle;
    unsigned __int16 on_hit_ped_handle;
    unsigned int reserved_by;
    Timestamp m_sound_delay_after_explosion;
    float m_fire_damage_rate;
    float m_fire_fractional_damage;
    Timestamp m_fade_timer;
    int m_fade_time;
    unsigned int m_num_mesh_deform_spheres;
    void* m_mesh_deform_sphere_list; //mesh_deform_sphere_link* m_mesh_deform_sphere_list;
    void* m_mesh_deform_pending_list; //mesh_deform_sphere_link* m_mesh_deform_pending_list;
    char m_tag_deform_weights[32];
    vehicle_vehicle_navcell_info m_navcell_info;
    Timestamp emergency_light_timer;
    float stream_load_distance_sqr;
    float stream_unload_distance_sqr;
    int engine_inst;
    int engine_started_inst;
    Timestamp engine_high_load_start_timer;
    int pass_by_play_id;
    float pass_by_distance;
    unsigned int m_nav_cell_detour_request_handle;
    unsigned int m_nav_cell_detour_component_request_handles[8];
    unsigned int m_num_nav_cell_detour_component_request_handles;
    float last_damage_reported;
    unsigned int spawn_node_handle;
    unsigned int squad_handle;
    Timestamp vehicle_check_cover_timestamp;
    Timestamp vehicle_cover_timestamp;
    vector vehicle_cover_creation_pos;
    rfg::farray<unsigned int, 10> vehicle_cover_nodes;
    int vehicle_check_cover_index;
    int vehicle_cover_index;
    cs_wrapper component_rinstance_cs;
    bool infinite_mass;
    bool extra_mass;
    float extra_mass_value;
};

struct vehicle_spawn_params_flags
{
    vehicle_spawn_params_flags()
        : no_save(0),
          one_attempt(0),
          interior_spawn(0),
          road_spawn(0),
          high_priority_clean_up(0),
          light_clean_up(0),
          force_to_ground(0),
          air_vehicle(0),
          static_spawn_placement(0),
          convoy_vehicle_spawn(0),
          mobile_vehicle_spawn(0),
          infinite_mass(0),
          has_car_bomb(0)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const vehicle_spawn_params_flags& obj)
    {
        return os
            << "\nno_save: " << obj.no_save
            << "\none_attempt: " << obj.one_attempt
            << "\ninterior_spawn: " << obj.interior_spawn
            << "\nroad_spawn: " << obj.road_spawn
            << "\nhigh_priority_clean_up: " << obj.high_priority_clean_up
            << "\nlight_clean_up: " << obj.light_clean_up
            << "\nforce_to_ground: " << obj.force_to_ground
            << "\nair_vehicle: " << obj.air_vehicle
            << "\nstatic_spawn_placement: " << obj.static_spawn_placement
            << "\nconvoy_vehicle_spawn: " << obj.convoy_vehicle_spawn
            << "\nmobile_vehicle_spawn: " << obj.mobile_vehicle_spawn
            << "\ninfinite_mass: " << obj.infinite_mass
            << "\nhas_car_bomb: " << obj.has_car_bomb;
    }

    unsigned __int32 no_save : 1;
    unsigned __int32 one_attempt : 1;
    unsigned __int32 interior_spawn : 1;
    unsigned __int32 road_spawn : 1;
    unsigned __int32 high_priority_clean_up : 1;
    unsigned __int32 light_clean_up : 1;
    unsigned __int32 force_to_ground : 1;
    unsigned __int32 air_vehicle : 1;
    unsigned __int32 static_spawn_placement : 1;
    unsigned __int32 convoy_vehicle_spawn : 1;
    unsigned __int32 mobile_vehicle_spawn : 1;
    unsigned __int32 infinite_mass : 1;
    unsigned __int32 has_car_bomb : 1;
};

struct object_spawn_region_flags
{
    __int8 disabled : 1;
    __int8 npc_only : 1;
    __int8 vehicle_only : 1;
    __int8 cont_attack_region : 1;
    __int8 vrail_spawn_region : 1;
};

enum stream2_status_val
{
    ST_UNLOADED = 0x0,
    ST_LOADING = 0x1,
    ST_ABORTING = 0x2,
    ST_LOADED = 0x3,
    ST_ERROR = 0x4,
};

struct  __declspec(align(4)) object_spawn_region : Object
{
    bbox local_bb;
    bbox bb;
    bbox near_bb;
    HumanTeams team;
    object_spawn_region_flags region_flags;
};

struct vehicle_spawn_params
{
    friend std::ostream& operator<<(std::ostream& os, const vehicle_spawn_params& obj)
    {
        return os
            << "\nveh_info: " << obj.veh_info
            << "\nspawn_pos: " << obj.spawn_pos
            << "\nosrp: " << obj.osrp
            << "\nzone_id_xy: " << obj.zone_id_xy
            << "\nspawn_orient: " << obj.spawn_orient
            << "\nforward_speed: " << obj.forward_speed
            << "\nparent_handle: " << obj.parent_handle
            << "\nbuilding_handle: " << obj.building_handle
            << "\nspawn_priority: " << obj.spawn_priority
            << "\nvflags: " << obj.vflags
            << "\nveh_spawn_flags: " << obj.veh_spawn_flags
            << "\nvp: " << obj.vp;
    }//88

    vehicle_info* veh_info;//4
    vector spawn_pos;//12
    object_spawn_region* osrp;//4
    unsigned __int16 zone_id_xy;//2
    matrix spawn_orient;//36 //58 total
    float forward_speed; //4 - 62
    unsigned int parent_handle; //4
    unsigned int building_handle; //4
    object_spawn_priority spawn_priority; //4
    vehicle_flags vflags; 
    vehicle_spawn_params_flags veh_spawn_flags;
    vehicle* vp;
};

























namespace keen
{
    enum ImmediateCullMode
    {
        ImmediateCullMode_None = 0x0,
        ImmediateCullMode_Back = 0x1,
        ImmediateCullMode_Front = 0x2,
        ImmediateCullMode_Count = 0x3,
    };

    enum ImmediateFillMode
    {
        ImmediateFillMode_Solid = 0x0,
        ImmediateFillMode_Wireframe = 0x1,
        ImmediateFillMode_Count = 0x2,
    };

    enum ProjectionType
    {
        ProjectionType_Perspective = 0x0,
        ProjectionType_Orthographic = 0x1,
        ProjectionType_Count = 0x2,
    };

    struct Vector3 : public keen::float3
    {

    };

    struct Vector2 : public keen::float2
    {

    };

    class Vector4 : public keen::float4
    {

    };

    struct Matrix33
    {
        keen::Vector3 x;
        keen::Vector3 y;
        keen::Vector3 z;
    };

    struct Matrix43
    {
        keen::Matrix33 rot;
        keen::Vector3 pos;
    };

    struct Matrix44
    {
        keen::Vector4 x;
        keen::Vector4 y;
        keen::Vector4 z;
        keen::Vector4 w;
    };

    struct PerspectiveProjection
    {
        float aspectRatio;
        float nearClip;
        float farClip;
        float fovY;
    };

    struct OrthographicProjection
    {
        float x0;
        float x1;
        float y0;
        float y1;
        float z0;
        float z1;
    };

    union Projection_data//$EB565B4EEB10713CE92675F66F76F40C
    {
        keen::PerspectiveProjection perspective;
        keen::OrthographicProjection orthographic;
    };

    /* 2435 */
    struct  __declspec(align(4)) Projection
    {
        Projection_data data;
        keen::ProjectionType type;
        bool rightHanded;
    };

    struct Plane
    {
        keen::Vector4 data;
    };

    struct Frustum
    {
        keen::Plane m_planes[6];
    };

    struct  __declspec(align(4)) Camera
    {
        keen::Matrix43 m_worldMatrix;
        keen::Projection m_projection;
        keen::Matrix43 m_viewMatrix;
        keen::Frustum m_frustum;
        bool m_viewDirty;
        bool m_frustumDirty;
    };

    struct ImmediateRenderer
    {
        void* m_pCommandWriter;//keen::GraphicsCommandWriter* m_pCommandWriter;
        void* m_pVertexData;
        keen::GraphicsSystem* m_pGraphicsSystem;
        keen::RasterizerState* m_pRasterizerStates[3][2];
        keen::BlendState* m_pBlendStates[2][6];
        keen::DepthStencilState* m_pDepthStencilState[8][2];
        keen::SamplerState* m_pSamplerState[3][3];
        keen::DynamicConstantBuffer* m_pShaderParameterBuffer;
        keen::DynamicConstantBuffer* m_pFragmentParameterBuffer;
        keen::ShaderPipeline* m_pShaderPipeline;
        keen::ShaderPipeline* m_pShaderPipelineVolumeSlice;
        keen::VertexFormat* m_pVertexFormat;
        keen::VertexInputBinding* m_pVertexInputBinding;
        keen::VertexInputBinding* m_pVolumeSliceInputBinding;
        keen::TextureData* m_pWhiteTexture;
        keen::Matrix44 m_viewProjectionMatrix;
        keen::Matrix43 m_worldMatrix;
        unsigned int m_screenWidth;
        unsigned int m_screenHeight;
        bool m_mvpMatrixDirty;
        bool m_endFinalRenderPass;
        keen::ImmediateCullMode m_cullMode;
        keen::ImmediateFillMode m_fillMode;
        keen::Camera m_renderPassCameraData[4];
        keen::Camera* m_renderPassCameras[4];
        unsigned int m_currentRenderPassStackSize;
    };
}

