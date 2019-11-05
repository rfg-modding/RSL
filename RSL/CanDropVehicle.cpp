#include "Hooks.h"
#include "Application.h"

bool __cdecl Hooks::can_drop_vehicle_hook(vehicle_info* v_info, rfg::farray<object*, 256> * delete_object_list, vector* position, matrix* orient, unsigned int ignore_object, bool high_priority)
{
    if(Globals::ForceVehicleDrops)
    {
        return true;
    }
    return rfg::can_drop_vehicle(v_info, delete_object_list, position, orient, ignore_object, high_priority);
}