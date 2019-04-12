#pragma once
#include "BaseGui.h"

class ScriptManager;

class OverlayConsole : public BaseGui
{
public:
	OverlayConsole(bool* _OpenState, std::string _Title);
	~OverlayConsole();

	void Draw();

	template <typename T> bool InputTextLambdaWrapper(const char* Label, std::string* Buffer, ImGuiInputTextFlags Flags = 0, T Callback = nullptr, void* UserData = nullptr);

	ImGuiWindowFlags WindowFlags = 0;

	int ConsoleLogType = LogAll;// LogLua | LogError;
	int BufferDisplayLength = 100;
	std::string InputBuffer;

	std::vector <std::string> CommandHistory;
	unsigned int HistoryPosition = 0;

	bool ReclaimFocus = true;
	bool Autoscroll = true;
	bool SimpleOutput = false;

private:
	int BufferEnd = 0;
	int BufferCount = 0;
};


