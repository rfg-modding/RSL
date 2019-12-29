#include "TextEditorWrapper.h"
#include <utility>

TextEditorWrapper::TextEditorWrapper(std::string Title_)
{
    Title = std::move(Title_);

    ScriptManager = IocContainer->resolve<IScriptManager>();

    MainOverlayWindowFlags |= ImGuiWindowFlags_MenuBar;

    LoadLanguageDefinitions();
    GenerateFileBrowserNodes();
    Logger::Log("Generated file browser nodes for the first time.\n");
    LastFileBrowserGeneration = std::chrono::steady_clock::now();
    ScriptPath = Globals::GetEXEPath() + "RSL//Scripts//Default//" + ScriptName;
}

void TextEditorWrapper::Draw()
{
    if (!Visible)
    {
        return;
    }
    ImGui::SetNextWindowSize(ImVec2(800.0f, 500.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(Title.c_str(), &Visible, MainOverlayWindowFlags))
    {
        ImGui::End();
        return;
    }

    DrawMenuBar();
    DrawToolbar();
    ImGui::Separator();

    ImGui::Columns(2);
    if(!DrawnOnce)
    {
        //Set initial file explorer column width.
        ImGui::SetColumnWidth(0, DefaultFileBrowserColumnWidthPercentage * ImGui::GetWindowContentRegionWidth());
        DrawnOnce = true;
    }

    ImGui::BeginChild("File explorer");

    ImGui::Text("File explorer");
    ImGui::Separator();

    UpdateFileBrowser();
    DrawFileBrowserNodes();

    ImGui::EndChild();

    ImGui::NextColumn();
    ImGui::BeginChild("Editor");
    Editor.Render("TextEditor");
    ImGui::EndChild();

    ImGui::Columns(1);

    ProcessPopups();

    ImGui::End();
}

void TextEditorWrapper::DrawMenuBar()
{
    if (!ImGui::BeginMenuBar())
        return;

    if (ImGui::BeginMenu(std::string(std::string(ICON_FA_FILE) + u8" File##ScriptEditor").c_str()))
    {
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_PLUS) + u8" New").c_str(), "Ctrl+N")) { ShowNewScriptPopup = true; }
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_FILE_IMPORT) + u8" Open").c_str(), "Ctrl+O")) { ShowOpenScriptPopup = true; }
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_FILE_EXPORT) + u8" Save").c_str(), "Ctrl+S")) { SaveScript(); }//ShowSaveScriptPopup = true; }
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_FILE_SIGNATURE) + u8" Save as").c_str(), "Ctrl+Shift+S")) { ShowSaveAsScriptPopup = true; }

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu(std::string(std::string(ICON_FA_EDIT) + u8" Edit##ScriptEditor").c_str()))
    {
        //if (ImGui::MenuItem("Go to")) {TextEditor::SetCursorPosition(Te)}
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_UNDO_ALT) + u8" Undo").c_str(), "Ctrl+Z", nullptr, Editor.CanUndo()))
            Editor.Undo();
        //Check can undo and pick color depending on that.
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_REDO_ALT) + u8" Redo").c_str(), "Ctrl+Y", nullptr, Editor.CanRedo()))
            Editor.Redo();

        ImGui::Separator();
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_CUT) + u8" Cut").c_str(), "Ctrl+X", nullptr, Editor.HasSelection()))
            Editor.Cut();
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_COPY) + u8" Copy").c_str(), "Ctrl+C", nullptr, Editor.HasSelection()))
            Editor.Copy();
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_PASTE) + u8" Paste").c_str(), "Ctrl+V", nullptr, ImGui::GetClipboardText() != nullptr))
            Editor.Paste();
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_TIMES) + u8" Delete").c_str(), "", nullptr, Editor.HasSelection()))
            Editor.Delete();

        ImGui::Separator();
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_HIGHLIGHTER) + u8" Select all").c_str(), "Ctrl+A"))
            Editor.SelectAll();

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu(std::string(std::string(ICON_FA_EYE) + u8" View##ScriptEditor").c_str()))
    {
        if (ImGui::MenuItem("Dark palette"))
            Editor.SetPalette(TextEditor::GetDarkPalette());
        if (ImGui::MenuItem("Light palette"))
            Editor.SetPalette(TextEditor::GetLightPalette());
        if (ImGui::MenuItem("Retro blue palette"))
            Editor.SetPalette(TextEditor::GetRetroBluePalette());

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu(std::string(std::string(ICON_FA_FLASK) + u8" Test##ScriptEditor").c_str())) //ICON_FA_VIAL
    {
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_PLAY) + u8" Run").c_str(), "F5"))
            RunCurrentScript();
        //if (ImGui::MenuItem(std::string(std::string(ICON_FA_STOP) + u8" Stop").c_str()))
        //{

        //}
        ////Todo: Add menu to view attached events or other info about the current script if it's running.

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu(std::string(std::string(ICON_FA_COGS) + u8" Settings##ScriptEditor").c_str()))
    {
        if (ImGui::MenuItem(std::string(std::string(ICON_FA_LANGUAGE) + u8" Reload language definitions").c_str()))
            LoadLanguageDefinitions();

        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
}

