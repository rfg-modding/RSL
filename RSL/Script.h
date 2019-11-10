#pragma once
#include <string>

/* Contains basic information about a script to avoid duplicate calculations.
 * This includes it's full path, folder path, and file name. Currently does
 * not buffer the script itself. Scripts are only loaded at the moment that
 * they are run.
 */
class Script
{
public:
    Script() = default;;
    Script(std::string FullPath_, std::string FolderPath_, std::string Name_) : FullPath(FullPath_), FolderPath(FolderPath_), Name(Name_) { }
    ~Script() = default;;

    std::string FullPath; //Full path with file name.
    std::string FolderPath; //Full path without file name.
    std::string Name; //Script file name.
};