#pragma once
#include "BaseGui.h"

class CameraWrapper;

class FreeCamGui : public BaseGui
{
public:
	FreeCamGui(bool* _OpenState, std::string _Title);
	~FreeCamGui();

	void Draw();

	CameraWrapper* Camera;

	/*WARNING: If this option is disabled two bugs are introduced. 
	1. The game will often crash if the player clicks when far from the character.
	2. The players weapon aim is incorrect since the camera is in an unexpected position.*/
	bool PlayerFollowCam = true;

	float CustomFarClipDistance = 475.0f;
	float CustomTimeValue = 100.0f;
	float CustomTODValue = 100.0f;
};

