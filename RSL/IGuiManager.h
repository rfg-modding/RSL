#pragma once
#include "GuiReference.h"
#include "OverlayConsole.h"

class IGuiManager
{
public:
    IGuiManager(const IGuiManager&) = delete;
    IGuiManager& operator=(const IGuiManager&) = delete;
    virtual ~IGuiManager() noexcept = default;

    virtual void Initialize() = 0;
    [[nodiscard]] virtual bool Ready() = 0;

    virtual void Draw() = 0;
    virtual void DrawPreInitWindow() = 0;
    virtual void ToggleLuaConsole() = 0;
    [[nodiscard]] virtual bool IsLuaConsoleActive() const = 0;
    virtual void DeactivateLuaConsole() = 0;
    virtual void ActivateLuaConsole() = 0;
    virtual void AddChildGui(BaseGui* Gui, bool InitialVisibility = false) = 0;
    virtual void SetLuaConsole(std::string Name) = 0;

    template<typename T>
    std::optional<GuiReference<T>> GetGuiReference(const std::string& Name)
    {
        for (int i = 0; i < GuiList.size(); i++)
        {
            if (GuiList[i]->Title == Name)
            {
                return GuiReference<T>(i, &GuiList);
            }
        }
        return {};
    }

    GuiReference<OverlayConsole> LuaConsole;
    bool ShowPreInitWindow = true;
    bool ShowAppMetrics = false;
    bool ShowAppAbout = false;

protected:
    IGuiManager() = default;

    std::vector <BaseGui*> GuiList {};
};
