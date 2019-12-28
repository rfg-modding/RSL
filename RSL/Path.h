#pragma once
#include <string>
#include <filesystem>

namespace Path
{
    [[nodiscard]] std::string GetFileName(const std::filesystem::path& FullPath);
    [[nodiscard]] std::string GetFileName(const std::string& FullPath);

    [[nodiscard]] std::string GetParentDirectory(const std::filesystem::path& FullPath);
    [[nodiscard]] std::string GetParentDirectory(const std::string& FullPath);

    [[nodiscard]] std::string GetExtension(const std::filesystem::path& FullPath);
    [[nodiscard]] std::string GetExtension(const std::string& FullPath);
}
