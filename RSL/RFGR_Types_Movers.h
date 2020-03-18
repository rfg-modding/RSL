#pragma once
#include "RFGR_Types_EventData.h"

using object_importance_level = ObjectImportanceLevel;
enum rfg_move_type
{
    RFGM_INVALID = 0xFFFFFFFF,
    RFGM_FIXED = 0x0,
    RFGM_NORMAL = 0x1,
    RFGM_LITE = 0x2,
    RFGM_ULTRA_LITE = 0x3,
    RFGM_WORLD_ONLY = 0x4,
    RFGM_NO_COLLISION = 0x5,
};

struct  explosion_container
{
    explosion_info* exp_info;
    char* attachment_point_name;
};

struct  __declspec(align(4)) custom_effect_info
{
    unsigned int effect_handle;
    char* attachment_point_name;
    bool looping;
};

struct  script_point_effect_info
{
    char script_point_name[32];
    int max_hitpoints;
    unsigned int* bullet_impact_override;
    unsigned int custom_effect;
    unsigned int prefix_effect;
    float prefix_effect_delay_min;
    float prefix_effect_delay_max;
    int prefix_hitpoints;
    unsigned int death_effect;
    explosion_info* death_explosion;
    unsigned int spe_flags;
};

struct level_object_properties_flags
{
    __int8 m_damaged_by_cars : 1;
    __int8 m_damaged_by_explosions : 1;
    __int8 m_damaged_by_bullets : 1;
    __int8 m_damaged_by_level_objects : 1;
    __int8 m_damaged_by_melee : 1;
    __int8 m_dislodged_by_cars : 1;
    __int8 m_dislodged_by_explosions : 1;
    __int8 m_dislodged_by_bullets : 1;
    __int8 m_dislodged_by_level_objects : 1;
    __int8 m_dislodged_by_melee : 1;
    __int8 m_allow_dynamic_link : 1;
    __int8 m_link_affects_effects : 1;
    __int8 m_death_explosion : 1;
    __int8 m_dislodge_on_death : 1;
    __int8 m_movable_by_humans : 1;
    __int8 m_generate_human_collision_event : 1;
};

const struct  level_object_base_properties
{
    char* m_name;
    unsigned int m_collision_impact_override;
    float m_collision_min_impact_energy;
    unsigned int* m_melee_impact_override;
    unsigned int* m_bullet_impact_override;
    script_point_effect_info* m_script_point_effect_infos[4];
    level_object_properties_flags m_flags;
    custom_effect_info m_custom_effect_infos[3];
    int m_max_hitpoints;
    int m_max_dislodge_hitpoints;
    float m_mass;
    float m_corpse_mass;
    float m_friction;
    float m_restitution;
    float m_linear_dampening;
    float m_angular_dampening;
    char m_physical_material;
    char m_effect_material;
    unsigned int m_death_effect;
    unsigned int m_release_effect;
    int m_release_delay_ms;
    int m_release_looping_ms;
    explosion_container m_death_explosions[1];
    int m_explosion_prefix_min_duration;
    int m_explosion_prefix_max_duration;
    int m_prefix_hitpoints;
    custom_effect_info m_prefix_effect_infos[2];
};

struct  level_object_inst_properties
{
    level_object_properties_flags m_flags;
    level_object_base_properties* m_base_properties;
    unsigned int m_custom_effects[3];
    void* m_script_point_effect_insts[4];//script_point_effect_inst* m_script_point_effect_insts[4];
    int m_hitpoints;
    int m_dislodge_hitpoints;
    unsigned int m_prefix_effects[2];
    timestamp m_death_timer;
    unsigned int m_release_effect_instance;
};

const struct  LOD_properties
{
    char* m_name;
    float m_lod_off_dist;
};

const struct  gameplay_properties
{
    char* name;
    int chunk_flags;
    object_importance_level importance;
    human_teams team;
    float game_destroyed_pct;
    float fully_destroyed_pct;
    salvage_material_type salvage_material;
    int salvage_num_pieces;
    float control;
    float monetary_value;
    LOD_properties* lod_properties;
};

struct  object_mover : object
{
    int mover_type_bit_flags;
    unsigned __int16 m_render_opacity;
    unsigned __int16 reference_position_index;
    unsigned int chunk_uid;
    unsigned int shape_uid;
    unsigned int chunk_obj_uid;
    unsigned int destruction_checksum;
    level_object_inst_properties* m_level_obj_properties;
    event_result(__cdecl* on_stream_in_callback)(event_data*, notify_info*);
    event_result(__cdecl* on_damaged_callback)(event_data*, notify_info*);
    event_result(__cdecl* on_destroyed_callback)(event_data*, notify_info*);
    event_result(__cdecl* on_use_action_callback)(event_data*, notify_info*);
    gameplay_properties* gameplay_props;
    human_teams team;
    float control;
    unsigned int nav_cell_detour_request_handle;
    unsigned int creator_handle;
    unsigned int final_attacker;
    unsigned int mover_flags;
    int fade_start_time;
    timestamp fade_out_timer;
    timestamp melee_damage_delay;
    timestamp inactive_fade_time;
    void* m_mp_error_info; //object_mover_error_info* m_mp_error_info;
};

