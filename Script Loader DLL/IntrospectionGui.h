#pragma once
#include "GeneralTweaksGui.h"

class IntrospectionGui
{
public:
	IntrospectionGui();
	~IntrospectionGui();

	void Initialize(bool* _OpenState);
	void Draw(const char* Title);
	void DrawPlayerIntrospectionGui(const char* Title);

	Player* PlayerPtr;

private:
	bool* OpenState;
};

