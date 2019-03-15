#pragma once
#include "BaseGui.h"

class ScriptManager;
class TextEditor;

class ScriptSelectGui
{
public:
	ScriptSelectGui();
	~ScriptSelectGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	ScriptManager* Scripts = nullptr;
	TextEditor* ScriptEditor = nullptr;
	bool* ScriptEditorState = nullptr;
	ImGuiWindowFlags WindowFlags = 0;

private:
	bool* OpenState = nullptr;
};

