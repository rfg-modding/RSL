#pragma once
#include "RFGR_Type_UI.h"
#include <ostream>

using timestamp = Timestamp;
using vehicle_seat_index = VehicleSeatIndex;
using human_teams = HumanTeams;
using damaged_by_types = DamagedByTypes;

enum trigger_region_shape
{
    TRIGGER_REGION_SHAPE_BOX = 0x0,
    TRIGGER_REGION_SHAPE_SPHERE = 0x1,
    NUM_TRIGGER_REGION_SHAPES = 0x2,
};

enum trigger_region_type
{
    TRIGGER_REGION_TYPE_DEFAULT = 0x0,
    TRIGGER_REGION_TYPE_KILL_HUMAN = 0x1,
    NUM_TRIGGER_REGION_TYPES = 0x2,
};

enum trigger_region_kill_human_types
{
    TRKHT_INVALID = 0xFFFFFFFF,
    TRKHT_CLIFF = 0x0,
    TRKHT_MINE = 0x1,
    NUM_TRIGGER_REGION_KILL_HUMAN_TYPES = 0x2,
};

enum vehicle_damage_area_type
{
    VDA_ENGINE = 0x0,
    NUM_VEHICLE_DAMAGE_AREAS = 0x1,
};

enum squad_spawn_status
{
    SQUAD_SPAWN_NONE = 0xFFFFFFFF,
    SQUAD_SPAWN_OK = 0x0,
    SQUAD_SPAWN_PARTIAL_NPC_CREATE_FAILED = 0x1,
    SQUAD_SPAWN_FAILED_NPC_MAX_QUANTITY = 0x2,
    SQUAD_SPAWN_FAILED_NO_ORDERS = 0x3,
    SQUAD_SPAWN_FAILED_OUT_OF_SPACE = 0x4,
    SQUAD_SPAWN_FAILED_OBJECT_DOES_NOT_EXIST = 0x5,
    SQUAD_SPAWN_FAILED_NO_OPEN_SPACE = 0x6,
    SQUAD_SPAWN_GENERIC_FAILURE = 0x7,
    SQUAD_SPAWN_FAILED_NPC_CREATE_FAILED = 0x8,
    SQUAD_SPAWN_FAILED_NO_DEFINITION = 0x9,
    NUM_SQUAD_SPAWN_STATUS = 0xA,
};

enum minimap_elements
{
    MAP_ELEMENT_INVALID = 0xFFFFFFFF,
    MAP_ELEMENT_STAR_RED_ICON = 0x0,
    MAP_ELEMENT_STAR_BLUE_ICON = 0x1,
    MAP_ELEMENT_STAR_GREEN_ICON = 0x2,
    MAP_ELEMENT_STAR_WHITE_ICON = 0x3,
    MAP_ELEMENT_CIRCLE_BLUE_ICON = 0x4,
    MAP_ELEMENT_CIRCLE_BLUE_1_ICON = 0x5,
    MAP_ELEMENT_CIRCLE_BLUE_2_ICON = 0x6,
    MAP_ELEMENT_CIRCLE_BLUE_3_ICON = 0x7,
    MAP_ELEMENT_CIRCLE_BLUE_4_ICON = 0x8,
    MAP_ELEMENT_CIRCLE_VIOLET_1_ICON = 0x9,
    MAP_ELEMENT_CIRCLE_VIOLET_2_ICON = 0xA,
    MAP_ELEMENT_CIRCLE_VIOLET_3_ICON = 0xB,
    MAP_ELEMENT_CIRCLE_VIOLET_4_ICON = 0xC,
    MAP_ELEMENT_AMMO_BOX = 0xD,
    MAP_ELEMENT_CONVOY_ICON = 0xE,
    MAP_ELEMENT_CONVOY_CAPTURE_ICON = 0xF,
    MAP_ELEMENT_RIDING_SHOTGUN = 0x10,
    MAP_ELEMENT_AREA_DEFENSE = 0x11,
    MAP_ELEMENT_COURIER_ICON = 0x12,
    MAP_ELEMENT_RAID_ICON = 0x13,
    MAP_ELEMENT_RAID_ICON_ALWAYS_SHOW = 0x14,
    MAP_ELEMENT_DEF_RAID_ICON = 0x15,
    MAP_ELEMENT_BASE_ICON = 0x16,
    MAP_ELEMENT_HOUSE_ICON = 0x17,
    MAP_ELEMENT_HOUSE_ICON_ALWAYS_SHOW = 0x18,
    MAP_ELEMENT_DEMOLITIONS_MASTER = 0x19,
    MAP_ELEMENT_GUERRILLA_EXPRESS = 0x1A,
    MAP_ELEMENT_GENERIC_ACTIVITY = 0x1B,
    MAP_ELEMENT_ARROW_ICON = 0x1C,
    MAP_ELEMENT_CIRCLE_FILLED_OUTLINE = 0x1D,
    MAP_ELEMENT_CONVOY_END_POINT = 0x1E,
    MAP_ELEMENT_GUERILLA_EXP_END_POINT = 0x1F,
    MAP_ELEMENT_MISSION_START = 0x20,
    MAP_ELEMENT_TARGET = 0x21,
    MAP_ELEMENT_TARGET_PRIORITY_1 = 0x22,
    MAP_ELEMENT_TARGET_PRIORITY_2 = 0x23,
    MAP_ELEMENT_TARGET_PRIORITY_3 = 0x24,
    MAP_ELEMENT_TARGET_PRIORITY_4 = 0x25,
    MAP_ELEMENT_SAFE_HOUSE = 0x26,
    MAP_ELEMENT_DIRECTIONAL_ARROW = 0x27,
    MAP_ELEMENT_MISSION_OBJECTIVE = 0x28,
    MAP_ELEMENT_MISSION_OBJECTIVE_UP = 0x29,
    MAP_ELEMENT_MISSION_OBJECTIVE_DOWN = 0x2A,
    MAP_ELEMENT_TANK_ICON = 0x2B,
    MAP_ELEMENT_FLAG_ICON = 0x2C,
    MAP_ELEMENT_KOTH_GUERRILLA = 0x2D,
    MAP_ELEMENT_KOTH_EDF = 0x2E,
    MAP_ELEMENT_KOTH_NEUTRAL = 0x2F,
    MAP_ELEMENT_CARBOMB = 0x30,
    MAP_ELEMENT_ICON_COUNT = 0x31,
    MAP_ELEMENT_BLIP = 0x31,
    MAP_ELEMENT_BLIP_HUMAN = 0x32,
    MAP_ELEMENT_PLAYER = 0x33,
    MAP_ELEMENT_STRUCTURE_EDF = 0x34,
    MAP_ELEMENT_VEHICLE = 0x35,
    MAP_ELEMENT_IMPORTANCE_MEDIUM = 0x36,
    MAP_ELEMENT_IMPORTANCE_HIGH = 0x37,
    MAP_ELEMENT_NORTH = 0x38,
    MAP_ELEMENT_RING_ICON = 0x39,
    MAP_ELEMENT_CAMERA_CONE = 0x3A,
    NUM_MAP_ELEMENTS = 0x3B,
};

enum gfm_orders_types
{
    GFM_ORDERS_TYPE_INVALID = 0xFFFFFFFF,
    GFM_ORDERS_TYPE_NONE = 0x0,
    GFM_ORDERS_TYPE_DEFEND = 0x1,
    GFM_ORDERS_TYPE_ATTACK = 0x2,
    GFM_ORDERS_TYPE_PATROL = 0x3,
    GFM_ORDERS_TYPE_SMASH = 0x4,
    GFM_ORDERS_TYPE_CONVOY = 0x5,
    GFM_ORDERS_TYPE_COURIER = 0x6,
    GFM_ORDERS_TYPE_AMBIENT_ACTION = 0x7,
    GFM_ORDERS_TYPE_AMBIENT_PED = 0x8,
    GFM_ORDERS_TYPE_FODDER = 0x9,
    GFM_ORDERS_TYPE_TERRORIZE = 0xA,
    GFM_ORDERS_TYPE_WAIT = 0xB,
    GFM_ORDERS_TYPE_ROADBLOCK = 0xC,
    GFM_ORDERS_TYPE_TRAPPED = 0xD,
    GFM_ORDERS_TYPE_TRAPPED_JAIL = 0xE,
    GFM_ORDERS_TYPE_DRIVE_BY = 0xF,
    GFM_ORDERS_TYPE_FLY_BY = 0x10,
    GFM_ORDERS_VEHICLE_DROP_OFF = 0x11,
    GFM_ORDERS_TIED_UP = 0x12,
    NUM_GFM_ORDERS_TYPES = 0x13,
};

enum spawn_node_respawn_speed
{
    INVALID_RESPAWN_SPEED = 0xFFFFFFFF,
    RESPAWN_SPEED_NONE = 0x0,
    RESPAWN_SPEED_SLOW = 0x1,
    RESPAWN_SPEED_MEDIUM = 0x2,
    RESPAWN_SPEED_FAST = 0x3,
    NUM_RESPAWN_SPEEDS = 0x4,
};

namespace keen
{
	enum PixelFormat
	{
		PixelFormat_None = 0x0,
		PixelFormat_Bc1 = 0x1,
		PixelFormat_Bc1_Gamma = 0x2,
		PixelFormat_Bc2 = 0x3,
		PixelFormat_Bc2_Gamma = 0x4,
		PixelFormat_Bc3 = 0x5,
		PixelFormat_Bc3_Gamma = 0x6,
		PixelFormat_Bc4 = 0x7,
		PixelFormat_Bc4_Gamma = 0x8,
		PixelFormat_Bc5 = 0x9,
		PixelFormat_Bc5_Gamma = 0xA,
		PixelFormat_Bc6H_SF16 = 0xB,
		PixelFormat_Bc6H_UF16 = 0xC,
		PixelFormat_Bc7 = 0xD,
		PixelFormat_Bc7_Gamma = 0xE,
		PixelFormat_Index4 = 0xF,
		PixelFormat_A4 = 0x10,
		PixelFormat_L4 = 0x11,
		PixelFormat_A8 = 0x12,
		PixelFormat_L8 = 0x13,
		PixelFormat_Index8 = 0x14,
		PixelFormat_L4A4 = 0x15,
		PixelFormat_G8R8 = 0x16,
		PixelFormat_R8G8 = 0x17,
		PixelFormat_R5G6B5 = 0x18,
		PixelFormat_R5G5B5A1 = 0x19,
		PixelFormat_R4G4B4A4 = 0x1A,
		PixelFormat_R5G5B5A3 = 0x1B,
		PixelFormat_Index14x2 = 0x1C,
		PixelFormat_R8G8B8 = 0x1D,
		PixelFormat_R8G8B8_Gamma = 0x1E,
		PixelFormat_R32F = 0x1F,
		PixelFormat_Y16X16 = 0x20,
		PixelFormat_A8R8G8B8 = 0x21,
		PixelFormat_A8R8G8B8_Gamma = 0x22,
		PixelFormat_X8R8G8B8 = 0x23,
		PixelFormat_X8R8G8B8_Gamma = 0x24,
		PixelFormat_A8B8G8R8 = 0x25,
		PixelFormat_A8B8G8R8_Gamma = 0x26,
		PixelFormat_R8G8B8A8 = 0x27,
		PixelFormat_R8G8B8A8_Gamma = 0x28,
		PixelFormat_A2R10G10B10F = 0x29,
		PixelFormat_A16B16G16R16F = 0x2A,
		PixelFormat_A32B32G32R32F = 0x2B,
		PixelFormat_Depth8 = 0x2C,
		PixelFormat_Depth16 = 0x2D,
		PixelFormat_Depth24Stencil8 = 0x2E,
		PixelFormat_ETC1_RGB8 = 0x2F,
		PixelFormat_ETC1_RGB8A4 = 0x30,
		PixelFormat_Pvrtc2 = 0x31,
		PixelFormat_Pvrtc4 = 0x32,
		PixelFormat_Pvrtc2A = 0x33,
		PixelFormat_Pvrtc4A = 0x34,
		PixelFormat_Ctx1 = 0x35,
		PixelFormat_DxN = 0x36,
		PixelFormat_Depth32F = 0x37,
		PixelFormat_Depth24FStencil8 = 0x38,
		PixelFormat_R11G11B10F = 0x39,
		PixelFormat_Depth32FStencil8 = 0x3A,
		PixelFormat_Depth16Stencil8 = 0x3B,
		PixelFormat_Count = 0x3C,
		PixelFormat_Invalid = 0x3C,
		PixelFormat_Native_RGBA32 = 0x27,
		PixelFormat_Native_RGBA32_Gamma = 0x28,
		PixelFormat_Default_Depth = 0x2E,
		PixelFormat_Dxt1 = 0x1,
		PixelFormat_Dxt1_Gamma = 0x2,
		PixelFormat_Dxt23 = 0x3,
		PixelFormat_Dxt23_Gamma = 0x4,
		PixelFormat_Dxt45 = 0x5,
		PixelFormat_Dxt45_Gamma = 0x6,
	};

