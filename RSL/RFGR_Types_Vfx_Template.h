#pragma once
#include "RFGR_Types_Cfile.h"

enum object_effect_category
{
    EFFECTS_CATEGORY_NONE = 0x0,
    EFFECTS_CATEGORY_GLASS = 0x1,
    EFFECTS_CATEGORY_EXPLOSION = 0x2,
    EFFECTS_CATEGORY_MAX = 0x3,
};

enum rl_shader_technique_type
{
    rl_shader_technique_none = 0xFFFFFFFF,
    rl_shader_technique_base = 0x0,
    rl_shader_technique_lighting = 0x1,
    rl_shader_technique_depth_only = 0x2,
    rl_shader_technique_user = 0x3,
};

struct vfx_float_key
{
    float time;
    float value;
};

struct quaternion
{
    float x;
    float y;
    float z;
    float w;
};

struct vfx_quat_key
{
    float time;
    quaternion value;
};

struct vfx_vector_key
{
    float time;
    vector value;
};

struct rl_vertex_buffer_data
{
    int num_verts;
    char vert_stride_0;
    char vertex_format;
    char num_uv_channels;
    char vert_stride_1;
    et_ptr_offset<unsigned char, 0> verts;
};

struct rl_index_buffer_data
{
    unsigned int num_indices;
    et_ptr_offset<unsigned char, 0> indices;
    char index_size;
    char prim_type;
    unsigned __int16 num_blocks;
};

struct rl_render_block
{
    unsigned __int16 material_map_idx;
    unsigned int start_index;
    unsigned int num_indices;
    unsigned int minimum_index;
    unsigned int maximum_index;
};

struct rl_submesh_data
{
    int num_render_blocks;
    vector offset_transform;
    vector bmin;
    vector bmax;
    et_ptr_offset<rl_render_block, 0> render_blocks;
};

struct rl_mesh_data
{
    int num_sub_meshes;
    et_ptr_offset<rl_submesh_data, 0> sub_meshes;
    rl_vertex_buffer_data vertex_buffer;
    rl_index_buffer_data index_buffer;
};

struct rl_material_map_data
{
    et_ptr_offset<unsigned int, 0> materials;
    unsigned int num_materials;
};

struct rl_material_map_data_runtime
{
    unsigned int* materials;
    unsigned int num_materials;
};

struct __declspec(align(4)) rl_material_map : rl_base_object
{
    rl_material_map_data_runtime m_data;
    bool m_isSet;
};

struct rl_material_const
{
    float elem[4];
};

struct rl_texture_desc
{
    union Data
    {
        struct DiscData
        {
            unsigned __int16 texture_stage_disk;
            unsigned __int16 texture_flags_disk;
        };

        struct DataStruct
        {
            unsigned __int32 texture_stage : 4;
            unsigned __int32 texture_flags : 4;
            unsigned __int32 sampler_state_idx : 24;
        };

        rl_texture_desc::Data::DiscData disc;
        rl_texture_desc::Data::DataStruct rt;
    };

    int texture_handle;
    unsigned int name_checksum;
    rl_texture_desc::Data data;
};

struct rl_material_data
{
    unsigned int shader_handle;
    unsigned int name_checksum;
    unsigned int mat_flags;
    unsigned __int16 num_textures;
    char num_constants;
    char max_constants;
    et_ptr_offset<rl_texture_desc, 1> textures;
    et_ptr_offset<unsigned int, 0> constant_name_checksum;
    et_ptr_offset<rl_material_const, 0> constant_block;
};

struct rl_material_base : rl_base_object
{
    unsigned int hash_cache;
    unsigned int base_flags;
};

struct  rl_material : rl_material_base
{
    int m_override_technique_index;
    rl_shader_technique_type m_override_technique_type;
    rl_material_data* m_data;
};

struct __declspec(align(4)) gr_shader_const
{
    int var_ref;
    __int16 const_loc;
    char data[16];
};

struct rl_shader_const_keyframe
{
    float time;
    char val[16];
};

