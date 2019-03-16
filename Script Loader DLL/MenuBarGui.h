#pragma once
#include "BaseGui.h"

class MenuBarGui : public BaseGui
{
public:
	MenuBarGui(bool* _OpenState, std::string _Title);
	~MenuBarGui();

	void Draw();
	void ConfirmScriptLoaderDeactivation();
	void ShowAboutWindow(bool* p_open);

	ImGuiWindowFlags WindowFlags = 0;
};

