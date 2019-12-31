#pragma once

class LightingStateBlock
{
public:
    LightingStateBlock() {}
    ~LightingStateBlock() {}

    bool* SubstanceDiffuseScaleEnabled = nullptr;
    float* CoronaAdaptionRate = nullptr;
    float* SubstanceSpecAlphaScale = nullptr;
    float* SubstanceSpecPowerScale = nullptr;
    float* SubstanceFresnelAlphaScale = nullptr;
    float* SubstanceFresnelPowerScale = nullptr;
    float* GlassFresnelBias = nullptr;
    float* GlassFresnelPower = nullptr;
    bool* GlassDirtEnabled = nullptr;
    bool* GlassReflectionEnabled = nullptr;
    bool* IndirectLightEnabled = nullptr;
    bool* AmbientSpecularEnabled = nullptr;
    float* IndirectLightScale = nullptr;
    float* IndirectLightAmount = nullptr;
    float* MainLightColorScale = nullptr;
    float* AmbientColorScale = nullptr;
    float* BackAmbientColorScale = nullptr;
    float* AmbientSpecularScale = nullptr;
    bool* EnabledHemisphericAmbient = nullptr;
};