#include "Hooks.h"

int __cdecl Hooks::rfgl_find_and_delete_object_mover_hook(int objects_to_delete, bool find_gm)
{
    if(Globals::DisableDebrisDeletion)
    {
        return 32;
    }
    if(Globals::UseFindGmOverride)
    {
        return rfgl_find_and_delete_object_mover(objects_to_delete, Globals::FindGmOverride);
    }
    return rfgl_find_and_delete_object_mover(objects_to_delete, find_gm);
}


int __cdecl Hooks::rfgl_find_and_delete_debris_object_hook(int objects_to_delete)
{
    if (Globals::DisableDebrisDeletion)
    {
        return 28;
    }
    return rfgl_find_and_delete_debris_object(objects_to_delete);
}