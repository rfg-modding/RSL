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
	RealX = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x2C);
	RealY = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x30);
	RealZ = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x34);

	//matrix real_orient; //36 Bytes
	//[50, 54, 58] Right
	//[5C, 60, 64] Up
	//[68, 6C, 70] Direction / Forward
	RealRightX = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x50);//
	RealRightY = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x54);
	RealRightZ = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x58);//
	
	RealUpX = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x5C);
	RealUpY = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x60);//
	RealUpZ = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x64);
	
	RealDirectionX = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x68);//
	RealDirectionY = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x6C);
	RealDirectionZ = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0x70);//4
	
	RealFOV = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0xBC);
	IdealFOV = (DWORD*)((*(DWORD*)(ModuleBase + 0x0023394C)) + 0xC0);

	SetCameraSpeed(InitialCameraSpeed, false);
	SetCameraRotationSpeed(InitialCameraRotationSpeed, false);

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
#if !PublicMode
	std::cout << "~~~ Camera data dump ~~~" << std::endl;
	std::cout << "CameraX = " << *(float*)RealX << std::endl;
	std::cout << "CameraY = " << *(float*)RealY << std::endl;
	std::cout << "CameraZ = " << *(float*)RealZ << std::endl;

	std::cout << "CameraRightX = " << *(float*)RealRightX << std::endl;
	std::cout << "CameraRightY = " << *(float*)RealRightY << std::endl;
	std::cout << "CameraRightZ = " << *(float*)RealRightZ << std::endl;

	std::cout << "CameraUpX = " << *(float*)RealUpX << std::endl;
	std::cout << "CameraUpY = " << *(float*)RealUpY << std::endl;
	std::cout << "CameraUpZ = " << *(float*)RealUpZ << std::endl;

	std::cout << "CameraDirectionX = " << *(float*)RealDirectionX << std::endl;
	std::cout << "CameraDirectionY = " << *(float*)RealDirectionY << std::endl;
	std::cout << "CameraDirectionZ = " << *(float*)RealDirectionZ << std::endl;

	std::cout << "CameraVelocity = " << CameraSpeed << std::endl;

	std::cout << "Pitch = " << Pitch << std::endl;
	std::cout << "Yaw = " << Yaw << std::endl;
	std::cout << "Roll = " << Roll << std::endl;

	std::cout << std::endl;
#endif
}

void CameraWrapper::MoveFreeCamera(CameraDirection Direction)
{
	if (Direction == FORWARD)
	{
		AdjustRealX(GetRealDirectionX() * CameraSpeed);
		AdjustRealY(GetRealDirectionY() * CameraSpeed);
		AdjustRealZ(GetRealDirectionZ() * CameraSpeed);
	}
	else if (Direction == BACKWARD)
	{
		AdjustRealX(-1.0f * GetRealDirectionX() * CameraSpeed);
		AdjustRealY(-1.0f * GetRealDirectionY() * CameraSpeed);
		AdjustRealZ(-1.0f * GetRealDirectionZ() * CameraSpeed);
	}
	else if (Direction == LEFT)
	{
		AdjustRealX(-1.0f * GetRealRightX() * CameraSpeed);
		AdjustRealY(-1.0f * GetRealRightY() * CameraSpeed);
		AdjustRealZ(-1.0f * GetRealRightZ() * CameraSpeed);
	}
	else if (Direction == RIGHT)
	{
		AdjustRealX(GetRealRightX() * CameraSpeed);
		AdjustRealY(GetRealRightY() * CameraSpeed);
		AdjustRealZ(GetRealRightZ() * CameraSpeed);
	}
	else if (Direction == UP)
	{
		AdjustRealY(CameraSpeed);
	}
	else if (Direction == DOWN)
	{
		AdjustRealY(-1.0f * CameraSpeed);
	}
	else
	{
		ConsoleLog("Invalid camera direction passed to MoveFreeCamera()", LOGERROR, false, true);
	}
}

void CameraWrapper::RecalculateOrientationMatrix()
{
	/*
	See the second answer (xyz form) in the link below for the math used here. 
	Switched pitch and yaw since the axes are different: https://stackoverflow.com/questions/1568568/how-to-convert-euler-angles-to-directional-vector
	*/
	*(float*)RealRightX = cosd(Yaw) * cosd(Roll);
	*(float*)RealUpX = -1.0f * cosd(Yaw) * sind(Roll);
	*(float*)RealDirectionX = sind(Yaw);
			 
	*(float*)RealRightY = cosd(Roll) * sind(Pitch) * sind(Yaw) + cosd(Pitch) * sind(Roll);
	*(float*)RealUpY = cosd(Pitch) * cosd(Roll) - sind(Pitch) * sind(Yaw) * sind(Roll);
	*(float*)RealDirectionY = -1.0f * cosd(Yaw) * sind(Pitch);
			 
	*(float*)RealRightZ = 1.0f * cosd(Roll) * sind(Yaw) + sind(Pitch) * sind(Roll);
	*(float*)RealUpZ = cosd(Roll) * sind(Pitch) + 1.0f * sind(Yaw) * sind(Roll);
	*(float*)RealDirectionZ = cosd(Pitch) * cosd(Yaw);
}

