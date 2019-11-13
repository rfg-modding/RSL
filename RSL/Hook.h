#pragma once
#include <minwindef.h>

/*Contains basic info about a hook that minhook needs to create, enable, disable them.*/
class Hook
{
public:
    Hook() = default;
    Hook(LPVOID Target_, LPVOID Detour_, LPVOID* Original_) : Target(Target_), Detour(Detour_), Original(Original_) { }

    LPVOID Target = nullptr;
    LPVOID Detour = nullptr;
    LPVOID* Original = nullptr;
    bool Enabled = false;
};