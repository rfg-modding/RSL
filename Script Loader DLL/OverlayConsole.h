#pragma once
#include "Functions.h"
//#include "imgui_stdlib.h"
//#include "IconsFontAwesome5.h"

class ScriptManager;

class OverlayConsole
{
public:
	OverlayConsole();
	~OverlayConsole();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	Player* PlayerPtr = nullptr;
	ImGuiWindowFlags MainOverlayWindowFlags = 0;
	ScriptManager* Scripts;

private:
	bool* OpenState;
};

