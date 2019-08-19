#include "WorldLua.h"
#include "Functions.h"

void Lua::BindStreamGridCell(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<stream_grid_cell>
    (
        "StreamGridCell",
        "new", sol::no_constructor,
        "StreamMask", & stream_grid_cell::stream_mask,
        "SRID", sol::property([](stream_grid_cell& Self) { return std::ref(Self.srid); }), //uint[4]
        "GridX", sol::property([](stream_grid_cell& Self) -> int {return static_cast<int>(Self.grid_x); }, [](stream_grid_cell& Self, int Value) {Self.grid_x = static_cast<char>(Value); }),
        "GridZ", sol::property([](stream_grid_cell& Self) -> int {return static_cast<int>(Self.grid_z); }, [](stream_grid_cell& Self, int Value) {Self.grid_z = static_cast<char>(Value); }),
        "LayerIndex", & stream_grid_cell::layer_index
    );
}

void Lua::BindStreamLayerMaskedCell(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<stream_layer_masked_cell>
    (
        "StreamLayerMaskedCell",
        "new", sol::no_constructor,
        "GridCell", &stream_layer_masked_cell::gc,
        "NRegion", sol::property([](stream_layer_masked_cell& Self) { return std::ref(Self.n_region); }) //HavokBPO*[4]
    );
}

void Lua::BindStreamLayer(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<stream_layer>
    (
        "StreamLayer",
        "new", sol::no_constructor,
        //"Cells", &stream_layer::cells, //stream_grid_cell**
        "NumCells", &stream_layer::num_cells,
        "DimX", &stream_layer::dim_x,
        "DimZ", &stream_layer::dim_z,
        "CellLoadDistance", &stream_layer::cell_load_distance,
        "StreamRadius", &stream_layer::stream_radius,
        "BMin", &stream_layer::bmin,
        "BMax", &stream_layer::bmax,
        "StreamBMin", &stream_layer::stream_bmin,
        "StreamBMax", &stream_layer::stream_bmax,
        //"ActiveCells", &stream_layer::active_cells, //rfg::farray
        //"MaskedCells", &stream_layer::masked_cells, //rfg::farray
        "CellDim", &stream_layer::cell_dim
    );
}

void Lua::BindDistrictFlags(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<district_flags>
    (
        "DistrictFlags",
        "new", sol::no_constructor,
        "AllowCough", sol::property(itsy_bitsy::read<district_flags, 0>, itsy_bitsy::write<district_flags, 0>), //int8 - 1
        "AllowAmbEdfCivilianDump", sol::property(itsy_bitsy::read<district_flags, 1>, itsy_bitsy::write<district_flags, 1>), //int8 - 1
        "PlayCapstoneUnlockedLines", sol::property(itsy_bitsy::read<district_flags, 2>, itsy_bitsy::write<district_flags, 2>), //int8 - 1
        "DisableMoraleChange", sol::property(itsy_bitsy::read<district_flags, 3>, itsy_bitsy::write<district_flags, 3>), //int8 - 1
        "DisableControlChange", sol::property(itsy_bitsy::read<district_flags, 4>, itsy_bitsy::write<district_flags, 4>) //int8 - 1
    );
}

void Lua::BindTDistrict(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<t_district>
    (
        "TDistrict",
        "new", sol::no_constructor,
        "Name", &t_district::name, //const char*
        "LiberatedRadioLine", &t_district::liberated_radio_line, //const char*
        "LocalizedNameHash", &t_district::localized_name_hash,
        "LocalizedNameHashNoAr", &t_district::localized_name_hash_no_ar,
        "Control", &t_district::control,
        "ControlMax", &t_district::control_max,
        "Morale", &t_district::morale,
        "MoraleMax", &t_district::morale_max,
        "TechLevel", &t_district::tech_level,
        "MarauderLevel", &t_district::marauder_level,
        "EdfLevel", &t_district::edf_level,
        "EdfProgressionLevel", &t_district::edf_progression_level,
        "Liberated", &t_district::liberated,
        "Flags", &t_district::flags,
        "Color", &t_district::col,
        "VfxTintColor", &t_district::vfx_tint,
        "DiscLayer", &t_district::disc_layer,
        "Index", sol::property([](t_district& Self) -> int {return static_cast<int>(Self.index); }, [](t_district& Self, int Value) {Self.index = static_cast<char>(Value); }),
        "Thumbnail", &t_district::thumbnail, //const char*
        "LoadScreenImages", sol::property([](t_district& Self) { return std::ref(Self.load_screen_images); }),
        "NumLoadScreenImages", sol::property([](t_district& Self) -> int {return static_cast<int>(Self.num_load_screen_images); }, [](t_district& Self, int Value) {Self.num_load_screen_images = static_cast<char>(Value); }),
        //"GridList", &t_district::list) //rfg::farray<grid_info, 21>
        "Next", &t_district::next, //tdistrict*
        "Prev", &t_district::prev //tdistrict*
    );
}

