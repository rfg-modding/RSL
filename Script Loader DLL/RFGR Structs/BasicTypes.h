#pragma once

	/* 2457 */
	/*union __m128i
	{
	  char m128i_i8[16];
	  short m128i_i16[8];
	  int m128i_i32[4];
	  long long m128i_i64[2];
	  char m128i_u8[16];
	  unsigned short m128i_u16[8];
	  unsigned int m128i_u32[4];
	  unsigned long long m128i_u64[2];
	};*/

	/* 2327 */
	/*union __m128 //144
	{
		float m128_f32[4]; //16
		unsigned __int64 m128_u64[2]; //16
		char m128_i8[16]; //16
		__int16 m128_i16[8]; //16
		int m128_i32[4]; //16
		__int64 m128_i64[2]; //16
		char m128_u8[16]; //16
		unsigned __int16 m128_u16[8]; //16
		unsigned int m128_u32[4]; //16
	};*/

	/* 3241 */
	struct _XMFLOAT2
	{
		float x;
		float y;
	};

	namespace keen
	{
		/* 4282 */
		struct SizedArray_unsigned_char
		{
			char *m_pData;
			unsigned int m_size;
			unsigned int m_capacity;
		};

		struct base_array_unsigned_char_Vtbl;
		/* 6419 */
		struct base_array_unsigned_char
		{
			base_array_unsigned_char_Vtbl* vfptr;
			char *elt;
			int array_size;
			int num;
		};

		/* 6420 */
		struct base_array_unsigned_char_Vtbl
		{
			void *(__thiscall *__vecDelDtor)(base_array_unsigned_char *This, unsigned int);
		};

		/* 3068 */
		struct Array_unsigned_char
		{
			char *m_pData;
			unsigned int m_size;
		};

		/* 3363 */
		struct Array_unsigned_char_pointer
		{
			char **m_pData;
			unsigned int m_size;
		};

		/* 2338 */
		struct float1
		{
			float x;
		};

		/* 2340 */
		struct float2
		{
			float x;
			float y;
		};

		/* 2334 */
		struct float3
		{
			float x;
			float y;
			float z;
		};

		/* 2335 */
		struct float4
		{
			float x;
			float y;
			float z;
			float w;
		};

		/* 2341 */
		union __m64
		{
			unsigned __int64 m64_u64;
			float m64_f32[2];
			char m64_i8[8];
			__int16 m64_i16[4];
			int m64_i32[2];
			__int64 m64_i64;
			char m64_u8[8];
			unsigned __int16 m64_u16[4];
			unsigned int m64_u32[2];
		};


		/* 2463 */
		struct Vector2 : keen::float2
		{

		};

		/* 2462 */
		struct Vector3 : keen::float3
		{

		};

		/* 2480 */
		struct Vector4 : keen::float4
		{

		};

		/* 2464 */
		struct Matrix33
		{
			keen::Vector3 x;
			keen::Vector3 y;
			keen::Vector3 z;
		};

		/* 2465 */
		struct Matrix43
		{
			keen::Matrix33 rot;
			keen::Vector3 pos;
		};

		/* 2489 */
		struct Matrix44
		{
			keen::Vector4 x;
			keen::Vector4 y;
			keen::Vector4 z;
			keen::Vector4 w;
		};
	};