#pragma once
#include "WelcomeGui.h"
#include "TeleportGui.h"
#include "ThemeEditorGui.h"
#include "IntrospectionGui.h"
#include "GeneralTweaksGui.h"
#include "ScriptSelectGui.h"
#include "OverlayConsole.h"
#include "TextEditor.h"
#include "MenuBarGui.h"
#include "LogWindow.h"

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

	void ToggleLuaConsole();
	bool IsLuaConsoleActive();
	void DeactivateLuaConsole();
	void ActivateLuaConsole();

	WelcomeGui MainWindow;
	OverlayConsole Console;
	ThemeEditorGui ThemeEditor;
	TeleportGui TeleportMenu;
	IntrospectionGui IntrospectionMenu;
	GeneralTweaksGui TweaksMenu;
	ScriptSelectGui ScriptsMenu;
	TextEditor ScriptEditor;
	MenuBarGui TopMenuBar;
	LogWindow LogGui;

	bool ShowAppWelcome = true;

	bool ShowAppConsole = false;
	bool ShowAppMetrics = false;
	bool ShowAppThemeEditor = false;
	bool ShowAppAbout = false;
	bool ShowAppGameInfoOverlay = false;

	bool ShowAppMainMenuBar = false;
	bool ShowAppSimpleOverlay = false;

	bool ShowAppTeleportMenu = false;
	bool ShowAppHelpWindow = false;
	bool ShowAppIntrospectionMenu = false;
	bool ShowAppTweaksMenu = false;
	bool ShowAppScriptsMenu = false;
	bool ShowAppScriptEditor = false;

	bool ShowAppLogWindow = false;

private:
	bool LuaConsoleActive = false;
	/*This is private to prevent accidental changes.*/
	ScriptManager* Scripts = nullptr;
	/*Private to insure that every instance of PlayerPtr is properly set,
	instead of mistakenly just setting this one.*/
	Player* PlayerPtr = nullptr;
};

