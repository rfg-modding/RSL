//This DLL is used to automatically load the script loader when the game is run. For now an optional feature,
//but once the launcher is stable this will be a default feature in use.
//You shouldn't put much program logic into here as it's primary purpose is to just load other script loader dlls.
//This is a slightly modified version of this: https://github.com/zerosum0x0/dinput-proxy-dll

#include "dinputproxy.h"

LPSTR GetLastWin32ErrorAsString();

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason,LPVOID v)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
        FILE* pFile = NULL;
        DWORD PID = GetCurrentProcessId();
        
        AllocConsole();
        freopen_s(&pFile, "CONOUT$", "r+", stdout);

        char ExePathBuffer[MAX_PATH];
        GetModuleFileName(0, ExePathBuffer, MAX_PATH);
        printf("Exe path: %s\n", ExePathBuffer);

		char szPath[MAX_PATH];

		if (!GetSystemDirectory(szPath, sizeof(szPath) - 20))
			return FALSE;

		strcat(szPath, "\\dinput8.dll");
        printf("Real dinput8.dll path: %s\n", szPath);

		hLThis = hInst;
		hL = LoadLibrary(szPath);

		if (!hL)
		{
            return FALSE;
		}

        const HINSTANCE RSLDLL = LoadLibrary(".\\RSL\\RSL.dll");
        if(!RSLDLL)
        {
            printf("Failed to load RSL DLL! Exiting! Error: %s\n", GetLastWin32ErrorAsString());
            return FALSE;
        }

		p[0] = GetProcAddress(hL,"DirectInput8Create");
		p[1] = GetProcAddress(hL,"DllCanUnloadNow");
		p[2] = GetProcAddress(hL,"DllGetClassObject");
		p[3] = GetProcAddress(hL,"DllRegisterServer");
		p[4] = GetProcAddress(hL,"DllUnregisterServer");
	}

	if (reason == DLL_PROCESS_DETACH)
	{
        FreeConsole();
		FreeLibrary(hL);
	}

	return TRUE;
}

LPSTR GetLastWin32ErrorAsString()
{
    //Get the error message, if any.
    DWORD errorMessageID = GetLastError();
    if (errorMessageID == 0)
        return NULL; //No error message has been recorded

    LPSTR messageBuffer = NULL;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    return messageBuffer;
}

// DirectInput8Create
//extern "C" __declspec(naked) void __stdcall __E__0__()
HRESULT __stdcall  __E__0__(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{
	//__asm { jmp p[0*4]; }
	
	proxy_IDirectInput *proxyDI;
	IDirectInput8 *di;

	typedef HRESULT (__stdcall *pCreate)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
	pCreate ppC = (pCreate)p[0*4];
	HRESULT ret = ppC(hinst, dwVersion, riidltf, &di, punkOuter);

	if (ret != DI_OK)
		return ret;

	proxyDI = (proxy_IDirectInput *)malloc(sizeof(proxy_IDirectInput));
    proxyDI->vtbl.QueryInterface = proxy_IDirectInput_QueryInterface;
    proxyDI->vtbl.AddRef = proxy_IDirectInput_AddRef;
    proxyDI->vtbl.Release = proxy_IDirectInput_Release;
    proxyDI->vtbl.CreateDevice = proxy_IDirectInput_CreateDevice;
    proxyDI->vtbl.EnumDevices = proxy_IDirectInput_EnumDevices;
    proxyDI->vtbl.GetDeviceStatus = proxy_IDirectInput_GetDeviceStatus;
    proxyDI->vtbl.RunControlPanel = proxy_IDirectInput_RunControlPanel;
    proxyDI->vtbl.Initialize = proxy_IDirectInput_Initialize;
    proxyDI->lpVtbl = &proxyDI->vtbl;
    proxyDI->di = di;
    proxyDI->refcount = 1;
    
    *ppvOut = (LPDIRECTINPUT)proxyDI;
		
	return ret; /* */
}

// DllCanUnloadNow
__declspec(naked) void __stdcall __E__1__()
{
	__asm
	{
		jmp p[1*4];
	}
}

// DllGetClassObject
__declspec(naked) void __stdcall __E__2__()
{
	__asm
	{
		jmp p[2*4];
	}
}

// DllRegisterServer
__declspec(naked) void __stdcall __E__3__()
{
	__asm
	{
		jmp p[3*4]; 
	}
}

// DllUnregisterServer
__declspec(naked) void __stdcall __E__4__()
{
	__asm 
	{ 
		jmp p[4*4]; 
	}
}

