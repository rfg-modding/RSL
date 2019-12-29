#pragma once
#include "BaseGui.h"

class PhysicsGui : public BaseGui
{
public:
	PhysicsGui(std::string Title_) { Title = Title_; };
	~PhysicsGui() = default;

	void Draw() override;

	hkVector4f* CurrentGravity = nullptr;
	hkVector4f CustomGravityVector{ 0.0f, 0.0f, 0.0f,  0.0f};
	hkVector4f DefaultGravityVector{0.0f, 0.0f, 0.0f,  0.0f};
};