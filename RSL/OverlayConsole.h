#pragma once
#include "BaseGui.h"
#include "IScriptManager.h"

class ScriptManager;

class OverlayConsole : public BaseGui
{
public:
	OverlayConsole(std::string Title_);
	~OverlayConsole() = default;

	void Draw() override;
	template <typename T> bool InputTextLambdaWrapper(const char* Label, std::string* Buffer, ImGuiInputTextFlags Flags = 0, T Callback = nullptr, void* UserData = nullptr);

	ImGuiWindowFlags WindowFlags = 0;
	int ConsoleLogType = LogAll;
	int BufferDisplayLength = 100;
	std::string InputBuffer;
	std::vector <std::string> CommandHistory;
	unsigned int HistoryPosition = 0;
	bool ReclaimFocus = true;

private:
    std::shared_ptr<IScriptManager> ScriptManager = nullptr;
	bool Autoscroll = true;
	bool SimpleOutput = false;
    int BufferEnd = 0;
};


