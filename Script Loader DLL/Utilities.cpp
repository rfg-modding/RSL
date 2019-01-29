#include "Utilities.h"

namespace Utilities::Json
{
	void SetFloat4(nlohmann::json& JsonObject, const char* FirstKey, const char* SecondKey, float r, float g, float b, float a)
	{
		JsonObject[FirstKey][SecondKey][0] = r;
		JsonObject[FirstKey][SecondKey][1] = g;
		JsonObject[FirstKey][SecondKey][2] = b;
		JsonObject[FirstKey][SecondKey][3] = a;
	}

	void SetFloat4(nlohmann::json& JsonObject, const char* FirstKey, const char* SecondKey, ImVec4 Color)
	{
		JsonObject[FirstKey][SecondKey][0] = Color.x;
		JsonObject[FirstKey][SecondKey][1] = Color.y;
		JsonObject[FirstKey][SecondKey][2] = Color.z;
		JsonObject[FirstKey][SecondKey][3] = Color.w;
	}

	ImVec2 GetFloat2(nlohmann::json& JsonObject, const char* FirstKey, const char* SecondKey)
	{
		return ImVec2(JsonObject[FirstKey][SecondKey][0], JsonObject[FirstKey][SecondKey][1]);
	}

	ImVec4 GetFloat4(nlohmann::json& JsonObject, const char* FirstKey, const char* SecondKey)
	{
		return ImVec4(JsonObject[FirstKey][SecondKey][0], JsonObject[FirstKey][SecondKey][1], JsonObject[FirstKey][SecondKey][2], JsonObject[FirstKey][SecondKey][3]);
	}
}

namespace Utilities::GUI
{
	void TooltipOnPrevious(std::string& Description)
	{
		TooltipOnPrevious(Description.c_str());
	}

	void TooltipOnPrevious(const char* Description)
	{
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(Description);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}