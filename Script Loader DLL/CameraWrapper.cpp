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
	RealX = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x2C);
	RealY = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x30);
	RealZ = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x34);

	//matrix real_orient; //36 Bytes
	//[50, 54, 58] Right
	//[5C, 60, 64] Up
	//[68, 6C, 70] Direction / Forward
	RealRightX = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x50);//
	RealRightY = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x54);
	RealRightZ = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x58);//
	
	RealUpX = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x5C);
	RealUpY = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x60);//
	RealUpZ = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x64);
	
	RealDirectionX = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x68);//
	RealDirectionY = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x6C);
	RealDirectionZ = (float*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x70);//4
	

	float x = *(float*)RealDirectionX;
	float y = *(float*)RealDirectionY;
	Yaw = x / (-1.0f * y); //atan(*(float*)CameraDirectionX / (-1.0 * (*(float*)CameraDirectionY)));
	float x2 = pow(x, 2);
	float y2 = pow(y, 2);
	float z = *(float*)RealDirectionZ;
	Pitch = sqrt(x2 + y2) / z; //atan(sqrt(pow(*(float*)CameraDirectionX, 2) + pow(*(float*)CameraDirectionY, 2)) / (*(float*)CameraDirectionZ));
	Roll = 0;

	CameraYWriteAddress = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04", (char*)"x???????x???????x???????x???????x???????x???????x???????x???????x?????x???????x?????x???????x???????x????xxxxxxxxx");
	CameraZWriteAddress = FindPattern((char*)"rfg.exe", (char*)"\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04\x66\x00\x00\x00\x00\x00\x00\x00\x8B\x46\x0C\xA3", (char*)"x?????x???????x?????x???????x???????x????xxxxxxxxxx???????xxxx");

	CameraRealOrientWrite1 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", (char*)"x???????x???????x???????x???????x???????x???????x?????x???????x");
	CameraRealOrientWrite2 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", (char*)"x???????x???????x???????x???????x?????x???????x");
	CameraRealOrientWrite3 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8", (char*)"x???????x???????x?????x???????x?????x???????x???????x");
	CameraRealOrientWrite4 = FindPattern((char*)"rfg.exe", (char*)"\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6", (char*)"x???????x?????x???????x???????x????xx");
	CameraRealOrientWrite5 = FindPattern((char*)"rfg.exe", (char*)"\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52", (char*)"x?????x???????x???????x????xxxx");
}

void CameraWrapper::PrintCameraInfo()
{
	std::cout << "~~~ Camera data dump ~~~" << "\n";
	std::cout << "CameraX = " << *RealX << "\n";
	std::cout << "CameraY = " << *RealY << "\n";
	std::cout << "CameraZ = " << *RealZ << "\n";

	std::cout << "CameraRightX = " << *RealRightX << "\n";
	std::cout << "CameraRightY = " << *RealRightY << "\n";
	std::cout << "CameraRightZ = " << *RealRightZ << "\n";

	std::cout << "CameraUpX = " << *RealUpX << "\n";
	std::cout << "CameraUpY = " << *RealUpY << "\n";
	std::cout << "CameraUpZ = " << *RealUpZ << "\n";

	std::cout << "CameraDirectionX = " << *RealDirectionX << "\n";
	std::cout << "CameraDirectionY = " << *RealDirectionY << "\n";
	std::cout << "CameraDirectionZ = " << *RealDirectionZ << "\n";

	std::cout << "CameraVelocity = " << CameraSpeed << "\n";

	std::cout << "Pitch = " << Pitch << "\n";
	std::cout << "Yaw = " << Yaw << "\n";
	std::cout << "Roll = " << Roll << "\n";

	std::cout << "\n";
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
		*RealZ += CameraSpeed;
	}
	else if (Direction == DOWN)
	{
		*RealZ -= CameraSpeed;
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
	OriginalCameraPosition.x = *(float*)RealX + 2.171509;
	OriginalCameraPosition.y = *(float*)RealY;
	OriginalCameraPosition.z = *(float*)RealZ + 1.8545898;
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