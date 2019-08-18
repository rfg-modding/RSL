#pragma once
#include "BaseGui.h"
class EventViewerGui : public BaseGui
{
public:
    EventViewerGui(std::string Title_) { Title = Title_; }
    ~EventViewerGui() = default;

    void Draw() override;

    ImGuiWindowFlags WindowFlags = 0;
};

