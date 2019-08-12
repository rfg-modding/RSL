#include "WorldLua.h"
#include "Functions.h"

void Lua::BindStreamGridCell(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<stream_grid_cell>();
	Utype.set("new", sol::no_constructor);
	Utype.set("StreamMask", &stream_grid_cell::stream_mask);
	Utype.set("SRID", sol::property([](stream_grid_cell& Self) { return std::ref(Self.srid); })); //uint[4]
	Utype.set("GridX", sol::property([](stream_grid_cell& Self) -> int {return static_cast<int>(Self.grid_x); }, [](stream_grid_cell& Self, int Value) {Self.grid_x = static_cast<char>(Value); }));
	Utype.set("GridZ", sol::property([](stream_grid_cell& Self) -> int {return static_cast<int>(Self.grid_z); }, [](stream_grid_cell& Self, int Value) {Self.grid_z = static_cast<char>(Value); }));
	Utype.set("LayerIndex", &stream_grid_cell::layer_index);
	RfgTable.set_usertype("StreamGridCell", Utype);
}

void Lua::BindStreamLayerMaskedCell(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<stream_layer_masked_cell>();
	Utype.set("new", sol::no_constructor);
	Utype.set("GridCell", &stream_layer_masked_cell::gc);
	Utype.set("NRegion", sol::property([](stream_layer_masked_cell& Self) { return std::ref(Self.n_region); })); //HavokBPO*[4]
	RfgTable.set_usertype("StreamLayerMaskedCell", Utype);
}

void Lua::BindStreamLayer(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<stream_layer>();
	Utype.set("new", sol::no_constructor);
	//Utype.set("Cells", &stream_layer::cells); //stream_grid_cell**
	Utype.set("NumCells", &stream_layer::num_cells);
	Utype.set("DimX", &stream_layer::dim_x);
	Utype.set("DimZ", &stream_layer::dim_z);
	Utype.set("CellLoadDistance", &stream_layer::cell_load_distance);
	Utype.set("StreamRadius", &stream_layer::stream_radius);
	Utype.set("BMin", &stream_layer::bmin);
	Utype.set("BMax", &stream_layer::bmax);
	Utype.set("StreamBMin", &stream_layer::stream_bmin);
	Utype.set("StreamBMax", &stream_layer::stream_bmax);
	//Utype.set("ActiveCells", &stream_layer::active_cells); //rfg::farray
	//Utype.set("MaskedCells", &stream_layer::masked_cells); //rfg::farray
	Utype.set("CellDim", &stream_layer::cell_dim);
	RfgTable.set_usertype("StreamLayer", Utype);
}

void Lua::BindDistrictFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<district_flags>();
	Utype.set("new", sol::no_constructor);
	Utype.set("AllowCough", sol::property(itsy_bitsy::read<district_flags, 0>, itsy_bitsy::write<district_flags, 0>)); //int8 - 1
	Utype.set("AllowAmbEdfCivilianDump", sol::property(itsy_bitsy::read<district_flags, 1>, itsy_bitsy::write<district_flags, 1>)); //int8 - 1
	Utype.set("PlayCapstoneUnlockedLines", sol::property(itsy_bitsy::read<district_flags, 2>, itsy_bitsy::write<district_flags, 2>)); //int8 - 1
	Utype.set("DisableMoraleChange", sol::property(itsy_bitsy::read<district_flags, 3>, itsy_bitsy::write<district_flags, 3>)); //int8 - 1
	Utype.set("DisableControlChange", sol::property(itsy_bitsy::read<district_flags, 4>, itsy_bitsy::write<district_flags, 4>)); //int8 - 1
	RfgTable.set_usertype("DistrictFlags", Utype);
}

void Lua::BindTDistrict(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<t_district>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Name", &t_district::name); //const char*
	Utype.set("LiberatedRadioLine", &t_district::liberated_radio_line); //const char*
	Utype.set("LocalizedNameHash", &t_district::localized_name_hash);
	Utype.set("LocalizedNameHashNoAr", &t_district::localized_name_hash_no_ar);
	Utype.set("Control", &t_district::control);
	Utype.set("ControlMax", &t_district::control_max);
	Utype.set("Morale", &t_district::morale);
	Utype.set("MoraleMax", &t_district::morale_max);
	Utype.set("TechLevel", &t_district::tech_level);
	Utype.set("MarauderLevel", &t_district::marauder_level);
	Utype.set("EdfLevel", &t_district::edf_level);
	Utype.set("EdfProgressionLevel", &t_district::edf_progression_level);
	Utype.set("Liberated", &t_district::liberated);
	Utype.set("Flags", &t_district::flags);
	Utype.set("Color", &t_district::col);
	Utype.set("VfxTintColor", &t_district::vfx_tint);
	Utype.set("DiscLayer", &t_district::disc_layer);
	Utype.set("Index", sol::property([](t_district& Self) -> int {return static_cast<int>(Self.index); }, [](t_district& Self, int Value) {Self.index = static_cast<char>(Value); }));
	Utype.set("Thumbnail", &t_district::thumbnail); //const char*
	Utype.set("LoadScreenImages", sol::property([](t_district& Self) { return std::ref(Self.load_screen_images); }));
	Utype.set("NumLoadScreenImages", sol::property([](t_district& Self) -> int {return static_cast<int>(Self.num_load_screen_images); }, [](t_district& Self, int Value) {Self.num_load_screen_images = static_cast<char>(Value); }));
	//Utype.set("GridList", &t_district::list); //rfg::farray<grid_info, 21>
	Utype.set("Next", &t_district::next); //tdistrict*
	Utype.set("Prev", &t_district::prev); //tdistrict*
	RfgTable.set_usertype("TDistrict", Utype);
}