void CameraWrapper::ActivateFreeCamera()
{
	ConsoleLog("Activating free camera\n", LOGMESSAGE);
	FreeCameraActive = true;
	DisableCameraCode(CameraYWriteAddress, CameraZWriteAddress);

	uintptr_t ModuleBase = (uintptr_t)GetModuleHandle(NULL);
	InMultiplayer = (DWORD*)(*(DWORD*)(ModuleBase + 0x002CA210)); //Todo: Fix this. For some reason this needs to be set again here even though it was already set in MainThread().
	
#if EnableSpectatorMode
	if (*(bool*)InMultiplayer)
	{
		SlewModeExplicityActivated = true;
		Camera_Start_Slew_Mode();
	}
#endif
}

void CameraWrapper::ActivateRotationControl()
{
	ConsoleLog("Activating rotation control\n", LOGMESSAGE);
	DisableCameraDirectionCode(CameraRealOrientWrite1, CameraRealOrientWrite2, CameraRealOrientWrite3, CameraRealOrientWrite4, CameraRealOrientWrite5);

	//Roll = 0;
	//GetCursorPos(&OriginalPosition);
	//RollLocked = true;
	InitialPitch = Pitch;
	InitialYaw = Yaw;
	InitialRoll = Roll;
	RotationControlActive = true;
}

void CameraWrapper::DeactivateFreeCamera()
{
	ConsoleLog("Deactivating free camera\n", LOGMESSAGE);
	RestoreCameraCode();

#if EnableSpectatorMode
	if (SlewModeExplicityActivated)
	{
		SlewModeExplicityActivated = false;
		Camera_Stop_Slew_Mode();
	}
#endif
	FreeCameraActive = false;
}

void CameraWrapper::DeactivateRotationControl()
{
	ConsoleLog("Deactivating rotation control\n", LOGMESSAGE);
	RestoreCameraDirectionCode();
	RotationControlActive = false;
	RollLocked = false;
}

void CameraWrapper::ToggleFreeCamera()
{
	if (FreeCameraActive)
	{
		DeactivateFreeCamera();
	}
	else
	{
		ActivateFreeCamera();
	}
}

void CameraWrapper::ToggleRotationControls()
{
	if (RotationControlActive)
	{
		DeactivateRotationControl();
	}
	else
	{
		ActivateRotationControl();
	}
}

bool CameraWrapper::IsFreeCameraActive()
{
	return FreeCameraActive;
}

bool CameraWrapper::IsRotationControlActive()
{
	return RotationControlActive;
}

void CameraWrapper::EnforcePitchLimits(float Minimum, float Maximum)
{
	if (Pitch < Minimum)
	{
		Pitch = Minimum;
	}
	if (Pitch > Maximum)
	{
		Pitch = Maximum;
	}
}

bool CameraWrapper::IsPitchLocked()
{
	return PitchLocked;
}

bool CameraWrapper::IsYawLocked()
{
	return YawLocked;
}

bool CameraWrapper::IsRollLocked()
{
	return RollLocked;
}

void CameraWrapper::LockPitch()
{
	PitchLocked = true;
	PreLockPitch = Pitch;
}

void CameraWrapper::LockYaw()
{
	YawLocked = true;
	PreLockYaw = Yaw;
}

void CameraWrapper::LockRoll()
{
	RollLocked = true;
	PreLockRoll = Roll;
}

void CameraWrapper::UnlockPitch()
{
	PitchLocked = false;
	Pitch = PreLockPitch;
}

void CameraWrapper::UnlockYaw()
{
	YawLocked = false;
	Yaw = PreLockYaw;
}

void CameraWrapper::UnlockRoll()
{
	RollLocked = false;
	Roll = PreLockRoll;
}

bool CameraWrapper::TogglePitchLock()
{
	if (PitchLocked)
	{
		UnlockPitch();
	}
	else
	{
		LockPitch();
	}
	return PitchLocked;
}

bool CameraWrapper::ToggleYawLock()
{
	if (YawLocked)
	{
		UnlockYaw();
	}
	else
	{
		LockYaw();
	}
	return YawLocked;
}

