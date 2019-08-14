#pragma once
#include "Timer.h"

class HdrStateBlock
{
public:
    HdrStateBlock() {}
    ~HdrStateBlock() {}

    bool* override = nullptr;
    bool* enable = nullptr;
    bool* bloom_soft = nullptr;
    bool* bloom_alternate = nullptr;
    bool* tone_mapped_bloom = nullptr;
    float* lum_range = nullptr;
    float* lum_offset = nullptr;
    float* hdr_level = nullptr;
    float* iris_rate = nullptr;
    float* luminance_max = nullptr;
    float* luminance_min = nullptr;
    float* luminance_mask_max = nullptr;
    float* brightpass_threshold = nullptr;
    float* brightpass_offset = nullptr;
    bool* use_hdr_level = nullptr;
    bool* bloom_new = nullptr;
    float* eye_adaption_base = nullptr;
    float* eye_adaption_amount = nullptr;
    float* eye_fade_min = nullptr;
    float* eye_fade_max = nullptr;
    float* bloom_amount = nullptr;
    float* bloom_theta = nullptr;
    float* bloom_slope_B = nullptr;
    vector* luminance_conversion = nullptr;
    bool* bloom_super_soft = nullptr;
    bool* eye_override = nullptr;
    float* bloom_slope_A = nullptr;
};

class GraphicsStateWrapper
{
public:
    GraphicsStateWrapper() {};
    ~GraphicsStateWrapper() {};

    void Init();
    [[nodiscard]] bool Ready() const;

    HdrStateBlock HdrState;

private:
    bool ReadyForUse = false;
};

