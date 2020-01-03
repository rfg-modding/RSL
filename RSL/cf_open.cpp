#include "Hooks.h"

cfile* __cdecl Hooks::cf_open_hook(const char* filename_in, const char* mode, vlib_platform disk_platform, bool async)
{
#if LOG_CF_OPEN_CALLS
    Logger::Log("cf_open:: \n    filename_in: {0}, \n    mode: {1}, \n    disk_platform: {2}, \n    async: {3}\n\n",
        filename_in, mode, magic_enum::enum_name(disk_platform), async);
#endif

#if DEBUG
    //Experimental file loading hook for loose primitives and str2s. Doesn't work for xtbl and vpp, possibly for other xml formats too
    //Todo: Test this more extensively
    //Todo: Hook xml_table_parse for xtbls and find functions to hook for other files
    //Todo: Combine this with IPC commands to reload levels from an external level editor by passing an edited zone file path
    string targetOverrideRelative = fmt::format("RSL/Overrides/General/{}", filename_in);
    if(fs::exists(targetOverrideRelative))
    {
        string targetOverrideAbsolute = fmt::format("{}/{}", Globals::GetEXEPath(false), targetOverrideRelative);
        Logger::LogWarning("Overriding \"{}\" with \"{}\"\n", filename_in, targetOverrideAbsolute);
        filename_in = targetOverrideAbsolute.c_str();
    }
#endif
    return rfg::cf_open(filename_in, mode, disk_platform, async);
}
