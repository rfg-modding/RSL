#include "Hooks.h"
#include "IScriptManager.h"

//.text:00CEE450 rfg.exe:$3EE450 #3ED850 <gamestate_gp_process> //void __cdecl gamestate_gp_process()
void __cdecl Hooks::gamestate_gp_process_hook()
{
    static auto ScriptManager = IocContainer->resolve<IScriptManager>();
    if (ScriptManager->Ready())
        ScriptManager->TriggerDoFrameEvent();

    return rfg::gamestate_gp_process();
}