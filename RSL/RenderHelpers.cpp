#include "Hooks.h"
#include "Application.h"

void Hooks::UpdateDebugDrawRenderInterfaceValues()
{
    if (Globals::RlCameraPtr && Globals::ImmediateRenderer)
    {
        //Globals::vpMatrix = (matrix44*)&Globals::ImmediateRenderer->m_viewProjectionMatrix;
        memcpy(&Globals::vpMatrix, &Globals::ImmediateRenderer->m_viewProjectionMatrix, 64);
        matrix44 MvpMatrix = Globals::vpMatrix.GetTransposed();
        Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&MvpMatrix));

        //matrix44& ViewMatrix = Globals::RlCameraPtr->m_view_transform;
        //matrix44& ProjectionMatrix = Globals::RlCameraPtr->m_projection_transform;
        //matrix44 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
        //matrix44 TransposedViewProjectionMatrix = ViewProjectionMatrix.GetTransposed();
        //Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&TransposedViewProjectionMatrix));

        //matrix44 ModelMatrix;
        //ModelMatrix.SetToIdentity();
        //rfg_camera& GameData = *Globals::Camera->GameData;
        //matrix44 ViewMatrix(GameData.real_orient.rvec, GameData.real_orient.uvec, GameData.real_orient.fvec, GameData.real_pos);

        //float f = tanf((Globals::pi / 2.0f) - (0.5f - GameData.real_fov));
        //float RangeInv = (1.0f / (GameData.m_near_clip_dist - GameData.m_far_clip_dist));
        //float Aspect = (Globals::WindowRect.right - Globals::WindowRect.left) / (Globals::WindowRect.bottom - Globals::WindowRect.top);
        //vector4 Col1((f / Aspect), 0.0f, 0.0f, 0.0f);
        //vector4 Col2(0.0f, f, 0.0f, 0.0f);
        //vector4 Col3(0.0f, 0.0f, ((GameData.m_near_clip_dist + GameData.m_far_clip_dist) * RangeInv), -1.0f);
        //vector4 Col4(0.0f, 0.0f, (((GameData.m_near_clip_dist - GameData.m_far_clip_dist) * RangeInv) * 2.0f), 0.0f);
        //matrix44 ProjectionMatrix(Col1, Col2, Col3, Col4);
        //Globals::vpMatrix = ProjectionMatrix * ViewMatrix;
        //matrix44 MvpMatrix = ProjectionMatrix * ViewMatrix * ModelMatrix;
        //Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&MvpMatrix));


        //matrix44 TransposedvpMatrix = Globals::vpMatrix.GetTransposed();
        //Globals::DebugDrawRenderInterface->setMvpMatrixPtr(reinterpret_cast<float*>(&TransposedvpMatrix));
    }

    //if (Globals::Camera)
    //{
    //    if (Globals::Camera->GameData)
    //    {
    //        vector& RealUpVec = Globals::Camera->GameData->real_orient.uvec;
    //        Vector3 CameraUpVector(RealUpVec.x, RealUpVec.y, RealUpVec.z);

    //        vector& RealRightVec = Globals::Camera->GameData->real_orient.rvec;
    //        Vector3 CameraRightVector(RealRightVec.x, RealRightVec.y, RealRightVec.z);

    //        vector& RealForwardVec = Globals::Camera->GameData->real_orient.fvec;
    //        Vector3 CameraForwardVector(RealForwardVec.x, RealForwardVec.y, RealForwardVec.z);
    //        Globals::DebugDrawRenderInterface->setCameraFrame(CameraUpVector, CameraRightVector, CameraForwardVector);
    //    }
    //}
}

HRESULT D3D11_DEVICE_CONTEXT_FROM_SWAPCHAIN(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext)
{
    const HRESULT Result = pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<PVOID*>(ppDevice));

    if (Result != S_OK)
    {
        Logger::LogFatalError("ID3D11SwapChain::GetDevice() failed, return value: {}\n", Result);
        return E_FAIL;
    }
    (*ppDevice)->GetImmediateContext(ppContext);

    return Result;
}

void __cdecl Hooks::AllocatorStillValidHook(void* ref_address)
{
    if (ref_address != nullptr)
    {
        delete ref_address;
        ref_address = new unsigned long long[0xFFFFFFF];
    }

    return rfg::AllocatorStillValid(&ref_address);
}