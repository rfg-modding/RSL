#pragma once
#include "Script.h"
#include "Path.h"
#include <vector>

class ScriptFolder
{
public:
    ScriptFolder() = default;
    ScriptFolder(const std::filesystem::path& path) : FullPath(path.string()), Name(Path::GetFileName(path))
    { }

    std::string FullPath;
    std::string Name;
    std::vector<Script> Scripts;
};
