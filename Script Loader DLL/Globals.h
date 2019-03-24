#pragma once
#define PublicMode true
#define ColorLogMessages false
#define EnableSpectatorMode false 
#include "Includes.h"

/*RFGR Script Loader DLL*/

//using json = nlohmann::json;
namespace fs = std::filesystem;

static const ImVec4 ColorTransparent = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
static const ImVec4 ColorRed = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
static const ImVec4 ColorGreen = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
static const ImVec4 ColorBlue = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
static const ImVec4 ColorBlack = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
static const ImVec4 ColorWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
static const ImVec4 ColorPurple = ImVec4(0.227f, 0.0f, 0.6588f, 1.0f);
static const ImVec4 ColorOrange = ImVec4(1.0f, 0.4157f, 0.0f, 1.0f);
static const ImVec4 ColorYellow = ImVec4(1.0f, 0.8902f, 0.0666f, 1.0f);
 
static const ImVec4 SecondaryTextColor(0.20f, 0.55f, 0.83f, 1.00f); //Light blue
static const ImVec4 ColorBlue2 = ImVec4(0.10f, 0.40f, 0.75f, 1.0f);
 
static const float pi = 3.14159265f;

extern HMODULE MainModule;

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
extern DWORD* InMultiplayer;
extern bool MultiplayerHookTriggered;

extern const WORD ConsoleMessageLabelTextAttributes;
extern const WORD ConsoleMessageTextAttributes;
extern const WORD ConsoleWarningTextAttributes;
extern const WORD ConsoleErrorTextAttributes;
extern const WORD ConsoleFatalErrorTextAttributes;
extern const WORD ConsoleSuccessTextAttributes;
extern const WORD ConsoleDefaultTextAttributes;

extern void* GlobalRlDrawPtr;
extern bool BlockNextTildeInput;
extern bool ScriptLoaderCloseRequested;

extern bool HudVisible;
extern bool FogVisible;

extern const std::string ScriptLoaderVersion;

const char* GetScriptLoaderVersion();
void ShowHelpMarker(const char* desc);
bool DirectoryExists(std::string Directory);
void CreateDirectoryIfNull(std::string Directory);
float FloatConvertDegreesToRadians(float AngleInDegrees);
float sind(float AngleInDegrees);
float cosd(float AngleInDegrees);
float tand(float AngleInDegrees);
void SetConsoleAttributes(WORD Attributes);
void ResetConsoleAttributes();
HWND FindTopWindow(DWORD pid);
DWORD GetProcessID(std::string ProcessName);
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