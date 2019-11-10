#pragma once
#include "CameraDirection.h"
#include "Functions.h"

class vector;
class matrix;

//Todo: Remove all free cam and fps cam funcs once they're moved over to lua. Should be a lightweight wrapper around the games camera
class ICameraManager
{
public:
    ICameraManager(const ICameraManager&) = delete;
    ICameraManager& operator=(const ICameraManager&) = delete;
    virtual ~ICameraManager() noexcept = default;

    virtual void Initialize() = 0;

    virtual void MoveFreeCamera(CameraDirection Direction) = 0;

    virtual bool IsFreeCameraActive() = 0;
    virtual void ActivateFreeCamera() = 0;
    virtual void DeactivateFreeCamera(bool Shutdown) = 0;
    virtual void ToggleFreeCamera() = 0;
    virtual void UpdateFreeView() = 0;

    virtual void ToggleFirstPersonCamera() = 0;
    virtual void ActivateFirstPersonCamera() = 0;
    virtual void DeactivateFirstPersonCamera() = 0;
    virtual bool IsFirstPersonCameraPaused() = 0;
    virtual void PauseFirstPersonCamera() = 0;
    virtual void UnpauseFirstPersonCamera() = 0;
    virtual bool IsFirstPersonCameraActive() = 0;
    virtual void UpdateFirstPersonView() = 0;

    virtual vector GetPosition() = 0;
    virtual void SetPosition(vector& NewPos) = 0;
    virtual void AdjustPosition(vector& Delta) = 0;

    virtual void DisableGameCamera() = 0;
    virtual void EnableGameCamera() = 0;
    virtual bool CameraEnabled() = 0;

    virtual void DisableCameraDirectionCode() = 0;
    virtual void EnableCameraDirectionCode() = 0;
    virtual bool IsCameraDirectionCodeEnabled() = 0;

    virtual vector GetLookDirection() = 0;
    virtual matrix GetLookOrient() = 0;

    float MaxSpeed = 5.0f;

    vector OriginalCameraPosition {0.0f};

    vector FirstPersonCameraOffset { 0.0f, 0.1f, 0.0f };
    bool UseFirstPersonDirectionOffset = true;
    bool UseThirdPersonForVehicles = true;
    float FirstPersonDirectionOffsetMultiplier = 0.18f;
    bool UseFirstPersonAutoPlayerDirection = true;
    float MinAngleDifferenceForRotation = 1.0f;

    bool FreeCamUseWasdMovement = true;
    bool NeedPostDeactivationCleanup = false;

    float* RealX = nullptr;
    float* RealY = nullptr;
    float* RealZ = nullptr;

    float* RealRightX = nullptr;
    float* RealRightY = nullptr;
    float* RealRightZ = nullptr;

    float* RealUpX = nullptr;
    float* RealUpY = nullptr;
    float* RealUpZ = nullptr;

    float* RealDirectionX = nullptr;
    float* RealDirectionY = nullptr;
    float* RealDirectionZ = nullptr;

protected:
    ICameraManager() = default;
};