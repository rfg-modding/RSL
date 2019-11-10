#pragma once
#include "Script.h"
#include <vector>

class ScriptFolder
{
public:
    ScriptFolder() = default;
    ScriptFolder(std::string FullPath_, std::string Name_) : FullPath(FullPath_), Name(Name_) { }

    std::string FullPath;
    std::string Name;
    std::vector<Script> Scripts;
};
