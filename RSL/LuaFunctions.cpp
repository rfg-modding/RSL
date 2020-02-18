#include "LuaFunctions.h"
#include "IScriptManager.h"

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
        Logger::Log("Module base: {}", Globals::ModuleBase);
	}

    vector GetGravity()
    {
        if(Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr); //Returns a hkVector4f but as far as I can tell it's only the 3 values that matter here. Probably some SIMD shenanigans.
            return vector(Gravity->m_quad.m128_f32[0], Gravity->m_quad.m128_f32[1], Gravity->m_quad.m128_f32[2]);
        }
        return vector(0.0f);
    }

    void SetGravity(vector& NewGravity)
    {
        if (Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);
            Gravity->m_quad.m128_f32[0] = NewGravity.x;
            Gravity->m_quad.m128_f32[1] = NewGravity.y;
            Gravity->m_quad.m128_f32[2] = NewGravity.z;
        }
    }

    void SetGravity(float x, float y, float z)
    {
        if (Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);
            Gravity->m_quad.m128_f32[0] = x;
            Gravity->m_quad.m128_f32[1] = y;
            Gravity->m_quad.m128_f32[2] = z;
        }
    }

    void ResetGravity()
    {
        if (Globals::hkpWorldPtr)
        {
            hkVector4f* Gravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, nullptr);
            Gravity->m_quad.m128_f32[0] = 0.0f;
            Gravity->m_quad.m128_f32[1] = -9.80f;
            Gravity->m_quad.m128_f32[2] = 0.0f;
        }
    }

    Object* GetObjectByName(std::string Name)
    {
        if (Globals::RfgWorldPtr)
        {
            for (int i = 0; i < Globals::RfgWorldPtr->all_objects.Size(); i++)
            {
                if (Globals::RfgWorldPtr)
                {
                    std::string IndexName(rfg::WorldGetObjectName(Globals::RfgWorldPtr, NULL, Globals::RfgWorldPtr->all_objects[i]));
                    if (IndexName == Name)
                    {
                        return Globals::RfgWorldPtr->all_objects[i];
                    }
                }
            }
        }
        return nullptr;
    }

    Object* GetObjectByHandle(uint Handle)
    {
        if(Globals::RfgWorldPtr)
        {
            for (int i = 0; i < Globals::RfgWorldPtr->all_objects.Size(); i++)
            {
                if (Globals::RfgWorldPtr)
                {
                    if (Globals::RfgWorldPtr->all_objects[i]->Handle == Handle)
                    {
                        return Globals::RfgWorldPtr->all_objects[i];
                    }
                }
            }
        }
        return nullptr;
    }

    explosion_info* GetExplosionInfo(std::string Name)
    {
        if(Globals::ExplosionInfos.Initialized())
        {
            for(int i = 0; i < Globals::ExplosionInfos.Size(); i++)
            {
                //Todo: Check if this works without the temporary string. Use a const char* comparison func.
                std::string IndexName(Globals::ExplosionInfos[i].m_name);
                if(IndexName == Name)
                {
                    return const_cast<explosion_info*>(&Globals::ExplosionInfos[i]);
                }
            }
        }
        return nullptr;
    }

    //Tries to find the specified effect_info in
    //Globals::EffectInfos. Ruturns nullptr if not found.
    effect_info* GetEffectInfo(string Name)
	{
        if (!Globals::EffectInfos.Initialized())
            return nullptr;

        for(int i = 0; i < Globals::EffectInfos.Size(); i++)
        {
            string IndexName(Globals::EffectInfos[i].name);
            if(IndexName == Name)
                return &Globals::EffectInfos[i];
        }

        return nullptr;
	}

    vehicle_info* GetVehicleInfo(string Name)
    {
        if (!Globals::VehicleInfos)
            return nullptr;

        for (int i = 0; i < Globals::VehicleInfos->Size(); i++)
        {
            string IndexName(Globals::VehicleInfos->data[i].name);
            if (IndexName == Name)
                return &Globals::VehicleInfos->data[i];
        }

        return nullptr;
    }

    //Tries to find the specified effect_info handle in
    //Globals::EffectInfos. Ruturns 0xFFFFFFFF if not found.
    uint GetEffectHandle(string Name)
	{
        if (!Globals::EffectInfos.Initialized())
            return 0xFFFFFFFF;

        for (int i = 0; i < Globals::EffectInfos.Size(); i++)
        {
            string IndexName(Globals::EffectInfos[i].name);
            if (IndexName == Name)
            {
                return i;//return Globals::EffectInfos[i].visual_handle; //return i; //
            }
        }
        return 0xFFFFFFFF;
	}

    std::vector<fmt::basic_format_arg<fmt::format_context>> GenerateFmtListFromSolVariadicArgs(const sol::variadic_args& Args)
    {
        std::vector<fmt::basic_format_arg<fmt::format_context>> FmtArgsList;
        for (auto& Arg : Args)
        {
            switch (Arg.get_type())
            {
            case sol::type::none:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            case sol::type::lua_nil: //covers lua_nil and nil
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("nil"));
                break;
            case sol::type::string:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>(Arg.get<const char*>()));
                break;
            case sol::type::number:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>(Arg.get<float>()));
                break;
            case sol::type::thread:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            case sol::type::boolean:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>(Arg.get<bool>()));
                break;
            case sol::type::function:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            case sol::type::userdata:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            case sol::type::lightuserdata:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            case sol::type::table:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            case sol::type::poly:
                FmtArgsList.push_back(fmt::internal::make_arg<fmt::format_context>("<unsupported format type>"));
                break;
            default:;
            }

        }
        return FmtArgsList;
    }

    //Todo: Try to support more unsupported types if possible
    void Log(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogInfo);
    }

    void LogNone(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogNone);
    }

    void LogInfo(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogInfo);
    }

    void LogWarning(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogWarning);
    }

    void LogError(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogError);
    }

    void LogFatalError(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogFatalError);
    }

    void LogLua(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogLua);
    }

    void LogJson(std::string Fmt, sol::variadic_args Args)
    {
        auto ArgsList = GenerateFmtListFromSolVariadicArgs(Args);
        Logger::LogInternal(fmt::vformat(Fmt, fmt::basic_format_args<fmt::format_context>(ArgsList.data(), static_cast<unsigned>(ArgsList.size()))), LogType::LogJson);
    }

    uint RfgStringHashWrapper(std::string Key)
    {
        return rfg::string_hash(Key.c_str(), Key.length());
    }

    bool RfgMessageBoxCallbackFunction(int mbox_handle, int selection_index, msgbox_choice choice)
    {
        //Script manager should be ready for use by the time this is first called
        static auto Scripts = IocContainer->resolve<IScriptManager>();
        if(Scripts)
        {
            auto& MessageBoxCallbacks = Scripts->GetMessageBoxCallbacks();
            if(MessageBoxCallbacks.count(mbox_handle) == 1)
            {
                sol::function& Callback = const_cast<sol::function&>(MessageBoxCallbacks.at(mbox_handle));
                sol::table CallbackInfo = Scripts->GetLuaState().create_table();
                CallbackInfo["SelectionIndex"] = selection_index;
                CallbackInfo["Choice"] = choice;
                sol::protected_function_result Result = Callback(CallbackInfo);
                if (!Result.valid())
                {
                    sol::error Error = Result;
                    std::string What(Error.what());
                    Logger::LogError("MessageBox callback encountered an error! Message: {}", What);
                }
                MessageBoxCallbacks.erase(mbox_handle);
            }
        }
        return true;
    }
}
