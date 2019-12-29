#include "Path.h"
#include <filesystem>

namespace Path
{
    std::string GetFileName(const std::filesystem::path& FullPath)
    {
        return GetFileName(FullPath.string());
    }
    std::string GetFileName(const std::string& FullPath)
    {
        if (!std::filesystem::path(FullPath).has_filename())
            return {};

        return std::filesystem::path(FullPath).filename().string();
    }

    std::string GetParentDirectory(const std::filesystem::path& FullPath)
    {
        return GetParentDirectory(FullPath.string());
    }
    std::string GetParentDirectory(const std::string& FullPath)
    {
        if (!std::filesystem::path(FullPath).has_parent_path())
            return {};

        return std::filesystem::path(FullPath).parent_path().string() + "\\";
    }

    std::string GetExtension(const std::filesystem::path& FullPath)
    {
        return GetExtension(FullPath.string());
    }
    std::string GetExtension(const std::string& FullPath)
    {
        if (!std::filesystem::path(FullPath).has_extension())
            return {};

        return std::filesystem::path(FullPath).extension().string();
    }

    void CreatePath(const std::string& fullPath)
    {
        if (!std::filesystem::exists(fullPath))
            std::filesystem::create_directories(fullPath);
    }
}