void Lua::BindTerritory(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<territory>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Name", &territory::name); //const char*
	Utype.set("TechLevelDefault", &territory::tech_level_default);
	Utype.set("TechLevelMax", &territory::tech_level_max);
	Utype.set("Index", sol::property([](territory& Self) -> int {return static_cast<int>(Self.index); }, [](territory& Self, int Value) {Self.index = static_cast<char>(Value); }));
	Utype.set("Districts", &territory::districts);
	Utype.set("VerticalMaskZones", &territory::vertical_mask_zones);
	Utype.set("NumVMaskZones", &territory::num_v_mask_zones);
	Utype.set("HorizMaskZones", &territory::horiz_mask_zones);
	Utype.set("NumHMaskZones", &territory::num_h_mask_zones);
	RfgTable.set_usertype("Territory", Utype);
}

void Lua::BindStreamGrid(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<stream_grid>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Layers", &stream_grid::layers);
	Utype.set("GridTerritory", &stream_grid::grid_territory);
	Utype.set("NsBase", &stream_grid::ns_base);
	Utype.set("NsPrecache", &stream_grid::ns_precache);
	Utype.set("LandmarksSRID", &stream_grid::landmarks_srid);
	Utype.set("CompactSuperEmergency", &stream_grid::compact_super_emergency); //wtf does that even mean?
	Utype.set("CompactTS", &stream_grid::compact_ts);
	Utype.set("CompactWaitTS", &stream_grid::compact_wait_ts);
	//Utype.set("TempTable", &stream_grid::m_tmp_table); //str_data_hash_table<unsigned char, 255, 64, unsigned char>*
	RfgTable.set_usertype("StreamGrid", Utype);
}

void Lua::BindGameSaveInfoNewData(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<game_save_info_new_data>();
	Utype.set("new", sol::no_constructor);
	Utype.set("HammersUnlockedLarge", sol::property([](game_save_info_new_data& Self) { return std::ref(Self.hammers_unlocked_large); })); //char[8]
	Utype.set("BackpacksUnlocked", sol::property([](game_save_info_new_data& Self) { return std::ref(Self.backpacks_unlocked); })); //char[2]
	Utype.set("JetpackUnlockLevel", &game_save_info_new_data::jetpack_unlock_level); //char
	RfgTable.set_usertype("GameSaveInfoNewData", Utype);
}

void Lua::BindGameSaveInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<game_save_info>();
	Utype.set("new", sol::no_constructor);
	Utype.set("NumMissionsCompleted", &game_save_info::num_missions_completed);
	Utype.set("NumActivitiesCompleted", &game_save_info::num_activities_completed);
	Utype.set("DistrictsLiberated", &game_save_info::districts_liberated);
	Utype.set("TerritoryIndex", &game_save_info::territory_index);
	Utype.set("DistrictIndex", &game_save_info::district_index);
	Utype.set("Day", &game_save_info::day);
	Utype.set("Month", &game_save_info::month);
	Utype.set("Year", &game_save_info::year);
	Utype.set("Hours", &game_save_info::hours);
	Utype.set("Minutes", &game_save_info::minutes);
	Utype.set("Seconds", &game_save_info::seconds);
	Utype.set("AutoSave", &game_save_info::auto_save);
	Utype.set("UsedSlot", &game_save_info::used_slot);
	Utype.set("DlcID", &game_save_info::dlc_id);
	Utype.set("SaveSlotIndex", &game_save_info::save_slot_index);
	Utype.set("HammersUnlocked", sol::property([](game_save_info& Self) -> int {return static_cast<int>(Self.hammers_unlocked); }, [](game_save_info& Self, int Value) {Self.hammers_unlocked = static_cast<char>(Value); }));
	Utype.set("GoldenHammerDesired", &game_save_info::golden_hammer_desired);
	Utype.set("NewData", &game_save_info::new_data);
	//Utype.set("Padding", &game_save_info::padding); //Size 117 char array
	RfgTable.set_usertype("GameSaveInfo", Utype);
}

