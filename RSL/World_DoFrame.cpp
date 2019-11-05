#include "Hooks.h"
#include "Application.h"

void __fastcall Hooks::world_do_frame_hook(World* This, void* edx, bool HardLoad)
{
    if (Globals::RfgWorldPtr != This)
    {
        Logger::LogWarning("Globals::RfgWorldPtr changed!\n");
        Globals::RfgWorldPtr = This;
        if (Globals::Scripts)
        {
            Globals::Scripts->UpdateRfgPointers();
        }
    }
    if (!Globals::TODLightPtr)
    {
        Globals::TODLightPtr = rfg::GameRenderGetTodLight();
        if (Globals::Scripts)
        {
            Globals::Scripts->UpdateRfgPointers();
        }
    }
    if (!Globals::Gui)
    {
        return rfg::WorldDoFrame(This, edx, HardLoad);
    }

    static GuiReference<GeneralTweaksGui> TweaksMenuRef = Globals::Gui->GetGuiReference<GeneralTweaksGui>("General tweaks").value();
    if (TweaksMenuRef.Get().UseCustomLevelAmbientLight)
    {
        Globals::RfgWorldPtr->level_ambient.x = TweaksMenuRef.Get().CustomLevelAmbientLight.x;
        Globals::RfgWorldPtr->level_ambient.y = TweaksMenuRef.Get().CustomLevelAmbientLight.y;
        Globals::RfgWorldPtr->level_ambient.z = TweaksMenuRef.Get().CustomLevelAmbientLight.z;
    }
    if (TweaksMenuRef.Get().UseCustomLevelBackgroundAmbientLight)
    {
        Globals::RfgWorldPtr->level_back_ambient.x = TweaksMenuRef.Get().CustomLevelBackgroundAmbientLight.x;
        Globals::RfgWorldPtr->level_back_ambient.y = TweaksMenuRef.Get().CustomLevelBackgroundAmbientLight.y;
        Globals::RfgWorldPtr->level_back_ambient.z = TweaksMenuRef.Get().CustomLevelBackgroundAmbientLight.z;
    }
    if (TweaksMenuRef.Get().UseCustomTimeOfDayLight)
    {
        Globals::TODLightPtr->m_color.red = TweaksMenuRef.Get().CustomTimeOfDayLightColor.red;
        Globals::TODLightPtr->m_color.green = TweaksMenuRef.Get().CustomTimeOfDayLightColor.green;
        Globals::TODLightPtr->m_color.blue = TweaksMenuRef.Get().CustomTimeOfDayLightColor.blue;
        Globals::TODLightPtr->m_color.alpha = TweaksMenuRef.Get().CustomTimeOfDayLightColor.alpha;
    }

    return rfg::WorldDoFrame(This, edx, HardLoad);
}