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
	//WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void OverlayConsole::Draw(const char* Title)
{
	ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));
	ImGui::SetNextWindowSize(ImVec2((float)(WindowRect.right - WindowRect.left) - 10.0f, 400.0f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImVec4* Colors = ImGui::GetStyle().Colors; //48 items
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, Colors[ImGuiCol_WindowBg]);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, Colors[ImGuiCol_WindowBg]);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, Colors[ImGuiCol_WindowBg]);
	if (!ImGui::Begin(Title, OpenState, WindowFlags))
	{
		ImGui::End();
		return;
	}

	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 2.0f));
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText

	std::string Buffer;
	ImVec4 Color;
	//Logger::Log(std::string("LogData size: " + std::to_string(Logger::LogData.size())), LogAll);
	int BufferStart = Logger::LogData.size() - 1 - BufferDisplayLength;
	if (BufferStart < 0)
	{
		BufferStart = 0;
	}
	for (size_t i = BufferStart; i < Logger::LogData.size() - 1; i++)
	{
		if (Logger::LogData[i].Flags & ConsoleLogType)
		{
			Buffer = Logger::GetFlagString(Logger::LogData[i].Flags);
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
				Buffer = "[Undefined Log Type] ";
				Color = ImVec4(1.000f, 0.000f, 0.000f, 1.0f); //Pure Red (255,0,0)
			}
			else
			{

			}

			ImGui::TextUnformatted(Buffer.substr(0, 1).c_str());
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, Color);
			ImGui::TextUnformatted(Buffer.substr(1, Buffer.size() - 3).c_str());
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::TextUnformatted(Buffer.substr(Buffer.size() - 2, 1).c_str());
			ImGui::SameLine();
			ImGui::TextUnformatted(Logger::LogData[i].Message.c_str());
		}	
	}
	//Auto-scrolls console output to bottom unless the user scrolls up.
	if (ImGui::GetScrollY() >= abs(ImGui::GetContentRegionAvail().y) - 25.0f)
	{
		ImGui::SetScrollHereY();
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();

	///ImGui::Separator();
	/*moneyl: Full credit goes to Elias Daler for the use of a stateless lambda and wrapper to pass a callback lambda to the InputText widget. I was having trouble implementing this, and his
	article here gave a solution: https://eliasdaler.github.io/using-imgui-with-sfml-pt2/ This method is preferred to having a separate callback function since it keeps the code in one place,
	and cleaner. He also described a general method of doing this for any widget which may be useful later on. Keep this in mind.*/
	bool ReclaimFocus = false;
	if (InputTextLambdaWrapper("##LuaConsoleInput", &InputBuffer, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory, [&](ImGuiInputTextCallbackData* CallbackData)
	{
		//Callback lambda which handles up/down keypresses
		if (CallbackData->EventFlag == ImGuiInputTextFlags_CallbackHistory)
		{
			if (CallbackData->EventKey == ImGuiKey_UpArrow)
			{
				if (HistoryPosition > 0)
				{
					HistoryPosition--;
				}
				CallbackData->DeleteChars(0, CallbackData->BufTextLen);
				CallbackData->InsertChars(0, CommandHistory[HistoryPosition].c_str());
			}
			else if (CallbackData->EventKey == ImGuiKey_DownArrow)
			{
				if (HistoryPosition < CommandHistory.size() - 1)
				{
					HistoryPosition++;
				}
				CallbackData->DeleteChars(0, CallbackData->BufTextLen);
				CallbackData->InsertChars(0, CommandHistory[HistoryPosition].c_str());
			}
		}
		return 0;
	}))
	{
		//This executes when the if statement returns true -> if the enter key is pressed.
		Scripts->RunStringAsScript(InputBuffer, "lua console command");
		CommandHistory.push_back(InputBuffer);
		HistoryPosition = CommandHistory.size() - 1;
		InputBuffer.clear();
		ReclaimFocus = true;
	}

	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (ReclaimFocus)
	{
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
	}

	ImGui::End();
	ImGui::PopStyleColor(3);
}

template<typename T>
inline bool OverlayConsole::InputTextLambdaWrapper(const char* Label, std::string* Buffer, ImGuiInputTextFlags Flags, T Callback, void* UserData)
{
	auto FreeCallback = [](ImGuiTextEditCallbackData* Data) 
	{
		auto& f = *static_cast<T*>(Data->UserData);
		return f(Data);
	};
	return ImGui::InputText(Label, Buffer, Flags, FreeCallback, &Callback);	
}