#pragma once
#include "BaseGui.h"

class LogWindow : public BaseGui
{
public:
	LogWindow(bool* _OpenState, std::string _Title);
	~LogWindow();

	void Draw();

	ImGuiWindowFlags WindowFlags = 0;
	int ConsoleLogType = LogAll;
	int BufferDisplayLength = 1000;
	bool AutoScroll = true;

private:
	int BufferEnd = 0;
	int BufferCount = 0;
};

