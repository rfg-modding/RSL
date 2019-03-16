#pragma once
#include "BaseGui.h"

class IntrospectionGui : public BaseGui
{
public:
	IntrospectionGui(bool* _OpenState, std::string _Title);
	~IntrospectionGui();

	void Draw();
	void DrawPlayerIntrospectionGui(const char* Title);

	ImGuiWindowFlags WindowFlags = 0;
};

