#include "Hooks.h"

void __cdecl Hooks::ExplosionCreateHook(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position, matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer)
{
    return rfg::ExplosionCreate(ExplosionInfo, Source, Owner, Position, Orientation, Direction, WeaponInfo, FromServer);
}