#include "Hooks.h"
#include "Application.h"

bool __fastcall Hooks::world_load_territory_hook(World* this_ptr, void* edx)
{
    bool Result = world_load_territory(this_ptr, edx);
    Globals::CanTriggerOnLoadEvent = true;
    return Result;
}