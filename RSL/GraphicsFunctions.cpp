#include "GraphicsFunctions.h"
#include "Globals.h"
#include "Logger.h"

void Lua::BindGraphicsFunctions(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();

    RfgTable["SetShadowResolutions"] = [](int res0, int res1, int res2, int res3)
    {
        if(!Globals::ShadowMapSizes.Initialized())
        {
            Logger::LogError("Failed to set shadow map sizes! The shadow map sizes array hasn't been setup by the RSL yet!\n");
            return;
        }
        Globals::ShadowMapSizes[0] = res0;
        Globals::ShadowMapSizes[1] = res1;
        Globals::ShadowMapSizes[2] = res2;
        Globals::ShadowMapSizes[3] = res3;
    };
#endif
}
