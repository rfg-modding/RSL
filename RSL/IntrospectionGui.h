#pragma once
#include "BaseGui.h"

class IntrospectionGui : public BaseGui
{
public:
	IntrospectionGui(std::string Title_) { Title = Title_; }
	~IntrospectionGui() = default;

	void Draw() override;
	void DrawPlayerIntrospectionGui(const char* Title);

    static std::string GetObjectTypeString(char ObjectType);
    static std::string GetObjectSubTypeString(char ObjectSubType);

	ImGuiWindowFlags WindowFlags = 0;

    uint SavedTargetObjectHandle = 0;
};

