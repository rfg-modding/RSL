#include "dinputproxy.h"

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetDeviceData(struct IDirectInputDevice *idid, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
	DIDEVICEOBJECTDATA data[128];
	DWORD dwCount;
	HRESULT ret;

	// hack here
	if (proxydid->bKeyboard)
		ret = proxydid->did->lpVtbl->GetDeviceData(proxydid->did, sizeof(data[0]), data, &dwCount, 0);
	else if (proxydid->bMouse)
		ret = proxydid->did->lpVtbl->GetDeviceData(proxydid->did, sizeof(data[0]), data, &dwCount, 0);
	else
		ret = proxydid->did->lpVtbl->GetDeviceData(proxydid->did, cbObjectData, rgdod, pdwInOut, dwFlags);

	return ret;
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_QueryInterface(struct IDirectInputDevice *idid, REFIID riid, LPVOID * ppvObj)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->QueryInterface(proxydid->did, riid, ppvObj);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_AddRef(struct IDirectInputDevice *idid)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    proxydid->refcount++;
    
    return proxydid->did->lpVtbl->AddRef(proxydid->did);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Release(struct IDirectInputDevice *idid)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    ULONG ret;
    
    ret = proxydid->did->lpVtbl->Release(proxydid->did);
    
    proxydid->refcount--;
    if (!proxydid->refcount)
    {
        free(proxydid);
    }
    
    return ret;
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetCapabilities(struct IDirectInputDevice *idid, LPDIDEVCAPS lpDIDevCaps)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->GetCapabilities(proxydid->did, lpDIDevCaps);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_EnumObjects(struct IDirectInputDevice *idid, LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->EnumObjects(proxydid->did, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetProperty(struct IDirectInputDevice *idid, REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->GetProperty(proxydid->did, rguidProp, pdiph);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetProperty(struct IDirectInputDevice *idid, REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->SetProperty(proxydid->did, rguidProp, pdiph);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Acquire(struct IDirectInputDevice *idid)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->Acquire(proxydid->did);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Unacquire(struct IDirectInputDevice *idid)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->Unacquire(proxydid->did);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetDeviceState(struct IDirectInputDevice *idid, DWORD cbData, LPVOID lpvData)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->GetDeviceState(proxydid->did, cbData, lpvData);
}


HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetDataFormat(struct IDirectInputDevice *idid, LPCDIDATAFORMAT lpdf)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->SetDataFormat(proxydid->did, lpdf);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetEventNotification(struct IDirectInputDevice *idid, HANDLE hEvent)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->SetEventNotification(proxydid->did, hEvent);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_SetCooperativeLevel(struct IDirectInputDevice *idid, HWND hwnd, DWORD dwFlags)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->SetCooperativeLevel(proxydid->did, hwnd, dwFlags);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetObjectInfo(struct IDirectInputDevice *idid, LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->GetObjectInfo(proxydid->did, pdidoi, dwObj, dwHow);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_GetDeviceInfo(struct IDirectInputDevice *idid, LPDIDEVICEINSTANCE pdidi)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->GetDeviceInfo(proxydid->did, pdidi);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_RunControlPanel(struct IDirectInputDevice *idid, HWND hwndOwner, DWORD dwFlags)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->RunControlPanel(proxydid->did, hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE proxy_IDirectInputDevice_Initialize(struct IDirectInputDevice *idid, HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
    proxy_IDirectInputDevice *proxydid = (proxy_IDirectInputDevice *)idid;
    
    return proxydid->did->lpVtbl->Initialize(proxydid->did, hinst, dwVersion, rguid);
}
