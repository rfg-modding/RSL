#include "Hooks.h"
#include "Application.h"

HRESULT __stdcall Hooks::D3D11PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!Globals::ImGuiInitialized)
    {
        return D3D11PresentFuncPtr(pSwapChain, SyncInterval, Flags);
    }

    if (!Globals::ScriptLoaderCloseRequested)
    {
        static auto Gui = IocContainer->resolve<IGuiManager>();
        if (Gui)
        {
            if (Gui->Ready())
            {
                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                Gui->Draw();
                Globals::D3D11Context->OMSetRenderTargets(1, &Globals::MainRenderTargetView, nullptr);
                ImGui::Render();
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }
    return D3D11PresentFuncPtr(pSwapChain, SyncInterval, Flags);
}