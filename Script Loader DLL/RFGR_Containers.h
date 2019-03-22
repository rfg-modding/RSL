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
		int Capacity() { return ArraySize; }

	private:
		void* VirtualFunctionPointer;
		T* Elements;
		int ArraySize;
		int NumberOfElements;
	};

	template <class T, unsigned int InitialSize>
	class farray : base_array<T>
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

bool m_init_dynamic;
unsigned int m_min_used;