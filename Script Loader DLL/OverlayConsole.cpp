#include "OverlayConsole.h"
#include "ScriptManager.h"

OverlayConsole::OverlayConsole()
{

}

OverlayConsole::~OverlayConsole()
{

}

void OverlayConsole::Initialize(bool* _OpenState)
{
	OpenState = _OpenState;

	WindowFlags = 0;
	WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	///WindowFlags |= ImGuiWindowFlags_MenuBar;
	WindowFlags |= ImGuiWindowFlags_NoMove;
	WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void OverlayConsole::Draw(const char* Title)
{
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvailWidth(), 400.0f), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	if (!ImGui::Begin(Title, OpenState, WindowFlags))
	{
		ImGui::End();
		return;
	}

	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
	//ImGui::BeginChild("ScrollingRegion");

	std::string Buffer;
	ImVec4 Color;
	//Logger::Log(std::string("LogData size: " + std::to_string(Logger::LogData.size())), LogAll);
	for (auto i = Logger::LogData.begin(); i != Logger::LogData.end(); i++)
	{
		if (i->Flags & ConsoleLogType)
		{
			Buffer = Logger::GetFlagString(i->Flags);
			if (Buffer == "[Info] ")
			{
				Color = ImVec4(0.945f, 0.945f, 0.945f, 1.0f); //White/Grey
			}
			else if (Buffer == "[Warning] ")
			{
				Color = ImVec4(0.756f, 0.611f, 0.000f, 1.0f); //Gold/Yellow
			}
			else if (Buffer == "[Lua] ")
			{
				Color = ImVec4(0.231f, 0.470f, 1.000f, 1.0f); //Light Blue (Info color in external console)
			}
			else if (Buffer == "[Json] ") 
			{
				Color = ImVec4(1.000f, 0.415f, 0.000f, 1.0f); //Light Orange
			}
			else if (Buffer == "[Error] ")
			{
				Color = ImVec4(0.772f, 0.058f, 0.121f, 1.0f); //Bright Red
			}
			else if (Buffer == "[Fatal Error] ")
			{
				Color = ImVec4(0.772f, 0.058f, 0.121f, 1.0f); //Bright Red
			}
			else if (Buffer == "[+] ")
			{
				Buffer == "[Undefined Log Type] ";
				Color = ImVec4(1.000f, 0.000f, 0.000f, 1.0f); //Pure Red (255,0,0)
			}
			else
			{

			}
			/*This code below is a crime againt humanity. Looks bad*/
			//Todo: Fix this mess below.
			ImGui::Text(Buffer.substr(0, 1).c_str());
			ImGui::SameLine();
			ImGui::TextColored(Color, Buffer.substr(1, Buffer.size() - 3).c_str());
			ImGui::SameLine();
			ImGui::Text(Buffer.substr(Buffer.size() - 2, 1).c_str());
			ImGui::SameLine();
			ImGui::Text(i->Message.c_str());
		}	
	}
	ImGui::EndChild();
	ImGui::End();
	Logger::Log("Console called End. Done drawing!", LogAll);
	/*Example code start*/


	/*ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	static ImGuiTextFilter filter;
	filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
	ImGui::PopStyleVar();
	ImGui::Separator();

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Clear")) ClearLog();
		ImGui::EndPopup();
	}

	// Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
	// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
	// You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
	// To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
	//     ImGuiListClipper clipper(Items.Size);
	//     while (clipper.Step())
	//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
	// However, note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
	// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
	// and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
	// If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	if (copy_to_clipboard)
		ImGui::LogToClipboard();
	ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
	for (int i = 0; i < Items.Size; i++)
	{
		const char* item = Items[i];
		if (!filter.PassFilter(item))
			continue;
		ImVec4 col = col_default_text;
		if (strstr(item, "[error]")) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
		else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_Text, col);
		ImGui::TextUnformatted(item);
		ImGui::PopStyleColor();
	}
	if (copy_to_clipboard)
		ImGui::LogFinish();
	if (ScrollToBottom)
		ImGui::SetScrollHereY(1.0f);
	ScrollToBottom = false;
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	// Command-line
	bool reclaim_focus = false;
	if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
	{
		char* s = InputBuf;
		Strtrim(s);
		if (s[0])
			ExecCommand(s);
		strcpy(s, "");
		reclaim_focus = true;
	}

	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus)
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget*/



	/*Example code end*/
}