#pragma once
#include "IGuiManager.h"

class GuiManager : public IGuiManager
{
public:
    GuiManager() { }
    ~GuiManager();

    void Initialize() override;
    [[nodiscard]] bool Ready() override;

    void Draw() override;
    void DrawPreInitWindow() override;
    void ToggleLuaConsole() override;
    [[nodiscard]] bool IsLuaConsoleActive() const override;
    void DeactivateLuaConsole() override;
    void ActivateLuaConsole() override;
    void AddChildGui(BaseGui* Gui, bool InitialVisibility) override;
    void SetLuaConsole(std::string Name) override;

private:
    std::once_flag InitialDrawCheck;
    bool DrawPassedOnce = false;
    bool LuaConsoleActive = false;
    bool Initialized = false;
};

