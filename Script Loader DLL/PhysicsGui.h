#pragma once
#include "BaseGui.h"

class PhysicsGui : public BaseGui
{
public:
	PhysicsGui(bool* OpenState_, std::string Title_) { OpenState = OpenState_; Title = Title_; };
	~PhysicsGui() = default;

	void Draw() override;

	bool UseCustomPhysicsTimestepMultiplier = false;
	float CustomPhysicsTimeStepMultiplier = 1.0f;

	hkVector4f* CurrentGravity = nullptr;
	hkVector4f CustomGravityVector{ 0.0f, 0.0f, 0.0f,  0.0f};
	hkVector4f DefaultGravityVector{0.0f, 0.0f, 0.0f,  0.0f};
};