	enum IndexFormat
	{
		IndexFormat_Invalid = 0x0,
		IndexFormat_Uint16 = 0x1,
		IndexFormat_Uint32 = 0x2,
		IndexFormat_Count = 0x3,
	};

	enum PrimitiveType
	{
		PrimitiveType_Invalid = 0xFFFFFFFF,
		PrimitiveType_TriangleList = 0x0,
		PrimitiveType_TriangleStrip = 0x1,
		PrimitiveType_LineList = 0x2,
		PrimitiveType_LineStrip = 0x3,
		PrimitiveType_QuadList = 0x4,
		PrimitiveType_Count = 0x5,
	};
};

enum rl_shadow_lod
{
	RL_SHADOW_LOD_OFF = 0x0,
	RL_SHADOW_LOD_LOW = 0x1,
	RL_SHADOW_LOD_MED = 0x2,
	RL_SHADOW_LOD_HIGH = 0x3,
	RL_NUM_SHADOW_LODS = 0x4,
};

enum rl_antialias_lod
{
	RL_AA_LOD_OFF = 0x0,
	RL_AA_LOD_2X = 0x1,
	RL_AA_LOD_4X = 0x2,
	RL_AA_LOD_8X = 0x3,
	RL_AA_LOD_16X = 0x4,
	RL_AA_LOD_8XQ = 0x5,
	RL_AA_LOD_16XQ = 0x6,
	RL_NUM_AA_LODS = 0x7,
};

enum rl_particle_lod
{
	RL_PARTICLE_LOD_LOW = 0x0,
	RL_PARTICLE_LOD_MED = 0x1,
	RL_PARTICLE_LOD_HIGH = 0x2,
	RL_PARTICLE_LOD_VERY_HIGH = 0x3,
	RL_NUM_PARTICLE_LODS = 0x4,
};

enum rl_anisotropic_filtering_lod
{
	RL_AF_LOD_OFF = 0x0,
	RL_AF_LOD_LOW = 0x1,
	RL_AF_LOD_MED = 0x2,
	RL_AF_LOD_HIGH = 0x3,
	RL_NUM_AF_LODS = 0x4,
};

enum rl_dev_vertex_format
{
	RLVF_INVALID = 0xFFFFFFFF,
	RLVF_PIXLIT = 0x0,
	RLVF_PIXLIT_CA = 0x1,
	RLVF_PIXLIT_NMAP = 0x2,
	RLVF_PIXLIT_NMAP_CA = 0x3,
	RLVF_UNLIT = 0x4,
	RLVF_PARTICLE_POINTSPRITE = 0x5,
	RLVF_PARTICLE_BILLBOARD = 0x6,
	RLVF_PARTICLE_RADIAL = 0x7,
	RLVF_PARTICLE_DROP = 0x8,
	RLVF_PARTICLE_RIBBON = 0x9,
	RLVF_PARTICLE_ORIENTED = 0xA,
	RLVF_PRIMITIVE_3D = 0xB,
	RLVF_PRIMITIVE_2D = 0xC,
	RLVF_SG_MESH = 0xD,
	RLVF_HEIGHT_MESH = 0xE,
	RLVF_HEIGHT_MESH_LOW_LOD = 0xF,
	RLVF_PARTICLE_PARAMETRIC = 0x10,
	RLVF_COMPOSITOR = 0x11,
	RLVF_CLONE_UVS = 0x12,
	RLVF_CLONE_NMAP = 0x13,
	RLVF_CLONE_CLR = 0x14,
	RLVF_2D_SPLINE = 0x15,
	RLVF_PARTICLE_CORONA = 0x16,
	RLVF_PARTICLE_RIBBON_PARAMETRIC = 0x17,
	RLVF_CONDITIONAL_BBOX = 0x18,
	RLVF_TERRAIN_ROAD = 0x19,
	RLVF_HEIGHT_MESH_LANDMARK_LOD = 0x1A,
	RLVF_STAR_FIELD_POINT = 0x1B,
	RLVF_STAR_FIELD_BILLBOARD = 0x1C,
	RLVF_METEOR_SHOWER_LINE = 0x1D,
	RLVF_PIXLIT_0UV = 0x1E,
	RLVF_PIXLIT_1UV = 0x1F,
	RLVF_PIXLIT_1UV_CA = 0x20,
	RLVF_PIXLIT_1UV_NMAP = 0x21,
	RLVF_PIXLIT_1UV_NMAP_CA = 0x22,
	RLVF_PIXLIT_2UV = 0x23,
	RLVF_PIXLIT_2UV_CA = 0x24,
	RLVF_PIXLIT_2UV_NMAP = 0x25,
	RLVF_PIXLIT_2UV_NMAP_CA = 0x26,
	RLVF_PIXLIT_3UV = 0x27,
	RLVF_PIXLIT_3UV_CA = 0x28,
	RLVF_PIXLIT_3UV_NMAP = 0x29,
	RLVF_PIXLIT_3UV_NMAP_CA = 0x2A,
	RLVF_PIXLIT_4UV = 0x2B,
	RLVF_PIXLIT_4UV_CA = 0x2C,
	RLVF_PIXLIT_4UV_NMAP = 0x2D,
	RLVF_PIXLIT_4UV_NMAP_CA = 0x2E,
	RLVF_CLONE_1UV_UVS = 0x2F,
	RLVF_CLONE_2UV_UVS = 0x30,
	RLVF_UNCOMPRESSED_MORPH = 0x31,
	RLVF_NUM_FORMATS = 0x32,
};

enum rl_shader_type
{
	shader_type_invalid = 0xFFFFFFFF,
	shader_type_generic = 0x0,
	shader_type_standard = 0x1,
	shader_type_character = 0x2,
	shader_type_terrain = 0x3,
	num_rl_shader_types = 0x4,
};

enum rl_cull_mode
{
	RL_CULL_CCW = 0x0,
	RL_CULL_CW = 0x1,
	RL_CULL_NONE = 0x2,
	RL_CULL_SHADER_DRIVEN = 0x3,
	NUM_RL_CULL_MODE_VALS = 0x4,
};

enum rl_fill_mode
{
	RL_FILL_POINT = 0x0,
	RL_FILL_LINE = 0x1,
	RL_FILL_SOLID = 0x2,
	NUM_RL_FILL_MODE_VALS = 0x3,
};

enum rl_prim_zbias_mode
{
	RLPZB_NONE = 0x0,
	RLPZB_DECAL = 0x1,
	RLPZB_SHADOW = 0x2,
	RLPZB_DISTORTION = 0x3,
	RLPZB_TERRAIN_LOW_LOD = 0x4,
	RLPZB_NUM_ZBIAS_MODES = 0x5,
};

enum rl_dev_present_result
{
	RL_ACQUIRED = 0x0,
	RL_LOST = 0x1,
	RL_READY = 0x2,
};

struct rl_rect
{
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
};

enum ambient_spawn_density
{
	AMB_SPAWN_DENSITY_INVALID = 0xFFFFFFFF,
	AMB_SPAWN_DENSITY_NONE = 0x0,
	AMB_SPAWN_DENSITY_LOW = 0x1,
	AMB_SPAWN_DENSITY_MEDIUM = 0x2,
	AMB_SPAWN_DENSITY_HIGH = 0x3,
	NUM_AMB_SPAWN_DENSITY = 0x4,
};

enum rl_decal_type
{
	RLDT_INVALID = 0xFFFFFFFF,
	RLDT_PLANAR = 0x0,
	RLDT_CLONE_MESH = 0x1,
	NUM_RL_DECAL_TYPES = 0x2,
};

/*enum rl_renderable_instance_sort_method /rl_renderable_instance::sort_method
{
	SORT_METHOD_NONE = 0x0,
	SORT_METHOD_BACK_TO_FRONT = 0x1,
	SORT_METHOD_FRONT_TO_BACK = 0x2,
	SORT_METHOD_FIRST = 0x3,
	SORT_METHOD_LAST = 0x4,
};

enum rl_renderable_instance_pass_flags /rl_renderable_instance::pass_flags
{
	PASS_FLAGS_DISTORTION = 0x1,
	PASS_FLAGS_GLOW = 0x2,
	PASS_FLAGS_HALF_RES = 0x4,
	PASS_FLAGS_QUARTER_RES = 0x8,
	PASS_FLAGS_OUTLINE_0 = 0x10,
	PASS_FLAGS_OUTLINE_1 = 0x20,
	PASS_FLAGS_OUTLINE_2 = 0x40,
	PASS_FLAGS_OUTLINE_3 = 0x80,
	PASS_FLAGS_XRAY_EFFECT = 0x100,
	PASS_FLAGS_ADDITIVE = 0x200,
	PASS_FLAGS_DISTORTION_ONLY = 0x400,
	PASS_FLAGS_FORCE_SIZEOF_ENUM = 0xFFFFFFFF,
};

enum rl_renderable_instance_flags /rl_renderable_instance::flags
{
	FLAGS_IS_TRANSPARENT = 0x20,
	FLAGS_CASTS_SHADOWS = 0x40,
	FLAGS_IS_BATCHABLE = 0x80,
	FLAGS_CASTS_DROP_SHADOWS = 0x100,
	FLAGS_CAST_TRANSPARENT_SHADOWS = 0x200,
	FLAGS_CASTS_TERRAIN_SHADOWS = 0x400,
	NUM_FLAGS = 0xB,
};*/

enum rl_renderable_instance_sort_method //rl_renderable_instance::sort_method
{
	SORT_METHOD_NONE = 0x0,
	SORT_METHOD_BACK_TO_FRONT = 0x1,
	SORT_METHOD_FRONT_TO_BACK = 0x2,
	SORT_METHOD_FIRST = 0x3,
	SORT_METHOD_LAST = 0x4,
};
/*
enum rl_renderable_instance_pass_flags /rl_renderable_instance::pass_flags
{
	PASS_FLAGS_DISTORTION = 0x1,
	PASS_FLAGS_GLOW = 0x2,
	PASS_FLAGS_HALF_RES = 0x4,
	PASS_FLAGS_QUARTER_RES = 0x8,
	PASS_FLAGS_OUTLINE_0 = 0x10,
	PASS_FLAGS_OUTLINE_1 = 0x20,
	PASS_FLAGS_OUTLINE_2 = 0x40,
	PASS_FLAGS_OUTLINE_3 = 0x80,
	PASS_FLAGS_XRAY_EFFECT = 0x100,
	PASS_FLAGS_ADDITIVE = 0x200,
	PASS_FLAGS_DISTORTION_ONLY = 0x400,
	PASS_FLAGS_FORCE_SIZEOF_ENUM = 0xFFFFFFFF,
};

enum rl_renderable_instance_flags
{
	FLAGS_IS_TRANSPARENT = 0x20,
	FLAGS_CASTS_SHADOWS = 0x40,
	FLAGS_IS_BATCHABLE = 0x80,
	FLAGS_CASTS_DROP_SHADOWS = 0x100,
	FLAGS_CAST_TRANSPARENT_SHADOWS = 0x200,
	FLAGS_CASTS_TERRAIN_SHADOWS = 0x400,
	NUM_FLAGS = 0xB,
};*/

enum gfm_alert_levels
{
	ALERT_LEVEL_INVALID = 0xFFFFFFFF,
	ALERT_LEVEL_GREEN = 0x0,
	ALERT_LEVEL_YELLOW = 0x1,
	ALERT_LEVEL_ORANGE = 0x2,
	ALERT_LEVEL_RED = 0x3,
	NUM_ALERT_LEVELS = 0x4,
};

enum world_deserialize_state
{
	DS_IDLE = 0x0,
	DS_PENDING = 0x1,
	DS_COLLECT = 0x2,
	DS_COMPRESS = 0x3,
	DS_SAVE_FINALIZE = 0x4,
};

enum world_zone_state
{
	WZS_UNLOADED = 0x0,
	WZS_STREAMING = 0x1,
	WZS_LOADED = 0x2,
};

enum world_state_mode
{
	WSM_DEFAULT = 0x0,
	WSM_CHECKPOINT = 0x1,
	NUM_WORLD_STATE_MODES = 0x2,
};

enum rl_outline_layer
{
	RLOL_DISABLED = 0x0,
	RLOL_USE_COLOR0 = 0x1,
	RLOL_USE_COLOR1 = 0x2,
};

struct rl_base_object
{
	rl_base_objectVtbl *vfptr;
	unsigned int m_leaf_class_id;
};