struct  __declspec(align(4)) rl_particle_shader_const
{
    gr_shader_const sc;
    et_ptr_offset<rl_shader_const_keyframe, 0> keys;
    char num_keys;
    char var_type;
};

struct __declspec(align(4)) gr_shader_texture_ref
{
    int var_ref;
    int tex_ref;
    __int16 tex_stage;
};

struct gr_shader_engine_const
{
    __int16 engine_const;
};

struct rl_particle_const_ref
{
    __int16 index;
};

struct  rl_particle_const_info
{
    et_ptr_offset<rl_particle_const_ref, 0> const_refs;
    unsigned __int16 num_const_refs;
    unsigned __int16 num_engine_consts;
    et_ptr_offset<gr_shader_engine_const, 0> engine_consts;
};

struct  rl_particle_material_data
{
    int effect_ref;
    __int16 shader_idx;
    __int16 num_textures;
    et_ptr_offset<gr_shader_texture_ref, 1> textures;
    unsigned __int16 num_shader_consts;
    et_ptr_offset<rl_particle_shader_const, 1> shader_consts;
    rl_particle_const_info vs_const_info;
    rl_particle_const_info ps_const_info;
    int flags;
};

struct rl_particle_base
{
    enum render_type
    {
        RENDER_TYPE_BILLBOARD = 0x0,
        RENDER_TYPE_POINTSPRITE = 0x1,
        RENDER_TYPE_RIBBON = 0x2,
        RENDER_TYPE_POINT = 0x3,
        RENDER_TYPE_LINE = 0x4,
        RENDER_TYPE_NODES = 0x5,
        RENDER_TYPE_RADIAL = 0x6,
        RENDER_TYPE_DROP = 0x7,
        RENDER_TYPE_ORIENTED = 0x8,
        RENDER_TYPE_CORONA = 0x9,
        RENDER_TYPE_MAX = 0xA,
    };

    struct tail_data
    {
        float rotation_angle;
        vector position;
        rl_color_float current_color;
        float current_size;
        float current_length;
    };

    vector position;
    float rotation_angle;
    vector velocity;
    float time_created;
    vector4 random;
    float lifetime;
    int emit_number;
    float* pad[2];
};

struct rl_renderable_particles : rl_base_object
{
    unsigned int m_flags;
    rl_particle_base::render_type m_particle_type;
    rl_particle_material_data* m_material_p;
    int m_tail_length;
    bool m_is_iterative;
    bool m_texture_anim_random_frames;
    matrix* m_color_correction_matrix_p;
    float m_lod_large_particle_fade_min;
    float m_lod_large_particle_fade_max;
    float m_effect_material_percent;
    float m_self_illum;
    rl_color_float m_ambient_color;
    rl_color_float m_diffuse_color;
    float m_soft_thickness;
};

