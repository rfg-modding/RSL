#pragma once

#include "FunctionManager.h"

//#include <cstddef>
//#include <cstdint>
//#include <climits>
//#include <type_traits>

namespace itsy_bitsy 
{

	template <std::size_t sz, typename C = void>
	struct bit_type {
		typedef uint64_t type;
	};

	template <std::size_t sz>
	struct bit_type<sz, std::enable_if_t<(sz <= 1)>> {
		typedef bool type;
	};

	template <std::size_t sz>
	struct bit_type<sz, std::enable_if_t<(sz > 2 && sz <= 16)>> {
		typedef uint16_t type;
	};

	template <std::size_t sz>
	struct bit_type<sz, std::enable_if_t<(sz > 16 && sz <= 32)>> {
		typedef uint32_t type;
	};

	template <std::size_t sz>
	struct bit_type<sz, std::enable_if_t<(sz > 32 && sz <= 64)>> {
		typedef uint64_t type;
	};

	template <std::size_t sz>
	using bit_type_t = typename bit_type<sz>::type;

	template <typename T, typename V>
	bool vcxx_warning_crap(std::true_type, V val) {
		return val != 0;
	}

	template <typename T, typename V>
	T vcxx_warning_crap(std::false_type, V val) {
		return static_cast<T>(val);
	}

	template <typename T, typename V>
	auto vcxx_warning_crap(V val) {
		return vcxx_warning_crap<T>(std::is_same<bool, T>(), val);
	}

	template <typename Base, std::size_t bit_target = 0x0, std::size_t size = 0x1>
	void write(Base& b, bit_type_t<size> bits) {
		typedef bit_type_t<sizeof(Base) * CHAR_BIT> aligned_type;
		static const std::size_t aligned_type_bit_size = sizeof(aligned_type) * CHAR_BIT;
		static_assert(sizeof(Base) * CHAR_BIT >= (bit_target + size), "bit offset and size are too large for the desired structure.");
		static_assert((bit_target % aligned_type_bit_size) <= ((bit_target + size) % aligned_type_bit_size), "bit offset and size cross beyond largest integral constant boundary.");

		const std::size_t aligned_target = (bit_target + size) / aligned_type_bit_size;
		const aligned_type bits_left = static_cast<aligned_type>(bit_target - aligned_target);
		const aligned_type shifted_mask = ((static_cast<aligned_type>(1) << size) - 1) << bits_left;
		const aligned_type compl_shifted_mask = ~shifted_mask;
		// Jump by native size of a pointer to target
		// then OR the bits
		aligned_type* jumper = static_cast<aligned_type*>(static_cast<void*>(&b));
		jumper += aligned_target;
		aligned_type& aligned = *jumper;
		aligned &= compl_shifted_mask;
		aligned |= (static_cast<aligned_type>(bits) << bits_left);
	}

	template <typename Base, std::size_t bit_target = 0x0, std::size_t size = 0x1>
	bit_type_t<size> read(Base& b) {
		typedef bit_type_t<sizeof(Base) * CHAR_BIT> aligned_type;
		typedef bit_type_t<size> field_type;
		static const std::size_t aligned_type_bit_size = sizeof(aligned_type) * CHAR_BIT;
		static_assert(sizeof(Base) * CHAR_BIT >= (bit_target + size), "bit offset and size are too large for the desired structure.");
		static_assert((bit_target % aligned_type_bit_size) <= ((bit_target + size) % aligned_type_bit_size), "bit offset and size cross beyond largest integral constant boundary.");

		const std::size_t aligned_target = (bit_target + size) / aligned_type_bit_size;
		const aligned_type bits_left = static_cast<aligned_type>(bit_target - aligned_target);
		const aligned_type mask = (static_cast<aligned_type>(1) << size) - 1;
		// Jump by native size of a pointer to target
		// then OR the bits
		aligned_type* jumper = static_cast<aligned_type*>(static_cast<void*>(&b));
		jumper += aligned_target;
		const aligned_type& aligned = *jumper;
		aligned_type field_bits = (aligned >> bits_left) & mask;
		field_type bits = vcxx_warning_crap<field_type>(field_bits);
		return bits;
	}
}