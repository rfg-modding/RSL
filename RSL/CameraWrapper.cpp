#include "CameraWrapper.h"

void CameraWrapper::Initialize(float InitialCameraSpeed, float InitialCameraRotationSpeed)
{
	GameData = reinterpret_cast<rfg_camera*>(*(DWORD*)(Globals::ModuleBase + 0x0023394C));

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

	CameraYWriteAddress = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04", "x???????x???????x???????x???????x???????x???????x???????x???????x?????x???????x?????x???????x???????x????xxxxxxxxx");
	CameraZWriteAddress = Globals::FindPattern("rfg.exe", "\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04\x66\x00\x00\x00\x00\x00\x00\x00\x8B\x46\x0C\xA3", "x?????x???????x?????x???????x???????x????xxxxxxxxxx???????xxxx");

	CameraRealOrientWrite1 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", "x???????x???????x???????x???????x???????x???????x?????x???????x");
	CameraRealOrientWrite2 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", "x???????x???????x???????x???????x?????x???????x");
	CameraRealOrientWrite3 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8", "x???????x???????x?????x???????x?????x???????x???????x");
	CameraRealOrientWrite4 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6", "x???????x?????x???????x???????x????xx");
	CameraRealOrientWrite5 = Globals::FindPattern("rfg.exe", "\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52", "x?????x???????x???????x????xxxx");
}

void CameraWrapper::MoveFreeCamera(CameraDirection Direction)
{
	if(FreeCameraActive)
	{
		if(SmoothCamera)
		{
			//CurrentSpeed = Velocity.Magnitude();
			//if(CurrentSpeed >= MaxSpeed)
			//{
			//	return;
			//}
			if (Direction == FORWARD)
			{
				Velocity.x += (*RealDirectionX) * AccelerationRate;
				Velocity.y += (*RealDirectionY) * AccelerationRate;
				Velocity.z += (*RealDirectionZ) * AccelerationRate;
			}
			else if (Direction == BACKWARD)
			{
				Velocity.x += -1.0f * (*RealDirectionX) * AccelerationRate;
				Velocity.y += -1.0f * (*RealDirectionY) * AccelerationRate;
				Velocity.z += -1.0f * (*RealDirectionZ) * AccelerationRate;
			}
			else if (Direction == LEFT)
			{
				Velocity.x += -1.0f * (*RealRightX) * AccelerationRate;
				Velocity.y += -1.0f * (*RealRightY) * AccelerationRate;
				Velocity.z += -1.0f * (*RealRightZ) * AccelerationRate;
			}
			else if (Direction == RIGHT)
			{
				Velocity.x += (*RealRightX) * AccelerationRate;
				Velocity.y += (*RealRightY) * AccelerationRate;
				Velocity.z += (*RealRightZ) * AccelerationRate;
			}
			else if (Direction == UP)
			{
				Velocity.y += AccelerationRate;
			}
			else if (Direction == DOWN)
			{
				Velocity.y -= AccelerationRate;
			}
			else
			{
				Logger::LogError("Invalid camera direction passed to MoveFreeCamera()\n");
			}
			ButtonPressedAfterUpdate = true;
		}
		else
		{
			if (Direction == FORWARD)
			{
				*RealX += (*RealDirectionX) * MaxSpeed;
				*RealY += (*RealDirectionY) * MaxSpeed;
				*RealZ += (*RealDirectionZ) * MaxSpeed;
			}
			else if (Direction == BACKWARD)
			{
				*RealX += -1.0f * (*RealDirectionX) * MaxSpeed;
				*RealY += -1.0f * (*RealDirectionY) * MaxSpeed;
				*RealZ += -1.0f * (*RealDirectionZ) * MaxSpeed;
			}
			else if (Direction == LEFT)
			{
				*RealX += -1.0f * (*RealRightX) * MaxSpeed;
				*RealY += -1.0f * (*RealRightY) *MaxSpeed;
				*RealZ += -1.0f * (*RealRightZ) *MaxSpeed;
			}
			else if (Direction == RIGHT)
			{
				*RealX += (*RealRightX) * MaxSpeed;
				*RealY += (*RealRightY) * MaxSpeed;
				*RealZ += (*RealRightZ) * MaxSpeed;
			}
			else if (Direction == UP)
			{
				*RealY += MaxSpeed;
			}
			else if (Direction == DOWN)
			{
				*RealY -= MaxSpeed;
			}
			else
			{
				Logger::LogError("Invalid camera direction passed to MoveFreeCamera()\n");
			}
		}

	}
}