bool CameraWrapper::ToggleRollLock()
{
	if (RollLocked)
	{
		UnlockRoll();
	}
	else
	{
		LockRoll();
	}
	return RollLocked;
}


/*Getters start here*/


float CameraWrapper::GetRealX()
{
	return *(float*)RealX;
}

float CameraWrapper::GetRealY()
{
	return *(float*)RealY;
}

float CameraWrapper::GetRealZ()
{
	return *(float*)RealZ;
}

float CameraWrapper::GetRealRightX()
{
	return *(float*)RealRightX;
}

float CameraWrapper::GetRealRightY()
{
	return *(float*)RealRightY;
}

float CameraWrapper::GetRealRightZ()
{
	return *(float*)RealRightZ;
}

float CameraWrapper::GetRealUpX()
{
	return *(float*)RealUpX;
}

float CameraWrapper::GetRealUpY()
{
	return *(float*)RealUpY;
}

float CameraWrapper::GetRealUpZ()
{
	return *(float*)RealUpZ;
}

float CameraWrapper::GetRealDirectionX()
{
	return *(float*)RealDirectionX;
}

float CameraWrapper::GetRealDirectionY()
{
	return *(float*)RealDirectionY;
}

float CameraWrapper::GetRealDirectionZ()
{
	return *(float*)RealDirectionZ;
}

float CameraWrapper::GetRealFOV()
{
	return *(float*)RealFOV;
}

float CameraWrapper::GetIdealFOV()
{
	return *(float*)IdealFOV;
}

float CameraWrapper::GetCustomFOV()
{
	return CustomFOV;
}

float CameraWrapper::GetPitch()
{
	return Pitch;
}

float CameraWrapper::GetYaw()
{
	return Yaw;
}

float CameraWrapper::GetRoll()
{
	return Roll;
}

float CameraWrapper::GetCameraSpeed()
{
	return CameraSpeed;
}

float CameraWrapper::GetCameraRotationSpeed()
{
	return CameraRotationSpeed;
}

float CameraWrapper::GetInitialPitch()
{
	return InitialPitch;
}

float CameraWrapper::GetInitialYaw()
{
	return InitialYaw;
}

float CameraWrapper::GetInitialRoll()
{
	return InitialRoll;
}

float CameraWrapper::GetPreLockPitch()
{
	return PreLockPitch;
}

float CameraWrapper::GetPreLockYaw()
{
	return PreLockYaw;
}

float CameraWrapper::GetPreLockRoll()
{
	return PreLockRoll;
}


/*Setters start here*/


void CameraWrapper::SetRealX(float Value)
{
	*(float*)RealX = Value;
}

void CameraWrapper::SetRealY(float Value)
{
	*(float*)RealY = Value;
}

void CameraWrapper::SetRealZ(float Value)
{
	*(float*)RealZ = Value;
}

void CameraWrapper::SetRealRightX(float Value)
{
	*(float*)RealRightX = Value;
}

void CameraWrapper::SetRealRightY(float Value)
{
	*(float*)RealRightY = Value;
}

void CameraWrapper::SetRealRightZ(float Value)
{
	*(float*)RealRightZ = Value;
}

void CameraWrapper::SetRealUpX(float Value)
{
	*(float*)RealUpX = Value;
}

void CameraWrapper::SetRealUpY(float Value)
{
	*(float*)RealUpY = Value;
}

void CameraWrapper::SetRealUpZ(float Value)
{
	*(float*)RealUpZ = Value;
}

void CameraWrapper::SetRealDirectionX(float Value)
{
	*(float*)RealDirectionX = Value;
}

void CameraWrapper::SetRealDirectionY(float Value)
{
	*(float*)RealDirectionY = Value;
}

void CameraWrapper::SetRealDirectionZ(float Value)
{
	*(float*)RealDirectionZ = Value;
}

void CameraWrapper::SetRealFOV(float Value)
{
	*(float*)RealFOV = Value;
}

void CameraWrapper::SetIdealFOV(float Value)
{
	*(float*)IdealFOV = Value;
}

void CameraWrapper::SetCustomFOV(float Value)
{
	CustomFOV = Value;
}

void CameraWrapper::SetPitch(float Value)
{
	Pitch = Value;
}

void CameraWrapper::SetYaw(float Value)
{
	Yaw = Value;
}

void CameraWrapper::SetRoll(float Value)
{
	Roll = Value;
}

void CameraWrapper::SetCameraSpeed(float Value, bool LogValue)
{
	CameraSpeed = Value;
	if (LogValue)
	{
		ConsoleLog(std::string("Camera Speed: " + std::to_string(CameraSpeed) + "\n").c_str(), LOGMESSAGE);
	}
}

