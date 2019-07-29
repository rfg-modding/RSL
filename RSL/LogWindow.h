#pragma once
#include "BaseGui.h"

class LogWindow : public BaseGui
{
public:
	LogWindow(std::string Title_) { Title = Title_; }
	~LogWindow() = default;

	void Draw() override;

	ImGuiWindowFlags WindowFlags = 0;
	int ConsoleLogType = LogAll;
	int BufferDisplayLength = 1000;
	bool AutoScroll = true;

private:
	int BufferEnd = 0;
	int BufferCount = 0;
};

