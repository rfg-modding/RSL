#pragma once
#include "BaseGui.h"
#include "IScriptManager.h"

class TextEditor;
class ScriptManager;

class ScriptSelectGui : public BaseGui
{
public:
    ScriptSelectGui(std::string Title_);
	~ScriptSelectGui() = default;

	void Draw() override;

	ImGuiWindowFlags WindowFlags = 0;

private:
    std::shared_ptr<IScriptManager> ScriptManager = nullptr;
};