void CameraWrapper::ActivateFreeCamera()
{
    if(FirstPersonCameraActive)
    {
        Logger::LogError("Failed to activate free camera. First person cam already active.\n");
        return;
    }
	Logger::Log("Activating free camera\n");
	FreeCameraActive = true;
	DisableCameraCode(CameraYWriteAddress, CameraZWriteAddress);

	//Slight adjustments so the player ends up roughly in their original position.
	OriginalCameraPosition.x = *RealX + 2.171509;
	OriginalCameraPosition.y = *RealY;
	OriginalCameraPosition.z = *RealZ + 1.8545898;
}

void CameraWrapper::DeactivateFreeCamera(bool Shutdown)
{
	Logger::Log("Deactivating free camera\n");
	RestoreCameraCode();

	FreeCameraActive = false;
	if (!Shutdown) //Don't want the player thrown in the air when they deactivate the script loader.
	{
		NeedPostDeactivationCleanup = true; 
	}
	if(Globals::PlayerPtr)
	{
		Globals::PlayerPtr->HitPoints = Globals::PlayerPtr->MaxHitPoints;
		Globals::PlayerPtr->Flags.ai_ignore = false;
		Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls = false;
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
		if(!FirstPersonCameraActive)
		{
			ActivateFreeCamera();
		}
		else
		{
			Logger::LogError("Failed to activate free camera. First person cam already active.\n");
		}
	}
}

void CameraWrapper::UpdateFreeView()
{
	if(SmoothCamera)
	{
		*RealX += Velocity.x;
		*RealY += Velocity.y;
		*RealZ += Velocity.z;
		if (!ButtonPressedAfterUpdate)
		{
			if (abs(Velocity.x) > 0.0f)
			{
				if (Velocity.x < 0.0f)
				{
					Velocity.x += DecelerationRate;
					if (Velocity.x > 0.0f)
					{
						Velocity.x = 0.0f;
					}
				}
				else if (Velocity.x > 0.0f)
				{
					Velocity.x -= DecelerationRate;
					if (Velocity.x < 0.0f)
					{
						Velocity.x = 0.0f;
					}
				}
			}
			if (abs(Velocity.y) > 0.0f)
			{
				if (Velocity.y < 0.0f)
				{
					Velocity.y += DecelerationRate;
					if (Velocity.y > 0.0f)
					{
						Velocity.y = 0.0f;
					}
				}
				else if (Velocity.y > 0.0f)
				{
					Velocity.y -= DecelerationRate;
					if (Velocity.y < 0.0f)
					{
						Velocity.y = 0.0f;
					}
				}
			}
			if (abs(Velocity.z) > 0.0f)
			{
				if (Velocity.z < 0.0f)
				{
					Velocity.z += DecelerationRate;
					if (Velocity.z > 0.0f)
					{
						Velocity.z = 0.0f;
					}
				}
				else if (Velocity.z > 0.0f)
				{
					Velocity.z -= DecelerationRate;
					if (Velocity.z < 0.0f)
					{
						Velocity.z = 0.0f;
					}
				}
			}
		}
		//if(Velocity.x > MaxSpeed)
		//{
		//	Velocity.x = MaxSpeed;
		//}	
		//if(Velocity.y > MaxSpeed)
		//{
		//	Velocity.y = MaxSpeed;
		//}	
		//if(Velocity.z > MaxSpeed)
		//{
		//	Velocity.z = MaxSpeed;
		//}

		CurrentSpeed = Velocity.Magnitude();
		ButtonPressedAfterUpdate = false;
	}
}

void CameraWrapper::ActivateFirstPersonCamera()
{
    if(FreeCameraActive)
    {
        Logger::LogWarning("Failed to activate the first person camera since free camera is already active!.\n");
        return;
    }
	Logger::Log("Activating first person camera\n");
	FirstPersonCameraActive = true;
	DisableCameraCode(CameraYWriteAddress, CameraZWriteAddress);
    LastFirstPersonPosition = Globals::PlayerPtr->Position;
}

void CameraWrapper::DeactivateFirstPersonCamera()
{
	Logger::Log("Deactivating first person camera\n");
	RestoreCameraCode();

	FirstPersonCameraActive = false;
	FreeCameraActive = false;
	NeedPostDeactivationCleanup = false;
}