/* 3587 */
struct rl_base_objectVtbl
{
	void *(__thiscall *__vecDelDtor)(rl_base_object* This, unsigned int);
	void(__thiscall *release)(rl_base_object* This);
};

struct plane //16
{
	vector normal; //12
	float offset; //4
};

struct rl_3d_entity : rl_base_object
{
	matrix43 m_world_matrix;
};

struct rl_handle
{
	unsigned int m_handle_i;
};

struct rl_sphere //16
{
	vector m_position; //12
	float m_radius; //4
};

struct rl_bvolume //32
{
	rl_sphere m_sphere; //16
	vector m_half_vec; //12
	float m_pad; //4
};

struct rl_partition_sector_entry;
struct linked_list_p__rl_partition_sector_entry
{
	rl_partition_sector_entry* m_head_p;
	int m_elem_count;
};

struct rl_partition_sector : rl_base_object
{
	linked_list_p__rl_partition_sector_entry m_entries;
	int m_child_count;
	rl_partition_sector **m_children;
	vector m_position;
	__declspec(align(16)) rl_bvolume m_world_bvolume;
};

struct rl_partition_system : rl_base_object
{
	rl_partition_sector *m_root_sector_p;
};

struct rl_scene_entity;
struct rl_partition_sector_entry
{
	rl_partition_sector *m_sector_p;
	rl_scene_entity *m_entity_p;
	rl_partition_sector_entry *next;
	rl_partition_sector_entry *prev;
};

struct rl_scene;
struct __declspec(align(16)) rl_scene_entity : rl_3d_entity
{
	rl_scene_entity *prev;
	rl_scene_entity *next;
	unsigned __int16 m_flags;
	unsigned __int16 m_pass_flags;
	float m_lod_off_distance;
	int m_gpu_vis_index;
	__declspec(align(8)) rl_bvolume m_world_bvolume;
	rl_bvolume m_local_bvolume;
	unsigned int m_vis_pass_flags;
	float m_camera_distance_squared;
	unsigned __int16 m_visibility_list_index;
	char m_category_id;
	char m_last_visibility_pass;
	rl_partition_system* m_partition_system_p;
	rl_partition_sector_entry m_partition_sector_entry;
	rl_scene *m_scene_p;
};

struct rl_color_float
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct __declspec(align(4)) rl_skybox_orbital_params
{
	rl_color_float tint;
	vector position;
	float scale;
	int texture_handle;
	bool alpha_blend;
};

struct rl_color_correct_state
{
	rl_color_float m_tint;
	float m_saturation;
	float m_gamma;
	float m_levels_pregamma_offset;
	float m_levels_pregamma_scale;
	float m_levels_postgamma_offset;
	float m_levels_postgamma_scale;
};

struct rl_fog_state
{
	float m_height_density;
	float m_atmosphere_scale;
	float m_density;
	float m_density_offset;
	rl_color_float m_color;
};

struct rl_particle_lighting_state
{
	rl_color_float m_ambient_color;
	rl_color_float m_tod_color;
	vector m_tod_light_dir;
};

struct rl_xray_render_state
{
	bool m_xray_effect_enabled;
	bool m_use_terrain_occlusion;
	float m_xray_effect_fade_start;
	float m_xray_effect_fade_dist;
	vector2 m_xray_outline_points[8];
	int m_num_xray_outline_points;
};

struct rl_outline_state
{
	rl_color_float colors[2];
	rl_outline_layer layer[4];
};

struct bbox
{
    bbox(const bbox& other)
        : min(other.min),
          max(other.max)
    {
    }

    bbox& operator=(const bbox& other)
    {
        if (this == &other)
            return *this;
        min = other.min;
        max = other.max;
        return *this;
    }

    bbox(const vector& min, const vector& max)
        : min(min),
          max(max)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const bbox& obj)
    {
        return os
            << "\nmin: " << obj.min
            << "\nmax: " << obj.max;
    }

	vector min;
	vector max;
};

struct rl_aabb : bbox
{

};

struct rl_renderable_instance;
struct rl_decal : rl_base_object
{
	rl_decal* sys_prev;
	rl_decal* sys_next;
	rl_decal* next;
	rl_decal* prev;
	vector m_relative_pos;
	matrix m_relative_orient;
	int m_birth_time;
	int m_fade_time;
	int m_lifetime;
	rl_decal_type m_decal_type;
	unsigned int m_decal_flags;
	rl_aabb m_local_aabb;
	rl_color_float m_color;
	float m_fade_pct;
	rl_renderable_instance *m_owner;
	unsigned int m_generic_ri_handle;
	unsigned int m_handle;
};

struct rl_named_object : rl_base_object
{

};

struct rl_renderable : rl_named_object
{
	rl_renderable *prev;
	rl_renderable *next;
	rl_bvolume m_local_bvolume;
};

struct rl_callback_widgetVtbl;
struct rl_callback_widget
{
	rl_callback_widgetVtbl *vfptr;
	rl_callback_widget *next;
	rl_callback_widget *prev;
};

struct rl_callback_widgetVtbl
{
	void*(__thiscall* __vecDelDtor)(rl_callback_widget* This, unsigned int);
	void(__thiscall* on_callback)(rl_callback_widget* This);
};

struct rl_callback_widget_list
{
	rl_callback_widget* m_head;
};

struct rl_renderable_instance : rl_scene_entity
{
	rl_renderable_instance *prev;
	rl_renderable_instance *next;
	__declspec(align(16)) vector4 m_instance_parameters;
	vector m_tint;
	rl_renderable *m_renderable_p;
	float m_opacity;
	__int16 m_batching_complexity;
	__int16 m_lod_level;
	rl_decal *m_decal_list;
	rl_callback_widget_list m_on_death;
	rl_renderable_instance_sort_method m_sort_method;
	int m_conditional_index;
	unsigned __int16 m_sort_priority;
	char m_xray_opacity;
	char m_xray_material_handle;
};

/*struct __cppobj rl_visibility_manager::visibility_pass_info
{
	unsigned int pass_index;
	unsigned int pass_index_shifted;
	unsigned int dependent_pass_index;
	unsigned int vis_pass_flags;
	rl_sphere bounding_sphere;
	unsigned int se_culling_flags;
	unsigned int ri_pass_culling_flags;
	rl_frustum culling_frustum;
};

struct rl_visibility_manager::visible_sector_entry
{
	rl_partition_sector *sector_p;
	unsigned int pass_fully_visible_flags;
	unsigned int occluder_use_flags;
	unsigned int pass_visibility_flags;
	unsigned int pass_occlusion_flags;
};

struct __cppobj rl_visibility_manager : rl_base_object
{
	__declspec(align(16)) rl_view_frustum m_view_frustum;
	rl_view_frustum m_low_lod_view_frustum;
	rl_view_frustum m_landmark_lod_view_frustum;
	rl_3d_entity *m_viewer_p;
	bool m_lod_off_enabled;
	pool_list<rl_occluder *> m_actual_occluders;
	pool_list<rl_occluder *> m_potential_occluders;
	rl_occluder *m_merged_occluder_p;
	int m_last_visibility_pass;
	unsigned __int64 m_render_category_filter;
	unsigned int m_num_entities_in_frustum;
	unsigned int m_num_entities_occluded;
	unsigned int m_num_entities_lod_offed;
	farray<rl_visibility_manager::visibility_pass_info, 31> m_visibility_passes;
	farray<rl_visibility_manager::visible_sector_entry, 5000> m_visible_sectors;
	farray<pool_list<rl_scene_entity *> *, 8> m_visibility_lists;
	pool_list<rl_light *> *m_visible_light_list;
	unsigned int m_base_pass_vis_index;
	unsigned int m_clb_base_vis_index;
	unsigned int m_drop_shadow_vis_index;
	unsigned int m_distortion_vis_index;
	unsigned int m_base_shadow_vis_index;
	unsigned int m_outline_vis_index[4];
	unsigned int m_xray_pass_vis_index;
	unsigned int m_xray_terrain_vis_index;
	unsigned int m_non_shadow_vis_flags;
	unsigned int m_shadow_vis_flags;
	unsigned int m_shadow_min_max_flags;
	float m_shadow_min_y;
	float m_shadow_max_y;
};*/

struct __declspec(align(16)) rl_light : rl_scene_entity
{
	rl_light *prev;
	rl_light *next;
	rl_light_light_type m_light_type;
	rl_color_float m_color;
	float m_attenuation_start;
	float m_attenuation_end;
	float m_hotspot_falloff_size;
	float m_hotspot_size;
	vector m_clip_min;
	vector m_clip_max;
	vector m_light_direction;
	rl_renderable_instance *m_clip_mesh;
	unsigned __int16 m_vis_pass_index;
	unsigned __int16 m_shadow_vis_pass_index;
};

struct base_array__rl_occluder_ptr__Vtbl;
struct rl_occluder;
struct base_array__rl_occluder_ptr
{
	base_array__rl_occluder_ptr__Vtbl* vfptr;
	rl_occluder **elt;
	int array_size;
	int num;
};

/* 3709 */
struct base_array__rl_occluder_ptr__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__rl_occluder_ptr* This, unsigned int);
};

/* 3712 */
struct pool_list__rl_occluder_ptr : base_array__rl_occluder_ptr
{
	bool m_init_dynamic;
	unsigned int m_min_used;
};

namespace keen
{
	const struct FragmentShader
	{
		ID3D11PixelShader *pPixelShader;
	};

	const struct VertexShader
	{
		rfg::Array<unsigned char> shaderCode;
		ID3D11VertexShader* pVertexShader;
		rfg::Array<_D3D11_SIGNATURE_PARAMETER_DESC> inputSignature;
		unsigned int inputSignatureHash;
	};

	/* 3262 */
	struct ShaderPipeline
	{
		keen::VertexShader *pVertexShader;
		keen::FragmentShader *pFragmentShader;
	};

	struct GraphicsStateObject
	{
		unsigned int hash;
		unsigned int refCount;
	};

	struct VertexAttributeDescription
	{
		char id;
		char format;
		char inputStreamIndex;
		char instanceStepRate;
	};

	const struct VertexFormat : keen::GraphicsStateObject
	{
		keen::VertexAttributeDescription attributes[17];
		unsigned int attributeOffsets[17];
		unsigned int attributeCount;
		unsigned int attributeIndices[17];
		unsigned int streamStride[6];
		unsigned int instanceDataStreamIndex;
	};

	const struct VertexInputBinding : keen::GraphicsStateObject
	{
		keen::VertexFormat *pVertexFormat;
		ID3D11InputLayout *pLayout;
		unsigned int geometryModeMask;
	};

	struct DynamicConstantBuffer
	{
		ID3D11Buffer *pBuffer;
		unsigned int sizeInBytes;
	};

	struct VertexBufferData
	{
		ID3D11Buffer* pBuffer;
		unsigned int vertexCount;
		unsigned int offset;
	};

	struct GeometryInstancingBuffer
	{
		ID3D11DeviceContext* pContext;
		ID3D11Buffer* pVertexBuffer;
		unsigned int currentPosition;
		unsigned int size;
	};

	struct CommonVertexShaderConstants
	{
		keen::GraphicsMatrix44 projTM;
		keen::GraphicsMatrix44 viewTM;
		keen::GraphicsMatrix43 camRot;
		keen::float4 camPos;
		keen::float4 time;
		keen::float4 fogDistance;
		keen::float3 renderOffset;
		float renderOffset_dummy0;
		keen::float4 targetDimensions;
	};

	struct CommonFragmentShaderConstants
	{
		keen::float2 saturation;
		float dummy0;
		float dummy1;
		keen::float4 time;
		keen::float4 ambient;
		keen::float4 backAmbient;
		keen::float4 fogColor;
		keen::float4 shadowFadeParams;
		keen::float4 targetDimensions;
		keen::float4 indirectLightParams;
		float substanceSpecAlphaScale;
		float substanceSpecPowerScale;
		float substanceDiffuseScale;
		float substanceFresnelAlphaScale;
		float substanceFresnelPowerScale;
		float glassFresnelBias;
		float glassFresnelPower;
		float glassReflectionEnabled;
		float glassDirtEnabled;
		float dummy2;
		float dummy3;
		float dummy4;
	};

	struct InstanceVertexShaderConstants
	{
		keen::GraphicsMatrix43 objTM;
		keen::float4 instanceData;
		keen::float3 Terrain_subzone_offset;
		float Terrain_subzone_offset_Dummy0;
	};

	struct InstanceFragmentShaderConstants
	{
		keen::float4 tint;
		float alphaTestRef;
		unsigned int doExplicitAlphaTest;
		unsigned int doExplicitAlphaTest_dummy0;
		unsigned int doExplicitAlphaTest_dummy1;
	};

