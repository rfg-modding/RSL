#include "WelcomeGui.h"

WelcomeGui::WelcomeGui(std::string Title_)
{
	Title = Title_;

	WindowFlags = 0;
	WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_NoCollapse;
	WindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	
    GuiManager = IocContainer->resolve<IGuiManager>();
}

void WelcomeGui::Draw()
{
	if (!Visible)
        return;
    if (!ImGui::Begin(Title.c_str(), &Visible, WindowFlags))
	{
		ImGui::End();
		return;
	}

    static auto GeneralTweaksGuiRef = GuiManager->GetGuiReference<BaseGui>("General tweaks").value();
    static auto ScriptSelectRef = GuiManager->GetGuiReference<BaseGui>("Scripts").value();
    static auto CameraSettingsRef = GuiManager->GetGuiReference<BaseGui>("Camera settings").value();
    static auto ScriptEditorRef = GuiManager->GetGuiReference<BaseGui>("Script editor").value();
    static auto TeleportGuiRef = GuiManager->GetGuiReference<BaseGui>("Teleport").value();
    static auto ExplosionSpawnerGuiRef = GuiManager->GetGuiReference<BaseGui>("Explosion spawner").value();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
	ImGui::PushFont(Globals::FontLarge);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_CODE) + u8" Scripts " + u8"##ScriptSelectIcon").c_str()))
        ScriptSelectRef.Get().Toggle();

    ImGui::PopStyleColor();
	Util::Gui::TooltipOnPrevious("This menu displays all the scripts detected in the scripts folder and lets you run, edit, and stop them on command. If the script isn't using event hooks then stopping it does nothing, since it stops after running once.", Globals::FontNormal);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.357f, 0.659f, 0.863f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_TERMINAL) + u8" Lua console " + u8"##LuaConsoleIcon").c_str()))
        GuiManager->ToggleLuaConsole();

    ImGui::PopStyleColor();
	Util::Gui::TooltipOnPrevious("The console is useful for quickly setting values or calling functions without writing a script. Anything that scripts have access to, the console does too. The console is just running your input into it as a script.", Globals::FontNormal);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.808f, 0.267f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8" Script editor " + u8"##ScriptEditorIcon").c_str()))
        ScriptEditorRef.Get().Toggle();

    ImGui::PopStyleColor();
	Util::Gui::TooltipOnPrevious("The script editor allows you to save, load, edit, and run lua scripts in game, and provides basic lua syntax highlighting.", Globals::FontNormal);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.404f, 0.416f, 0.435f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_SLIDERS_H) + u8" Tweaks menu " + u8"##TweaksIcon").c_str()))
        GeneralTweaksGuiRef.Get().Toggle();

    ImGui::PopStyleColor();
	Util::Gui::TooltipOnPrevious("This menu has settings for invulnerability, infinite jetpack, player move speed, player jump height, xray vision, and more.", Globals::FontNormal);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.961f, 0.753f, 0.698f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_MAP_MARKED) + u8" Teleport menu " + u8"##TeleportIcon").c_str()))
        TeleportGuiRef.Get().Toggle();

    ImGui::PopStyleColor();
	Util::Gui::TooltipOnPrevious("This menu allows you to teleport around the map. There are many preset locations, and you may create your own. Any of your custom locations are saved in TeleportLocations.json. You don't need to edit it by hand as you can do all the editing you need in the gui.", Globals::FontNormal);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.361f, 0.129f, 1.0f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_CAMERA) + u8" Camera menu " + u8"##CameraIcon").c_str()))
        CameraSettingsRef.Get().Toggle();

    ImGui::PopStyleColor();
	Util::Gui::TooltipOnPrevious("Contains several settings for the free camera and and experimental first person camera. Includes settings for clip distance which determines how far away you can see terrain and some shadows from.", Globals::FontNormal);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.784f, 0.094f, 0.035f, 1.0f));
    if (ImGui::Button(std::string(std::string(ICON_FA_BOMB) + u8" Explosion spawner " + u8"##BombIcon").c_str()))
        ExplosionSpawnerGuiRef.Get().Toggle();

    ImGui::PopStyleColor();
    Util::Gui::TooltipOnPrevious("This menu lets you turn on the explosion spawn feature, customize your explosion starting from presets, view explosion and effect presets, and more.", Globals::FontNormal);
	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::SetNextItemWidth(225.0f);
	ImGui::TextWrapped("Welcome to the Re-mars-tered Script Loader (RSL) overlay. Above are some \
buttons for menus which you might find useful. Tooltips with more info \
appear if you hover over them. You can also access all of these menus \
with the top menu bar above.");

	ImGui::Text("\nUseful shortcuts:");
    Util::Gui::LabelAndValue("Toggle overlay: ", "F1");
    Util::Gui::LabelAndValue("Toggle script editor: ", "F2");
    Util::Gui::LabelAndValue("Toggle lua console: ", "F4 (works any time)");
    Util::Gui::LabelAndValue("Run current script in editor: ", "F5");
    Util::Gui::LabelAndValue("Toggle hud: ", "Numpad 1");
    Util::Gui::LabelAndValue("Toggle fog: ", "Numpad 2");
    Util::Gui::LabelAndValue("Toggle free cam: ", "Numpad 3");
    Util::Gui::LabelAndValue("Lock object in crosshairs to introspection menu: ", "Numpad 4");
    Util::Gui::LabelAndValue("Ragdoll player: ", "Numpad 5");
	ImGui::End();
}