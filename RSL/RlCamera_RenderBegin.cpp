#include "Hooks.h"
#include "Application.h"

void __fastcall Hooks::rl_camera_render_begin_hook(rl_camera* This, void* edx, rl_renderer* Renderer) //.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>
{
    static std::once_flag HookRlCameraRenderBegin;
    std::call_once(HookRlCameraRenderBegin, [&]()
        {
            Globals::RlCameraPtr = This;
            Globals::RlRendererPtr = Renderer;

            if (Renderer)
            {
                Globals::RlRenderLibPtr = Renderer->m_pRenderLib;
                Globals::RlStateManagerPtr = Renderer->m_state_p;
            }

            Globals::MainScenePtr = rfg::GameRenderGetMainScene();
            if (Globals::MainScenePtr)
            {
                Globals::MainSceneRendererPtr = Globals::MainScenePtr->m_scene_renderer_p;
                if (!Globals::MainSceneRendererPtr)
                {
                    Globals::MainSceneRendererPtr = Globals::MainScenePtr->m_default_scene_renderer_p;
                }
                Globals::MainSceneCameraPtr = Globals::MainSceneRendererPtr->m_part2_params.p_camera;
            }
        });
    if (This != Globals::RlCameraPtr)
    {
        Globals::RlCameraPtr = This;
    }

    return rfg::RlCameraRenderBegin(This, edx, Renderer);
}