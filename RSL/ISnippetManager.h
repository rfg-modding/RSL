#pragma once
#include <vector>
#include <string>

using ulong = unsigned long;

class ISnippetManager
{
public:
    ISnippetManager(const ISnippetManager&) = delete;
    ISnippetManager& operator=(const ISnippetManager&) = delete;
    virtual ~ISnippetManager() noexcept = default;

    virtual void BackupSnippet(std::string Name, ulong Address, ulong Length, bool NOP) = 0;
    virtual void RestoreSnippet(std::string Name, bool RemoveFromCache) = 0;
    virtual void NOPSnippet(std::string Name) = 0;
    virtual void ReplaceSnippet(std::string Name, ulong Address, std::vector<int>& NewOpcodes) = 0;

protected:
    ISnippetManager() = default;
};