void CameraWrapper::ToggleFirstPersonCamera()
{
	if (FirstPersonCameraActive)
	{
		DeactivateFirstPersonCamera();
	}
	else
	{ 
		if(!FreeCameraActive)
		{
			ActivateFirstPersonCamera();
		}
		else
		{
			Logger::LogError("Failed to activate first person camera. Free cam already active.\n");
		}
	}
}

void CameraWrapper::UpdateFirstPersonView()
{
    if(FirstPersonCameraPaused)
    {
        return;
    }
    vector HeadVector(0.0f);
    matrix HeadMatrix(0.0f);

    human_get_head_pos_orient(Globals::PlayerPtr, HeadVector, HeadMatrix);

    vector NewPos = GameData->real_pos;


    NewPos = HeadVector + FirstPersonCameraOffset;
    CurrentSpeed = Globals::PlayerPtr->Velocity.Magnitude(); //Note: Not sure what the point of this line is...
    if (UseFirstPersonDirectionOffset)
    {
        vector TempVec = Globals::PlayerPtr->Orientation.fvec;
        NewPos += TempVec.Scale(FirstPersonDirectionOffsetMultiplier);
    }

    if(FirstPersonSmoothingEnabled) //Doesn't really seem to help vehicle shakiness much. 
    {
        if(UseMidpointSmoothing)
        {
            vector TempVec = NewPos;
            NewPos = LastFirstPersonPosition.Midpoint(TempVec);
        }
        else
        {
            vector TempVec = NewPos;
            NewPos = LastFirstPersonPosition.Lerp(TempVec, LerpParameter);
        }
    }

    if(UseFirstPersonAutoPlayerDirection)
    {
        vector2 CamFvec{ GameData->real_orient.fvec.x, GameData->real_orient.fvec.z };
        vector2 PlayerFvec{ Globals::PlayerPtr->Orientation.fvec.x, Globals::PlayerPtr->Orientation.fvec.z };
        float DotProduct = CamFvec * PlayerFvec;
        float MagProduct = CamFvec.Magnitude() * PlayerFvec.Magnitude();
        float AngleRadians = acos(DotProduct / MagProduct);

        float Angle2 = atan2((PlayerFvec.x * CamFvec.y) - (PlayerFvec.y * CamFvec.x), (PlayerFvec.x * CamFvec.x) - (PlayerFvec.y * CamFvec.y));

        if(abs(Globals::FloatConvertRadiansToDegrees(AngleRadians)) > MinAngleDifferenceForRotation)
        {
            vector YAxis = { 0.0f, 1.0f, 0.0f };

            if (Angle2 > 0.0f)
            {
                AngleRadians *= -1.0f;
            }
            matrix_rotate_around_local_vector(&Globals::PlayerPtr->Orientation, nullptr, YAxis, AngleRadians);
        }
    }

    GameData->real_pos = NewPos;
    LastFirstPersonPosition = GameData->real_pos;
}

bool CameraWrapper::IsFreeCameraActive() const
{
	return FreeCameraActive;
}

bool CameraWrapper::IsFirstPersonCameraActive() const
{
	return FirstPersonCameraActive;
}

bool CameraWrapper::IsFirstPersonCameraPaused() const
{
    return FirstPersonCameraPaused;
}

void CameraWrapper::PauseFirstPersonCamera()
{
    if(FirstPersonCameraActive)
    {
        if(!FirstPersonCameraPaused)
        {
            Logger::Log("Pausing first person camera.\n");
            RestoreCameraCode();
            FirstPersonCameraPaused = true;
        }
    }
    else
    {
        Logger::LogWarning("Failed to pause the first person camera because it is not active!\n");
    }
}

void CameraWrapper::UnpauseFirstPersonCamera()
{
    if(FirstPersonCameraActive)
    {
        if(FirstPersonCameraPaused)
        {
            Logger::Log("Unpausing first person camera.\n");
            DisableCameraCode(CameraYWriteAddress, CameraZWriteAddress);
            FirstPersonCameraPaused = false;
        }
    }
    else
    {
        Logger::LogWarning("Failed to unpause the first person camera because it is not active!\n");
    }
}

float CameraWrapper::GetCurrentSpeed() const
{
	return CurrentSpeed;
}

vector CameraWrapper::GetRealPosition() const
{
	return vector(*RealX, *RealY, *RealZ);
}
