#pragma once
#include "Functions.h"

class ScriptManager;

class MenuBarGui
{
public:
	MenuBarGui();
	~MenuBarGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	ScriptManager* Scripts = nullptr;
	ImGuiWindowFlags WindowFlags = 0;

private:
	bool* OpenState = nullptr;
};

