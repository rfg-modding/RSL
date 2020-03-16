#include "Hooks.h"

Hooks::D3D11Present Hooks::D3D11PresentFuncPtr;
Hooks::D3D11_ResizeBuffers Hooks::D3D11_ResizeBuffersFuncPtr;

bool Hooks::UpdateD3D11Pointers = true;