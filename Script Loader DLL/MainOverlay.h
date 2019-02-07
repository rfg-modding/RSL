#pragma once
///#include "Globals.h"
///#include "RFGR_Types_Player.h"
#include "TeleportGui.h"

class ScriptManager;

class MainOverlay
{
public:
	MainOverlay();
	~MainOverlay();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);
	void DrawPlayerVariablesGui(bool UseSeparateWindow, const char* Title, bool* Open, ImGuiWindowFlags Flags);

	void ShowExampleAppMainMenuBar();
	//void ShowExampleAppConsole(bool* p_open);
	//void ShowExampleAppLog(bool* p_open);
	void ShowExampleAppPropertyEditor(bool* p_open);
	void ShowExampleAppLongText(bool* p_open);
	void ShowExampleAppSimpleOverlay(bool* p_open);
	void ShowAboutWindow(bool* p_open);
	//void ShowStyleEditor(ImGuiStyle* ref);

	//bool ShowStyleSelector(const char* label);
	//void ShowFontSelector(const char* label);

	//void ShowHelpMarker(const char* Description);

	Player* PlayerPtr = nullptr;
	Player TargetValues;
	matrix HavokPlayerOrient;
	vector HavokPlayerPosition;

	ImGuiWindowFlags MainOverlayWindowFlags = 0;
	ImGuiWindowFlags MainOverlayPopupFlags = 0;
	ImGuiInputTextFlags MainOverlayTeleportEditTextFlags = 0;

	bool* ShowAppConsole = false;
	bool* ShowAppMetrics = false;
	bool* ShowAppStyleEditor = false;
	bool* ShowAppAbout = false;
	bool* ShowAppGameInfoOverlay = false;

	bool* ShowAppMainMenuBar = false;
	bool* ShowAppLog = false;
	bool* ShowAppLongText = false;
	bool* ShowAppSimpleOverlay = false;

	bool PlayerPtrTargetsInitialized = false;
	bool NeedPlayerPosSet = false;
	float PlayerPositionTargetArray[3] = { 0 };

	float PlayerVelocityTargetArray[3] = { 0 };
	bool NeedPlayerVelocitySet = false;

	ScriptManager* Scripts;

private:
	bool* OpenState;
};