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

	void ActivateFirstPersonCamera();
	void DeactivateFirstPersonCamera();
	void ToggleFirstPersonCamera();
	vector FirstPersonCameraOffset;

	bool IsFreeCameraActive() const;
	bool IsFirstPersonCameraActive() const;

	float CameraSpeed = 2.0f;

	vector OriginalCameraPosition;
	bool NeedPostDeactivationCleanup = false;

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

private:
	bool FreeCameraActive = false;
	bool FirstPersonCameraActive = false;

	DWORD CameraYWriteAddress;
	DWORD CameraZWriteAddress;
								
	DWORD CameraRealOrientWrite1;
	DWORD CameraRealOrientWrite2;
	DWORD CameraRealOrientWrite3;
	DWORD CameraRealOrientWrite4;
	DWORD CameraRealOrientWrite5;
};