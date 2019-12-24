#include "CameraManager.h"
#include "RFGR_Types.h"
#include "Logger.h"

CameraManager::CameraManager()
{
    SnippetManager = IocContainer->resolve<ISnippetManager>();
}

void CameraManager::Initialize()
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

    FarClipDistance = &GameData->m_far_clip_dist;
    HighLodFarClipDistance = &GameData->m_high_lod_far_clip_dist;

    CameraYWriteAddress = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04", "x???????x???????x???????x???????x???????x???????x???????x???????x?????x???????x?????x???????x???????x????xxxxxxxxx");
    CameraZWriteAddress = Globals::FindPattern("rfg.exe", "\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52\xF3\x0F\x7E\x46\x04\x66\x00\x00\x00\x00\x00\x00\x00\x8B\x46\x0C\xA3", "x?????x???????x?????x???????x???????x????xxxxxxxxxx???????xxxx");

    CameraRealOrientWrite1 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", "x???????x???????x???????x???????x???????x???????x?????x???????x");
    CameraRealOrientWrite2 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89", "x???????x???????x???????x???????x?????x???????x");
    CameraRealOrientWrite3 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8", "x???????x???????x?????x???????x?????x???????x???????x");
    CameraRealOrientWrite4 = Globals::FindPattern("rfg.exe", "\x66\x00\x00\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6", "x???????x?????x???????x???????x????xx");
    CameraRealOrientWrite5 = Globals::FindPattern("rfg.exe", "\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xF6\x74\x52", "x?????x???????x???????x????xxxx");
}

