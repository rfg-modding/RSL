#pragma once
#include "BaseGui.h"

class TextEditor;
class ScriptManager;

class ScriptSelectGui : public BaseGui
{
public:
	ScriptSelectGui(bool* _OpenState, std::string _Title);
	~ScriptSelectGui();

	void Draw();

	ImGuiWindowFlags WindowFlags = 0;
};

