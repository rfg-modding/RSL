#pragma once
#include "RFGR_Types_World.h"

struct effect_info_flags
{
    __int8 sound_kill_oneshot_when_done : 1;
    __int8 sound_follows_effect_pos : 1;
    __int8 vfx_kill_particles_on_stop : 1;
    __int8 stop_when_host_destroyed : 1;
};

/* 5437 */
const struct  __declspec(align(4)) effect_info
{
    char name[65];
    unsigned int visual_handle;
    int sound_handle;
    int sound_alr_handle;
    float vfx_kill_particles_fade_time_s;
    effect_info_flags flags;
};

struct material_effect_layer_info
{
    char mat_name[64];
    int map_index;
    unsigned int flags;
};

/* 8381 */
struct material_effect_info
{
    char name[64];
    int num_layers;
    material_effect_layer_info layers[4];
    unsigned int srid;
};

/*struct rl_shader_header_runtime
{
	int signature;
	int version;
	unsigned int shader_flags;
	__int16 num_tex_fixups;
	__int16 num_const_fixups;
	__int16 num_bool_fixups;
	char num_vertex_shaders;
	char num_pixel_shaders;
	rl_dev_vertex_shader *vertex_shaders;
	rl_dev_pixel_shader *pixel_shaders;
	rl_shader_tex_fixup_runtime *tex_fixups;
	rl_shader_const_fixup *const_fixups;
	rl_shader_const_fixup *bool_fixups;
	char base_technique_index;
	char lighting_technique_index;
	char depth_only_technique_index;
	char user_technique_start_index;
	rl_shader_technique_runtime *shader_techniques;
	int num_techniques;
};

struct  rl_shader : rl_base_object
{
	rl_shader_header_runtime* m_shader_data_p;
	unsigned int m_max_user_space_const;
};*/



struct rl_singleton__rl_render_lib__Vtbl;
struct  rl_singleton__rl_render_lib
{
	rl_singleton__rl_render_lib__Vtbl* vfptr;
};

struct rl_singleton__rl_render_lib__Vtbl
{
	void *(__thiscall *__vecDelDtor)(rl_singleton__rl_render_lib* This, unsigned int);
};

struct mempool_base
{
	void* vfptr; //mempool_baseVtbl* vfptr;
	volatile bool locked;
	volatile unsigned int lock_id;
	char name[32];
	char flags;
	volatile unsigned int thread_id;
	unsigned int peak_usage;
};

/*union $058DF3FFA7125B0957BD799298D7361D
{
	void(__thiscall *~mempool_base)(mempool_base *This);
	void *(__thiscall *__vecDelDtor)(mempool_base *This, unsigned int);
};

struct mempool_baseVtbl
{
	void(__thiscall *set_thread_ownership)(mempool_base *this);
	char gap4[8]//_BYTE gap4[8];
	unsigned int(__thiscall *space_free)(mempool_base *this);
	unsigned int(__thiscall *space_used)(mempool_base *this);
	unsigned int(__thiscall *space_max)(mempool_base *this);
	bool(__thiscall *can_alloc)(mempool_base *this, unsigned int, unsigned int);
	void *(__thiscall *alloc)(mempool_base *this, unsigned int, unsigned int);
	void *(__thiscall *realloc)(mempool_base *this, void *, unsigned int);
	bool(__thiscall *contains_address)(mempool_base *this, const void *);
	bool(__thiscall *clear)(mempool_base *this);
	void *(__thiscall *get_base)(mempool_base *this);
	unsigned int(__thiscall *mark)(mempool_base *this);
	bool(__thiscall *restore_to_mark)(mempool_base *this, unsigned int);
	bool(__thiscall *release_bytes)(mempool_base *this, unsigned int);
	bool(__thiscall *pad_to_page)(mempool_base *this, unsigned int);
	$058DF3FFA7125B0957BD799298D7361D ___u14;
};*/

struct static_mempool_base : mempool_base
{
	char *last_alloc;
	char *pool;
	unsigned int max_size;
	unsigned int def_align;
	volatile unsigned int current_pos;
};

struct mempool : static_mempool_base
{
	volatile unsigned int end_pos;
};

