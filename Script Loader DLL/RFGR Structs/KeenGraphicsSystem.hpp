#pragma once
#include "KeenNamespace.h"
#include <DXGI.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace keen
{
	namespace graphics
	{
		/* 336 */
		enum WindowMode
		{
			WindowMode_Windowed = 0x0,
			WindowMode_Borderless = 0x1,
			WindowMode_Fullscreen = 0x2,
			WindowMode_Count = 0x3,
		};
	}

	/* 64 */
	enum ProjectionType
	{
		ProjectionType_Perspective = 0x0,
		ProjectionType_Orthographic = 0x1,
		ProjectionType_Count = 0x2,
	};

	/* 462 */
	enum ImmediateBlendMode
	{
		ImmediateBlendMode_Invalid = 0xFFFFFFFF,
		ImmediateBlendMode_None = 0x0,
		ImmediateBlendMode_Blend_Alpha = 0x1,
		ImmediateBlendMode_Add_Alpha = 0x2,
		ImmediateBlendMode_Sub_Alpha = 0x3,
		ImmediateBlendMode_Add = 0x4,
		ImmediateBlendMode_Sub = 0x5,
		ImmediateBlendMode_Count = 0x6,
	};

	/* 463 */
	enum ImmediateAlphaMode
	{
		ImmediateAlphaMode_Invalid = 0xFFFFFFFF,
		ImmediateAlphaMode_PremultipliedAlpha = 0x0,
		ImmediateAlphaMode_NonPremultipliedAlpha = 0x1,
		ImmediateAlphaMode_Count = 0x2,
		ImmediateAlphaMode_PlatformDefault = 0x1,
	};

	/* 464 */
	enum ImmediateDepthTestMode
	{
		ImmediateDepthTestMode_Never = 0x0,
		ImmediateDepthTestMode_Less = 0x1,
		ImmediateDepthTestMode_Equal = 0x2,
		ImmediateDepthTestMode_LessEqual = 0x3,
		ImmediateDepthTestMode_Greater = 0x4,
		ImmediateDepthTestMode_NotEqual = 0x5,
		ImmediateDepthTestMode_GreaterEqual = 0x6,
		ImmediateDepthTestMode_Always = 0x7,
		ImmediateDepthTestMode_Count = 0x8,
	};

	/* 465 */
	enum ImmediateDepthWriteMode
	{
		ImmediateDepthWriteMode_Enabled = 0x0,
		ImmediateDepthWriteMode_Disabled = 0x1,
		ImmediateDepthWriteMode_Count = 0x2,
	};

	/* 466 */
	enum ImmediateCullMode
	{
		ImmediateCullMode_None = 0x0,
		ImmediateCullMode_Back = 0x1,
		ImmediateCullMode_Front = 0x2,
		ImmediateCullMode_Count = 0x3,
	};

	/* 467 */
	enum ImmediateFillMode
	{
		ImmediateFillMode_Solid = 0x0,
		ImmediateFillMode_Wireframe = 0x1,
		ImmediateFillMode_Count = 0x2,
	};

	/* 468 */
	enum ImmediateTextureFilterMode
	{
		ImmediateTextureFilterMode_Nearest = 0x0,
		ImmediateTextureFilterMode_BiLinear = 0x1,
		ImmediateTextureFilterMode_TriLinear = 0x2,
		ImmediateTextureFilterMode_Count = 0x3,
	};

	/* 469 */
	enum ImmediateTextureAddressMode
	{
		ImmediateTextureAddressMode_Wrap = 0x0,
		ImmediateTextureAddressMode_Mirror = 0x1,
		ImmediateTextureAddressMode_Clamp = 0x2,
		ImmediateTextureAddressMode_Count = 0x3,
	};

	/* 477 */
	enum ScreenCaptureState
	{
		ScreenCaptureState_Recording = 0x0,
		ScreenCaptureState_StartWriting = 0x1,
		ScreenCaptureState_Writing = 0x2,
		ScreenCaptureState_StartRecording = 0x3,
	};

	/* 484 */
	enum GraphicsStateObjectType
	{
		GraphicsStateObjectType_BlendState = 0x0,
		GraphicsStateObjectType_RasterizerState = 0x1,
		GraphicsStateObjectType_SamplerState = 0x2,
		GraphicsStateObjectType_DepthStencilState = 0x3,
		GraphicsStateObjectType_VertexFormat = 0x4,
		GraphicsStateObjectType_VertexInputBinding = 0x5,
		GraphicsStateObjectType_Count = 0x6,
	};

	/* 242 */
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

	/* 67 */
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

	/* 3270 */
	struct D3D11_RASTERIZER_DESC
	{
		D3D11_FILL_MODE FillMode;
		D3D11_CULL_MODE CullMode;
		int FrontCounterClockwise;
		int DepthBias;
		float DepthBiasClamp;
		float SlopeScaledDepthBias;
		int DepthClipEnable;
		int ScissorEnable;
		int MultisampleEnable;
		int AntialiasedLineEnable;
	};

	/* 3271 */
	struct CD3D11_QUERY_DESC : D3D11_QUERY_DESC
	{

	};

	/* 3272 */
	struct _XMSHORTN4
	{
		__int16 x;
		__int16 y;
		__int16 z;
		__int16 w;
	};

	/* 3273 */
	struct CD3D11_VIEWPORT : D3D11_VIEWPORT
	{

	};

	/* 3274 */
	struct CD3D11_DEPTH_STENCIL_DESC : D3D11_DEPTH_STENCIL_DESC
	{

	};

	/* 3275 */
	union $E4DFE8BEB43F9A2F2521D89DB9FA3F7A
	{
		unsigned int u[4];
		__m128 v;
	};

	/* 3276 */
	struct XMVECTORU32
	{
		$E4DFE8BEB43F9A2F2521D89DB9FA3F7A ___u0;
	};

	/* 3277 */
	struct  __declspec(align(16)) XMFLOAT2A : _XMFLOAT2
	{

	};

	/* 3278 */
	struct $AB1E74D5BEA037416C105EC420DB6EF3
	{
		__int64 x : 20;
		__int64 y : 20;
		__int64 z : 20;
		__int64 w : 4;
	};

	/* 3279 */
	union $2BB689D4C70620C64AB8E171B51331E7
	{
		$AB1E74D5BEA037416C105EC420DB6EF3 __s0;
		unsigned __int64 v;
	};

	/* 3280 */
	struct _XMICON4
	{
		$2BB689D4C70620C64AB8E171B51331E7 ___u0;
	};

	/* 3281 */
	struct _XMSHORT2
	{
		__int16 x;
		__int16 y;
	};

	/* 3282 */
	struct  CD3D11_SAMPLER_DESC : D3D11_SAMPLER_DESC
	{
	};

	/* 3283 */
	struct D3D10_TEXTURE3D_DESC
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Depth;
		unsigned int MipLevels;
		DXGI_FORMAT Format;
		D3D10_USAGE Usage;
		unsigned int BindFlags;
		unsigned int CPUAccessFlags;
		unsigned int MiscFlags;
	};

	/* 3284 */
	struct  CD3D10_TEXTURE3D_DESC : D3D10_TEXTURE3D_DESC
	{
	};

	/* 3285 */
	struct _XMUSHORT4
	{
		unsigned __int16 x;
		unsigned __int16 y;
		unsigned __int16 z;
		unsigned __int16 w;
	};

	/* 3182 */
	struct $C3417F61F4833792F44264398840ADCA
	{
		unsigned __int64 x : 20;
		unsigned __int64 y : 20;
		unsigned __int64 z : 20;
		unsigned __int64 w : 4;
	};

	/* 3183 */
	union $15C3FEEC41D653F6774DA570F9939961
	{
		$C3417F61F4833792F44264398840ADCA __s0;
		unsigned __int64 v;
	};

	/* 3286 */
	struct _XMUICON4
	{
		$15C3FEEC41D653F6774DA570F9939961 ___u0;
	};

	/* 3287 */
	struct _XMICO4
	{
		$2BB689D4C70620C64AB8E171B51331E7 ___u0;
	};

	/* 3288 */
	struct D3D10_TEXTURE2D_DESC
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int MipLevels;
		unsigned int ArraySize;
		DXGI_FORMAT Format;
		DXGI_SAMPLE_DESC SampleDesc;
		D3D10_USAGE Usage;
		unsigned int BindFlags;
		unsigned int CPUAccessFlags;
		unsigned int MiscFlags;
	};

	/* 3289 */
	struct CD3D10_TEXTURE2D_DESC : D3D10_TEXTURE2D_DESC
	{
	};

	/* 3290 */
	struct SkinningSimdMatrix33
	{
		__m128 x;
		__m128 y;
		__m128 z;
	};

	/* 3291 */
	struct GraphicsStateObject
	{
		unsigned int hash;
		unsigned int refCount;
	};

	/* 3292 */
	struct DepthStencilState : GraphicsStateObject
	{
		ID3D11DepthStencilState *pState;
	};

	/* 3293 */
	struct RasterizerState : GraphicsStateObject
	{
		ID3D11RasterizerState *pState;
	};

	/* 3294 */
	struct BlendState : GraphicsStateObject
	{
		ID3D11BlendState *pState;
	};

	/* 3295 */
	struct SamplerState : GraphicsStateObject
	{
		ID3D11SamplerState *pState;
	};

	/* 3296 */
	struct DynamicConstantBuffer
	{
		ID3D11Buffer *pBuffer;
		unsigned int sizeInBytes;
	};

	/* 3297 */
	const struct FragmentShader
	{
		ID3D11PixelShader *pPixelShader;
	};

	/* 3298 */
	struct Array_D3D11_SIGNATURE_PARAMETER_DESC
	{
		_D3D11_SIGNATURE_PARAMETER_DESC *m_pData;
		unsigned int m_size;
	};

	/* 3299 */
	const struct VertexShader
	{
		keen::Array_unsigned_char shaderCode;
		ID3D11VertexShader *pVertexShader;
		Array_D3D11_SIGNATURE_PARAMETER_DESC inputSignature;
		unsigned int inputSignatureHash;
	};

	/* 3300 */
	struct ShaderPipeline
	{
		keen::VertexShader *pVertexShader;
		keen::FragmentShader *pFragmentShader;
	};

	/* 3301 */
	struct FallbackVariants
	{
		keen::FragmentShader *m_fragmentShaders[3];
		keen::VertexShader *m_vertexShaders[4];
		keen::ShaderPipeline m_pipelines[12];
	};

	/* 3304 */
	struct PoolAllocator_BlendState
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 2454 */
	struct InternalListBase
	{
		/* 2452 */
		struct Listable
		{
			keen::InternalListBase::Listable *m_pNext;
			keen::InternalListBase::Listable *m_pPrev;
		};
		/* 2453 */
		struct IteratorBase
		{
			keen::InternalListBase::Listable *m_pCurrent;
		};


		keen::InternalListBase::Listable *m_pFirst;
		keen::InternalListBase::Listable *m_pLast;
		unsigned int m_numObjects;
		keen::InternalListBase::IteratorBase m_begin;
		keen::InternalListBase::IteratorBase m_end;
		keen::InternalListBase::IteratorBase m_local;
	};

	/* 3305 */
	struct PoolAllocator_HashMap_unsigned_int__GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject__Entry
	{
		keen::BasePoolAllocator m_pool;
	};

	//struct keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry>::Iterator : keen::InternalListBase::IteratorBase
	/* 3306 */
	struct InternalList_HashMap_unsigned_int___GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject___Entry___Iterator : keen::InternalListBase::IteratorBase
	{

	};

	//Array<keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry>::Iterator>
	/* 3307 */
	struct Array_InternalList_HashMap_unsigned_int__GraphicsStateObject___DefaultHashmapTraits_unsigned_int__GraphicsStateObject__Entry__Iterator
	{
		keen::InternalList_HashMap_unsigned_int___GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject___Entry___Iterator* m_pData;
		unsigned int m_size;
	};

	//InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry>
	/* 3308 */
	struct InternalList_HashMap_unsigned_int__GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject__Entry : keen::InternalListBase
	{

	};

	//HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >
	/* 3309 */
	struct HashMap_unsigned_int__GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject
	{
		keen::PoolAllocator_HashMap_unsigned_int__GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject__Entry *m_pEntryAllocator;
		bool m_ownsAllocator;
		keen::Array_InternalList_HashMap_unsigned_int__GraphicsStateObject___DefaultHashmapTraits_unsigned_int__GraphicsStateObject__Entry__Iterator m_buckets;
		keen::InternalList_HashMap_unsigned_int__GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject__Entry m_entries;
		unsigned int m_bucketCount;
		unsigned int m_bucketMask;
	};

	/* 3310 */
	struct GraphicsStateObjectCache
	{
		HashMap_unsigned_int__GraphicsStateObject__DefaultHashmapTraits_unsigned_int__GraphicsStateObject m_stateObjects;
	};

	/* 3311 */
	struct GraphicsStateObjectPool_BlendState
	{
		keen::PoolAllocator_BlendState m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3312 */
	struct PoolAllocator_RasterizerState
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3313 */
	struct GraphicsStateObjectPool_RasterizerState
	{
		keen::PoolAllocator_RasterizerState m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3314 */
	struct PoolAllocator_SamplerState
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3315 */
	struct GraphicsStateObjectPool_SamplerState
	{
		keen::PoolAllocator_SamplerState m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3316 */
	struct PoolAllocator_DepthStencilState
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3317 */
	struct GraphicsStateObjectPool_DepthStencilState
	{
		keen::PoolAllocator_DepthStencilState m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3318 */
	struct PoolAllocator_VertexFormat
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3319 */
	struct GraphicsStateObjectPool_VertexFormat
	{
		keen::PoolAllocator_VertexFormat m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3320 */
	struct PoolAllocator_VertexInputBinding
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3321 */
	struct GraphicsStateObjectPool_VertexInputBinding
	{
		keen::PoolAllocator_VertexInputBinding m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3322 */
	struct CombinedGraphicsStateObjectPool
	{
		keen::GraphicsStateObjectPool_BlendState m_blendStatePool;
		keen::GraphicsStateObjectPool_RasterizerState m_rasterizerStatePool;
		keen::GraphicsStateObjectPool_SamplerState m_samplerStatePool;
		keen::GraphicsStateObjectPool_DepthStencilState m_depthStencilStatePool;
		keen::GraphicsStateObjectPool_VertexFormat m_vertexFormatPool;
		keen::GraphicsStateObjectPool_VertexInputBinding m_vertexInputBindingPool;
	};

	/* 3324 */
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

	/* 3325 */
	struct TextureData
	{
		keen::TextureDescription description;
		ID3D11Resource *pTexture;
		ID3D11ShaderResourceView *pShaderView;
		DXGI_FORMAT d3dFormat;
	};

	/* 2485 */
	struct VertexAttributeDescription
	{
		char id;
		char format;
		char inputStreamIndex;
		char instanceStepRate;
	};

	/* 3323 */
	const struct VertexFormat : keen::GraphicsStateObject
	{
		keen::VertexAttributeDescription attributes[17];
		unsigned int attributeOffsets[17];
		unsigned int attributeCount;
		unsigned int attributeIndices[17];
		unsigned int streamStride[6];
		unsigned int instanceDataStreamIndex;
	};

	/* 3326 */
	struct StockObjects
	{
		keen::ShaderPipeline m_shaderPipelines[3];
		keen::VertexShader *m_pStockVertexShaders[2];
		keen::FragmentShader *m_pStockFragmentShaders[3];
		keen::VertexFormat *m_pFormats[3];
		keen::TextureData m_textures[1];
	};

	/* 3303 */
	struct ShaderFactory
	{
		keen::FileSystem *pShaderFileSystem;
		keen::GraphicsSystem *pGraphicsSystem;
		keen::TlsfMemoryAllocator scratchAllocator;
		keen::TlsfMemoryAllocator shaderObjectAllocator;
		keen::TlsfMemoryAllocator shaderProgramCodeAllocator;
		keen::MemoryAllocator *pShaderProgramCodeAllocator;
	};

	/* 3327 */
	struct GraphicsSystemBase
	{
		keen::ShaderFactory *pShaderFactory;
		keen::MemoryAllocator *pSystemAllocator;
		keen::CombinedGraphicsStateObjectPool stateObjectPool;
		keen::StockObjects stockObjects;
	};

	/* 3330 */
	struct SkinningBatch
	{
		keen::SkinningD3D11 *pSkinningBuffer;
		char *pMappedBufferData;
	};

	/* 3331 */
	struct SkinnedGeometryInstance
	{
		ID3D11Buffer *pVertexBuffer;
		char *pMappedData;
		unsigned int skinBufferOffset;
	};

	/* 3332 */
	struct SizedArray_SkinnedGeometryInstance
	{
		keen::SkinnedGeometryInstance *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3347 */
	struct DataBuffer
	{
		char *m_pCurrentPosition;
		char *m_pEnd;
		char *m_pBufferStart;
	};

	/* 3333 */
	struct SkinningSimdMatrix43
	{
		keen::SkinningSimdMatrix33 rot;
		__m128 pos;
	};

	/* 3334 */
	struct SoftwareSkinningJointMatrixData
	{
		keen::SkinningSimdMatrix43 jointMatrices[256];
	};

	/* 3329 */
	struct SkinningD3D11
	{
		ID3D11Buffer *m_pSkinningBuffer;
		keen::SkinningBatch m_skinningBatch;
		keen::SizedArray_SkinnedGeometryInstance m_instances[2];
		unsigned int m_currentFrameIndex;
		unsigned int m_currentBufferPosition;
		unsigned int m_size;
		unsigned int m_bufferSize;
		keen::SoftwareSkinningJointMatrixData *m_pSkinningJointMatrices;
		unsigned int m_currentJointMatricesPosition;
		keen::TaskQueue *m_pTaskQueue;
		keen::DataBuffer m_morphBuffer;
		unsigned int m_morphBufferSize;
		void *m_pMorphBufferData;
	};

	/* 3348 */
	struct RenderTargetBuffer
	{
		keen::PixelFormat format;
		keen::TextureData *pDataBuffer;
	};

	/* 3349 */
	const struct RenderTarget
	{
		ID3D11RenderTargetView *renderTargetViews[8];
		ID3D11DepthStencilView *pDepthBufferView;
		keen::RenderTargetBuffer colorBuffers[8];
		keen::RenderTargetBuffer depthBuffer;
		unsigned int colorBufferCount;
		unsigned int width;
		unsigned int height;
	};

	/* 3350 */
	struct DownsampleDepthVariants
	{
		keen::FragmentShader *m_fragmentShaders[2];
		keen::VertexShader *m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[2];
	};

	/* 3351 */
	struct CopyDepthVariants
	{
		keen::FragmentShader *m_fragmentShaders[1];
		keen::VertexShader *m_vertexShaders[1];
		keen::ShaderPipeline m_pipelines[1];
	};

	/* 3352 */
	const struct VertexInputBinding : keen::GraphicsStateObject
	{
		keen::VertexFormat *pVertexFormat;
		ID3D11InputLayout *pLayout;
		unsigned int geometryModeMask;
	};

	/* 3353 */
	struct StockVertexPos2f
	{
		keen::float2 position;
	};

	/* 3364 */
	const struct StaticConstantBuffer
	{
		ID3D11Buffer *pBuffer;
		unsigned int sizeInBytes;
	};

	/* 2482 */
	struct GraphicsMatrix43
	{
		float row0[4];
		float row1[4];
		float row2[4];
	};

	/* 2471 */
	struct PerspectiveProjection
	{
		float aspectRatio;
		float nearClip;
		float farClip;
		float fovY;
	};
	/* 2472 */
	struct OrthographicProjection
	{
		float x0;
		float x1;
		float y0;
		float y1;
		float z0;
		float z1;
	};
	/* 2473 */
	union $BF4FE4277C2DBB62089E59F5A39002B2
	{
		keen::PerspectiveProjection perspective;
		keen::OrthographicProjection orthographic;
	};

	/* 2481 */
	struct Plane
	{
		keen::Vector4 data;
	};

	/* 2483 */
	struct Frustum
	{
		keen::Plane m_planes[6];
	};

	/* 2474 */
	struct __declspec(align(4)) Projection
	{
		$BF4FE4277C2DBB62089E59F5A39002B2 data;
		keen::ProjectionType type;
		bool rightHanded;
	};

	/* 2490 */
	struct __declspec(align(4)) Camera
	{
		keen::Matrix43 m_worldMatrix;
		keen::Projection m_projection;
		keen::Matrix43 m_viewMatrix;
		keen::Frustum m_frustum;
		bool m_viewDirty;
		bool m_frustumDirty;
	};

	/* 3365 */
	struct GraphicsCommandWriter
	{
		keen::GraphicsCommandBuffer *m_pBuffer;
		keen::GraphicsSystem *m_pGraphicsSystem;
		keen::RenderTarget *m_pRenderTarget;
		keen::VertexInputBinding *m_pVertexInputBinding;
		keen::BlendState *m_pBlendState;
		keen::RasterizerState *m_pRasterizerState;
		keen::DepthStencilState *m_pDepthStencilState;
		keen::SamplerState *m_fragmentShaderSamplerStates[16];
		keen::TextureData *m_fragmentShaderTextures[16];
		keen::ShaderPipeline *m_pShaderPipeline;
		keen::TextureData *m_vertexShaderTextures[16];
		keen::SamplerState *m_vertexShaderSamplerStates[16];
		keen::VertexFormat *m_screenQuadVertexFormats[3];
		keen::RenderTarget *m_renderPassStack[4];
		keen::StaticConstantBuffer *m_currentStaticVertexConstantBuffers[8];
		keen::StaticConstantBuffer *m_currentStaticFragmentConstantBuffers[8];
		unsigned int m_renderPassStackIndex;
		unsigned int m_stencilRefValue;
		unsigned int m_mappedConstantBufferSlotIndex;
	};
	
	/* 3366 */
	struct ImmediateRenderer
	{
		keen::GraphicsCommandWriter *m_pCommandWriter;
		void *m_pVertexData;
		keen::GraphicsSystem *m_pGraphicsSystem;
		keen::RasterizerState *m_pRasterizerStates[3][2];
		keen::BlendState *m_pBlendStates[2][6];
		keen::DepthStencilState *m_pDepthStencilState[8][2];
		keen::SamplerState *m_pSamplerState[3][3];
		keen::DynamicConstantBuffer *m_pShaderParameterBuffer;
		keen::DynamicConstantBuffer *m_pFragmentParameterBuffer;
		keen::ShaderPipeline *m_pShaderPipeline;
		keen::ShaderPipeline *m_pShaderPipelineVolumeSlice;
		keen::VertexFormat *m_pVertexFormat;
		keen::VertexInputBinding *m_pVertexInputBinding;
		keen::VertexInputBinding *m_pVolumeSliceInputBinding;
		keen::TextureData *m_pWhiteTexture;
		keen::Matrix44 m_viewProjectionMatrix;
		keen::Matrix43 m_worldMatrix;
		unsigned int m_screenWidth;
		unsigned int m_screenHeight;
		bool m_mvpMatrixDirty;
		bool m_endFinalRenderPass;
		keen::ImmediateCullMode m_cullMode;
		keen::ImmediateFillMode m_fillMode;
		keen::Camera m_renderPassCameraData[4];
		keen::Camera *m_renderPassCameras[4];
		unsigned int m_currentRenderPassStackSize;
	};

	/* 3367 */
	struct ScreenCapture
	{
		keen::GraphicsSystem *pGraphicsSystem;
		keen::FileSystem *pFileSystem;
		unsigned int width;
		unsigned int height;
		keen::TextureData captureTargetData;
		keen::TextureData captureCopyData;
		keen::RenderTarget *pCaptureTarget;
		keen::RenderTarget *pNoGammaCaptureTarget;
		keen::Array_unsigned_char_pointer frameBuffer;
		unsigned int frameBufferWriteIndex;
		keen::Array_unsigned_char_pointer tempBuffer;
		unsigned int tempBufferWriteIndex;
		unsigned int tempBufferReadIndex;
		keen::ImmediateRenderer immediateRenderer;
		char basePath[128];
		char subPath[128];
		char filenamePrefix[128];
		keen::Thread thread;
		bool threadStarted;
		keen::Semaphore tempBufferDataCount;
		keen::Semaphore tempBufferFreeCount;
		unsigned int captureCount;
		unsigned int saveFrameIndex;
		keen::ScreenCaptureState state;
	};

	/* 3362 */
	struct RenderSwapChain
	{
		keen::GraphicsSystem *pGraphicsSystem; //4
		keen::PixelFormat depthBufferFormat;
		HWND__ *windowHandle; //4
		keen::TextureData backBufferColorData;
		keen::TextureData backBufferDepthData;
		keen::RenderTarget backBufferRenderTarget;
		keen::RenderTarget noGammaBackBufferRenderTarget;
		IDXGISwapChain *pSwapChain; //4
		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		ID3D11RenderTargetView *pBackBufferRenderTargetView; //4
		ID3D11RenderTargetView *pNoGammaBackBufferRenderTargetView; //4
		ID3D11DepthStencilView *pBackBufferDepthView; //4
		unsigned int windowWidth;
		unsigned int windowHeight;
		unsigned int presentationInterval;
	};

	/* 3354 */
	struct DownsampleDepthContext
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
	};

	/* 3355 */
	struct GraphicsCommandBuffer
	{
		ID3D11DeviceContext *pContext;
		ID3D11Buffer *pMappedConstantBuffer;
		keen::RenderTarget *pCurrentRenderTarget;
		keen::SkinningD3D11 *pSkinningBuffer;
		ID3D11Buffer *pImmediateVertexData;
		unsigned int immediateVertexBufferOffset;
		unsigned int immediateVertexBufferSize;
		unsigned int immediateVertexDataStride;
		unsigned int immediateVertexCount;
		keen::PrimitiveType immediatePrimitiveType;
		keen::DownsampleDepthContext *pDownsampleDepthContext;
		keen::VertexFormat *pCurrentlyBoundVertexFormat;
		void *pRenderCommandBufferStorage;
		bool quadlistImmediateCommand;
		char *pCurrentImmediateBuffer;
		char quadBuffer[65536];
	};

	/* 3302 */
	struct GraphicsSystem : keen::GraphicsSystemBase
	{
		ID3D11Device *pDevice;
		ID3D11DeviceContext *pImmediateContext;
		float screenAspectRatio;
		HWND__ *createdWindowHandle;
		bool isWindowDestroyed;
		keen::SkinningD3D11 skinningBuffer;
		unsigned int ownerThreadId;
		unsigned int frontThreadId;
		keen::GraphicsCommandBuffer immediateCommandBuffer;
		keen::GraphicsCommandBuffer deferredCommandBuffer;
		keen::FragmentShader emptyFragmentShader;
		keen::RenderSwapChain *pDefaultSwapChain;
		keen::RenderSwapChain *pCurrentSwapChain;
		unsigned int currentFrameNumber;
		keen::ScreenCapture *pScreenCapture;
		keen::graphics::WindowMode previousFullscreenMode;
		keen::graphics::WindowMode fullscreenMode;
		unsigned int exclusiveModeWidth;
		unsigned int exclusiveModeHeight;
		unsigned int exclusiveModeRefreshRateNumerator;
		unsigned int exclusiveModeRefreshRateDenominator;
		unsigned int windowModeWidth;
		unsigned int windowModeHeight;
	};
};