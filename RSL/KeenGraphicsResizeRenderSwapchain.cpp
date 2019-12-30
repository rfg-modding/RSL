#include "Hooks.h"
#include "Application.h"

bool __cdecl Hooks::KeenGraphicsResizeRenderSwapchainHook(keen::RenderSwapChain* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight)
{
    return rfg::KeenGraphicsResizeRenderSwapchain(KeenSwapchain, NewWidth, NewHeight);
}

void __cdecl Hooks::CsWrapSliceHook()
{
    Globals::HookDidFrame = true;
    return rfg::CsWrapSlice();
}