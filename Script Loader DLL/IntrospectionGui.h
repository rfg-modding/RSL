#pragma once
#include "BaseGui.h"

class IntrospectionGui : public BaseGui
{
public:
	IntrospectionGui(bool* OpenState_, std::string Title_) { OpenState = OpenState_; Title = Title_; }
	~IntrospectionGui() = default;

	void Draw() override;
	void DrawPlayerIntrospectionGui(const char* Title);

	ImGuiWindowFlags WindowFlags = 0;
};

