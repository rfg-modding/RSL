#pragma once

class ShadowStateBlock
{
public:
    ShadowStateBlock() {}
    ~ShadowStateBlock() {}

    bool* ShadowsEnabled = nullptr;
    bool* CloudShadowEnabled = nullptr;
    float* CloudShadowScale = nullptr;
    float* CloudShadowIntensityScale = nullptr;
    float* CloudShadowIntensityBias = nullptr;
    float* ShadowMapMaxDist = nullptr;
    float* ShadowMapFadePercent = nullptr;
    float* ShadowPercent = nullptr;
    float* DropShadowPercent = nullptr;
    float* TerrainShadowMaxDist = nullptr;
};