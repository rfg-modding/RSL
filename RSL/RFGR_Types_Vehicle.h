#pragma once
#include "RFGR_Types_Keen_InputEvent.h"

//Note: vehicle_info and vehicle are already defined in RFGR_Types_Vehicle_Spawn_Params
//Todo: See if these files can be reorganized a bit to move those values into this file so they aren't split

struct automobile_resource_dependent_data
{
    void* m_hk_vehicle_data; //hkpVehicleData* m_hk_vehicle_data;
    void* m_hk_vehicle_instance; //hk_custom_vehicle_instance* m_hk_vehicle_instance;
    unsigned int m_num_wheels;
    vehicle_component* m_wheel_components[16];
    unsigned int m_wheel_axle_ids[16];
    float m_wheelbase;
    unsigned int m_axle_wheel_counts[4];
    float m_wheel_radius_per_axle[4];
    float m_wheel_width_per_axle[4];
    bool m_front_wheels[16];
    bool m_back_wheels[16];
};

/* 6640 */
struct __declspec(align(4)) object_stream_resource__automobile_resource_dependent_data
{
    automobile_resource_dependent_data m_data;
    bool m_loaded;
};

struct automobile_tire_track_decal_data
{
    vector m_start_pos;
    vector m_move_dir;
    vector m_normal;
    float m_length;
    unsigned int m_decal_handle;
    unsigned int m_obj_handle;
};

struct automobile_wheel_effect_info
{
    unsigned int m_motion_effect;
    unsigned int m_skid_effect;
    int m_skid_foley;
    unsigned int m_peel_effect;
    int m_peel_foley;
    unsigned int m_brake_effect;
    int m_brake_foley;
    rfg::circ_array<automobile_tire_track_decal_data, 3> m_track_decals;
};

struct automobile_collision_effect_info
{
    vector m_position;
    vector m_normal;
    unsigned int m_other_handle;
    int m_foley_info;
    unsigned int m_effect_obj;
};

struct mp_collision_prediction_info
{
    timestamp check_time;
    vector last_start_pos;
    vector last_end_pos;
    vector last_pos;
    vector last_vel;
};

struct automobile : vehicle
{
    object_stream_resource__automobile_resource_dependent_data a_rdd; //object_stream_resource<automobile::resource_dependent_data> a_rdd;
    automobile_wheel_effect_info m_wheel_effect_infos[16];
    int m_motion_foley;
    int m_tread_foley;
    void* m_decal_collection_data; //decal_collection_data* m_decal_collection_data;
    unsigned int m_num_decal_collections;
    float m_decal_width;
    bool m_decal_collection_occurred;
    timestamp m_wheel_effect_stopped_timer;
    bool m_wheel_effect_is_stopped;
    int honk_alr_id;
    int foley_siren;
    int foley_megaphone;
    int foley_chassis;
    int engine_peel;
    int gear_shift;
    float user_acc_input;
    timestamp time_at_max_speed;
    bool play_shift_foley;
    timestamp horn_timeout;
    automobile_collision_effect_info m_collision_impact_sounds[4];
    automobile_collision_effect_info m_collision_scraping_sounds[4];
    timestamp m_impact_sound_delay;
    timestamp m_scraping_sound_delay;
    timestamp m_chassis_sound_delay;
    timestamp brake_effect_release_timer;
    timestamp catch_fire_timestamp;
    unsigned int m_h_trailer_vehicle;
    unsigned int m_h_tractor_vehicle;
    float prev_chassis_stress;
    float max_chassis_stress;
    timestamp is_airborne;
    timestamp is_landing;
    timestamp is_skipping;
    timestamp is_skiprecovery;
    float force_assist_value;
    float powerslide_amount;
    float current_powerslide_friction;
    bool powerslide_was_handbrake_on;
    void* mp_sim_state; //multi_sim_state<multi_automobile_state>* mp_sim_state;
    mp_collision_prediction_info mp_collision_prediction;
};




























struct flyer_resource_dependent_data
{

};

struct hkpUnaryAction : hkpAction
{
    hkpEntity* m_entity;
};

struct flyer;
struct flyer_control_action : hkpUnaryAction
{
    flyer* fp;
};

struct flyer_flags
{
    __int8 landing_gear_up : 1;
    __int8 landing_gear_collision_off : 1;
    __int8 needs_to_takeoff : 1;
    __int8 has_lift : 1;
    __int8 stay_at_constant_height : 1;
    __int8 on_ground : 1;
};

