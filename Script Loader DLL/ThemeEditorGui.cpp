#include "ThemeEditorGui.h"

ThemeEditorGui::ThemeEditorGui()
{

}

ThemeEditorGui::~ThemeEditorGui()
{

}

void ThemeEditorGui::Initialize(bool* _OpenState)
{
	OpenState = _OpenState;

	LoadGUIConfig();
}

void ThemeEditorGui::Draw(const char* Title)
{
	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title, OpenState))
	{
		ImGui::End();
		return;
	}
	ImGuiStyle* ref = &ImGui::GetStyle();

	// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
	ImGuiStyle& style = ImGui::GetStyle();
	static ImGuiStyle ref_saved_style;

	// Default to using internal storage as reference
	static bool init = true;
	if (init && ref == NULL)
		ref_saved_style = style;
	init = false;
	if (ref == NULL)
		ref = &ref_saved_style;

	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

	if (ImGui::ShowStyleSelector("Colors##Selector"))
		ref_saved_style = style;
	ImGui::ShowFontSelector("Fonts##Selector");

	// Simplified Settings
	if (ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
		style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
	{ bool window_border = (style.WindowBorderSize > 0.0f); if (ImGui::Checkbox("WindowBorder", &window_border)) style.WindowBorderSize = window_border ? 1.0f : 0.0f; }
	ImGui::SameLine();
	{ bool frame_border = (style.FrameBorderSize > 0.0f); if (ImGui::Checkbox("FrameBorder", &frame_border)) style.FrameBorderSize = frame_border ? 1.0f : 0.0f; }
	ImGui::SameLine();
	{ bool popup_border = (style.PopupBorderSize > 0.0f); if (ImGui::Checkbox("PopupBorder", &popup_border)) style.PopupBorderSize = popup_border ? 1.0f : 0.0f; }

	// Save/Revert button
	if (ImGui::Button("Save Ref"))
		*ref = ref_saved_style = style;
	ImGui::SameLine();
	if (ImGui::Button("Revert Ref"))
		style = *ref;
	ImGui::SameLine();
	ShowHelpMarker("Save/Revert in local non-persistent storage. Default Colors definition are not affected. Use \"Export Colors\" below to save them somewhere.");
	ImGui::SameLine();
	if (ImGui::Button("Save to file"))
	{
		SaveGUIConfig("Default Dark Theme", "The default dark theme for the script loader.", "moneyl", "When making your own themes you can use this for extra information such as known bugs or optional settings. Note: This section will be used once I add a custom theme loading GUI to the script loader. Not present for the initial themes release.", "GUI Config");
	}

	ImGui::Separator();

	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Sizes"))
		{
			ImGui::Text("Main");
			ImGui::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
			ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 16.0f, "%.0f");
			ImGui::SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
			ImGui::SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
			ImGui::SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
			ImGui::SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
			ImGui::SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
			ImGui::SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
			ImGui::SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
			ImGui::Text("Borders");
			ImGui::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
			ImGui::SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
			ImGui::SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
			ImGui::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
			ImGui::SliderFloat("TabBorderSize", &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
			ImGui::Text("Rounding");
			ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 14.0f, "%.0f");
			ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 16.0f, "%.0f");
			ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
			ImGui::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");
			ImGui::Text("Alignment");
			ImGui::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
			ImGui::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); ShowHelpMarker("Alignment applies when a button is larger than its text content.");
			ImGui::Text("Safe Area Padding"); ImGui::SameLine(); ShowHelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
			ImGui::SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Colors"))
		{
			static int output_dest = 0;
			static bool output_only_modified = true;
			if (ImGui::Button("Export Unsaved"))
			{
				if (output_dest == 0)
					ImGui::LogToClipboard();
				else
					ImGui::LogToTTY();
				ImGui::LogText("ImVec4* colors = ImGui::GetStyle().Colors;", "\r\n");
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const ImVec4& col = style.Colors[i];
					const char* name = ImGui::GetStyleColorName(i);
					if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(ImVec4)) != 0)
						ImGui::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);", "\r\n", name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
				}
				ImGui::LogFinish();
			}
			ImGui::SameLine(); ImGui::PushItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0"); ImGui::PopItemWidth();
			ImGui::SameLine(); ImGui::Checkbox("Only Modified Colors", &output_only_modified);

			static ImGuiTextFilter filter;
			filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

			static ImGuiColorEditFlags alpha_flags = 0;
			ImGui::RadioButton("Opaque", &alpha_flags, 0); ImGui::SameLine();
			ImGui::RadioButton("Alpha", &alpha_flags, ImGuiColorEditFlags_AlphaPreview); ImGui::SameLine();
			ImGui::RadioButton("Both", &alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf); ImGui::SameLine();
			ShowHelpMarker("In the color list:\nLeft-click on colored square to open color picker,\nRight-click to open edit options menu.");

			ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
			ImGui::PushItemWidth(-160);
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				const char* name = ImGui::GetStyleColorName(i);
				if (!filter.PassFilter(name))
					continue;
				ImGui::PushID(i);
				ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
				if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
				{
					// Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
					// Read the FAQ and misc/fonts/README.txt about using icon fonts. It's really easy and super convenient!
					ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Save")) ref->Colors[i] = style.Colors[i];
					ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Revert")) style.Colors[i] = ref->Colors[i];
				}
				ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
				ImGui::TextUnformatted(name);
				ImGui::PopID();
			}
			ImGui::PopItemWidth();
			ImGui::EndChild();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Fonts"))
		{
			ImFontAtlas* atlas = ImGui::GetIO().Fonts;
			ShowHelpMarker("Read FAQ and misc/fonts/README.txt for details on font loading.");
			ImGui::PushItemWidth(120);
			for (int i = 0; i < atlas->Fonts.Size; i++)
			{
				ImFont* font = atlas->Fonts[i];
				ImGui::PushID(font);
				bool font_details_opened = ImGui::TreeNode(font, "Font %d: \"%s\"\n%.2f px, %d glyphs, %d file(s)", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
				ImGui::SameLine(); if (ImGui::SmallButton("Set as default")) ImGui::GetIO().FontDefault = font;
				if (font_details_opened)
				{
					ImGui::PushFont(font);
					ImGui::Text("The quick brown fox jumps over the lazy dog");
					ImGui::PopFont();
					ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
					ImGui::SameLine(); ShowHelpMarker("Note than the default embedded font is NOT meant to be scaled.\n\nFont are currently rendered into bitmaps at a given size at the time of building the atlas. You may oversample them to get some flexibility with scaling. You can also render at multiple sizes and select which one to use at runtime.\n\n(Glimmer of hope: the atlas system should hopefully be rewritten in the future to make scaling more natural and automatic.)");
					ImGui::InputFloat("Font offset", &font->DisplayOffset.y, 1, 1, "%.0f");
					ImGui::Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
					ImGui::Text("Fallback character: '%c' (%d)", font->FallbackChar, font->FallbackChar);
					ImGui::Text("Texture surface: %d pixels (approx) ~ %dx%d", font->MetricsTotalSurface, (int)sqrtf((float)font->MetricsTotalSurface), (int)sqrtf((float)font->MetricsTotalSurface));
					for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
						if (ImFontConfig* cfg = &font->ConfigData[config_i])
							ImGui::BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d", config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH);
					if (ImGui::TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size))
					{
						// Display all glyphs of the fonts in separate pages of 256 characters
						for (int base = 0; base < 0x10000; base += 256)
						{
							int count = 0;
							for (int n = 0; n < 256; n++)
								count += font->FindGlyphNoFallback((ImWchar)(base + n)) ? 1 : 0;
							if (count > 0 && ImGui::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
							{
								float cell_size = font->FontSize * 1;
								float cell_spacing = style.ItemSpacing.y;
								ImVec2 base_pos = ImGui::GetCursorScreenPos();
								ImDrawList* draw_list = ImGui::GetWindowDrawList();
								for (int n = 0; n < 256; n++)
								{
									ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size + cell_spacing), base_pos.y + (n / 16) * (cell_size + cell_spacing));
									ImVec2 cell_p2(cell_p1.x + cell_size, cell_p1.y + cell_size);
									const ImFontGlyph* glyph = font->FindGlyphNoFallback((ImWchar)(base + n));
									draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255, 255, 255, 100) : IM_COL32(255, 255, 255, 50));
									if (glyph)
										font->RenderChar(draw_list, cell_size, cell_p1, ImGui::GetColorU32(ImGuiCol_Text), (ImWchar)(base + n)); // We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions available to generate a string.
									if (glyph && ImGui::IsMouseHoveringRect(cell_p1, cell_p2))
									{
										ImGui::BeginTooltip();
										ImGui::Text("Codepoint: U+%04X", base + n);
										ImGui::Separator();
										ImGui::Text("AdvanceX: %.1f", glyph->AdvanceX);
										ImGui::Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
										ImGui::Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
										ImGui::EndTooltip();
									}
								}
								ImGui::Dummy(ImVec2((cell_size + cell_spacing) * 16, (cell_size + cell_spacing) * 16));
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
				ImGui::PopID();
			}
			if (ImGui::TreeNode("Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight))
			{
				ImGui::Image(atlas->TexID, ImVec2((float)atlas->TexWidth, (float)atlas->TexHeight), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
				ImGui::TreePop();
			}

			static float window_scale = 1.0f;
			if (ImGui::DragFloat("this window scale", &window_scale, 0.005f, 0.3f, 2.0f, "%.1f"))           // scale only this window
				ImGui::SetWindowFontScale(window_scale);
			ImGui::DragFloat("global scale", &ImGui::GetIO().FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.1f");  // scale everything
			ImGui::PopItemWidth();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Rendering"))
		{
			ImGui::Checkbox("Anti-aliased lines", &style.AntiAliasedLines); ImGui::SameLine(); ShowHelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");
			ImGui::Checkbox("Anti-aliased fill", &style.AntiAliasedFill);
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX, "%.2f", 2.0f);
			if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;
			ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
			ImGui::PopItemWidth();

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::PopItemWidth();
	ImGui::End();
}

bool ThemeEditorGui::ShowStyleSelector(const char* label)
{
	static int style_idx = -1;
	if (ImGui::Combo(label, &style_idx, "RFGR Dark\0Classic\0Dark\0Light\0"))
	{
		switch (style_idx)
		{
		case 0: LoadGUIConfig(); break;
		case 1: ImGui::StyleColorsClassic(); break;
		case 2: ImGui::StyleColorsDark(); break;
		case 3: ImGui::StyleColorsLight(); break;
		}
		return true;
	}
	return false;
}

void ThemeEditorGui::ShowFontSelector(const char* label)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font_current = ImGui::GetFont();
	if (ImGui::BeginCombo(label, font_current->GetDebugName()))
	{
		for (int n = 0; n < io.Fonts->Fonts.Size; n++)
			if (ImGui::Selectable(io.Fonts->Fonts[n]->GetDebugName(), io.Fonts->Fonts[n] == font_current))
				io.FontDefault = io.Fonts->Fonts[n];
		ImGui::EndCombo();
	}
	ImGui::SameLine();
	ShowHelpMarker(
		"- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
		"- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
		"- Read FAQ and documentation in misc/fonts/ for more details.\n"
		"- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}

bool ThemeEditorGui::LoadGUIConfig()
{
	std::string ExePath = GetEXEPath(false);
	Logger::Log("Started loading \"GUI Config.json\".", LogInfo);

	if (fs::exists(ExePath + "RFGR Script Loader/Settings/GUI Config.json"))
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("Parsing \"GUI Config.json\"", LogInfo);
			std::ifstream Config(ExePath + "RFGR Script Loader/Settings/GUI Config.json");
			Config >> GUIConfig;
			Config.close();
			return true;
		}, "GUI Config.json", "parse", "parsing"))
		{
			return false;
		}
		Logger::Log("No parse exceptions detected.", LogInfo);
	}
	else
	{
		if (!JsonExceptionHandler([&]
		{
			Logger::Log("\"GUI Settings.json\" not found. Creating from default values.", LogWarning);
			CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");

			GUIConfig["Theme Info"]["Theme name"] = std::string("Default Dark Theme");
			GUIConfig["Theme Info"]["Description"] = std::string("The default dark theme for the script loader.");
			GUIConfig["Theme Info"]["Author"] = std::string("moneyl");
			GUIConfig["Theme Info"]["Readme"] = std::string("When making your own themes you can use this for extra information such as known bugs or optional settings. Note: This section will be used once I add a custom theme loading GUI to the script loader. Not present for the initial themes release.");

			GUIConfig["Style"]["Alpha"] = 0.95f;
			GUIConfig["Style"]["AntiAliasedFill"] = true;
			GUIConfig["Style"]["ButtonTextAlign"][0] = 0.5f;
			GUIConfig["Style"]["ButtonTextAlign"][1] = 0.5f;
			GUIConfig["Style"]["ChildBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
			GUIConfig["Style"]["ChildRounding"] = 3.0f;
			GUIConfig["Style"]["DisplaySafeAreaPadding"][0] = 3.0f;
			GUIConfig["Style"]["DisplaySafeAreaPadding"][1] = 3.0f;
			GUIConfig["Style"]["FrameBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
			GUIConfig["Style"]["FramePadding"][0] = 4.0f;
			GUIConfig["Style"]["FramePadding"][1] = 3.0f;
			GUIConfig["Style"]["FrameRounding"] = 3.0f;
			GUIConfig["Style"]["GrabMinSize"] = 12.0f;
			GUIConfig["Style"]["GrabRounding"] = 3.0f;
			GUIConfig["Style"]["IndentSpacing"] = 21.0f;
			GUIConfig["Style"]["ItemInnerSpacing"][0] = 4.0f;
			GUIConfig["Style"]["ItemInnerSpacing"][1] = 4.0f;
			GUIConfig["Style"]["ItemSpacing"][0] = 8.0f;
			GUIConfig["Style"]["ItemSpacing"][1] = 4.0f;
			GUIConfig["Style"]["PopupBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
			GUIConfig["Style"]["PopupRounding"] = 3.0f;
			GUIConfig["Style"]["ScrollbarRounding"] = 3.0f;
			GUIConfig["Style"]["ScrollbarSize"] = 18.0f;
			GUIConfig["Style"]["TabBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
			GUIConfig["Style"]["TabRounding"] = 3.0f;
			GUIConfig["Style"]["TouchExtraPadding"][0] = 0.0f;
			GUIConfig["Style"]["TouchExtraPadding"][1] = 0.0f;
			GUIConfig["Style"]["WindowBorderSize"] = 1.0f; //Values > 1.0 can cause performance issues.
			GUIConfig["Style"]["WindowPadding"][0] = 8.0f;
			GUIConfig["Style"]["WindowPadding"][1] = 8.0f;
			GUIConfig["Style"]["WindowRounding"] = 3.0f;
			GUIConfig["Style"]["WindowTitleAlign"][0] = 0.0f;
			GUIConfig["Style"]["WindowTitleAlign"][1] = 0.5f;

			/*float DefaultGlobalOpacity = 1.0f;
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Text", ImVec4(0.945f, 0.945f, 0.945f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TextDisabled", ImVec4(0.610f, 0.610f, 0.610f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "WindowBackground", ImVec4(0.349f, 0.349f, 0.349f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ChildBackground", ImVec4(0.357f, 0.357f, 0.357f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PopupBackground", ImVec4(0.357f, 0.357f, 0.357f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Border", ImVec4(0.430f, 0.430f, 0.430f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "BorderShadow", ImVec4(0.498f, 0.498f, 0.498f, 0.000f));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackground", ImVec4(0.394f, 0.394f, 0.394f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackgroundHovered", ImVec4(0.333f, 0.333f, 0.333f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackgroundActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackground", ImVec4(0.522f, 0.522f, 0.522f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackgroundActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackgroundCollapsed", ImVec4(0.422f, 0.422f, 0.422f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "MenuBarBackground", ImVec4(0.422f, 0.422f, 0.422f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarBackground", ImVec4(0.322f, 0.322f, 0.322f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrab", ImVec4(0.510f, 0.510f, 0.510f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrabHovered", ImVec4(0.610f, 0.610f, 0.610f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrabActive", ImVec4(0.710f, 0.710f, 0.710f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "CheckMark", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SliderGrab", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SliderGrabActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Button", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ButtonHovered", ImVec4(0.334f, 0.615f, 0.812f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ButtonActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Header", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "HeaderHovered", ImVec4(0.334f, 0.615f, 0.812f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "HeaderActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Separator", ImVec4(0.510f, 0.510f, 0.510f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SeparatorHovered", ImVec4(0.610f, 0.610f, 0.610f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SeparatorActive", ImVec4(0.710f, 0.710f, 0.710f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGrip", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGripHovered", ImVec4(0.334f, 0.615f, 0.812f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGripActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Tab", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabHovered", ImVec4(0.334f, 0.615f, 0.812f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabActive", ImVec4(0.358f, 0.660f, 0.871f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabUnfocused", ImVec4(0.07f, 0.10f, 0.15f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabUnfocusedActive", ImVec4(0.14f, 0.26f, 0.42f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotLines", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotLinesHovered", ImVec4(0.000f, 0.578f, 0.900f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotHistogram", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotHistogramHovered", ImVec4(0.334f, 0.615f, 0.812f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TextSelectedBackground", ImVec4(0.310f, 0.571f, 0.753f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "DragDropTarget", ImVec4(1.00f, 1.00f, 0.00f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavHighlight", ImVec4(0.26f, 0.59f, 0.98f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavWindowingHighlight", ImVec4(1.00f, 1.00f, 1.00f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavWindowingDimBackground", ImVec4(0.80f, 0.80f, 0.80f, DefaultGlobalOpacity));
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ModalWindowDimBackground", ImVec4(0.80f, 0.80f, 0.80f, DefaultGlobalOpacity));*/

			ImVec4* Colors = ImGui::GetStyle().Colors;
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Text", Colors[ImGuiCol_Text]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TextDisabled", Colors[ImGuiCol_TextDisabled]);
			Colors[ImGuiCol_WindowBg].w = 0.8627f;
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "WindowBackground", Colors[ImGuiCol_WindowBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ChildBackground", Colors[ImGuiCol_ChildBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PopupBackground", Colors[ImGuiCol_PopupBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Border", Colors[ImGuiCol_Border]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "BorderShadow", Colors[ImGuiCol_BorderShadow]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackground", Colors[ImGuiCol_FrameBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackgroundHovered", Colors[ImGuiCol_FrameBgHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackgroundActive", Colors[ImGuiCol_FrameBgActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackground", Colors[ImGuiCol_TitleBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackgroundActive", Colors[ImGuiCol_TitleBgActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackgroundCollapsed", Colors[ImGuiCol_TitleBgCollapsed]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "MenuBarBackground", Colors[ImGuiCol_MenuBarBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarBackground", Colors[ImGuiCol_ScrollbarBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrab", Colors[ImGuiCol_ScrollbarGrab]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrabHovered", Colors[ImGuiCol_ScrollbarGrabHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrabActive", Colors[ImGuiCol_ScrollbarGrabActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "CheckMark", Colors[ImGuiCol_CheckMark]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SliderGrab", Colors[ImGuiCol_SliderGrab]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SliderGrabActive", Colors[ImGuiCol_SliderGrabActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Button", Colors[ImGuiCol_Button]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ButtonHovered", Colors[ImGuiCol_ButtonHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ButtonActive", Colors[ImGuiCol_ButtonActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Header", Colors[ImGuiCol_Header]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "HeaderHovered", Colors[ImGuiCol_HeaderHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "HeaderActive", Colors[ImGuiCol_HeaderActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Separator", Colors[ImGuiCol_Separator]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SeparatorHovered", Colors[ImGuiCol_SeparatorHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "SeparatorActive", Colors[ImGuiCol_SeparatorActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGrip", Colors[ImGuiCol_ResizeGrip]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGripHovered", Colors[ImGuiCol_ResizeGripHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGripActive", Colors[ImGuiCol_ResizeGripActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "Tab", Colors[ImGuiCol_Tab]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabHovered", Colors[ImGuiCol_TabHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabActive", Colors[ImGuiCol_TabActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabUnfocused", Colors[ImGuiCol_TabUnfocused]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabUnfocusedActive", Colors[ImGuiCol_TabUnfocusedActive]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotLines", Colors[ImGuiCol_PlotLines]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotLinesHovered", Colors[ImGuiCol_PlotLinesHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotHistogram", Colors[ImGuiCol_PlotHistogram]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotHistogramHovered", Colors[ImGuiCol_PlotHistogramHovered]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "TextSelectedBackground", Colors[ImGuiCol_TextSelectedBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "DragDropTarget", Colors[ImGuiCol_DragDropTarget]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavHighlight", Colors[ImGuiCol_NavHighlight]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavWindowingHighlight", Colors[ImGuiCol_NavWindowingHighlight]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavWindowingDimBackground", Colors[ImGuiCol_NavWindowingDimBg]);
			Utilities::Json::SetFloat4(GUIConfig, "Colors", "ModalWindowDimBackground", Colors[ImGuiCol_ModalWindowDimBg]);

			std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/GUI Config.json");
			ConfigOutput << std::setw(4) << GUIConfig << std::endl;
			ConfigOutput.close();
			return true;
		}, "GUI Config.json", "write", "writing"))
		{
			return false;
		}
		Logger::Log("No write exceptions detected.", LogInfo);
	}

	if (!JsonExceptionHandler([&]
	{
		Logger::Log("Start of gui style reading.", LogInfo);
		ImGuiStyle& Style = ImGui::GetStyle(); //Currently 25 items
		Style.Alpha = GUIConfig["Style"]["Alpha"].get<float>();
		Style.AntiAliasedFill = GUIConfig["Style"]["AntiAliasedFill"].get<bool>();
		Style.ButtonTextAlign = Utilities::Json::GetFloat2(GUIConfig, "Style", "ButtonTextAlign");
		Style.ChildBorderSize = GUIConfig["Style"]["ChildBorderSize"].get<float>();
		Style.ChildRounding = GUIConfig["Style"]["ChildRounding"].get<float>();
		//Style.ColumnsMinSpacing = 1.0f;
		//Style.CurveTessellationTol = 1.25f;
		Style.DisplaySafeAreaPadding = Utilities::Json::GetFloat2(GUIConfig, "Style", "DisplaySafeAreaPadding");
		//Style.DisplayWindowPadding = ImVec2(1.0, 1.0f);
		Style.FrameBorderSize = GUIConfig["Style"]["FrameBorderSize"].get<float>();
		Style.FramePadding = Utilities::Json::GetFloat2(GUIConfig, "Style", "FramePadding");
		Style.FrameRounding = GUIConfig["Style"]["FrameRounding"].get<float>();
		Style.GrabMinSize = GUIConfig["Style"]["GrabMinSize"].get<float>();
		Style.GrabRounding = GUIConfig["Style"]["GrabRounding"].get<float>();
		Style.IndentSpacing = GUIConfig["Style"]["IndentSpacing"].get<float>();
		Style.ItemInnerSpacing = Utilities::Json::GetFloat2(GUIConfig, "Style", "ItemInnerSpacing");
		Style.ItemSpacing = Utilities::Json::GetFloat2(GUIConfig, "Style", "ItemSpacing");
		//Style.MouseCursorScale = 1.0f;
		Style.PopupBorderSize = GUIConfig["Style"]["PopupBorderSize"].get<float>();
		Style.PopupRounding = GUIConfig["Style"]["PopupRounding"].get<float>();
		Style.ScrollbarRounding = GUIConfig["Style"]["ScrollbarRounding"].get<float>();
		Style.ScrollbarSize = GUIConfig["Style"]["ScrollbarSize"].get<float>();
		Style.TabBorderSize = GUIConfig["Style"]["TabBorderSize"].get<float>();
		Style.TabRounding = GUIConfig["Style"]["TabRounding"].get<float>();
		Style.TouchExtraPadding = Utilities::Json::GetFloat2(GUIConfig, "Style", "TouchExtraPadding");
		Style.WindowBorderSize = GUIConfig["Style"]["WindowBorderSize"].get<float>();
		//Style.WindowMinSize = 1.0f;
		Style.WindowPadding = Utilities::Json::GetFloat2(GUIConfig, "Style", "WindowPadding");
		Style.WindowRounding = GUIConfig["Style"]["WindowRounding"].get<float>();
		Style.WindowTitleAlign = Utilities::Json::GetFloat2(GUIConfig, "Style", "WindowTitleAlign");
		Logger::Log("Done reading gui style.", LogInfo);

		Logger::Log("Start of gui color reading.", LogInfo);
		ImVec4* Colors = ImGui::GetStyle().Colors; //48 items
		Colors[ImGuiCol_Text] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "Text");
		Colors[ImGuiCol_TextDisabled] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TextDisabled");
		Colors[ImGuiCol_WindowBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "WindowBackground");
		Colors[ImGuiCol_ChildBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ChildBackground");
		Colors[ImGuiCol_PopupBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "PopupBackground");
		Colors[ImGuiCol_Border] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "Border");
		Colors[ImGuiCol_BorderShadow] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "BorderShadow");
		Colors[ImGuiCol_FrameBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "FrameBackground");
		Colors[ImGuiCol_FrameBgHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "FrameBackgroundHovered");
		Colors[ImGuiCol_FrameBgActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "FrameBackgroundActive");
		Colors[ImGuiCol_TitleBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TitleBackground");
		Colors[ImGuiCol_TitleBgActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TitleBackgroundActive");
		Colors[ImGuiCol_TitleBgCollapsed] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TitleBackgroundCollapsed");
		Colors[ImGuiCol_MenuBarBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "MenuBarBackground");
		Colors[ImGuiCol_ScrollbarBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ScrollbarBackground");
		Colors[ImGuiCol_ScrollbarGrab] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ScrollbarGrab");
		Colors[ImGuiCol_ScrollbarGrabHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ScrollbarGrabHovered");
		Colors[ImGuiCol_ScrollbarGrabActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ScrollbarGrabActive");
		Colors[ImGuiCol_CheckMark] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "CheckMark");
		Colors[ImGuiCol_SliderGrab] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "SliderGrab");
		Colors[ImGuiCol_SliderGrabActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "SliderGrabActive");
		Colors[ImGuiCol_Button] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "Button");
		Colors[ImGuiCol_ButtonHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ButtonHovered");
		Colors[ImGuiCol_ButtonActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ButtonActive");
		Colors[ImGuiCol_Header] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "Header");
		Colors[ImGuiCol_HeaderHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "HeaderHovered");
		Colors[ImGuiCol_HeaderActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "HeaderActive");
		Colors[ImGuiCol_Separator] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "Separator");
		Colors[ImGuiCol_SeparatorHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "SeparatorHovered");
		Colors[ImGuiCol_SeparatorActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "SeparatorActive");
		Colors[ImGuiCol_ResizeGrip] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ResizeGrip");
		Colors[ImGuiCol_ResizeGripHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ResizeGripHovered");
		Colors[ImGuiCol_ResizeGripActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ResizeGripActive");
		Colors[ImGuiCol_Tab] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "Tab");
		Colors[ImGuiCol_TabHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TabHovered");
		Colors[ImGuiCol_TabActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TabActive");
		Colors[ImGuiCol_TabUnfocused] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TabUnfocused");
		Colors[ImGuiCol_TabUnfocusedActive] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TabUnfocusedActive");
		Colors[ImGuiCol_PlotLines] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "PlotLines");
		Colors[ImGuiCol_PlotLinesHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "PlotLinesHovered");
		Colors[ImGuiCol_PlotHistogram] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "PlotHistogram");
		Colors[ImGuiCol_PlotHistogramHovered] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "PlotHistogramHovered");
		Colors[ImGuiCol_TextSelectedBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "TextSelectedBackground");
		Colors[ImGuiCol_DragDropTarget] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "DragDropTarget");
		Colors[ImGuiCol_NavHighlight] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "NavHighlight");
		Colors[ImGuiCol_NavWindowingHighlight] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "NavWindowingHighlight");
		Colors[ImGuiCol_NavWindowingDimBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "NavWindowingDimBackground");
		Colors[ImGuiCol_ModalWindowDimBg] = Utilities::Json::GetFloat4(GUIConfig, "Colors", "ModalWindowDimBackground");
		Logger::Log("Done reading gui color.", LogInfo);
		Logger::Log("End of gui theme reading.", LogInfo);

		return true;
	}, "GUI Config.json", "read", "reading"))
	{
		return false;
	}
	Logger::Log("No read exceptions detected.", LogInfo);

	Logger::Log("Done loading \"Settings.json\".", LogInfo);
	return true;
}

bool ThemeEditorGui::SaveGUIConfig(std::string ThemeName, std::string Description, std::string Author, std::string Readme, std::string Filename)
{
	if (!JsonExceptionHandler([&]
	{
		Logger::Log("Started saving \"GUI Config.json\".", LogInfo);
		std::string ExePath = GetEXEPath(false);
		CreateDirectoryIfNull(ExePath + "RFGR Script Loader/Settings/");

		GUIConfig["Theme Info"]["Theme name"] = ThemeName;
		GUIConfig["Theme Info"]["Description"] = Description;
		GUIConfig["Theme Info"]["Author"] = Author;
		GUIConfig["Theme Info"]["Readme"] = Readme;

		ImGuiStyle& Style = ImGui::GetStyle(); //Currently 25 items, some not provided to users since they aren't in the style editor.
		GUIConfig["Style"]["Alpha"] = Style.Alpha;
		GUIConfig["Style"]["AntiAliasedFill"] = Style.AntiAliasedFill;
		GUIConfig["Style"]["ButtonTextAlign"][0] = Style.ButtonTextAlign.x;
		GUIConfig["Style"]["ButtonTextAlign"][1] = Style.ButtonTextAlign.y;
		GUIConfig["Style"]["ChildBorderSize"] = Style.ChildBorderSize; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["ChildRounding"] = Style.ChildRounding;
		GUIConfig["Style"]["DisplaySafeAreaPadding"][0] = Style.DisplaySafeAreaPadding.x;
		GUIConfig["Style"]["DisplaySafeAreaPadding"][1] = Style.DisplaySafeAreaPadding.y;
		GUIConfig["Style"]["FrameBorderSize"] = Style.FrameBorderSize; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["FramePadding"][0] = Style.FramePadding.x;
		GUIConfig["Style"]["FramePadding"][1] = Style.FramePadding.y;
		GUIConfig["Style"]["FrameRounding"] = Style.FrameRounding;
		GUIConfig["Style"]["GrabMinSize"] = Style.GrabMinSize;
		GUIConfig["Style"]["GrabRounding"] = Style.GrabRounding;
		GUIConfig["Style"]["IndentSpacing"] = Style.IndentSpacing;
		GUIConfig["Style"]["ItemInnerSpacing"][0] = Style.ItemInnerSpacing.x;
		GUIConfig["Style"]["ItemInnerSpacing"][1] = Style.ItemInnerSpacing.y;
		GUIConfig["Style"]["ItemSpacing"][0] = Style.ItemSpacing.x;
		GUIConfig["Style"]["ItemSpacing"][1] = Style.ItemSpacing.y;
		GUIConfig["Style"]["PopupBorderSize"] = Style.PopupBorderSize; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["PopupRounding"] = Style.PopupRounding;
		GUIConfig["Style"]["ScrollbarRounding"] = Style.ScrollbarRounding;
		GUIConfig["Style"]["ScrollbarSize"] = Style.ScrollbarSize;
		GUIConfig["Style"]["TabBorderSize"] = Style.TabBorderSize;
		GUIConfig["Style"]["TabRounding"] = Style.TabRounding;
		GUIConfig["Style"]["TouchExtraPadding"][0] = Style.TouchExtraPadding.x;
		GUIConfig["Style"]["TouchExtraPadding"][1] = Style.TouchExtraPadding.y;
		GUIConfig["Style"]["WindowBorderSize"] = Style.WindowBorderSize; //Values > 1.0 can cause performance issues.
		GUIConfig["Style"]["WindowPadding"][0] = Style.WindowPadding.x;
		GUIConfig["Style"]["WindowPadding"][1] = Style.WindowPadding.y;
		GUIConfig["Style"]["WindowRounding"] = Style.WindowRounding;
		GUIConfig["Style"]["WindowTitleAlign"][0] = Style.WindowTitleAlign.x;
		GUIConfig["Style"]["WindowTitleAlign"][1] = Style.WindowTitleAlign.y;

		ImVec4* Colors = ImGui::GetStyle().Colors;
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "Text", Colors[ImGuiCol_Text]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TextDisabled", Colors[ImGuiCol_TextDisabled]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "WindowBackground", Colors[ImGuiCol_WindowBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ChildBackground", Colors[ImGuiCol_ChildBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "PopupBackground", Colors[ImGuiCol_PopupBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "Border", Colors[ImGuiCol_Border]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "BorderShadow", Colors[ImGuiCol_BorderShadow]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackground", Colors[ImGuiCol_FrameBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackgroundHovered", Colors[ImGuiCol_FrameBgHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "FrameBackgroundActive", Colors[ImGuiCol_FrameBgActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackground", Colors[ImGuiCol_TitleBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackgroundActive", Colors[ImGuiCol_TitleBgActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TitleBackgroundCollapsed", Colors[ImGuiCol_TitleBgCollapsed]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "MenuBarBackground", Colors[ImGuiCol_MenuBarBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarBackground", Colors[ImGuiCol_ScrollbarBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrab", Colors[ImGuiCol_ScrollbarGrab]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrabHovered", Colors[ImGuiCol_ScrollbarGrabHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ScrollbarGrabActive", Colors[ImGuiCol_ScrollbarGrabActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "CheckMark", Colors[ImGuiCol_CheckMark]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "SliderGrab", Colors[ImGuiCol_SliderGrab]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "SliderGrabActive", Colors[ImGuiCol_SliderGrabActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "Button", Colors[ImGuiCol_Button]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ButtonHovered", Colors[ImGuiCol_ButtonHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ButtonActive", Colors[ImGuiCol_ButtonActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "Header", Colors[ImGuiCol_Header]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "HeaderHovered", Colors[ImGuiCol_HeaderHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "HeaderActive", Colors[ImGuiCol_HeaderActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "Separator", Colors[ImGuiCol_Separator]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "SeparatorHovered", Colors[ImGuiCol_SeparatorHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "SeparatorActive", Colors[ImGuiCol_SeparatorActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGrip", Colors[ImGuiCol_ResizeGrip]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGripHovered", Colors[ImGuiCol_ResizeGripHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ResizeGripActive", Colors[ImGuiCol_ResizeGripActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "Tab", Colors[ImGuiCol_Tab]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabHovered", Colors[ImGuiCol_TabHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabActive", Colors[ImGuiCol_TabActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabUnfocused", Colors[ImGuiCol_TabUnfocused]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TabUnfocusedActive", Colors[ImGuiCol_TabUnfocusedActive]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotLines", Colors[ImGuiCol_PlotLines]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotLinesHovered", Colors[ImGuiCol_PlotLinesHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotHistogram", Colors[ImGuiCol_PlotHistogram]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "PlotHistogramHovered", Colors[ImGuiCol_PlotHistogramHovered]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "TextSelectedBackground", Colors[ImGuiCol_TextSelectedBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "DragDropTarget", Colors[ImGuiCol_DragDropTarget]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavHighlight", Colors[ImGuiCol_NavHighlight]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavWindowingHighlight", Colors[ImGuiCol_NavWindowingHighlight]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "NavWindowingDimBackground", Colors[ImGuiCol_NavWindowingDimBg]);
		Utilities::Json::SetFloat4(GUIConfig, "Colors", "ModalWindowDimBackground", Colors[ImGuiCol_ModalWindowDimBg]);

		std::ofstream ConfigOutput(ExePath + "RFGR Script Loader/Settings/" + Filename + ".json");
		ConfigOutput << std::setw(4) << GUIConfig << std::endl;
		ConfigOutput.close();
		return true;
	}, "GUI Settings.json", "write", "writing"))
	{
		return false;
	}
	Logger::Log("No write exceptions detected.", LogInfo);

	Logger::Log("Done saving \"GUI Config.json\".", LogInfo);
	return true;
}