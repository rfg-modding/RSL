#include <stdio.h>
#include <windows.h>
#include <dinput.h>
#include <time.h>
#pragma pack(1)



// globals
static HINSTANCE hLThis = 0;
static HINSTANCE hL = 0;
static FARPROC p[5] = {0};

// new types
typedef unsigned long uint32;

typedef struct
{
    DWORD offset;
    DWORD data;
} keyqueueitem_t;

typedef struct
{
	IDirectInput8Vtbl *lpVtbl;
	IDirectInput8Vtbl vtbl;
	IDirectInput8 *di;
	int refcount;
} proxy_IDirectInput;

typedef struct
{
	IDirectInputDevice8Vtbl *lpVtbl;
	IDirectInputDevice8Vtbl vtbl;
	IDirectInputDevice8 *did;
	int refcount;
	BOOL bKeyboard;
	BOOL bMouse;
	BOOL bControlDown;
	uint32 sequence;
} proxy_IDirectInputDevice;

// Methods to implement
HRESULT KeyboardHandler(proxy_IDirectInputDevice *proxydid, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut);


// keyboard helper functions
void AddKeyToQueue(DWORD offset, DWORD data);
BOOL GetKeyFromQueue(keyqueueitem_t *key);
void PressKeyQueue(DWORD key);
void PressKeysString(char* str);
void SendBufferedKeys(proxy_IDirectInputDevice* proxydid, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwCount);

// IDirectInput vtbl methods
HRESULT STDMETHODCALLTYPE proxy_IDirectInput_QueryInterface(struct IDirectInput *idi, REFIID riid, LPVOID * ppvObj);
ULONG STDMETHODCALLTYPE proxy_IDirectInput_AddRef(struct IDirectInput *idi);
ULONG STDMETHODCALLTYPE proxy_IDirectInput_Release(struct IDirectInput *idi);
HRESULT STDMETHODCALLTYPE proxy_IDirectInput_CreateDevice(struct IDirectInput *idi, REFGUID rguid, LPDIRECTINPUTDEVICEA *lplpDirectInputDevice, LPUNKNOWN pUnkOuter);
HRESULT STDMETHODCALLTYPE proxy_IDirectInput_EnumDevices(struct IDirectInput *idi, DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags);
HRESULT STDMETHODCALLTYPE proxy_IDirectInput_GetDeviceStatus(struct IDirectInput *idi, REFGUID rguidInstance);
HRESULT STDMETHODCALLTYPE proxy_IDirectInput_RunControlPanel(struct IDirectInput *idi, HWND hwndOnwer, DWORD dwFlags);
HRESULT STDMETHODCALLTYPE proxy_IDirectInput_Initialize(struct IDirectInput *idi, HINSTANCE inst, DWORD dwVersion);

// IDirectInputDevice vtbl methods
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_QueryInterface(struct IDirectInputDevice *idid, REFIID riid, LPVOID * ppvObj);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_AddRef(struct IDirectInputDevice *idid);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Release(struct IDirectInputDevice *idid);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetCapabilities(struct IDirectInputDevice *idid, LPDIDEVCAPS lpDIDevCaps);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_EnumObjects(struct IDirectInputDevice *idid, LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetProperty(struct IDirectInputDevice *idid, REFGUID rguidProp, LPDIPROPHEADER pdiph);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetProperty(struct IDirectInputDevice *idid, REFGUID rguidProp, LPCDIPROPHEADER pdiph);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Acquire(struct IDirectInputDevice *idid);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Unacquire(struct IDirectInputDevice *idid);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetDeviceState(struct IDirectInputDevice *idid, DWORD cbData, LPVOID lpvData);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetDeviceData(struct IDirectInputDevice *idid, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetDataFormat(struct IDirectInputDevice *idid, LPCDIDATAFORMAT lpdf);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetEventNotification(struct IDirectInputDevice *idid, HANDLE hEvent);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetCooperativeLevel(struct IDirectInputDevice *idid, HWND hwnd, DWORD dwFlags);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetObjectInfo(struct IDirectInputDevice *idid, LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetDeviceInfo(struct IDirectInputDevice *idid, LPDIDEVICEINSTANCE pdidi);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_RunControlPanel(struct IDirectInputDevice *idid, HWND hwndOwner, DWORD dwFlags);
HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Initialize(struct IDirectInputDevice *idid, HINSTANCE hinst, DWORD dwVersion, REFGUID rguid);


