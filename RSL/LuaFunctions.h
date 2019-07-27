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
    extern Object* GetObjectByName(std::string Name);
    extern Object* GetObjectByHandle(uint Handle);

    extern explosion_info* GetExplosionInfo(std::string Name);

    extern std::vector<fmt::basic_format_arg<fmt::format_context>> GenerateFmtListFromSolVariadicArgs(const sol::variadic_args& Args);
    //Todo: Profile all these lua logging funcs because they're probably slow as shit the way this is being done.
    extern void Log(std::string Fmt, sol::variadic_args Args);
    extern void LogNone(std::string Fmt, sol::variadic_args Args);
    extern void LogInfo(std::string Fmt, sol::variadic_args Args);
    extern void LogWarning(std::string Fmt, sol::variadic_args Args);
    extern void LogError(std::string Fmt, sol::variadic_args Args);
    extern void LogFatalError(std::string Fmt, sol::variadic_args Args);
    extern void LogLua(std::string Fmt, sol::variadic_args Args);
    extern void LogJson(std::string Fmt, sol::variadic_args Args);

    extern uint RfgStringHashWrapper(std::string Key);
}