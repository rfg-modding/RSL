#include "Hooks.h"
#include "Application.h"

void __fastcall Hooks::ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData)
{
    return ObjectUpdatePosAndOrient(ObjectPtr, edx, UpdatedPosition, UpdatedOrientation, SetHavokData);
}