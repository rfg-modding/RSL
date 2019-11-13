#include "Hooks.h"
#include "Application.h"
#include "FreeCamGui.h"
#include "GeneralTweaksGui.h"

void __fastcall Hooks::PlayerDoFrameHook(Player* PlayerPtr)
{
    static int OnLoadCounter = 0;
    static int TimesCalled = 0;
    static bool InitEventTriggered = false;

    static auto ScriptManager = IocContainer->resolve<IScriptManager>();
    static auto Gui = IocContainer->resolve<IGuiManager>();

    if(ScriptManager->Ready())
    {
        if (!InitEventTriggered)
        {
            if (TimesCalled >= 200) //Wait 200 frames to ensure everything is initialized
            {
                ScriptManager->TriggerInitializedEvent();
                InitEventTriggered = true;
            }
            else
            {
                TimesCalled++;
            }
        }
        if (Globals::CanTriggerOnLoadEvent)
        {
            if (OnLoadCounter >= 200) //Wait 200 frames to ensure everything is initialized
            {
                ScriptManager->TriggerLoadEvent();
                Globals::CanTriggerOnLoadEvent = false;
                OnLoadCounter = 0;
            }
            else
            {
                OnLoadCounter++;
            }
        }
    }
    if (Globals::PlayerPtr != PlayerPtr)
    {
        Globals::PlayerPtr = PlayerPtr;
        Globals::PlayerRigidBody = rfg::HavokBodyGetPointer(PlayerPtr->HavokHandle);
        if(ScriptManager->Ready())
            ScriptManager->UpdateRfgPointers();
    }

    if (!Gui)
    {
        return rfg::PlayerDoFrame(PlayerPtr);
    }
    static GuiReference<GeneralTweaksGui> TweaksMenuRef = Gui->GetGuiReference<GeneralTweaksGui>("General tweaks").value();
    static GuiReference<FreeCamGui> FreeCamMenuRef = Gui->GetGuiReference<FreeCamGui>("Camera settings").value();

    auto Camera = IocContainer->resolve<ICameraManager>();
    if (Camera)
    {
        if (Camera->IsFreeCameraActive())
        {
            PlayerPtr->Flags.ai_ignore = true;
        }
        if (Camera->IsFreeCameraActive() && FreeCamMenuRef.Get().PlayerFollowCam)
        {
            Camera->UpdateFreeView();
            vector CameraPos(*Camera->RealX, *Camera->RealY + 1.5f, *Camera->RealZ);
            rfg::HumanTeleportUnsafe(PlayerPtr, CameraPos, PlayerPtr->Orientation);
        }
        if (!Camera->IsFreeCameraActive() && Camera->NeedPostDeactivationCleanup)
        {
            if (FreeCamMenuRef.Get().ReturnPlayerToOriginalPosition)
            {
                rfg::HumanTeleportUnsafe(PlayerPtr, Camera->OriginalCameraPosition, PlayerPtr->Orientation);
            }
            Camera->NeedPostDeactivationCleanup = false;
        }
        if (Camera->IsFirstPersonCameraActive())
        {
            if (Camera->UseThirdPersonForVehicles)
            {
                if (PlayerPtr->VehicleHandle != 0xFFFFFFFF)
                {
                    Camera->PauseFirstPersonCamera();
                }
                else
                {
                    Camera->UnpauseFirstPersonCamera();
                    Camera->UpdateFirstPersonView();
                }
            }
            else
            {
                if (Camera->IsFirstPersonCameraPaused())
                {
                    Camera->UnpauseFirstPersonCamera();
                }
                Camera->UpdateFirstPersonView();
            }
        }
        if (Camera->IsFreeCameraActive() && FreeCamMenuRef.Get().PlayerFollowCam)
        {
            PlayerPtr->Flags.invulnerable = true;
            PlayerPtr->HitPoints = 2147483647.0f;
        }
    }


    if (Globals::InfiniteJetpack)
    {
        PlayerPtr->JetpackFuelPercent = 1.0f;
    }
    if (TweaksMenuRef.Get().Invulnerable)
    {
        PlayerPtr->Flags.invulnerable = true;
        PlayerPtr->HitPoints = 2147483647.0f;
    }
    if (TweaksMenuRef.Get().NeedCustomJumpHeightSet)
    {
        PlayerPtr->CodeDrivenJumpHeight = TweaksMenuRef.Get().CustomJumpHeight;
    }
    if (TweaksMenuRef.Get().LockAlertLevel)
    {
        rfg::GsmSetAlertLevel(TweaksMenuRef.Get().CustomAlertLevel);
    }

    //Todo: Make some kind of event system/class to avoid needing to do this and having tons of globals laying around
    //This is done to avoid problems when a thread spawned by the RSL tries teleporting the player at an unsafe time for doing so.
    if (Globals::PlayerNeedsTeleport)
    {
        rfg::HumanTeleportUnsafe(PlayerPtr, Globals::PlayerTeleportPos, PlayerPtr->Orientation);
        Globals::PlayerNeedsTeleport = false;
    }

    return rfg::PlayerDoFrame(PlayerPtr);
}

void __cdecl Hooks::HookDoFrameHook()
{
    Globals::HookDidFrame = true;
    return rfg::HookDoFrame();
}