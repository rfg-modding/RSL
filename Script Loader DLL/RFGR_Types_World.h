#pragma once
#include "RFGR_Type_UI.h"

/* 577 */
enum world_deserialize_state
{
	DS_IDLE = 0x0,
	DS_PENDING = 0x1,
	DS_COLLECT = 0x2,
	DS_COMPRESS = 0x3,
	DS_SAVE_FINALIZE = 0x4,
};

/* 1205 */
enum world_zone_state
{
	WZS_UNLOADED = 0x0,
	WZS_STREAMING = 0x1,
	WZS_LOADED = 0x2,
};

/* 578 */
enum world_state_mode
{
	WSM_DEFAULT = 0x0,
	WSM_CHECKPOINT = 0x1,
	NUM_WORLD_STATE_MODES = 0x2,
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

/* 5239 */
struct zone_header
{
	unsigned int signature;
	unsigned int version;
	int num_objects;
	int num_handles;
	unsigned int district_hash;
	unsigned int flags;
};

/* 5240 */
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

/* 5308 */
struct handle_manager_7280
{
	char status[910];
	unsigned int last_bin;
	unsigned int last_slot;
	unsigned int upper_bits;
};

/*
struct bb_pfg_zone
{
	bb_pfg_layer *pfg;
	unsigned int pfg_shape;
	unsigned int pfg_havok_handle;
	bb_pfg_layer *vehicle_pfg;
	unsigned int vehicle_pfg_shape;
	unsigned int vehicle_pfg_havok_handle;
};


struct base_array__rl_terrain_occluder_ptr
{
	base_array<rl_terrain_occluder *>Vtbl *vfptr;
	rl_terrain_occluder **elt;
	int array_size;
	int num;
};


struct farray__rl_terrain_occluder_ptr_40 : base_array__rl_terrain_occluder_ptr
{
	rl_terrain_occluder* data[40]; //160
};


struct obj_zone : object
{
	bb_pfg_zone zone_pfg;
	unsigned int heightfield_shape;
	unsigned int stitch_piece_havok_handle;
	unsigned int district_handle;
	void* spawn_res_data;//spawn_resource_data* spawn_res_data;
	void* amb_spawn_info;//ambient_spawn_info* amb_spawn_info;
	float wind_min_speed;
	float wind_max_speed;
	void* terrain;//rfg_terrain* terrain;
	farray<rl_terrain_occluder *, 40> m_occluders;
	vector local_bmin;
	vector local_bmax;
	int aabb_phantom_index;
};*/

/* 5309 */
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
	void* zone_objp;//obj_zone* zone_objp;
	unsigned int srid;
	bool is_border_zone;
	handle_manager_7280 obj_handle_mgr;
	unsigned __int16 gid;
};

struct base_array__unsigned_short__Vtbl;
struct base_array__unsigned_short
{
	base_array__unsigned_short__Vtbl* vfptr;
	unsigned __int16* elt;
	int array_size;
	int num;
};

/* 5227 */
struct base_array__unsigned_short__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__unsigned_short* This, unsigned int);
};

struct base_array__object_ptr__Vtbl;
struct base_array__object_ptr //base_array<object *>
{
	base_array__object_ptr__Vtbl* vfptr;
	Object** elt;
	int array_size;
	int num;
};

/* 4659 */
struct base_array__object_ptr__Vtbl
{
	void *(__thiscall *__vecDelDtor)(base_array__object_ptr* This, unsigned int);
};

/* 5320 */
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

/* 5321 */
struct hammer_unlock_data
{
	char raw_data[8];
};

/* 5322 */
struct backpack_unlock_data
{
	char raw_data[2];
};

/* 5323 */
struct game_save_info_new_data
{
	hammer_unlock_data hammers_unlocked_large;
	backpack_unlock_data backpacks_unlocked;
	char jetpack_unlock_level;
};

/* 5324 */
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

/* 5386 */
struct __declspec(align(8)) World //11108
{
	bool mission_object_creation_mode; //1
	vector level_ambient; //12
	vector level_back_ambient; //12
	char last_loaded_territory[64]; //64
	int max_world_objects; //4
	base_array__object_ptr all_objects; //16
	base_array__unsigned_short type_objects[53]; //848
	base_array__unsigned_short subtype_objects[11]; //176
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
	void* grid; //stream_grid* grid; //4
	vector stream_pos; //12
	int num_territory_zones; //4
	world_zone** all_zones; //4
	world_zone* global_zone_grid[257]; //1028
	bool is_territory; //1
	char territory_name[128]; //128
	int num_streaming_objects; //4
	bool stub_serialization_in_progress; //1
};