void TextEditorWrapper::DrawToolbar()
{
    auto cursorPos = Editor.GetCursorPosition();
    static auto DisabledUndoRedoColor = ImVec4(0.165f, 0.29f, 0.47f, 1.0f);
    static auto EnabledUndoRedoColor = ImVec4(0.478f, 0.753f, 1.0f, 1.0f);
    static auto EnabledRunColor = ImVec4(0.556f, 0.823f, 0.541f, 1.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
    ImGui::PushStyleColor(ImGuiCol_Text, Editor.CanUndo() ? EnabledUndoRedoColor : DisabledUndoRedoColor);
    if (ImGui::Button(std::string(std::string(ICON_FA_UNDO_ALT) + u8"##ToolbarUndo").c_str()))
        Editor.Undo();

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Text, Editor.CanRedo() ? EnabledUndoRedoColor : DisabledUndoRedoColor);
    if (ImGui::Button(std::string(std::string(ICON_FA_REDO_ALT) + u8"##ToolbarRedo").c_str()))
        Editor.Redo();

    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Text, EnabledRunColor);
    if (ImGui::Button(std::string(std::string(ICON_FA_PLAY) + u8"##ToolbarRun").c_str()))
        RunCurrentScript();

    ImGui::SameLine();
    ImGui::PopStyleColor(6);
    ImGui::PopStyleVar();
    ImGui::Text("| Line %d | Column %d | %d lines | %s | %s", cursorPos.mLine + 1, cursorPos.mColumn + 1, Editor.GetTotalLines(),
        Editor.IsOverwrite() ? "Ovr" : "Ins",
        ScriptName.c_str());
}

void TextEditorWrapper::UpdateFileBrowser()
{
    auto CurrentTime = std::chrono::steady_clock::now();
    long long TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - LastFileBrowserGeneration).count();
    if (TimeElapsed > BrowserUpdatePeriodMs && !FileTreeLocked)
    {
        GenerateFileBrowserNodes();
        LastFileBrowserGeneration = std::chrono::steady_clock::now();
    }
}

void TextEditorWrapper::DrawFileBrowserNodes()
{
    for(auto& Node : FileBrowserRootNode.Children)
        DrawFileBrowserNode(Node);
}

void TextEditorWrapper::DrawFileBrowserNode(FileBrowserNode& Node) //const std::filesystem::path& NodePath
{
    Node.IsSelected = Node.Index == SelectedIndex;
    if(Node.IsEmpty && Node.IsFolder)
        return;

    bool NodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)Node.Index, Node.Flags | Node.IsSelected, Node.Label.c_str());
    if(ImGui::IsItemClicked())
    {
        TryOpenBrowserNode(Node);
        SelectedIndex = Node.Index;
    }
    if (NodeOpen && Node.IsFolder)
    {
        for (auto& ChildNode : Node.Children)
            DrawFileBrowserNode(ChildNode);

        ImGui::TreePop();
    }
}