struct  __declspec(align(4)) flyer : vehicle
{
    flyer(const flyer& other)
        : vehicle(other),
          f_rdd(other.f_rdd),
          ctl_action(other.ctl_action),
          req_urgency(other.req_urgency),
          req_max_vel(other.req_max_vel),
          req_point(other.req_point),
          req_vel(other.req_vel),
          req_lookat(other.req_lookat),
          req_point_isvalid(other.req_point_isvalid),
          req_vel_isvalid(other.req_vel_isvalid),
          req_lookat_isvalid(other.req_lookat_isvalid),
          req_stop_at_point(other.req_stop_at_point),
          req_halt(other.req_halt),
          wing_is_detached(other.wing_is_detached),
          vehicle_mass(other.vehicle_mass),
          chassis_com_cs(other.chassis_com_cs),
          chassis_com_ws(other.chassis_com_ws),
          thrust_mat_cs(other.thrust_mat_cs),
          thrust_mat_ws(other.thrust_mat_ws),
          thrust_up_target(other.thrust_up_target),
          hover_noise_vec(other.hover_noise_vec),
          hover_noise_vec_new(other.hover_noise_vec_new),
          hover_noise_vec_old(other.hover_noise_vec_old),
          hover_noise_timer(other.hover_noise_timer),
          hover_noise_dur(other.hover_noise_dur),
          engine_off_suspension_period(other.engine_off_suspension_period),
          turbine_rpm_target(other.turbine_rpm_target),
          turbine_rpm(other.turbine_rpm),
          turbine_load(other.turbine_load),
          l_wing(other.l_wing),
          r_wing(other.r_wing),
          l_canard(other.l_canard),
          r_canard(other.r_canard),
          jetwash(other.jetwash),
          engine_force(other.engine_force),
          startup_timer(other.startup_timer),
          last_player_damage(other.last_player_damage),
          catch_fire_timer(other.catch_fire_timer),
          flyer_flags(other.flyer_flags)
    {
    }

    flyer& operator=(const flyer& other)
    {
        if (this == &other)
            return *this;
        vehicle::operator =(other);
        f_rdd = other.f_rdd;
        ctl_action = other.ctl_action;
        req_urgency = other.req_urgency;
        req_max_vel = other.req_max_vel;
        req_point = other.req_point;
        req_vel = other.req_vel;
        req_lookat = other.req_lookat;
        req_point_isvalid = other.req_point_isvalid;
        req_vel_isvalid = other.req_vel_isvalid;
        req_lookat_isvalid = other.req_lookat_isvalid;
        req_stop_at_point = other.req_stop_at_point;
        req_halt = other.req_halt;
        wing_is_detached = other.wing_is_detached;
        vehicle_mass = other.vehicle_mass;
        chassis_com_cs = other.chassis_com_cs;
        chassis_com_ws = other.chassis_com_ws;
        thrust_mat_cs = other.thrust_mat_cs;
        thrust_mat_ws = other.thrust_mat_ws;
        thrust_up_target = other.thrust_up_target;
        hover_noise_vec = other.hover_noise_vec;
        hover_noise_vec_new = other.hover_noise_vec_new;
        hover_noise_vec_old = other.hover_noise_vec_old;
        hover_noise_timer = other.hover_noise_timer;
        hover_noise_dur = other.hover_noise_dur;
        engine_off_suspension_period = other.engine_off_suspension_period;
        turbine_rpm_target = other.turbine_rpm_target;
        turbine_rpm = other.turbine_rpm;
        turbine_load = other.turbine_load;
        l_wing = other.l_wing;
        r_wing = other.r_wing;
        l_canard = other.l_canard;
        r_canard = other.r_canard;
        jetwash = other.jetwash;
        engine_force = other.engine_force;
        startup_timer = other.startup_timer;
        last_player_damage = other.last_player_damage;
        catch_fire_timer = other.catch_fire_timer;
        flyer_flags = other.flyer_flags;
        return *this;
    }

    rfg::object_stream_resource<flyer_resource_dependent_data> f_rdd;
    flyer_control_action* ctl_action;
    float req_urgency;
    float req_max_vel;
    vector req_point;
    vector req_vel;
    vector req_lookat;
    bool req_point_isvalid;
    bool req_vel_isvalid;
    bool req_lookat_isvalid;
    bool req_stop_at_point;
    bool req_halt;
    bool wing_is_detached;
    float vehicle_mass;
    vector chassis_com_cs;
    vector chassis_com_ws;
    matrix thrust_mat_cs;
    matrix thrust_mat_ws;
    vector thrust_up_target;
    vector hover_noise_vec;
    vector hover_noise_vec_new;
    vector hover_noise_vec_old;
    timestamp hover_noise_timer;
    float hover_noise_dur;
    timestamp engine_off_suspension_period;
    float turbine_rpm_target;
    float turbine_rpm;
    float turbine_load;
    int l_wing;
    int r_wing;
    int l_canard;
    int r_canard;
    unsigned int wingtip_effect[2];
    unsigned int front_thruster[2];
    unsigned int center_thruster[2];
    unsigned int main_engines[2];
    unsigned int jetwash;
    float engine_force;
    timestamp startup_timer;
    timestamp last_player_damage;
    timestamp catch_fire_timer;
    flyer_flags flyer_flags;
};
















