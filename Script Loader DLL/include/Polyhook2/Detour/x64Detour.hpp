//
// Created by steve on 7/4/17.
//

#ifndef POLYHOOK_2_X64DETOUR_HPP
#define POLYHOOK_2_X64DETOUR_HPP

#include <sstream>
#include <algorithm>
#include <functional>
using namespace std::placeholders;

#include "Polyhook2/Detour/ADetour.hpp"
#include "Polyhook2/Enums.hpp"
#include "Polyhook2/Instruction.hpp"
#include "Polyhook2/ADisassembler.hpp"
#include "Polyhook2/ErrorLog.hpp"
#include "Polyhook2/MemProtector.hpp"

namespace PLH {

class x64Detour : public Detour {
public:
	x64Detour(const uint64_t fnAddress, const uint64_t fnCallback, uint64_t* userTrampVar, PLH::ADisassembler& dis);

	x64Detour(const char* fnAddress, const char* fnCallback, uint64_t* userTrampVar, PLH::ADisassembler& dis);
	virtual ~x64Detour() = default;
	virtual bool hook() override;

	Mode getArchType() const;

	uint8_t getMinJmpSize() const;

	uint8_t getPrefJmpSize() const;
private:
	bool makeTrampoline(insts_t& prologue, insts_t& trampolineOut);
};
}
#endif //POLYHOOK_2_X64DETOUR_HPP