	struct DecalVertexShaderConstants
	{
		keen::float3 xvec;
		float xvec_Dummy0;
		keen::float3 yvec;
		float yvec_Dummy0;
		keen::float3 zvec;
		float zvec_Dummy0;
		keen::float3 pos;
		float pos_Dummy0;
		keen::float4 tint;
		keen::float4 params1;
		keen::float4 params2;
	};

	/*struct DownsampleDepthContext
	{
		keen::DownsampleDepthVariants shaders;
		keen::CopyDepthVariants copyDepthShader;
		keen::DynamicConstantBuffer *pConstantBuffer;
		keen::RasterizerState *pRasterizerState;
		keen::SamplerState *pDepthBufferSamplerState;
		keen::VertexInputBinding *pVertexInputBinding;
		keen::VertexInputBinding *pCopyVertexInputBinding;
		keen::BlendState *pDepthBlendState;
		keen::DepthStencilState *pDepthDepthStencilState;
		keen::BlendState *pStencilBlendState;
		keen::DepthStencilState *pStencilDepthStencilState;
		keen::StockVertexPos2f vertexData[3];
	};*/

	struct RenderTarget;
	struct GraphicsCommandBuffer
	{
		ID3D11DeviceContext *pContext;
		ID3D11Buffer *pMappedConstantBuffer;
		keen::RenderTarget *pCurrentRenderTarget;
		void* pSkinningBuffer; //keen::SkinningD3D11 *pSkinningBuffer;
		ID3D11Buffer *pImmediateVertexData;
		unsigned int immediateVertexBufferOffset;
		unsigned int immediateVertexBufferSize;
		unsigned int immediateVertexDataStride;
		unsigned int immediateVertexCount;
		keen::PrimitiveType immediatePrimitiveType;
		void* pDownsampleDepthContext; //keen::DownsampleDepthContext *pDownsampleDepthContext;
		keen::VertexFormat* pCurrentlyBoundVertexFormat;
		void *pRenderCommandBufferStorage;
		bool quadlistImmediateCommand;
		char *pCurrentImmediateBuffer;
		char quadBuffer[65536];
	};

	/*struct TextureData;
	struct GraphicsCommandWriter
	{
		keen::GraphicsCommandBuffer* m_pBuffer;
		keen::GraphicsSystem* m_pGraphicsSystem;
		keen::RenderTarget* m_pRenderTarget;
		keen::VertexInputBinding* m_pVertexInputBinding;
		keen::BlendState* m_pBlendState;
		keen::RasterizerState* m_pRasterizerState;
		keen::DepthStencilState* m_pDepthStencilState;
		keen::SamplerState* m_fragmentShaderSamplerStates[16];
		keen::TextureData* m_fragmentShaderTextures[16];
		keen::ShaderPipeline* m_pShaderPipeline;
		keen::TextureData* m_vertexShaderTextures[16];
		keen::SamplerState* m_vertexShaderSamplerStates[16];
		keen::VertexFormat* m_screenQuadVertexFormats[3];
		keen::RenderTarget* m_renderPassStack[4];
		keen::StaticConstantBuffer* m_currentStaticVertexConstantBuffers[8];
		keen::StaticConstantBuffer* m_currentStaticFragmentConstantBuffers[8];
		unsigned int m_renderPassStackIndex;
		unsigned int m_stencilRefValue;
		unsigned int m_mappedConstantBufferSlotIndex;
	};*/

	struct BlendState : keen::GraphicsStateObject
	{
		ID3D11BlendState* pState;
	};

	struct DepthStencilState : keen::GraphicsStateObject
	{
		ID3D11DepthStencilState *pState;
	};

	struct RasterizerState : keen::GraphicsStateObject
	{
		ID3D11RasterizerState* pState;
	};

	struct SamplerState : keen::GraphicsStateObject
	{
		ID3D11SamplerState *pState;
	};

	struct SizedArray__unsigned_int
	{
		unsigned int *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	struct Stack__unsigned_int
	{
		keen::SizedArray__unsigned_int m_data;
	};

	struct ZoneAllocator
	{
		keen::MemoryBlock m_memory;
		char* m_pCurrentAddress;
	};

	struct ZoneAllocatorAdapter
	{
		ZoneAllocator m_allocator;
		unsigned int m_allocationCount;
	};

	struct MemoryAllocator
	{
		void* vfptr; //keen::MemoryAllocatorVtbl *vfptr;
	};

	struct Mutex
	{
		char m_name[32];
		unsigned int m_criticalSectionData[6];
	};

	struct BaseMemoryAllocator__keen_ZoneAllocatorAdapter : keen::MemoryAllocator
	{
		keen::Mutex m_mutex;
		char m_name[128];
		keen::ZoneAllocatorAdapter m_allocator;
		keen::MemoryBlock m_memoryBlock;
		unsigned int m_allocatedSize;
		unsigned int m_maxAllocatedSize;
		unsigned int m_allocationCount;
		unsigned int m_flags;
	};

	struct ZoneMemoryAllocator : keen::BaseMemoryAllocator__keen_ZoneAllocatorAdapter
	{

	};

	struct OcclusionQuery
	{
		ID3D11Query* pQuery;
	};

	struct OcclusionQueryManager
	{
		rfg::Array<keen::OcclusionQuery> m_occlusionQueryPool;
		Stack__unsigned_int m_freeOcclusionQueries;
		keen::ZoneMemoryAllocator m_gpuMemoryAllocator;
	};

	struct TextureDescription
	{
		unsigned __int16 width;
		unsigned __int16 height;
		unsigned __int16 depth;
		unsigned __int16 flags;
		char type;
		char format;
		char lutFormat;
		char multiSampleType;
		char addressModeU;
		char addressModeV;
		char addressModeW;
		char levelCount;
		char cpuAccessMode;
		char gpuAccessMode;
	};

	struct TextureData
	{
		keen::TextureDescription description;
		ID3D11Resource *pTexture;
		ID3D11ShaderResourceView *pShaderView;
		DXGI_FORMAT d3dFormat;
	};

	struct RenderTargetBuffer
	{
		keen::PixelFormat format;
		keen::TextureData* pDataBuffer;
	};

	const struct RenderTarget
	{
		ID3D11RenderTargetView* renderTargetViews[8];
		ID3D11DepthStencilView* pDepthBufferView;
		keen::RenderTargetBuffer colorBuffers[8];
		keen::RenderTargetBuffer depthBuffer;
		unsigned int colorBufferCount;
		unsigned int width;
		unsigned int height;
	};

	struct GaussBlurVariants
	{
		keen::FragmentShader *m_fragmentShaders[1];
		keen::VertexShader *m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[1];
	};

	struct SsaoCalcVariants
	{
		keen::FragmentShader *m_fragmentShaders[6];
		keen::VertexShader *m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[6];
	};

	struct SsaoBlurVariants
	{
		keen::FragmentShader *m_fragmentShaders[3];
		keen::VertexShader *m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[3];
	};

	struct SsaoMinifyVariants
	{
		keen::FragmentShader *m_fragmentShaders[1];
		keen::VertexShader *m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[1];
	};

	struct FxaaShaderVariants
	{
		keen::FragmentShader* m_fragmentShaders[2];
		keen::VertexShader* m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[2];
	};

	struct FxaaContext
	{
		keen::BlendState *pBlendState;
		keen::RasterizerState *pRasterizerState;
		keen::DepthStencilState *pDepthStencilState;
		keen::SamplerState *pSamplerState;
		keen::VertexInputBinding *pVertexInputBinding;
		keen::FxaaShaderVariants shaderVariants;
		keen::DynamicConstantBuffer *pConstantBuffer;
	};

	struct Event
	{
		void *m_eventHandle;
	};

	struct Thread
	{
		void* m_threadHandle;
		unsigned int m_threadId;
		volatile void* m_pArgument;
		char m_identifier[64];
		bool m_quitRequested;
		int(__cdecl *m_pFunction)(keen::Thread*);
	};

