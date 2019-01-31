#pragma once
///#include "Globals.h"
///#include "RFGR_Types_Player.h"
#include "TeleportGui.h"

class ScriptManager;

class MainOverlay
{
public:
	MainOverlay();
	~MainOverlay();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);
	void DrawPlayerVariablesGui(bool UseSeparateWindow, const char* Title, bool* Open, ImGuiWindowFlags Flags);

	void ShowExampleAppMainMenuBar();
	//void ShowExampleAppConsole(bool* p_open);
	//void ShowExampleAppLog(bool* p_open);
	void ShowExampleAppPropertyEditor(bool* p_open);
	void ShowExampleAppLongText(bool* p_open);
	void ShowExampleAppSimpleOverlay(bool* p_open);
	void ShowAboutWindow(bool* p_open);
	//void ShowStyleEditor(ImGuiStyle* ref);

	//bool ShowStyleSelector(const char* label);
	//void ShowFontSelector(const char* label);

	//void ShowHelpMarker(const char* Description);

	Player* PlayerPtr = nullptr;
	Player TargetValues;
	matrix HavokPlayerOrient;
	vector HavokPlayerPosition;

	ImGuiWindowFlags MainOverlayWindowFlags = 0;
	ImGuiWindowFlags MainOverlayPopupFlags = 0;
	ImGuiInputTextFlags MainOverlayTeleportEditTextFlags = 0;

	bool* ShowAppConsole = false;
	bool* ShowAppMetrics = false;
	bool* ShowAppStyleEditor = false;
	bool* ShowAppAbout = false;
	bool* ShowAppGameInfoOverlay = false;

	bool* ShowAppMainMenuBar = false;
	bool* ShowAppLog = false;
	bool* ShowAppLongText = false;
	bool* ShowAppSimpleOverlay = false;

	bool PlayerPtrTargetsInitialized = false;
	bool NeedPlayerPosSet = false;
	float PlayerPositionTargetArray[3];

	float PlayerVelocityTargetArray[3];
	bool NeedPlayerVelocitySet = false;

	ScriptManager* Scripts;

private:
	bool* OpenState;
};

struct ExampleAppLog
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset
	bool                ScrollToBottom;

	void    Clear() { Buf.clear(); LineOffsets.clear(); }

	void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size);
		ScrollToBottom = true;
	}

	void    Draw(const char* title, bool* p_open = NULL)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}
		if (ImGui::Button("Clear")) Clear();
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		if (copy) ImGui::LogToClipboard();

		if (Filter.IsActive())
		{
			const char* buf_begin = Buf.begin();
			const char* line = buf_begin;
			for (int line_no = 0; line != NULL; line_no++)
			{
				const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
				if (Filter.PassFilter(line, line_end))
					ImGui::TextUnformatted(line, line_end);
				line = line_end && line_end[1] ? line_end + 1 : NULL;
			}
		}
		else
		{
			ImGui::TextUnformatted(Buf.begin());
		}

		if (ScrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;
		ImGui::EndChild();
		ImGui::End();
	}
};