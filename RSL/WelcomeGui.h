#pragma once
#include "BaseGui.h"

class WelcomeGui : public BaseGui
{
public:
	WelcomeGui(std::string Title_);
	~WelcomeGui() = default;

	void Draw() override;

	ImGuiWindowFlags MainOverlayWindowFlags = 0;
	ImGuiWindowFlags MainOverlayPopupFlags = 0;
	ImGuiInputTextFlags MainOverlayTeleportEditTextFlags = 0;
};