	namespace graphics
	{
		enum WindowMode
		{
			WindowMode_Windowed = 0x0,
			WindowMode_Borderless = 0x1,
			WindowMode_Fullscreen = 0x2,
			WindowMode_Count = 0x3,
		};
	};
};

struct rl_dev_blend_state
{
	keen::BlendState* m_internal_state_p;
};

struct  rl_dev_sampler_state
{
	keen::SamplerState* m_internal_state_p;
};

struct  rl_dev_depth_stencil_state
{
	keen::DepthStencilState* m_internal_state_p;
};

struct  rl_dev_rasterizer_state
{
	keen::RasterizerState* m_internal_state_p;
};

struct new_rl_level_of_detail_settings
{
	char m_texture_reduction;
	rl_anisotropic_filtering_lod m_anisotropic_filtering;
};

struct  rl_level_of_detail
{
	rl_shadow_lod m_shadow_lod;
	rl_antialias_lod m_aa_lod;
	rl_particle_lod m_particle_lod;
	bool m_soft_shadows;
	bool m_bloom_enabled;
	bool m_motion_blur_enabled;
	bool m_depth_of_field_enabled;
	bool m_distortion_enabled;
	bool m_ssao_enabled;
	bool m_sun_shafts_enabled;
	new_rl_level_of_detail_settings m_new_data;
	char padding[120];
};

struct  new_rl_screen_info_settings
{

};

struct  __declspec(align(4)) rl_screen_info
{
	int m_current_width;
	int m_current_height;
	int m_rr_num;
	int m_rr_den;
	float m_aspect_ratio;
	unsigned int m_monitor;
	keen::graphics::WindowMode m_window_mode;
	bool m_vsync_enabled;
	new_rl_screen_info_settings m_new_info;
	char padding[127];
};

struct rl_dev_render_target
{
	keen::RenderTarget* pData;
};

struct rl_dev_depth_stencil_target
{
	keen::RenderTarget* pData;
};

struct  rl_material_state_store
{
	rl_primitive_state old_state[8];
	rl_primitive_state implicit_state;
};

struct  rl_iterrain_renderer : rl_base_object
{

};

struct __declspec(align(4)) rl_deferred_batch_item
{
	unsigned int def_id;
	float dist_sq;
	bool opacity_fade;
};

struct rl_deferred_batch_info
{
	rl_deferred_batch_item *m_elem;
	unsigned int m_max_items;
	volatile unsigned int m_num_items;
};

struct rl_dev_texture
{
	keen::TextureData *pData;
};

struct rl_dyn_texture_base : rl_base_object
{
	int m_tex_handle;
};

struct rl_dyn_texture : rl_dyn_texture_base
{
	rl_dev_texture m_dev_texture;
};

struct rl_render_texture
{
	rl_dyn_texture* m_dyn_texture_p;
	rl_dev_texture m_msaa_texture;
	rl_dev_render_target m_render_target;
	rl_dev_depth_stencil_target m_depth_stencil_target;
	unsigned int m_flags;
};

struct rl_shader_const_ref
{
	unsigned int m_ref;
};

struct rl_gaussian5x5_blur_kernel : rl_sampling_offsets
{
	rl_sampling_vector m_values[17];
};

struct rl_scene_renderer_saved_texture
{
	rl_render_texture* m_render_texture_p;
	rl_dev_texture m_saved_texture;
	unsigned int m_width;
	unsigned int m_height;
};

struct SsaoContext
{
	keen::SsaoCalcVariants ssaoCalcVariants;
	keen::SsaoBlurVariants ssaoBlurVariants;
	keen::SsaoMinifyVariants ssaoMinifyVariants;
	keen::DynamicConstantBuffer *pCalcFragmentShaderConstants;
	keen::DynamicConstantBuffer *pBlurFragmentShaderConstants;
	keen::VertexInputBinding *pInputBindingCalc[5];
	keen::VertexInputBinding *pInputBindingBlur[3];
	keen::SamplerState *pDepthMapSamplerState;
	keen::DepthStencilState *pDepthStencilState[2];
	keen::BlendState *pBlendState[2];
	keen::RasterizerState *pRasterizerState;
};

struct GaussBlurContext
{
	keen::GaussBlurVariants gaussBlurVariants;
	keen::DynamicConstantBuffer *pFragmentShaderConstants;
	keen::VertexInputBinding *pInputBinding;
	keen::SamplerState *pSamplerState;
	keen::DepthStencilState *pDepthStencilState;
	keen::BlendState *pBlendState;
	keen::RasterizerState *pRasterizerState;
};

struct rl_depth_of_field
{
	unsigned int m_dof_effect;
	rl_shader_const_ref m_near_clip_params;
	rl_shader_const_ref m_focal_params;
	rl_shader_const_ref m_dof_equation_near;
	rl_shader_const_ref m_dof_lerp_scale;
	rl_shader_const_ref m_dof_lerp_bias;
	rl_shader_const_ref m_override_blur_percent;
	rl_shader_const_ref m_dof_equation_far;
	rl_shader_const_ref m_depth_sampling_offsets_const;
	rfg::rl_downscale_sampling_offsets<9> m_depth_sampling_offsets;
};

struct rl_shader_technique_ref
{
	int m_ref;
};

struct rl_distortion
{
	unsigned int m_distortion_effect;
	rl_shader_const_ref m_distortion_scale;
	rl_shader_const_ref m_blur_scale;
	rl_shader_technique_ref m_technique_base;
	rl_shader_technique_ref m_technique_diffraction;
};

struct rl_motion_blur
{
	unsigned int m_motion_blur_effect;
	rl_shader_technique_ref m_camera_based_tech;
	rl_shader_technique_ref m_radial_tech;
	rl_shader_const_ref m_curr_to_prev_const;
	rl_shader_const_ref m_blur_scale;
	rl_shader_const_ref m_blur_clamp;
	rl_shader_const_ref m_radial_blur_radius;
	rl_shader_const_ref m_radial_blur_position;
	matrix44 m_view_proj_prev;
	vector m_render_offset_prev;
};

struct rl_shadow_render_parameters
{
	matrix44 shadow_texture_matrix;
	unsigned int shadows_enabled;
	unsigned int use_clb_shadows;
	float shadow_max_dist;
	float shadow_fade_start;
	unsigned int shadow_aa_enabled;
	float shadow_percent;
	float shadow_percent_bias;
};

struct __declspec(align(4)) rl_scene_renderer_deferred_sort_entry
{
	rl_renderable_instance* renderable_instance_p;
	rl_renderable_instance_sort_method sort_method;
	unsigned int generic_id;
	int sort_priority;
	float dist_to_camera_sq;
	struct rl_render_pass* render_pass_p;
	int secondary_sort_priority;
	bool opacity_fade;
};

struct rl_camera : rl_scene_entity
{
	matrix44 m_projection_transform;
	matrix44 m_view_transform;
	float m_fov;
	__declspec(align(16)) rl_view_frustum m_frustum;
	rl_view_frustum m_high_lod_frustum;
	float m_near_clip;
	float m_far_clip;
	float m_high_lod_far_clip;
	rl_camera_type m_type;
	bool m_use_pixel_aspect_ratio;
	bool m_depth_of_field_enabled;
	float m_focus_start_A;
	float m_focus_start_B;
	float m_focus_end_A;
	float m_focus_end_B;
	bool m_motion_blur_enabled;
	rl_camera_motion_blur_type m_motion_blur_type;
	float m_motion_blur_amount;
	float m_radial_blur_radius;
	vector2 m_radial_blur_position;
	float m_frame_override_blur;
	float m_signal_noise_scale;
	float m_signal_noise_frequency;
};

struct rl_renderer;
struct rl_scene_renderer_Part2Params
{
	rl_renderer* p_deferredRenderer;
	rl_camera* p_camera;
	bool msaa_enabled;
	rl_scene* p_scene;
	rl_dev_render_target* p_original_rt;
	rl_shadow_render_parameters* p_shadow_render_params;
	rl_hdr_state* p_hdr_state;
	rl_color_correct_state* p_color_correct_state;
	rl_dev_depth_stencil_target* p_original_ds;
	rl_rect* p_original_vp;
};

struct rl_metrics;
struct rl_scene_renderer : rl_base_object
{
	void* m_compositor_p; //rl_compositor *m_compositor_p;
	void* m_hdr_compositor; //rl_hdr_compositor *m_hdr_compositor_p;
	void* m_outline_compositor; //rl_outline_compositor *m_outline_compositor_p;
	unsigned int m_flags;
	rl_scene *m_scene_p;
	rl_iterrain_renderer *m_terrain_renderer_p;
	rfg::pool_list<rl_renderable_instance*> m_visible_renderable_instances;
	rfg::pool_list<rl_light*> m_visible_lights;
	void* m_base_batched_pass; //rl_batched_pass *m_base_batched_pass;
	rl_deferred_batch_info m_deferred_ids_to_add;
	rl_metrics *m_metrics_p;
	unsigned int m_num_transparent_shadow_objects;
	rl_renderable_instance *m_transparent_shadow_objects[100];
	int m_main_scene_target_width;
	int m_main_scene_target_height;
	int m_half_target_width;
	int m_half_target_height;
	int m_particle_brightpass_width;
	int m_particle_brightpass_height;
	int m_distortion_width;
	int m_distortion_height;
	rl_render_texture m_main_scene_render_target;
	rl_render_texture m_half_render_target;
	rl_render_texture m_half_depth_target;
	rl_render_texture m_full_res_particle_target;
	rl_render_texture m_particle_brightpass_target;
	rl_render_texture m_particle_fog_color_target;
	rl_render_texture m_distortion_target;
	rl_dev_depth_stencil_target m_main_scene_depth_stencil_target;
	keen::TextureData *m_pMainSceneDepthTexture;
	rl_dev_depth_stencil_target m_half_depth_stencil_target;
	keen::RenderTarget *m_pMainSceneDepthTarget;
	rl_dev_depth_stencil_target m_main_scene_depth_stencil_target_msaa;
	int m_main_scene_downsample_width;
	int m_main_scene_downsample_height;
	rl_render_texture m_main_scene_downsample_target;
	rl_render_texture m_main_scene_blur_target;
	rl_render_texture m_main_scene_temp_target[2];
	int m_outline_width;
	int m_outline_height;
	rl_render_texture m_outline_target;
	int m_ssao_width;
	int m_ssao_height;
	keen::TextureData *m_pSsaoBlurTexture[2];
	keen::RenderTarget *m_pSsaoBlurTarget[2];
	int m_sun_shafts_skybox_mask_width;
	int m_sun_shafts_skybox_mask_height;
	rl_render_texture m_sun_shafts_skybox_mask_target;
	int m_clb_width;
	int m_clb_height;
	keen::TextureData *m_pClbTexture;
	keen::RenderTarget *m_pClbTarget;
	GaussBlurContext *m_pGaussBlurContext;
	int m_shadow_map_width;
	int m_shadow_map_height;
	rl_render_texture m_shadow_map_target;
	rl_color_float m_particle_fog_color;
	SsaoContext *m_pSsaoContext;
	rl_depth_of_field m_depth_of_field;
	rl_distortion m_distortion;
	rl_motion_blur m_motion_blur;
	keen::FxaaContext *m_pFxaaContext;
	rl_level_of_detail m_level_of_detail;
	rl_level_of_detail m_new_level_of_detail;
	rl_gaussian5x5_blur_kernel m_blur_kernel;
	volatile unsigned int m_num_deferred_sort_entries;
	rl_scene_renderer_deferred_sort_entry m_deferred_sort_entries[9216];
	volatile unsigned int m_num_deferred_sort_entries_first;
	rl_scene_renderer_deferred_sort_entry m_deferred_sort_entries_first[200];
	volatile unsigned int m_num_deferred_sort_entries_last;
	rl_scene_renderer_deferred_sort_entry m_deferred_sort_entries_last[200];
	rfg::farray<rl_renderable_instance *, 50> m_distortion_only_entries;
	rfg::farray<rl_scene_renderer_saved_texture, 16> m_saved_textures;
	rl_dev_texture m_locked_framebuffer_texture;
	unsigned int m_blit_shader;
	void* m_pRecordedCommandBuffer; //struct keen::RecordedCommandBuffer *m_pRecordedCommandBuffer;
	keen::Event m_startPart2Event;
	keen::Event m_endPart2Event;
	keen::Thread m_part2Thread;
	keen::Mutex m_gpuVisMutex;
	rl_scene_renderer_Part2Params m_part2_params;
	keen::MemoryBlock m_commandBufferMemory;
};

//struct rl_base_object;
struct __declspec(align(8)) rl_scene : rl_base_object
{
	rl_scene* prev;
	rl_scene* next;
	bool m_initialized;
    rfg::pool_list<rl_occluder*> m_occluder_list;
	unsigned int m_last_visibility_pass;
	rl_fog_state m_fog_state;
	rl_color_correct_state m_color_correct_state;
	rl_hdr_state m_hdr_state;
	rl_particle_lighting_state m_particle_lighting_state;
	rl_color_float m_ambient_color;
	rl_color_float m_back_ambient_color;
	rl_light* m_largest_light_default_p;
	rl_light* m_largest_light_p;
	void* m_visibility_manager_p; //rl_visibility_manager* m_visibility_manager_p;
	rl_scene_renderer* m_default_scene_renderer_p;
	rl_scene_renderer* m_scene_renderer_p;
	rl_partition_system* m_partition_system_p;
	rl_partition_system* m_light_partition_system_p;
	rl_partition_system* m_low_lod_partition_system_p;
	rl_partition_system* m_landmark_lod_partition_system_p;
	rl_outline_state m_outline_state;
	float m_opacity_distance_start;
	float m_opacity_distance_end;
	rl_renderable_instance* m_skybox_p;
	vector m_render_offset;
	unsigned int m_last_render_offset_update;
	int m_renderable_instance_count;
	int m_light_count;
	unsigned int m_distortion_effect_material;
	float m_time_val;
	float m_time_of_day_val;
	unsigned __int64 m_render_category_filter;
	rl_xray_render_state m_xray_render_state;
	bool m_diffraction_enabled;
};

struct __declspec(align(4)) rl_occluder : rl_scene_entity
{
	rl_occluder *prev;
	rl_occluder *next;
	rl_handle m_handle;
	bool m_occluded;
};

struct rl_metrics : rl_base_object
{
	int m_start_visibility;
	int m_visibility_time;
	int m_start_base_pass;
	int m_base_pass_time;
	int m_start_multipass_lighting;
	int m_multipass_lighting_time;
	int m_start_sort;
	int m_sort_time;
	int m_start_deferred_sorted;
	int m_deferred_sorted_time;
	int m_start_deferred_instanced;
	int m_deferred_instanced_time;
	int m_start_total;
	int m_total_time;
	int m_potential_occluders_count;
	int m_actual_occluders_count;
	int m_occlusion_query_pixels_drawn;
	int m_start_shadow_visibility;
	int m_shadow_visibility_time;
	int m_start_shadow_pass;
	int m_shadow_pass_time;
	int m_start_overlay_pass;
	int m_overlay_pass_time;
	unsigned int m_warning_flags;
};

struct base_alert_level_values
{
	gfm_alert_levels level;
	float min_value;
	float max_value;
	float lower_bound;
	float upper_bound;
	float decay_rate;
	const char* min_value_tag;
	const char* max_value_tag;
	const char* decay_rate_tag;
};

struct alert_value_parameters
{
	object_type type;
	const char* type_name;
	float imp_multipliers[4];
	float damage_mult;
	float death_value;
};

/*
struct cf_keen_open_file
{
	unsigned int m_handle;
	void* m_pFileSystem;//keen::FileSystem* m_pFileSystem;
	unsigned int m_flags;
	unsigned int m_async_num_bytes_to_transfer;
	unsigned int m_async_pad_bytes;
	unsigned int m_async_num_pad_bytes_to_transfer;
	unsigned int m_async_num_bytes_read;
};


struct et_ptr_offset__char_0
{
	int m_offset;
};


struct et_ptr_offset__v_packfile_0
{
	int m_offset;
};


struct PackfileEntrySerializedPointerOffset
{
	int m_offset;
};


struct v_packfile_entry_serialized
{
	et_ptr_offset__char_0 name;
	unsigned int sector;
	unsigned int start;
	unsigned int hash;
	unsigned int size;
	unsigned int compressed_size;
	et_ptr_offset__v_packfile_0 parent;
};


struct v_packfile_entry
{
	char *name;
	unsigned int sector;
	unsigned int start;
	unsigned int hash;
	unsigned int size;
	unsigned int compressed_size;
	v_packfile *parent;
};


struct v_packfile
{
	unsigned int descriptor;
	unsigned int version;
	char short_name[65];
	char pathname[256];
	unsigned int flags;
	unsigned int sector;
	unsigned int num_files;
	unsigned int file_size;
	unsigned int dir_size;
	unsigned int filename_size;
	unsigned int data_size;
	unsigned int compressed_data_size;
	v_packfile_entry *dir;
	v_packfile_entry_serialized *dir_serialized;
	char *filenames;
	char *data;
};


struct keen_cf_packfile_handle
{
	cf_keen_open_file *file_handle;
	v_packfile_entry *packfile_entry;
};


struct cf_memory_handle
{
	char *buf;
	unsigned int size;
	bool compressed;
	unsigned int compressed_size;
};


union cf_file_info //$10968121105CFFA681E301E790211F5F
{
	cf_keen_open_file* m_standard_fp;
	keen_cf_packfile_handle* m_packfile_fp;
	cf_memory_handle* _m_memory_fp;
};


struct cfile
{
	char name[65];
	char full_pathname[257];
	cf_search_types m_searched_system;
	cf_io_access_types m_access_type;
	cf_file_info file_info; //old name: ____u4
	cf_io_media_types m_media_type;
	cfmode_type mode;
	cf_error_codes m_error_code;
	unsigned int pos;
	unsigned int size;
	unsigned int max_write_size;
	unsigned int m_flags;
};*/

struct zone_header
{
	unsigned int signature;
	unsigned int version;
	int num_objects;
	int num_handles;
	unsigned int district_hash;
	unsigned int flags;
};

struct world_state_buf
{
	vector player_start_pos;
	matrix player_start_orient;
	vector player_start_pos_safehouse;
	matrix player_start_orient_safehouse;
	char* buf;
	int cur_size;
	int max_size;
};

struct handle_manager_7280
{
	char status[910];
	unsigned int last_bin;
	unsigned int last_slot;
	unsigned int upper_bits;
};

/*struct base_array__human_info_const_ptr__Vtbl;
struct base_array__human_info_const_ptr
{
	base_array__human_info_const_ptr__Vtbl *vfptr;
	HumanInfo **elt; //human_info
	int array_size;
	int num;
};

struct base_array__human_info_const_ptr__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__human_info_const_ptr* This, unsigned int);
};*/

const struct __declspec(align(4)) human_spawn_group_info
{
	const char *group_name;
	rfg::base_array<HumanInfo const*> h_info_list; //base_array__human_info_const_ptr h_info_list;
	unsigned int name_crc;
	bool homogeneous_team;
};

struct base_array__vehicle_info_const_ptr__Vtbl;
struct base_array__vehicle_info_const_ptr
{
	//Todo: Fill out vehicle_info struct
	/*const vehicle_info& operator [](int index) { return elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }*/

