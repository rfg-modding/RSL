#include "Hooks.h"
#include "Application.h" //Note: Compilation could possibly be speed up by selectively including needed files rather than including everything like this does

Hooks::D3D11Present Hooks::D3D11PresentFuncPtr;
bool Hooks::UpdateD3D11Pointers = true;