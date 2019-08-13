#pragma once
#include "BaseGui.h"

class GraphicsTweaksGui : public BaseGui
{
public:
    GraphicsTweaksGui(std::string Title_);
    ~GraphicsTweaksGui() = default;

    void Draw() override;
};
