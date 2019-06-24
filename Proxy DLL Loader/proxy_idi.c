#include "dinputproxy.h"

HRESULT STDMETHODCALLTYPE proxy_IDirectInput_QueryInterface(struct IDirectInput *idi, REFIID riid, LPVOID * ppvObj)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;
    
    return proxydi->di->lpVtbl->QueryInterface(proxydi->di, riid, ppvObj);
}

ULONG STDMETHODCALLTYPE proxy_IDirectInput_AddRef(struct IDirectInput *idi)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;
    
    proxydi->refcount++;
    
    return proxydi->di->lpVtbl->AddRef(proxydi->di);
}

ULONG STDMETHODCALLTYPE proxy_IDirectInput_Release(struct IDirectInput *idi)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;
    ULONG ret;
    
    ret = proxydi->di->lpVtbl->Release(proxydi->di);
    
    proxydi->refcount--;
    if (!proxydi->refcount)
    {
        free(proxydi);
    }
    
    return ret;
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInput_CreateDevice(struct IDirectInput *idi, REFGUID rguid, LPDIRECTINPUTDEVICEA *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;
    proxy_IDirectInputDevice *proxydid;
    IDirectInputDevice *did;
    HRESULT ret;
    
    ret = proxydi->di->lpVtbl->CreateDevice(proxydi->di, rguid, &did, pUnkOuter);
    if (ret != DI_OK)
    {
        return ret;
    }
    
    proxydid = (proxy_IDirectInputDevice *)malloc(sizeof(proxy_IDirectInputDevice));
    proxydid->vtbl.QueryInterface = proxy_IDirectInputDevice_QueryInterface;
    proxydid->vtbl.AddRef = proxy_IDirectInputDevice_AddRef;
    proxydid->vtbl.Release = proxy_IDirectInputDevice_Release;
    proxydid->vtbl.GetCapabilities = proxy_IDirectInputDevice_GetCapabilities;
    proxydid->vtbl.EnumObjects = proxy_IDirectInputDevice_EnumObjects;
    proxydid->vtbl.GetProperty = proxy_IDirectInputDevice_GetProperty;
    proxydid->vtbl.SetProperty = proxy_IDirectInputDevice_SetProperty;
    proxydid->vtbl.Acquire = proxy_IDirectInputDevice_Acquire;
    proxydid->vtbl.Unacquire = proxy_IDirectInputDevice_Unacquire;
    proxydid->vtbl.GetDeviceState = proxy_IDirectInputDevice_GetDeviceState;
    proxydid->vtbl.GetDeviceData = proxy_IDirectInputDevice_GetDeviceData;
    proxydid->vtbl.SetDataFormat = proxy_IDirectInputDevice_SetDataFormat;
    proxydid->vtbl.SetEventNotification = proxy_IDirectInputDevice_SetEventNotification;
    proxydid->vtbl.SetCooperativeLevel = proxy_IDirectInputDevice_SetCooperativeLevel;
    proxydid->vtbl.GetObjectInfo = proxy_IDirectInputDevice_GetObjectInfo;
    proxydid->vtbl.GetDeviceInfo = proxy_IDirectInputDevice_GetDeviceInfo;
    proxydid->vtbl.RunControlPanel = proxy_IDirectInputDevice_RunControlPanel;
    proxydid->vtbl.Initialize = proxy_IDirectInputDevice_Initialize;
    proxydid->lpVtbl = &proxydid->vtbl;
    proxydid->did = did;
    proxydid->refcount = 1;
    proxydid->bKeyboard = FALSE;
    proxydid->bMouse = FALSE;
    proxydid->sequence = 0;
    if (IsEqualGUID(rguid, &GUID_SysKeyboard))
    {
        proxydid->bKeyboard = TRUE;
        proxydid->bControlDown = FALSE;
    }
    else if (IsEqualGUID(rguid, &GUID_SysMouse))
    {
        proxydid->bMouse = TRUE;
    }
    
    *lplpDirectInputDevice = (LPDIRECTINPUTDEVICE)proxydid;
    
    return DI_OK;
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInput_EnumDevices(struct IDirectInput *idi, DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;
    return proxydi->di->lpVtbl->EnumDevices(proxydi->di, dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInput_GetDeviceStatus(struct IDirectInput *idi, REFGUID rguidInstance)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;   
    return proxydi->di->lpVtbl->GetDeviceStatus(proxydi->di, rguidInstance);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInput_RunControlPanel(struct IDirectInput *idi, HWND hwndOwner, DWORD dwFlags)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;  
    return proxydi->di->lpVtbl->RunControlPanel(proxydi->di, hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInput_Initialize(struct IDirectInput *idi, HINSTANCE hinst, DWORD dwVersion)
{
    proxy_IDirectInput *proxydi = (proxy_IDirectInput *)idi;   
    return proxydi->di->lpVtbl->Initialize(proxydi->di, hinst, dwVersion);
}