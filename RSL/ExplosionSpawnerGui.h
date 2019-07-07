#pragma once
#include "BaseGui.h"

class ExplosionSpawnerGui : public BaseGui
{
public:
    ExplosionSpawnerGui(bool* OpenState_, std::string Title_);
    ~ExplosionSpawnerGui() = default;

    void Draw() override;

    explosion_info CustomExplosionInfo;
    bool MiddleMouseBoomActive = false;
    int MiddleMouseExplosionsPerSecond = 20;

private:
    bool DrawnOnce = false;
};
