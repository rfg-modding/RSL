#pragma once
#include "BaseGui.h"
#include "ImGuiColorTextEdit/TextEditor.h"

class TextEditorWrapper : public BaseGui
{
public:
    TextEditorWrapper(bool* OpenState_, std::string Title_);
    ~TextEditorWrapper() = default;

    void Draw() override;

    ImGuiWindowFlags MainOverlayWindowFlags = 0;

private:
    TextEditor Editor;
};