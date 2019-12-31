#include "GraphicsStateWrapper.h"

void GraphicsStateWrapper::Init()
{
    //Set HDR state pointers
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
    
    //Set shadow state pointers
    ShadowState.ShadowsEnabled = OffsetPtr<bool*>(0x10FA47F);
    ShadowState.CloudShadowEnabled = OffsetPtr<bool*>(0x10FA47E);
    ShadowState.CloudShadowScale = OffsetPtr<float*>(0x10FA480);
    ShadowState.CloudShadowIntensityScale = OffsetPtr<float*>(0x10FA484);
    ShadowState.CloudShadowIntensityBias = OffsetPtr<float*>(0x10FA488);
    ShadowState.ShadowMapMaxDist = OffsetPtr<float*>(0x10FA510);
    ShadowState.ShadowMapFadePercent = OffsetPtr<float*>(0x10FA514);
    ShadowState.ShadowPercent = OffsetPtr<float*>(0x10FA540);
    ShadowState.DropShadowPercent = OffsetPtr<float*>(0x10FA548);
    ShadowState.TerrainShadowMaxDist = OffsetPtr<float*>(0x10FA550);

    //Set SSAO state pointers
    SsaoState.Enabled = OffsetPtr<bool*>(0x10FA610);
    SsaoState.Bias = OffsetPtr<float*>(0x10FA5FC);
    SsaoState.Clamp = OffsetPtr<float*>(0x10FA600);
    SsaoState.Epsilon = OffsetPtr<float*>(0x10FA614);
    SsaoState.Falloff = OffsetPtr<float*>(0x10FA618);
    SsaoState.Intensity = OffsetPtr<float*>(0x10FA61C);
    SsaoState.Radius = OffsetPtr<float*>(0x10FA624);
    SsaoState.DepthFadeRange = OffsetPtr<float*>(0x10FA604);
    SsaoState.DepthThreshold = OffsetPtr<float*>(0x10FA608);
    SsaoState.EdgeSharpness = OffsetPtr<float*>(0x10FA60C);
    SsaoState.ImagePlanePixelsPerMeterFactor = OffsetPtr<float*>(0x10FA620);

    //Set terrain state pointers
    TerrainState.DetailMapTiling = OffsetPtr<float*>(0x110A5EC);
    TerrainState.DetailMapScale = OffsetPtr<float*>(0x110A5F0);
    TerrainState.DetailMapBias = OffsetPtr<float*>(0x110A5F4);
    TerrainState.DetailMapBlend = OffsetPtr<float*>(0x110A5F8);
    TerrainState.DetailMapEnable = OffsetPtr<bool*>(0x110A5FC);
    TerrainState.SpecularEnable = OffsetPtr<bool*>(0x110A5FD);
    TerrainState.RenderAlphaSkirts = OffsetPtr<bool*>(0x110A5FE);
    TerrainState.AnisotropyLevel = OffsetPtr<int*>(0x110A600);
    TerrainState.FadeStart = OffsetPtr<float*>(0x110A604);
    TerrainState.FadeEnd = OffsetPtr<float*>(0x110A608);
    TerrainState.MedLod = OffsetPtr<bool*>(0x10FA2DE);
    TerrainState.UseNewRenderer = OffsetPtr<bool*>(0x10FA613);

    //Set DOF state pointers
    DofState.FocusStartA = OffsetPtr<float*>(0x10FA124);
    DofState.FocusStartB = OffsetPtr<float*>(0x10FA128);
    DofState.FocusEndA = OffsetPtr<float*>(0x10FA12C);
    DofState.FocusEndB = OffsetPtr<float*>(0x10FA130);

    //Set sun shaft state pointers
    SunShaftsState.Enabled = OffsetPtr<bool*>(0x10FA288);
    SunShaftsState.SunMask = OffsetPtr<bool*>(0x10FA289);
    SunShaftsState.UseHalfResSource = OffsetPtr<bool*>(0x10FA28A);
    SunShaftsState.SunSize = OffsetPtr<float*>(0x10FA28C);
    SunShaftsState.Scale = OffsetPtr<float*>(0x10FA290);
    SunShaftsState.BaseLum = OffsetPtr<float*>(0x10FA294);
    SunShaftsState.LumStepScale = OffsetPtr<float*>(0x10FA298);
    SunShaftsState.Radius = OffsetPtr<float*>(0x10FA29C);
    SunShaftsState.ColorCurveBase = OffsetPtr<float*>(0x10FA2A0);
    SunShaftsState.ColorCurveExp = OffsetPtr<float*>(0x10FA2A4);
    SunShaftsState.ColorCurveShift = OffsetPtr<float*>(0x10FA2A8);
    SunShaftsState.BlurMultiplier = OffsetPtr<float*>(0x10FA2AC);
    SunShaftsState.BlurRho = OffsetPtr<float*>(0x10FA2B0);
    SunShaftsState.CoronaAdaption = OffsetPtr<bool*>(0x10FA301);

    //Set lighting state pointers
    LightingState.SubstanceDiffuseScaleEnabled = OffsetPtr<bool*>(0x10FA303);
    LightingState.CoronaAdaptionRate = OffsetPtr<float*>(0x10FA310);
    LightingState.SubstanceSpecAlphaScale = OffsetPtr<float*>(0x10FA3A4);
    LightingState.SubstanceSpecPowerScale = OffsetPtr<float*>(0x10FA3A8);
    LightingState.SubstanceFresnelAlphaScale = OffsetPtr<float*>(0x10FA3AC);
    LightingState.SubstanceFresnelPowerScale = OffsetPtr<float*>(0x10FA3B0);
    LightingState.GlassFresnelBias = OffsetPtr<float*>(0x10FA3B4);
    LightingState.GlassFresnelPower = OffsetPtr<float*>(0x10FA3B8);
    LightingState.GlassDirtEnabled = OffsetPtr<bool*>(0x10FA3BC);
    LightingState.GlassReflectionEnabled = OffsetPtr<bool*>(0x10FA3BD);
    LightingState.IndirectLightEnabled = OffsetPtr<bool*>(0x10FA3BE);
    LightingState.AmbientSpecularEnabled = OffsetPtr<bool*>(0x10FA3BF);
    LightingState.IndirectLightScale = OffsetPtr<float*>(0x10FA3C0);
    LightingState.IndirectLightAmount = OffsetPtr<float*>(0x10FA3C4);
    LightingState.MainLightColorScale = OffsetPtr<float*>(0x10FA3C8);
    LightingState.AmbientColorScale = OffsetPtr<float*>(0x10FA3CC);
    LightingState.BackAmbientColorScale = OffsetPtr<float*>(0x10FA3D0);
    LightingState.AmbientSpecularScale = OffsetPtr<float*>(0x10FA3D4);
    LightingState.EnabledHemisphericAmbient = OffsetPtr<bool*>(0x10FA3D8);

    //Set misc state pointers. None of these have enough similar values to make separate classes worthwhile
    MiscState.FxaaEnabled = OffsetPtr<bool*>(0x10FA47C);
    MiscState.DecalDepthBias = OffsetPtr<float*>(0x10FA120);
    MiscState.AlphaDistEnabled = OffsetPtr<bool*>(0x10FA103);
    MiscState.AlphaDistStart = OffsetPtr<float*>(0x10FA474);
    MiscState.AlphaDistEnd = OffsetPtr<float*>(0x10FA478);
    MiscState.DistortionScale = OffsetPtr<float*>(0x10FA138);
    MiscState.DistortionBlurScale = OffsetPtr<float*>(0x10FA13C);
    MiscState.DistortionDepthBias = OffsetPtr<float*>(0x10FA30C);

    ReadyForUse = true;
}

bool GraphicsStateWrapper::Ready() const
{
    return ReadyForUse;
}