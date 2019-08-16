#pragma once
#include "RFGR_Types_Vehicle_Spawn_Params.h"

enum weapon_class_type
{
    WEAPON_CLASS_NONE = 0xFFFFFFFF,
    WEAPON_CLASS_BULLET = 0x0,
    WEAPON_CLASS_LAUNCHER = 0x1,
    WEAPON_CLASS_THROWN = 0x2,
    WEAPON_CLASS_THROWN_CHARGE = 0x3,
    WEAPON_CLASS_THROWN_MINE = 0x4,
    WEAPON_CLASS_THROWN_GRENADE = 0x5,
    WEAPON_CLASS_MELEE = 0x6,
    WEAPON_CLASS_SLEDGEHAMMER = 0x7,
    WEAPON_CLASS_GUTTER = 0x8,
    WEAPON_CLASS_GRINDER = 0x9,
    WEAPON_CLASS_ARC_WELDER = 0xA,
    WEAPON_CLASS_NANO_RIFLE = 0xB,
    WEAPON_CLASS_MASS_DRIVER = 0xC,
    WEAPON_CLASS_HARPOON = 0xD,
    WEAPON_CLASS_SINGULARITY_BOMB = 0xE,
    WEAPON_CLASS_REPAIR = 0xF,
    WEAPON_CLASS_FLAME = 0x10,
    NUM_WEAPON_CLASSES = 0x11,
};

enum animation_group
{
    ANIMATION_GROUP_NONE = 0xFFFFFFFF,
    ANIMATION_GROUP_DEFAULT = 0x0,
    ANIMATION_GROUP_AK = 0x1,
    ANIMATION_GROUP_MELEE = 0x2,
    ANIMATION_GROUP_PISTOL = 0x3,
    ANIMATION_GROUP_REVOLVER = 0x4,
    ANIMATION_GROUP_RIFLE = 0x5,
    ANIMATION_GROUP_RPG = 0x6,
    ANIMATION_GROUP_MORTAR = 0x7,
    ANIMATION_GROUP_MINE = 0x8,
    ANIMATION_GROUP_HAMMER = 0x9,
    ANIMATION_GROUP_REMOTE_CHARGE = 0xA,
    ANIMATION_GROUP_TURRET_MACHINEGUN = 0xB,
    ANIMATION_GROUP_TURRET_ROCKET = 0xC,
    ANIMATION_GROUP_TURRET_RAILGUN = 0xD,
    ANIMATION_GROUP_2H_CARRY = 0xE,
    ANIMATION_GROUP_GUTTER = 0xF,
    ANIMATION_GROUP_SHOTGUN = 0x10,
    ANIMATION_GROUP_SNIPER = 0x11,
    ANIMATION_GROUP_ARC = 0x12,
    ANIMATION_GROUP_RAILGUN = 0x13,
    ANIMATION_GROUP_NANO = 0x14,
    ANIMATION_GROUP_THERMOBARIC_ROCKET_LAUNCHER = 0x15,
    ANIMATION_GROUP_PIPE = 0x16,
    ANIMATION_GROUP_SHIELD = 0x17,
    ANIMATION_GROUP_GRINDER = 0x18,
    ANIMATION_GROUP_ENFORCER = 0x19,
    NUM_ANIM_GROUPS = 0x1A,
};

enum weapon_trigger_type
{
    WEAPON_TRIGGER_TYPE_SINGLE = 0x0,
    WEAPON_TRIGGER_TYPE_AUTOMATIC = 0x1,
    WEAPON_TRIGGER_TYPE_CHARGE = 0x2,
    NUM_WEAPON_TRIGGER_TYPES = 0x3,
};

enum weapon_ammo_type
{
    WEAPON_AMMO_TYPE_BULLET = 0x0,
    WEAPON_AMMO_TYPE_PROJECTILE = 0x1,
    WEAPON_AMMO_TYPE_THROWN = 0x2,
    WEAPON_AMMO_TYPE_MELEE = 0x3,
    WEAPON_AMMO_TYPE_ELECTRICITY = 0x4,
    WEAPON_AMMO_TYPE_REPAIR = 0x5,
    WEAPON_AMMO_TYPE_BLANKS = 0x6,
    WEAPON_AMMO_TYPE_FLAME = 0x7,
    NUM_WEAPON_AMMO_TYPES = 0x8,
};

