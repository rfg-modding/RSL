#pragma once
#include "Functions.h"

class BaseGui
{
public:
	virtual ~BaseGui() {};
	virtual void Draw();
	
	std::string Title;

    void Show() { Visible = true; }
    void Hide() { Visible = false; }
    void Toggle() { Visible = !Visible; }
    [[nodiscard]] bool IsVisible() const { return Visible; }

	bool Visible = false;
};