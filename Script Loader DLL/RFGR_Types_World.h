#pragma once
#include "RFGR_Type_UI.h"

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

enum rl_camera_type
{
	RLCT_PERSPECTIVE = 0x0,
	RLCT_ORTHO = 0x1,
	NUM_RL_CAMERA_TYPES = 0x2,
};

enum rl_camera_motion_blur_type
{
	MOTION_BLUR_TYPE_RADIAL = 0x0,
	MOTION_BLUR_TYPE_CAMERA = 0x1,
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

struct __declspec(align(8)) plane_info //32 (25 align(8) -> 32) //rl_frustum_base::plane_info
{
	vector4 m_plane; //16
	int m_neg_verts; //4
	int m_pos_verts; //4
	bool m_active; //1
};

struct __declspec(align(4)) frustum_cache //212 (209 align(4) -> 212) //rl_frustum_base::frustum_cache
{
	vector m_absPlanes[9]; //108
	int m_numValidCornerPoints; //4
	vector m_corners[8]; //96
	bool m_dirty; //1
};

struct rl_frustum_base //508
{
	int m_num_active_planes; //4
	int m_max_planes; //4
	__declspec(align(16)) plane_info m_planes[9]; //288
	frustum_cache m_cache; //212
};

struct rl_frustum : rl_frustum_base
{

};

/* 3722 */
struct __declspec(align(8)) rl_view_frustum : rl_frustum_base
{
	vector m_view_point;
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

//struct rl_base_object;
struct __declspec(align(8)) rl_scene : rl_base_object
{
	rl_scene* prev;
	rl_scene* next;
	bool m_initialized;
	pool_list__rl_occluder_ptr m_occluder_list;
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
	void* m_default_scene_renderer_p; //rl_scene_renderer* m_default_scene_renderer_p;
	void* m_scene_renderer; //rl_scene_renderer* m_scene_renderer_p;
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

const struct vehicle_spawn_group_info
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

const struct __declspec(align(4)) ambient_spawn_info
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

struct base_array__vehicle_reservation_info__Vtbl;
struct base_array__vehicle_reservation_info
{
	const vehicle_reservation_info& operator [](int index) { return elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	base_array__vehicle_reservation_info__Vtbl* vfptr;
	vehicle_reservation_info *elt;
	int array_size;
	int num;
};

struct base_array__vehicle_reservation_info__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__vehicle_reservation_info* This, unsigned int);
};

struct farray__vehicle_reservation_info_7 : base_array__vehicle_reservation_info
{
	vehicle_reservation_info data[7];
};

struct human_reservation_info
{
	human_spawn_group_info *spawn_group;
	int count;
};

struct base_array__human_reservation_info__Vtbl;
struct base_array__human_reservation_info
{
	const human_reservation_info& operator [](int index) { return elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	base_array__human_reservation_info__Vtbl* vfptr;
	human_reservation_info* elt;
	int array_size;
	int num;
};

struct base_array__human_reservation_info__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__human_reservation_info* This, unsigned int);
};

struct farray__human_reservation_info_16 : base_array__human_reservation_info
{
	human_reservation_info data[16];
};

struct __declspec(align(4)) spawn_resource_data
{
	const char *name;
	int team_squad_counts[4];
	farray__human_reservation_info_16 required_human_slots;
	farray__vehicle_reservation_info_7 required_vehicle_slots;
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

struct hammer_unlock_data
{
	char raw_data[8];
};

struct backpack_unlock_data
{
	char raw_data[2];
};

struct game_save_info_new_data
{
	hammer_unlock_data hammers_unlocked_large;
	backpack_unlock_data backpacks_unlocked;
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

struct base_array__grid_info__Vtbl;
struct base_array__grid_info
{
	const grid_info& operator [](int index) { return elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	base_array__grid_info__Vtbl* vfptr;
	grid_info* elt;
	int array_size;
	int num;
};

struct base_array__grid_info__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__grid_info* This, unsigned int);
};

struct farray__grid_info_21 : base_array__grid_info
{
	grid_info data[21];
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
	farray__grid_info_21 grid_ids;
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
	farray__grid_info_21 list;
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

struct stream_grid_cell;
struct stream_layer_masked_cell
{
	stream_grid_cell* gc;
	HavokBPO* n_region[4];
};

struct base_array__stream_layer_masked_cell_Vtbl;
struct base_array__stream_layer_masked_cell
{
	const stream_layer_masked_cell& operator [](int index) { return elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	base_array__stream_layer_masked_cell_Vtbl* vfptr;
	stream_layer_masked_cell* elt;
	int array_size;
	int num;
};

struct base_array__stream_layer_masked_cell_Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__stream_layer_masked_cell* This, unsigned int);
};

struct farray__stream_layer_masked_cell_50 : base_array__stream_layer_masked_cell
{
	stream_layer_masked_cell data[50];
};

struct base_array__stream_grid_cell_ptr_Vtbl;
struct base_array__stream_grid_cell_ptr
{
	const stream_grid_cell& operator [](int index) { return *elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	base_array__stream_grid_cell_ptr_Vtbl* vfptr;
	stream_grid_cell** elt;
	int array_size;
	int num;
};

struct base_array__stream_grid_cell_ptr_Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__stream_grid_cell_ptr* This, unsigned int);
};

struct farray__stream_grid_cell_ptr_25 : base_array__stream_grid_cell_ptr
{
	stream_grid_cell* data[25];
};

struct stream_grid_cell
{
	unsigned int stream_mask;
	unsigned int srid[4];
	char grid_x;
	char grid_z;
	unsigned __int16 layer_index;
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
	farray__stream_grid_cell_ptr_25 active_cells;
	farray__stream_layer_masked_cell_50 masked_cells; //farray<stream_layer::masked_cell, 50> masked_cells;
	vector cell_dim;
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

struct base_array__rl_terrain_occluder_ptr__Vtbl;
struct base_array__rl_terrain_occluder_ptr
{
	const rl_terrain_occluder& operator [](int index) { return *elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	struct base_array__rl_terrain_occluder_ptr__Vtbl *vfptr;
	rl_terrain_occluder** elt;
	int array_size;
	int num;
};

struct base_array__rl_terrain_occluder_ptr__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__rl_terrain_occluder_ptr* This, unsigned int);
};

struct farray__rl_terrain_occluder_ptr_40 : base_array__rl_terrain_occluder_ptr
{
	rl_terrain_occluder* data[40]; //160
};

/*struct base_array__unsigned_short__Vtbl;
struct base_array__unsigned_short
{
	const unsigned __int16& operator [](int index) { return elt[index]; };
	int size() { return num; }
	int capacity() { return array_size; }

	base_array__unsigned_short__Vtbl* vfptr;
	unsigned __int16* elt;
	int array_size;
	int num;
};

struct base_array__unsigned_short__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__unsigned_short* This, unsigned int);
};

struct base_array__object_ptr__Vtbl;
struct base_array__object_ptr
{
	const Object& operator [](int index) 
	{
		if (index < num)
		{
			return *elt[index];
		}		
	};
	int size() { return num; }
	int capacity() { return array_size; }

private:
	base_array__object_ptr__Vtbl* vfptr;
	Object** elt;
	int array_size;
	int num; 
};

struct base_array__object_ptr__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__object_ptr* This, unsigned int);
};*/

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
	farray__rl_terrain_occluder_ptr_40 m_occluders;
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
	char hash_table[8198]; //hash_table<unsigned int, &hash_uint, 1024, unsigned short> destroyed_object_table; //8198
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