struct  vfx_particle_system_emitter : rl_base_object
{
    bool is_iterative;
    rl_particle_base::render_type m_particle_type;
    float iterations_per_sec;
    int num_tails;
    int max_tails;
    bool use_length;
    bool use_length_mid_value;
    bool local_space_emission;
    bool use_weight_variance;
    float m_weight_start;
    float m_weight_end;
    float m_weight_scale;
    bool use_size_mid_value;
    bool use_color_mid_value;
    bool use_color_saturation_value;
    bool use_additive_key_value;
    float density;
    float density_variance;
    bool use_density_variance;
    rl_color_float color_start;
    rl_color_float color_start_variance;
    rl_color_float color_end;
    rl_color_float color_end_variance;
    rl_color_float color_mid_A;
    rl_color_float color_mid_A_variance;
    float color_mid_A_offset;
    rl_color_float color_mid_B;
    rl_color_float color_mid_B_variance;
    float color_mid_B_offset;
    float alpha_mid_A_offset;
    float alpha_mid_B_offset;
    float color_saturation_start;
    float color_saturation_start_variance;
    float color_saturation_end;
    float color_saturation_end_variance;
    float color_saturation_mid_A;
    float color_saturation_mid_A_variance;
    float color_saturation_mid_B;
    float color_saturation_mid_B_variance;
    vector acceleration_start;
    vector acceleration_start_variance;
    vector acceleration_mid;
    vector acceleration_mid_variance;
    vector acceleration_end;
    vector acceleration_end_variance;
    float yaw_variance;
    float pitch_variance;
    float speed_variance;
    bool is_reverse_render;
    bool use_accel_values;
    bool use_accel_variance;
    bool use_accel_mid_value;
    bool use_color_variance;
    bool is_color_variance_by_value;
    float additive_key_start;
    float additive_key_start_variance;
    float additive_key_end;
    float additive_key_end_variance;
    float additive_key_mid_A;
    float additive_key_mid_A_variance;
    float additive_key_mid_B;
    float additive_key_mid_B_variance;
    bool is_rotation_enabled;
    bool is_rotation_dir_dependant;
    bool is_random_start_rotation;
    float angular_speed_start_variance;
    float angular_speed_end_variance;
    float m_size_scale;
    float m_emission_rate_scale;
    float m_opacity_scale;
    float m_lod_emission_distance;
    bool use_size_variance;
    bool use_length_variance;
    float bounce;
    float bounce_variance;
    bool use_bounce_variance;
    int max_emission;
    bool use_lifetime_variance;
    float lifetime;
    float lifetime_variance;
    int max_particles;
    float animation_duration;
    int num_position_keys;
    vfx_vector_key* position_keys;
    int num_rotation_keys;
    vfx_quat_key* rotation_keys;
    int num_scale_keys;
    vfx_vector_key* scale_keys;
    int num_emission_rate_keys;
    vfx_float_key* emission_rate_keys;
    int num_angular_speed_start_keys;
    vfx_float_key* angular_speed_start_keys;
    int num_angular_speed_end_keys;
    vfx_float_key* angular_speed_end_keys;
    int num_speed_keys;
    vfx_float_key* speed_keys;
    int m_num_texture_anim_rate_keys;
    vfx_float_key* m_texture_anim_rate_keys;
    int num_size_start_keys;
    vfx_float_key* size_start_keys;
    int num_size_start_var_keys;
    vfx_float_key* size_start_var_keys;
    int num_size_mida_keys;
    vfx_float_key* size_mida_keys;
    int num_size_mida_var_keys;
    vfx_float_key* size_mida_var_keys;
    int num_size_mida_offset_keys;
    vfx_float_key* size_mida_offset_keys;
    int num_size_midb_keys;
    vfx_float_key* size_midb_keys;
    int num_size_midb_var_keys;
    vfx_float_key* size_midb_var_keys;
    int num_size_midb_offset_keys;
    vfx_float_key* size_midb_offset_keys;
    int num_size_end_keys;
    vfx_float_key* size_end_keys;
    int num_size_end_var_keys;
    vfx_float_key* size_end_var_keys;
    int num_length_start_keys;
    vfx_float_key* length_start_keys;
    int num_length_start_var_keys;
    vfx_float_key* length_start_var_keys;
    int num_length_mida_keys;
    vfx_float_key* length_mida_keys;
    int num_length_mida_var_keys;
    vfx_float_key* length_mida_var_keys;
    int num_length_mida_offset_keys;
    vfx_float_key* length_mida_offset_keys;
    int num_length_midb_keys;
    vfx_float_key* length_midb_keys;
    int num_length_midb_var_keys;
    vfx_float_key* length_midb_var_keys;
    int num_length_midb_offset_keys;
    vfx_float_key* length_midb_offset_keys;
    int num_length_end_keys;
    vfx_float_key* length_end_keys;
    int num_length_end_var_keys;
    vfx_float_key* length_end_var_keys;
    matrix local_rotation_lazy;
    rl_renderable_particles* m_renderable_p;
    bool m_inherit_velocity;
    rfg::pool_list<rfg::et_sized_native_pointer<vfx_particle_system_emitter> > m_emit_node_emitter_list;
};

struct  vfx_vector4_key
{
    float time;
    __declspec(align(16)) vector4 value;
};

