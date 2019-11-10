#include "Hooks.h"
#include "Application.h"

bool __cdecl Hooks::peg_load_wrapper_hook(const char* filename, unsigned srid, char* cpu_preload, int cpu_size, char* gpu_preload, int gpu_size)
{
#ifdef DEBUG
    //Logger::Log("peg_load_wrapper hook: filename: {}, srid: {}, cpu_preload: {}, cpu_size: {},  gpu_preload: {}, gpu_size: {}\n", filename, srid, reinterpret_cast<DWORD>(cpu_preload), cpu_size, reinterpret_cast<DWORD>(gpu_preload), gpu_size);
#endif

    if (Globals::DumpTexturesWhenLoading)
    {
        fs::create_directory("RSL/Dumps/");
        fs::create_directory("RSL/Dumps/Textures/");
        auto SplitName = Globals::SplitFilename(filename);
        std::string& Filename = SplitName[0];
        std::string& Extension = SplitName[1];

        if (Extension == ".cpeg_pc")
        {
            Logger::Log("Dumping texture file \"{}\" and \"{}\"\n", filename, Filename + ".gpeg_pc");
            std::ofstream("RSL/Dumps/Textures/" + std::string(filename), std::ios::binary).write(cpu_preload, cpu_size);
            std::ofstream("RSL/Dumps/Textures/" + Filename + ".gpeg_pc", std::ios::binary).write(gpu_preload, gpu_size);
        }
        else if (Extension == ".cvbm_pc")
        {
            Logger::Log("Dumping texture file \"{}\" and \"{}\"\n", filename, Filename + ".gvbm_pc");
            std::ofstream("RSL/Dumps/Textures/" + std::string(filename), std::ios::binary).write(cpu_preload, cpu_size);
            std::ofstream("RSL/Dumps/Textures/" + Filename + ".gvbm_pc", std::ios::binary).write(gpu_preload, gpu_size);
        }
        else
        {
            Logger::LogError("Invalid peg extension in peg_load_wrapper_hook! Extension: {}\n", Extension);
        }
    }

    if (fs::exists("RSL/Overrides/Textures/" + std::string(filename)))
    {
        auto SplitName = Globals::SplitFilename(filename);
        std::string& Filename = SplitName[0];
        std::string& Extension = SplitName[1];

        //Todo: Figure out if it's necessary to call delete on the games char array to avoid a memory leak.
        Logger::Log("Found texture file \"{}\". Replacing...\n", "./RSL/Overrides/Textures/" + std::string(filename));

        const int cpu_file_size = fs::file_size("RSL/Overrides/Textures/" + std::string(filename));
        char* TempCpuBuffer = new char[cpu_file_size];

        std::ifstream("RSL/Overrides/Textures/" + std::string(filename), std::ios::binary).read(TempCpuBuffer, cpu_file_size);

        if (Extension == ".cpeg_pc")
        {
            if(fs::exists("RSL/Overrides/Textures/" + Filename + ".gpeg_pc"))
            {
                const int gpu_file_size = fs::file_size("RSL/Overrides/Textures/" + Filename + ".gpeg_pc");
                char* TempGpuBuffer = new char[gpu_file_size];

                std::ifstream("RSL/Overrides/Textures/" + Filename + ".gpeg_pc", std::ios::binary).read(TempGpuBuffer, gpu_file_size);

                return rfg::peg_load_wrapper(filename, srid, TempCpuBuffer, cpu_file_size, TempGpuBuffer, gpu_file_size);
            }
            else
            {
                Logger::Log("Failed to find the matching gpeg_pc file for \"{}\". Using default texture instead.\n", "./RSL/Overrides/Textures/" + std::string(filename));
            }
        }
        else if (Extension == ".cvbm_pc")
        {
            if (fs::exists("RSL/Overrides/Textures/" + Filename + ".gvbm_pc"))
            {
                int gpu_file_size = fs::file_size("RSL/Overrides/Textures/" + Filename + ".gvbm_pc");
                char* TempGpuBuffer = new char[gpu_file_size];

                std::ifstream("RSL/Overrides/Textures/" + Filename + ".gvbm_pc", std::ios::binary).read(TempGpuBuffer, gpu_file_size);

                return rfg::peg_load_wrapper(filename, srid, TempCpuBuffer, cpu_file_size, TempGpuBuffer, gpu_file_size);
            }
            else
            {
                Logger::Log("Failed to find the matching gpeg_pc file for \"{}\". Using default texture instead.\n", "./RSL/Overrides/Textures/" + std::string(filename));
            }
        }
    }

    return rfg::peg_load_wrapper(filename, srid, cpu_preload, cpu_size, gpu_preload, gpu_size);
}