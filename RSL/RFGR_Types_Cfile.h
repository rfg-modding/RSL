#pragma once
#include "RFGR_Types_Vehicle.h"

enum vlib_platform
{
    PLATFORM_NONE = 0xFFFFFFFF,
    PLATFORM_PC = 0x0,
    PLATFORM_PS2 = 0x1,
    PLATFORM_PS3 = 0x2,
    PLATFORM_XBOX = 0x3,
    PLATFORM_XBOX2 = 0x4,
    PLATFORM_XBONE = 0x5,
    PLATFORM_PS4 = 0x6,
    PLATFORM_SWITCH = 0x7,
    NUM_VLIB_PLATFORMS = 0x8,
};

union rfg_file_handle //$E6E582DEAE142D71F38CAABECEAEA2E0
{
    cf_keen_open_file* m_standard_fp;
    keen_cf_packfile_handle* m_packfile_fp;
    cf_memory_handle* _m_memory_fp;
};

struct cfile
{
    char name[65];
    char full_pathname[257];
    cf_search_types m_searched_system;
    cf_io_access_types m_access_type;
    rfg_file_handle file_handle;
    cf_io_media_types m_media_type;
    cfmode_type mode;
    cf_error_codes m_error_code;
    unsigned int pos;
    unsigned int size;
    unsigned int max_write_size;
    unsigned int m_flags;
};