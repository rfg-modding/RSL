#pragma once
#include "BaseGui.h"
#include <ImGuiColorTextEdit/TextEditor.h>

class FileBrowserNode
{
public:
    FileBrowserNode() = default;
    FileBrowserNode(const std::filesystem::path& Path_) : Path(Path_) {}
    ~FileBrowserNode() { Children.clear(); }

    //Sort children so that folders are before files
    void SortChildren()
    {
        std::partition(std::begin(Children), std::end(Children), [](FileBrowserNode& Child) { return Child.IsFolder; });
    }

    std::vector<FileBrowserNode> Children;

    std::filesystem::path Path;

    bool IsSelected = false;
    bool IsOpen = false;
    bool IsFolder = false; //Is a file if true and a folder if false.
    bool IsEmpty = true;

    int Index = 0;

    std::string Label = {};

    ImGuiTreeNodeFlags Flags = 0;
};

class TextEditorWrapper : public BaseGui
{
public:
    TextEditorWrapper(std::string Title_);
    ~TextEditorWrapper() = default;

    void Draw() override;

    void DrawMenuBar();
    void DrawToolbar();

    void UpdateFileBrowser();

    void DrawFileBrowserNodes();
    void DrawFileBrowserNode(FileBrowserNode& Node);

    void GenerateFileBrowserNodes();
    void GenerateFileBrowserNode(FileBrowserNode& Node);

    void TryOpenBrowserNode(FileBrowserNode& Node);
    [[nodiscard]] bool ScriptBeenEdited() const;

    ImGuiWindowFlags MainOverlayWindowFlags = 0;

    void RunCurrentScript();
    void ClearErrorMarkers();

    bool LoadScript(std::string FullPath, std::string NewScriptName);
    bool SaveScript();
    std::string FixScriptExtension(std::string CurrentScriptName);
    void ClearScript();

    void ProcessPopups();
    void DrawNewScriptPopup();
    void DrawOpenScriptPopup();
    void DrawSaveAsScriptPopup();
    void DrawConfirmSaveChangesPopup();

    std::string GetCurrentScriptString();
    void LoadLanguageDefinitions();

    std::string ScriptName = "NewScript.lua";
    std::string ScriptPath;
    const std::string DefaultScriptName = "NewScript.lua";
    //ScriptManager* Scripts = nullptr;

    bool ShowNewScriptPopup = false;
    bool ShowOpenScriptPopup = false;
    bool ShowSaveScriptPopup = false;
    bool ShowSaveAsScriptPopup = false;
    bool ShowConfirmSaveChangesPopup = false;

    std::string NewNameBuffer;

private:
    TextEditor Editor;
    nlohmann::json LanguageConfig;

    int NodeIndex = 0;
    int SelectedIndex = -1;
    FileBrowserNode FileBrowserRootNode;

    std::string InitialScript;
    FileBrowserNode* PendingOpenNode = nullptr;

    std::chrono::steady_clock::time_point LastFileBrowserGeneration;

    long long BrowserUpdatePeriodMs = 3000; //Time between updating the file browser tree nodes

    bool DrawnOnce = false;
    float DefaultFileBrowserColumnWidthPercentage = 0.3f;

    std::string PathBuffer; //Used as buffer for path input in save as popup
};