#pragma once
#include "BaseGui.h"

class IntrospectionGui
{
public:
	IntrospectionGui();
	~IntrospectionGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);
	void DrawPlayerIntrospectionGui(const char* Title);

	ImGuiWindowFlags WindowFlags = 0;
	Player* PlayerPtr = nullptr;

private:
	bool* OpenState = nullptr;
};

