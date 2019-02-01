#pragma once
#include "TextEditor.h"
//#include "Functions.h"
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
	ImGuiWindowFlags WindowFlags = 0;
	ScriptManager* Scripts;

	int ConsoleLogType = LogLua | LogError;
	int BufferDisplayLength = 100;
	std::string InputBuffer;

private:
	bool* OpenState;
};

