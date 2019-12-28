#include "LogWindow.h"

void LogWindow::Draw()
{
	//auto StartTime = std::chrono::steady_clock::now();
	if (!Visible)
	{
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(800.0f, 700.0f), ImGuiCond_Once);
	if (!ImGui::Begin(Title.c_str(), &Visible, WindowFlags))
	{
		ImGui::End();
		return;
	}

	ImGui::Checkbox("Auto scroll", &AutoScroll);
	ImGui::SameLine();

	static bool ShowAll = ConsoleLogType & LogAll ? true : false;
	static bool ShowInfo = ConsoleLogType & LogInfo ? true : false;
	static bool ShowWarning = ConsoleLogType & LogWarning ? true : false;
	static bool ShowError = ConsoleLogType & LogError ? true : false;
	static bool ShowFatalError = ConsoleLogType & LogFatalError ? true : false;
	static bool ShowLua = ConsoleLogType & LogLua ? true : false;
	static bool ShowJson = ConsoleLogType & LogJson ? true : false;

	//ImGui::PushItemWidth(225.0f);
	//ImGui::TextWrapped("Select which message types you wish to see in the logger below.");

	ImGui::Text("Filtering: ");
	ImGui::SameLine();
	ImGui::Checkbox("All", &ShowAll);
	if (!ShowAll)
	{
		ImGui::SameLine();
		ImGui::Checkbox("Info", &ShowInfo);
		ImGui::SameLine();
		ImGui::Checkbox("Warning", &ShowWarning);
		ImGui::SameLine();
		ImGui::Checkbox("Error", &ShowError);
		ImGui::SameLine();
		ImGui::Checkbox("Fatal Error", &ShowFatalError);
		ImGui::SameLine();
		ImGui::Checkbox("Lua", &ShowLua);
		ImGui::SameLine();
		ImGui::Checkbox("Json", &ShowJson);
		//ImGui::SameLine();
	}

	if (ShowAll)
	{
		ConsoleLogType = ConsoleLogType | LogAll;
	}
	else
	{
		ConsoleLogType = 0;
		if (ShowInfo)
		{
			ConsoleLogType = ConsoleLogType | LogInfo;
		}
		if (ShowWarning)
		{
			ConsoleLogType = ConsoleLogType | LogWarning;
		}
		if (ShowError)
		{
			ConsoleLogType = ConsoleLogType | LogError;
		}
		if (ShowFatalError)
		{
			ConsoleLogType = ConsoleLogType | LogFatalError;
		}
		if (ShowLua)
		{
			ConsoleLogType = ConsoleLogType | LogLua;
		}
		if (ShowJson)
		{
			ConsoleLogType = ConsoleLogType | LogJson;
		}
	}

	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 2.0f));
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::BeginChild("ScrollingRegion", ImVec2(0,0), true, ImGuiWindowFlags_HorizontalScrollbar);// , ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText

	BufferCount = 0;
	int i = BufferDisplayLength - 1;
	if (i >= Logger::LogCache.size())
	{
		i = Logger::LogCache.size() - 1;
	}
	while (i >= 0 && BufferCount < BufferDisplayLength)
	{
		if (Logger::LogCache[i].Flags & ConsoleLogType)
		{
			ImGui::TextUnformatted("[");
			ImGui::SameLine();
			if (Logger::LogCache[i].Flags & LogInfo)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.945f, 0.945f, 0.945f, 1.0f));
				ImGui::TextUnformatted("Info");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogCache[i].Flags & LogWarning)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.756f, 0.611f, 0.000f, 1.0f));
				ImGui::TextUnformatted("Warning");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogCache[i].Flags & LogLua)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.231f, 0.470f, 1.000f, 1.0f));
				ImGui::TextUnformatted("Lua");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogCache[i].Flags & LogJson)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.415f, 0.000f, 1.0f));
				ImGui::TextUnformatted("Json");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogCache[i].Flags & LogError)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.772f, 0.058f, 0.121f, 1.0f));
				ImGui::TextUnformatted("Error");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogCache[i].Flags & LogFatalError)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.772f, 0.058f, 0.121f, 1.0f));
				ImGui::TextUnformatted("Fatal Error");
				ImGui::PopStyleColor();
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.0f));
				ImGui::TextUnformatted("Undefined Message Type");
				ImGui::PopStyleColor();
			}
			ImGui::SameLine();
			ImGui::TextUnformatted("] ");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(ImGui::GetWindowSize().x - 20.0f);
			ImGui::TextWrapped(Logger::LogCache[i].Message.c_str());
			BufferCount++;
		}
		i--;
	}
	BufferCount = 0;

	//Auto-scrolls console output to bottom unless the user scrolls up.
	if (AutoScroll)
	{
		if (ImGui::GetScrollMaxY() - ImGui::GetScrollY() < 50.0f)
		{
			ImGui::SetScrollHereY(1.0f);
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::End();

	/*auto EndTime = std::chrono::steady_clock::now();
	auto TimeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count();
	std::cout << "OverlayConsole::Draw() TimeElapsed = " << TimeElapsed << " ns\n";*/
}