#pragma once
#include "BaseGui.h"

class WelcomeGui : public BaseGui
{
public:
	WelcomeGui(bool* _OpenState, std::string _Title);
	~WelcomeGui();

	void Draw();

	ImGuiWindowFlags MainOverlayWindowFlags = 0;
	ImGuiWindowFlags MainOverlayPopupFlags = 0;
	ImGuiInputTextFlags MainOverlayTeleportEditTextFlags = 0;
};