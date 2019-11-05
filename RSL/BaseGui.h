#pragma once
#include "Functions.h"

class BaseGui
{
public:
    //Disable copying by deleting the copy constructor and copy assignment constructor to avoid derived class slicing
    BaseGui(BaseGui const&) = delete;
    BaseGui& operator=(BaseGui const&) = delete;
    virtual ~BaseGui() { }
    virtual void Draw() = 0;

    std::string Title;

    void Show() { Visible = true; }
    void Hide() { Visible = false; }
    void Toggle() { Visible = !Visible; }
    [[nodiscard]] bool IsVisible() const { return Visible; }

    bool Visible = false;

protected:
    BaseGui() { }
};