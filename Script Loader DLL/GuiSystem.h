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
#include "FreeCamGui.h"
#include "PhysicsGui.h"

class ScriptManager;

class GuiSystem
{
public:
	GuiSystem();
	~GuiSystem();

	void Initialize();
	void SetScriptManager(ScriptManager* _Scripts);
	ScriptManager* GetScriptManager();
	//bool LoadTeleportLocations();
	//bool LoadGUIConfig();
	void Draw();

	void SetPlayerPtr(Player* NewPlayerPtr);
	void SetPlayerPtr(void* NewPlayerPtr);

	void ToggleLuaConsole();
	bool IsLuaConsoleActive();
	void DeactivateLuaConsole();
	void ActivateLuaConsole();

	std::vector <BaseGui*> GuiList;

	std::once_flag InitialDrawCheck;
	bool DrawPassedOnce = false;

	//These pointers are used by any other class which wants quick access to a gui's state
	//Avoids the cost of a search for each access.
	MenuBarGui* MainMenuBar = nullptr;
	WelcomeGui* Welcome = nullptr;
	OverlayConsole* Console = nullptr;
	ThemeEditorGui* ThemeEditor = nullptr;
	TeleportGui* Teleport = nullptr;
	IntrospectionGui* Introspection = nullptr;
	GeneralTweaksGui* TweaksMenu = nullptr;
	TextEditor* ScriptEditor = nullptr;
	ScriptSelectGui* ScriptList = nullptr;
	LogWindow* LogGui = nullptr;
	FreeCamGui* FreeCamSettings = nullptr;
	PhysicsGui* PhysicsSettings = nullptr;

	bool ShowAppWelcome = true;

	bool ShowAppConsole = false;
	bool ShowAppMetrics = false;
	bool ShowAppThemeEditor = false;
	bool ShowAppAbout = false;
	bool ShowAppGameInfoOverlay = false;

	bool ShowAppMainMenuBar = true;
	bool ShowAppSimpleOverlay = false;

	bool ShowAppTeleportMenu = false;
	bool ShowAppHelpWindow = false;
	bool ShowAppIntrospectionMenu = false;
	bool ShowAppTweaksMenu = false;
	bool ShowAppScriptsMenu = false;
	bool ShowAppScriptEditor = false;

	bool ShowAppLogWindow = false;
	bool ShowAppFreeCamSettings = false;
	bool ShowAppPhysicsSettings = false;

private:
	bool LuaConsoleActive = false;
	/*This is private to prevent accidental changes.*/
	ScriptManager* Scripts = nullptr;
	/*Private to insure that every instance of PlayerPtr is properly set,
	instead of mistakenly just setting this one.*/
	Player* PlayerPtr = nullptr;
};

