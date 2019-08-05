#include "Hooks.h"
#include "Application.h"

//Note: Currently disabled, not sure why. It might have been causing a crash. Would be useful for logging vehicle spawns if re-enabled.

//spawn_status_result ObjectSpawnVehicleHook(vehicle_spawn_params* spawn_param)
//{
//    //Todo: Print custom params address (with adn without modulebase) as hex and compare with x32dbg values
//    std::cout << "\t[Hook] ModuleBase, decimal: " << Globals::ModuleBase << "\n";
//    std::cout << "\t[Hook] ModuleBase, hex: " << std::hex << Globals::ModuleBase << "\n";
//    std::cout << "\t[Hook] &CustomVehicleSpawnParams, decimal: " << &spawn_param << "\n";
//    std::cout << "\t[Hook] &CustomVehicleSpawnParams, hex: " << std::hex << &spawn_param << "\n";
//    std::cout << "\t[Hook] ModuleBase + &CustomVehicleSpawnParams, decimal: " << Globals::ModuleBase + (DWORD)&spawn_param << "\n";
//    std::cout << "\t[Hook] ModuleBase + &CustomVehicleSpawnParams, hex: " << std::hex << Globals::ModuleBase + (DWORD)&spawn_param << "\n";
//
//    return ObjectSpawnVehicle(spawn_param);
//}