#pragma once
#include "MainOverlay.h"

class ScriptManager;

class GuiSystem
{
public:
	GuiSystem();
	~GuiSystem();

	void Initialize();
	void SetScriptManager(ScriptManager* _Scripts);
	//bool LoadTeleportLocations();
	//bool LoadGUIConfig();
	void Draw();

	void SetPlayerPtr(Player* NewPlayerPtr);
	void SetPlayerPtr(void* NewPlayerPtr);

	MainOverlay MainWindow;
	OverlayConsole Console;
	ThemeEditorGui ThemeEditor;
	TeleportGui TeleportMenu;

	bool ShowAppMainWindow = true;

	bool ShowAppConsole = false;
	bool ShowAppMetrics = false;
	bool ShowAppThemeEditor = true;
	bool ShowAppAbout = false;
	bool ShowAppGameInfoOverlay = false;

	bool ShowAppMainMenuBar = false;
	bool ShowAppLog = false;
	bool ShowAppLongText = false;
	bool ShowAppSimpleOverlay = false;

	bool ShowAppTeleportMenu = true;
	bool ShowAppHelpWindow = false;

private:
	/*This is private to prevent accidental changes.*/
	ScriptManager* Scripts;
	/*Private to insure that every instance of PlayerPtr is properly set,
	instead of mistakenly just setting this one.*/
	Player* PlayerPtr;
};

