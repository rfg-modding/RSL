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
}