enum human_melee_combat_move_id
{
    INVALID_MELEE_COMBAT_MOVE_ID = 0xFFFFFFFF,
    HUMAN_MELEE_COMBAT_MOVE_ID_FORCE_TO_32_BITS = 0x7FFFFFFF,
};

struct weight_times
{
    float time;
    float wobble;
    float destable;
    float wander;
    float jitter;
    float oscillate1;
    float oscillate2;
    float direct;
    float wander_direct;
    float blur;
    float controller_vibration_strong;
    float controller_vibration_weak;
};

struct camera_shake
{
    char name[32];
    int foley_ref;
    int foley_play_id;
    vector wobble;
    float wobble_variation;
    vector destable;
    float destable_frequency;
    vector wander;
    float wander_frequency;
    vector jitter;
    vector oscillate1;
    float oscillate1_frequency;
    vector oscillate2;
    float oscillate2_frequency;
    vector direct;
    vector wander_direct;
    weight_times weights[10];
    int num_weights;
};

struct item_info__item_prop_flags//$71CEC94321954E1EE07AD4E683FB18F0
{
    unsigned __int32 offhand : 1;
};

struct item_info__item_prop
{
    char* prop_name;
    char* prop_tag;
    prop_type type;
    item_info__item_prop_flags flags;
};

struct item_info_special_flags//$5366E9642BD3DD59EF50DFB8CFD3E258
{
    __int8 high_res_texture_requested : 1;
    __int8 high_res_texture_loaded : 1;
    __int8 high_res_texture_request_unload : 1;
};

struct item_info
{
    char* name;
    char* smesh_name;
    char* cmesh_name;
    char* rig_name;
    char* anim_set_name;
    char* pickup_smesh_name;
    unsigned int srid;
    unsigned int high_res_srid;
    bool multiplayer_only;
    bool shared_backpack;
    int flags;
    bool no_peg_load;
    unsigned int material_effect_id;
    int num_props;
    item_info__item_prop props[6];
    item_info_special_flags special_flags;
    void* high_res_material;//material* high_res_material; //Todo: Re-enable this once 'material' is bound
    float mass;
    float linear_damping;
    float angular_damping;
    float restitution;
    float friction;
    vector angular_velocity;
    int respawn_delay;
    float touch_arg1;
    float touch_arg2;
    void* touch;//bool(__cdecl* touch)(Human*, item*, bool*, bool*); //Todo: Re-enable this once 'item' is bound
    int damage_flags;
    int hitpoints;
    int pickup_snd;
    int pickup_snd_2;
    int spin_time;
    int m_foley_collision;
    int cloth_foley;
    inv_item_info* safehouse_weapon;
    explosion_info* m_explosion_info;
};

struct damage_scaling_info
{
    float scale_value;
    float damage[4];
};

struct weapon_projectile_info //$4CC5F1CDA5212CF270796B525117DA23
{
    item_info* obj_item_info;
    float start_speed;
    float max_speed;
    float acceleration;
    unsigned __int16 fuse_time;
    float max_throw_dist;
    float gravity;
    int sound;
    unsigned int effect1;
    unsigned int effect2;
    unsigned int effect3;
    unsigned int effect4;
    unsigned int flags;
    float inaccurate_flight;
    float time_until_propelled;
    float time_until_prop_expire;
    float time_until_drop;
    unsigned int damage_effect;
    camera_shake* hit_camera_shake;
};

//Todo: Try changing these all to bools. Should work since they're all __int8 values
struct weapon_info_flags 
{
    __int8 armor_piercing : 1;
    __int8 can_fine_aim : 1;
    __int8 can_scope : 1;
    __int8 shatter : 1;
    __int8 held_in_left_hand : 1;
    __int8 draw_proj_in_opposite_hand : 1;
    __int8 silent_bullets : 1;
    __int8 penetrating_bullets : 1;
    __int8 non_inventory : 1;
    __int8 use_even_spread : 1;
    __int8 disable_player_cover : 1;
    __int8 mp_selectable : 1;
    __int8 is_obvious_weapon : 1;
    __int8 auto_aim_curved_trail : 1;
    __int8 looping_effects : 1;
    __int8 never_in_cabinet : 1;
    __int8 use_secondary_weapon_heat : 1;
    __int8 dont_drop_on_death : 1;
};

