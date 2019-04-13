#include "OverlayConsole.h"
#include "ScriptManager.h"

OverlayConsole::OverlayConsole(bool* _OpenState, std::string _Title)
{
	OpenState = _OpenState;
	Title = _Title;

	WindowFlags = 0;
	WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	//WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	//WindowFlags |= ImGuiWindowFlags_MenuBar;
	WindowFlags |= ImGuiWindowFlags_NoMove;
	//WindowFlags |= ImGuiWindowFlags_NoResize;
	WindowFlags |= ImGuiWindowFlags_NoCollapse;
	//WindowFlags |= ImGuiWindowFlags_NoNav;
	//WindowFlags |= ImGuiWindowFlags_NoBackground;
	//WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

OverlayConsole::~OverlayConsole()
{

}

void OverlayConsole::Draw()
{
	//auto StartTime = std::chrono::steady_clock::now();
	if (!*OpenState)
	{
		return;
	}

	ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));
	ImGui::SetNextWindowSize(ImVec2((float)(WindowRect.right - WindowRect.left) - 10.0f, 400.0f), ImGuiCond_Once);
	if (OverlayActive)
	{
		ImGui::SetNextWindowPos(ImVec2(0.0f, 22.0f)); //FontSize + 5.0f seems to work for menu bar alignment.
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f)); //If the main overlay 
		//isn't visible then place the console at the very top of the screen.
	}
	ImVec4* Colors = ImGui::GetStyle().Colors; //48 items
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, Colors[ImGuiCol_WindowBg]);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, Colors[ImGuiCol_WindowBg]);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, Colors[ImGuiCol_WindowBg]);
	if (!ImGui::Begin(Title.c_str(), OpenState, WindowFlags))
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
			if (Logger::LogData[i].Flags & LogNone || SimpleOutput)
			{
				ImGui::TextUnformatted(Logger::LogData[i].Message.c_str());
			}
			else
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
				ImGui::TextUnformatted(Logger::LogData[i].Message.c_str());
			}
			BufferCount++;
		}
		i--;
	}
	BufferCount = 0;

	//Auto-scrolls console output to bottom unless the user scrolls up.
	if (Autoscroll)
	{
		ImGui::SetScrollHereY(1.0f);
		/*if (ImGui::GetScrollY() >= abs(ImGui::GetContentRegionAvail().y) - 75.0f)
		{
			ImGui::SetScrollHereY();
		}*/
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();

	///ImGui::Separator();
	/*moneyl: Full credit goes to Elias Daler for the use of a stateless lambda and wrapper to pass a callback lambda to the InputText widget. I was having trouble implementing this, and his
	article here gave a solution: https://eliasdaler.github.io/using-imgui-with-sfml-pt2/ This method is preferred to having a separate callback function since it keeps the code in one place,
	and cleaner. He also described a general method of doing this for any widget which may be useful later on. Keep this in mind for future gui additions which might use it.*/
	//ReclaimFocus = false;
	if (InputTextLambdaWrapper("##LuaConsoleInput", &InputBuffer, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory, [&](ImGuiInputTextCallbackData* CallbackData)
	{
		//Callback lambda which handles up/down key presses
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
		CommandHistory.push_back(InputBuffer);
		Logger::Log(std::string(InputBuffer), LogLua);
		HistoryPosition = CommandHistory.size(); //Since pressing the up arrow key will subtract by one, the subtraction by one is not done here to insure the latest history entry isn't skipped.
		Scripts->RunStringAsScript(InputBuffer, "lua console command");
		InputBuffer.clear();
		ReclaimFocus = true;
	}
	ImGui::SameLine();
	ImGui::Checkbox("Auto scroll", &Autoscroll);
	ImGui::SameLine();
	ImGui::Checkbox("Simple output", &SimpleOutput);

	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (ReclaimFocus)
	{
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
		ReclaimFocus = false;
	}
	//ImGui::SetKeyboardFocusHere(-1);

	ImGui::End();
	ImGui::PopStyleColor(3);

	//auto EndTime = std::chrono::steady_clock::now();
	//auto TimeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count();
	//std::cout << "OverlayConsole::Draw() TimeElapsed = " << TimeElapsed << " ns\n";
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