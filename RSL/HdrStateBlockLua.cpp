#include "HdrStateBlockLua.h"
#include "Globals.h"
#include "GraphicsStateWrapper.h"

void Lua::BindHdrStateBlock(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

	auto Utype = RfgTable.create_simple_usertype<HdrStateBlock>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Override", sol::property(
			[](HdrStateBlock& self) { return *self.override; }, 
			[](HdrStateBlock& self, bool value) { *self.override = value; }
	));
	Utype.set("Enable", sol::property(
		[](HdrStateBlock& self) { return *self.enable; }, 
		[](HdrStateBlock& self, bool value) { *self.enable = value; }
	));
	Utype.set("BloomSoft", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_soft; }, 
		[](HdrStateBlock& self, bool value) { *self.bloom_soft = value; }
	));
	Utype.set("BloomAlternate", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_alternate; }, 
		[](HdrStateBlock& self, bool value) { *self.bloom_alternate = value; }
	));
	Utype.set("ToneMappedBloom", sol::property(
		[](HdrStateBlock& self) { return *self.tone_mapped_bloom; }, 
		[](HdrStateBlock& self, bool value) { *self.tone_mapped_bloom = value; }
	));
	Utype.set("LuminanceRange", sol::property(
		[](HdrStateBlock& self) { return *self.lum_range; }, 
		[](HdrStateBlock& self, float value) { *self.lum_range = value; }
	));
	Utype.set("LuminanceOffset", sol::property(
		[](HdrStateBlock& self) { return *self.lum_offset; },
		[](HdrStateBlock& self, float value) { *self.lum_offset = value; }
	));
	Utype.set("HdrLevel", sol::property(
		[](HdrStateBlock& self) { return *self.hdr_level; },
		[](HdrStateBlock& self, float value) { *self.hdr_level = value; }
	));
	Utype.set("IrisRate", sol::property(
		[](HdrStateBlock& self) { return *self.iris_rate; },
		[](HdrStateBlock& self, float value) { *self.iris_rate = value; }
	));
	Utype.set("LuminanceMin", sol::property(
		[](HdrStateBlock& self) { return *self.luminance_min; },
		[](HdrStateBlock& self, float value) { *self.luminance_min = value; }
	));
	Utype.set("LuminanceMax", sol::property(
		[](HdrStateBlock& self) { return *self.luminance_max; },
		[](HdrStateBlock& self, float value) { *self.luminance_max = value; }
	));
	Utype.set("LuminanceMaskMax", sol::property(
		[](HdrStateBlock& self) { return *self.luminance_mask_max; },
		[](HdrStateBlock& self, float value) { *self.luminance_mask_max = value; }
	));
	Utype.set("BrightpassThreshold", sol::property(
		[](HdrStateBlock& self) { return *self.brightpass_threshold; },
		[](HdrStateBlock& self, float value) { *self.brightpass_threshold = value; }
	));
	Utype.set("BrightpassOffset", sol::property(
		[](HdrStateBlock& self) { return *self.brightpass_offset; },
		[](HdrStateBlock& self, float value) { *self.brightpass_offset = value; }
	));
	Utype.set("UseHdrLevel", sol::property(
		[](HdrStateBlock& self) { return *self.use_hdr_level; },
		[](HdrStateBlock& self, bool value) { *self.use_hdr_level = value; }
	));
	Utype.set("BloomNew", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_new; },
		[](HdrStateBlock& self, bool value) { *self.bloom_new = value; }
	));

	Utype.set("EyeAdaptionBase", sol::property(
		[](HdrStateBlock& self) { return *self.eye_adaption_base; },
		[](HdrStateBlock& self, float value) { *self.eye_adaption_base = value; }
	));
	Utype.set("EyeAdaptionAmount", sol::property(
		[](HdrStateBlock& self) { return *self.eye_adaption_amount; },
		[](HdrStateBlock& self, float value) { *self.eye_adaption_amount = value; }
	));
	Utype.set("EyeFadeMin", sol::property(
		[](HdrStateBlock& self) { return *self.eye_fade_min; },
		[](HdrStateBlock& self, float value) { *self.eye_fade_min = value; }
	));
	Utype.set("EyeFadeMax", sol::property(
		[](HdrStateBlock& self) { return *self.eye_fade_max; },
		[](HdrStateBlock& self, float value) { *self.eye_fade_max = value; }
	));
	Utype.set("BloomAmount", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_amount; },
		[](HdrStateBlock& self, float value) { *self.bloom_amount = value; }
	));
	Utype.set("BloomTheta", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_theta; },
		[](HdrStateBlock& self, float value) { *self.bloom_theta = value; }
	));
	Utype.set("BloomSlopeA", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_slope_A; },
		[](HdrStateBlock& self, float value) { *self.bloom_slope_A = value; }
	));
	Utype.set("BloomSlopeB", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_slope_B; },
		[](HdrStateBlock& self, float value) { *self.bloom_slope_B = value; }
	));
	Utype.set("LuminanceConversion", sol::property(
		[](HdrStateBlock& self)->vector& { return *self.luminance_conversion; }
	));
	Utype.set("BloomSuperSoft", sol::property(
		[](HdrStateBlock& self) { return *self.bloom_super_soft; },
		[](HdrStateBlock& self, bool value) { *self.bloom_super_soft = value; }
	));
	Utype.set("EyeOverride", sol::property(
		[](HdrStateBlock& self) { return *self.eye_override; },
		[](HdrStateBlock& self, bool value) { *self.eye_override = value; }
	));
	RfgTable.set_usertype("HdrStateBlock", Utype);
#endif
}