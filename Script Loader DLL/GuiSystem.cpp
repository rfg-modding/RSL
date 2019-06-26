#include "GuiSystem.h"
#include "ScriptManager.h"

GuiSystem::~GuiSystem()
{
	for (const auto& i : GuiList)
	{
		delete i;
	}
}

/* Creates all GUI class instances and adds them to the GuiList. Sets pointers for each of 
 * them for quick (no string comparisons) and easy access. 
 */
void GuiSystem::Initialize()
{
	GuiList.push_back(new MenuBarGui(&ShowAppMainMenuBar, "Top Menu Bar"));
	MainMenuBar = static_cast<MenuBarGui*>(GuiList.back());
    GuiList.push_back(new GeneralTweaksGui(&ShowAppTweaksMenu, "General tweaks"));
    TweaksMenu = static_cast<GeneralTweaksGui*>(GuiList.back());
	GuiList.push_back(new OverlayConsole(&ShowAppConsole, "Lua console"));
	Console = static_cast<OverlayConsole*>(GuiList.back());
    GuiList.push_back(new ScriptSelectGui(&ShowAppScriptsMenu, "Scripts"));
    ScriptList = static_cast<ScriptSelectGui*>(GuiList.back());
    GuiList.push_back(new FreeCamGui(&ShowAppFreeCamSettings, "Camera settings"));
    FreeCamSettings = static_cast<FreeCamGui*>(GuiList.back());
	GuiList.push_back(new TextEditor(&ShowAppScriptEditor, "Script editor"));
	ScriptEditor = static_cast<TextEditor*>(GuiList.back());
	GuiList.push_back(new LogWindow(&ShowAppLogWindow , "Logger"));
	LogGui = static_cast<LogWindow*>(GuiList.back());
    GuiList.push_back(new WelcomeGui(&ShowAppWelcome, "Welcome"));
    Welcome = static_cast<WelcomeGui*>(GuiList.back());
    GuiList.push_back(new ThemeEditorGui(&ShowAppThemeEditor, "Theme editor"));
    ThemeEditor = static_cast<ThemeEditorGui*>(GuiList.back());
	GuiList.push_back(new PhysicsGui(&ShowAppPhysicsSettings, "Physics settings"));
	PhysicsSettings = static_cast<PhysicsGui*>(GuiList.back());
    GuiList.push_back(new TeleportGui(&ShowAppTeleportMenu, "Teleport"));
    Teleport = static_cast<TeleportGui*>(GuiList.back());
    GuiList.push_back(new IntrospectionGui(&ShowAppIntrospectionMenu, "Object introspection"));
    Introspection = static_cast<IntrospectionGui*>(GuiList.back());

	for (const auto& i : GuiList)
	{
		i->Gui = this;
	}
	Initialized = true;
}

/* Returns true if this GuiSystem instance has been initialized.*/
bool GuiSystem::Ready() const
{
	return Initialized;
}

/* Sets the ScriptManager pointer for all GUIs. This function is used instead of manually
 * setting it to avoid accidentally missing one of the GUIs and to avoid code duplication.
 */
void GuiSystem::SetScriptManager(ScriptManager* Scripts_)
{
	Scripts = Scripts_;
	for (const auto& i : GuiList)
	{
		i->Scripts = Scripts_;
	}
}

/* Gets this instances ScriptManager pointer. */
ScriptManager* GuiSystem::GetScriptManager() const
{
	return Scripts;
}

/* Returns true if ScriptManager pointer is not a nullptr, and false if it is.*/
bool GuiSystem::HasValidScriptManager() const
{
	return (Scripts != nullptr);
}

/* Draws all GUIs in GuiList. Has exception checking so that if one gui fails it shouldn't 
 * break all other GUIs.
 */
