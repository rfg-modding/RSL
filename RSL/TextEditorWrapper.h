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

    void RunCurrentScript();
    void ClearErrorMarkers();

    bool LoadScript(std::string FullPath, std::string NewScriptName);
    bool SaveScript();
    std::string FixScriptExtension(std::string CurrentScriptName);
    void ClearScript();

    void DrawNewScriptPopup();
    void DrawOpenScriptPopup();
    void DrawSaveScriptPopup();
    void DrawSaveAsScriptPopup();

    std::string GetCurrentScriptString();
    void LoadLanguageDefinitions();

    std::string ScriptName = "NewScript.lua";
    const std::string DefaultScriptName = "NewScript.lua";
    //ScriptManager* Scripts = nullptr;

    bool ShowNewScriptPopup = false;
    bool ShowOpenScriptPopup = false;
    bool ShowSaveScriptPopup = false;
    bool ShowSaveAsScriptPopup = false;

    std::string NewNameBuffer;

private:
    TextEditor Editor;
    nlohmann::json LanguageConfig;
};