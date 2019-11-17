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

    void Show() { Visible = true; }
    void Hide() { Visible = false; }
    void Toggle() { Visible = !Visible; }
    [[nodiscard]] bool IsVisible() const { return Visible; }
    void Delete() { _markedForDeletion = true; }
    [[nodiscard]] bool MarkedForDeletion() const { return _markedForDeletion; }

    std::string Title;
    bool Visible = false;
    bool IndependentVisibility = false;

protected:
    BaseGui() { }

    bool _markedForDeletion = false;
};