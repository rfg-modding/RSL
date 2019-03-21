#include "LuaFunctions.h"


namespace Lua
{
	Player* GetPlayer()
	{
		if (GlobalPlayerPtr)
		{
			return (Player*)GlobalPlayerPtr;
		}
		else
		{
			return nullptr;
		}
	}
}