void TextEditorWrapper::GenerateFileBrowserNodes()
{
    NodeIndex = 0;
    FileBrowserRootNode.IsFolder = true;
    FileBrowserRootNode.Path = std::filesystem::path(Globals::GetEXEPath() + "RSL\\Scripts");
    FileBrowserRootNode.Children.clear();
    FileBrowserRootNode.Index = NodeIndex++;
    GenerateFileBrowserNode(FileBrowserRootNode);
}

void TextEditorWrapper::GenerateFileBrowserNode(FileBrowserNode& Node)
{
    if (is_directory(Node.Path))
    {
        Node.IsFolder = true;
        if(is_empty(Node.Path))
            return;

        Node.Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        Node.IsEmpty = false;
        Node.Label = Node.Path.stem().string();
        for (const auto& Entry : std::filesystem::directory_iterator(Node.Path))
        {
            FileBrowserNode ChildNode(Entry.path());
            GenerateFileBrowserNode(ChildNode);
            Node.Children.push_back(ChildNode);
            Node.Index = NodeIndex++;
        }
        Node.SortChildren();
    }
    else
    {
        Node.Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        Node.Label = std::string(ICON_FA_ALIGN_LEFT) + " " + Node.Path.filename().string();
        Node.Index = NodeIndex++;
    }
}

void TextEditorWrapper::TryOpenBrowserNode(FileBrowserNode& Node)
{
    if(Node.IsFolder)
        return;

    LockFileTree(); //Lock file tree so folder scan doesn't edit it while it's being used
    if(ScriptBeenEdited())
    {
        //Script has been edited. Ask player if they'd like to save it.
        PendingOpenNode = &Node;
        ShowConfirmSaveChangesPopup = true;
    }
    else
    {
        //Script not edited, just save it and unlock tree
        LoadScript(Node.Path.string(), Node.Path.stem().string());
        UnlockFileTree();
    }
}

//Check if the script has been edited since the last save/load/clear/new/etc
bool TextEditorWrapper::ScriptBeenEdited() const
{
    return (InitialScript + "\n") != Editor.GetText();
}

void TextEditorWrapper::RunCurrentScript()
{
    ScriptResult Result = ScriptManager->RunScript(Editor.GetText(), ScriptName);

    //Insert markers if the script fails and we have the error line number
    TextEditor::ErrorMarkers Markers;
    if(Result.Failed && Result.ErrorLineNumber)
        Markers.insert(std::make_pair<int, std::string>(static_cast<int>(Result.ErrorLineNumber.value()), Result.ErrorString.c_str()));

    Editor.SetErrorMarkers(Markers);
}

void TextEditorWrapper::ClearErrorMarkers()
{
    Editor.SetErrorMarkers(TextEditor::ErrorMarkers());
}

bool TextEditorWrapper::LoadScript(std::string FullPath, std::string NewScriptName)
{
    bool Successful = true;
    try
    {
        std::ifstream ScriptStream;
        ScriptStream.exceptions(std::ios::failbit | std::ios::badbit);
        ScriptStream.open(FullPath);
        std::string ScriptString((std::istreambuf_iterator<char>(ScriptStream)), std::istreambuf_iterator<char>());

        ScriptName = NewScriptName;
        ScriptPath = FullPath;
        Editor.SetText(ScriptString);
        ImGui::CloseCurrentPopup();
        ClearErrorMarkers();

        InitialScript = ScriptString;
    }
    catch (std::exception& Ex)
    {
        Successful = false;
        std::string ExceptionInfo = fmt::format("Exception caught while loading script: \"{}\". Path: \"{}\". File: {}, Function: {}\n",
            Ex.what(), FullPath, __FILE__, __FUNCSIG__);

        Logger::LogError("{}\n", ExceptionInfo);
        MessageBoxA(Globals::FindRfgTopWindow(), ExceptionInfo.c_str(), "Failed to load script!", MB_OK);
    }

    return Successful;
}

