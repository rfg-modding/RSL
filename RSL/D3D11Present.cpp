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
#if DebugDrawTestEnabled
        try
        {
            if (Globals::DebugDrawRenderInterface)
            {
                UpdateDebugDrawRenderInterfaceValues();
                if (Globals::PlayerPtr)
                {
                    const ddVec3 boxColor = { 0.0f, 0.8f, 0.8f };
                    const ddVec3 boxCenter = { Globals::PlayerPtr->Position.x, Globals::PlayerPtr->Position.y, Globals::PlayerPtr->Position.z };
                    const ddVec3 UpVector = { 0.0f, 1.0f, 0.0f };

                    dd::circle(boxCenter, UpVector, boxColor, 500.0f, 2000, 5000);
                    dd::box(boxCenter, boxColor, 15.0f, 15.0f, 15.0f);
                    dd::cross(boxCenter, 1.0f);

                    const ddVec3 DebugTextPosition = { 0.2f, 0.2f, 0.0f };
                    const ddVec3 DebugTextColor = { 1.0f, 0.0f, 0.0f };
                    dd::screenText("hOi!!!!! I'm tEMMIE!!", DebugTextPosition, DebugTextColor, 2.0f, 5000); //Highly experimental code...

                    //dd::projectedText("Space asshole", boxCenter, DebugTextColor, Globals::vpMatrix, 300, 300, 300, 300, 1.0f);
                }
                dd::flush();
            }
        }
        catch (std::exception& Ex)
        {
            Logger::LogError("Exception caught while testing debug draw cube! Message: {}\n", Ex.what());
        }
#endif

        if (Globals::Gui)
        {
            if (Globals::Gui->Ready())
            {
                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                Globals::Gui->Draw();
                //ImGui::ShowDemoWindow(&Globals::OverlayActive);
                Globals::D3D11Context->OMSetRenderTargets(1, &Globals::MainRenderTargetView, nullptr);
                //Globals::D3D11Context->ClearRenderTargetView(Globals::MainRenderTargetView, (float*)& clear_color);
                ImGui::Render();
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }
    return D3D11PresentFuncPtr(pSwapChain, SyncInterval, Flags);
}