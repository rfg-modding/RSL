#pragma once

class vector;

class ICameraManager
{
public:
    ICameraManager(const ICameraManager&) = delete;
    ICameraManager& operator=(const ICameraManager&) = delete;
    virtual ~ICameraManager() noexcept = default;

    virtual vector GetPosition() = 0;
    virtual void SetPosition(vector& NewPos) = 0;
    virtual void AdjustPosition(vector& Delta) = 0;

    virtual void DisableGameCamera() = 0;
    virtual void EnableGameCamera() = 0;
    virtual bool CameraEnabled() = 0;

protected:
    ICameraManager() = default;
};