bool TextEditorWrapper::SaveScript()
{
    bool Successful = true;
    try
    {
        //Ensure output path exists and get script string
        Path::CreatePath(Path::GetParentDirectory(ScriptPath));
        const std::string scriptString = Editor.GetText();

        //Open output stream
        std::ofstream scriptStream;
        scriptStream.exceptions(std::ios::failbit | std::ios::badbit);
        scriptStream.open(ScriptPath, std::ios_base::trunc | std::ios_base::out);

        //Write script, rescan scripts folder for new files
        scriptStream << scriptString;
        scriptStream.close();
        ScriptManager->ScanScriptsFolder();

        InitialScript = scriptString;
    }
    catch (std::exception& Ex)
    {
        Successful = false;
        std::string ExceptionInfo = fmt::format("Exception caught while saving script: \"{}\". Path: \"{}\". File: {}, Function: {}\n", 
            Ex.what(), ScriptPath, __FILE__, __FUNCSIG__);

        Logger::LogError("{}\n", ExceptionInfo);
        MessageBoxA(Globals::FindRfgTopWindow(), ExceptionInfo.c_str(), "Failed to save script!", MB_OK);
    }

    return Successful;
}

std::string TextEditorWrapper::FixScriptExtension(std::string CurrentScriptName) const
{
    if (Path::GetExtension(CurrentScriptName) != ".lua")
        CurrentScriptName.append(".lua");

    return CurrentScriptName;
}

void TextEditorWrapper::ClearScript()
{
    Editor.SetText("");
    InitialScript = "";
    ScriptName = "NewScript.lua";
    ScriptPath = Globals::GetEXEPath() + "RSL//Scripts//Default//NewScript.lua";
    while (fs::exists(Globals::GetEXEPath(false) + "RSL/Scripts/" + ScriptName))
        ScriptName = "NewScript" + std::to_string(time(nullptr)) + ".lua";

    ClearErrorMarkers();
}

void TextEditorWrapper::ProcessPopups()
{
    if (ShowNewScriptPopup)
    {
        if(ScriptBeenEdited())
            ImGui::OpenPopup("New script"); //Asks the user if they want to discard or save the current script.
        else
            ClearScript(); //If the script hasn't been edited since the last save the just clear it without asking.

        ShowNewScriptPopup = false;
    }
    if (ShowOpenScriptPopup)
    {
        ImGui::OpenPopup("Open script");
        ShowOpenScriptPopup = false;
    }
    if (ShowSaveScriptPopup)
    {
        ImGui::OpenPopup("Save script");
        ShowSaveScriptPopup = false;
    }
    if (ShowSaveAsScriptPopup)
    {
        //Todo: Make a less gross way of passing this data to the Save as popup
        PathBuffer = Path::GetParentDirectory(ScriptPath); 
        NewNameBuffer = ScriptName;
        ImGui::OpenPopup("Save as");
        ShowSaveAsScriptPopup = false;
    }
    if(ShowConfirmSaveChangesPopup)
    {
        ImGui::OpenPopup("Save changes");
        ShowConfirmSaveChangesPopup = false;
    }
    DrawNewScriptPopup();
    DrawOpenScriptPopup();
    DrawSaveAsScriptPopup();
    DrawConfirmSaveChangesPopup();
}

