#pragma once
#include "RFGR_Types_World.h"

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

struct rl_rect
{
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
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

	struct MemoryBlock
	{
		char* pStart;
		unsigned int size;
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

struct rl_singleton__rl_render_lib__Vtbl;
struct  rl_singleton__rl_render_lib
{
	rl_singleton__rl_render_lib__Vtbl* vfptr;
};

struct rl_singleton__rl_render_lib__Vtbl
{
	void *(__thiscall *__vecDelDtor)(rl_singleton__rl_render_lib* This, unsigned int);
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

struct  rl_render_lib : rl_base_object, rl_singleton__rl_render_lib
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