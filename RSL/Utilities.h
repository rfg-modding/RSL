#pragma once
#include "RenderInterfaceD3D11.h"

namespace Util::Json
{
	void SetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, float r, float g, float b, float a);
	void SetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, ImVec4 Color);
	ImVec2 GetFloat2(nlohmann::json& Json, const char* FirstKey, const char* SecondKey);
	ImVec4 GetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey);
}

namespace Util::Gui
{
	void TooltipOnPrevious(std::string& Description, ImFont* Font = nullptr);
	void TooltipOnPrevious(const char* Description, ImFont* Font = nullptr);
	void ShowHelpMarker(const char* Description);
    void LabelAndValue(const std::string& Label, const std::string& Value);
}

namespace Util::General
{
    void ThreadedBeep(ulong Frequency, ulong Duration);
    std::string LoadFileToString(const std::string& FullPath);
}