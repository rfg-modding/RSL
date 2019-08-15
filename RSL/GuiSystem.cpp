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
	Initialized = true;
}

/* Returns true if this GuiSystem instance has been initialized.*/
bool GuiSystem::Ready() const
{
	return Initialized;
}

/* Draws all GUIs in GuiList. Has exception checking so that if one gui fails it shouldn't 
 * break all other GUIs.
 */
void GuiSystem::Draw()
{
	try
	{
		if (!Globals::ImGuiInitialized)
		{
			if (DrawPassedOnce)
			{
				throw std::exception("ImGui not initialized! Failed to draw overlay gui!");
			}
			return;
		}
        if (!Globals::PlayerPtr)
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
		if (!Globals::Scripts)
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
                LuaConsole.Get().Draw();
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
		Logger::LogError("{}\n", ExceptionInfo);
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
		Logger::LogError("{}\n", ExceptionInfo);
		//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), ExceptionInfo.c_str(), "Failed to draw overlay gui!", MB_OK);
	}
    if(*reinterpret_cast<bool*>(*reinterpret_cast<DWORD*>(Globals::ModuleBase + 0x002CA210)))
    {
        Logger::LogFatalError("Failure route A reached\n");
        _Exit(1);
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

    if(ImGui::Button("Log RFG menu info"))
    {
        Globals::LogGameMenuInfo();
    }
    ImGui::SameLine();
    Util::Gui::ShowHelpMarker("Logs information about the currently loaded game menus. Does not have much use currently. Mainly a debug feature I decided to leave in. Check the logger window or the master log for the output. I've included it in this preload menu so you could still access this feature before loading a save.");

    ImGui::End();
}

/* Toggles visibility of the lua console*/
void GuiSystem::ToggleLuaConsole()
{
	LuaConsoleActive = !LuaConsoleActive;
    LuaConsole.Get().Toggle();
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

void GuiSystem::AddChildGui(BaseGui* Gui, bool InitialVisibility)
{
    GuiList.push_back(Gui);
    GuiList.back()->Visible = InitialVisibility;
}