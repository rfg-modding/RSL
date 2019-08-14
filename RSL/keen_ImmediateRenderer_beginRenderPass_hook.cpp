#include "Hooks.h"
//#include "Application.h"

void __fastcall Hooks::keen_ImmediateRenderer_beginRenderPass_hook(keen::ImmediateRenderer* this_ptr, void* edx, keen::RenderTarget* pRenderTarget, keen::Camera* pCamera)
{
    if(Globals::ImmediateRenderer != this_ptr)
    {
        Logger::LogWarning("Globals::ImmediateRenderer* changed!\n");
        Globals::ImmediateRenderer = this_ptr;
    }


    return keen_ImmediateRenderer_beginRenderPass(this_ptr, edx, pRenderTarget, pCamera);
}