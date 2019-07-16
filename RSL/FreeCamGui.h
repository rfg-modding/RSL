#pragma once
#include "BaseGui.h"

class CameraWrapper;

class FreeCamGui : public BaseGui
{
public:
	FreeCamGui(bool* OpenState_, std::string Title_) { OpenState = OpenState_; Title = Title_; }
	~FreeCamGui() = default;

	void Draw() override;

	CameraWrapper* Camera = nullptr;

	/*WARNING: If this option is disabled two bugs are introduced. 
	1. The game will often crash if the player clicks when far from the character.
	2. The players weapon aim is incorrect since the camera is in an unexpected position.*/
	bool PlayerFollowCam = true;

	float CustomFarClipDistance = 475.0f;
	float CustomTimeValue = 100.0f;
	float CustomTODValue = 100.0f;

	bool ReturnPlayerToOriginalPosition = false;
	vector OriginalPosition{0.0f};

    std::string LevelNameBuffer;
    bool NewGame = false;
    bool SingleZone = true;
    bool PlayerStartAtSafehouse = false;
    uint DlcId = 4294967295; //0xFFFFFFFF (Default one I saw passed in IDA)
    bool ResetDestruction = false;
};