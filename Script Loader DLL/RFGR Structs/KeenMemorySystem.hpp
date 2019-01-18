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
}
