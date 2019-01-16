#pragma once

	/* 2457 */
	union __m128i
	{
	  char m128i_i8[16];
	  short m128i_i16[8];
	  int m128i_i32[4];
	  long long m128i_i64[2];
	  char m128i_u8[16];
	  unsigned short m128i_u16[8];
	  unsigned int m128i_u32[4];
	  unsigned long long m128i_u64[2];
	};