#pragma once
#include "ScriptSelectGui.h"

class GeneralTweaksGui
{
public:
	GeneralTweaksGui();
	~GeneralTweaksGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	Player* PlayerPtr = nullptr;

	bool TeleportWindowOpen = false;
	bool PlayerVariablesGuiOpen = false;

	bool UseUnsafeTeleport = false;
	float SafeTeleportPlacementRange = 10.0f;
	bool AllowSafeTeleportFail = false;

	bool Invulnerable = false;

	float CustomPlayerMoveSpeed = 5.0f;
	float CustomPlayerMaxSpeed = 50.0f;
	float CustomJumpHeight = 1.2f;

	bool NeedCustomJumpHeightSet = false;
	bool NeedCustomMoveSpeedSet = false;
	bool NeedCustomMaxMoveSpeedSet = false;

	int XrayEffectMode = 0;
	bool XrayModeOn = false;

private:
	bool* OpenState = nullptr;
};

