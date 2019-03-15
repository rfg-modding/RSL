#pragma once
#include "BaseGui.h"

class ScriptManager;

class OverlayConsole
{
public:
	OverlayConsole();
	~OverlayConsole();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	template <typename T> bool InputTextLambdaWrapper(const char* Label, std::string* Buffer, ImGuiInputTextFlags Flags = 0, T Callback = nullptr, void* UserData = nullptr);

	Player* PlayerPtr = nullptr;
	ImGuiWindowFlags WindowFlags = 0;
	ScriptManager* Scripts = nullptr;

	int ConsoleLogType = LogAll;// LogLua | LogError;
	int BufferDisplayLength = 100;
	std::string InputBuffer;

	std::vector <std::string> CommandHistory;
	unsigned int HistoryPosition = 0;

	bool ReclaimFocus = true;
	bool Autoscroll = true;

private:
	bool* OpenState = nullptr;
	int BufferEnd = 0;
	int BufferCount = 0;
};


