#pragma once
#include "Functions.h"

extern std::chrono::steady_clock::time_point ExplosionTimerBegin;
extern std::chrono::steady_clock::time_point ExplosionTimerEnd;

extern std::once_flag HookD3D11PresentInitialCall;
extern std::once_flag HookExplosionCreateInitialCall;

LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern LRESULT ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern void UpdateDebugDrawRenderInterfaceValues();

typedef HRESULT(__stdcall* D3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern D3D11Present D3D11PresentObject;

HRESULT __stdcall D3D11PresentHook(IDXGISwapChain * pSwapChain, UINT SyncInterval, UINT Flags);
void __cdecl ExplosionCreateHook(explosion_info * ExplosionInfo, void * Source, void * Owner, vector * Position, matrix * Orientation, vector * Direction, void * WeaponInfo, bool FromServer);

void __fastcall PlayerDoFrameHook(Player* PlayerPtr);
extern std::once_flag HookPlayerDoFrameInitialCall;

void __fastcall ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData);
extern std::once_flag HookObjectUpdatePosAndOrientInitialCall;
extern std::once_flag HookHumanUpdatePosAndOrientInitialCall;

/*Start of MP Detection Hooks*/
bool __fastcall IsValidGameLinkLobbyKaikoHook(void* This); 
void __cdecl GameMusicMultiplayerStartHook();
void __cdecl InitMultiplayerDataItemRespawnHook(void* Item);
void __cdecl HudUiMultiplayerProcessHook(float DeltaTime);
void __cdecl HudUiMultiplayerEnterHook();
/*End of MP Detection Hooks*/

//void __cdecl HavokBodySetPositionHook(unsigned int HavokHandle, vector* NewPosition);

extern bool UpdateD3D11Pointers;

bool __cdecl KeenGraphicsResizeRenderSwapchainHook(void* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight);

void __fastcall world_do_frame_hook(World* This, void* edx, bool HardLoad); //.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame>
extern std::once_flag HookWorldDoFrameInitialCall;

void __fastcall rl_camera_render_begin_hook(rl_camera* This, void* edx, rl_renderer* Renderer); //.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>
extern std::once_flag HookRlCameraRenderBegin;

void __fastcall hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime); //0x9E1A70
extern std::once_flag HookhkpWorld_stepDeltaTime;

void __fastcall ApplicationUpdateTimeHook(void* This, void* edx, float TimeStep); //0x9E1A70
extern std::once_flag HookApplicationUpdateTime;

int __cdecl LuaDoBufferHook(lua_State *L, const char *buff, unsigned int size, const char *name);
extern std::once_flag HookLuaDoBuffer;