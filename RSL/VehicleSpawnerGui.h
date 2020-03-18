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

    void DrawProjItemFlagsGui();

    weapon_info* projWeaponInfo = nullptr;
    item_info* projItemInfo = nullptr;
    vector projPos = { 0.0 };
    matrix projOrient = { 0.0 };
    vector projVelocity = { 10.0, 0.0, 0.0 };
    vector projTarget = { 0.0 };
    uint projCreateId = 0xFFFFFFFF;
    uint projOwnerHandle = 0xFFFFFFFF;
    obj_item_flags projItemFlags;
    //create_id, owner_handle, obj_item_flags
};