void GuiSystem::Draw()
{
	try
	{
        PlayerPtr = Globals::PlayerPtr;
		if (!Globals::ImGuiInitialized)
		{
			if (DrawPassedOnce)
			{
				throw std::exception("ImGui not initialized! Failed to draw overlay gui!");
			}
			return;
		}
        if (!PlayerPtr)
        {
            if(Globals::OverlayActive)
            {
                DrawPreInitWindow();
            }
            if (DrawPassedOnce)
            {
                throw std::exception("Player pointer is null! Failed to draw overlay gui!");
            }
            return;
        }
		if (!Scripts)
		{
			if (DrawPassedOnce)
			{
				throw std::exception("Scripts pointer is null! Failed to draw overlay gui!");
			}
			return;
		}
		//Used on the first successful draw of the gui to insure that each gui element has valid PlayerPtr*, Scripts*, and Gui* values. 
		//Very duct-tapey solution, but it works. Put in place since the values in menus are sometimes not being set properly, causing crashes.
		std::call_once(InitialDrawCheck, [&]()
		{
			for (const auto& i : GuiList)
			{
				i->PlayerPtr = PlayerPtr;
				i->Scripts = Scripts;
				i->Gui = this;

				//This is used to prevent the spamming of failure messages from invalid pointers before they've been set.
				//So, error messages from invalid pointers will only show up after they've all been set properly once.
				//Need to consider if this could obscure bugs in some instances, but for now I've got no better way of doing this.
				DrawPassedOnce = true;
			}
		});

		if (Globals::OverlayActive)
		{
			for (const auto& i : GuiList)
			{
				try
				{
					i->Draw();
				}
				catch (const std::exception& Ex)
				{
					std::string ExceptionInfo = Ex.what();
					ExceptionInfo += " \nstd::exception caught when drawing overlay sub-gui! ";
					ExceptionInfo += ", Additional info: ";
					ExceptionInfo += "Sub-gui: ";
					ExceptionInfo += i->Title;
					ExceptionInfo += ", File: ";
					ExceptionInfo += __FILE__;
					ExceptionInfo += ", Function: ";
					ExceptionInfo += __func__;
					ExceptionInfo += ", Line: ";
					ExceptionInfo += __LINE__;
					//Logger::Log(ExceptionInfo, LogError, true, true);
					throw std::exception(ExceptionInfo.c_str());
				}
			}
		}
		if (LuaConsoleActive && !Globals::OverlayActive)
		{
			try
			{
				Console->Draw();
			}
			catch (const std::exception& Ex)
			{
				std::string ExceptionInfo = Ex.what();
				ExceptionInfo += " \nstd::exception caught when drawing lone console! ";
				ExceptionInfo += ", Additional info: ";
				ExceptionInfo += "File: ";
				ExceptionInfo += __FILE__;
				ExceptionInfo += ", Function: ";
				ExceptionInfo += __func__;
				ExceptionInfo += ", Line: ";
				ExceptionInfo += __LINE__;
				//Logger::Log(ExceptionInfo, LogError, true, true);
				throw std::exception(ExceptionInfo.c_str());
			}
		}
	}
	catch (const std::exception& Ex)
	{
		std::string ExceptionInfo = Ex.what();
		ExceptionInfo += " \nstd::exception caught when drawing overlay gui! ";
		ExceptionInfo += ", Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogError, true, true);
		//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), ExceptionInfo.c_str(), "Failed to draw overlay gui!", MB_OK);
	}
	catch (...)
	{
		std::string ExceptionInfo = "Default exception caught when drawing overlay gui! ";
		ExceptionInfo += ", Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogError, true, true);
		//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), ExceptionInfo.c_str(), "Failed to draw overlay gui!", MB_OK);
	}
}

void GuiSystem::DrawPreInitWindow()
{
    ImGui::SetNextWindowSize(ImVec2(250.0f, 300.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Initialization not complete", &ShowPreInitWindow, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    ImGui::SetNextItemWidth(250.0f);
    ImGui::TextWrapped("RSL initialization currently requires a save game to be loaded to complete. Please load a save game to access the rest of the overlay.");

    ImGui::End();
}

/* Sets the Player pointer for all GUIs.*/
void GuiSystem::SetPlayerPtr(Player* NewPlayerPtr)
{
	PlayerPtr = NewPlayerPtr;
	for (const auto& i : GuiList)
	{
		i->PlayerPtr = NewPlayerPtr;
	}
}

/* Sets the Player pointer for all GUIs.*/
void GuiSystem::SetPlayerPtr(void* NewPlayerPtr)
{
	SetPlayerPtr(static_cast<Player*>(NewPlayerPtr));
}

/* Toggles visibility of the lua console*/
void GuiSystem::ToggleLuaConsole()
{
	LuaConsoleActive = !LuaConsoleActive;
	ShowAppConsole = !ShowAppConsole;
}

/* Returns true if the lua console is active/visible.*/
bool GuiSystem::IsLuaConsoleActive() const
{
	return LuaConsoleActive;
}

/* Deactivates the lua console so it's no longer visible.*/
void GuiSystem::DeactivateLuaConsole()
{
	LuaConsoleActive = false;
}

/* Activats the lua console so it's now visible.*/
void GuiSystem::ActivateLuaConsole()
{
	LuaConsoleActive = true;
}
