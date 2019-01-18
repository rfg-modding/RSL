#pragma once
#include "KeenNamespace.h"

namespace keen
{
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

	/* 4592 */
	struct keen::MemoryLayout
	{
		unsigned int memoryBlockCount;
		keen::MemoryBlock memoryBlocks[128];
		keen::MemoryType memoryBlockTypes[128];
		keen::MemoryBlock baseMemoryBlocks[12];
	};

	/* 4593 */
	struct keen::MappedMemoryBlockDefinition
	{
		keen::MemoryBlockDefinition *pBlockDefinition;
		keen::MemoryBlock *pBlock;
	};

	/* 4594 */
	struct __declspec(align(4)) keen::MemorySystem
	{
		keen::MemoryLayoutDefinition layoutDefinition;
		keen::MemoryLayout memoryLayout;
		keen::MappedMemoryBlockDefinition mappedMemoryBlocks[128];
		bool isMemoryBlockLocked[128];
		bool isMemoryTrackerInitialized;
	};
}
