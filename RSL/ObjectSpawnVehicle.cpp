#include "Hooks.h"

spawn_status_result __cdecl Hooks::object_spawn_vehicle_hook(vehicle_spawn_params& spawn_param)
{
    //Note: I was getting a crash only when x32dbg was attached which was due to a nullptr being pass to this function
    //Not sure if this is something caused by the debugger or also indicative of an issue with the RSL somewhere.
    //For now this fixes the issue. 

    vehicle_spawn_params* ptr = &spawn_param;
    if(!ptr)
    {
        Logger::LogWarning("Null pointer passed to object_spawn_vehicle. Blocking this spawn attempt!\n");
        return SPAWN_STATUS_FAILURE;
    }

#if DEBUG
    Globals::VehicleSpawnCache = spawn_param;
    Logger::Log("Caching vehicle spawn params");
    if(spawn_param.veh_info->name)
        Logger::Log("object_spawn_vehicle called! Vehicle name: {}\n", spawn_param.veh_info->name);
    else
        Logger::Log("object_spawn_vehicle called!\n");
#endif

    return rfg::object_spawn_vehicle(spawn_param);
}