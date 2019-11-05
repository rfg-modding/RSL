#include "Hooks.h"
#include "Application.h"

//.text:01569430 rfg.exe:$3C9430 #3C8830 <verify_gamesave_exit_notify> //bool __cdecl verify_gamesave_exit_notify(game_state new_state)
using F_verify_gamesave_exit_notify = bool(__cdecl*)(GameState new_state);
extern F_verify_gamesave_exit_notify verify_gamesave_exit_notify;

bool __cdecl Hooks::verify_gamesave_exit_notify_hook(GameState new_state)
{
    static int CallCount = 0;
    CallCount++;
    Logger::LogWarning("verify_gamesave_exit_notify_hook! Times called: {}\n", CallCount);

    return rfg::verify_gamesave_exit_notify(new_state);
}