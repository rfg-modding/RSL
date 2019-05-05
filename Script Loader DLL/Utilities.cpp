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
    /* Creates a tooltip with the given description and font on the previous ImGui element
     * created. The font argument is optional. If you leave it blank it'll use the current
     * font on the top of the stack.
     */
	void TooltipOnPrevious(std::string& Description, ImFont* Font)
	{
		TooltipOnPrevious(Description.c_str(), Font);
	}

    /* Creates a tooltip with the given description and font on the previous ImGui element
     * created. The font argument is optional. If you leave it blank it'll use the current
     * font on the top of the stack.
     */
	void TooltipOnPrevious(const char* Description, ImFont* Font)
	{
		if (ImGui::IsItemHovered())
		{
			if (Font)
			{
				ImGui::PushFont(Font);
			}
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(Description);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
			if (Font)
			{
				ImGui::PopFont();
			}
		}
	}

    /* Adds a text element of "(?)" to the current gui with the provided description as it's 
     * tooltip.
     */
	void ShowHelpMarker(const char* Description)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(Description);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

    /* GUI helper function for Label-Value pairs. For example, the shortcut list in the welcome
     * menu does this. So, you might have inputs of Label = "F1: ", and Value = "Toggle Overlay",
     * the resulting gui would be:
     * F1: Toggle Overlay
     */
    void LabelAndValue(std::string Label, std::string Value)
    {
        ImGui::Text(Label.c_str());
        ImGui::SameLine(); 
	    ImGui::TextColored(Globals::SecondaryTextColor, Value.c_str());
    }
}