struct  __declspec(align(4)) vfx_particle_system_filter : rl_base_object
{
    enum base_type
    {
        BASE_TYPE_INTERACTOR = 0x0,
        BASE_TYPE_DEFLECTOR = 0x1,
        BASE_TYPE_INVALID = 0xFFFFFFFF,
    };

    vfx_particle_system_filter* prev;
    vfx_particle_system_filter* next;
    vfx_particle_system_filter::base_type m_base_type;
    float m_animation_duration;
    int m_num_position_keys;
    vfx_vector_key* m_position_keys_p;
    int m_num_rotation_keys;
    vfx_quat_key* m_rotation_keys_p;
    matrix m_local_rotation_cached;
    bool m_local_rotation_cached_dirty;
};

struct vfx_effect_template : rl_base_object
{
    enum mesh_type
    {
        MESH_TYPE_NORMAL = 0x1,
        MESH_TYPE_FACING = 0x2,
        MESH_TYPE_ROD = 0x4,
        MESH_TYPE_ADDITIVE = 0x8,
        MESH_TYPE_VOLFOG = 0x10,
        _MESH_TYPE_SIZEOF_INT = 0xFFFFFFFF,
    };

    enum emitter_type
    {
        EMITTER_TYPE_SPHERE = 0x0,
        EMITTER_TYPE_PLANE = 0x1,
        EMITTER_TYPE_POINT = 0x2,
        EMITTER_TYPE_BOX = 0x3,
        EMITTER_TYPE_CYLINDER = 0x4,
        EMITTER_TYPE_MAX = 0x5,
    };

    enum filter_flags
    {
        FILTER_FLAGS_GLOBAL = 0x0,
        FILTER_FLAGS_PER_EMITTER = 0x1,
        FILTER_FLAGS_PER_EFFECT = 0x2,
    };

    enum filter_type
    {
        FILTER_TYPE_GRAVITY = 0x0,
        FILTER_TYPE_WIND = 0x1,
        FILTER_TYPE_MAGNET = 0x2,
        FILTER_TYPE_TURBULENCE = 0x3,
        FILTER_TYPE_VORTEX = 0x4,
        FILTER_TYPE_ORIENTOR = 0x5,
    };

    struct expression_param
    {
        bool m_variable;
        unsigned int m_variable_crc;
        rfg::et_sized_native_pointer<unsigned char> m_data_p_index;
    };

    struct expression
    {
        unsigned int m_expression_function_name_crc;
        unsigned int just_a_stub;
        int object_index;
        int m_num_expression_params;
        rfg::et_sized_native_pointer<vfx_effect_template::expression_param> m_params;
    };

    struct mesh
    {
        rfg::et_sized_native_pointer<char> name;
        unsigned int type;
        int num_position_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> position_keys;
        int num_rotation_keys;
        rfg::et_sized_native_pointer<vfx_quat_key> rotation_keys;
        int num_scale_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> scale_keys;
        int num_opacity_keys;
        rfg::et_sized_native_pointer<vfx_float_key> opacity_keys;
        rfg::et_sized_native_pointer<rl_mesh_data> mesh_data_p;
        rfg::et_sized_native_pointer<rl_material_map_data> material_map_data_p;
        rfg::et_sized_native_pointer<rl_material_map> material_map_p;
        unsigned int num_materials;
        rfg::et_sized_native_pointer<rfg::et_sized_native_pointer<rl_material>> materials;
        rfg::et_sized_native_pointer<unsigned char> collision_model_data_p;
        unsigned int shape_material_index;
        float shape_volume;
        vector shape_center_of_mass;
        matrix shape_inertia_tensor;
    };