void CameraManager::MoveFreeCamera(CameraDirection Direction)
{
    if (FreeCameraActive)
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
            *RealY += -1.0f * (*RealRightY) * MaxSpeed;
            *RealZ += -1.0f * (*RealRightZ) * MaxSpeed;
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

bool CameraManager::IsFreeCameraActive()
{
    return FreeCameraActive;
}

void CameraManager::ActivateFreeCamera()
{
    if (FirstPersonCameraActive)
    {
        Logger::LogError("Failed to activate free camera. First person cam already active.\n");
        return;
    }
    Logger::Log("Activating free camera\n");
    FreeCameraActive = true;
    DisableGameCamera();

    //Slight adjustments so the player ends up roughly in their original position.
    OriginalCameraPosition.x = *RealX + 2.171509;
    OriginalCameraPosition.y = *RealY;
    OriginalCameraPosition.z = *RealZ + 1.8545898;
}

void CameraManager::DeactivateFreeCamera(bool Shutdown)
{
    Logger::Log("Deactivating free camera\n");
    EnableGameCamera();

    FreeCameraActive = false;
    if (!Shutdown) //Don't want the player thrown in the air when they deactivate the script loader.
    {
        NeedPostDeactivationCleanup = true;
    }
    if (Globals::PlayerPtr)
    {
        Globals::PlayerPtr->HitPoints = Globals::PlayerPtr->MaxHitPoints;
        Globals::PlayerPtr->Flags.ai_ignore = false;
        Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls = false;
    }
}

void CameraManager::ToggleFreeCamera()
{
    if (FreeCameraActive)
    {
        DeactivateFreeCamera(false);
    }
    else
    {
        if (!FirstPersonCameraActive)
        {
            ActivateFreeCamera();
        }
        else
        {
            Logger::LogError("Failed to activate free camera. First person cam already active.\n");
        }
    }
}

void CameraManager::UpdateFreeView()
{

}

void CameraManager::ToggleFirstPersonCamera()
{
    if (FirstPersonCameraActive)
    {
        DeactivateFirstPersonCamera();
    }
    else
    {
        if (!FreeCameraActive)
        {
            ActivateFirstPersonCamera();
        }
        else
        {
            Logger::LogError("Failed to activate first person camera. Free cam already active.\n");
        }
    }
}

void CameraManager::ActivateFirstPersonCamera()
{
    if (FreeCameraActive)
    {
        Logger::LogWarning("Failed to activate the first person camera since free camera is already active!.\n");
        return;
    }
    Logger::Log("Activating first person camera\n");
    FirstPersonCameraActive = true;
    DisableGameCamera();
    LastFirstPersonPosition = Globals::PlayerPtr->Position;
}

void CameraManager::DeactivateFirstPersonCamera()
{
    Logger::Log("Deactivating first person camera\n");
    EnableGameCamera();

    FirstPersonCameraActive = false;
    FreeCameraActive = false;
    NeedPostDeactivationCleanup = false;
}

bool CameraManager::IsFirstPersonCameraPaused()
{
    return FirstPersonCameraPaused;
}

void CameraManager::PauseFirstPersonCamera()
{
    if (FirstPersonCameraActive)
    {
        if (!FirstPersonCameraPaused)
        {
            Logger::Log("Pausing first person camera.\n");
            EnableGameCamera();
            FirstPersonCameraPaused = true;
        }
    }
    else
    {
        Logger::LogWarning("Failed to pause the first person camera because it is not active!\n");
    }
}

void CameraManager::UnpauseFirstPersonCamera()
{
    if (FirstPersonCameraActive)
    {
        if (FirstPersonCameraPaused)
        {
            Logger::Log("Unpausing first person camera.\n");
            DisableGameCamera();
            FirstPersonCameraPaused = false;
        }
    }
    else
    {
        Logger::LogWarning("Failed to unpause the first person camera because it is not active!\n");
    }
}

bool CameraManager::IsFirstPersonCameraActive()
{
    return FirstPersonCameraActive;
}

void CameraManager::UpdateFirstPersonView()
{
    if (FirstPersonCameraPaused)
    {
        return;
    }
    vector HeadVector(0.0f);
    matrix HeadMatrix(0.0f);

    rfg::human_get_head_pos_orient(Globals::PlayerPtr, HeadVector, HeadMatrix);

    vector NewPos = GameData->real_pos;


    NewPos = HeadVector + FirstPersonCameraOffset;
    CurrentSpeed = Globals::PlayerPtr->Velocity.Magnitude(); //Note: Not sure what the point of this line is... For broken smooth cam?
    if (UseFirstPersonDirectionOffset)
    {
        vector TempVec = Globals::PlayerPtr->Orientation.fvec;
        NewPos += TempVec.Scale(FirstPersonDirectionOffsetMultiplier);
    }

    if (FirstPersonSmoothingEnabled) //Doesn't really seem to help vehicle shakiness much. 
    {
        if (UseMidpointSmoothing)
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

    if (UseFirstPersonAutoPlayerDirection)
    {
        vector2 CamFvec{ GameData->real_orient.fvec.x, GameData->real_orient.fvec.z };
        vector2 PlayerFvec{ Globals::PlayerPtr->Orientation.fvec.x, Globals::PlayerPtr->Orientation.fvec.z };
        float DotProduct = CamFvec * PlayerFvec;
        float MagProduct = CamFvec.Magnitude() * PlayerFvec.Magnitude();
        float AngleRadians = acos(DotProduct / MagProduct);
        //CamFvec = CamFvec.Rotate(FirstPersonAutoPlayerDirectionAngleOffset);

        float Angle2 = atan2((PlayerFvec.x * CamFvec.y) - (PlayerFvec.y * CamFvec.x), (PlayerFvec.x * CamFvec.x) - (PlayerFvec.y * CamFvec.y));

        if (abs(Globals::FloatConvertRadiansToDegrees(AngleRadians)) > MinAngleDifferenceForRotation)
        {
            vector YAxis = { 0.0f, 1.0f, 0.0f };

            if (Angle2 > 0.0f)
            {
                AngleRadians *= -1.0f;
            }
            rfg::matrix_rotate_around_local_vector(&Globals::PlayerPtr->Orientation, nullptr, YAxis, AngleRadians);
        }
    }

    GameData->real_pos = NewPos;
    LastFirstPersonPosition = GameData->real_pos;
}

vector CameraManager::GetPosition()
{
    if (!GameData)
        return vector(0.0f);

    return GameData->real_pos;
}

void CameraManager::SetPosition(vector& NewPos)
{
    *RealX = NewPos.x;
    *RealY = NewPos.y;
    *RealZ = NewPos.z;
}

void CameraManager::AdjustPosition(vector& Delta)
{
    *RealX += Delta.x;
    *RealY += Delta.y;
    *RealZ += Delta.z;
}

void CameraManager::DisableGameCamera()
{
    if (!CameraCodeEnabled)
        return;

    SnippetManager->BackupSnippet("CameraWriteY", CameraYWriteAddress, 8, true);
    SnippetManager->BackupSnippet("CameraWriteZ", CameraZWriteAddress, 6, true);
    CameraCodeEnabled = false;
}

void CameraManager::EnableGameCamera()
{
    if(CameraCodeEnabled)
        return;
    
    SnippetManager->RestoreSnippet("CameraWriteY", true);
    SnippetManager->RestoreSnippet("CameraWriteZ", true);
    CameraCodeEnabled = true;
}

bool CameraManager::CameraEnabled()
{
    return CameraCodeEnabled;
}

void CameraManager::DisableCameraDirectionCode()
{
    if(!CameraDirectionCodeEnabled)
        return;

    SnippetManager->BackupSnippet("CameraRealOrient1", CameraRealOrientWrite1, 8, true);
    SnippetManager->BackupSnippet("CameraRealOrient2", CameraRealOrientWrite2, 8, true);
    SnippetManager->BackupSnippet("CameraRealOrient3", CameraRealOrientWrite3, 8, true);
    SnippetManager->BackupSnippet("CameraRealOrient4", CameraRealOrientWrite4, 8, true);
    SnippetManager->BackupSnippet("CameraRealOrient5", CameraRealOrientWrite5, 6, true);

    CameraDirectionCodeEnabled = false;
}

void CameraManager::EnableCameraDirectionCode()
{
    if (CameraDirectionCodeEnabled)
        return;

    SnippetManager->RestoreSnippet("CameraRealOrient1", true);
    SnippetManager->RestoreSnippet("CameraRealOrient2", true);
    SnippetManager->RestoreSnippet("CameraRealOrient3", true);
    SnippetManager->RestoreSnippet("CameraRealOrient4", true);
    SnippetManager->RestoreSnippet("CameraRealOrient5", true);

    CameraDirectionCodeEnabled = true;
}

bool CameraManager::IsCameraDirectionCodeEnabled()
{
    return CameraDirectionCodeEnabled;
}

vector CameraManager::GetLookDirection()
{
    if (!GameData)
        return vector(0.0f);

    return GameData->real_orient.fvec;
}

matrix CameraManager::GetLookOrient()
{
    if (!GameData)
        return matrix(0.0f);

    return GameData->real_orient;
}