void Lua::BindSaveLoadInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<save_load_info>();
	Utype.set("new", sol::no_constructor);
	Utype.set("PendingNewSave", sol::property(itsy_bitsy::read<save_load_info, 0>, itsy_bitsy::write<save_load_info, 0>)); //int8 - 1
	Utype.set("ResetDestruction", sol::property(itsy_bitsy::read<save_load_info, 1>, itsy_bitsy::write<save_load_info, 1>)); //int8 - 1
	Utype.set("PendingSaveGame", sol::property(itsy_bitsy::read<save_load_info, 2>, itsy_bitsy::write<save_load_info, 2>)); //int8 - 1
	Utype.set("PerformingSaveGame", sol::property(itsy_bitsy::read<save_load_info, 3>, itsy_bitsy::write<save_load_info, 3>)); //int8 - 1
	Utype.set("PendingSaveState", sol::property(itsy_bitsy::read<save_load_info, 4>, itsy_bitsy::write<save_load_info, 4>)); //int8 - 1
	Utype.set("PerformingSaveState", sol::property(itsy_bitsy::read<save_load_info, 5>, itsy_bitsy::write<save_load_info, 5>)); //int8 - 1
	Utype.set("PendingSingleZone", sol::property(itsy_bitsy::read<save_load_info, 6>, itsy_bitsy::write<save_load_info, 6>)); //int8 - 1
	Utype.set("SaveGameWarp", sol::property(itsy_bitsy::read<save_load_info, 7>, itsy_bitsy::write<save_load_info, 7>)); //int8 - 1
	Utype.set("GameSaveCheckpoint", sol::property(itsy_bitsy::read<save_load_info, 8>, itsy_bitsy::write<save_load_info, 8>)); //int8 - 1
	Utype.set("GameSaveToDisk", sol::property(itsy_bitsy::read<save_load_info, 9>, itsy_bitsy::write<save_load_info, 9>)); //int8 - 1
	Utype.set("PendingLoadGameFromMemory", sol::property(itsy_bitsy::read<save_load_info, 10>, itsy_bitsy::write<save_load_info, 10>)); //int8 - 1
	Utype.set("AutoSaveGame", sol::property(itsy_bitsy::read<save_load_info, 11>, itsy_bitsy::write<save_load_info, 11>)); //int8 - 1
	Utype.set("SaveStateData", sol::property(itsy_bitsy::read<save_load_info, 12>, itsy_bitsy::write<save_load_info, 12>)); //int8 - 1
	Utype.set("PlayerStartAtSafehouse", sol::property(itsy_bitsy::read<save_load_info, 13>, itsy_bitsy::write<save_load_info, 13>)); //int8 - 1
	Utype.set("PlayerStartPos", &save_load_info::player_start_pos);
	Utype.set("PlayerStartOrient", &save_load_info::player_start_orient);
	RfgTable.set_usertype("SaveLoadInfo", Utype);
}

void Lua::BindWorldStateBuf(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<world_state_buf>();
	Utype.set("new", sol::no_constructor);
	Utype.set("PlayerStartPos", &world_state_buf::player_start_pos);
	Utype.set("PlayerStartOrient", &world_state_buf::player_start_orient);
	Utype.set("PlayerStartPosSafehouse", &world_state_buf::player_start_pos_safehouse);
	Utype.set("PlayerStartOrientSafehouse", &world_state_buf::player_start_orient_safehouse);
	Utype.set("Buffer", &world_state_buf::buf); //char*
	Utype.set("CurrentSize", &world_state_buf::cur_size);
	Utype.set("MaxSize", &world_state_buf::max_size);
	RfgTable.set_usertype("WorldStateBuf", Utype);
}

void Lua::BindZoneHeader(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<zone_header>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Signature", &zone_header::signature);
	Utype.set("Version", &zone_header::version);
	Utype.set("NumberOfObjects", &zone_header::num_objects);
	Utype.set("NumberOfHandles", &zone_header::num_handles);
	Utype.set("DistrictHash", &zone_header::district_hash);
	Utype.set("Flags", &zone_header::flags);
	RfgTable.set_usertype("ZoneHeader", Utype);
}