    struct emitter
    {
        rfg::et_sized_native_pointer<char> name;
        rl_particle_material_data material;
        int type;
        unsigned int class_id;
        bool is_iterative;
        bool is_reverse_render;
        bool is_half_res;
        bool is_quarter_res;
        bool is_always_on_top;
        bool is_soft_render;
        float interations_per_second;
        bool texture_anim_random_frames;
        bool is_emit_node;
        bool inherit_velocity;
        bool local_space_emission;
        bool acceleration_enabled;
        vector acceleration_start;
        vector acceleration_end;
        bool acceleration_variance_enabled;
        vector acceleration_start_variance;
        vector acceleration_end_variance;
        bool use_color_mid_value;
        bool is_color_variance_by_value;
        bool use_color_saturation_value;
        rl_color_float color_start;
        rl_color_float color_start_variance;
        rl_color_float color_end;
        rl_color_float color_end_variance;
        rl_color_float color_mid_A;
        rl_color_float color_mid_A_variance;
        float color_mid_A_offset;
        rl_color_float color_mid_B;
        rl_color_float color_mid_B_variance;
        float color_mid_B_offset;
        float alpha_mid_A_offset;
        float alpha_mid_B_offset;
        float color_saturation_start;
        float color_saturation_start_variance;
        float color_saturation_end;
        float color_saturation_end_variance;
        float color_saturation_mid_A;
        float color_saturation_mid_A_variance;
        float color_saturation_mid_B;
        float color_saturation_mid_B_variance;
        bool use_additive_key_value;
        float additive_key_start;
        float additive_key_start_variance;
        float additive_key_end;
        float additive_key_end_variance;
        float additive_key_mid_A;
        float additive_key_mid_A_variance;
        float additive_key_mid_B;
        float additive_key_mid_B_variance;
        rfg::et_sized_native_pointer<matrix> color_correction_matrix;
        int num_texture_anim_rate_keys;
        rfg::et_sized_native_pointer<vfx_float_key> texture_anim_rate_keys;
        bool rotation_enabled;
        float weight_start;
        float weight_end;
        float density;
        float density_variance;
        int num_emit_node_emitters;
        rfg::et_sized_native_pointer<rfg::et_sized_native_pointer<vfx_particle_system_emitter>> emit_node_emitters;
        int num_tails;
        int particle_type;
        int material_index;
        float yaw_variance;
        float pitch_variance;
        int max_particles;
        bool use_size_mid_value;
        bool use_length_mid_value;
        bool use_length;
        bool use_lifetime_variance;
        float lifetime;
        float lifetime_variance;
        float speed_variance;
        float angular_speed_start_variance;
        float angular_speed_end_variance;
        bool is_random_start_rotation;
        float lod_large_particle_fade_min;
        float lod_large_particle_fade_max;
        float lod_emission_distance;
        float self_illum;
        vector ambient_color;
        vector diffuse_color;
        float effect_material_percent;
        float soft_thickness;
        char pad[4];
        int num_position_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> position_keys;
        int num_rotation_keys;
        rfg::et_sized_native_pointer<vfx_quat_key> rotation_keys;
        int num_scale_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> scale_keys;
        int num_emission_rate_keys;
        rfg::et_sized_native_pointer<vfx_float_key> emission_rate_keys;
        int num_angular_speed_start_keys;
        rfg::et_sized_native_pointer<vfx_float_key> angular_speed_start_keys;
        int num_angular_speed_end_keys;
        rfg::et_sized_native_pointer<vfx_float_key> angular_speed_end_keys;
        int num_speed_keys;
        rfg::et_sized_native_pointer<vfx_float_key> speed_keys;
        int num_size_start_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_start_keys;
        int num_size_start_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_start_var_keys;
        int num_size_mida_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_mida_keys;
        int num_size_mida_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_mida_var_keys;
        int num_size_mida_offset_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_mida_offset_keys;
        int num_size_midb_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_midb_keys;
        int num_size_midb_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_midb_var_keys;
        int num_size_midb_offset_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_midb_offset_keys;
        int num_size_end_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_end_keys;
        int num_size_end_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> size_end_var_keys;
        int num_length_start_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_start_keys;
        int num_length_start_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_start_var_keys;
        int num_length_mida_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_mida_keys;
        int num_length_mida_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_mida_var_keys;
        int num_length_mida_offset_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_mida_offset_keys;
        int num_length_midb_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_midb_keys;
        int num_length_midb_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_midb_var_keys;
        int num_length_midb_offset_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_midb_offset_keys;
        int num_length_end_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_end_keys;
        int num_length_end_var_keys;
        rfg::et_sized_native_pointer<vfx_float_key> length_end_var_keys;
        rfg::et_sized_native_pointer<vfx_particle_system_emitter> particle_system_emitter_p;
        int parent_index;
        int unique_data_size;
        rfg::et_sized_native_pointer<unsigned char> unique_data;
    };

