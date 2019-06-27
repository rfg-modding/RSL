#include "TextEditorWrapper.h"

TextEditorWrapper::TextEditorWrapper(bool* OpenState_, std::string Title_)
{
    OpenState = OpenState_;
    Title = Title_;

    MainOverlayWindowFlags = 0;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoTitleBar;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoScrollbar;
    MainOverlayWindowFlags |= ImGuiWindowFlags_MenuBar;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoMove;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoResize;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoCollapse;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoNav;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoBackground;
    //MainOverlayWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    auto Lang = TextEditor::LanguageDefinition::Lua();

    static const char* ppnames[] = { "NULL", "PM_REMOVE",
    "ZeroMemory", "DXGI_SWAP_EFFECT_DISCARD", "D3D_FEATURE_LEVEL", "D3D_DRIVER_TYPE_HARDWARE", "WINAPI","D3D11_SDK_VERSION", "assert" };
    // ... and their corresponding values
    static const char* ppvalues[] = {
        "#define NULL ((void*)0)",
        "#define PM_REMOVE (0x0001)",
        "Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ",
        "enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0",
        "enum D3D_FEATURE_LEVEL",
        "enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
        "#define WINAPI __stdcall",
        "#define D3D11_SDK_VERSION (7)",
        " #define assert(expression) (void)(                                                  \n"
        "    (!!(expression)) ||                                                              \n"
        "    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
        " )"
    };

    for (int i = 0; i < sizeof(ppnames) / sizeof(ppnames[0]); ++i)
    {
        TextEditor::Identifier id;
        id.mDeclaration = ppvalues[i];
        Lang.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
    }

    // set your own identifiers
    static const char* identifiers[] = {
        "HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
        "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
        "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
        "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor" };
    static const char* idecls[] =
    {
        "typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
        "typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
        "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
        "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
        "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor" };
    for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i)
    {
        TextEditor::Identifier id;
        id.mDeclaration = std::string(idecls[i]);
        Lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
    }
    Editor.SetLanguageDefinition(Lang);

    TextEditor::ErrorMarkers Markers;
    Markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
    Markers.insert(std::make_pair<int, std::string>(41, "Another example error"));
    Editor.SetErrorMarkers(Markers);

    //static 
    //	static const char* fileToEdit = "test.cpp";

    //{
    //    std::ifstream t(fileToEdit);
    //    if (t.good())
    //    {
    //        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    //        Editor.SetText(str);
    //    }
    //}
}

void TextEditorWrapper::Draw()
{
    if (!*OpenState)
    {
        return;
    }
    ImGui::SetNextWindowSize(ImVec2(800.0f, 500.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(Title.c_str(), OpenState, MainOverlayWindowFlags))
    {
        ImGui::End();
        return;
    }

    auto cpos = Editor.GetCursorPosition();
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save"))
            {
                auto textToSave = Editor.GetText();
                /// save text....
            }
            if (ImGui::MenuItem("Quit", "Alt-F4"))
            {
                //break;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            bool ro = Editor.IsReadOnly();
            if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                Editor.SetReadOnly(ro);
            ImGui::Separator();

            if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && Editor.CanUndo()))
                Editor.Undo();
            if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && Editor.CanRedo()))
                Editor.Redo();

            ImGui::Separator();

            if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, Editor.HasSelection()))
                Editor.Copy();
            if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && Editor.HasSelection()))
                Editor.Cut();
            if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && Editor.HasSelection()))
                Editor.Delete();
            if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                Editor.Paste();

            ImGui::Separator();

            if (ImGui::MenuItem("Select all", nullptr, nullptr))
                Editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(Editor.GetTotalLines(), 0));

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Dark palette"))
                Editor.SetPalette(TextEditor::GetDarkPalette());
            if (ImGui::MenuItem("Light palette"))
                Editor.SetPalette(TextEditor::GetLightPalette());
            if (ImGui::MenuItem("Retro blue palette"))
                Editor.SetPalette(TextEditor::GetRetroBluePalette());
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, Editor.GetTotalLines(),
        Editor.IsOverwrite() ? "Ovr" : "Ins",
        Editor.CanUndo() ? "*" : " ",
        Editor.GetLanguageDefinition().mName.c_str(), "meow.lua");

    Editor.Render("TextEditor");

    ImGui::End();
}