const struct weapon_info
{
    char* name;
    checksum_stri name_crc;
    int unique_id;
    weapon_info_flags flags;
    weapon_class_type weapon_class;
    item_info* weapon_obj_item_info;
    inv_item_info* weapon_inv_item_info;
    human_teams default_team;
    char* icon_name;
    char* small_icon_name;
    char* reticule_name;
    char* fine_aim_reticule_name;
    char* mp_kill_phrase;
    animation_group weapon_anim_group;
    unsigned int muzzle_flash_effect;
    unsigned int muzzle_smoke_effect;
    unsigned int special_hit_effect;
    unsigned int special_effect;
    unsigned int secondary_special_effect;
    unsigned int overheated_effect;
    unsigned int tracer_effect;
    camera_shake* fire_camera_shake;
    bool fire_camera_shake_ignore_disabled;
    camera_shake* secondary_camera_shake;
    camera_shake* player_hit_camera_shake;
    char attachment_point[32];
    int fire_sound;
    int secondary_sound;
    int upgrade_sound;
    int reload_sound;
    int reload_sound_delay;
    int no_ammo_sound;
    int special_sound;
    int flyby_sound;
    int num_weapon_personas;
    int npc_fire_sounds[16];
    float max_range;
    float red_range;
    float max_engagement_dist;
    float min_engagement_dist;
    float max_ai_penetrating_dist;
    void* npc_firing_pattern; //weapon_firing_pattern* npc_firing_pattern; //Todo: Bind and re-enable this.
    void* npc_aim_drift_profile; //aim_drift_profile* npc_aim_drift_profile; //Todo: Bind and re-enable this.
    weapon_trigger_type trigger_type;
    weapon_ammo_type ammo_type;
    unsigned __int16 magazine_size;
    unsigned __int16 magazine_start_num;
    unsigned __int16 max_rounds;
    unsigned __int16 max_rounds_upgrade;
    unsigned __int16 ammo_box_restock;
    unsigned __int16 to_min_spread;
    unsigned __int16 to_max_spread;
    char melee_group_index;
    char bullet_group_index;
    char tracer_frequency;
    char shots_per_round;
    float firing_sound_radius;
    float npc_refire_delay;
    float default_refire_delay;
    float prefire_delay;
    int default_reload_delay;
    damage_scaling_info low_scale_damage;
    damage_scaling_info high_scale_damage;
    explosion_info* m_explosion_info;
    explosion_info* m_ai_explosion_info;
    float fire_cone_dot;
    float even_spread_accuracy_dot;
    float max_spread;
    float min_spread;
    float fine_aim_max_spread;
    float fine_aim_min_spread;
    float npc_max_spread;
    float npc_min_spread;
    float spread_multiplier_run;
    float ragdoll_force_shoot;
    float ragdoll_chance;
    float recoil_camera_kick;
    float recoil_impulse;
    int out_of_ammo_reload_delay;
    float overheat_cool_down_time;
    float overheat_percent_per_shot;
    float dropped_ammo_scale;
    float bullet_hole_scale;
    float headshot_multiplier;
    float zoom_magnification;
    float autoaim_override;
    float npc_autoaim;
    float aim_assist;
    float player_move_speed_multiplier;
    float npc_move_speed_multiplier;
    float alert_multiplier;
    weapon_projectile_info projectile_info;
    human_melee_combat_move_id standing_primary_melee_attack;
    human_melee_combat_move_id standing_secondary_melee_attack;
    human_melee_combat_move_id standing_tertiary_melee_attack;
    human_melee_combat_move_id crouching_primary_melee_attack;
    human_melee_combat_move_id crouching_secondary_melee_attack;
    human_melee_combat_move_id crouching_tertiary_melee_attack;
};

struct game_clock
{
    unsigned __int16 m_year;
    char m_month;
    char m_day;
    char m_hour;
    char m_minutes;
    char m_seconds;
    char m_day_of_week;
    float m_time_scale;
    unsigned int m_curr_day_ticks;
};