    struct __declspec(align(8)) light
    {
        rfg::et_sized_native_pointer<char> name;
        __int16 flags;
        __int16 type;
        int num_clr_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> clr_keys;
        int num_intensity_keys;
        rfg::et_sized_native_pointer<vfx_float_key> intensity_keys;
        int num_position_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> position_keys;
        int num_fvec_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> fvec_keys;
        float hotspot_size;
        float hotspot_falloff_size;
        float atten_start;
        float atten_end;
        int parent_index;
    };

    struct filter
    {
        rfg::et_sized_native_pointer<char> name;
        int type;
        int flags;
        unsigned int class_id;
        int parent_index;
        int num_affected_emitters;
        rfg::et_sized_native_pointer<int> affected_emitters;
        int num_affected_meshes;
        rfg::et_sized_native_pointer<int> affected_meshes;
        int num_position_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> position_keys;
        int num_rotation_keys;
        rfg::et_sized_native_pointer<vfx_quat_key> rotation_keys;
        rfg::et_sized_native_pointer<vfx_particle_system_filter> particle_system_filter_p;
        int unique_data_size;
        rfg::et_sized_native_pointer<unsigned char> unique_data;
    };

    struct  __declspec(align(8)) corona
    {
        rfg::et_sized_native_pointer<char> name;
        rl_particle_material_data material;
        int type;
        rfg::et_sized_native_pointer<vfx_float_key> rotation_offset_keys;
        int num_rotation_offset_keys;
        int num_position_keys;
        bool is_linear_scaling;
        bool is_linear_fading;
        rfg::et_sized_native_pointer<vfx_vector_key> position_keys;
        int num_rotation_keys;
        rfg::et_sized_native_pointer<vfx_quat_key> rotation_keys;
        int num_scale_keys;
        rfg::et_sized_native_pointer<vfx_vector_key> scale_keys;
        int num_radius_start_keys;
        rfg::et_sized_native_pointer<vfx_float_key> radius_start_keys;
        int num_radius_end_keys;
        rfg::et_sized_native_pointer<vfx_float_key> radius_end_keys;
        int num_width_scale_keys;
        rfg::et_sized_native_pointer<vfx_float_key> width_scale_keys;
        int num_visibility_radius_keys;
        rfg::et_sized_native_pointer<vfx_float_key> visibility_radius_keys;
        int num_color_start_keys;
        rfg::et_sized_native_pointer<vfx_vector4_key> color_start_keys;
        int num_color_end_keys;
        rfg::et_sized_native_pointer<vfx_vector4_key> color_end_keys;
        int num_position_offset_keys;
        rfg::et_sized_native_pointer<vfx_float_key> position_offset_keys;
        int num_saturation_keys;
        rfg::et_sized_native_pointer<vfx_float_key> saturation_keys;
        int num_rotation_scale_keys;
        rfg::et_sized_native_pointer<vfx_float_key> rotation_scale_keys;
        int num_intensity_scale_keys;
        rfg::et_sized_native_pointer<vfx_float_key> intensity_scale_keys;
        int num_intensity_exponential_decay_keys;
        rfg::et_sized_native_pointer<vfx_float_key> intensity_exponential_decay_keys;
        int num_opacity_exponential_decay_keys;
        rfg::et_sized_native_pointer<vfx_float_key> opacity_exponential_decay_keys;
        int num_radius_distance_start_keys;
        rfg::et_sized_native_pointer<vfx_float_key> radius_distance_start_keys;
        int num_radius_distance_end_keys;
        rfg::et_sized_native_pointer<vfx_float_key> radius_distance_end_keys;
        int num_color_distance_start_keys;
        rfg::et_sized_native_pointer<vfx_float_key> color_distance_start_keys;
        int num_color_distance_end_keys;
        rfg::et_sized_native_pointer<vfx_float_key> color_distance_end_keys;
        int num_radius_exponential_decay_keys;
        rfg::et_sized_native_pointer<vfx_float_key> radius_exponential_decay_keys;
        int num_view_fade_scale_keys;
        rfg::et_sized_native_pointer<vfx_float_key> view_fade_scale_keys;
        int num_view_fade_decay_keys;
        rfg::et_sized_native_pointer<vfx_float_key> view_fade_decay_keys;
        int num_opacity_visibility_decay_keys;
        rfg::et_sized_native_pointer<vfx_float_key> opacity_visibility_decay_keys;
        int num_radius_visibility_decay_keys;
        rfg::et_sized_native_pointer<vfx_float_key> radius_visibility_decay_keys;
        bool view_fade_intensity_enabled;
        bool view_fade_opacity_enabled;
        bool view_fade_radius_enabled;
        bool pad0;
    };

