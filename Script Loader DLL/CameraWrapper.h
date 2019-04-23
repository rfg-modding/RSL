#pragma once
///#include "Globals.h"
///#include "SnippetManager.h"
//#include "Hooks.h"
#include "Functions.h"

enum CameraDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class CameraWrapper
{
public:
	CameraWrapper();
	~CameraWrapper();
	
	void Initialize(float InitialCameraSpeed, float InitialCameraRotationSpeed);
	void PrintCameraInfo();

	void MoveFreeCamera(CameraDirection Direction);

	void ActivateFreeCamera();
	void DeactivateFreeCamera(bool Shutdown);
	void ToggleFreeCamera();
	void UpdateFreeView();

	void ActivateFirstPersonCamera();
	void DeactivateFirstPersonCamera();
	void ToggleFirstPersonCamera();
	void UpdateFirstPersonView();

	bool IsFreeCameraActive() const;
	bool IsFirstPersonCameraActive() const;

	float GetCurrentSpeed();
	
	float AccelerationRate = 0.7f;
	float DecelerationRate = 0.5f;
	float MaxSpeed = 2.0f;
	vector Velocity;
	vector OriginalCameraPosition;
	bool NeedPostDeactivationCleanup = false;
	bool ButtonPressedAfterUpdate = false;
	bool SmoothCamera = false;

	vector FirstPersonCameraOffset;
	float FirstPersonDirectionOffsetMultiplier = 0.3f;
	bool UseFirstPersonDirectionOffset = true;
	bool UseFirstPersonAutoPlayerDirection = false;
	bool UseFirstPersonAutoPlayerDirectionAngleOffset = false;
	float FirstPersonAutoPlayerDirectionAngleOffset = 0.0f;

	rfg_camera* GameData = nullptr;

	float* RealX = nullptr;
	float* RealY = nullptr;
	float* RealZ = nullptr;

	//matrix real_orient; //36 Bytes
	//[50, 54, 58] Right
	//[5C, 60, 64] Up
	//[68, 6C, 70] Direction / Forward
	float* RealRightX = nullptr;
	float* RealRightY = nullptr;
	float* RealRightZ = nullptr;
				   
	float* RealUpX = nullptr;
	float* RealUpY = nullptr;
	float* RealUpZ = nullptr;
		 
	float* RealDirectionX = nullptr;
	float* RealDirectionY = nullptr;
	float* RealDirectionZ = nullptr;

	bool UpdatePlayerRvec = true;
	bool UpdatePlayerUvec = true;
	bool UpdatePlayerFvec = true;

	bool UpdateByAxis = true;
	bool UpdateX = true;
	bool UpdateY = true;
	bool UpdateZ = true;

private:
	bool FreeCameraActive = false;
	bool FirstPersonCameraActive = false;

	float CurrentSpeed = 2.0f;

	DWORD CameraYWriteAddress;
	DWORD CameraZWriteAddress;
								
	DWORD CameraRealOrientWrite1;
	DWORD CameraRealOrientWrite2;
	DWORD CameraRealOrientWrite3;
	DWORD CameraRealOrientWrite4;
	DWORD CameraRealOrientWrite5;
};