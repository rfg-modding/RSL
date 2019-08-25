#pragma once
#include "BaseGui.h"

class VehicleSpawnerGui : public BaseGui
{
public:
    VehicleSpawnerGui(std::string Title_);
    ~VehicleSpawnerGui() = default;

    void Draw() override;

    vehicle_spawn_params CustomVehicleSpawnParams;

private:
    bool DrawnOnce = false;
};
