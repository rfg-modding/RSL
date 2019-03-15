#pragma once
#include "Functions.h"

class BaseGui
{
public:
	virtual ~BaseGui() {};
	virtual void Draw(const char* Title) = 0;
	
	Player* PlayerPtr = nullptr;

protected:
	bool* OpenState = nullptr;
};