	base_array__vehicle_info_const_ptr__Vtbl* vfptr;
	void** elt; //vehicle_info** elt;
	int array_size;
	int num;
};

struct base_array__vehicle_info_const_ptr__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__vehicle_info_const_ptr* This, unsigned int);
};

struct vehicle_spawn_group_info
{
	const char *group_name;
	base_array__vehicle_info_const_ptr v_info_list;
	unsigned int name_crc;
};

struct ambient_spawn_flags //$AAD2752B7E4D21C5B6F05C7F617B9C71
{
	__int8 ped_spawn_enabled : 1;
	__int8 veh_spawn_enabled : 1;
};

struct __declspec(align(4)) ambient_spawn_info
{
	char *group_name;
	human_spawn_group_info *h_spawn_group;
	vehicle_spawn_group_info *v_spawn_group;
	ambient_spawn_density ped_density;
	ambient_spawn_density night_ped_density;
	ambient_spawn_density veh_density;
	ambient_spawn_density night_veh_density;
	int ambient_behavior_id;
	ambient_spawn_flags ambient_flags;
};

struct vehicle_reservation_info
{
	vehicle_spawn_group_info *spawn_group;
	int count;
};

struct human_reservation_info
{
	human_spawn_group_info *spawn_group;
	int count;
};

struct __declspec(align(4)) spawn_resource_data
{
	const char *name;
	int team_squad_counts[4];
    rfg::farray<human_reservation_info, 16> required_human_slots;
    rfg::farray<vehicle_reservation_info, 7> required_vehicle_slots;
	bool dlc_resource;
};

struct __declspec(align(16)) rl_terrain_occluder : rl_occluder
{
	vector2 m_point1;
	vector2 m_point2;
	float m_height_base;
	float m_height;
	vector m_top_point1;
	vector m_top_point2;
	rl_frustum m_frustum;
	vector m_view_position;
	vector m_occlude_plane_normal;
	bool m_updated;
	vector m_abc1;
	vector m_abc2;
	vector m_abc3;
	vector m_abc4;
	vector m_abc5;
	plane m_occlude_plane;
	vector m_plane_pos;
};

struct terrain_layer_map
{
	int res_x;
	int res_y;
	int bit_depth;
	int data_size;
	int data_p; //et_ptr_offset<unsigned char, 0> data_p;
	int num_materials;
	int material_names; //et_ptr_offset<et_ptr_offset<char, 0>, 0> material_names;
	int material_index; //et_ptr_offset<int, 0> material_index;
};

/* 5301 */
struct terrain_data
{
	vector bmin;
	vector bmax;
	int x_res;
	int z_res;
	int m_num_occluders;
	int m_occluders;//et_ptr_offset<terrain_occluder, 0> m_occluders;
	int m_terrain_material_map_p; //et_ptr_offset<rl_material_map, 0> m_terrain_material_map_p;
	int m_terrain_materials; //et_ptr_offset<et_ptr_offset<rl_material, 0>, 0> m_terrain_materials;
	unsigned int m_num_terrain_materials;
	unsigned int m_minimap_material_handle;
	int m_minimap_material_p; //et_ptr_offset<rl_material, 0> m_minimap_material_p;
	int m_low_lod_patches_p; //et_ptr_offset<terrain_lowlod_patch, 0> m_low_lod_patches_p;
	int m_low_lod_material_p; //et_ptr_offset<rl_material, 0> m_low_lod_material_p;
	int m_low_lod_material_map_p;//et_ptr_offset<rl_material_map, 0> m_low_lod_material_map_p;
	int m_num_subzones;
	int m_subzones; //et_ptr_offset<et_ptr_offset<terrain_subzone_data, 1>, 0> m_subzones;
	int m_pf_data_p; //et_ptr_offset<terrain_pf_data, 0> m_pf_data_p;
	terrain_layer_map m_layer_map;
	unsigned int m_num_ug_layers;
	int m_ug_layers; //et_ptr_offset<undergrowth_layer_data, 0> m_ug_layers;
	int m_ug_cell_data; //et_ptr_offset<undergrowth_cell_data, 0> m_ug_cell_data;
	int m_num_ug_cell_layer_datas;
	int m_ug_cell_layer_data; //et_ptr_offset<undergrowth_cell_layer_data, 0> m_ug_cell_layer_data;
	int m_sug_cell_layer_data; //et_ptr_offset<single_undergrowth_cell_layer_data, 0> m_sug_cell_layer_data;
	unsigned int m_stitch_piece_cm_index;
	int m_num_invisible_barriers;
	int m_invisible_barriers; //et_ptr_offset<invisible_barrier_data, 0> m_invisible_barriers;
	unsigned int m_shape_handle;
	int m_num_sidemap_materials;
	int m_sidemap_data; //et_ptr_offset<terrain_sidemap_data, 1> m_sidemap_data;
	int m_object_p_stub; //et_ptr_offset<object, 0> m_object_p_stub;
	int m_stitch_physics_instances_p; //et_ptr_offset<terrain_stitch_physics_instance, 0> m_stitch_physics_instances_p;
	int m_num_stitch_physics_instances;
	Object* m_object_p;
	unsigned int m_object_p_padding;
	char pad[880];
};

struct rfg_terrain
{
	terrain_data* terrain_data_p;
	char filename[64];
};

struct et_ptr_offset__vector_0
{
	int m_offset;
};

struct et_ptr_offset__nav_cell_0
{
	int m_offset;
};

struct et_ptr_offset__nav_cell_ptr_0
{
	int m_offset;
};

struct et_ptr_offset__nav_cell_outer_edge_0
{
	int m_offset;
};

struct bb_pfg_layer
{
	unsigned int pfg_sig;
	unsigned int pfg_version;
	unsigned __int16 num_vertices;
	int vertices; //et_ptr_offset<vector, 0> vertices;
	unsigned __int16 num_nav_cells;
	int nav_cells; //et_ptr_offset<nav_cell, 0> nav_cells;
	int nav_cell_heap; //et_ptr_offset<nav_cell_ptr, 0> nav_cell_heap;
	unsigned __int16 num_nav_cell_outer_edges;
	int nav_cell_outer_edges; //et_ptr_offset<nav_cell_outer_edge, 0> nav_cell_outer_edges;
	vector bbox_min;
	vector bbox_max;
};

struct bb_pfg_zone
{
	bb_pfg_layer* pfg;
	unsigned int pfg_shape;
	unsigned int pfg_havok_handle;
	bb_pfg_layer* vehicle_pfg;
	unsigned int vehicle_pfg_shape;
	unsigned int vehicle_pfg_havok_handle;
};

struct save_load_info
{
	__int8 pending_new_game : 1;
	__int8 reset_destruction : 1;
	__int8 pending_save_game : 1;
	__int8 performing_save_game : 1;
	__int8 pending_save_state : 1;
	__int8 performing_save_state : 1;
	__int8 pending_single_zone : 1;
	__int8 save_game_warp : 1;
	__int8 game_save_checkpoint : 1;
	__int8 game_save_to_disk : 1;
	__int8 pending_load_game_from_memory : 1;
	__int8 auto_save_game : 1;
	__int8 saving_state_data : 1;
	__int8 player_start_at_safehouse : 1;
	vector player_start_pos;
	matrix player_start_orient;
};

/*struct hammer_unlock_data
{
	char raw_data[8];
};

struct backpack_unlock_data
{
	char raw_data[2];
};*/

struct game_save_info_new_data
{
	char hammers_unlocked_large[8];//hammer_unlock_data hammers_unlocked_large;
	char backpacks_unlocked[2]; //backpack_unlock_data backpacks_unlocked;
	char jetpack_unlock_level;
};

struct __declspec(align(4)) game_save_info
{
	int num_missions_completed;
	int num_activities_completed;
	int districts_liberated;
	int territory_index;
	int district_index;
	int day;
	int month;
	int year;
	int hours;
	int minutes;
	int seconds;
	bool auto_save;
	bool used_slot;
	int dlc_id;
	unsigned int save_slot_index;
	char hammers_unlocked;
	bool golden_hammer_desired;
	game_save_info_new_data new_data;
	char padding[117];
};

struct grid_flags
{
	__int8 play_marauder_howl : 1;
	__int8 marauder_zone : 1;
};

struct __declspec(align(2)) grid_info
{
	unsigned __int16 gid;
	grid_flags flags;
};

struct district_flags
{
	__int8 allow_cough : 1;
	__int8 allow_amb_edf_civilian_dump : 1;
	__int8 play_capstone_unlocked_lines : 1;
	__int8 disable_morale_change : 1;
	__int8 disable_control_change : 1;
};

struct __declspec(align(4)) district : Object
{
	float control;
	float morale;
	float control_max;
	float morale_max;
	float liberated_tech_level;
	int liberated_marauder_level;
	int liberated_edf_level;
	voice_line_handle liberated_radio_line_handle;
	voice_line_handle capstone_line_1;
	voice_line_handle capstone_line_2;
	int min_edf_progression_level;
	bool liberated;
	bool needs_to_play_radio_line;
	district_flags flags;
	color col;
	unsigned int localized_name_hash;
    rfg::farray<grid_info, 21> grid_ids;
	char district_index;
	rl_color_float m_vfx_tint;
	const char *load_screen_images[5];
	char num_load_screen_images;
};

struct t_district
{
	const char *name;
	const char *liberated_radio_line;
	unsigned int localized_name_hash;
	unsigned int localized_name_hash_no_ar;
	float control;
	float control_max;
	float morale;
	float morale_max;
	float tech_level;
	int marauder_level;
	int edf_level;
	int edf_progression_level;
	bool liberated;
	district_flags flags;
	color col;
	color vfx_tint;
	int disc_layer;
	char index;
	const char *thumbnail;
	const char *load_screen_images[5];
	char num_load_screen_images;
	rfg::farray<grid_info, 21> list;
	t_district *next;
	t_district *prev;
};

/* 5341 */
struct territory
{
	const char* name;
	float tech_level_default;
	float tech_level_max;
	char index;
	t_district* districts;
	unsigned __int16* vertical_mask_zones;
	int num_v_mask_zones;
	unsigned __int16* horiz_mask_zones;
	int num_h_mask_zones;
};

