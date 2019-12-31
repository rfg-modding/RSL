#pragma once

class SunShaftsStateBlock
{
public:
    SunShaftsStateBlock() { }
    ~SunShaftsStateBlock() { }

    bool* Enabled = nullptr;
    bool* SunMask = nullptr;
    bool* UseHalfResSource = nullptr;
    float* SunSize = nullptr;
    float* Scale = nullptr;
    float* BaseLum = nullptr;
    float* LumStepScale = nullptr;
    float* Radius = nullptr;
    float* ColorCurveBase = nullptr;
    float* ColorCurveExp = nullptr;
    float* ColorCurveShift = nullptr;
    float* BlurMultiplier = nullptr;
    float* BlurRho = nullptr;
    bool* CoronaAdaption = nullptr;
};