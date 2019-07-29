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

    void Show() { Visible = true; }
    void Hide() { Visible = false; }
    void Toggle() { Visible = !Visible; }
    bool IsVisible() const { return Visible; }

	bool Visible = false;
};