namespace keen
{
    /* 26 */
    enum VertexAttributeId
    {
        VertexAttributeId_Position = 0x0,
        VertexAttributeId_Normal = 0x1,
        VertexAttributeId_Tangent = 0x2,
        VertexAttributeId_BiTangent = 0x3,
        VertexAttributeId_Color0 = 0x4,
        VertexAttributeId_Color1 = 0x5,
        VertexAttributeId_Color2 = 0x6,
        VertexAttributeId_TexCoord0 = 0x7,
        VertexAttributeId_TexCoord1 = 0x8,
        VertexAttributeId_TexCoord2 = 0x9,
        VertexAttributeId_TexCoord3 = 0xA,
        VertexAttributeId_TexCoord4 = 0xB,
        VertexAttributeId_TexCoord5 = 0xC,
        VertexAttributeId_TexCoord6 = 0xD,
        VertexAttributeId_TexCoord7 = 0xE,
        VertexAttributeId_BoneIndex = 0xF,
        VertexAttributeId_BoneWeight = 0x10,
        VertexAttributeId_Count = 0x11,
        VertexAttributeId_Invalid = 0xFF,
    };

    /* 28 */
    enum VertexAttributeFormat
    {
        VertexAttributeFormat_x32_float = 0x0,
        VertexAttributeFormat_x32y32_float = 0x1,
        VertexAttributeFormat_x32y32z32_float = 0x2,
        VertexAttributeFormat_x32y32z32w32_float = 0x3,
        VertexAttributeFormat_x16y16z16w16_float = 0x4,
        VertexAttributeFormat_x16y16z16w16_sint = 0x5,
        VertexAttributeFormat_x16y16z16w16_uint = 0x6,
        VertexAttributeFormat_x16y16z16w16_snorm = 0x7,
        VertexAttributeFormat_x16y16z16w16_unorm = 0x8,
        VertexAttributeFormat_x8y8z8w8_unorm = 0x9,
        VertexAttributeFormat_x8y8z8w8_uint = 0xA,
        VertexAttributeFormat_x8y8z8w8_snorm = 0xB,
        VertexAttributeFormat_x8y8z8w8_sint = 0xC,
        VertexAttributeFormat_x16y16_float = 0xD,
        VertexAttributeFormat_x16y16_sint = 0xE,
        VertexAttributeFormat_x16y16_snorm = 0xF,
        VertexAttributeFormat_x16y16_uint = 0x10,
        VertexAttributeFormat_x16y16_unorm = 0x11,
        VertexAttributeFormat_x10y10z10_snorm = 0x12,
        VertexAttributeFormat_x10y10z10w2_snorm = 0x13,
        VertexAttributeFormat_x11y11z10_snorm = 0x14,
        VertexAttributeFormat_z8y8x8w8_unorm = 0x15,
        VertexAttributeFormat_D3dColor = 0x16,
        VertexAttributeFormat_x16y16z16_snorm = 0x17,
        VertexAttributeFormat_x8y8z8_snorm = 0x18,
        VertexAttributeFormat_Count = 0x19,
        //VertexAttributeFormat_Default_Position3d = 0x2,
        //VertexAttributeFormat_Default_Normal = 0x2,
        //VertexAttributeFormat_Default_TangentFlip = 0x3,
        //VertexAttributeFormat_Default_TexCoord2d = 0xD,
        //VertexAttributeFormat_Default_Color = 0x9,
        //VertexAttributeFormat_Invalid = 0xFF,
    };
}

/* 1608 */
enum $8229491407A0F1FB035BE2A880EADB46
{
    VertexAttributeId_Position0 = 0x0,
    VertexAttributeId_Position1 = 0xB,
    VertexAttributeId_Position2 = 0xC,
    VertexAttributeId_Position3 = 0xD,
    VertexAttributeId_Position4 = 0xE,
    VertexAttributeId_Normal0 = 0x1,
    VertexAttributeId_Normal1 = 0x3,
    VertexAttributeId_PointSize = 0xE,
};

struct rl_state_manager
{
	unsigned int m_flags;
	rl_color_float m_primitive_color;
	int m_primitive_texture;
	int m_primitive_bink_y_texture;
	int m_primitive_bink_cr_texture;
	int m_primitive_bink_cb_texture;
	unsigned int m_primitive_material;
	rl_dev_vertex_format m_vertex_format;
	rl_shader_type m_shader_type;
	int m_shader_configuration;
	int m_shader_technique;
	void* m_shader_p; //rl_shader* m_shader_p;
	rl_primitive_state m_macro_state;
	rl_cull_mode m_cull_mode;
	rl_cull_mode m_shader_cull_mode;
	rl_fill_mode m_fill_mode;
	rl_color_float m_fade_color;
	rl_color_float m_tint_color;
	float m_saturation;
	rl_camera* m_active_camera_p;
	vector m_eye_position;
	vector m_render_offset;
	rl_color_float m_fog_color;
	rl_color_float m_ambient_color;
	rl_color_float m_back_ambient_color;
	__declspec(align(8)) vector4 m_fog_parameters;
	vector4 m_time_values;
	unsigned int m_target_width;
	unsigned int m_target_height;
	rl_prim_zbias_mode m_zbias_mode;
	rl_rect m_scissor_region;
	int m_local_world_stack_top;
	matrix43 m_local_world_transform[16];
	matrix44 m_world_view_transform;
	matrix44 m_projection_transform;
	matrix44 m_clip_screen_transform;
	matrix44 m_world_clip_transform;
	matrix44 m_world_screen_transform;
	matrix44 m_local_clip_transform;
	matrix44 m_shadow_texture_transform;
};