enum walker_ik_joints
{
    WALKER_IK_JOINT_LEFT_LEG = 0x0,
    WALKER_IK_JOINT_RIGHT_LEG = 0x1,
    NUM_WALKER_IK_JOINTS = 0x2,
};

enum walker_model_type
{
    WMT_SMALL = 0x0,
    WMT_FLAME = 0x1,
    WMT_CIVILIAN = 0x2,
};

enum walker_control_scheme
{
    WCS_FACING_CAMERA = 0x0,
    WCS_CHARACTER_STYLE = 0x1,
};

enum walker_attack_types
{
    WALKER_ATTACK_NONE = 0x0,
    WALKER_ATTACK_THROW = 0x1,
    WALKER_ATTACK_SWEEP = 0x2,
    WALKER_ATTACK_SMASH = 0x3,
    NUM_WALKER_ATTACK_TYPES = 0x4,
};

enum state_enums_walker
{
    STATE_DATA_WALKER = 0x0,
    STATE_PHYSICS_POS_WALKER = 0x1,
    STATE_PHYSICS_ORIENT_WALKER = 0x2,
    STATE_PHYSICS_VEL_WALKER = 0x3,
    STATE_HITPOINTS_WALKER = 0x4,
    STATE_COMPONENT_WALKER = 0x5,
    STATE_LIGHTS_WALKER = 0x6,
    STATE_ACTIONS_WALKER = 0x7,
    STATE_NUM_WALKER = 0x8,
};

struct walker_resource_dependent_data
{
    int left_foot_component_idx;
    int right_foot_component_idx;
};

struct walker_flags
{
    unsigned __int32 reduce_impact_momentum : 1;
    unsigned __int32 in_ramming_mode : 1;
    unsigned __int32 rotating_left : 1;
    unsigned __int32 rotating_right : 1;
    unsigned __int32 teleport_components : 1;
    unsigned __int32 is_mounting : 1;
    unsigned __int32 jump_jet_on : 1;
    unsigned __int32 jump_take_off : 1;
};

struct walker_component_info
{
    vector desired_pos;
    matrix desired_orient;
    vector anim_pos;
    matrix anim_orient;
    float component_error;
    int has_children;
    vector debug_pos;
    matrix debug_orient;
    timestamp collide_ts;
};

struct wik_joint
{
    int anchor_tag;
    int joint_tag;
    int ik_tag;
    float ik_strength;
    float ik_rate_of_change;
    float correction_amount;
    vector cached_hit_point;
    bool hit_point_valid;
    float cur_foot_p;
    float cur_foot_b;
    walker_ik_joints location;
};

struct walker_attack_data
{
    char attack_1_id;
    char attack_2_id;
    char attack_3_id;
    char attack_4_id;
    char charge_id;
};

struct walker_mp_data
{
    char attack_1_id;
    char attack_2_id;
    char attack_3_id;
    char attack_4_id;
    char charge_id;
};

struct mp_x_collision_prediction_info
{
    timestamp check_time;
    vector last_start_pos;
    vector last_end_pos;
    vector last_pos;
    vector last_vel;
};

using block_movement_types = BlockMovementTypes;
struct walker : vehicle
{
    rfg::object_stream_resource<walker_resource_dependent_data> w_rdd;
    walker_flags w_flags;
    vector chassis_pos;
    matrix chassis_orient;
    unsigned int collision_model;
    float hull_radius;
    walker_component_info comp_info[74];
    int comp_transform_order[74];
    vector steering_vector;
    float move_speed;
    float cur_rotation_speed;
    float desired_move_speed;
    vector input_velocity;
    vector chassis_pos_last_frame;
    vector actual_velocity;
    float actual_velocity_mag;
    float vertical_anim_speed;
    float y_offset;
    vector mount_vector;
    unsigned int mount_vehicle;
    unsigned int ground_obj_handle;
    unsigned int last_ground_obj_handle;
    vector ground_normal;
    vector ground_world_pos;
    timestamp ground_test_ts;
    float ground_impact_momentum;
    float ram_momentum;
    float ram_max_energy_used;
    float jump_jet_energy;
    float jump_jet_speed;
    float jump_jet_engage_time;
    int jump_jet_tag_idx;
    unsigned int jump_jet_effect;
    int jump_jet_foley;
    timestamp jump_jet_foley_disable;
    timestamp jump_timeout;
    float engine_load;
    timestamp time_since_last_supported;
    walker_model_type model_type;
    walker_control_scheme control_scheme;
    int block_movement_anim;
    block_movement_types block_movement_type;
    wik_joint ik_joints[2];
    void* mp_sim_state; //multi_sim_state<multi_walker_state>* mp_sim_state;
    walker_mp_data mp_data;
    mp_x_collision_prediction_info mp_collision_prediction;
};