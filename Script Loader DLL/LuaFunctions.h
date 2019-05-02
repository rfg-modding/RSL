#pragma once
#include "Functions.h"

//These functions are only for use in Lua.
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