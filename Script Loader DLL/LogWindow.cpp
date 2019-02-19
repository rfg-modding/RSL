#include "LogWindow.h"
#include "ScriptManager.h"

LogWindow::LogWindow()
{

}

LogWindow::~LogWindow()
{

}

void LogWindow::Initialize(bool * _OpenState)
{
	OpenState = _OpenState;

	WindowFlags = 0;
	//WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	//WindowFlags |= ImGuiWindowFlags_MenuBar;
	//WindowFlags |= ImGuiWindowFlags_NoMove;
	//WindowFlags |= ImGuiWindowFlags_NoResize;
	//WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void LogWindow::Draw(const char * Title)
{
	//auto StartTime = std::chrono::steady_clock::now();
	if (!*OpenState)
	{
		return;
	}

	ImGui::SetNextWindowSize(ImVec2(600.0f, 500.0f), ImGuiCond_Once);
	if (!ImGui::Begin(Title, OpenState, WindowFlags))
	{
		ImGui::End();
		return;
	}

	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 2.0f));
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText

	BufferCount = 0;
	int i = BufferDisplayLength - 1;
	if (i >= Logger::LogData.size())
	{
		i = Logger::LogData.size() - 1;
	}
	while (i >= 0 && BufferCount < BufferDisplayLength)
	{
		if (Logger::LogData[i].Flags & ConsoleLogType)
		{
			ImGui::TextUnformatted("[");
			ImGui::SameLine();
			if (Logger::LogData[i].Flags & LogInfo)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.945f, 0.945f, 0.945f, 1.0f));
				ImGui::TextUnformatted("Info");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogData[i].Flags & LogWarning)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.756f, 0.611f, 0.000f, 1.0f));
				ImGui::TextUnformatted("Warning");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogData[i].Flags & LogLua)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.231f, 0.470f, 1.000f, 1.0f));
				ImGui::TextUnformatted("Lua");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogData[i].Flags & LogJson)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.415f, 0.000f, 1.0f));
				ImGui::TextUnformatted("Json");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogData[i].Flags & LogError)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.772f, 0.058f, 0.121f, 1.0f));
				ImGui::TextUnformatted("Error");
				ImGui::PopStyleColor();
			}
			else if (Logger::LogData[i].Flags & LogFatalError)
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
			ImGui::PushItemWidth(ImGui::GetWindowSize().x - 20.0f);
			ImGui::TextWrapped(Logger::LogData[i].Message.c_str());
			BufferCount++;
		}
		i--;
	}
	BufferCount = 0;

	//Auto-scrolls console output to bottom unless the user scrolls up.
	if (ImGui::GetScrollY() >= abs(ImGui::GetContentRegionAvail().y) - 75.0f)
	{
		ImGui::SetScrollHereY();
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::End();

	/*auto EndTime = std::chrono::steady_clock::now();
	auto TimeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count();
	std::cout << "OverlayConsole::Draw() TimeElapsed = " << TimeElapsed << " ns\n";*/
}