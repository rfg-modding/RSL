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
}

void OverlayConsole::Draw(const char * Title)
{
	if (!ImGui::Begin(Title, OpenState))
	{
		ImGui::End();
		return;
	}

	ImGui::End();
}
