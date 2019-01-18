#pragma once
/*RFGR Script Loader DLL*/

#define _CRT_SECURE_NO_WARNINGS true

#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <utility>

#include <ctype.h>
#include <math.h>

#include <chrono>
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include <filesystem>
#include <experimental/filesystem>

#include <nlohmann/json.hpp>

//#pragma comment(lib, "dinput8.lib")
//#pragma comment(lib, "dxguid.lib")
//#include <dinput.h>

// Include GLM core features
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

// Include GLM extension
#include <glm/ext/matrix_transform.hpp>

// Include Kiero, MinHook, and D3D11 for D3D11 hooking
//#include <d3d11.h>
//#pragma comment(lib, "d3d11.lib")

#include "kiero/kiero.h"
#include "MinHook/MinHook.h"

#include <imgui.h>
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


#include <tchar.h>
#include <thread>
#include <mutex>

#include <sapi.h>

//#pragma comment(lib, "lua51.lib")

//#include <lua.h>
//#include <lualib.h>
//#include <lauxlib.h>
#include "sol.hpp"

#include <windef.h>