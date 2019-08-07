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
#include "ExplosionSpawnerGui.h"
#include "VehicleSpawnerGui.h"

//Todo: Add a name var to BaseGui and use that to find refs. That way people can have a constantly changing title and still reference a gui via it's name.
//Used to reference a Gui without needing to directly access the Gui std::vector and keep track of each guis index.
template <class T>
class GuiReference
{
public:
    GuiReference() {}
    GuiReference(int Index_, std::vector<BaseGui*>* List_) : Index(Index_), List(List_) { Ready = true; }

    void Set(int Index_, std::vector<BaseGui*>* List_)
    {
        Index = Index_;
        List = List_;
        Ready = true;
    }
    T& Get()
    {
        if(Ready)
        {
            return *reinterpret_cast<T*>(List->at(Index));
        }
    }
    void Clear()
    {
        Index = -1;
        List = nullptr;
        Ready = false;
    }
    bool IsReady() const
    {
        return Ready;
    }


    GuiReference& operator=(const GuiReference& other)
    {
        if (this == &other)
        {
            return *this;
        }
        Index = other.Index;
        List = other.List;
        Ready = other.Ready;
        return *this;
    }

private:
    int Index = -1; //Index of the gui on the GuiList
    std::vector<BaseGui*>* List = nullptr; //Pointer to the GuiList
    bool Ready = false;
};

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

	void Draw();

    void DrawPreInitWindow();

	void ToggleLuaConsole();
	bool IsLuaConsoleActive() const;
	void DeactivateLuaConsole();
	void ActivateLuaConsole();

    void AddChildGui(BaseGui* Gui, bool InitialVisibility = false);

    template<typename T>
    std::optional<GuiReference<T>> GetGuiReference(const std::string& Name)
    {
        for(int i = 0; i < GuiList.size(); i++)
        {
            if(GuiList[i]->Title == Name)
            {
                return GuiReference<T>(i, &GuiList);
            }
        }
        return {};
    }

    //Todo: Consider using a smart pointer for this to avoid any memory leak issues.
    std::vector <BaseGui*> GuiList;

	std::once_flag InitialDrawCheck;
	bool DrawPassedOnce = false;
    bool ShowPreInitWindow = true;

    GuiReference<OverlayConsole> LuaConsole;

    bool ShowAppMetrics = false;
    bool ShowAppAbout = false;

private:
	bool LuaConsoleActive = false;
	bool Initialized = false;
};