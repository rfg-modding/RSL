#include "Hooks.h"
#include "Application.h"
#include "PhysicsGui.h"

void __fastcall Hooks::hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime) //0x9E1A70
{
    static auto ScriptManager = IocContainer->resolve<IScriptManager>();
    static auto Gui = IocContainer->resolve<IGuiManager>();
    if (Globals::hkpWorldPtr != This)
    {
        Logger::LogWarning("GlobalhkpWorldPtr address changed!\n");
        Globals::hkpWorldPtr = This;
        if(ScriptManager->Ready())
            ScriptManager->UpdateRfgPointers();
    }

    static bool InitCustomGravityVector = false;
    if (!Gui)
    {
        return rfg::hkpWorldStepDeltaTime(This, edx, PhysicsDeltaTime);
    }
    static GuiReference<PhysicsGui> PhysicsMenuRef = Gui->GetGuiReference<PhysicsGui>("Physics settings").value();

    if (!InitCustomGravityVector)
    {
        PhysicsMenuRef.Get().CurrentGravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);

        PhysicsMenuRef.Get().CustomGravityVector.m_quad.m128_f32[0] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[0];
        PhysicsMenuRef.Get().CustomGravityVector.m_quad.m128_f32[1] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[1];
        PhysicsMenuRef.Get().CustomGravityVector.m_quad.m128_f32[2] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[2];
        PhysicsMenuRef.Get().CustomGravityVector.m_quad.m128_f32[3] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[3];

        PhysicsMenuRef.Get().DefaultGravityVector.m_quad.m128_f32[0] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[0];
        PhysicsMenuRef.Get().DefaultGravityVector.m_quad.m128_f32[1] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[1];
        PhysicsMenuRef.Get().DefaultGravityVector.m_quad.m128_f32[2] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[2];
        PhysicsMenuRef.Get().DefaultGravityVector.m_quad.m128_f32[3] = PhysicsMenuRef.Get().CurrentGravity->m_quad.m128_f32[3];
        InitCustomGravityVector = true;
    }

    if (PhysicsMenuRef.IsReady())
    {
        if (PhysicsMenuRef.Get().UseCustomPhysicsTimestepMultiplier)
        {
            PhysicsDeltaTime *= PhysicsMenuRef.Get().CustomPhysicsTimeStepMultiplier;
        }
    }

    return rfg::hkpWorldStepDeltaTime(This, edx, PhysicsDeltaTime);
}

bool __fastcall Hooks::IsValidEigenGradientHook(void* This)
{
    throw std::exception();
    return rfg::IsValidEigenGradient(&This);
}