void Lua::BindTerritory(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<territory>
    (
        "Territory",
        "new", sol::no_constructor,
        "Name", &territory::name, //const char*
        "TechLevelDefault", &territory::tech_level_default,
        "TechLevelMax", &territory::tech_level_max,
        "Index", sol::property([](territory& Self) -> int {return static_cast<int>(Self.index); }, [](territory& Self, int Value) {Self.index = static_cast<char>(Value); }),
        "Districts", &territory::districts,
        "VerticalMaskZones", &territory::vertical_mask_zones,
        "NumVMaskZones", &territory::num_v_mask_zones,
        "HorizMaskZones", &territory::horiz_mask_zones, //ushort* (array of ushorts...), need to make a wrapper that works for this to provide easy element access.
        "NumHMaskZones", &territory::num_h_mask_zones
    );
}

void Lua::BindStreamGrid(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<stream_grid>
    (
        "StreamGrid",
        "new", sol::no_constructor,
        "Layers", &stream_grid::layers,
        "GridTerritory", &stream_grid::grid_territory,
        "NsBase", &stream_grid::ns_base,
        "NsPrecache", &stream_grid::ns_precache,
        "LandmarksSRID", &stream_grid::landmarks_srid,
        "CompactSuperEmergency", &stream_grid::compact_super_emergency, //wtf does that even mean? //Maybe something that happens when there's too many objects or streaming errors
        "CompactTS", &stream_grid::compact_ts,
        "CompactWaitTS", &stream_grid::compact_wait_ts
        //"TempTable", &stream_grid::m_tmp_table); //str_data_hash_table<unsigned char, 255, 64, unsigned char>*
    );
}

void Lua::BindGameSaveInfoNewData(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<game_save_info_new_data> //Todo: Wrap these char values in sol::properties so they can be treated as ints in lua (if applicable)
    (
        "GameSaveInfoNewData",
        "new", sol::no_constructor,
        "HammersUnlockedLarge", sol::property([](game_save_info_new_data& Self) { return std::ref(Self.hammers_unlocked_large); }), //char[8]
        "BackpacksUnlocked", sol::property([](game_save_info_new_data& Self) { return std::ref(Self.backpacks_unlocked); }), //char[2]
        "JetpackUnlockLevel", &game_save_info_new_data::jetpack_unlock_level //char
    );
}

void Lua::BindGameSaveInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<game_save_info>
    (
        "GameSaveInfo",
        "new", sol::no_constructor,
        "NumMissionsCompleted", &game_save_info::num_missions_completed,
        "NumActivitiesCompleted", &game_save_info::num_activities_completed,
        "DistrictsLiberated", &game_save_info::districts_liberated,
        "TerritoryIndex", &game_save_info::territory_index,
        "DistrictIndex", &game_save_info::district_index,
        "Day", &game_save_info::day,
        "Month", &game_save_info::month,
        "Year", &game_save_info::year,
        "Hours", &game_save_info::hours,
        "Minutes", &game_save_info::minutes,
        "Seconds", &game_save_info::seconds,
        "AutoSave", &game_save_info::auto_save,
        "UsedSlot", &game_save_info::used_slot,
        "DlcID", &game_save_info::dlc_id,
        "SaveSlotIndex", &game_save_info::save_slot_index,
        "HammersUnlocked", sol::property([](game_save_info& Self) -> int {return static_cast<int>(Self.hammers_unlocked); }, [](game_save_info& Self, int Value) {Self.hammers_unlocked = static_cast<char>(Value); }),
        "GoldenHammerDesired", &game_save_info::golden_hammer_desired,
        "NewData", &game_save_info::new_data
        //"Padding", &game_save_info::padding, //Size 117 char array
    );
}

