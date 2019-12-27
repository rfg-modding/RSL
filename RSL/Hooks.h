
/* Hooks.h/.cpp contain all the function hooks used by the script loader. These hooks are
 * created and enabled by the HookManager class. Hooks are a very powerful tool. They are 
 * basically some additional code stuck on front of a function. This lets you do things like
 * intercept their arguments and use them later, change them, or have events that occur when 
 * a specific function is called.
 */

#pragma once
#include "Functions.h"
#include "GuiReference.h"

#define DebugDrawTestEnabled false

class TextEditorWrapper;

namespace Hooks
{
    LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    extern LRESULT ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, const KeyState& keys);
    extern void ProcessScriptEditorInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, const KeyState& keys, GuiReference<TextEditorWrapper>& textEditor);

    extern void UpdateDebugDrawRenderInterfaceValues();

    typedef HRESULT(__stdcall* D3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    extern D3D11Present D3D11PresentFuncPtr;
    HRESULT __stdcall D3D11PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

    typedef HRESULT(__stdcall* D3D11_ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
    extern D3D11_ResizeBuffers D3D11_ResizeBuffersFuncPtr;
    HRESULT __stdcall D3D11_ResizeBuffersHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

    bool __cdecl KeenGraphicsResizeRenderSwapchainHook(keen::RenderSwapChain* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight);
    keen::GraphicsCommandBuffer* __cdecl KeenGraphicsBeginFrameHook(keen::GraphicsSystem* pGraphicsSystem, keen::RenderSwapChain* pSwapChain);
    void __fastcall PlayerDoFrameHook(Player* PlayerPtr);
    void __cdecl AllocatorStillValidHook(void* ref_address);
    void __cdecl ExplosionCreateHook(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position, matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer);
    extern bool UpdateD3D11Pointers;
    void __cdecl HookDoFrameHook();
    void __fastcall hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime);
    void __fastcall rl_camera_render_begin_hook(rl_camera* This, void* edx, rl_renderer* Renderer);
    void __cdecl InvertDataItemHook(void* Item);
    void __fastcall ApplicationUpdateTimeHook(void* This, void* edx, float TimeStep);
    void __fastcall world_do_frame_hook(World* This, void* edx, bool HardLoad);
    int __cdecl LuaDoBufferHook(lua_State* L, const char* buff, unsigned int size, const char* name);
    void __fastcall ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData);
    void __fastcall StreamGridDoFrameHook(stream_grid* This, void* edx, vector* StreamPos, bool SingleZoneMode);
    void __cdecl CsWrapSliceHook();
    //vehicle* __cdecl CutsceneSpawnVehicleHook(vehicle_info* v_info, vector* pos, matrix* orient);
    bool __cdecl peg_load_wrapper_hook(const char* filename, unsigned int srid, char* cpu_preload, int cpu_size, char* gpu_preload, int gpu_size);


    bool __fastcall IsValidEigenGradientHook(void* This);
    
    //.text:01317F40 rfg.exe:$757F40 #757340 <object_spawn_vehicle> //spawn_status_result __cdecl object_spawn_vehicle(vehicle_spawn_params *spawn_param)
    spawn_status_result __cdecl object_spawn_vehicle_hook(vehicle_spawn_params& spawn_param);

    //.text:008AC810 rfg.exe:$86C810 #86BC10 <keen::ImmediateRenderer::beginRenderPass> //void __thiscall keen::ImmediateRenderer::beginRenderPass(keen::ImmediateRenderer *this, keen::RenderTarget *pRenderTarget, keen::Camera *pCamera)
    void __fastcall keen_ImmediateRenderer_beginRenderPass_hook(keen::ImmediateRenderer* this_ptr, void* edx, keen::RenderTarget* pRenderTarget, keen::Camera* pCamera);


    //.text:00664A60 rfg.exe:$324A60 #323E60 <rfgl_find_and_delete_object_mover> //int __cdecl rfgl_find_and_delete_object_mover(int objects_to_delete, bool find_gm)
    int __cdecl rfgl_find_and_delete_object_mover_hook(int objects_to_delete, bool find_gm);
    //.text:00664B90 rfg.exe:$324B90 #323F90 <rfgl_find_and_delete_debris_object> //int __cdecl rfgl_find_and_delete_debris_object(int objects_to_delete)
    int __cdecl rfgl_find_and_delete_debris_object_hook(int objects_to_delete);

    //.text:00CEE450 rfg.exe:$3EE450 #3ED850 <gamestate_gp_process> //void __cdecl gamestate_gp_process()
    void __cdecl gamestate_gp_process_hook();

    void __cdecl rfg_init_stage_2_done_hook(void* pSoundSystem);
    void __cdecl rfg_init_stage_2_done_2_hook();

    bool __cdecl verify_gamesave_exit_notify_hook(GameState new_state);

    //.text:016E1430 rfg.exe:$541430 #540830 <world::load_territory> //bool __thiscall world::load_territory(world *this)
    bool __fastcall world_load_territory_hook(World* this_ptr, void* edx);

    bool __cdecl can_drop_vehicle_hook(vehicle_info* v_info, rfg::farray<object*, 256> * delete_object_list, vector* position, matrix* orient, unsigned int ignore_object, bool high_priority);

    cfile* __cdecl cf_open_hook(const char* filename_in, const char* mode, vlib_platform disk_platform, bool async);

    void __cdecl gem_post_event_hook(event_data& data);
}

