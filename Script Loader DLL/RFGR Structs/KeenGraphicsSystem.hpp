#pragma once
#include "KeenNamespace.h"
#include <DXGI.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace keen
{
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
	struct __cppobj CD3D11_QUERY_DESC : D3D11_QUERY_DESC
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
	struct __cppobj CD3D11_VIEWPORT : D3D11_VIEWPORT
	{
	};

	/* 3274 */
	struct __cppobj CD3D11_DEPTH_STENCIL_DESC : D3D11_DEPTH_STENCIL_DESC
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
	struct __cppobj __declspec(align(16)) XMFLOAT2A : _XMFLOAT2
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
	struct __cppobj CD3D11_SAMPLER_DESC : D3D11_SAMPLER_DESC
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
	struct __cppobj CD3D10_TEXTURE3D_DESC : D3D10_TEXTURE3D_DESC
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
	struct __cppobj CD3D10_TEXTURE2D_DESC : D3D10_TEXTURE2D_DESC
	{
	};

	/* 3290 */
	struct keen::SkinningSimdMatrix33
	{
		__m128 x;
		__m128 y;
		__m128 z;
	};

	/* 3291 */
	struct keen::GraphicsStateObject
	{
		unsigned int hash;
		unsigned int refCount;
	};

	/* 3292 */
	struct __cppobj keen::DepthStencilState : keen::GraphicsStateObject
	{
		ID3D11DepthStencilState *pState;
	};

	/* 3293 */
	struct __cppobj keen::RasterizerState : keen::GraphicsStateObject
	{
		ID3D11RasterizerState *pState;
	};

	/* 3294 */
	struct __cppobj keen::BlendState : keen::GraphicsStateObject
	{
		ID3D11BlendState *pState;
	};

	/* 3295 */
	struct __cppobj keen::SamplerState : keen::GraphicsStateObject
	{
		ID3D11SamplerState *pState;
	};

	/* 3296 */
	struct keen::DynamicConstantBuffer
	{
		ID3D11Buffer *pBuffer;
		unsigned int sizeInBytes;
	};

	/* 3297 */
	const struct keen::FragmentShader
	{
		ID3D11PixelShader *pPixelShader;
	};

	/* 3298 */
	struct keen::Array<_D3D11_SIGNATURE_PARAMETER_DESC>
	{
		_D3D11_SIGNATURE_PARAMETER_DESC *m_pData;
		unsigned int m_size;
	};

	/* 3299 */
	const struct keen::VertexShader
	{
		keen::Array<unsigned char> shaderCode;
		ID3D11VertexShader *pVertexShader;
		keen::Array<_D3D11_SIGNATURE_PARAMETER_DESC> inputSignature;
		unsigned int inputSignatureHash;
	};

	/* 3300 */
	struct keen::ShaderPipeline
	{
		keen::VertexShader *pVertexShader;
		keen::FragmentShader *pFragmentShader;
	};

	/* 3301 */
	struct keen::FallbackVariants
	{
		keen::FragmentShader *m_fragmentShaders[3];
		keen::VertexShader *m_vertexShaders[4];
		keen::ShaderPipeline m_pipelines[12];
	};

	/* 3304 */
	struct keen::PoolAllocator<keen::BlendState>
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3307 */
	struct keen::Array<keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry>::Iterator>
	{
		keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry>::Iterator *m_pData;
		unsigned int m_size;
	};

	/* 3308 */
	struct __cppobj keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry> : keen::InternalListBase
	{
	};

	/* 3309 */
	struct keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >
	{
		keen::PoolAllocator<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry> *m_pEntryAllocator;
		bool m_ownsAllocator;
		keen::Array<keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry>::Iterator> m_buckets;
		keen::InternalList<keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> >::Entry> m_entries;
		unsigned int m_bucketCount;
		unsigned int m_bucketMask;
	};

	/* 3310 */
	struct keen::GraphicsStateObjectCache
	{
		keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> > m_stateObjects;
	};

	/* 3311 */
	struct keen::GraphicsStateObjectPool<keen::BlendState>
	{
		keen::PoolAllocator<keen::BlendState> m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3312 */
	struct keen::PoolAllocator<keen::RasterizerState>
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3313 */
	struct keen::GraphicsStateObjectPool<keen::RasterizerState>
	{
		keen::PoolAllocator<keen::RasterizerState> m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3314 */
	struct keen::PoolAllocator<keen::SamplerState>
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3315 */
	struct keen::GraphicsStateObjectPool<keen::SamplerState>
	{
		keen::PoolAllocator<keen::SamplerState> m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3316 */
	struct keen::PoolAllocator<keen::DepthStencilState>
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3317 */
	struct keen::GraphicsStateObjectPool<keen::DepthStencilState>
	{
		keen::PoolAllocator<keen::DepthStencilState> m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3318 */
	struct keen::PoolAllocator<keen::VertexFormat>
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3319 */
	struct keen::GraphicsStateObjectPool<keen::VertexFormat>
	{
		keen::PoolAllocator<keen::VertexFormat> m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3320 */
	struct keen::PoolAllocator<keen::VertexInputBinding>
	{
		keen::BasePoolAllocator m_pool;
	};

	/* 3321 */
	struct keen::GraphicsStateObjectPool<keen::VertexInputBinding>
	{
		keen::PoolAllocator<keen::VertexInputBinding> m_allocator;
		keen::GraphicsStateObjectCache m_cache;
		unsigned int m_peakSize;
		unsigned int m_cacheHits;
		unsigned int m_cacheRequests;
	};

	/* 3322 */
	struct keen::CombinedGraphicsStateObjectPool
	{
		keen::GraphicsStateObjectPool<keen::BlendState> m_blendStatePool;
		keen::GraphicsStateObjectPool<keen::RasterizerState> m_rasterizerStatePool;
		keen::GraphicsStateObjectPool<keen::SamplerState> m_samplerStatePool;
		keen::GraphicsStateObjectPool<keen::DepthStencilState> m_depthStencilStatePool;
		keen::GraphicsStateObjectPool<keen::VertexFormat> m_vertexFormatPool;
		keen::GraphicsStateObjectPool<keen::VertexInputBinding> m_vertexInputBindingPool;
	};

	/* 3324 */
	struct keen::TextureDescription
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
	struct keen::TextureData
	{
		keen::TextureDescription description;
		ID3D11Resource *pTexture;
		ID3D11ShaderResourceView *pShaderView;
		DXGI_FORMAT d3dFormat;
	};

	/* 3326 */
	struct keen::StockObjects
	{
		keen::ShaderPipeline m_shaderPipelines[3];
		keen::VertexShader *m_pStockVertexShaders[2];
		keen::FragmentShader *m_pStockFragmentShaders[3];
		keen::VertexFormat *m_pFormats[3];
		keen::TextureData m_textures[1];
	};

	/* 3327 */
	struct keen::GraphicsSystemBase
	{
		keen::ShaderFactory *pShaderFactory;
		keen::MemoryAllocator *pSystemAllocator;
		keen::CombinedGraphicsStateObjectPool stateObjectPool;
		keen::StockObjects stockObjects;
	};

	/* 3330 */
	struct keen::SkinningBatch
	{
		keen::SkinningD3D11 *pSkinningBuffer;
		char *pMappedBufferData;
	};

	/* 3332 */
	struct keen::SizedArray<keen::SkinnedGeometryInstance>
	{
		keen::SkinnedGeometryInstance *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3347 */
	struct keen::DataBuffer
	{
		char *m_pCurrentPosition;
		char *m_pEnd;
		char *m_pBufferStart;
	};

	/* 3329 */
	struct keen::SkinningD3D11
	{
		ID3D11Buffer *m_pSkinningBuffer;
		keen::SkinningBatch m_skinningBatch;
		keen::SizedArray<keen::SkinnedGeometryInstance> m_instances[2];
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

	/* 3355 */
	struct keen::GraphicsCommandBuffer
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
	struct __cppobj keen::GraphicsSystem : keen::GraphicsSystemBase
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