struct rfg_mover_flags
{
    unsigned __int32 under_stress : 1;
    unsigned __int32 run_stress_on_stream : 1;
    unsigned __int32 collapse_effect : 1;
    unsigned __int32 invulnerable : 1;
    unsigned __int32 game_destroyed : 1;
    unsigned __int32 fully_destroyed : 1;
    unsigned __int32 large_explosion : 1;
    unsigned __int32 pristine : 1;
    unsigned __int32 mp_no_fade_destroy : 1;
    unsigned __int32 render_xform_dirty : 1;
    unsigned __int32 is_ai_structure : 1;
    unsigned __int32 is_ai_building : 1;
    unsigned __int32 is_ai_subpiece : 1;
    unsigned __int32 is_ai_composite : 1;
    unsigned __int32 updating_anchors : 1;
    unsigned __int32 plume_on_death : 1;
    unsigned __int32 one_of_many : 1;
    unsigned __int32 mining : 1;
    unsigned __int32 supply_crate : 1;
    unsigned __int32 regrow_on_stream_begin : 1;
    unsigned __int32 regrow_on_stream_finish : 1;
    unsigned __int32 inherit_damage_pct : 1;
    unsigned __int32 rebuild : 1;
    unsigned __int32 propaganda : 1;
    unsigned __int32 building : 1;
};

struct rfg_mover__resource_dependent_data
{
    void* shape; //rfg_destroyable_shape* shape;
    void* model_instance_p; //rl_destroyable_model_instance* model_instance_p;
};

struct rfg_mover : object_mover
{
    rfg_move_type move_type;
    float damage_pct;
    float current_structural_mass;
    void* state_data; //rfg_mover_temporary_data* state_data;
    float game_destroyed_pct;
    rfg_mover_flags flags;
    void* mp_info; //multi_rfg_mover_info* mp_info;
    unsigned __int16 explosion_event_index;
    unsigned __int16 damaged_subpiece_event_first_index;
    unsigned __int16 repair_event_list;
    __int16 stress_test_count;
    timestamp stress_test_delay;
    timestamp slice_delay;
    rfg_mover* stress_next;
    rfg_mover* stress_prev;
    unsigned int restricted_area;
    int salvage_num_pieces;
    unsigned int destruction_uid;
    int damage_report_handle;
    int stream_out_time;
    timestamp stress_sound_propagate_timer;
    float accumulated_load_amount;
    unsigned int process_shardify_candidate_index;
    rfg::object_stream_resource<rfg_mover__resource_dependent_data> rdd;
    unsigned int dead_smoke_plume_effect;
    rfg_mover* pre_stream_next;
    rfg_mover* pre_stream_prev;
    void* m_glass_obj_list; //glass_obj* m_glass_obj_list;
    timestamp damage_sound_propagate_timer;
};

struct obj_prop
{
    unsigned __int16 type;
    unsigned __int16 size;
    unsigned int name_crc;
    char data[];
};

struct rfg_prop_block
{
    unsigned __int16 num_props;
    unsigned __int16 owner;
    unsigned __int16 buf_pos;
    unsigned __int16 buf_size;
    char* prop_list;
};

struct obj_prop_block : rfg_prop_block
{

};

struct prop_name
{
    const char* str;
    unsigned int crc;
};

struct obj_auto_props : obj_prop_block
{
};

struct obj_item_props : obj_prop_block
{
};

struct obj_projectile_props : obj_item_props
{
};

struct obj_weapon_props : obj_item_props
{
};

/* 5204 */
struct $2C5C31389D845770D898EFDFE506A801
{
    unsigned __int32 delete_on_exit : 1;
};

using animation_action = AnimationAction;
/* 5201 */
struct $05B30DA556A417BB98EF16C60783726B
{
    unsigned __int32 loop_effect : 1;
    unsigned __int32 attach_effct : 1;
};

/* 5202 */
const struct  ambient_prop_effect_info
{
    animation_state anim_state;
    animation_action anim_action;
    unsigned int effect_handle;
    const char* attach_point_name;
    int start_tag_id;
    int end_tag_id;
    $05B30DA556A417BB98EF16C60783726B effect_flags;
};

/* 5205 */
const struct  ambient_prop_info
{
    item_info* prop_item_info;
    const char* human_attach_point_name;
    const char* child_attach_point_name;
    int prop_walk_state;
    int prop_stand_state;
    animation_action prop_exit_anim;
    int exit_anim_trigger_id;
    unsigned int perm_effect_handle;
    const char* perm_effect_attach_name;
    rfg::farray<ambient_prop_effect_info const*, 3> effect_info_list;
    $2C5C31389D845770D898EFDFE506A801 prop_flags;
};

struct general_mover__resource_dependent_data
{
    void* shape;//rfg_destroyable_shape* shape;
    rl_renderable_instance* model_instance_p;
};

