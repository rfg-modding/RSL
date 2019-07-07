#pragma once
#include "BaseGui.h"

class VehicleSpawnerGui : public BaseGui
{
public:
    VehicleSpawnerGui(bool* OpenState_, std::string Title_);
    ~VehicleSpawnerGui() = default;

    void Draw() override;

    vehicle_info CustomVehicleInfo;
    vehicle_spawn_params CustomVehicleSpawnParams;
    //bool MiddleMouseBoomActive = false;
    //int VehicleSpawnsPerSecond = 20;

private:
    bool DrawnOnce = false;
};
