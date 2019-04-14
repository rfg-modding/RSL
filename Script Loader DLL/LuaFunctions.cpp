#include "LuaFunctions.h"

namespace Lua
{
	Player* GetPlayer()
	{
		return GlobalPlayerPtr;
	}

	World* GetWorld()
	{
		return GlobalRfgWorldPtr;
	}

	hkpWorld* GetPhysicsWorld()
	{
		return GlobalhkpWorldPtr;
	}

	void LogModuleBase()
	{
		Logger::Log(std::string("Module base: " + std::to_string((uintptr_t)GetModuleHandle(NULL))), LogInfo);
	}
}
