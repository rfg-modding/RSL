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

	bool IsFreeCameraActive();

	float CameraSpeed = 2.0f;

	vector OriginalCameraPosition;
	bool NeedPostDeactivationCleanup = false;

	glm::mat3x3 RealOrientationMatrix;
	glm::vec3 RealPositionVector;

	float* RealX;
	float* RealY;
	float* RealZ;

	//matrix real_orient; //36 Bytes
	//[50, 54, 58] Right
	//[5C, 60, 64] Up
	//[68, 6C, 70] Direction / Forward
	float* RealRightX;
	float* RealRightY;
	float* RealRightZ;
					   
	float* RealUpX;
	float* RealUpY;
	float* RealUpZ;

	float* RealDirectionX;
	float* RealDirectionY;
	float* RealDirectionZ;

	float Pitch = 0.0f;
	float Yaw = 0.0f;
	float Roll = 0.0f;

	//float CameraSpeed = 0.7f;
	float CameraRotationSpeed = 5.0f;

	bool FreeCameraActive = false;
	bool RotationControlActive = false;
	bool SlewModeExplicityActivated = false;

	bool PitchLocked = false;
	bool YawLocked = false;
	bool RollLocked = false;

	float InitialPitch = 0.0f;
	float InitialYaw = 0.0f;
	float InitialRoll = 0.0f;

	float PreLockPitch = 0.0f;
	float PreLockYaw = 0.0f;
	float PreLockRoll = 0.0f;

	DWORD CameraYWriteAddress;
	DWORD CameraZWriteAddress;
								
	DWORD CameraRealOrientWrite1;
	DWORD CameraRealOrientWrite2;
	DWORD CameraRealOrientWrite3;
	DWORD CameraRealOrientWrite4;
	DWORD CameraRealOrientWrite5;
};