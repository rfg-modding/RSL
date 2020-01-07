#include "Hooks.h"

void __cdecl Hooks::gem_post_event_hook(event_data& data)
{
#if DEBUG
    Logger::LogWarning("[gem_post_event_hook]:: Rfg event posted. Type: {}\n", magic_enum::enum_name(data.type));
#endif
    return rfg::gem_post_event(data);
}