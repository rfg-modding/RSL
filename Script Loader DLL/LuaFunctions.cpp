#include "LuaFunctions.h"

namespace Lua
{
	Player* GetPlayer()
	{
		return Globals::PlayerPtr;
	}

	World* GetWorld()
	{
		return Globals::RfgWorldPtr;
	}

	hkpWorld* GetPhysicsWorld()
	{
		return Globals::hkpWorldPtr;
	}

	void LogModuleBase()
	{
		Logger::Log(std::string("Module base: " + std::to_string(Globals::ModuleBase)), LogInfo);
	}

    vector GetGravity()
    {
        if(Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr); //Returns a hkVector4f but as far as I can tell it's only the 3 values that matter here. Probably some SIMD shenanigans.
            return vector(Gravity->m_quad.m128_f32[0], Gravity->m_quad.m128_f32[1], Gravity->m_quad.m128_f32[2]);
        }
        return vector(0.0f);
    }

    void SetGravity(vector& NewGravity)
    {
        if (Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);
            Gravity->m_quad.m128_f32[0] = NewGravity.x;
            Gravity->m_quad.m128_f32[1] = NewGravity.y;
            Gravity->m_quad.m128_f32[2] = NewGravity.z;
        }
    }

    void SetGravity(float x, float y, float z)
    {
        if (Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);
            Gravity->m_quad.m128_f32[0] = x;
            Gravity->m_quad.m128_f32[1] = y;
            Gravity->m_quad.m128_f32[2] = z;
        }
    }

    void ResetGravity()
    {
        if (Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);
            Gravity->m_quad.m128_f32[0] = 0.0f;
            Gravity->m_quad.m128_f32[1] = -9.80f;
            Gravity->m_quad.m128_f32[2] = 0.0f;
        }
    }

    Object* GetObjectByName(std::string Name)
    {
        for(int i = 0; i < Globals::RfgWorldPtr->all_objects.Size(); i++)
        {
            if(Globals::RfgWorldPtr)
            {
                std::string IndexName(WorldGetObjectName(Globals::RfgWorldPtr, NULL, Globals::RfgWorldPtr->all_objects[i]));
                if (IndexName == Name)
                {
                    return Globals::RfgWorldPtr->all_objects[i];
                }
            }
        }
        return nullptr;
    }

    Object* GetObjectByHandle(uint Handle)
    {
        for (int i = 0; i < Globals::RfgWorldPtr->all_objects.Size(); i++)
        {
            if (Globals::RfgWorldPtr)
            {
                if(Globals::RfgWorldPtr->all_objects[i]->Handle == Handle)
                {
                    return Globals::RfgWorldPtr->all_objects[i];
                }
            }
        }
        return nullptr;
    }
}