void Lua::BindWorldZone(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<world_zone>();
	Utype.set("new", sol::no_constructor);
	Utype.set("BMin", &world_zone::bmin);
	Utype.set("BMax", &world_zone::bmax);
	Utype.set("Name", sol::property([](world_zone& Self) { return std::ref(Self.name); })); //char[64]
	Utype.set("State", &world_zone::state);
	Utype.set("DeserializeHeader", &world_zone::deserialize_header);
	//Utype.set("DeserializeHeaderF", &world_zone::deserialize_header_f); //cfile*
	//Utype.set("DeserializeF", &world_zone::deserialize_f); //cfile*
	Utype.set("StoredZoneState", &world_zone::stored_zone_state);
	///Utype.set("ObjectZone", &world_zone::zone_objp); //obj_zone type
	Utype.set("SRID", &world_zone::srid);
	Utype.set("IsBorderZone", &world_zone::is_border_zone);
	//Utype.set("ObjectHandleManager", &world_zone::obj_handle_mgr);
	Utype.set("GID", &world_zone::gid);
	RfgTable.set_usertype("WorldZone", Utype);
}

void Lua::BindWorld(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<World>();
	Utype.set("new", sol::no_constructor);
	Utype.set("MissionObjectCreationMode", &World::mission_object_creation_mode);
	Utype.set("LevelAmbient", &World::level_ambient);
	Utype.set("LevelBackAmbient", &World::level_back_ambient);
	Utype.set("LastLoadedTerritory", sol::property([](World& Self) { return std::ref(Self.last_loaded_territory); })); //Size 64 array of chars
	Utype.set("MaxWorldObjects", &World::max_world_objects);
	Utype.set("AllObjects", &World::all_objects); //rfg::base_array<Object*>
	Utype.set("Objects", &World::all_objects); //rfg::base_array<Object*>
	///Utype.set("TypeObjects", &World::type_objects); //rfg::base_array<ushort> array size 53
	///Utype.set("SubTypeObjects", &World::subtype_objects); //rfg::base_array<ushort> array size 11
	Utype.set("TechLevel", &World::tech_level);
	Utype.set("TechLevelMax", &World::tech_level_max);
	//Utype.set("ThreadID", &World::thread_id); //Volatile - unbound for now
	//Utype.set("ObjectHandleHash", &World::object_handle_hash); //dynamic_uint_hash_table<object *>
	//Utype.set("DestroyedObjectTable", &World::destroyed_object_table); //hash_table<unsigned int, &hash_uint, 1024, unsigned short>
	//Utype.set("SaveFile", &World::save_file); //cfile*
	Utype.set("FlaggedObjects", &World::flagged_objects);
	Utype.set("CurrentFlaggedObject", &World::current_flagged_object);
	Utype.set("CurrentFlaggedMode", sol::property([](World& Self) -> int {return static_cast<int>(Self.current_flagged_mode); }, [](World& Self, int Value) {Self.current_flagged_mode = static_cast<char>(Value); }));
	Utype.set("DeserializeState", &World::deserialize_state); //enum
	//Utype.set("DeserializePool", &World::deserialize_pool); //virtual_mempool*
	//Utype.set("DeserializeList", &World::deserialize_list); //farray<world_zone *, 32>
	Utype.set("CurrentWorldState", &World::cur_world_state);
	//Utype.set("StoredWorldState", &World::stored_world_state); //Size 2 array of world_state_buf
	//Utype.set("CompressStream", &World::compress_steam); //zlib_stream*
	//Utype.set("DecompressStream", &World::decompress_steam); //zlib_stream*
	Utype.set("SaveLoadFlags", &World::sl_flags);
	Utype.set("PendingGameSaveSlot", &World::pending_game_save_slot);
	Utype.set("DlcBundleID", &World::dlc_bundle_id);
	Utype.set("PendingFilename", sol::property([](World& Self) { return std::ref(Self.pending_filename); })); //Size 64 char array
	Utype.set("PendingGameLoadWarpToPos", &World::pending_game_load_warp_to_pos);
	Utype.set("PendingGameLoadWarpToOrient", &World::pending_game_load_warp_to_orient);
	//Utype.set("LoadAborted", &World::load_aborted); //Volatile - unbound for now
	Utype.set("Grid", &World::grid);
	Utype.set("StreamPos", &World::stream_pos);
	Utype.set("NumTerritoryZones", &World::num_territory_zones);
	//Utype.set("AllZones", &World::all_zones); //Double pointer
	Utype.set("GlobalZoneGrid", sol::property([](World& Self) { return std::ref(Self.global_zone_grid); })); //world_zone*[257]
	Utype.set("IsTerritory", &World::is_territory);
	Utype.set("TerritoryName", sol::property([](World& Self) { return std::ref(Self.territory_name); })); //Size 128 char array
	Utype.set("NumStreamingObjects", &World::num_streaming_objects);
	Utype.set("StubSerializationInProgress", &World::stub_serialization_in_progress);
	RfgTable.set_usertype("World", Utype);
}