#pragma once
#include "BaseGui.h"

class ThemeEditorGui : public BaseGui
{
public:
	ThemeEditorGui(bool* OpenState_, std::string Title_);
	~ThemeEditorGui() = default;

	void Draw() override;

	bool ShowStyleSelector(const char* Label);
	void ShowFontSelector(const char* Label);

	bool LoadGUIConfig();
	bool SaveGUIConfig(std::string ThemeName, std::string Description, std::string Author, std::string Readme, std::string Filename);

	nlohmann::json GUIConfig;
};

