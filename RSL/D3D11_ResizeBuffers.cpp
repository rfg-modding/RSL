#include "Hooks.h"
#include "Application.h"

HRESULT __stdcall Hooks::D3D11_ResizeBuffersHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    bool ShouldReInit = false;
    if (Globals::MainRenderTargetView)
    {
        Globals::MainRenderTargetView->Release();
        Globals::MainRenderTargetView = nullptr;
        ShouldReInit = true;
    }

    HRESULT Result = D3D11_ResizeBuffersFuncPtr(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
#ifdef DEBUG
    Logger::Log("[D3D11_ResizeBuffersHook]:: BufferCount: {}, Width: {}, Height: {}, NewFormat: {}, SwapChainFlags: {} .... Result: {:#x}\n", BufferCount, Width, Height, NewFormat, SwapChainFlags, (uint)Result);
#endif

    if (ShouldReInit)
    {
        Globals::D3D11Device = Globals::GraphicsSystemPtr->pDevice;
        Globals::D3D11Context = Globals::GraphicsSystemPtr->pImmediateContext;
        Globals::D3D11SwapchainPtr = Globals::GraphicsSystemPtr->pDefaultSwapChain->pSwapChain;

        ID3D11Texture2D* BackBuffer;
        Result = Globals::D3D11SwapchainPtr->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&BackBuffer));
        if (Result != S_OK)
            Logger::LogFatalError("GetBuffer() failed, return value: {}\n", Result);

        D3D11_RENDER_TARGET_VIEW_DESC desc = {};
        memset(&desc, 0, sizeof(desc));
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Required to avoid rendering issue with overlay. Without this the proper rgb values will not be displayed.
        desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        Result = Globals::D3D11Device->CreateRenderTargetView(BackBuffer, &desc, &Globals::MainRenderTargetView);
        if (Result != S_OK)
            Logger::LogFatalError("CreateRenderTargetView() failed, return value: {}\n", Result);

        BackBuffer->Release();
    }
    return Result;
}