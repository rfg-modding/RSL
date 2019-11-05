#include "Hooks.h"
#include "Application.h"

int __cdecl Hooks::LuaDoBufferHook(lua_State* L, const char* buff, unsigned int size, const char* name)
{
    static std::string TempBuffer;
    if (Globals::RfgVintLuaState != L)
    {
        Globals::RfgVintLuaState = L;
    }
    if (!L)
    {
        Logger::LogWarning("RFG lua_state pointer null\n");
        return rfg::LuaDoBuffer(L, buff, size, name);
    }

    //Dump current script file
    std::string Buffer(buff, size);
    std::string Name(name);
    std::string RfgLuaPath = Globals::GetEXEPath(false);
    RfgLuaPath += "RSL/RFG_Lua/";
    fs::create_directory(RfgLuaPath);
    std::string DumpFilePath = RfgLuaPath + "Lua_Dumps/";
    fs::create_directory(DumpFilePath);
    DumpFilePath += Name;
    Logger::Log("Dumping {}\n", Name);
    std::ofstream myfile;
    myfile.open(DumpFilePath, std::ios_base::trunc);
    myfile << Buffer;
    myfile.close();

    std::string OverrideFilePath = RfgLuaPath + "Overrides/" + Name;
    //Load override if it exists and pass it on to lua.
    if (fs::exists(OverrideFilePath))
    {
        std::ifstream OverrideStream(OverrideFilePath);
        std::string OverrideBuffer((std::istreambuf_iterator<char>(OverrideStream)), std::istreambuf_iterator<char>());
        Logger::Log("Overriding {}\n", Name);

        TempBuffer.clear();
        TempBuffer = OverrideBuffer;
        return rfg::LuaDoBuffer(L, TempBuffer.c_str(), TempBuffer.length(), name);
    }
    return rfg::LuaDoBuffer(L, buff, size, name);
}