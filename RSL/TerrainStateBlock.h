#pragma once

class TerrainStateBlock
{
public:
    TerrainStateBlock() {}
    ~TerrainStateBlock() {}

    float* DetailMapTiling = nullptr;
    float* DetailMapScale = nullptr;
    float* DetailMapBias = nullptr;
    float* DetailMapBlend = nullptr;
    bool* DetailMapEnable = nullptr;
    bool* SpecularEnable = nullptr;
    bool* RenderAlphaSkirts = nullptr;
    int* AnisotropyLevel = nullptr;
    float* FadeStart = nullptr;
    float* FadeEnd = nullptr;
    bool* MedLod = nullptr;
    bool* UseNewRenderer = nullptr;
};