#include "Globals.h"

bool OpenDebugConsole = false;
nlohmann::json MainConfig;
float DefaultFreeCameraSpeed = 0.3f;
float DefaultRotationSpeed = 0.7f;

IDXGISwapChain* D3D11SwapchainPtr = nullptr;
ID3D11Device* D3D11Device = nullptr;
ID3D11DeviceContext* D3D11Context = nullptr;
ID3D11RenderTargetView* MainRenderTargetView = nullptr;
HWND hwnd = NULL;
ImVec4* Colors = nullptr;

//MainOverlay Overlay;
bool ShowMainOverlay = true;

float OverlayFontSize = 16.0f;
bool show_demo_window = true;
bool ImGuiInitialized = false;
ImGuiIO io;
bool OverlayActive = false;
WNDPROC OriginalWndProc = NULL;
bool FirstPersonModeActive = false;

float GlobalExplosionStrengthMultiplier = 2.0f;
bool UseGlobalExplosionStrengthMultiplier = false;
bool UseExplosionRadiusLimits = true;
float MinimumExplosionRadius = 0.0f;
float MaximumExplosionRadius = 12.0f;
DWORD* GlobalPlayerPtr = nullptr;

bool InfiniteJetpack = false;

sol::state Lua;

HANDLE ConsoleHandle = { 0 };
DWORD* InMultiplayer = nullptr;
bool MultiplayerHookTriggered = false;

const WORD ConsoleMessageLabelTextAttributes = 0 | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const WORD ConsoleMessageTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD ConsoleWarningTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN;
const WORD ConsoleErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD ConsoleFatalErrorTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;
const WORD ConsoleSuccessTextAttributes = 0 | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD ConsoleDefaultTextAttributes = 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;