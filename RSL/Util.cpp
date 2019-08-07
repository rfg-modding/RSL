#include "Util.h"

namespace Util::Json
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

namespace Util::Gui
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
    void ShowHelpMarker(const char* Description, const char* Label)
    {
        ImGui::TextDisabled(Label);
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
    void LabelAndValue(const std::string& Label, const std::string& Value)
    {
        ImGui::Text(Label.c_str());
        ImGui::SameLine();
        ImGui::TextColored(Globals::SecondaryTextColor, Value.c_str());
    }
}

// Wrapper for the windows function "Beep". Runs Beep in it's own thread 
// to avoid pausing execution in the current thread for the duration of the sound.
// Still causes a slight pause, likely due to the overhead of starting a new thread, 
// but it's better than running Beep in the same thread.
void Util::General::ThreadedBeep(ulong Frequency, ulong Duration)
{
    std::thread BeepThread([&] {Beep(Frequency, Duration); });
    BeepThread.detach();
}

// Loads a file into a string and returns that string.
// Got this from here: https://stackoverflow.com/a/2602060
std::string Util::General::LoadFileToString(const std::string& FullPath)
{
    std::ifstream t(FullPath);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    return str;
}

// Takes a string as input and returns it's fully lowercase equivalent. This function might crash if non ascii characters are passed in.
std::string Util::General::ToLower(std::string& String)
{
    std::string Copy = String; //Copy the string since we want to leave the original string intact
    std::transform(Copy.begin(), Copy.end(), Copy.begin(), [](unsigned char c) { return std::tolower(c); });
    return Copy;
}
