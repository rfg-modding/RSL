#pragma once
#include "BaseGui.h"
#include "IScriptManager.h"

class EventViewerGui : public BaseGui
{
public:
    EventViewerGui(std::string Title_);
    ~EventViewerGui() = default;

    void Draw() override;

private:
    std::shared_ptr<IScriptManager> ScriptManager = nullptr;
};

