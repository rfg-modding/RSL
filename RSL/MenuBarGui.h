#pragma once
#include "BaseGui.h"

class MenuBarGui : public BaseGui
{
public:
	MenuBarGui(std::string Title_);
	~MenuBarGui() = default;

	void Draw() override;
	void ConfirmScriptLoaderDeactivation() const;
	void ConfirmLockoutModeActivation();

    void ActivateLockoutMode();
	void ShowAboutWindow(bool* p_open) const;

	ImGuiWindowFlags WindowFlags = 0;
};

