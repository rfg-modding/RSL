#include "CameraWrapper.h"

CameraWrapper::CameraWrapper()
{

}

CameraWrapper::~CameraWrapper()
{

}

void CameraWrapper::Initialize(float InitialCameraSpeed, float InitialCameraRotationSpeed)
{
	uintptr_t ModuleBase = (uintptr_t)GetModuleHandle(NULL);
	GameData = (rfg_camera*)*(DWORD*)(ModuleBase + 0x0023394C);

	RealX = &GameData->real_pos.x;
	RealY = &GameData->real_pos.y;
	RealZ = &GameData->real_pos.z;

	RealRightX = &GameData->real_orient.rvec.x;
	RealRightY = &GameData->real_orient.rvec.y;
	RealRightZ = &GameData->real_orient.rvec.z;

	RealUpX = &GameData->real_orient.uvec.x;
	RealUpY = &GameData->real_orient.uvec.y;
	RealUpZ = &GameData->real_orient.uvec.z;

	RealDirectionX = &GameData->real_orient.fvec.x;
	RealDirectionY = &GameData->real_orient.fvec.y;
	RealDirectionZ = &GameData->real_orient.fvec.z;

	CameraYWriteAddress = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04", (char*)"x???????x???????x???????x???????x???????x???????x???????x???????x?????x???????x?????x???????x???????x????xxxxxxxxx");
	CameraZWriteAddress = FindPattern((char*)"rfg.exe", (char*)"\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04\x66\x00\x00\x00\x00\x00\x00\x00\x8B\x46\x0C\xA3", (char*)"x?????x???????x?????x???????x???????x????xxxxxxxxxx???????xxxx");

	CameraRealOrientWrite1 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", (char*)"x???????x???????x???????x???????x???????x???????x?????x???????x");
	CameraRealOrientWrite2 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", (char*)"x???????x???????x???????x???????x?????x???????x");
	CameraRealOrientWrite3 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8", (char*)"x???????x???????x?????x???????x?????x???????x???????x");
	CameraRealOrientWrite4 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6", (char*)"x???????x?????x???????x???????x????xx");
	CameraRealOrientWrite5 = FindPattern((char*)"rfg.exe", (char*)"\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52", (char*)"x?????x???????x???????x????xxxx");
}

void CameraWrapper::MoveFreeCamera(CameraDirection Direction)
{
	if (Direction == FORWARD)
	{
		*RealX += (*RealDirectionX) * CameraSpeed;
		*RealY += (*RealDirectionY) * CameraSpeed;
		*RealZ += (*RealDirectionZ) * CameraSpeed;
	}
	else if (Direction == BACKWARD)
	{
		*RealX += -1.0f * (*RealDirectionX) * CameraSpeed;
		*RealY += -1.0f * (*RealDirectionY) * CameraSpeed;
		*RealZ += -1.0f * (*RealDirectionZ) * CameraSpeed;
	}
	else if (Direction == LEFT)
	{
		*RealX += -1.0f * (*RealDirectionX) * CameraSpeed;
		*RealY += -1.0f * (*RealDirectionY) * CameraSpeed;
		*RealZ += -1.0f * (*RealDirectionZ) * CameraSpeed;
	}
	else if (Direction == RIGHT)
	{
		*RealX += (*RealDirectionX) * CameraSpeed;
		*RealY += (*RealDirectionY) * CameraSpeed;
		*RealZ += (*RealDirectionZ) * CameraSpeed;
	}
	else if (Direction == UP)
	{
		*RealY += CameraSpeed;
	}
	else if (Direction == DOWN)
	{
		*RealY -= CameraSpeed;
	}
	else
	{
		Logger::Log("Invalid camera direction passed to MoveFreeCamera()", LogError);
	}
}

void CameraWrapper::ActivateFreeCamera()
{
	Logger::Log("Activating free camera", LogInfo);
	FreeCameraActive = true;
	DisableCameraCode(CameraYWriteAddress, CameraZWriteAddress);

	uintptr_t ModuleBase = (uintptr_t)GetModuleHandle(NULL);
	InMultiplayer = (DWORD*)(*(DWORD*)(ModuleBase + 0x002CA210)); //Todo: Fix this. For some reason this needs to be set again here even though it was already set in MainThread().
	
	//Slight adjustments so the player ends up roughly in their original position.
	OriginalCameraPosition.x = *RealX + 2.171509;
	OriginalCameraPosition.y = *RealY;
	OriginalCameraPosition.z = *RealZ + 1.8545898;
}

void CameraWrapper::DeactivateFreeCamera(bool Shutdown)
{
	Logger::Log("Deactivating free camera", LogInfo);
	RestoreCameraCode();

#if EnableSpectatorMode
	if (SlewModeExplicityActivated)
	{
		SlewModeExplicityActivated = false;
		Camera_Stop_Slew_Mode();
	}
#endif
	FreeCameraActive = false;
	if (!Shutdown) //Don't want the player thrown in the air when they deactivate the script loader.
	{
		NeedPostDeactivationCleanup = true; 
	}
	if(GlobalPlayerPtr)
	{
		GlobalPlayerPtr->HitPoints = GlobalPlayerPtr->MaxHitPoints;
		GlobalPlayerPtr->Flags.ai_ignore = false;
	}
}

void CameraWrapper::ToggleFreeCamera()
{
	if (FreeCameraActive)
	{
		DeactivateFreeCamera(false);
	}
	else
	{
		ActivateFreeCamera();
	}
}

bool CameraWrapper::IsFreeCameraActive()
{
	return FreeCameraActive;
}