union $002CCC9B1632BB5CD0DDD2EA2984EB06
{
    unsigned int collision_type;
    int move_type;
};

struct  general_mover : object_mover
{
    unsigned int gm_flags;
    $002CCC9B1632BB5CD0DDD2EA2984EB06 ___u2;
    unsigned int subpiece_index;
    unsigned int name_checksum;
    int gobj_index;
    void* mp_sim_state;//multi_sim_state<multi_mover_state>* mp_sim_state;
    unsigned int destruction_uid;
    rfg::object_stream_resource<general_mover__resource_dependent_data> rdd;
    general_mover* pre_stream_next;
    general_mover* pre_stream_prev;
    unsigned int original_object;
    timestamp last_damaged_timer;
};

struct  mesh_tag
{
    unsigned int m_name_crc;
    matrix43 m_transform;
};

struct mesh_tags
{
    int m_num_tags;
    rfg::et_sized_native_pointer<mesh_tag> m_tags;
};

struct rl_vertex_buffer_data_runtime
{
    int num_verts;
    char vert_stride_0;
    char vertex_format;
    char num_uv_channels;
    char vert_stride_1;
    char* verts;
};

struct rl_index_buffer_data_runtime
{
    unsigned int num_indices;
    char* indices;
    char index_size;
    char prim_type;
    unsigned __int16 num_blocks;
};

struct rl_mesh_data_runtime
{
    int num_sub_meshes;
    rl_submesh_data* sub_meshes;
    rl_vertex_buffer_data_runtime vertex_buffer;
    rl_index_buffer_data_runtime index_buffer;
};

namespace keen
{
    struct RenderGeometry
    {
        keen::VertexFormat* pVertexFormat;
        ID3D11Buffer* pVertexBuffer;
        unsigned int vertexCount;
        ID3D11Buffer* pIndexBuffer;
        unsigned int indexCount;
        void* pSkinGeometry;//keen::SoftwareSkinGeometry* pSkinGeometry;
        unsigned int skinningBufferOffset;
        const char* pDebugName;
        unsigned int indexFormat;
        unsigned int primitiveTopology;
        void* pMorphData; //keen::SoftwareMorphData* pMorphData;
    };
}


const struct __declspec(align(8)) rl_mesh : rl_renderable
{
    bool m_data_set;
    rl_mesh_data_runtime m_data;
    rl_render_block* m_base_render_block;
    unsigned int m_max_material_index;
    unsigned int m_uid;
    keen::RenderGeometry m_geometry;
};

struct mesh_header_shared
{
    unsigned int m_signature;
    unsigned int m_version;
    rfg::et_sized_native_pointer<rl_mesh> m_mesh;
    rfg::et_sized_native_pointer<rl_material_map> m_material_map;
    rfg::et_sized_native_pointer<rfg::et_sized_native_pointer<rl_material> > m_materials;
    unsigned int m_num_materials;
    rfg::et_sized_native_pointer<char const > m_texture_names;
};

struct __declspec(align(8)) static_mesh
{
    mesh_header_shared m_shared_header;
    unsigned int m_num_lods;
    rfg::et_sized_native_pointer<int> m_lod_submesh_id;
    rfg::et_sized_native_pointer<mesh_tags> m_tags_offset;
    mesh_tags m_tags;
    unsigned int m_cm_index;
};

struct debris_create_info
{
    vector m_position;
    matrix m_orientation;
    float m_mass;
    float m_friction;
    float m_restitution;
    float m_linear_damp;
    float m_angular_damp;
    char m_physical_material;
    char m_effect_material;
    unsigned int m_mesh_srid;
    rl_renderable_instance* m_renderable_instance_p;
    static_mesh* m_mesh;
    int m_submesh_id;
    unsigned int m_num_lod_infos;
    lod_info* m_lod_info;
    unsigned int m_collision_type;
    unsigned int m_cm_index;
    hkpShape* m_shape;
    int m_impact_foley_id;
    unsigned int m_delay_before_first_impact_foley;
    unsigned int m_vehicle_handle;
    unsigned int m_component_index;
    bool m_is_persistent;
    bool m_is_retrievable;
    int m_retrievable_material_type;
    int m_deformed_morph_target;
    bool m_has_precalc_inertia;
    matrix m_precalc_tensor;
    vector m_precalc_center_of_mass;
};

struct  object_debris : object
{
    int debris_flags;
    timestamp m_min_existance_time;
    bool m_is_persistent;
    timestamp m_retrievable_delay;
    int m_retrievable_material_type;
    int fade_ms;
    timestamp m_fade_stamp;
    bool fading_from_nano;
    unsigned int m_num_lod_infos;
    lod_info* m_lod_info;
    int m_impact_foley_id;
    timestamp m_impact_foley_delay;
    timestamp m_effect_end;
    unsigned int m_effect_instance;
    debris_create_info m_create_info;
    rl_renderable_instance* m_renderable_instance_p;
    static_mesh* m_mesh;
    int m_submesh_id;
};