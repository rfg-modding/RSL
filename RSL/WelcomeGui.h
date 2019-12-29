#pragma once
#include "BaseGui.h"
#include "IGuiManager.h"

class WelcomeGui : public BaseGui
{
public:
	WelcomeGui(std::string Title_);
	~WelcomeGui() = default;

	void Draw() override;

private:
	ImGuiWindowFlags WindowFlags = 0;
    std::shared_ptr<IGuiManager> GuiManager = nullptr;
};