    struct vfx_data
    {
        int signature;
        int version;
        int num_expressions;
        rfg::et_sized_native_pointer<vfx_effect_template::expression> expressions;
        rfg::et_sized_native_pointer<char> effect_name;
        float duration;
        float radius;
        int num_bitmaps;
        rfg::et_sized_native_pointer<rfg::et_sized_native_pointer<char> > bitmaps;
        rfg::et_sized_native_pointer<char> mesh_bitmaps;
        int num_meshes;
        rfg::et_sized_native_pointer<vfx_effect_template::mesh> meshes;
        int num_emitters;
        rfg::et_sized_native_pointer<vfx_effect_template::emitter> emitters;
        int num_lights;
        rfg::et_sized_native_pointer<vfx_effect_template::light> lights;
        int num_filters;
        rfg::et_sized_native_pointer<vfx_effect_template::filter> filters;
        int num_coronas;
        rfg::et_sized_native_pointer<vfx_effect_template::corona> coronas;
    };

    rfg::linked_list_p<rl_renderable> m_mesh_renderables;
    vfx_effect_template::vfx_data* m_vfx_data_p;
    bool m_initialized;
    int m_instance_handle;
    const char* peg_filename;
};

struct  __declspec(align(16)) vfx_effect
{
    int m_instance_handle;
    float m_elapsed_time;
    vector m_position;
    matrix m_rotation;
    bool m_is_particle_system_active;
    int num_particle_systems;
    int num_particles;
    bool use_alpha_fade;
    float alpha_fade;
    bool m_is_visible;
    vfx_effect_template* m_effect_template_p;
    int m_render_flags;
    rl_aabb m_world_aabb;
    rl_sphere m_world_bounding_sphere;
    rl_color_float m_effect_material_tint;
    float m_eps;
    void* m_emitter_kill_list; //vfx_particle_system_emitter_instance* m_emitter_kill_list;
    rfg::linked_list_p<char> m_emitters; //rfg::linked_list_p<vfx_particle_system_emitter_instance> m_emitters;
    rfg::linked_list_p<char> m_filters; //rfg::linked_list_p<vfx_particle_system_filter_instance> m_filters;
    rfg::linked_list_p<char> m_mesh_filters; //rfg::linked_list_p<vfx_renderable_filter_instance> m_mesh_filters;
    rfg::linked_list_p<rl_renderable_instance> m_renderable_mesh_insts;
    rfg::linked_list_p<rl_light> m_lights;
    void* m_renderable_particles_instance_group_p; //rl_renderable_particles_instance_group* m_renderable_particles_instance_group_p;
};

struct vfx_effect_manager
{
    struct effect_list : rfg::pool_list<vfx_effect*>
    {

    };

    struct effect_template_list : rfg::pool_list<vfx_effect_template*>
    {

    };

    vfx_effect_manager::effect_list effects_freelist;
    vfx_effect_manager::effect_list effects_registered;
    vfx_effect_manager::effect_template_list effect_templates;
};