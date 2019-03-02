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

	ImGui::SetNextWindowSize(ImVec2(800.0f, 700.0f), ImGuiCond_Once);
	if (!ImGui::Begin(Title, OpenState, WindowFlags))
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
	if (AutoScroll)
	{
		ImGui::SetScrollHereY(1.0f);
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::End();

	/*auto EndTime = std::chrono::steady_clock::now();
	auto TimeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count();
	std::cout << "OverlayConsole::Draw() TimeElapsed = " << TimeElapsed << " ns\n";*/
}