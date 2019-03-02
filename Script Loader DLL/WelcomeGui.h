#pragma once
///#include "Globals.h"
///#include "RFGR_Types_Player.h"
#include "TeleportGui.h"

class ScriptManager;

class WelcomeGui
{
public:
	WelcomeGui();
	~WelcomeGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);
	void ShowAboutWindow(bool* p_open);

	ImGuiWindowFlags MainOverlayWindowFlags = 0;
	ImGuiWindowFlags MainOverlayPopupFlags = 0;
	ImGuiInputTextFlags MainOverlayTeleportEditTextFlags = 0;

	ScriptManager* Scripts = nullptr;

private:
	bool* OpenState;
};