#pragma once
#include <string>
#include <optional>

using uint = unsigned int;

class ScriptResult
{
public:
    ScriptResult(bool Failed_, std::optional<uint> ErrorLineNumber_, std::string ErrorString_)
        : Failed(Failed_), ErrorLineNumber(ErrorLineNumber_), ErrorString(ErrorString_) {}
    ~ScriptResult() = default;

    bool Failed = false;
    std::optional<uint> ErrorLineNumber = 0;
    std::string ErrorString = {};
};
