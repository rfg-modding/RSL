#include "Hooks.h"

void __cdecl Hooks::rfg_init_stage_2_done_hook(void* pSoundSystem)
{
    static int CallCount = 0;
    CallCount++;
    Logger::LogWarning("rfg_init_stage2_done_hook called! Times called: {}\n", CallCount);

    return rfg::rfg_init_stage_2_done(pSoundSystem);
}

void __cdecl Hooks::rfg_init_stage_2_done_2_hook()
{
    static int CallCount = 0;
    CallCount++;
    Logger::LogWarning("rfg_init_stage2_done_2_hook called! Times called: {}\n", CallCount);

    return rfg::rfg_init_stage_2_done_2();
}