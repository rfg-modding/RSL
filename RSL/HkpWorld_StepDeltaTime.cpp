#include "Hooks.h"
#include "Application.h"
#include "PhysicsGui.h"

void __fastcall Hooks::hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime) //0x9E1A70
{
    static bool InitCustomGravityVector = false;
    static auto ScriptManager = IocContainer->resolve<IScriptManager>();
    static auto Gui = IocContainer->resolve<IGuiManager>();
    if (Globals::hkpWorldPtr != This)
    {
        Logger::LogWarning("GlobalhkpWorldPtr address changed!\n");
        Globals::hkpWorldPtr = This;
        if(ScriptManager->Ready())
            ScriptManager->UpdateRfgPointers();
    }
    if (!Gui)
        return rfg::hkpWorldStepDeltaTime(This, edx, PhysicsDeltaTime);

    static GuiReference<PhysicsGui> PhysicsMenuRef = Gui->GetGuiReference<PhysicsGui>("Physics settings").value();
    if (!InitCustomGravityVector)
    {
        PhysicsGui& physGuiRef = PhysicsMenuRef.Get();
        physGuiRef.CurrentGravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);

        physGuiRef.CustomGravityVector.m_quad.m128_f32[0] = physGuiRef.CurrentGravity->m_quad.m128_f32[0];
        physGuiRef.CustomGravityVector.m_quad.m128_f32[1] = physGuiRef.CurrentGravity->m_quad.m128_f32[1];
        physGuiRef.CustomGravityVector.m_quad.m128_f32[2] = physGuiRef.CurrentGravity->m_quad.m128_f32[2];
        physGuiRef.CustomGravityVector.m_quad.m128_f32[3] = physGuiRef.CurrentGravity->m_quad.m128_f32[3];

        physGuiRef.DefaultGravityVector.m_quad.m128_f32[0] = physGuiRef.CurrentGravity->m_quad.m128_f32[0];
        physGuiRef.DefaultGravityVector.m_quad.m128_f32[1] = physGuiRef.CurrentGravity->m_quad.m128_f32[1];
        physGuiRef.DefaultGravityVector.m_quad.m128_f32[2] = physGuiRef.CurrentGravity->m_quad.m128_f32[2];
        physGuiRef.DefaultGravityVector.m_quad.m128_f32[3] = physGuiRef.CurrentGravity->m_quad.m128_f32[3];
        InitCustomGravityVector = true;
    }

    return rfg::hkpWorldStepDeltaTime(This, edx, PhysicsDeltaTime);
}

bool __fastcall Hooks::IsValidEigenGradientHook(void* This)
{
    throw std::exception();
    return rfg::IsValidEigenGradient(&This);
}