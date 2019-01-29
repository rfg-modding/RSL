#pragma once
#include "Globals.h"

namespace Utilities::Json
{
	void SetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, float r, float g, float b, float a);
	void SetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey, ImVec4 Color);
	ImVec2 GetFloat2(nlohmann::json& Json, const char* FirstKey, const char* SecondKey);
	ImVec4 GetFloat4(nlohmann::json& Json, const char* FirstKey, const char* SecondKey);
}

namespace Utilities::GUI
{
	void TooltipOnPrevious(std::string& Description);
	void TooltipOnPrevious(const char* Description);
}