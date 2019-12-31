#pragma once

class SsaoStateBlock
{
public:
    SsaoStateBlock() {}
    ~SsaoStateBlock() {}

    bool* Enabled = nullptr;
    float* Bias = nullptr;
    float* Clamp = nullptr;
    float* Epsilon = nullptr;
    float* Falloff = nullptr;
    float* Intensity = nullptr;
    float* Radius = nullptr;
    float* DepthFadeRange = nullptr;
    float* DepthThreshold = nullptr;
    float* EdgeSharpness = nullptr;
    float* ImagePlanePixelsPerMeterFactor = nullptr;
};