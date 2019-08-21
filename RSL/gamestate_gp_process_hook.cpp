#include "Hooks.h"
#include "Application.h"

//.text:00CEE450 rfg.exe:$3EE450 #3ED850 <gamestate_gp_process> //void __cdecl gamestate_gp_process()
void __cdecl Hooks::gamestate_gp_process_hook()
{
    if(Globals::Scripts)
    {
        Globals::Scripts->TriggerDoFrameEvent();
    }
    gamestate_gp_process();
}