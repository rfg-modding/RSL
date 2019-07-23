#pragma once
#include "Includes.h"
#include "RFGR_Types_Vehicle_Spawn_Params.h"
#include "FixedArrayWrapper.h"

/*RSL*/

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

    extern FixedArrayWrapper<explosion_info> ExplosionInfos;
    extern uint* NumExplosionInfos;

    extern FixedArrayWrapper<material_effect_info> MaterialEffectInfos; //.data:0226B6F0 rfg.exe:$19EB6F0 #0 <Effect_infos>
    extern uint* NumMaterialEffectInfos; //.data:0226E4C4 rfg.exe:$19EE4C4 #0 <Num_effect_infos>

    extern FixedArrayWrapper<effect_info> EffectInfos; //.data:02602E60 rfg.exe:$1D82E60 #0 <Effect_info>
    extern uint* NumEffectInfos; //.data:02602DF0 rfg.exe:$1D82DF0 #0 <Num_effect_types>

    extern rfg::farray<vehicle_info, 163>* VehicleInfos; //.data:012FA5F8 rfg.exe:$12BA5F8 #12B8FF8 <Vehicle_info_pool>

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
	extern nlohmann::json MainConfig;
	extern float DefaultFreeCameraSpeed;
	extern float DefaultRotationSpeed;

	extern IDXGISwapChain* D3D11SwapchainPtr;
	extern ID3D11Device* D3D11Device;
	extern ID3D11DeviceContext* D3D11Context;
	extern ID3D11RenderTargetView* MainRenderTargetView;
	extern HWND GameWindowHandle;
	extern RECT WindowRect;
    
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
	extern bool MultiplayerHookTriggered;

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

    namespace Launcher
    {
        extern bool ShouldRunRsl; //Used by the launcher WndProc to track if the launcher should launch the main RSL code after it closes or start a vanilla game.
    }

	extern const std::string ScriptLoaderVersion;
    
	const char* GetScriptLoaderVersion();
	bool DirectoryExists(const std::string& Directory);
	void CreateDirectoryIfNull(const std::string& Directory);
	float FloatConvertDegreesToRadians(float AngleInDegrees);
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
	MODULEINFO GetModuleInfo(const char* ModuleName);
	DWORD FindPattern(const char* ModuleName, const char* PatternString, const char* MaskString);
    std::string CharArrayToString(char* Array, int Size);
    std::string CharArrayToString(const char* Array, int Size);

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
}