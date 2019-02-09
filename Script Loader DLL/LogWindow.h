#pragma once
#include "Functions.h"

class ScriptManager;

class LogWindow
{
public:
	LogWindow();
	~LogWindow();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	ImGuiWindowFlags WindowFlags = 0;
	int ConsoleLogType = LogAll;
	int BufferDisplayLength = 1000;

private:
	bool* OpenState = nullptr;
	int BufferEnd = 0;
	int BufferCount = 0;
};

