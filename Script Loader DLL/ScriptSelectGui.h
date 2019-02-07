#pragma once
#include "OverlayConsole.h"

class ScriptManager;

class ScriptSelectGui
{
public:
	ScriptSelectGui();
	~ScriptSelectGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	ScriptManager* Scripts = nullptr;
	ImGuiWindowFlags WindowFlags = 0;

private:
	bool* OpenState = nullptr;
};

