#include "ApiTables.h"
#include "Functions.h"
#include "LuaFunctions.h"
#include "CameraWrapper.h"
#include "ScriptManager.h"

void Lua::BindApiFunctions(sol::state& LuaStateRef)
{
    LuaStateRef["print"] = sol::nil;
    LuaStateRef["ToString"] = LuaStateRef.get<sol::function>("tostring");

    auto RslTable = LuaStateRef["rsl"].get_or_create<sol::table>();
    RslTable["GetVersion"] = Globals::GetScriptLoaderVersion;
    RslTable["LogModuleBase"] = Lua::LogModuleBase;
    RslTable["BuildDate"] = RSL_BUILD_DATE;

    RslTable["Log"] = Lua::Log;
    RslTable["LogNone"] = Lua::LogNone;
    RslTable["LogInfo"] = Lua::LogInfo;
    RslTable["LogWarning"] = Lua::LogWarning;
    RslTable["LogError"] = Lua::LogError;
    RslTable["LogFatalError"] = Lua::LogFatalError;
    RslTable["LogLua"] = Lua::LogLua;
    RslTable["LogJson"] = Lua::LogJson;

    RslTable.set_function("CharArrayToString", sol::overload(
        [](char* Array, int Size) { return Globals::CharArrayToString(Array, Size); },
        [](const char* Array, int Size) { return Globals::CharArrayToString(Array, Size); }
    ));

    auto RfgTable = LuaStateRef["rfg"].get_or_create<sol::table>();
    RfgTable["HideHud"] = HideHud;
    RfgTable["HideFog"] = HideFog;
    RfgTable["ToggleFog"] = ToggleFog;
    RfgTable["ToggleHud"] = ToggleHud;
    RfgTable["SetFarClip"] = GameRenderSetFarClipDistance;
    RfgTable["GetFarClip"] = GameRenderGetFarClipDistance;
    RfgTable["SetAlertLevel"] = GsmSetAlertLevel;
    RfgTable["GetAlertLevel"] = GsmGetAlertLevel;
    RfgTable.set_function("TeleportHuman", sol::overload(
        [](Human* Target, vector Position, matrix Orientation)
        {
            if (!Target) throw std::exception("[TeleportHuman]: The target passed to TeleportHuman is nil!");
            if (Target->ObjectType != OT_HUMAN) throw std::exception(fmt::format("The target passed to TeleportHuman is not a human object! It's a {} object.", Util::RFG::GetObjectTypeString(Target->ObjectType)).c_str());
            HumanTeleportUnsafe(Target, Position, Orientation);
        },
        [](Human* Target, vector Position)
        {
            if (!Target) throw std::exception("[TeleportHuman]: The target passed to TeleportHuman is nil!");
            if (Target->ObjectType != OT_HUMAN) throw std::exception(fmt::format("The target passed to TeleportHuman is not a human object! It's a {} object.", Util::RFG::GetObjectTypeString(Target->ObjectType)).c_str());
            HumanTeleportUnsafe(Target, Position, Target->Orientation);
        }
    ));
    RfgTable.set_function("GetObject", sol::overload(
        Lua::GetObjectByName,
        Lua::GetObjectByHandle
    ));

    RfgTable["GetGravity"] = Lua::GetGravity;
    RfgTable.set_function("SetGravity", sol::overload(
        [](vector& NewGravity) {Lua::SetGravity(NewGravity); },
        [](float x, float y, float z) {Lua::SetGravity(x, y, z); }));
    RfgTable["ResetGravity"] = Lua::ResetGravity;

    RfgTable["HavokBodyGetPointer"] = HavokBodyGetPointer;
    RfgTable.set_function("ApplyLinearImpulse", sol::overload(HavokBodyApplyLinearImpulseA, HavokBodyApplyLinearImpulseB));

    RfgTable.set_function("TeleportPlayer", sol::overload(
        [](vector Position, matrix Orientation) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Orientation); },
        [](vector Position) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Globals::PlayerPtr->Orientation); },
        [](float x, float y, float z) {HumanTeleportUnsafe(Globals::PlayerPtr, vector(x, y, z), Globals::PlayerPtr->Orientation); }
    ));

    RfgTable["GetVersion"] = KeenGetBuildVersionString;
    RfgTable["StringHash"] = Lua::RfgStringHashWrapper;

    RfgTable.set_function("ExplosionCreate", sol::overload( //Todo: Maybe rename this to SpawnExplosion. //Todo: Add overload that just takes preset name and position.
        [](explosion_info* Info, Object* Source, Object* Owner, vector* Position, matrix* Orientation, vector* Direction)// , weapon_info* WeaponInfo) //Todo: Add WeaponInfo once that's bound to lua
        {
            if (!Info) throw std::exception("[ExplosionCreate]: Info argument is nil!");
            //if (!Source) throw std::exception("[ExplosionCreate]: Source argument is nil!"); //Should not crash when passed nil
            //if (!Owner) throw std::exception("[ExplosionCreate]: Owner argument is nil!"); //Should not crash when passed nil
            if (!Position) throw std::exception("[ExplosionCreate]: Position argument is nil!");
            if (!Orientation) throw std::exception("[ExplosionCreate]: Orientation argument is nil!");
            //if (!Direction) throw std::exception("[ExplosionCreate]: Direction argument is nil!"); //Should not crash when passed nil
            ExplosionCreate(Info, Source, Owner, Position, Orientation, Direction, nullptr, false);
        }, //Todo: remember to replace this nullptr with WeaponInfo once bound
        [](explosion_info* Info, vector* Position)
        {
            if (!Info) throw std::exception("[ExplosionCreate]: Info argument is nil!");
            if (!Position) throw std::exception("[ExplosionCreate]: Position argument is nil!");
            ExplosionCreate(Info, nullptr, nullptr, Position, new matrix(0.0f), new vector(0.0f, 1.0f, 0.0f), nullptr, false);
        },
            [](explosion_info* Info, float x, float y, float z)
        {
            if (!Info) throw std::exception("[ExplosionCreate]: Info argument is nil!");
            vector Position(x, y, z);
            ExplosionCreate(Info, nullptr, nullptr, &Position, new matrix(0.0f), new vector(0.0f, 1.0f, 0.0f), nullptr, false);
        }
    ));
    RfgTable["GetExplosionInfo"] = Lua::GetExplosionInfo;

    RfgTable.set_function("AddUiMessage", sol::overload(
        [](const char* Message, float DisplayTime, bool UseSecondaryAnim, bool ForceRedisplay)
        {
            ui_add_secondary_message(Util::Widen(Message).c_str(), DisplayTime, UseSecondaryAnim, ForceRedisplay);
        },
        [](const char* Message, float DisplayTime, bool UseSecondaryAnim)
        {
            ui_add_secondary_message(Util::Widen(Message).c_str(), DisplayTime, UseSecondaryAnim, false);
        },
            [](const char* Message, float DisplayTime)
        {
            ui_add_secondary_message(Util::Widen(Message).c_str(), DisplayTime, false, false);
        },
            [](const char* Message)
        {
            ui_add_secondary_message(Util::Widen(Message).c_str(), 3.0f, false, false);
    }));

    RfgTable.set_function("AddUserMessage", sol::overload(
        [](std::string Text, float PosX, float PosY, bool Outlined, float Lifespan, hud_user_message_types Type)->hud_message_handle
        {
            return ui_add_user_message(Util::Widen(Text).c_str(), Type, PosX, PosY, Outlined, Lifespan);
        }
    ));
    RfgTable.set_function("ChangeUserMessage", sol::overload(
        [](hud_message_handle Handle, const char* NewText)->hud_message_handle
        {
            return hud_message_change_user(Handle, NewText);
        }
    ));
    RfgTable.set_function("RemoveUserMessage", sol::overload(
        [](hud_message_handle Handle)
        {
            hud_message_remove_user(Handle);
        }
    ));
    RfgTable.set_function("AddMessageBox", sol::overload(
        [](msgbox_type Type, const char* Title, const char* Description)->int
        {
            if (Util::ContainsChar(Title, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box titles."); }
            if (Util::ContainsChar(Description, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box descriptions."); }
            return ui_add_msgbox(Type, Title, Description, nullptr, false, false, nullptr, nullptr, false);
        },
        [&](msgbox_type Type, const char* Title, const char* Description, sol::function CallbackFunc)->int
        {
            if (Util::ContainsChar(Title, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box titles."); }
            if (Util::ContainsChar(Description, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box descriptions."); }

            int Handle = ui_add_msgbox(Type, Title, Description, Lua::RfgMessageBoxCallbackFunction, false, false, nullptr, nullptr, false);
            Globals::Scripts->MessageBoxCallbacks.insert_or_assign(Handle, CallbackFunc);
            return Handle;
        },
        [&](msgbox_type Type, const char* Title, const char* Description, sol::function CallbackFunc, const char* Button1Override, const char* Button2Override)->int
        {
            if (Util::ContainsChar(Title, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box titles."); }
            if (Util::ContainsChar(Description, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box descriptions."); }

            int Handle = ui_add_msgbox(Type, Title, Description, Lua::RfgMessageBoxCallbackFunction, false, false, Button1Override, Button2Override, false);
            Globals::Scripts->MessageBoxCallbacks.insert_or_assign(Handle, CallbackFunc);
            return Handle;
        }
    ));
    RfgTable.set_function("HumanFireIgnite", sol::overload(
        [](Human* Target, Human* Killer)
        {
            //if (!Target) { throw std::exception("Target is nil!"); }
            //if (!Killer) { throw std::exception("Killer is nil!"); }
            human_fire_ignite(Target, Killer);
    }));
    RfgTable.set_function("HumanFireStop", human_fire_stop);

    RfgTable.set_function("HavokBodyApplyLinearImpulse", sol::overload(
        [](uint Handle, vector& Impulse)
        {
            HavokBodyApplyLinearImpulseB(Handle, Impulse);
    }));

    RfgTable.set_function("HavokBodyApplyPointImpulse", sol::overload(
        [](uint Handle, vector& Impulse, vector& Position)
        {
            havok_body_apply_point_impulse(Handle, Impulse, Position);
    }));

    RfgTable.set_function("HavokBodySetPos", HavokBodySetPosition);
    RfgTable.set_function("HavokBodySetPosOrient", HavokBodySetPositionAndOrient);

    RfgTable.set_function("HavokBodyGetPosOrient", HavokBodyGetPositionAndOrient);

    RfgTable.set_function("HavokBodyForceActivate", havok_body_force_activate);
    RfgTable.set_function("HavokBodySetMovable", havok_body_set_movable);
    RfgTable.set_function("HavokBodyGetMass", havok_body_get_mass);

    RfgTable.set_function("GetLookDirection", []()->vector
        {
            if (!Globals::Camera) return vector(0.0f);
            if (!Globals::Camera->GameData) return vector(0.0f);
            return vector(Globals::Camera->GameData->real_orient.fvec);
    });

    RfgTable["ObjectiveHighlightAdd"] = objective_highlight_add;
    RfgTable["ObjectiveHighlightRemove"] = objective_highlight_remove;
    RfgTable["ObjectiveHighlightRemoveAll"] = objective_highlight_remove_all;

    RfgTable.set_function("RegisterEvent", sol::overload(
        [&](std::string EventTypeName, sol::function EventFunction, std::string EventName)
        {
            Globals::Scripts->RegisterEvent(EventTypeName, EventFunction, EventName);
        },
        [&](std::string EventTypeName, sol::function EventFunction)
        {
            Globals::Scripts->RegisterEvent(EventTypeName, EventFunction);
        }
    ));
}
