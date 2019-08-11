#include "Hooks.h"
#include "Application.h"

void __fastcall Hooks::PlayerDoFrameHook(Player* PlayerPtr)
{
    if (Globals::PlayerPtr != PlayerPtr)
    {
        Globals::PlayerPtr = PlayerPtr;
        Globals::PlayerRigidBody = HavokBodyGetPointer(PlayerPtr->HavokHandle);
        if (Globals::Scripts)
        {
            Globals::Scripts->UpdateRfgPointers();
        }
    }

    if (!Globals::Gui)
    {
        return PlayerDoFrame(PlayerPtr);
    }
    static GuiReference<GeneralTweaksGui> TweaksMenuRef = Globals::Gui->GetGuiReference<GeneralTweaksGui>("General tweaks").value();
    static GuiReference<FreeCamGui> FreeCamMenuRef = Globals::Gui->GetGuiReference<FreeCamGui>("Camera settings").value();

    if (!Globals::Camera)
    {
        return PlayerDoFrame(PlayerPtr);
    }

    if (Globals::InfiniteJetpack)
    {
        PlayerPtr->JetpackFuelPercent = 1.0f;
    }
    if (TweaksMenuRef.Get().Invulnerable || (Globals::Camera->IsFreeCameraActive() && FreeCamMenuRef.Get().PlayerFollowCam))
    {
        PlayerPtr->Flags.invulnerable = true;
        PlayerPtr->HitPoints = 2147483647.0f;
    }
    if (Globals::Camera->IsFreeCameraActive())
    {
        PlayerPtr->Flags.ai_ignore = true;
    }
    if (TweaksMenuRef.Get().NeedCustomJumpHeightSet)
    {
        PlayerPtr->CodeDrivenJumpHeight = TweaksMenuRef.Get().CustomJumpHeight;
    }
    if (TweaksMenuRef.Get().NeedCustomMoveSpeedSet)
    {
        PlayerPtr->MoveSpeed = TweaksMenuRef.Get().CustomPlayerMoveSpeed;
    }
    if (TweaksMenuRef.Get().NeedCustomMaxMoveSpeedSet)
    {
        PlayerPtr->MaxSpeed = TweaksMenuRef.Get().CustomPlayerMaxSpeed;
    }
    if (TweaksMenuRef.Get().LockAlertLevel)
    {
        GsmSetAlertLevel(TweaksMenuRef.Get().CustomAlertLevel);
    }

    if (Globals::Camera->IsFreeCameraActive() && FreeCamMenuRef.Get().PlayerFollowCam)
    {
        Globals::Camera->UpdateFreeView();
        vector CameraPos(*Globals::Camera->RealX, *Globals::Camera->RealY + 1.5f, *Globals::Camera->RealZ);
        HumanTeleportUnsafe(PlayerPtr, CameraPos, PlayerPtr->Orientation);
    }
    if (!Globals::Camera->IsFreeCameraActive() && Globals::Camera->NeedPostDeactivationCleanup)
    {
        if (FreeCamMenuRef.Get().ReturnPlayerToOriginalPosition)
        {
            HumanTeleportUnsafe(PlayerPtr, Globals::Camera->OriginalCameraPosition, PlayerPtr->Orientation);
        }
        Globals::Camera->NeedPostDeactivationCleanup = false;
    }

    if (Globals::Camera)
    {
        if (Globals::Camera->IsFirstPersonCameraActive())
        {
            Globals::Camera->UpdateFirstPersonView();
            Globals::PlayerPtr->Flags.disallow_flinches_and_ragdolls = true;
        }
        if (Globals::Camera->IsFirstPersonCameraActive())
        {
            Globals::Camera->UpdateFirstPersonView();
        }
    }

    return PlayerDoFrame(PlayerPtr);
}

void __cdecl Hooks::HookDoFrameHook()
{
    Globals::HookDidFrame = true;
    return HookDoFrame();
}