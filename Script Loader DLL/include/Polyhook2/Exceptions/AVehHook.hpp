#ifndef POLYHOOK_2_0_VEHHOOK_HPP
#define POLYHOOK_2_0_VEHHOOK_HPP

#include <cassert>
#include <map>

#include "Polyhook2/MemProtector.hpp"
#include "Polyhook2/ErrorLog.hpp"
#include "Polyhook2/IHook.hpp"
#include "Polyhook2/Enums.hpp"

namespace PLH {

#ifdef _WIN64
#define XIP Rip
#else
#define XIP Eip
#endif // _WIN64

class RefCounter {
public:
	uint16_t m_count = 0;
};

class AVehHook : public IHook {
public:
	AVehHook();
	virtual ~AVehHook();

	virtual HookType getType() const {
		return HookType::VEHHOOK;
	}
protected:
	// May not allocate or acquire synchonization objects in this
	virtual LONG OnException(EXCEPTION_POINTERS* ExceptionInfo) = 0;

	static RefCounter m_refCount;
	static void* m_hHandler;
	static std::map<uint64_t, AVehHook*> m_impls;
	static LONG CALLBACK Handler(EXCEPTION_POINTERS* ExceptionInfo);
};
}

#endif