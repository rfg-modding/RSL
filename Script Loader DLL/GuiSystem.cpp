#include "GuiSystem.h"
#include "ScriptManager.h"

GuiSystem::GuiSystem()
{

}

GuiSystem::~GuiSystem()
{

}

void GuiSystem::Initialize()
{
	TopMenuBar.ShowAppMainWindow = &ShowAppWelcome;
	TopMenuBar.ShowAppConsole = &ShowAppConsole;
	TopMenuBar.ShowAppThemeEditor = &ShowAppThemeEditor;
	TopMenuBar.ShowAppAbout = &ShowAppAbout;
	TopMenuBar.ShowAppSimpleOverlay = &ShowAppSimpleOverlay;
	TopMenuBar.ShowAppTeleportMenu = &ShowAppTeleportMenu;
	TopMenuBar.ShowAppHelpWindow = &ShowAppHelpWindow;
	TopMenuBar.ShowAppIntrospectionMenu = &ShowAppIntrospectionMenu;
	TopMenuBar.ShowAppTweaksMenu = &ShowAppTweaksMenu;
	TopMenuBar.ShowAppScriptsMenu = &ShowAppScriptsMenu;
	TopMenuBar.ShowAppScriptEditor = &ShowAppScriptEditor;
	TopMenuBar.ShowAppLogWindow = &ShowAppLogWindow;
	TopMenuBar.Initialize(&ShowAppMainMenuBar);

	MainWindow.Initialize(&ShowAppWelcome);
	Console.Initialize(&ShowAppConsole);
	ThemeEditor.Initialize(&ShowAppThemeEditor);
	TeleportMenu.Initialize(&ShowAppTeleportMenu);
	IntrospectionMenu.Initialize(&ShowAppIntrospectionMenu);
	TweaksMenu.Initialize(&ShowAppTweaksMenu);

	ScriptEditor.Initialize(&ShowAppScriptEditor);
	ScriptEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());

	ScriptsMenu.ScriptEditor = &ScriptEditor;
	ScriptsMenu.ScriptEditorState = &ShowAppScriptEditor;
	ScriptsMenu.Initialize(&ShowAppScriptsMenu);

	LogGui.Initialize(&ShowAppLogWindow);
}

/*Should only be doing this once.*/
void GuiSystem::SetScriptManager(ScriptManager* _Scripts)
{
	Scripts = _Scripts;
	MainWindow.Scripts = _Scripts;
	Console.Scripts = _Scripts;
	ScriptsMenu.Scripts = _Scripts;
	ScriptEditor.Scripts = _Scripts;
	TopMenuBar.Scripts = _Scripts;
}

void GuiSystem::Draw()
{
	if (!PlayerPtr)
	{
		return;
	}
	if (!Scripts)
	{
		return;
	}

	if (OverlayActive)
	{
		MainWindow.Draw("Welcome");
		//Console.Draw("Lua Console");
		ThemeEditor.Draw("Theme Editor");
		TeleportMenu.Draw("Teleport Menu");
		IntrospectionMenu.Draw("Introspection Menu");
		TweaksMenu.Draw("General Tweaks Menu");
		ScriptsMenu.Draw("Script Select Menu");
		ScriptEditor.Render("Script Editor");// , ImVec2(400.0f, 400.0f));
		TopMenuBar.Draw("Top Menu Bar");
		LogGui.Draw("Logger");
	}
	if (LuaConsoleActive)
	{
		Console.Draw("Lua Console");
	}
}

void GuiSystem::SetPlayerPtr(Player* NewPlayerPtr)
{
	PlayerPtr = NewPlayerPtr;
	Console.PlayerPtr = NewPlayerPtr;
	//ThemeEditor.PlayerPtr = NewPlayerPtr;
	TeleportMenu.PlayerPtr = NewPlayerPtr;
	IntrospectionMenu.PlayerPtr = NewPlayerPtr;
	TweaksMenu.PlayerPtr = NewPlayerPtr;
}

/*Sets PlayerPtr for all GUI classes which use it.*/
void GuiSystem::SetPlayerPtr(void* NewPlayerPtr)
{
	SetPlayerPtr((Player*)NewPlayerPtr);
}

void GuiSystem::ToggleLuaConsole()
{
	LuaConsoleActive = !LuaConsoleActive;
	ShowAppConsole = !ShowAppConsole;
	/*if (LuaConsoleActive && !ShowAppConsole)
	{
		ShowAppConsole = true;
	}*/
}

bool GuiSystem::IsLuaConsoleActive()
{
	return LuaConsoleActive;
}

void GuiSystem::DeactivateLuaConsole()
{
	LuaConsoleActive = false;
}

void GuiSystem::ActivateLuaConsole()
{
	LuaConsoleActive = true;
}
