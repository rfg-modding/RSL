#include "WelcomeGui.h"
#include "GuiSystem.h"

WelcomeGui::WelcomeGui(bool* OpenState_, std::string Title_)
{
	OpenState = OpenState_;
	Title = Title_;

	MainOverlayWindowFlags = 0;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoScrollbar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_MenuBar;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoMove;
	MainOverlayWindowFlags |= ImGuiWindowFlags_NoResize;
	MainOverlayWindowFlags |= ImGuiWindowFlags_NoCollapse;
	MainOverlayWindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoNav;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBackground;
	//MainOverlayWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

}

void WelcomeGui::Draw()
{
	if (!*OpenState)
	{
		return;
	}
	if (!ImGui::Begin(Title.c_str(), OpenState, MainOverlayWindowFlags))
	{
		ImGui::End();
		return;
	}

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
	ImGui::PushFont(Globals::FontLarge);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_CODE) + u8" Scripts " + u8"##ScriptSelectIcon").c_str()))
	{
		Gui->ShowAppScriptsMenu = !Gui->ShowAppScriptsMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu displays all the scripts detected in the scripts folder and lets you run, edit, and stop them on command. If the script isn't using event hooks then stopping it does nothing, since it stops after running once.", Globals::FontNormal);
	
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.357f, 0.659f, 0.863f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_TERMINAL) + u8" Lua console " + u8"##LuaConsoleIcon").c_str()))
	{
		Gui->ToggleLuaConsole();
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("The console is useful for quickly setting values or calling functions without writing a script. Anything that scripts have access to, the console does too. The console is just running your input into it as a script.", Globals::FontNormal);
	
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.808f, 0.267f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_EDIT) + u8" Script editor " + u8"##ScriptEditorIcon").c_str()))
	{
		Gui->ShowAppScriptEditor = !Gui->ShowAppScriptEditor;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("The script editor allows you to save, load, edit, and run lua scripts in game, and provides basic lua syntax highlighting.", Globals::FontNormal);
	
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.404f, 0.416f, 0.435f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_SLIDERS_H) + u8" Tweaks menu " + u8"##TweaksIcon").c_str()))
	{
		Gui->ShowAppTweaksMenu = !Gui->ShowAppTweaksMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu has settings for invulnerability, infinite jetpack, player move speed, player jump height, xray vision, and more.", Globals::FontNormal);
	
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.961f, 0.753f, 0.698f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_MAP_MARKED) + u8" Teleport menu " + u8"##TeleportIcon").c_str()))
	{
		Gui->ShowAppTeleportMenu = !Gui->ShowAppTeleportMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu allows you to teleport around the map. There are many preset locations, and you may create your own. Any of your custom locations are saved in TeleportLocations.json. You don't need to edit it by hand as you can do all the editing you need in the gui.", Globals::FontNormal);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.361f, 0.129f, 1.0f, 1.0f));
	if (ImGui::Button(std::string(std::string(ICON_FA_CAMERA) + u8" Camera menu " + u8"##CameraIcon").c_str()))
	{
		Gui->ShowAppFreeCamSettings = !Gui->ShowAppFreeCamSettings;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("Contains several settings for the free camera and and experimental first person camera. Includes settings for clip distance which determines how far away you can see terrain and some shadows from.", Globals::FontNormal);

	ImGui::PopStyleColor();
	ImGui::PopFont();

	ImGui::PushItemWidth(225.0f);
	ImGui::TextWrapped(R"(Welcome to the RFGR Script Loader overlay. Above are some 
                      buttons for menus which you might find useful. Tooltips with more info 
                      appear if you hover over them. You can also access all of these menus 
                      with the top menu bar above.)");

	ImGui::Text("\nUseful shortcuts:");
    Utilities::GUI::LabelAndValue("Toggle overlay: ", "F1");
    Utilities::GUI::LabelAndValue("Toggle script editor: ", "F2");
    Utilities::GUI::LabelAndValue("Toggle lua console: ", "Tilde (~)");
    Utilities::GUI::LabelAndValue("Toggle hud: ", "Numpad 1");
    Utilities::GUI::LabelAndValue("Toggle fog: ", "Numpad 2");
    Utilities::GUI::LabelAndValue("Toggle free cam: ", "Numpad 3");

	ImGui::End();
}