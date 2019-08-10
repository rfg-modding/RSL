#include "Hooks.h"
#include "Application.h"

spawn_status_result __cdecl Hooks::object_spawn_vehicle_hook(vehicle_spawn_params* spawn_param)
{
    ////Todo: Print custom params address (with adn without modulebase) as hex and compare with x32dbg values
    //std::cout << "\t[Hook] ModuleBase, decimal: " << Globals::ModuleBase << "\n";
    //std::cout << "\t[Hook] ModuleBase, hex: " << std::hex << Globals::ModuleBase << "\n";
    //std::cout << "\t[Hook] &CustomVehicleSpawnParams, decimal: " << &spawn_param << "\n";
    //std::cout << "\t[Hook] &CustomVehicleSpawnParams, hex: " << std::hex << &spawn_param << "\n";
    //std::cout << "\t[Hook] ModuleBase + &CustomVehicleSpawnParams, decimal: " << Globals::ModuleBase + (DWORD)&spawn_param << "\n";
    //std::cout << "\t[Hook] ModuleBase + &CustomVehicleSpawnParams, hex: " << std::hex << Globals::ModuleBase + (DWORD)&spawn_param << "\n";

    //Note: I was getting a crash only when x32dbg was attached which was due to a nullptr being pass to this function
    //Not sure if this is something caused by the debugger or also indicative of an issue with the RSL somewhere.
    //For now this fixes the issue. 
    if(!spawn_param)
    {
        Logger::LogWarning("Null pointer passed to object_spawn_vehicle. Blocking this spawn attempt!\n");
        return SPAWN_STATUS_FAILURE;
    }

    return object_spawn_vehicle(spawn_param);
}