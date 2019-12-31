#pragma once

class MiscStateBlock
{
public:
    MiscStateBlock() {}
    ~MiscStateBlock() {}

    bool* FxaaEnabled = nullptr;
    float* DecalDepthBias = nullptr;
    bool* AlphaDistEnabled = nullptr;
    float* AlphaDistStart = nullptr;
    float* AlphaDistEnd = nullptr;
    float* DistortionScale = nullptr;
    float* DistortionBlurScale = nullptr;
    float* DistortionDepthBias = nullptr;
};