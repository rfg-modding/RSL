#include "Hooks.h"
#include "Application.h"

bool __cdecl Hooks::KeenGraphicsResizeRenderSwapchainHook(keen::RenderSwapChain* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight)
{
    ///Logger::Log("Entered Keen::Graphics::ResizeRenderSwapchain Hook!", LogWarning);
    //UpdateD3D11Pointers = true;


    //Logger::Log("WM_SIZE Received in custom WndProc. Invalidating ImGui DX11 device object. Releasing MainRenderTargetView.", LogWarning);
    //Globals::MainRenderTargetView->Release();
    //Globals::MainRenderTargetView = nullptr;
    //Globals::D3D11SwapchainPtr->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
    //ID3D11Texture2D* pBackBuffer;
    //Globals::D3D11SwapchainPtr->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    //Globals::D3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &Globals::MainRenderTargetView);
    //pBackBuffer->Release();


    return rfg::KeenGraphicsResizeRenderSwapchain(KeenSwapchain, NewWidth, NewHeight);
    //return nullptr;
}

void __cdecl Hooks::CsWrapSliceHook()
{
    Globals::HookDidFrame = true;
    return rfg::CsWrapSlice();
}