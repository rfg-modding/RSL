#pragma once
#include "Functions.h"

/* This namespace contains functions only used by Lua. It's mainly wrapper functions with 
 * different arguments for convenience sake when calling them through lua.
 */
namespace Lua
{
	extern Player* GetPlayer();
	extern World* GetWorld();
	extern hkpWorld* GetPhysicsWorld();
	extern void LogModuleBase();
    extern vector GetGravity();
    extern void SetGravity(vector& NewGravity);
    extern void SetGravity(float x, float y, float z);
    extern void ResetGravity();
}