/*
struct hash_table<char const *, &string_hash, 255, unsigned char>
{
	hash_table<char const *, &string_hash, 255, unsigned char>Vtbl *vfptr;
	char free;
	char slot[255];
	char next[255];
	const char *entry_key[255];
};

union $F3F56A0CE35B573E2FEC6C4E6DE08A77
{
	void(__thiscall *~hash_table<char const *, &string_hash, 255, unsigned char>)(hash_table<char const *, &string_hash, 255, unsigned char> *this);
	void *(__thiscall *__vecDelDtor)(hash_table<char const *, &string_hash, 255, unsigned char> *this, unsigned int);
};

struct hash_table<char const *, &string_hash, 255, unsigned char>Vtbl
{
	bool(__thiscall *comp_keys)(hash_table<char const *, &string_hash, 255, unsigned char> *this, const char *, const char *);
	$F3F56A0CE35B573E2FEC6C4E6DE08A77 ___u1;
	bool(__thiscall *insert)(hash_table<char const *, &string_hash, 255, unsigned char> *this, const char *);
	bool(__thiscall *save)(hash_table<char const *, &string_hash, 255, unsigned char> *this, cfile *);
};

struct __declspec(align(2)) data_hash_table<char const *, unsigned char, &string_hash, 255, unsigned char> : hash_table<char const *, &string_hash, 255, unsigned char>
{
	char entry_data[255];
};

struct str_data_hash_table<unsigned char, 255, 64, unsigned char> : data_hash_table<char const *, unsigned char, &string_hash, 255, unsigned char>
{
	char str_data[255][64];
};*/

struct stream_grid_cell
{
	unsigned int stream_mask;
	unsigned int srid[4];
	char grid_x;
	char grid_z;
	unsigned __int16 layer_index;
};

struct stream_layer_masked_cell
{
	stream_grid_cell* gc;
	HavokBPO* n_region[4];
};

struct stream_layer
{
	stream_grid_cell** cells;
	int num_cells;
	int dim_x;
	int dim_z;
	int cell_load_distance;
	float stream_radius;
	vector bmin;
	vector bmax;
	vector stream_bmin;
	vector stream_bmax;
	rfg::farray<stream_grid_cell*, 25> active_cells;
	rfg::farray<stream_layer_masked_cell, 50> masked_cells;
	vector cell_dim;
};

enum layout_layer
{
    LAYER_LEVEL = 0x0,
    LAYER_TERRAIN = 0x1,
    NUM_LAYERS = 0x2,
};

struct stream_grid
{
	stream_layer* layers;
	territory* grid_territory;
	unsigned int ns_base;
	unsigned int ns_precache;
	unsigned int landmarks_srid;
	bool compact_super_emergency;
	timestamp_realtime compact_ts;
	timestamp_realtime compact_wait_ts;
	void* m_tmp_table; //str_data_hash_table<unsigned char, 255, 64, unsigned char> *m_tmp_table;
};

struct obj_zone : Object
{
	bb_pfg_zone zone_pfg;
	unsigned int heightfield_shape;
	unsigned int stitch_piece_havok_handle;
	unsigned int district_handle;
	spawn_resource_data* spawn_res_data;
	ambient_spawn_info* amb_spawn_info;
	float wind_min_speed;
	float wind_max_speed;
	rfg_terrain* terrain;
    rfg::farray<rl_terrain_occluder*, 40> m_occluders;
	vector local_bmin;
	vector local_bmax;
	int aabb_phantom_index;
};

struct __declspec(align(4)) world_zone
{
	vector bmin;
	vector bmax;
	char name[64];
	world_zone_state state;
	zone_header* deserialize_header;
	void* deserialize_header_f;//cfile* deserialize_header_f;
	void* deserialize_f;//cfile* deserialize_f;
	world_state_buf stored_zone_state;
	obj_zone* zone_objp;
	unsigned int srid;
	bool is_border_zone;
	handle_manager_7280 obj_handle_mgr;
	unsigned __int16 gid;
};

struct __declspec(align(8)) World //11108
{
	bool mission_object_creation_mode; //1
	vector level_ambient; //12
	vector level_back_ambient; //12
	char last_loaded_territory[64]; //64
	int max_world_objects; //4
	rfg::base_array<Object*> all_objects; //16
	rfg::base_array<unsigned short> type_objects[53]; //848
	rfg::base_array<unsigned short> subtype_objects[11]; //176
	float tech_level; //4
	float tech_level_max; //4
	volatile unsigned int thread_id; //4
	char object_handle_hash[64]; //dynamic_uint_hash_table<object *> object_handle_hash; //64
	char destroyed_object_table[8198]; //hash_table<unsigned int, &hash_uint, 1024, unsigned short> destroyed_object_table; //8198
	void* save_file; //cfile* save_file; //4
	Object* flagged_objects; //4
	Object* current_flagged_object; //4
	char current_flagged_mode; //1
	world_deserialize_state deserialize_state; //4
	void* deserialize_pool; //virtual_mempool* deserialize_pool; //4
	char deserialize_list[144]; //farray<world_zone *, 32> deserialize_list; //144
	world_state_mode cur_world_state; //4
	world_state_buf stored_world_state[2]; //216
	void* compress_steam; //zlib_stream* compress_stream; //4
	void* decompress_steam; //zlib_stream* decompress_stream; //4
	save_load_info sl_flags; //62
	game_save_info* pending_game_save_slot; //4
	int dlc_bundle_id; //4
	char pending_filename[64]; //64
	vector pending_game_load_warp_to_pos; //12
	matrix pending_game_load_warp_to_orient; //36
	volatile bool load_aborted; //4
	stream_grid* grid; //4
	vector stream_pos; //12
	int num_territory_zones; //4
	world_zone** all_zones; //4
	world_zone* global_zone_grid[257]; //1028
	bool is_territory; //1
	char territory_name[128]; //128
	int num_streaming_objects; //4
	bool stub_serialization_in_progress; //1
};
/* World def ends here */























struct vehicle_flags
{
    vehicle_flags()
        : activity(0),
          old_activity(0),
          activity_destroyed(0),
          convoy_vehicle(0),
          ambient_spawn(0),
          death_reported(0),
          no_ragdoll(0),
          despawned_squad_vehicle(0),
          delete_mission_vehicle(0),
          do_not_destroy_with_squad(0),
          m_corpse(0),
          m_despawn_after_fade(0),
          m_door_collision_enabled(0),
          m_engine_running(0),
          m_engine_smoking(0),
          m_fading_in(0),
          m_fading_out(0),
          m_fading_from_nano(0),
          m_hidden(0),
          m_hijacked(0),
          m_scripted_bail(0),
          m_scripted_abandon(0),
          m_horn_down(0),
          m_invulnerable(0),
          m_mission_invulnerable(0),
          m_is_player_car(0),
          m_kill_by_vehicle(0),
          m_mp_honked_horn(0),
          m_needs_repair(0),
          m_occupied(0),
          m_on_fire(0),
          m_nano_sim_fire(0),
          m_nano_sim_smoke(0),
          m_grenade_inside(0),
          m_released_from_cutscene(0),
          m_resource_access_disabled(0),
          m_reverse_last_frame(0),
          m_series_of_honks(0),
          m_siren_dying(0),
          m_siren_audio_on(0),
          m_using_horn(0),
          pass_by_getting_closer(0),
          m_wheels_on_ground(0),
          m_all_wheels_on_ground(0),
          m_only_fire_damage(0),
          m_headlights_on(0),
          m_emergency_lights_on(0),
          high_priority_target(0),
          player_may_capture(0),
          disable_for_npc_drivers(0),
          disable_for_player(0),
          disable_accelerator(0),
          locked_in_place(0),
          fixed_motion(0),
          disable_turrets_for_npcs(0),
          immediate_spawn(0),
          no_player_use(0),
          invisible_driver(0)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const vehicle_flags& obj)
    {
        return os
            << "\nactivity: " << obj.activity
            << "\nold_activity: " << obj.old_activity
            << "\nactivity_destroyed: " << obj.activity_destroyed
            << "\nconvoy_vehicle: " << obj.convoy_vehicle
            << "\nambient_spawn: " << obj.ambient_spawn
            << "\ndeath_reported: " << obj.death_reported
            << "\nno_ragdoll: " << obj.no_ragdoll
            << "\ndespawned_squad_vehicle: " << obj.despawned_squad_vehicle
            << "\ndelete_mission_vehicle: " << obj.delete_mission_vehicle
            << "\ndo_not_destroy_with_squad: " << obj.do_not_destroy_with_squad
            << "\nm_corpse: " << obj.m_corpse
            << "\nm_despawn_after_fade: " << obj.m_despawn_after_fade
            << "\nm_door_collision_enabled: " << obj.m_door_collision_enabled
            << "\nm_engine_running: " << obj.m_engine_running
            << "\nm_engine_smoking: " << obj.m_engine_smoking
            << "\nm_fading_in: " << obj.m_fading_in
            << "\nm_fading_out: " << obj.m_fading_out
            << "\nm_fading_from_nano: " << obj.m_fading_from_nano
            << "\nm_hidden: " << obj.m_hidden
            << "\nm_hijacked: " << obj.m_hijacked
            << "\nm_scripted_bail: " << obj.m_scripted_bail
            << "\nm_scripted_abandon: " << obj.m_scripted_abandon
            << "\nm_horn_down: " << obj.m_horn_down
            << "\nm_invulnerable: " << obj.m_invulnerable
            << "\nm_mission_invulnerable: " << obj.m_mission_invulnerable
            << "\nm_is_player_car: " << obj.m_is_player_car
            << "\nm_kill_by_vehicle: " << obj.m_kill_by_vehicle
            << "\nm_mp_honked_horn: " << obj.m_mp_honked_horn
            << "\nm_needs_repair: " << obj.m_needs_repair
            << "\nm_occupied: " << obj.m_occupied
            << "\nm_on_fire: " << obj.m_on_fire
            << "\nm_nano_sim_fire: " << obj.m_nano_sim_fire
            << "\nm_nano_sim_smoke: " << obj.m_nano_sim_smoke
            << "\nm_grenade_inside: " << obj.m_grenade_inside
            << "\nm_released_from_cutscene: " << obj.m_released_from_cutscene
            << "\nm_resource_access_disabled: " << obj.m_resource_access_disabled
            << "\nm_reverse_last_frame: " << obj.m_reverse_last_frame
            << "\nm_series_of_honks: " << obj.m_series_of_honks
            << "\nm_siren_dying: " << obj.m_siren_dying
            << "\nm_siren_audio_on: " << obj.m_siren_audio_on
            << "\nm_using_horn: " << obj.m_using_horn
            << "\npass_by_getting_closer: " << obj.pass_by_getting_closer
            << "\nm_wheels_on_ground: " << obj.m_wheels_on_ground
            << "\nm_all_wheels_on_ground: " << obj.m_all_wheels_on_ground
            << "\nm_only_fire_damage: " << obj.m_only_fire_damage
            << "\nm_headlights_on: " << obj.m_headlights_on
            << "\nm_emergency_lights_on: " << obj.m_emergency_lights_on
            << "\nhigh_priority_target: " << obj.high_priority_target
            << "\nplayer_may_capture: " << obj.player_may_capture
            << "\ndisable_for_npc_drivers: " << obj.disable_for_npc_drivers
            << "\ndisable_for_player: " << obj.disable_for_player
            << "\ndisable_accelerator: " << obj.disable_accelerator
            << "\nlocked_in_place: " << obj.locked_in_place
            << "\nfixed_motion: " << obj.fixed_motion
            << "\ndisable_turrets_for_npcs: " << obj.disable_turrets_for_npcs
            << "\nimmediate_spawn: " << obj.immediate_spawn
            << "\nno_player_use: " << obj.no_player_use
            << "\ninvisible_driver: " << obj.invisible_driver;
    }

    unsigned __int32 activity : 1; //78
    unsigned __int32 old_activity : 1; //82
    unsigned __int32 activity_destroyed : 1; //86
    unsigned __int32 convoy_vehicle : 1;
    unsigned __int32 ambient_spawn : 1;
    unsigned __int32 death_reported : 1;
    unsigned __int32 no_ragdoll : 1;
    unsigned __int32 despawned_squad_vehicle : 1;
    unsigned __int32 delete_mission_vehicle : 1;
    unsigned __int32 do_not_destroy_with_squad : 1;
    unsigned __int32 m_corpse : 1;
    unsigned __int32 m_despawn_after_fade : 1;
    unsigned __int32 m_door_collision_enabled : 1;
    unsigned __int32 m_engine_running : 1;
    unsigned __int32 m_engine_smoking : 1;
    unsigned __int32 m_fading_in : 1;
    unsigned __int32 m_fading_out : 1;
    unsigned __int32 m_fading_from_nano : 1;
    unsigned __int32 m_hidden : 1;
    unsigned __int32 m_hijacked : 1;
    unsigned __int32 m_scripted_bail : 1;
    unsigned __int32 m_scripted_abandon : 1;
    unsigned __int32 m_horn_down : 1;
    unsigned __int32 m_invulnerable : 1;
    unsigned __int32 m_mission_invulnerable : 1;
    unsigned __int32 m_is_player_car : 1;
    unsigned __int32 m_kill_by_vehicle : 1;
    unsigned __int32 m_mp_honked_horn : 1;
    unsigned __int32 m_needs_repair : 1;
    unsigned __int32 m_occupied : 1;
    unsigned __int32 m_on_fire : 1;
    unsigned __int32 m_nano_sim_fire : 1;
    unsigned __int32 m_nano_sim_smoke : 1;
    unsigned __int32 m_grenade_inside : 1;
    unsigned __int32 m_released_from_cutscene : 1;
    unsigned __int32 m_resource_access_disabled : 1;
    unsigned __int32 m_reverse_last_frame : 1;
    unsigned __int32 m_series_of_honks : 1;
    unsigned __int32 m_siren_dying : 1;
    unsigned __int32 m_siren_audio_on : 1;
    unsigned __int32 m_using_horn : 1;
    unsigned __int32 pass_by_getting_closer : 1;
    unsigned __int32 m_wheels_on_ground : 1;
    unsigned __int32 m_all_wheels_on_ground : 1;
    unsigned __int32 m_only_fire_damage : 1;
    unsigned __int32 m_headlights_on : 1;
    unsigned __int32 m_emergency_lights_on : 1;
    unsigned __int32 high_priority_target : 1;
    unsigned __int32 player_may_capture : 1;
    unsigned __int32 disable_for_npc_drivers : 1;
    unsigned __int32 disable_for_player : 1;
    unsigned __int32 disable_accelerator : 1;
    unsigned __int32 locked_in_place : 1;
    unsigned __int32 fixed_motion : 1;
    unsigned __int32 disable_turrets_for_npcs : 1;
    unsigned __int32 immediate_spawn : 1;
    unsigned __int32 no_player_use : 1;
    unsigned __int32 invisible_driver : 1;
};

