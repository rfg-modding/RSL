#pragma once
#include "Includes.h"
#include "RFGR_Types_Vehicle_Spawn_Params.h"
#include "FixedArrayWrapper.h"
#include "Version.h"

/*RSL*/
#define UseLauncher true

//using json = nlohmann::json;
namespace fs = std::filesystem;
using uint = unsigned int;
using ulong = unsigned long;
using ulonglong = unsigned long long;

class Application;
class GuiSystem;
class ScriptManager;
class CameraWrapper;
class RenderInterfaceD3D11;
class GraphicsStateWrapper;

namespace Globals
{
	extern Application* Program;
	extern GuiSystem* Gui;
	extern ScriptManager* Scripts;
	extern CameraWrapper* Camera;
    
	extern Player* PlayerPtr;
	extern World* RfgWorldPtr;
	extern rl_light* TODLightPtr;
	extern rl_camera* RlCameraPtr;
	extern rl_renderer* RlRendererPtr;
	extern rl_render_lib* RlRenderLibPtr;
	extern rl_state_manager* RlStateManagerPtr;
	extern rl_scene* MainScenePtr;
	extern rl_scene_renderer* MainSceneRendererPtr;
	extern rl_camera* MainSceneCameraPtr;
	extern hkpWorld* hkpWorldPtr;
	extern lua_State* RfgVintLuaState;
	extern hkpRigidBody* PlayerRigidBody;
    extern keen::GraphicsSystem* KeenGraphicsSystemPtr;
    extern stream_grid* MainStreamGrid;
    extern GraphicsStateWrapper GraphicsState;

    extern keen::ImmediateRenderer* ImmediateRenderer;

    extern FixedArrayWrapper<explosion_info> ExplosionInfos;
    extern uint* NumExplosionInfos;

    extern FixedArrayWrapper<material_effect_info> MaterialEffectInfos; //.data:0226B6F0 rfg.exe:$19EB6F0 #0 <Effect_infos>
    extern uint* NumMaterialEffectInfos; //.data:0226E4C4 rfg.exe:$19EE4C4 #0 <Num_effect_infos>

    extern FixedArrayWrapper<effect_info> EffectInfos; //.data:02602E60 rfg.exe:$1D82E60 #0 <Effect_info>
    extern uint* NumEffectInfos; //.data:02602DF0 rfg.exe:$1D82DF0 #0 <Num_effect_types>

    extern rfg::farray<vehicle_info, 163>* VehicleInfos; //.data:012FA5F8 rfg.exe:$12BA5F8 #12B8FF8 <Vehicle_info_pool>

    extern FixedArrayWrapper<int> ShadowMapSizes; //.rdata:01A81BB4 rfg.exe:$EC1BB4 #EC07B4 <shadow_map_resolutions> int[4]

	extern DWORD MouseGenericPollMouseVisible;
	extern DWORD CenterMouseCursorCall;

	extern const ImVec4 ColorTransparent;
	extern const ImVec4 ColorRed;
	extern const ImVec4 ColorGreen;
	extern const ImVec4 ColorBlue;
	extern const ImVec4 ColorBlack;
	extern const ImVec4 ColorWhite;
	extern const ImVec4 ColorPurple;
	extern const ImVec4 ColorOrange;
	extern const ImVec4 ColorYellow;

	extern const ImVec4 SecondaryTextColor;
	extern const ImVec4 ColorBlue2;

	extern const float pi;

	extern HMODULE ScriptLoaderModule;
	extern uintptr_t ModuleBase;
	extern DWORD PID;

	extern ImFont* FontNormal;
	extern ImFont* FontBig;
	extern ImFont* FontLarge;
	extern ImFont* FontHuge; 

	extern bool OpenDebugConsole;
    extern bool DumpTexturesWhenLoading;
    extern bool DisableNumpadWhileOverlayVisible;
	extern nlohmann::json MainConfig;
	extern float DefaultFreeCameraSpeed;
	extern float DefaultRotationSpeed;

	extern IDXGISwapChain* D3D11SwapchainPtr;
	extern ID3D11Device* D3D11Device;
	extern ID3D11DeviceContext* D3D11Context;
	extern ID3D11RenderTargetView* MainRenderTargetView;
	extern HWND GameWindowHandle;
	extern RECT WindowRect;
    extern keen::GraphicsSystem* GraphicsSystemPtr;
    
	extern RenderInterfaceD3D11* DebugDrawRenderInterface;
    extern matrix44 vpMatrix;

	extern bool ShowMainOverlay;

	extern float OverlayFontSize;
	extern bool show_demo_window;
	extern bool ImGuiInitialized;
	extern ImGuiIO io;
	extern bool OverlayActive;
	extern WNDPROC OriginalWndProc;
	extern bool FirstPersonModeActive;

