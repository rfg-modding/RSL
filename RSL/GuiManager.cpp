#include "GuiManager.h"

GuiManager::~GuiManager()
{
    for (const auto& i : GuiList)
    {
        delete i;
    }
}

void GuiManager::Initialize()
{
    Initialized = true;
}

bool GuiManager::Ready()
{
    return Initialized;
}

/* Draws all GUIs in GuiList. Has exception checking so that if one gui fails it shouldn't
 * break all other GUIs.
 */
void GuiManager::Draw()
{
    if (!Globals::ImGuiInitialized)
        return;
    if (!Globals::PlayerPtr && Globals::OverlayActive)
        DrawPreInitWindow();
    if (!Globals::PlayerPtr)
        return;

    ProcessDeletions();
    try
    {
        for (const auto& i : GuiList)
            if(Globals::OverlayActive || i->IndependentVisibility)
                i->Draw();

        if (LuaConsoleActive && !Globals::OverlayActive) //Todo: Ideally this should be rewritten in lua with independent visibility if doable
            LuaConsole.Get().Draw();
    }
    catch (const std::exception & Ex)
    {
        std::string ExceptionInfo = fmt::format("Exception caught while drawing overlay gui: \"{}\". File: {}, Function: {}\n",
            Ex.what(), __FILE__, __FUNCSIG__);

        Logger::LogError("{}\n", ExceptionInfo);
    }
}

//Remove GUIs marked for deletion
void GuiManager::ProcessDeletions()
{
    GuiList.erase(std::remove_if(GuiList.begin(), GuiList.end(),
    [](BaseGui* gui)
    {
        return gui->MarkedForDeletion();
    }),
    GuiList.end());
}

void GuiManager::DrawPreInitWindow()
{
    ImGui::SetNextWindowSize(ImVec2(250.0f, 300.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Initialization not complete", &ShowPreInitWindow, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    ImGui::SetNextItemWidth(250.0f);
    ImGui::TextWrapped("RSL initialization currently requires a save game to be loaded to complete. Please load a save game to access the rest of the overlay.");

    if (ImGui::Button("Log RFG menu info"))
        Globals::LogGameMenuInfo();

    ImGui::SameLine();
    Gui::ShowHelpMarker("Logs information about the currently loaded game menus. Does not have much use currently. \
Mainly a debug feature I decided to leave in. Check the logger window or the master log for the output. I've included it in this \
preload menu so you could still access this feature before loading a save.");
    ImGui::End();
}

/* Toggles visibility of the lua console*/
void GuiManager::ToggleLuaConsole()
{
    LuaConsoleActive = !LuaConsoleActive;
    LuaConsole.Get().Toggle();
}

/* Returns true if the lua console is active/visible.*/
bool GuiManager::IsLuaConsoleActive() const
{
    return LuaConsoleActive;
}

/* Deactivates the lua console so it's no longer visible.*/
void GuiManager::DeactivateLuaConsole()
{
    LuaConsoleActive = false;
}

/* Activates the lua console so it's now visible.*/
void GuiManager::ActivateLuaConsole()
{
    LuaConsoleActive = true;
}

void GuiManager::AddChildGui(BaseGui* Gui, bool InitialVisibility)
{
    GuiList.push_back(Gui);
    GuiList.back()->Visible = InitialVisibility;
}

void GuiManager::SetLuaConsole(std::string Name)
{
    LuaConsole = GetGuiReference<OverlayConsole>("Lua console").value();
}
