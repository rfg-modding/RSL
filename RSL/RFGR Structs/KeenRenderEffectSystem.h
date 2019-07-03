#pragma once
#include "KeenNamespace.h"

namespace keen
{
	/* 3379 */
	struct Blob
	{
		unsigned int size;
	};

	/* 3380 */
	struct BlobMember_SoftwareSkinningBoneInfo
	{
		unsigned int offset;
	};

	/* 3381 */
	struct BlobMember_float3
	{
		unsigned int offset;
	};

	/* 3382 */
	struct BlobMember_float4
	{
		unsigned int offset;
	};

	/* 3383 */
	const struct SoftwareSkinGeometry : keen::Blob
	{
		keen::BlobMember_SoftwareSkinningBoneInfo boneInfos;
		keen::BlobMember_float3 positions;
		keen::BlobMember_float3 normals;
		keen::BlobMember_float4 tangents;
	};

	/* 3384 */
	const struct SoftwareMorphData : keen::Blob
	{
		keen::BlobMember_float3 positions;
		keen::BlobMember_float3 normals;
	};

	/* 3385 */
	const struct RenderGeometry
	{
		keen::VertexFormat *pVertexFormat;
		ID3D11Buffer *pVertexBuffer;
		unsigned int vertexCount;
		ID3D11Buffer *pIndexBuffer;
		unsigned int indexCount;
		keen::SoftwareSkinGeometry *pSkinGeometry;
		unsigned int skinningBufferOffset;
		const char *pDebugName;
		unsigned int indexFormat;
		unsigned int primitiveTopology;
		keen::SoftwareMorphData *pMorphData;
	};

	/* 3386 */
	const struct GeometryInstancingBatch
	{
		ID3D11Buffer *pVertexBuffer;
		unsigned int instanceCount;
		unsigned int vertexBufferByteOffset;
		unsigned int vertexBufferStride;
	};

	/* 3387 */
	const struct RenderInstance
	{
		keen::Matrix43 worldTransform;
		keen::SkinnedGeometryInstance *pSkinnedInstance;
		keen::GeometryInstancingBatch *pInstancingData;
	};

	/* 3378 */
	const struct BaseMaterialData
	{
		unsigned int renderEffectId;
		unsigned int mainTextureHandleOffset;
	};

	/* 3388 */
	const struct RenderObject
	{
		keen::BaseMaterialData *pMaterial;
		keen::RenderGeometry *pGeometry;
		keen::RenderInstance *pInstance;
	};

	/* 3389 */
	struct RenderCommand
	{
		unsigned int sortKey;
		keen::RenderObject *pObject;
		void(__cdecl *pExecuteCommandsFunc)(keen::GraphicsCommandWriter *, keen::RenderCommands *, keen::RenderContext *, void *);
	};

	/* 3390 */
	const struct RenderCommands
	{
		keen::RenderCommand *pStart;
		keen::RenderCommand *pEnd;
		unsigned int renderPass;
	};

	/* 3391 */
	struct RenderContext
	{
		keen::RenderEffectSystem *pRenderEffectSystem;
		keen::Camera *pActiveCamera;
		keen::Matrix44 viewProjectionMatrix;
		float activeCameraReciprocFarPlane;
	};

	/* 3392 */
	struct Slice_RenderCommand
	{
		keen::RenderCommand *m_pStart;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3393 */
	struct Array_Slice_RenderCommand
	{
		keen::Slice_RenderCommand *m_pData;
		unsigned int m_size;
	};

	/* 3394 */
	struct RenderCommandList
	{
		keen::Array_Slice_RenderCommand m_buffers;
		keen::RenderCommand *m_pData;
	};

	/* 3395 */
	struct RenderEffectSetupData
	{
		unsigned int materialDataFormatCrc;
		void(__cdecl *pCreateCommandsFunc)(keen::RenderCommandList *, keen::RenderObject *, unsigned int, keen::RenderContext *, void *);
		void *pEffectContextData;
	};

	/* 3396 */
	struct RenderEffectSlot
	{
		unsigned int effectId;
		unsigned int refCount;
		keen::RenderEffectSetupData data;
	};

	/* 3397 */
	struct Array_RenderEffectSlot
	{
		keen::RenderEffectSlot *m_pData;
		unsigned int m_size;
	};

	/* 3398 */
	const struct RenderEffectSystem
	{
		keen::Array_RenderEffectSlot effectSlots;
		unsigned int fallbackRenderEffectId;
		keen::MemoryAllocator *pAllocator;
	};
}