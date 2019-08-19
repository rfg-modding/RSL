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

enum audiolib_result
{
    AUDIOLIB_FILE_LOAD_STATUS_UNLOADED = 0x66,
    AUDIOLIB_FILE_LOAD_STATUS_LOADED = 0x65,
    AUDIOLIB_FILE_LOAD_STATUS_LOADING = 0x64,
    AUDIOLIB_CUE_WAITING_FOR_BANDWIDTH = 0xB,
    AUDIOLIB_CUE_WAITING_FOR_A_CHANNEL = 0xA,
    AUDIOLIB_ERR_NONE = 0x0,
    AUDIOLIB_ERR_NOT_INITED = 0xFFFFFFFF,
    AUDIOLIB_ERR_MEM_ALLOC_FAILED = 0xFFFFFFFE,
    AUDIOLIB_ERR_FILE_OPEN = 0xFFFFFFFD,
    AUDIOLIB_ERR_FILE_READ = 0xFFFFFFFC,
    AUDIOLIB_ERR_FILE_FORMAT = 0xFFFFFFFB,
    AUDIOLIB_ERR_DSP_INIT_FAILED = 0xFFFFFFFA,
    AUDIOLIB_ERR_THREAD_FAILED = 0xFFFFFFF9,
    AUDIOLIB_ERR_THREAD_PRIORITY_FAILED = 0xFFFFFFF8,
    AUDIOLIB_ERR_THREAD_NOT_CLOSED = 0xFFFFFFF7,
    AUDIOLIB_ERR_NO_PROCESS_SLOTS = 0xFFFFFFF6,
    AUDIOLIB_ERR_NO_SOUNDBANK_SLOTS = 0xFFFFFFF5,
    AUDIOLIB_ERR_NO_PLAY_SLOTS = 0xFFFFFFF4,
    AUDIOLIB_ERR_NO_MORE_MUSIC_SLOTS = 0xFFFFFFF3,
    AUDIOLIB_ERR_NO_MORE_ALR_SLOTS = 0xFFFFFFF2,
    AUDIOLIB_ERR_NO_FOLEY_SLOTS = 0xFFFFFFF1,
    AUDIOLIB_ERR_NOT_PLAYING = 0xFFFFFFF0,
    AUDIOLIB_ERR_NOT_SUPPORTED = 0xFFFFFFEF,
    AUDIOLIB_ERR_SOUNDS_PAUSED = 0xFFFFFFEE,
    AUDIOLIB_ERR_NO_MORE_ENTRIES = 0xFFFFFFED,
    AUDIOLIB_NOT_ENABLED = 0xFFFFFFCE,
    AUDIOLIB_FILE_LOAD_STATUS_ERROR = 0xFFFFFFBB,
    AUDIOLIB_ERR_BAD_INTERNAL = 0xFFFFFF9D,
    AUDIOLIB_ERR_BAD_PARAM = 0xFFFFFF9C,
    AUDIOLIB_ERR_NO_MEMPOOL = 0xFFFFFF9B,
    AUDIOLIB_ERR_BAD_CUE_ID = 0xFFFFFF9A,
    AUDIOLIB_ERR_BAD_BANK_ID = 0xFFFFFF99,
    AUDIOLIB_ERR_BAD_PLAY_ID = 0xFFFFFF98,
    AUDIOLIB_ERR_NO_MARKERS = 0xFFFFFF97,
    AUDIOLIB_ERR_BAD_CATEGORY_ID = 0xFFFFFF96,
    AUDIOLIB_ERR_BAD_MUSIC_ID = 0xFFFFFF95,
    AUDIOLIB_ERR_SOUNDBANK_IN_USE = 0xFFFFFF94,
    AUDIOLIB_ERR_CUE_NOT_FOUND = 0xFFFFFF93,
    AUDIOLIB_ERR_MARKERS_NOT_FOUND = 0xFFFFFF92,
    AUDIOLIB_ERR_NO_MARKER_SLOTS = 0xFFFFFF91,
    AUDIOLIB_ERR_FOLEY_TABLE = 0xFFFFFF90,
    AUDIOLIB_ERR_DIST_TOO_FAR = 0xFFFFFF8F,
    AUDIOLIB_ERR_DONT_PLAY_PERCENTAGE = 0xFFFFFF8E,
    AUDIOLIB_ERR_EXCEED_FOLEY_LIMIT = 0xFFFFFF8D,
    AUDIOLIB_ERR_EXCEED_CATEGORY_LIMIT = 0xFFFFFF8C,
    AUDIOLIB_ERR_MUSIC_TRANSITION_FAILED = 0xFFFFFF8B,
    AUDIOLIB_ERR_CATEGORY_VOLUME_TOO_LOW = 0xFFFFFF8A,
    AUDIOLIB_ERR_VARIATION_NOT_KNOWN = 0xFFFFFF89,
    AUDIOLIB_ERR_MULTI_CUE_NO_SLOTS = 0xFFFFFF88,
    AUDIOLIB_ERR_MULTI_CUE_NO_ROOM = 0xFFFFFF87,
    AUDIOLIB_ERR_CANT_PLAY_WHEN_LOADING = 0xFFFFFF86,
    AUDIOLIB_ERR_NOT_2D = 0xFFFFFF38,
    AUDIOLIB_ERR_NOT_3D = 0xFFFFFF37,
    AUDIOLIB_ERR_NO_MULT_EMITTERS = 0xFFFFFF36,
    AUDIOLIB_ERR_NO_MULT_POSITION = 0xFFFFFF35,
    AUDIOLIB_ERR_HW_INIT_FAILED = 0xFFFFFED4,
    AUDIOLIB_ERR_HW_NOT_READY = 0xFFFFFED3,
    AUDIOLIB_ERR_HW_FAILED_TO_GET_PLAYSTATE = 0xFFFFFED2,
    AUDIOLIB_ERR_HW_FAILED_TO_PLAY_CUE = 0xFFFFFED1,
    AUDIOLIB_ERR_HW_FAILED_TO_STOP_CUE = 0xFFFFFED0,
    AUDIOLIB_ERR_HW_FAILED_TO_PAUSE_CUE = 0xFFFFFECF,
    AUDIOLIB_ERR_HW_FAILED_TO_UNPAUSE_CUE = 0xFFFFFECE,
    AUDIOLIB_ERR_HW_CALLBACK_REGISTER_FAILED = 0xFFFFFECD,
    AUDIOLIB_ERR_HW_SOUNDBANK_INVALID = 0xFFFFFECC,
    AUDIOLIB_ERR_HW_SOUNDBANK_LOAD_FAILED = 0xFFFFFECB,
    AUDIOLIB_ERR_HW_SOUNDBANK_CREATE_FAILED = 0xFFFFFECA,
    AUDIOLIB_ERR_HW_NOT_SUPPORTED = 0xFFFFFEC9,
    AUDIOLIB_ERR_HW_MISC = 0xFFFFFEC8,
    AUDIOLIB_ERR_HW_UNKNOWN_FOLEY = 0xFFFFFEC7,
    AUDIOLIB_ERR_HW_UNKNOWN_CATEGORY = 0xFFFFFEC6,
    AUDIOLIB_ERR_HW_FAILED_CATEGORY_SET = 0xFFFFFEC5,
    AUDIOLIB_ERR_HW_FAILED_VOICE_CREATE = 0xFFFFFEC4,
    AUDIOLIB_ERR_HW_FAILED_VOICES_SET = 0xFFFFFEC3,
    AUDIOLIB_ERR_HW_NUM_CHANNELS_0 = 0xFFFFFEC2,
    AUDIOLIB_ERR_HW_NUM_CHANNELS = 0xFFFFFEC1,
    AUDIOLIB_ERR_HW_VARIATION_MISMATCH = 0xFFFFFEC0,
    AUDIOLIB_ERR_STREAM_OUTOFMEMORY = 0xFFFFFE70,
    AUDIOLIB_ERR_STREAM_TIMEOUT_ERROR = 0xFFFFFE6F,
    AUDIOLIB_ERR_STREAM_MISC_ERROR = 0xFFFFFE6E,
    AUDIOLIB_ERR_TRY_CACHE_LATER = 0xFFFFFE6D,
    AUDIOLIB_ERR_NOT_IMPLEMENTED = 0xFFFFD8F0,
};