struct  squad_flags_struct
{
    unsigned __int32 simulation : 1;
    unsigned __int32 inside_load_dist : 1;
    unsigned __int32 outside_unload_dist : 1;
    unsigned __int32 force_spawn : 1;
    unsigned __int32 leader_has_died : 1;
    unsigned __int32 activity : 1;
    unsigned __int32 old_activity : 1;
    unsigned __int32 ignore_road_spawn : 1;
    unsigned __int32 disallow_reassignment : 1;
    unsigned __int32 player_squad : 1;
    unsigned __int32 stay_in_vehicle : 1;
    unsigned __int32 high_priority_targets : 1;
    unsigned __int32 vehicle_damage_update : 1;
    unsigned __int32 flagged_for_despawn : 1;
    unsigned __int32 squad_icon_is_sticky : 1;
    unsigned __int32 squad_icon_is_closest : 1;
    unsigned __int32 just_spawned : 1;
    unsigned __int32 flier_squad : 1;
    unsigned __int32 reinforcement_squad : 1;
    unsigned __int32 vehicle_infinite_mass : 1;
    unsigned __int32 managed_layer_creation : 1;
    unsigned __int32 dynamic_creation : 1;
    unsigned __int32 mission_created : 1;
    unsigned __int32 hands_off_raid_squad : 1;
    unsigned __int32 special_despawn_rules : 1;
};

struct  npc_flags_struct
{
    unsigned __int32 had_squad : 1;
    unsigned __int32 always_show_on_minimap : 1;
    unsigned __int32 deaf : 1;
    unsigned __int32 force_targetable : 1;
    unsigned __int32 in_cutscene : 1;
    unsigned __int32 not_recruitable : 1;
    unsigned __int32 recruitable_escort : 1;
    unsigned __int32 turning_around : 1;
    unsigned __int32 use_default_team : 1;
    unsigned __int32 reequipping_weapon : 1;
    unsigned __int32 going_left : 1;
    unsigned __int32 going_left_last_time : 1;
    unsigned __int32 passenger_wait : 1;
    unsigned __int32 player_exit_wait : 1;
    unsigned __int32 chase_teleport_disable : 1;
    unsigned __int32 honked_at : 1;
    unsigned __int32 honked_at_friendly : 1;
    unsigned __int32 honked_at_hostile : 1;
    unsigned __int32 activity_related : 1;
    unsigned __int32 mission_related : 1;
    unsigned __int32 ambush_related : 1;
    unsigned __int32 convoy_squad : 1;
    unsigned __int32 civilian_has_been_oppressed : 1;
    unsigned __int32 entered_raid : 1;
    unsigned __int32 raid_cheer : 1;
    unsigned __int32 raid_watch : 1;
    unsigned __int32 return_fire_aim_bonus : 1;
    unsigned __int32 reduced_npc_damage : 1;
    unsigned __int32 maneuver_required : 1;
    unsigned __int32 activity_driver_vr : 1;
    unsigned __int32 activity_pursuit_vr : 1;
    unsigned __int32 activity_pursuit_ca : 1;
    unsigned __int32 activity_ha : 1;
    unsigned __int32 prevent_weapon_draw : 1;
    unsigned __int32 tied_up : 1;
    unsigned __int32 freed_from_bonds : 1;
    unsigned __int32 run_to_safehouse : 1;
    unsigned __int32 bureaucrat : 1;
    unsigned __int32 ambient_spawn : 1;
    unsigned __int32 ambient_flee : 1;
    unsigned __int32 ambient_near_player : 1;
    unsigned __int32 ambient_vehicle_spawn : 1;
    unsigned __int32 ambient_edf_flyer : 1;
    unsigned __int32 roadblock_guard : 1;
    unsigned __int32 thanked_player : 1;
    unsigned __int32 converted_guerrilla : 1;
    unsigned __int32 attempted_spontaneous_conversion : 1;
    unsigned __int32 dont_collide_with_humans : 1;
    unsigned __int32 disable_grenades : 1;
    unsigned __int32 no_turret_attacks : 1;
    unsigned __int32 force_out_of_vehicle : 1;
    unsigned __int32 scripted_move : 1;
    unsigned __int32 scripted_drive : 1;
    unsigned __int32 only_ride_with_player : 1;
    unsigned __int32 played_added_message : 1;
    unsigned __int32 has_reached_player : 1;
    unsigned __int32 too_far_from_player : 1;
    unsigned __int32 spawned_as_corpse : 1;
    unsigned __int32 use_corpse_vehicle_exit : 1;
    unsigned __int32 man_flyer : 1;
    unsigned __int32 ignore_player : 1;
    unsigned __int32 squad_leader_ignore_player : 1;
    unsigned __int32 fire_on_vehicles : 1;
    unsigned __int32 ignore_vehicles : 1;
    unsigned __int32 orders_active : 1;
    unsigned __int32 fodder_on_object : 1;
    unsigned __int32 remove_icon_on_death : 1;
    unsigned __int32 courier_run_to_destination : 1;
    unsigned __int32 can_use_special_roads : 1;
    unsigned __int32 bomb : 1;
    unsigned __int32 drive_disabled : 1;
    unsigned __int32 used_action_node : 1;
    unsigned __int32 immediate_spawn : 1;
    unsigned __int32 console_created : 1;
    unsigned __int32 amb_watch_player : 1;
    unsigned __int32 despawn_after_fade : 1;
    unsigned __int32 allow_idle_despawn : 1;
    unsigned __int32 disallow_idle_despawn : 1;
    unsigned __int32 despawn_npc : 1;
    unsigned __int32 disallow_despawn_engagement : 1;
    unsigned __int32 high_priority_despawn : 1;
    unsigned __int32 despawn_on_green_alert : 1;
};

struct vehicle_damage_area
{
    vehicle_damage_area_type m_type;
    int m_max_hit_points;
    int m_hit_points;
    unsigned int m_effect_instances[2];
};

struct npc_script_info_flags//$39A5CD0A01CBACDCC8ACC9FFCAC3EB9B
{
    __int8 run : 1;
    __int8 fire_at_target : 1;
    __int8 use_vehicle : 1;
    __int8 drive_directly : 1;
};

struct __declspec(align(4)) npc_script_info
{
    unsigned int location_object;
    npc_script_info_flags flags;
};

struct patrol_node_handle_flags//$E3C9819FB7D46A058EA9E2A20532DA63
{
    __int8 reverse : 1;
    __int8 last_node : 1;
    __int8 node_checked : 1;
    __int8 near_road : 1;
};

struct  __declspec(align(4)) patrol_node_handle
{
    unsigned int patrol_handle;
    unsigned int nav_handle;
    patrol_node_handle_flags node_flags;
};

struct squad_progression_set
{
    HumanInfo* h_info;
    int member_load;
    int spawn_weight;
};

struct squad_progression_level
{
    rfg::farray<squad_progression_set, 8> squad_progression_list;
    int total_spawn_weight;
    HumanInfo *priority_reservations[8];
};

struct squad_progress_info
{
    const char *name;
    HumanTeams team;
    squad_progression_level progression_list[8];
    int last_member_used;
};

struct squad_definition
{
    const char* name;
    HumanInfo* special_npc_info;
    HumanTeams squad_team;
    int total_npc_count;
    squad_progress_info* primary_info;
    squad_progress_info* secondary_info;
    squad_progress_info* reinforcement_info;
};

struct object_squad : Object
{
    squad_spawn_status spawn_status;
    rfg::farray<unsigned int, 10> member_array;
    npc_flags_struct npc_flags;
    HumanFlags hflags;
    vehicle_flags vflags;
    npc_script_info scripting_info;
    vehicle_spawn_group_info *veh_spawn_group;
    unsigned int squad_vehicle;
    Timestamp last_member_removed;
    patrol_node_handle current_node_handle;
    int squad_map_objective;
    minimap_elements squad_map_icon;
    unsigned int spawn_node_handle;
    squad_definition* definition;
    unsigned int base_orders_handle;
    unsigned int assigned_orders_handle;
    squad_flags_struct squad_flags;
    Timestamp squad_age;
    vector simulated_velocity;
    vehicle_damage_area stored_damage_areas[1];
    void* dest_spline_node; //navmesh_lane_spline_node* dest_spline_node;
    HumanTeams override_team;
    float vehicle_hp_mult;
    unsigned int squad_leader;
};

struct ambush_region_flags
{
    unsigned __int32 enabled : 1;
    unsigned __int32 ambush_is_triggered : 1;
    unsigned __int32 marauders_used : 1;
    unsigned __int32 edf_used : 1;
    unsigned __int32 guerrillas_used : 1;
    unsigned __int32 teams_checked : 1;
    unsigned __int32 skirmish_ambush : 1;
    unsigned __int32 abort_ambush : 1;
};

struct marauder_ambush_region : Object
{
    bbox bb;
    bbox local_bb;
    float radius;
    float night_ambush_prob;
    float day_ambush_prob;
    int min_squad_spawns;
    int max_squad_spawns;
    unsigned int edf_squad_spawn_node;
    unsigned int marauder_squad_spawn_node;
    unsigned int guerrilla_squad_spawn_node;
    object_squad* edf_squad;
    object_squad* marauder_squad;
    object_squad* guerrilla_squad;
    bool is_day;
    vector last_pos;
    Timestamp squad_update_timer;
    ambush_region_flags flags;
};

struct squad_spawn_node_flags //object_squad_spawn_node::squad_spawn_node_flags
{
    unsigned __int32 disabled : 1;
    unsigned __int32 mission_disabled : 1;
    unsigned __int32 evaluated_spawn : 1;
    unsigned __int32 spawn_next_frame : 1;
    unsigned __int32 no_reassignment : 1;
    unsigned __int32 raid_spawn : 1;
    unsigned __int32 hands_off_raid_squad : 1;
    unsigned __int32 miner_persona : 1;
    unsigned __int32 safehouse_vip : 1;
    unsigned __int32 ignore_tod_spawning : 1;
    unsigned __int32 respawn : 1;
    unsigned __int32 special_spawn_npc : 1;
    unsigned __int32 special_spawn_vehicle : 1;
    unsigned __int32 disable_during_alert : 1;
    unsigned __int32 roadblock_spawn_node : 1;
    unsigned __int32 radio_operator : 1;
};

struct object_squad_spawn_node : Object
{
    float spawn_prob;
    float night_spawn_prob;
    squad_definition *squad_def;
    vehicle_spawn_group_info *veh_spawn_group;
    bbox local_bbox;
    spawn_node_respawn_speed respawn_speed;
    gfm_orders_types default_orders_type;
    unsigned int original_orders_handle;
    unsigned int child_squad_handle;
    unsigned int child_vehicle_handle;
    Timestamp respawn_timer;
    squad_spawn_node_flags node_flags; //object_squad_spawn_node::squad_spawn_node_flags
};

struct trigger_region : Object
{
    bbox bb;
    bbox local_bb;
    float radius;
    trigger_region_shape tr_shape;
    bool enabled;
    trigger_region_type tr_type;
    trigger_region_kill_human_types tr_kill_type;
    int tr_flags;
    vector last_pos;
};