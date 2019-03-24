#pragma once
#include "BaseGui.h"
class PhysicsGui :
	public BaseGui
{
public:
	PhysicsGui(bool* _OpenState, std::string _Title);
	~PhysicsGui();

	void Draw();

	bool UseCustomPhysicsTimestepMultiplier = false;
	float CustomPhysicsTimeStepMultiplier = 1.0f;

	hkVector4f* CurrentGravity;
	hkVector4f CustomGravityVector;
	hkVector4f DefaultGravityVector;
};