#pragma once
#include "GraphicsStateWrapper.h"

namespace String
{
    std::wstring Widen(const std::string& str);
    [[nodiscard]] bool ContainsChar(const std::string& str, std::initializer_list<char> Filter);
    [[nodiscard]] bool CharIsDigit(const char Character);
    std::string ToLower(std::string& String);
}

namespace Color
{
    ImVec4 NormalizeColor(float red, float green, float blue, float alpha = 255.0f);
}

namespace Json
{
    void SetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, float r, float g, float b, float a);
    void SetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, ImVec4 Color);
    ImVec2 GetFloat2(nlohmann::json& Json, const char* FirstKey, const char* SecondKey);
    ImVec4 GetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey);
}

namespace Gui
{
    void TooltipOnPrevious(std::string& Description, ImFont* Font = nullptr);
    void TooltipOnPrevious(const char* Description, ImFont* Font = nullptr);
    void ShowHelpMarker(const char* Description, const char* Label = "(?)");
    void LabelAndValue(const std::string& Label, const std::string& Value);
}

namespace File
{
    std::string LoadFileToString(const std::string& FullPath);
}

namespace Rfg
{
    std::string GetObjectTypeString(char ObjectType);
    std::string GetObjectSubTypeString(char ObjectSubType);
}

namespace Patching
{
    void LockGameMain();
    void UnlockGameMain();
}