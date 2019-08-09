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

std::string Util::RFG::GetObjectTypeString(char ObjectType)
{
    switch (ObjectType)
    {
    case 0:
        return "Human";
    case 1:
        return "Item";
    case 2:
        return "Mover";
    case 3:
        return "Vehicle";
    case 4:
        return "Effect";
    case 5:
        return "Debris";
    case 6:
        return "Turret";
    case 7:
        return "Light";
    case 8:
        return "PlayerStart";
    case 9:
        return "CoverNode";
    case 10:
        return "NavPoint";
    case 11:
        return "Squad";
    case 12:
        return "Convoy";
    case 13:
        return "ConvoyEnd";
    case 14:
        return "Patrol";
    case 15:
        return "GuardNode";
    case 16:
        return "Skybox";
    case 17:
        return "Ladder";
    case 18:
        return "Constraint";
    case 19:
        return "Zone";
    case 20:
        return "TriggerRegion";
    case 21:
        return "MarauderAmbushRegion";
    case 22:
        return "RestrictedArea";
    case 23:
        return "SpawnRegion";
    case 24:
        return "AmbientSpawnRegion";
    case 25:
        return "VehicleSpawnNode";
    case 26:
        return "NpcSpawnNode";
    case 27:
        return "TurretSpawnNode";
    case 28:
        return "ActionNode";
    case 29:
        return "SquadSpawnNode";
    case 30:
        return "RoadblockNode";
    case 31:
        return "ShapeCutter";
    case 32:
        return "District";
    case 33:
        return "MultiMarker";
    case 34:
        return "PathRoad";
    case 35:
        return "LightParams";
    case 36:
        return "Dummy";
    case 37:
        return "ActivitySpawn";
    case 38:
        return "RaidNode";
    case 39:
        return "Subzone";
    case 40:
        return "HouseArrestNode";
    case 41:
        return "DemolitionsMasterNode";
    case 42:
        return "RidingShotgunNode";
    case 43:
        return "DeliveryNode";
    case 44:
        return "BoundingBox";
    case 45:
        return "MissionStartNode";
    case 46:
        return "Courier";
    case 47:
        return "CourierEnd";
    case 48:
        return "Safehouse";
    case 49:
        return "BftpNode";
    case 50:
        return "AirstrikeDefenseNode";
    case 51:
        return "UpgradeNode";
    case 52:
        return "AreaDefenseNode";
    case 4294967295:
        return "Undefined";
    default:
        return "Invalid object type";
    }
}

std::string Util::RFG::GetObjectSubTypeString(char ObjectSubType)
{
    switch (ObjectSubType)
    {
    case 4294967295:
        return "Undefined";
    case 0:
        return "MoverGeneral";
    case 1:
        return "MoverRfg";
    case 2:
        return "HumanNpc";
    case 3:
        return "HumanPlayer";
    case 4:
        return "VehicleAuto";
    case 5:
        return "VehicleFlyer";
    case 6:
        return "VehicleWalker";
    case 7:
        return "ItemWeapon";
    case 8:
        return "ItemProjectile";
    case 9:
        return "ItemMultiFlag";
    case 10:
        return "ItemMultiBackpack";
    case 11:
        return "NumObjectSubTypes (You probably shouldn't be seeing this...)";
    default:
        return "Invalid object subtype";
    }
}
