#include "Hooks.h"
#include "Application.h"

void __fastcall Hooks::ApplicationUpdateTimeHook(void* This, void* edx, float TimeStep)
{
    return ApplicationUpdateTime(This, edx, TimeStep);
}