#pragma once
#include "BaseGui.h"

class LogWindow : public BaseGui
{
public:
	LogWindow(std::string Title_) { Title = Title_; }
	~LogWindow() = default;

	void Draw() override;

private:
	int ConsoleLogType = LogAll;
	int BufferDisplayLength = 1000;
	bool AutoScroll = true;
};

