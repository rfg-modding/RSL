#include "Hooks.h"

bool __cdecl Hooks::verify_gamesave_exit_notify_hook(GameState new_state)
{
    static int CallCount = 0;
    CallCount++;
    Logger::LogWarning("verify_gamesave_exit_notify_hook! Times called: {}\n", CallCount);

    return rfg::verify_gamesave_exit_notify(new_state);
}