enum AUDIOLIB_REVERB_ROOM_TYPE
{
    AUDIOLIB_REVERB_ROOM_TYPE_DEFAULT = 0x0,
    AUDIOLIB_REVERB_ROOM_TYPE_GENERIC = 0x1,
    AUDIOLIB_REVERB_ROOM_TYPE_PADDEDCELL = 0x2,
    AUDIOLIB_REVERB_ROOM_TYPE_ROOM = 0x3,
    AUDIOLIB_REVERB_ROOM_TYPE_BATHROOM = 0x4,
    AUDIOLIB_REVERB_ROOM_TYPE_LIVINGROOM = 0x5,
    AUDIOLIB_REVERB_ROOM_TYPE_STONEROOM = 0x6,
    AUDIOLIB_REVERB_ROOM_TYPE_AUDITORIUM = 0x7,
    AUDIOLIB_REVERB_ROOM_TYPE_CONCERTHALL = 0x8,
    AUDIOLIB_REVERB_ROOM_TYPE_CAVE = 0x9,
    AUDIOLIB_REVERB_ROOM_TYPE_ARENA = 0xA,
    AUDIOLIB_REVERB_ROOM_TYPE_HANGAR = 0xB,
    AUDIOLIB_REVERB_ROOM_TYPE_CARPETEDHALLWAY = 0xC,
    AUDIOLIB_REVERB_ROOM_TYPE_HALLWAY = 0xD,
    AUDIOLIB_REVERB_ROOM_TYPE_STONECORRIDOR = 0xE,
    AUDIOLIB_REVERB_ROOM_TYPE_ALLEY = 0xF,
    AUDIOLIB_REVERB_ROOM_TYPE_FOREST = 0x10,
    AUDIOLIB_REVERB_ROOM_TYPE_CITY = 0x11,
    AUDIOLIB_REVERB_ROOM_TYPE_MOUNTAINS = 0x12,
    AUDIOLIB_REVERB_ROOM_TYPE_QUARRY = 0x13,
    AUDIOLIB_REVERB_ROOM_TYPE_PLAIN = 0x14,
    AUDIOLIB_REVERB_ROOM_TYPE_PARKINGLOT = 0x15,
    AUDIOLIB_REVERB_ROOM_TYPE_SEWERPIPE = 0x16,
    AUDIOLIB_REVERB_ROOM_TYPE_UNDERWATER = 0x17,
    AUDIOLIB_REVERB_ROOM_TYPE_SMALLROOM = 0x18,
    AUDIOLIB_REVERB_ROOM_TYPE_MEDIUMROOM = 0x19,
    AUDIOLIB_REVERB_ROOM_TYPE_LARGEROOM = 0x1A,
    AUDIOLIB_REVERB_ROOM_TYPE_MEDIUMHALL = 0x1B,
    AUDIOLIB_REVERB_ROOM_TYPE_LARGEHALL = 0x1C,
    AUDIOLIB_REVERB_ROOM_TYPE_PLATE = 0x1D,
    AUDIOLIB_NUM_REVERB_ROOM_TYPES = 0x1E,
};

struct audiolib_low_pass_info
{
    int freq;
    float effect;
};

struct audiolib_reverb_info
{
    AUDIOLIB_REVERB_ROOM_TYPE room_type;
    float effect;
};

struct audiolib_dsp_info
{
    audiolib_low_pass_info low_pass;
    audiolib_reverb_info reverb;
};

struct audiolib_params
{
    unsigned __int16 flags;
    unsigned __int16 callback_flags;
    void* callback_func;//void(__cdecl* callback_func)(AUDIOLIB_CUE_CALLBACK_DATA*);
    void* callback_data;
    char priority;
    float volume;
    float pitch;
    float pan;
    char rolloff_curve;
    float curve_midpoint;
    unsigned __int16 dsp_type;
    audiolib_dsp_info dsp;
    float distance_min;
    float distance_max;
    unsigned int delay_ms;
    unsigned int fade_ms;
    unsigned int offset_ms;
    vector pos;
    vector orient;
    vector velocity;
    __int16 num_positions;
    vector position_list[16];
};