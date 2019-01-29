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
	MainWindow.ShowAppConsole = &ShowAppConsole;
	MainWindow.ShowAppMetrics = &ShowAppMetrics;
	MainWindow.ShowAppStyleEditor = &ShowAppThemeEditor;
	MainWindow.ShowAppAbout = &ShowAppAbout;
	MainWindow.ShowAppGameInfoOverlay = &ShowAppGameInfoOverlay;
	MainWindow.ShowAppMainMenuBar = &ShowAppMainMenuBar;
	MainWindow.ShowAppLog = &ShowAppLog;
	MainWindow.ShowAppLongText = &ShowAppLongText;
	MainWindow.ShowAppSimpleOverlay = &ShowAppSimpleOverlay;

	MainWindow.Initialize(&ShowAppMainWindow);
	Console.Initialize(&ShowAppConsole);
	ThemeEditor.Initialize(&ShowAppThemeEditor);
	TeleportMenu.Initialize(&ShowAppTeleportMenu);
}

/*Should only be doing this once.*/
void GuiSystem::SetScriptManager(ScriptManager* _Scripts)
{
	Scripts = _Scripts;

	MainWindow.Scripts = _Scripts;
}

void GuiSystem::Draw()
{
	MainWindow.Draw("Main overlay");
	Console.Draw("Lua Console");
	ThemeEditor.Draw("Theme Editor");
	TeleportMenu.Draw("Teleport Menu");
}

void GuiSystem::SetPlayerPtr(Player* NewPlayerPtr)
{
	PlayerPtr = NewPlayerPtr;
	MainWindow.PlayerPtr = NewPlayerPtr;
	Console.PlayerPtr = NewPlayerPtr;
	//ThemeEditor.PlayerPtr = NewPlayerPtr;
	TeleportMenu.PlayerPtr = NewPlayerPtr;
}

/*Sets PlayerPtr for all GUI classes which use it.*/
void GuiSystem::SetPlayerPtr(void* NewPlayerPtr) 
{
	PlayerPtr = (Player*)(NewPlayerPtr);
	MainWindow.PlayerPtr = (Player*)(NewPlayerPtr);
	Console.PlayerPtr = (Player*)(NewPlayerPtr);
	//ThemeEditor.PlayerPtr = (Player*)(NewPlayerPtr);
	TeleportMenu.PlayerPtr = (Player*)(NewPlayerPtr);
}
