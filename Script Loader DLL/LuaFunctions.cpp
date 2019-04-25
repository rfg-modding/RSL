#include "LuaFunctions.h"

namespace Lua
{
	Player* GetPlayer()
	{
		return Globals::PlayerPtr;
	}

	World* GetWorld()
	{
		return Globals::RfgWorldPtr;
	}

	hkpWorld* GetPhysicsWorld()
	{
		return Globals::hkpWorldPtr;
	}

	void LogModuleBase()
	{
		Logger::Log(std::string("Module base: " + std::to_string(reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)))), LogInfo);
	}
}
