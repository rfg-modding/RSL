#pragma once
#include "Functions.h"

class GuiSystem;
class ScriptManager;

class BaseGui
{
public:
	virtual ~BaseGui() {};
	virtual void Draw() = 0;
	
	std::string Title;

	Player* PlayerPtr = nullptr;
	GuiSystem* Gui = nullptr;
	ScriptManager* Scripts = nullptr;

protected:
	bool* OpenState = nullptr;
};