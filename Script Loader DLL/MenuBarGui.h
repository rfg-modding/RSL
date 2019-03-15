#pragma once
#include "BaseGui.h"

class ScriptManager;

class MenuBarGui
{
public:
	MenuBarGui();
	~MenuBarGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);
	void ConfirmScriptLoaderDeactivation();

	ScriptManager* Scripts = nullptr;
	ImGuiWindowFlags WindowFlags = 0;

	bool* ShowAppMainWindow = nullptr; //Welcome window
		
	bool* ShowAppConsole = nullptr;
	bool* ShowAppThemeEditor = nullptr;
	bool* ShowAppAbout = nullptr;
		
	bool* ShowAppSimpleOverlay = nullptr;
		
	bool* ShowAppTeleportMenu = nullptr;
	bool* ShowAppHelpWindow = nullptr;
	bool* ShowAppIntrospectionMenu = nullptr;
	bool* ShowAppTweaksMenu = nullptr;
	bool* ShowAppScriptsMenu = nullptr;
	bool* ShowAppScriptEditor = nullptr;

	bool* ShowAppLogWindow = nullptr;

private:
	bool* OpenState = nullptr;
};

