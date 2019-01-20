#pragma once
#include "KeenNamespace.h"

namespace keen
{
	/* 49 */
	enum MemoryType
	{
		MemoryType_MainMemory = 0x0,
		MemoryType_Ps3_RsxLocal = 0x1,
		MemoryType_Ps3_RsxMain = 0x2,
		MemoryType_Xb360_Physical = 0x3,
		MemoryType_Xb360_Physical_WriteCombined = 0x4,
		MemoryType_WiiU_Mem1 = 0x5,
		MemoryType_Garlic = 0x6,
		MemoryType_Onion = 0x7,
		MemoryType_PsV_VRAM = 0x8,
		MemoryType_GPU_Mapped = 0x9,
		MemoryType_XBone_APU = 0xA,
		MemoryType_Switch_AudioBuffers = 0xB,
		MemoryType_Count = 0xC,
	};

	/* 2374 */
	struct MemoryBlock
	{
		char *pStart;
		unsigned int size;
	};

	/* 2415 */
	struct BasePoolAllocator
	{
		keen::MemoryBlock m_memoryBlock;
		unsigned int m_capacity;
		unsigned int m_size;
		unsigned int m_elementSize;
		unsigned int m_firstFreeIndex;
	};

	/* 2342 */
	struct MemoryBlockDefinition
	{
		unsigned int size;
		unsigned int alignment;
		unsigned __int16 type;
		unsigned __int16 flags;
		unsigned int initialProtectionMask;
		const char *pDescription;
	};

	/* 2343 */
	struct MemoryLayoutDefinition
	{
		keen::MemoryBlockDefinition *pBlockDefinitions;
		unsigned int blockCount;
	};

	/* 4592 */
	struct MemoryLayout
	{
		unsigned int memoryBlockCount;
		keen::MemoryBlock memoryBlocks[128];
		keen::MemoryType memoryBlockTypes[128];
		keen::MemoryBlock baseMemoryBlocks[12];
	};

	/* 4593 */
	struct MappedMemoryBlockDefinition
	{
		keen::MemoryBlockDefinition *pBlockDefinition;
		keen::MemoryBlock *pBlock;
	};

	/* 4594 */
	struct __declspec(align(4)) MemorySystem
	{
		keen::MemoryLayoutDefinition layoutDefinition;
		keen::MemoryLayout memoryLayout;
		keen::MappedMemoryBlockDefinition mappedMemoryBlocks[128];
		bool isMemoryBlockLocked[128];
		bool isMemoryTrackerInitialized;
	};
}
