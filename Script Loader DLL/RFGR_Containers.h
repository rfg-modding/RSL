#pragma once

namespace rfg
{
	template<class T>
	class base_array
	{
	public:
		const T& operator[](int Index)
		{
			if (Index < NumberOfElements)
			{
				return Elements[Index];
			}
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
		T* data[InitialSize];
	};
}