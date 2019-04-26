#pragma once
#define PublicMode true
#define ColorLogMessages false
#define EnableSpectatorMode false 
#include "Includes.h"
#include "RFGR_Types_Havok.h"

/*RFGR Script Loader DLL*/

//using json = nlohmann::json;
namespace fs = std::filesystem;
using uint = unsigned int;
using ulong = unsigned long;
using ulonglong = unsigned long long;

class ProgramManager;
class GuiSystem;
class ScriptManager;
class CameraWrapper;

namespace Globals
{
	extern ProgramManager* Program;
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

	extern ImFont* FontNormal;
	extern ImFont* FontBig;
	extern ImFont* FontLarge;
	extern ImFont* FontHuge;

	extern bool OpenDebugConsole;
	extern nlohmann::json MainConfig;
	extern float DefaultFreeCameraSpeed;
	extern float DefaultRotationSpeed;
	//static bool UseConsole = false;

	extern IDXGISwapChain* D3D11SwapchainPtr;
	extern ID3D11Device* D3D11Device;
	extern ID3D11DeviceContext* D3D11Context;
	extern ID3D11RenderTargetView* MainRenderTargetView;
	extern HWND hwnd;
	extern RECT WindowRect;
	//extern ImVec4* Colors;

	//extern MainOverlay Overlay;
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

	//extern sol::state LuaState;

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
	std::string GetEXEPath(bool IncludeExeInPath);
	void PlaceNOP(BYTE* Address, DWORD Length = 1);
	MODULEINFO GetModuleInfo(char *szModule);
	DWORD FindPattern(char *module, char *pattern, char *mask);
	//Source of the next three functions: https://stackoverflow.com/a/21767578
	HWND find_main_window(unsigned long process_id);
	BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam);
	BOOL is_main_window(HWND handle);

	template <typename T>
	std::string to_string_precise(const T Value, const int Precision = 1)
	{
		std::ostringstream Out;
		Out.precision(Precision);
		Out << std::fixed << Value;
		return Out.str();
	}
}