void Lua::BindSaveLoadInfo(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<save_load_info>
    (
        "SaveLoadInfo",
        "new", sol::no_constructor,
        "PendingNewSave", sol::property(itsy_bitsy::read<save_load_info, 0>, itsy_bitsy::write<save_load_info, 0>), //int8 - 1
        "ResetDestruction", sol::property(itsy_bitsy::read<save_load_info, 1>, itsy_bitsy::write<save_load_info, 1>), //int8 - 1
        "PendingSaveGame", sol::property(itsy_bitsy::read<save_load_info, 2>, itsy_bitsy::write<save_load_info, 2>), //int8 - 1
        "PerformingSaveGame", sol::property(itsy_bitsy::read<save_load_info, 3>, itsy_bitsy::write<save_load_info, 3>), //int8 - 1
        "PendingSaveState", sol::property(itsy_bitsy::read<save_load_info, 4>, itsy_bitsy::write<save_load_info, 4>), //int8 - 1
        "PerformingSaveState", sol::property(itsy_bitsy::read<save_load_info, 5>, itsy_bitsy::write<save_load_info, 5>), //int8 - 1
        "PendingSingleZone", sol::property(itsy_bitsy::read<save_load_info, 6>, itsy_bitsy::write<save_load_info, 6>), //int8 - 1
        "SaveGameWarp", sol::property(itsy_bitsy::read<save_load_info, 7>, itsy_bitsy::write<save_load_info, 7>), //int8 - 1
        "GameSaveCheckpoint", sol::property(itsy_bitsy::read<save_load_info, 8>, itsy_bitsy::write<save_load_info, 8>), //int8 - 1
        "GameSaveToDisk", sol::property(itsy_bitsy::read<save_load_info, 9>, itsy_bitsy::write<save_load_info, 9>), //int8 - 1
        "PendingLoadGameFromMemory", sol::property(itsy_bitsy::read<save_load_info, 10>, itsy_bitsy::write<save_load_info, 10>), //int8 - 1
        "AutoSaveGame", sol::property(itsy_bitsy::read<save_load_info, 11>, itsy_bitsy::write<save_load_info, 11>), //int8 - 1
        "SaveStateData", sol::property(itsy_bitsy::read<save_load_info, 12>, itsy_bitsy::write<save_load_info, 12>), //int8 - 1
        "PlayerStartAtSafehouse", sol::property(itsy_bitsy::read<save_load_info, 13>, itsy_bitsy::write<save_load_info, 13>), //int8 - 1
        "PlayerStartPos", &save_load_info::player_start_pos,
        "PlayerStartOrient", &save_load_info::player_start_orient
    );
}

void Lua::BindWorldStateBuf(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<world_state_buf>
    (
        "WorldStateBuf",
        "new", sol::no_constructor,
        "PlayerStartPos", &world_state_buf::player_start_pos,
        "PlayerStartOrient", &world_state_buf::player_start_orient,
        "PlayerStartPosSafehouse", &world_state_buf::player_start_pos_safehouse,
        "PlayerStartOrientSafehouse", &world_state_buf::player_start_orient_safehouse,
        "Buffer", &world_state_buf::buf, //char*
        "CurrentSize", &world_state_buf::cur_size,
        "MaxSize", &world_state_buf::max_size
    );
}

void Lua::BindZoneHeader(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<zone_header>
    (
        "ZoneHeader",
        "new", sol::no_constructor,
        "Signature", &zone_header::signature,
        "Version", &zone_header::version,
        "NumberOfObjects", &zone_header::num_objects,
        "NumberOfHandles", &zone_header::num_handles,
        "DistrictHash", &zone_header::district_hash,
        "Flags", &zone_header::flags
    );
}

