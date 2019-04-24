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

	//ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
	ImGui::PushFont(FontLarge);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.556f, 0.823f, 0.541f, 1.0f));
	if (ImGui::Button(std::string(u8"Scripts " + std::string(ICON_FA_CODE) + u8"##ScriptSelectIcon").c_str()))
	{
		Gui->ShowAppScriptsMenu = !Gui->ShowAppScriptsMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu displays all the scripts detected in the scripts folder and lets you run, edit, and stop them on command. If the script isn't using event hooks then stopping it does nothing, since it stops after running once.", FontNormal);
	
	//ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.357f, 0.659f, 0.863f, 1.0f));
	if (ImGui::Button(std::string(u8"Lua console " + std::string(ICON_FA_TERMINAL) + u8"##LuaConsoleIcon").c_str()))
	{
		Gui->ToggleLuaConsole();
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("The console is useful for quickly setting values or calling functions without writing a script. Anything that scripts have access to, the console does too. The console is just running your input into it as a script.", FontNormal);
	
	//ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.808f, 0.267f, 1.0f));
	if (ImGui::Button(std::string(u8"Script editor " + std::string(ICON_FA_EDIT) + u8"##ScriptEditorIcon").c_str()))
	{
		Gui->ShowAppScriptEditor = !Gui->ShowAppScriptEditor;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("The script editor allows you to save, load, edit, and run lua scripts in game, and provides basic lua syntax highlighting.", FontNormal);
	
	//ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.404f, 0.416f, 0.435f, 1.0f));
	if (ImGui::Button(std::string(u8"Tweaks menu " + std::string(ICON_FA_SLIDERS_H) + u8"##TweaksIcon").c_str()))
	{
		Gui->ShowAppTweaksMenu = !Gui->ShowAppTweaksMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu has settings for invulnerability, infinite jetpack, player move speed, player jump height, xray vision, and more.", FontNormal);
	
	//ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.961f, 0.753f, 0.698f, 1.0f));
	if (ImGui::Button(std::string(u8"Teleport menu " + std::string(ICON_FA_MAP_MARKED) + u8"##TeleportIcon").c_str()))
	{
		Gui->ShowAppTeleportMenu = !Gui->ShowAppTeleportMenu;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("This menu allows you to teleport around the map. There are many preset locations, and you may create your own. Any of your custom locations are saved in TeleportLocations.json. You don't need to edit it by hand as you can do all the editing you need in the gui.", FontNormal);
	
	//ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.361f, 0.129f, 1.0f, 1.0f));
	if (ImGui::Button(std::string(u8"Theme editor " + std::string(ICON_FA_PALETTE) + u8"##ThemeEditorIcon").c_str()))
	{
		Gui->ShowAppThemeEditor = !Gui->ShowAppThemeEditor;
	}
	ImGui::PopStyleColor();
	Utilities::GUI::TooltipOnPrevious("You can use the theme editor to change the color scheme and style of the overlay gui. It allows you to save your settings to GUIConfig.json and share that with others so they can use it. This release only supports a having a single theme, but a later release will have a themes folder so you can easily switch between them.", FontNormal);
	ImGui::PopFont();
	ImGui::PopStyleColor();
	//ImGui::PopStyleColor(3);
	//ImGui::PopStyleVar();

	ImGui::PushItemWidth(225.0f);
	ImGui::TextWrapped("Welcome to the RFGR Script Loader overlay. Above are \
some buttons for menus which you might find useful. Tooltips with more info \
appear if you hover over them. You can also access all of these menus with \
the top menu bar above.");
	//ImGui::Text("");
	ImGui::Text("\nUseful shortcuts:");
	ImGui::Text("Toggle overlay: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "F1");
	ImGui::Text("Toggle script editor: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "F2");
	ImGui::Text("Toggle lua console: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Tilde (~)");
	ImGui::Text("Toggle hud: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Numpad 1");
	ImGui::Text("Toggle fog: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Numpad 2");
	ImGui::Text("Toggle free cam: ");
	ImGui::SameLine(); ImGui::TextColored(SecondaryTextColor, "Numpad 3");

	/*if (ImGui::CollapsingHeader("Notes:"))
	{
		ImGui::Text("Notes");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Please keep in mind that this is a very early version of this tool. Expect there to be bugs and incomplete features. If you encounter a bug that is not in the known bugs section, please let me know. I'd appreciate that. Some issues only pop up for certain people and I can only test on so many computers myself.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The menu above has some example menus that came with the gui library I'm using. They will be customized for the game later on.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- I've not implemented scripts yet so that section is empty.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Globals has a few values you can modify, later on you'll there will be more values and they will be accesible to scripts.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Teleport has both manual and preset teleportation options. Try not to move for at least 5 seconds after teleporting to allow for assets to load in. Sometimes you'll fall through the world with TP. Either wait or repeatedly press the teleport button in this case. Usually if you wait the game will bring you back to the surface after a few seconds.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Player variables is a list of some of the values in memory that define the player. I've only added a 1/4th to 1/3rd of the values so far and I haven't mapped some of them out yet, so it isn't very useful immediately. Once I have all values added to the gui and figure out which ones you can safely change I'll add the option to edit these values as well.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Try hovering your mouse over different gui elements. Many of them, especially in the teleport section, have useful tooltips.");
	}
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Known bugs / issues"))
	{
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- Having this tool activated causes opening weapons lockers not to work. Weapon crates still work. This is an odd bug since none of my code affects weapon lockers in a direct way. It's something unexpected which I will work on fixing soon.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The game will crash if you try to switch either to or from plain windowed mode. Using the maximize button visible in windowed mode should not cause crashes. Switching between exclusive fullscreen and fullscreen windowed should not cause any crashes. I suggest using fullscreen windowed if you expect yourself to be alt-tabbing out of the game.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- I recommend using the tool with the debug console disabled. It's an exterior window and can sometimes cause issues with the tool loading. It is off by default, so if you haven't turned it on, don't worry about it. Eventually I'll replace it completely with the in game console in the examples menu. Which is a dummy console that came with this gui library for now.");
		ImGui::PushItemWidth(300.0f);
		ImGui::TextWrapped("- The \"Global explosion modifiers\" section is completely broken and will make explosions stupidly overpowered rapidly. Use at your own risk. You must restart the game to revert it's effects.");
	}*/

	ImGui::End();
}