#pragma once
#include "BaseGui.h"

class TextEditor;
class ScriptManager;

class ScriptSelectGui : public BaseGui
{
public:
	ScriptSelectGui(bool* OpenState_, std::string Title_) {OpenState = OpenState_; Title = Title_; }
	~ScriptSelectGui() = default;

	void Draw() override;

	ImGuiWindowFlags WindowFlags = 0;
};

