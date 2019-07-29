#pragma once
#include "BaseGui.h"

class TextEditor;
class ScriptManager;

class ScriptSelectGui : public BaseGui
{
public:
	ScriptSelectGui(std::string Title_) { Title = Title_; }
	~ScriptSelectGui() = default;

	void Draw() override;

	ImGuiWindowFlags WindowFlags = 0;
};

