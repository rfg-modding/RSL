#pragma once
#include "BaseGui.h"

class GeneralTweaksGui : public BaseGui
{
public:
	GeneralTweaksGui(bool* _OpenState, std::string _Title);
	~GeneralTweaksGui();

	void Draw();

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

	explosion_info CustomExplosionInfo; 
	bool MiddleMouseBoomActive = false;
	int MiddleMouseExplosionsPerSecond = 20;

	bool UseCustomTimeOfDayLight = false;
	rl_color_float CustomTimeOfDayLightColor;

	gfm_alert_levels CustomAlertLevel;

	bool MiddleMouseRepairSphereActive = false;
	float RepairRadius = 6.0f;
	int RepairDuration = 1;
	int RepairPosition = 0;

	bool LockAlertLevel = false;
	bool UnlimitedAmmo = false;

	bool TempUseCustoms = false;
	int CustomUnlimitedAmmo = 0;
	float CustomStealthPercent = 0.0f;
	float CustomRenderAlpha = 0.0f;
};