struct rl_render_lib_multisample_desc
{
	unsigned int m_samples;
	unsigned __int32 m_quality : 31;
	unsigned __int32 m_enabled : 1;
};

struct rl_render_lib : rl_base_object, rl_singleton__rl_render_lib
{
	rl_dev_blend_state m_prim_blend_states[22][8];
	rl_dev_sampler_state m_prim_sampler_states[2];
	rl_dev_depth_stencil_state m_prim_depth_stencil_states[13][5];
	keen::VertexFormat *m_vertex_formats_p[50];
	rl_dev_rasterizer_state m_engine_rasterizer_states[5][2][3][2];
	rl_dev_sampler_state m_material_sampler_states[2][2][2];
	rl_renderer_metrics *m_metrics_p;
	rl_level_of_detail m_level_of_detail;
	rl_level_of_detail m_new_level_of_detail;
	unsigned int m_current_frame_count;
	float m_texel_offset;
	unsigned int m_frametime_total_ms;
	unsigned int m_num_gpus;
	mempool m_shader_base_mempool;
	rl_screen_info m_screen_info;
	int m_last_width;
	int m_last_height;
	keen::graphics::WindowMode m_lastWindowMode;
	rl_render_lib_multisample_desc m_msaa_level[7];
	bool m_lodChanged;
	bool m_sizesChanged;
	keen::OcclusionQueryManager m_occlusionQueries;
	keen::Mutex m_inputBindingMutex;
};

struct rl_renderer
{
	keen::VertexBufferData m_vertexBufferData[3];
	keen::GeometryInstancingBuffer* m_instancing_buffer;
	__declspec(align(16)) keen::CommonVertexShaderConstants m_commonVertexData;
	keen::CommonFragmentShaderConstants m_commonFragmentData;
	keen::InstanceVertexShaderConstants m_instanceVertexData;
	keen::InstanceFragmentShaderConstants m_instanceFragmentData;
	keen::DecalVertexShaderConstants m_decalVertexData;
	keen::float4 m_materialConstantData[24];
	void* m_pCommandWriter; //keen::GraphicsCommandWriter *m_pCommandWriter;
	unsigned int m_constantDataDirtyMask;
	keen::DynamicConstantBuffer *m_pCommonVertexConstants;
	keen::DynamicConstantBuffer *m_pCommonFragmentConstants;
	keen::DynamicConstantBuffer *m_pSkinningVertexConstants;
	keen::DynamicConstantBuffer *m_pDecalVertexConstants;
	keen::DynamicConstantBuffer *m_pLightingVertexConstants;
	keen::DynamicConstantBuffer *m_pLightingFragmentConstants;
	keen::DynamicConstantBuffer *m_pMaterialVertexConstants;
	keen::DynamicConstantBuffer *m_pMaterialFragmentConstants;
	keen::DynamicConstantBuffer *m_pInstanceVertexConstants;
	keen::DynamicConstantBuffer *m_pInstanceFragmentConstants;
	unsigned int m_flags;
	rl_dev_present_result m_last_dev_status;
	rl_state_manager* m_state_p;
	rl_render_lib* m_pRenderLib;
	rl_rect m_viewPort;
	float m_z_near;
	float m_z_far;
	keen::ShaderPipeline *m_pipeline_p;
	keen::VertexInputBinding **m_input_layouts_p;
	rl_dev_vertex_format m_vertex_format;
	rl_dev_render_target m_render_target;
	rl_dev_depth_stencil_target m_depth_stencil_target;
	unsigned int m_merged_target_stack_index;
	keen::RenderTarget *m_merged_targets_p[8];
	keen::RenderTarget *m_current_target_p;
	unsigned int m_override_shader;
	rl_material_state_store m_state_store;
};

namespace keen
{
    struct RenderSwapChain;
    struct SkinningD3D11;

    struct SkinnedGeometryInstance
    {
        ID3D11Buffer* pVertexBuffer;
        char* pMappedData;
        unsigned int skinBufferOffset;
    };