void Lua::BindWorldZone(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<world_zone>
    (
        "WorldZone",
        "new", sol::no_constructor,
        "BMin", &world_zone::bmin,
        "BMax", &world_zone::bmax,
        "Name", sol::property([](world_zone& Self) { return std::ref(Self.name); }), //char[64]
        "State", &world_zone::state,
        "DeserializeHeader", &world_zone::deserialize_header,
        //"DeserializeHeaderF", &world_zone::deserialize_header_f, //cfile*
        //"DeserializeF", &world_zone::deserialize_f, //cfile*
        "StoredZoneState", &world_zone::stored_zone_state,
        //"ObjectZone", &world_zone::zone_objp, //obj_zone type //Todo: Bind this
        "SRID", &world_zone::srid,
        "IsBorderZone", &world_zone::is_border_zone,
        //"ObjectHandleManager", &world_zone::obj_handle_mgr,
        "GID", &world_zone::gid
    );
}

void Lua::BindWorld(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<World>
    (
        "World",
        "new", sol::no_constructor,
        "MissionObjectCreationMode", &World::mission_object_creation_mode,
        "LevelAmbient", &World::level_ambient,
        "LevelBackAmbient", &World::level_back_ambient,
        "LastLoadedTerritory", sol::property([](World& Self) { return Globals::CharArrayToString(Self.last_loaded_territory, 64); }), //Size 64 array of chars
        "MaxWorldObjects", &World::max_world_objects,
        "AllObjects", &World::all_objects, //rfg::base_array<Object*>
        "Objects", &World::all_objects, //rfg::base_array<Object*>
        //"TypeObjects", & World::type_objects, //rfg::base_array<ushort> array size 53
        //"SubTypeObjects", & World::subtype_objects, //rfg::base_array<ushort> array size 11
        "TechLevel", & World::tech_level,
        "TechLevelMax", & World::tech_level_max,
        //"ThreadID", & World::thread_id, //Volatile - unbound for now
        //"ObjectHandleHash", & World::object_handle_hash, //dynamic_uint_hash_table<object *>
        //"DestroyedObjectTable", & World::destroyed_object_table, //hash_table<unsigned int, &hash_uint, 1024, unsigned short>
        //"SaveFile", & World::save_file, //cfile*
        "FlaggedObjects", & World::flagged_objects,
        "CurrentFlaggedObject", & World::current_flagged_object,
        "CurrentFlaggedMode", sol::property([](World& Self) -> int {return static_cast<int>(Self.current_flagged_mode); }, [](World& Self, int Value) {Self.current_flagged_mode = static_cast<char>(Value); }),
        "DeserializeState", & World::deserialize_state, //enum
        //"DeserializePool", &World::deserialize_pool, //virtual_mempool*
        //"DeserializeList", &World::deserialize_list, //farray<world_zone *, 32>
        "CurrentWorldState", &World::cur_world_state,
        //"StoredWorldState", &World::stored_world_state, //Size 2 array of world_state_buf
        //"CompressStream", &World::compress_steam, //zlib_stream*
        //"DecompressStream", &World::decompress_steam, //zlib_stream*
        "SaveLoadFlags", &World::sl_flags,
        "PendingGameSaveSlot", &World::pending_game_save_slot,
        "DlcBundleID", &World::dlc_bundle_id,
        "PendingFilename", sol::property([](World& Self) { return Globals::CharArrayToString(Self.pending_filename, 64); }), //Size 64 char array
        "PendingGameLoadWarpToPos", &World::pending_game_load_warp_to_pos,
        "PendingGameLoadWarpToOrient", &World::pending_game_load_warp_to_orient,
        //"LoadAborted", & World::load_aborted, //Volatile - unbound for now
        "Grid", & World::grid,
        "StreamPos", & World::stream_pos,
        "NumTerritoryZones", & World::num_territory_zones,
        //"AllZones", & World::all_zones, //Double pointer //Todo: See about providing a wrapper around this to treat it as an array
        "GlobalZoneGrid", sol::property([](World& Self) { return std::ref(Self.global_zone_grid); }), //world_zone*[257]
        "IsTerritory", & World::is_territory,
        "TerritoryName", sol::property([](World& Self) { return Globals::CharArrayToString(Self.territory_name, 128); }), //Size 128 char array
        "NumStreamingObjects", & World::num_streaming_objects,
        "StubSerializationInProgress", & World::stub_serialization_in_progress
    );
}