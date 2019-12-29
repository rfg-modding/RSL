#pragma once
#include "BaseGui.h"
#include "IScriptManager.h"
#include "IGuiManager.h"

class TextEditor;
class ScriptManager;

class ScriptSelectGui : public BaseGui
{
public:
    ScriptSelectGui(std::string Title_);
	~ScriptSelectGui() = default;

	void Draw() override;

private:
    std::shared_ptr<IScriptManager> ScriptManager = nullptr;
    std::shared_ptr<IGuiManager> GuiManager = nullptr;
};