	extern float GlobalExplosionStrengthMultiplier;
	extern bool UseGlobalExplosionStrengthMultiplier;
	extern bool UseExplosionRadiusLimits;
	extern float MinimumExplosionRadius;
	extern float MaximumExplosionRadius;

	extern bool InfiniteJetpack;

	extern HANDLE ConsoleHandle;
	extern bool* InMultiplayer;
	extern bool HookDidFrame;

	extern const WORD ConsoleMessageLabelTextAttributes;
	extern const WORD ConsoleMessageTextAttributes;
	extern const WORD ConsoleWarningTextAttributes;
	extern const WORD ConsoleErrorTextAttributes;
	extern const WORD ConsoleFatalErrorTextAttributes;
	extern const WORD ConsoleSuccessTextAttributes;
	extern const WORD ConsoleDefaultTextAttributes;

	extern bool BlockNextTildeInput;
	extern bool ScriptLoaderCloseRequested;

	extern bool HudVisible;
	extern bool FogVisible;

    extern bool ReadyForImGuiInit;

    extern bool* UnlimitedAmmo;
    extern bool* UnlimitedMagazineAmmo;
    extern bool* UnlimitedAiThrownWeapons;
    extern float* VehicleMaxSpeed;
    extern bool* SsaoVisionEnabled;
    extern int* RfgMaxCharges;
    extern bool* TodEnabled;
    //Note: TodOverride seems to really be something like "MaxTodValue", gotta be careful writing to it. Only use Globals::SetFloat, since it's apparently write protected by default.
    //extern float* TodOverride; //.rdata:01AAEB60 rfg.exe:$EEEB60 #EED760 <__real@41c00000>
    extern float* CurrentTimeOfDay; //.data:01E1CC80 rfg.exe:$125CC80 #125B680 <Current_time_of_day>

    extern bool LockoutModeEnabled;

    extern int* ChargeExplosionDelay; //.data:015D4728 rfg.exe:$1294728 #1293128 <RFG_charge_delay>

    extern rfg::farray<ui_menu*, 8>* RfgMenusList; //farray<ui_menu *,8> RfgMenusList //.data:015A7698 rfg.exe:$1267698 #1266098 <RfgMenusList>

    extern bool DisableDebrisDeletion;
    extern bool FindGmOverride;
    extern bool UseFindGmOverride;

    namespace Launcher
    {
        extern bool ShouldRunRsl; //Used by the launcher WndProc to track if the launcher should launch the main RSL code after it closes or start a vanilla game.
    }
    
	const char* GetScriptLoaderVersion();
	bool DirectoryExists(const std::string& Directory);
	void CreateDirectoryIfNull(const std::string& Directory);
	float FloatConvertDegreesToRadians(float AngleInDegrees);
	float FloatConvertRadiansToDegrees(float AngleInRadians);
	float sind(float AngleInDegrees);
	float cosd(float AngleInDegrees);
	float tand(float AngleInDegrees);
	void SetConsoleAttributes(WORD Attributes);
	void ResetConsoleAttributes();
	HWND FindTopWindow(DWORD pid);
	HWND FindRfgTopWindow();
	DWORD GetProcessID(const std::string& ProcessName);
	void EnforceFloatRange(float& Value, float& Minimum, float& Maximum);
	void ChangeMemoryFloat(DWORD BaseAddress, float Value, DWORD Offset1, DWORD Offset2, bool PrintMessage);
	std::string GetEXEPath(bool IncludeExeInPath = false);
	void PlaceNOP(BYTE* Address, DWORD Length = 1);
    void SetFloat(float* Address, float NewValue);
    void EnableMemoryRegionReadWrite(void* RegionAddress, ulong RegionSize);
	MODULEINFO GetModuleInfo(const char* ModuleName);
	DWORD FindPattern(const char* ModuleName, const char* PatternString, const char* MaskString);
    std::string CharArrayToString(char* Array, int Size);
    std::string CharArrayToString(const char* Array, int Size);

    void TryHideInvalidMainMenuOptions();
    void LogGameMenuInfo();

    std::string GetLastWin32ErrorAsString();

    std::string RemoveFileExtension(const std::string& Filename);
    std::tuple<std::string, std::string> SplitFilename(const std::string& Filename);

    std::optional<explosion_info*> GetExplosionInfo(std::string Name);

	template <typename T>
	std::string to_string_precise(const T Value, const int Precision = 1)
	{
		std::ostringstream Out;
		Out.precision(Precision);
		Out << std::fixed << Value;
		return Out.str();
	}

    extern std::vector<HANDLE> RfgThreadHandles;
    extern void LockGameMain();
    extern void UnlockGameMain();
    extern void SuspendAllThreadsExceptLauncher(HANDLE LauncherThreadHandle);
    extern void ResumeAllThreads();
}

template<class T>
T OffsetPtr(unsigned long Offset)
{
    if(Globals::ModuleBase == 0)
    {
        Globals::ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    }
    return reinterpret_cast<T>(Globals::ModuleBase + Offset);
}