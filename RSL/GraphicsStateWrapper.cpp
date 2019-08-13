#include "GraphicsStateWrapper.h"

void GraphicsStateWrapper::Init()
{
    //Set HDR state values
    HdrState.override = OffsetPtr<bool*>(0x10FA28B);
    HdrState.enable = OffsetPtr<bool*>(0x10FA2B4);
    HdrState.bloom_soft = OffsetPtr<bool*>(0x10FA2B5);
    HdrState.bloom_alternate = OffsetPtr<bool*>(0x10FA2B6);
    HdrState.tone_mapped_bloom = OffsetPtr<bool*>(0x10FA2B7);
    HdrState.lum_range = OffsetPtr<float*>(0x10FA2B8);
    HdrState.lum_offset = OffsetPtr<float*>(0x10FA2BC);
    HdrState.hdr_level = OffsetPtr<float*>(0x10FA2C0);
    HdrState.iris_rate = OffsetPtr<float*>(0x10FA2C4);
    HdrState.luminance_max = OffsetPtr<float*>(0x10FA2C8);
    HdrState.luminance_min = OffsetPtr<float*>(0x10FA2CC);
    HdrState.luminance_mask_max = OffsetPtr<float*>(0x10FA2D0);
    HdrState.brightpass_threshold = OffsetPtr<float*>(0x10FA2D4);
    HdrState.brightpass_offset = OffsetPtr<float*>(0x10FA2D8);
    HdrState.use_hdr_level = OffsetPtr<bool*>(0x10FA2DC);
    HdrState.bloom_new = OffsetPtr<bool*>(0x10FA2DD);
    HdrState.eye_adaption_base = OffsetPtr<float*>(0x10FA2E0);
    HdrState.eye_adaption_amount = OffsetPtr<float*>(0x10FA2E4);
    HdrState.eye_fade_min = OffsetPtr<float*>(0x10FA2E8);
    HdrState.eye_fade_max = OffsetPtr<float*>(0x10FA2EC);
    HdrState.bloom_amount = OffsetPtr<float*>(0x10FA2F0);
    HdrState.bloom_theta = OffsetPtr<float*>(0x10FA2F4);
    HdrState.bloom_slope_B = OffsetPtr<float*>(0x10FA2F8);
    HdrState.luminance_conversion = OffsetPtr<vector*>(0x1114B98);
    HdrState.bloom_super_soft = OffsetPtr<bool*>(0x177BCA6);
    HdrState.eye_override = OffsetPtr<bool*>(0x177BCA7);
    HdrState.bloom_slope_A = OffsetPtr<float*>(0x177BCC4);

    ReadyForUse = true;
}

bool GraphicsStateWrapper::Ready() const
{
    return ReadyForUse;
}
