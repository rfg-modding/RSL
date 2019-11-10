#pragma once
#include "ICameraManager.h"
#include "ISnippetManager.h"

class CameraManager : public ICameraManager
{
public:
    CameraManager();
    ~CameraManager() { }

    void Initialize() override;

    void MoveFreeCamera(CameraDirection Direction) override;

    bool IsFreeCameraActive() override;
    void ActivateFreeCamera() override;
    void DeactivateFreeCamera(bool Shutdown) override;
    void ToggleFreeCamera() override;
    void UpdateFreeView() override;

    void ToggleFirstPersonCamera() override;
    void ActivateFirstPersonCamera() override;
    void DeactivateFirstPersonCamera() override;
    bool IsFirstPersonCameraPaused() override;
    void PauseFirstPersonCamera() override;
    void UnpauseFirstPersonCamera() override;
    bool IsFirstPersonCameraActive() override;
    void UpdateFirstPersonView() override;

    vector GetPosition() override;
    void SetPosition(vector& NewPos) override;
    void AdjustPosition(vector& Delta) override;

    void DisableGameCamera() override;
    void EnableGameCamera() override;
    bool CameraEnabled() override;

    void DisableCameraDirectionCode() override;
    void EnableCameraDirectionCode() override;
    bool IsCameraDirectionCodeEnabled() override;

    vector GetLookDirection() override;
    matrix GetLookOrient() override;
private:
    std::shared_ptr<ISnippetManager> SnippetManager = nullptr;

    rfg_camera* GameData = nullptr;

    bool CameraCodeEnabled = true;
    bool CameraDirectionCodeEnabled = true;

    bool FreeCameraActive = false;
    bool FirstPersonCameraActive = false;
    bool FirstPersonCameraPaused = false;

    vector LastFirstPersonPosition{ 0.0f };
    bool FirstPersonSmoothingEnabled = true;
    bool UseMidpointSmoothing = false;
    float LerpParameter = 0.5f;
    float CurrentSpeed = 2.0f;

    DWORD CameraYWriteAddress = 0;
    DWORD CameraZWriteAddress = 0;

    DWORD CameraRealOrientWrite1 = 0;
    DWORD CameraRealOrientWrite2 = 0;
    DWORD CameraRealOrientWrite3 = 0;
    DWORD CameraRealOrientWrite4 = 0;
    DWORD CameraRealOrientWrite5 = 0;
};

