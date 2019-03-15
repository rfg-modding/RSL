#pragma once
#include "BaseGui.h"

class ThemeEditorGui
{
public:
	ThemeEditorGui();
	~ThemeEditorGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);

	bool ShowStyleSelector(const char* Label);
	void ShowFontSelector(const char* Label);

	bool LoadGUIConfig();
	bool SaveGUIConfig(std::string ThemeName, std::string Description, std::string Author, std::string Readme, std::string Filename);

	nlohmann::json GUIConfig;

private:
	bool* OpenState = nullptr;
};

