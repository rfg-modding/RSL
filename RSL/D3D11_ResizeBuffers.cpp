#include "Hooks.h"
#include "Application.h"

HRESULT __stdcall Hooks::D3D11_ResizeBuffersHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    HRESULT Result = D3D11_ResizeBuffersFuncPtr(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
#ifdef DEBUG
    Logger::Log("[D3D11_ResizeBuffersHook]:: BufferCount: {}, Width: {}, Height: {}, NewFormat: {}, SwapChainFlags: {} .... Result: {:#x}\n", BufferCount, Width, Height, NewFormat, SwapChainFlags, (uint)Result);
#endif
    //DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH = 2
    return Result;
}