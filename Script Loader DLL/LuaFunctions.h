#pragma once
#include "Functions.h"

//These functions are only for use in Lua.
namespace Lua
{
	extern Player* GetPlayer();
	extern World* GetWorld();
	extern hkpWorld* GetPhysicsWorld();
	extern void LogModuleBase();
}