#include "Hooks.h"
#include "Application.h"

bool __cdecl Hooks::peg_load_wrapper_hook(const char* filename, unsigned srid, char* cpu_preload, int cpu_size, char* gpu_preload, int gpu_size)
{
    Logger::Log("peg_load_wrapper hook: filename: {}, srid: {}, cpu_preload: {}, cpu_size: {},  gpu_preload: {}, gpu_size: {}\n", filename, srid, reinterpret_cast<DWORD>(cpu_preload), cpu_size, reinterpret_cast<DWORD>(gpu_preload), gpu_size);

    if (Globals::DumpTexturesWhenLoading)
    {
        fs::create_directory("RSL/Dumps/Textures/");
        auto SplitName = Globals::SplitFilename(filename);
        if (std::get<1>(SplitName) == ".cpeg_pc")
        {
            std::ofstream("RSL/Dumps/Textures/" + std::string(filename), std::ios::binary).write(cpu_preload, cpu_size);
            std::ofstream("RSL/Dumps/Textures/" + std::get<0>(SplitName) + ".gpeg_pc", std::ios::binary).write(gpu_preload, gpu_size);
        }
        else if (std::get<1>(SplitName) == ".cvbm_pc")
        {
            std::ofstream("RSL/Dumps/Textures/" + std::string(filename), std::ios::binary).write(cpu_preload, cpu_size);
            std::ofstream("RSL/Dumps/Textures/" + std::get<0>(SplitName) + ".gvbm_pc", std::ios::binary).write(gpu_preload, gpu_size);
        }
        else
        {
            Logger::LogError("Invalid peg extension in peg_load_wrapper_hook! Extension: {}\n", std::get<1>(SplitName));
        }
    }

    if (fs::exists("RSL/Overrides/Textures/" + std::string(filename)))
    {
        auto SplitName = Globals::SplitFilename(filename);
        //Todo: Figure out if it's necessary to call delete on the games char array to avoid a memory leak.
        Logger::Log("Found texture file {}. Replacing.", "./RSL/Overrides/Textures/" + std::string(filename));

        const int cpu_file_size = fs::file_size("RSL/Overrides/Textures/" + std::string(filename));
        char* TempCpuBuffer = new char[cpu_file_size];

        std::ifstream("RSL/Overrides/Textures/" + std::string(filename), std::ios::binary).read(TempCpuBuffer, cpu_file_size);

        if (std::get<1>(SplitName) == ".cpeg_pc")
        {
            const int gpu_file_size = fs::file_size("RSL/Overrides/Textures/" + std::get<0>(SplitName) + ".gpeg_pc");
            char* TempGpuBuffer = new char[gpu_file_size];

            std::ifstream("RSL/Overrides/Textures/" + std::get<0>(SplitName) + ".gpeg_pc", std::ios::binary).read(TempGpuBuffer, gpu_file_size);

            return peg_load_wrapper(filename, srid, TempCpuBuffer, cpu_file_size, TempGpuBuffer, gpu_file_size);
        }
        else if (std::get<1>(SplitName) == ".cvbm_pc")
        {
            int gpu_file_size = fs::file_size("RSL/Overrides/Textures/" + std::get<0>(SplitName) + ".gvbm_pc");
            char* TempGpuBuffer = new char[gpu_file_size];

            std::ifstream("RSL/Overrides/Textures/" + std::get<0>(SplitName) + ".gvbm_pc", std::ios::binary).read(TempGpuBuffer, gpu_file_size);

            return peg_load_wrapper(filename, srid, TempCpuBuffer, cpu_file_size, TempGpuBuffer, gpu_file_size);
        }
    }

    return peg_load_wrapper(filename, srid, cpu_preload, cpu_size, gpu_preload, gpu_size);
}