    struct SkinningBatch
    {
        keen::SkinningD3D11* pSkinningBuffer;
        char* pMappedBufferData;
    };

    struct DataBuffer
    {
        char* m_pCurrentPosition;
        char* m_pEnd;
        char* m_pBufferStart;
    };

    struct SkinningD3D11
    {
        ID3D11Buffer* m_pSkinningBuffer;
        keen::SkinningBatch m_skinningBatch;
        keen::SizedArray<keen::SkinnedGeometryInstance> m_instances[2];
        unsigned int m_currentFrameIndex;
        unsigned int m_currentBufferPosition;
        unsigned int m_size;
        unsigned int m_bufferSize;
        void* m_pSkinningJointMatrices; //keen::SoftwareSkinningJointMatrixData* m_pSkinningJointMatrices;
        unsigned int m_currentJointMatricesPosition;
        void* m_pTaskQueue; //keen::TaskQueue* m_pTaskQueue;
        keen::DataBuffer m_morphBuffer;
        unsigned int m_morphBufferSize;
        void *m_pMorphBufferData;
    };

    struct StockObjects
    {
        keen::ShaderPipeline m_shaderPipelines[3];
        keen::VertexShader* m_pStockVertexShaders[2];
        keen::FragmentShader* m_pStockFragmentShaders[3];
        keen::VertexFormat* m_pFormats[3];
        keen::TextureData m_textures[1];
    };

    struct CombinedGraphicsStateObjectPool
    {
        keen::GraphicsStateObjectPool<keen::BlendState> m_blendStatePool;
        keen::GraphicsStateObjectPool<keen::RasterizerState> m_rasterizerStatePool;
        keen::GraphicsStateObjectPool<keen::SamplerState> m_samplerStatePool;
        keen::GraphicsStateObjectPool<keen::DepthStencilState> m_depthStencilStatePool;
        keen::GraphicsStateObjectPool<keen::VertexFormat> m_vertexFormatPool;
        keen::GraphicsStateObjectPool<keen::VertexInputBinding> m_vertexInputBindingPool;
    };

    struct GraphicsSystemBase
    {
        void* pShaderFactory; //keen::ShaderFactory* pShaderFactory;
        void* pSystemAllocator; //keen::MemoryAllocator* pSystemAllocator;
        keen::CombinedGraphicsStateObjectPool stateObjectPool;
        keen::StockObjects stockObjects;
    };

    struct GraphicsSystem : keen::GraphicsSystemBase
    {
        ID3D11Device* pDevice;
        ID3D11DeviceContext* pImmediateContext;
        float screenAspectRatio;
        HWND__* createdWindowHandle;
        bool isWindowDestroyed;
        keen::SkinningD3D11 skinningBuffer;
        unsigned int ownerThreadId;
        unsigned int frontThreadId;
        keen::GraphicsCommandBuffer immediateCommandBuffer;
        keen::GraphicsCommandBuffer deferredCommandBuffer;
        keen::FragmentShader emptyFragmentShader;
        keen::RenderSwapChain* pDefaultSwapChain;
        keen::RenderSwapChain* pCurrentSwapChain;
        unsigned int currentFrameNumber;
        void* pScreenCapture; //keen::ScreenCapture* pScreenCapture;
        keen::graphics::WindowMode previousFullscreenMode;
        keen::graphics::WindowMode fullscreenMode;
        unsigned int exclusiveModeWidth;
        unsigned int exclusiveModeHeight;
        unsigned int exclusiveModeRefreshRateNumerator;
        unsigned int exclusiveModeRefreshRateDenominator;
        unsigned int windowModeWidth;
        unsigned int windowModeHeight;
    };

    struct RenderSwapChain
    {
        keen::GraphicsSystem* pGraphicsSystem;
        keen::PixelFormat depthBufferFormat;
        HWND__* windowHandle;
        keen::TextureData backBufferColorData;
        keen::TextureData backBufferDepthData;
        keen::RenderTarget backBufferRenderTarget;
        keen::RenderTarget noGammaBackBufferRenderTarget;
        IDXGISwapChain* pSwapChain;
        DXGI_SWAP_CHAIN_DESC swapChainDescription;
        ID3D11RenderTargetView* pBackBufferRenderTargetView;
        ID3D11RenderTargetView* pNoGammaBackBufferRenderTargetView;
        ID3D11DepthStencilView* pBackBufferDepthView;
        unsigned int windowWidth;
        unsigned int windowHeight;
        unsigned int presentationInterval;
    };
}
