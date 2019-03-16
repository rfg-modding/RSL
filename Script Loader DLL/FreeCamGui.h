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
};

