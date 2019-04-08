#include "WorldLua.h"
#include "Functions.h"

void Lua::BindWorld(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<World>();
	Utype.set("new", sol::no_constructor);
	Utype.set("", &World::mission_object_creation_mode);
	Utype.set("", &World::level_ambient);
	Utype.set("", &World::level_back_ambient);
	Utype.set("", &World::last_loaded_territory); //Size 64 array of chars
	Utype.set("", &World::all_objects); //rfg::base_array<Object*>
	Utype.set("", &World::type_objects); //rfg::base_array<ushort> array size 53
	Utype.set("", &World::subtype_objects); //rfg::base_array<ushort> array size 11
	Utype.set("", &World::tech_level);
	Utype.set("", &World::tech_level_max);
	Utype.set("", &World::thread_id);
	//Utype.set("", &World::object_handle_hash); //dynamic_uint_hash_table<object *>
	//Utype.set("", &World::destroyed_object_table); //hash_table<unsigned int, &hash_uint, 1024, unsigned short>
	//Utype.set("", &World::save_file); //cfile*
	Utype.set("", &World::flagged_objects);
	Utype.set("", &World::current_flagged_object);
	Utype.set("", &World::current_flagged_mode);
	Utype.set("", &World::deserialize_state); //enum
	//Utype.set("", &World::deserialize_pool); //virtual_mempool*
	Utype.set("", &World::deserialize_list); //farray<world_zone *, 32>
	Utype.set("", &World::cur_world_state);
	Utype.set("", &World::stored_world_state); //Size 2 array of world_state_buf
	//Utype.set("", &World::compress_steam); //zlib_stream*
	//Utype.set("", &World::decompress_steam); //zlib_stream*
	Utype.set("", &World::sl_flags);
	Utype.set("", &World::pending_game_save_slot);
	Utype.set("", &World::dlc_bundle_id);
	Utype.set("", &World::pending_filename); //Size 64 char array
	Utype.set("", &World::pending_game_load_warp_to_pos);
	Utype.set("", &World::pending_game_load_warp_to_orient);
	Utype.set("", &World::load_aborted);
	Utype.set("", &World::grid);
	Utype.set("", &World::stream_pos);
	Utype.set("", &World::num_territory_zones);
	Utype.set("", &World::all_zones);
	Utype.set("", &World::global_zone_grid);
	Utype.set("", &World::is_territory);
	Utype.set("", &World::territory_name); //Size 128 char array
	Utype.set("", &World::num_streaming_objects);
	Utype.set("", &World::stub_serialization_in_progress);
	LuaState.set_usertype("World", Utype);
}