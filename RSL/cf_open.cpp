#include "Hooks.h"

cfile* __cdecl Hooks::cf_open_hook(const char* filename_in, const char* mode, vlib_platform disk_platform, bool async)
{
#if LOG_CF_OPEN_CALLS
    Logger::Log("cf_open:: \n    filename_in: {0}, \n    mode: {1}, \n    disk_platform: {2}, \n    async: {3}\n\n",
        filename_in, mode, magic_enum::enum_name(disk_platform), async);
#endif

    return rfg::cf_open(filename_in, mode, disk_platform, async);
}
