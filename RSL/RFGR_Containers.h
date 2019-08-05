#pragma once

struct rl_sampling_vector
{
	float x;
	float y;
	float z;
	float w;
};

struct rl_sampling_offsets
{
	rl_sampling_vector *m_values_p;
	int m_num_samples;
};

template<class T, unsigned int UnkVar>
class et_ptr_offset
{
	int m_offset;
};

namespace rfg
{
	template<class T>
	class base_array
	{
	public:
		const T& operator[](int Index)
		{
			return Elements[Index];
		}
		int Size() { return NumberOfElements; }
		int Length() { return NumberOfElements; }
		int Capacity() { return ArraySize; }

	private:
		void* VirtualFunctionPointer;
		T* Elements;
		int ArraySize;
		int NumberOfElements;
	};

	template <class T, unsigned int InitialSize>
	class farray : public base_array<T>
	{
	public:
		T data[InitialSize];
	};

	template <class T>
	class Array
	{
	public:
		const T& operator[](int Index)
		{
			return Data[Index];
		}
		unsigned int GetSize() { return Size; }
	private:
		T* Data;
		unsigned int Size;
	};

	template <class T>
	class pool_list : base_array<T>
	{
		bool DynamicInit;
		unsigned int MinUsed;
	};

	template <unsigned int T>
	class rl_downscale_sampling_offsets : rl_sampling_offsets
	{
		rl_sampling_vector Values[T];
	};
}

namespace keen
{
    template <class T>
    class SizedArray
    {
        T* Data;
        unsigned int Size;
        unsigned int Capacity;
    };

    struct MemoryBlock
    {
        char* pStart;
        unsigned int size;
    };

    struct BasePoolAllocator //24 bytes
    {
        keen::MemoryBlock m_memoryBlock;
        unsigned int m_capacity;
        unsigned int m_size;
        unsigned int m_elementSize;
        unsigned int m_firstFreeIndex;
    };

    template <class T>
    class PoolAllocator //24 bytes
    {
        keen::BasePoolAllocator m_pool;
    };

    struct GraphicsStateObjectCache
    {
        char m_stateObjects[45];
        //keen::HashMap<unsigned int, keen::GraphicsStateObject *, keen::DefaultHashmapTraits<unsigned int, keen::GraphicsStateObject *> > m_stateObjects;
    };

    template <class T>
    class GraphicsStateObjectPool
    {
        keen::PoolAllocator<char> m_allocator;
        //keen::PoolAllocator<keen::VertexInputBinding> m_allocator;
        keen::GraphicsStateObjectCache m_cache;
        unsigned int m_peakSize;
        unsigned int m_cacheHits;
        unsigned int m_cacheRequests;
    };
}