#pragma once
#include "WelcomeGui.h"
#include "TeleportGui.h"
#include "ThemeEditorGui.h"
#include "IntrospectionGui.h"
#include "GeneralTweaksGui.h"
#include "ScriptSelectGui.h"
#include "OverlayConsole.h"
#include "TextEditorWrapper.h"
#include "MenuBarGui.h"
#include "LogWindow.h"
#include "FreeCamGui.h"
#include "PhysicsGui.h"

class ScriptManager;

/* Keeps track of all menus/gui's used in the script loader overlay. Handles visibility, 
 * updates common values they use, and manages access to the GUI's by other parts of the code.
 * Keeps things cleaner and easier to maintain and add new guis.
 */
class GuiSystem
{
public:
	GuiSystem() = default;
	~GuiSystem();

	void Initialize();
	bool Ready() const;
	void SetScriptManager(ScriptManager* Scripts_);
	ScriptManager* GetScriptManager() const;
	bool HasValidScriptManager() const;
	//bool LoadTeleportLocations();
	//bool LoadGUIConfig();
	void Draw();

    void DrawPreInitWindow();

	void SetPlayerPtr(Player* NewPlayerPtr);
	void SetPlayerPtr(void* NewPlayerPtr);

	void ToggleLuaConsole();
	bool IsLuaConsoleActive() const;
	void DeactivateLuaConsole();
	void ActivateLuaConsole();

	std::vector <BaseGui*> GuiList;

	std::once_flag InitialDrawCheck;
	bool DrawPassedOnce = false;

	//These pointers are used by any other class which wants quick access to a gui's state
	//Avoids the cost of a search for each access.
    LogWindow* LogGui = nullptr;
    ScriptSelectGui* ScriptList = nullptr;
    PhysicsGui* PhysicsSettings = nullptr;
    ThemeEditorGui* ThemeEditor = nullptr;
	WelcomeGui* Welcome = nullptr;
    TeleportGui* Teleport = nullptr;
	IntrospectionGui* Introspection = nullptr;
	GeneralTweaksGui* TweaksMenu = nullptr;
	TextEditorWrapper* ScriptEditor = nullptr;
	FreeCamGui* FreeCamSettings = nullptr;
    OverlayConsole* Console = nullptr;
    MenuBarGui* MainMenuBar = nullptr;

    bool ShowPreInitWindow = true;

	bool ShowAppWelcome = true;
	bool ShowAppConsole = false;
    bool ShowAppIntrospectionMenu = false;
	bool ShowAppThemeEditor = false;
	bool ShowAppAbout = false;
	bool ShowAppGameInfoOverlay = false;
	bool ShowAppMainMenuBar = true;
    bool ShowAppMetrics = false;
	bool ShowAppSimpleOverlay = false;
	bool ShowAppHelpWindow = false;
    bool ShowAppPhysicsSettings = false;
	bool ShowAppTweaksMenu = false;
	bool ShowAppScriptsMenu = false;
    bool ShowAppTeleportMenu = false;
	bool ShowAppScriptEditor = false;
    bool ShowAppFreeCamSettings = false;
	bool ShowAppLogWindow = false;

private:
	bool LuaConsoleActive = false;
	/*This is private to prevent accidental changes.*/
	ScriptManager* Scripts = nullptr;
	/*Private to insure that every instance of PlayerPtr is properly set,
	instead of mistakenly just setting this one.*/
	Player* PlayerPtr = nullptr;
	bool Initialized = false;
};