void TextEditorWrapper::DrawNewScriptPopup()
{
    static bool ShouldOpenOverwriteConfirmationDialog = false;
    static bool ShouldCancelNewScript = false;
    if (!ImGui::BeginPopup("New script"))
        return;

    ImGui::Text("Would you like to save your current script?");
    if (ImGui::Button("Yes"))
    {
        if (fs::exists(ScriptPath))
            ShouldOpenOverwriteConfirmationDialog = true;
        else
        {
            ScriptName = FixScriptExtension(ScriptName);
            SaveScript();
            ClearScript();
            ImGui::CloseCurrentPopup();
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("No"))
    {
        ClearScript();
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
    {
        ImGui::CloseCurrentPopup();
    }
    if (ShouldOpenOverwriteConfirmationDialog)
    {
        ImGui::OpenPopup("NewScriptOverwriteConfirmation");
        ShouldOpenOverwriteConfirmationDialog = false;
    }
    if (ImGui::BeginPopup("NewScriptOverwriteConfirmation"))
    {
        ImGui::SetNextItemWidth(400.0f);
        ImGui::TextWrapped(std::string(FixScriptExtension(ScriptName) + " already exists. Are you sure you would like to overwrite it?").c_str());
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.972f, 0.545f, 0.462f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.000f, 0.545f, 0.462f, 1.0f));
        if (ImGui::Button("Overwrite##NewScriptOverwriteConfirmPopup"))
        {
            ScriptName = FixScriptExtension(ScriptName);
            SaveScript();
            ClearScript();
            ShouldCancelNewScript = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        if (ImGui::Button("Cancel##NewScriptOverwriteConfirmPopup"))
        {
            ShouldCancelNewScript = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    if (ShouldCancelNewScript)
    {
        ShouldCancelNewScript = false;
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
}

void TextEditorWrapper::DrawOpenScriptPopup()
{
    static bool OpenConfirmDeletePopup = false;
    static std::string ScriptToDelete = "";
    static std::string ScriptToDeleteFullPath = "";
    ImGui::SetNextWindowSize(ImVec2(280.0f, 0.0f));
    if (!ImGui::BeginPopup("Open script"))//, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    if (ImGui::Button("Rescan"))
        ScriptManager->ScanScriptsFolder();

    for (const auto& SubFolder : ScriptManager->GetSubFolders())
    {
        if(!ImGui::TreeNode(SubFolder.Name.c_str()))
        {
            //ImGui::TreePop();
            continue;
        }

        ImGui::Columns(2);
        for (const auto& Script : SubFolder.Scripts)
        {
            ImGui::Text("\t%s", Script.Name.c_str());
            ImGui::SameLine();
            ImGui::NextColumn();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
            if (ImGui::Button(fmt::format("{}##OpenEdit{}", ICON_FA_EDIT, Script.FullPath)))
                LoadScript(Script.FullPath, Script.Name);

            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
            if (ImGui::Button(fmt::format("{}##OpenDelete{}", ICON_FA_TRASH, Script.FullPath)))
            {
                ScriptToDelete = Script.Name;
                ScriptToDeleteFullPath = Script.FullPath;
                OpenConfirmDeletePopup = true;
            }
            ImGui::PopStyleColor(4);
            ImGui::NextColumn();
        }
        ImGui::TreePop();
        ImGui::Columns();
    }
    if (OpenConfirmDeletePopup)
    {
        ImGui::OpenPopup("Delete file?");
        OpenConfirmDeletePopup = false;
    }
    if (ImGui::BeginPopup("Delete file?"))
    {
        ImGui::SetNextItemWidth(400.0f);
        ImGui::TextWrapped("Are you sure you would like to delete %s?", ScriptToDelete.c_str());
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.972f, 0.545f, 0.462f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.000f, 0.545f, 0.462f, 1.0f));
        if (ImGui::Button("Delete##DeleteConfirmPopup"))
        {
            fs::remove(ScriptToDeleteFullPath);
            ScriptManager->ScanScriptsFolder();
            ImGui::CloseCurrentPopup();
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        if (ImGui::Button("Cancel##DeleteConfirmPopup"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
    ImGui::EndPopup();
}

void TextEditorWrapper::DrawSaveAsScriptPopup()
{
    static bool ShouldOpenOverwritePopup = false;
    static bool ShouldCloseMainPopup = false;
    if (ImGui::BeginPopup("Save as"))
    {
        ImGui::SetNextItemWidth(300.0f);
        ImGui::TextWrapped("Please enter the new script file name. The .lua extension will be automatically added if you forget it.");
        ImGui::InputText("##File path", &PathBuffer);
        ImGui::SameLine();
        ImGui::InputText("##File name", &NewNameBuffer);

        if (ImGui::Button("Save"))
        {
            std::string FinalScriptName = FixScriptExtension(NewNameBuffer);
            if (fs::exists(PathBuffer + FinalScriptName))
                ShouldOpenOverwritePopup = true;
            else
            {
                ScriptPath = PathBuffer + FinalScriptName;
                ScriptName = NewNameBuffer;
                SaveScript();
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();

        if (ShouldOpenOverwritePopup)
        {
            ImGui::OpenPopup("Overwrite script?");
            ShouldOpenOverwritePopup = false;
        }
        if (ImGui::BeginPopup("Overwrite script?"))
        {
            ImGui::SetNextItemWidth(400.0f);
            ImGui::TextWrapped(std::string("Are you sure you would like to overwrite " + FixScriptExtension(NewNameBuffer) + "?").c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.952f, 0.545f, 0.462f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.972f, 0.545f, 0.462f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.000f, 0.545f, 0.462f, 1.0f));
            if (ImGui::Button("Overwrite##OverwriteConfirmPopup"))
            {
                ScriptName = NewNameBuffer;
                SaveScript();
                ShouldCloseMainPopup = true;
                ImGui::CloseCurrentPopup();
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            if (ImGui::Button("Cancel##OverwriteConfirmPopup"))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }
        if(ShouldCloseMainPopup)
        {
            ShouldCloseMainPopup = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void TextEditorWrapper::DrawConfirmSaveChangesPopup()
{
    if(ImGui::BeginPopup("Save changes"))
    {
        ImGui::Text("Would you like to save your current script?");
        if(ImGui::Button("Yes"))
        {
            auto& Path = PendingOpenNode->Path;
            SaveScript();
            LoadScript(PendingOpenNode->Path.string(), PendingOpenNode->Path.stem().string());
            PendingOpenNode = nullptr;
            UnlockFileTree();
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("No"))
        {
            LoadScript(PendingOpenNode->Path.string(), PendingOpenNode->Path.stem().string());
            PendingOpenNode = nullptr;
            UnlockFileTree();
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("Cancel"))
        {
            PendingOpenNode = nullptr;
            UnlockFileTree();
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

std::string TextEditorWrapper::GetCurrentScriptString() const
{
    return Editor.GetText();
}

void TextEditorWrapper::LoadLanguageDefinitions()
{
    LanguageConfig.clear();
    auto Lang = TextEditor::LanguageDefinition::Lua();

    std::string ExePath = Globals::GetEXEPath(false);
    Logger::Log("Started loading \"LanguageConfig.json\".\n");

    // Load and parse LanguageConfig.json
    if (fs::exists(ExePath + "RSL/Settings/LanguageConfig.json"))
    {
        if (JsonExceptionHandler([&]
           {
               Logger::Log("Parsing \"LanguageConfig.json\".\n");
               std::ifstream Config(ExePath + "RSL/Settings/LanguageConfig.json");
               Config >> LanguageConfig;
               Config.close();
               return true;
           }, "LanguageConfig.json", "parse", "parsing"))
        {
            Logger::Log("No parse exceptions detected for \"LanguageConfig.json\".\n");
        }
    }
    // Read values from LanguageConfig.json and use them to setup syntax highlighting and type tooltips.
    if (JsonExceptionHandler([&]
       {    
            // For now only look for lua defs. Doing it this way opens the door to other langs in the future with no format changes.
            auto& PreprocessorValues = LanguageConfig["Lua"]["PreprocessorValues"];
            auto& Identifiers = LanguageConfig["Lua"]["Identifiers"];
            
            for (auto& i : PreprocessorValues)
            {
                auto Name = i["Name"].get<std::string>();
                auto Description = i["Description"].get<std::string>();

                TextEditor::Identifier Id;
                Id.mDeclaration = Description;
                Lang.mPreprocIdentifiers.insert(std::make_pair(Name, Id));
            }
            for(auto& i : Identifiers)
            {
                auto Name = i["Name"].get<std::string>();
                auto Description = i["Description"].get<std::string>();

                TextEditor::Identifier Id;
                Id.mDeclaration = Description;
                Lang.mIdentifiers.insert(std::make_pair(Name, Id));
            }
            return true;
       }, "LanguageConfig.json", "read", "reading"))
    {
        Logger::Log("No read exceptions detected for \"LanguageConfig.json\".\n");
    }
    Logger::Log("Done loading \"LanguageConfig.json\".\n");

    Editor.SetLanguageDefinition(Lang);
}