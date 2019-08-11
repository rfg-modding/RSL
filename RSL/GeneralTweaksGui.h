#pragma once
#include "BaseGui.h"

class GeneralTweaksGui : public BaseGui
{
public:
	GeneralTweaksGui(std::string Title_);
	~GeneralTweaksGui() = default;

	void Draw() override;

	bool Invulnerable = false;

	float CustomPlayerMoveSpeed = 5.0f;
	float CustomPlayerMaxSpeed = 50.0f;
	float CustomJumpHeight = 1.2f;

	bool NeedCustomJumpHeightSet = false;
	bool NeedCustomMoveSpeedSet = false;
	bool NeedCustomMaxMoveSpeedSet = false;

	int XrayEffectMode = 0;
	bool XrayModeOn = false;

	vector CustomLevelAmbientLight;
	vector CustomLevelBackgroundAmbientLight;
	bool UseCustomLevelAmbientLight = false;
	bool UseCustomLevelBackgroundAmbientLight = false;

	bool UseCustomTimeOfDayLight = false;
	rl_color_float CustomTimeOfDayLightColor;

	gfm_alert_levels CustomAlertLevel;

	bool LockAlertLevel = false;

	bool AiIgnore = false;
	bool DisablePlayerRagdoll = false;

    float CustomTodOverride = 12.0f;
    bool UseCustomTodOverride = false;
};

