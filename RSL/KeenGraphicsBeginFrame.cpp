#include "Hooks.h"
#include "Application.h"

bool ReadyForD3D11Init(keen::GraphicsSystem* pGraphicsSystem);
void InitImGuiD3D11();

keen::GraphicsCommandBuffer* Hooks::KeenGraphicsBeginFrameHook(keen::GraphicsSystem* pGraphicsSystem, keen::RenderSwapChain* pSwapChain)
{
    //static std::once_flag KeenGraphicsBeginFrameHookInitialCall;
    //std::call_once(KeenGraphicsBeginFrameHookInitialCall, [&]()
    //{
    //    Globals::KeenGraphicsSystemPtr = pGraphicsSystem;
    //});
    if (Globals::KeenGraphicsSystemPtr != pGraphicsSystem)
    {
        Logger::LogWarning("Globals::KeenGraphicsSystemPtr changed!\n");
        Globals::KeenGraphicsSystemPtr = pGraphicsSystem;
    }
    //Grab required D3D11 pointers for rendering and set up imgui.
    if(!Globals::ImGuiInitialized)
    {
        if(ReadyForD3D11Init(pGraphicsSystem))
        {
            Globals::GraphicsSystemPtr = pGraphicsSystem;
            Globals::D3D11Device = pGraphicsSystem->pDevice;
            Globals::D3D11Context = pGraphicsSystem->pImmediateContext;
            Globals::D3D11SwapchainPtr = pGraphicsSystem->pDefaultSwapChain->pSwapChain;

            ID3D11Texture2D* BackBuffer;
            HRESULT Result = Globals::D3D11SwapchainPtr->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&BackBuffer));
            if (Result != S_OK)
            {
                Logger::LogFatalError("GetBuffer() failed, return value: {}\n", Result);
            }

            D3D11_RENDER_TARGET_VIEW_DESC desc = {};
            memset(&desc, 0, sizeof(desc));
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Required to avoid rendering issue with overlay. Without this the proper rgb values will not be displayed.
            desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            Result = Globals::D3D11Device->CreateRenderTargetView(BackBuffer, &desc, &Globals::MainRenderTargetView);
            if (Result != S_OK)
            {
                Logger::LogFatalError("CreateRenderTargetView() failed, return value: {}\n", Result);
            }
            BackBuffer->Release();

            InitImGuiD3D11();
        }
    }

    return KeenGraphicsBeginFrame(pGraphicsSystem, pSwapChain);
}


bool ReadyForD3D11Init(keen::GraphicsSystem* pGraphicsSystem)
{
    if (Globals::ReadyForImGuiInit)
    {
        if (pGraphicsSystem)
        {
            if (pGraphicsSystem->pDevice && pGraphicsSystem->pImmediateContext && pGraphicsSystem->pDefaultSwapChain)
            {
                if (pGraphicsSystem->pDefaultSwapChain->pSwapChain && pGraphicsSystem->pDefaultSwapChain->pBackBufferRenderTargetView)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void InitImGuiD3D11()
{
    //ImGui_ImplWin32_EnableDpiAwareness();  //Todo: viewports

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    Globals::io = io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ///io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Todo: viewports
    ImGui::StyleColorsDark();

    ImGui_ImplDX11_Init(Globals::D3D11Device, Globals::D3D11Context);
    const bool RectResult = GetWindowRect(Globals::GameWindowHandle, &Globals::WindowRect);
    if (!RectResult)
    {
        Logger::LogError("GetWindowRect() failed during script loader init!\n Error message: {}\n", Globals::GetLastWin32ErrorAsString());
    }
    ImGui_ImplWin32_Init(Globals::GameWindowHandle);

    const float GlobalFontSize = 17.0f;
    std::string DefaultFontPath = std::string(Globals::GetEXEPath(false) + "RSL/Fonts/Roboto-Regular.ttf");
    bool DefaultFontLoaded = false;
    if (fs::exists(DefaultFontPath))
    {
        io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalFontSize);
        DefaultFontLoaded = true;
    }
    else
    {
        io.Fonts->AddFontDefault();
    }

    static const ImWchar IconsRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig IconsConfig;
    IconsConfig.MergeMode = true;
    IconsConfig.PixelSnapH = true;
    std::string FontAwesomeSolidPath(Globals::GetEXEPath(false) + "RSL/Fonts/fa-solid-900.ttf");

    Globals::FontNormal = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalFontSize, &IconsConfig, IconsRanges);

    const float GlobalBigFontSize = 24.0f;
    if (DefaultFontLoaded)
    {
        io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalBigFontSize);
    }
    Globals::FontBig = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalBigFontSize, &IconsConfig, IconsRanges);

    /*Start of FontLarge loading*/
    float GlobalLargeFontSize = 35.0f;
    if (DefaultFontLoaded)
    {
        io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalLargeFontSize);
    }
    Globals::FontLarge = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalLargeFontSize, &IconsConfig, IconsRanges);
    /*End of FontLarge loading*/

    /*Start of FontHuge loading*/
    float GlobalHugeFontSize = 70.0f;
    if (DefaultFontLoaded)
    {
        io.Fonts->AddFontFromFileTTF(DefaultFontPath.c_str(), GlobalHugeFontSize);
    }
    Globals::FontHuge = io.Fonts->AddFontFromFileTTF(FontAwesomeSolidPath.c_str(), GlobalHugeFontSize, &IconsConfig, IconsRanges);
    /*End of FontHuge loading*/

    Globals::ImGuiInitialized = true;
    Hooks::UpdateD3D11Pointers = false;

    Logger::Log("ImGui Initialized.\n");

#if DebugDrawTestEnabled
    try
    {
        Globals::DebugDrawRenderInterface = new RenderInterfaceD3D11(Globals::D3D11Device, Globals::D3D11Context);
        dd::initialize(Globals::DebugDrawRenderInterface);
    }
    catch (std::exception& Ex)
    {
        Logger::LogError("Exception caught while initializing debug draw! Message: {}\n", Ex.what());
    }
#endif
}