void CameraWrapper::SetCameraRotationSpeed(float Value, bool LogValue)
{	
	CameraRotationSpeed = Value;
	if (LogValue)
	{
		ConsoleLog(std::string("Rotation Speed: " + std::to_string(CameraRotationSpeed) + "\n").c_str(), LOGMESSAGE);
	}
}

void CameraWrapper::SetInitialPitch(float Value)
{
	InitialPitch = Value;
}

void CameraWrapper::SetInitialYaw(float Value)
{
	InitialYaw = Value;
}

void CameraWrapper::SetInitialRoll(float Value)
{
	InitialRoll = Value;
}

void CameraWrapper::SetPreLockPitch(float Value)
{
	PreLockPitch = Value;
}

void CameraWrapper::SetPreLockYaw(float Value)
{
	PreLockYaw = Value;
}

void CameraWrapper::SetPreLockRoll(float Value)
{
	PreLockRoll = Value;
}


/*Adjusters start here*/


void CameraWrapper::AdjustRealX(float Value)
{
	*(float*)RealX += Value;
}

void CameraWrapper::AdjustRealY(float Value)
{
	*(float*)RealY += Value;
}

void CameraWrapper::AdjustRealZ(float Value)
{
	*(float*)RealZ += Value;
}

void CameraWrapper::AdjustRealRightX(float Value)
{
	*(float*)RealRightX += Value;
}

void CameraWrapper::AdjustRealRightY(float Value)
{
	*(float*)RealRightY += Value;
}

void CameraWrapper::AdjustRealRightZ(float Value)
{
	*(float*)RealRightZ += Value;
}

void CameraWrapper::AdjustRealUpX(float Value)
{
	*(float*)RealUpX += Value;
}

void CameraWrapper::AdjustRealUpY(float Value)
{
	*(float*)RealUpY += Value;
}

void CameraWrapper::AdjustRealUpZ(float Value)
{
	*(float*)RealUpZ += Value;
}

void CameraWrapper::AdjustRealDirectionX(float Value)
{
	*(float*)RealDirectionX += Value;
}

void CameraWrapper::AdjustRealDirectionY(float Value)
{
	*(float*)RealDirectionY += Value;
}

void CameraWrapper::AdjustRealDirectionZ(float Value)
{
	*(float*)RealDirectionZ += Value;
}

void CameraWrapper::AdjustRealFOV(float Value)
{
	*(float*)RealFOV += Value;
}

void CameraWrapper::AdjustIdealFOV(float Value)
{
	*(float*)IdealFOV += Value;
}

void CameraWrapper::AdjustCustomFOV(float Value)
{
	CustomFOV += Value;
}

void CameraWrapper::AdjustPitch(float Value)
{
	if (!PitchLocked)
	{
		Pitch += Value;
		ConsoleLog(std::string("Pitch: " + std::to_string(Pitch) + "\n").c_str(), LOGMESSAGE, false, true);
	}
}

void CameraWrapper::AdjustYaw(float Value)
{
	if (!YawLocked)
	{
		Yaw += Value;
		ConsoleLog(std::string("Yaw: " + std::to_string(Yaw) + "\n").c_str(), LOGMESSAGE, false, true);
		//RecalculateOrientationMatrix();
	}
}

void CameraWrapper::AdjustRoll(float Value)
{
	if (!RollLocked)
	{
		Roll += Value;
		ConsoleLog(std::string("Roll: " + std::to_string(Roll) + "\n").c_str(), LOGMESSAGE, false, true);
		//RecalculateOrientationMatrix();
	}
}

void CameraWrapper::AdjustCameraSpeed(float Value)
{
	ConsoleLog(std::string("Camera Speed: " + std::to_string(CameraSpeed) + "\n").c_str(), LOGMESSAGE);
	CameraSpeed += Value;
	if (CameraSpeed < 0.0f)
	{
		CameraSpeed = 0.0f;
	}
}

void CameraWrapper::AdjustCameraRotationSpeed(float Value)
{
	ConsoleLog(std::string("Rotation Speed: " + std::to_string(CameraRotationSpeed) + "\n").c_str(), LOGMESSAGE);
	CameraRotationSpeed += Value;
}

void CameraWrapper::AdjustInitialPitch(float Value)
{
	InitialPitch += Value;
}

void CameraWrapper::AdjustInitialYaw(float Value)
{
	InitialYaw += Value;
}

void CameraWrapper::AdjustInitialRoll(float Value)
{
	InitialRoll += Value;
}

void CameraWrapper::AdjustPreLockPitch(float Value)
{
	PreLockPitch += Value;
}

void CameraWrapper::AdjustPreLockYaw(float Value)
{
	PreLockYaw += Value;
}

void CameraWrapper::AdjustPreLockRoll(float Value)
{
	PreLockRoll += Value;
}

