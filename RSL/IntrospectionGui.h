#pragma once
#include "BaseGui.h"

class IntrospectionGui : public BaseGui
{
public:
	IntrospectionGui(std::string Title_) { Title = Title_; }
	~IntrospectionGui() = default;

	void Draw() override;
	void DrawPlayerIntrospectionGui(const char* Title);

    uint SavedTargetObjectHandle = 0;
};

