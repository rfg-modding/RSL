#include "ApiTables.h"
#include "Functions.h"
#include "LuaFunctions.h"
#include "IScriptManager.h"
#include "ICameraManager.h"

//Todo: Split this into multiple functions & files, organize by function type / area. This is too large for one function
void Lua::BindApiFunctions(sol::state& LuaStateRef)
{
#if LUA_ENABLED
    auto ScriptManager = IocContainer->resolve<IScriptManager>();

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
    RfgTable["HideHud"] = rfg::HideHud;
    RfgTable["HideFog"] = rfg::HideFog;
    RfgTable["ToggleFog"] = rfg::ToggleFog;
    RfgTable["ToggleHud"] = rfg::ToggleHud;
    RfgTable["SetFarClip"] = rfg::GameRenderSetFarClipDistance;
    RfgTable["GetFarClip"] = rfg::GameRenderGetFarClipDistance;
    RfgTable["SetHighLodFarClip"] = [](float highLodFarClip)
    {
        static auto Camera = IocContainer->resolve<ICameraManager>();
        *Camera->HighLodFarClipDistance = highLodFarClip;
    };
    RfgTable["GetHighLodFarClip"] = [](float highLodFarClip)
    {
        static auto Camera = IocContainer->resolve<ICameraManager>();
        return *Camera->HighLodFarClipDistance;
    };

    RfgTable["SetAlertLevel"] = rfg::GsmSetAlertLevel;
    RfgTable["GetAlertLevel"] = rfg::GsmGetAlertLevel;
    RfgTable.set_function("TeleportHuman", sol::overload(
        [](Human* Target, vector Position, matrix Orientation)
        {
            if (!Target) throw std::exception("[TeleportHuman]: The target passed to TeleportHuman is nil!");
            if (Target->ObjectType != OT_HUMAN) throw std::exception(fmt::format("The target passed to TeleportHuman is not a human object! It's a {} object.", Util::RFG::GetObjectTypeString(Target->ObjectType)).c_str());
            rfg::HumanTeleportUnsafe(Target, Position, Orientation);
        },
        [](Human* Target, vector Position)
        {
            if (!Target) throw std::exception("[TeleportHuman]: The target passed to TeleportHuman is nil!");
            if (Target->ObjectType != OT_HUMAN) throw std::exception(fmt::format("The target passed to TeleportHuman is not a human object! It's a {} object.", Util::RFG::GetObjectTypeString(Target->ObjectType)).c_str());
            rfg::HumanTeleportUnsafe(Target, Position, Target->Orientation);
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

    RfgTable["HavokBodyGetPointer"] = rfg::HavokBodyGetPointer;
    RfgTable.set_function("ApplyLinearImpulse", sol::overload(rfg::HavokBodyApplyLinearImpulseA, rfg::HavokBodyApplyLinearImpulseB));

    RfgTable.set_function("TeleportPlayer", sol::overload(
        [](vector Position, matrix Orientation) { rfg::HumanTeleportUnsafe(Globals::PlayerPtr, Position, Orientation); },
        [](vector Position) { rfg::HumanTeleportUnsafe(Globals::PlayerPtr, Position, Globals::PlayerPtr->Orientation); },
        [](float x, float y, float z) { rfg::HumanTeleportUnsafe(Globals::PlayerPtr, vector(x, y, z), Globals::PlayerPtr->Orientation); }
    ));

    RfgTable["GetVersion"] = rfg::KeenGetBuildVersionString;
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
            rfg::ExplosionCreate(Info, Source, Owner, Position, Orientation, Direction, nullptr, false);
        }, //Todo: remember to replace this nullptr with WeaponInfo once bound
        [](explosion_info* Info, vector* Position)
        {
            if (!Info) throw std::exception("[ExplosionCreate]: Info argument is nil!");
            if (!Position) throw std::exception("[ExplosionCreate]: Position argument is nil!");
            rfg::ExplosionCreate(Info, nullptr, nullptr, Position, new matrix(0.0f), new vector(0.0f, 1.0f, 0.0f), nullptr, false);
        },
            [](explosion_info* Info, float x, float y, float z)
        {
            if (!Info) throw std::exception("[ExplosionCreate]: Info argument is nil!");
            vector Position(x, y, z);
            rfg::ExplosionCreate(Info, nullptr, nullptr, &Position, new matrix(0.0f), new vector(0.0f, 1.0f, 0.0f), nullptr, false);
        }
    ));
    RfgTable["GetExplosionInfo"] = Lua::GetExplosionInfo;

    RfgTable.set_function("AddUiMessage", sol::overload(
        [](const char* Message, float DisplayTime, bool UseSecondaryAnim, bool ForceRedisplay)
        {
            rfg::ui_add_secondary_message(Util::Widen(Message).c_str(), DisplayTime, UseSecondaryAnim, ForceRedisplay);
        },
        [](const char* Message, float DisplayTime, bool UseSecondaryAnim)
        {
            rfg::ui_add_secondary_message(Util::Widen(Message).c_str(), DisplayTime, UseSecondaryAnim, false);
        },
        [](const char* Message, float DisplayTime)
        {
            rfg::ui_add_secondary_message(Util::Widen(Message).c_str(), DisplayTime, false, false);
        },
        [](const char* Message)
        {
            rfg::ui_add_secondary_message(Util::Widen(Message).c_str(), 3.0f, false, false);
        }
    ));

    RfgTable.set_function("AddUserMessage", sol::overload(
        [](std::string Text, float PosX, float PosY, bool Outlined, float Lifespan, hud_user_message_types Type)->hud_message_handle
        {
            return rfg::ui_add_user_message(Util::Widen(Text).c_str(), Type, PosX, PosY, Outlined, Lifespan);
        }
    ));
    RfgTable.set_function("ChangeUserMessage", sol::overload(
        [](hud_message_handle Handle, const char* NewText)->hud_message_handle
        {
            return rfg::hud_message_change_user(Handle, NewText);
        }
    ));
    RfgTable.set_function("RemoveUserMessage", sol::overload(
        [](hud_message_handle Handle)
        {
            rfg::hud_message_remove_user(Handle);
        }
    ));
    RfgTable.set_function("AddMessageBox", sol::overload(
        [](msgbox_type Type, const char* Title, const char* Description)->int
        {
            if (Util::ContainsChar(Title, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box titles."); }
            if (Util::ContainsChar(Description, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box descriptions."); }
            return rfg::ui_add_msgbox(Type, Title, Description, nullptr, false, false, nullptr, nullptr, false);
        },
        [&](msgbox_type Type, const char* Title, const char* Description, sol::function CallbackFunc)->int
        {
            if (Util::ContainsChar(Title, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box titles."); }
            if (Util::ContainsChar(Description, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box descriptions."); }

            int Handle = rfg::ui_add_msgbox(Type, Title, Description, Lua::RfgMessageBoxCallbackFunction, false, false, nullptr, nullptr, false);
            ScriptManager->GetMessageBoxCallbacks().insert_or_assign(Handle, CallbackFunc);
            return Handle;
        },
        [&](msgbox_type Type, const char* Title, const char* Description, sol::function CallbackFunc, const char* Button1Override, const char* Button2Override)->int
        {
            if (Util::ContainsChar(Title, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box titles."); }
            if (Util::ContainsChar(Description, { '[', ']' })) { throw std::exception("The game does not allow the use '[' or ']' in message box descriptions."); }

            int Handle = rfg::ui_add_msgbox(Type, Title, Description, Lua::RfgMessageBoxCallbackFunction, false, false, Button1Override, Button2Override, false);
            ScriptManager->GetMessageBoxCallbacks().insert_or_assign(Handle, CallbackFunc);
            return Handle;
        }
    ));
    RfgTable.set_function("HumanFireIgnite", sol::overload(
        [](Human* Target, Human* Killer)
        {
            //if (!Target) { throw std::exception("Target is nil!"); }
            //if (!Killer) { throw std::exception("Killer is nil!"); }
            rfg::human_fire_ignite(Target, Killer);
    }));
    RfgTable.set_function("HumanFireStop", rfg::human_fire_stop);

    RfgTable.set_function("HavokBodyApplyLinearImpulse", sol::overload(
        [](uint Handle, vector& Impulse)
        {
            rfg::HavokBodyApplyLinearImpulseB(Handle, Impulse);
    }));

    RfgTable.set_function("HavokBodyApplyPointImpulse", sol::overload(
        [](uint Handle, vector& Impulse, vector& Position)
        {
            rfg::havok_body_apply_point_impulse(Handle, Impulse, Position);
    }));

    RfgTable.set_function("HavokBodySetPos", rfg::HavokBodySetPosition);
    RfgTable.set_function("HavokBodySetPosOrient", rfg::HavokBodySetPositionAndOrient);

    RfgTable.set_function("HavokBodyGetPosOrient", rfg::HavokBodyGetPositionAndOrient);

    RfgTable.set_function("HavokBodyForceActivate", rfg::havok_body_force_activate);
    RfgTable.set_function("HavokBodySetMovable", rfg::havok_body_set_movable);
    RfgTable.set_function("HavokBodyGetMass", rfg::havok_body_get_mass);

    auto Camera = IocContainer->resolve<ICameraManager>();
    RfgTable.set_function("GetLookDirection", [Camera]()->vector
    {
            return Camera->GetLookDirection();
    });
    RfgTable.set_function("GetLookDirectionRightVector", [Camera]()->vector
    {
            return Camera->GetLookOrient().rvec;
    });

    RfgTable["ObjectiveHighlightAdd"] = rfg::objective_highlight_add;
    RfgTable["ObjectiveHighlightRemove"] = rfg::objective_highlight_remove;
    RfgTable["ObjectiveHighlightRemoveAll"] = rfg::objective_highlight_remove_all;

    RfgTable.set_function("RegisterEvent", sol::overload(
        [&](std::string EventTypeName, sol::function EventFunction, std::string EventName)
        {
            static auto Scripts = IocContainer->resolve<IScriptManager>();
            Scripts->RegisterEvent(EventTypeName, EventFunction, EventName);
        },
        [&](std::string EventTypeName, sol::function EventFunction)
        {
            static auto Scripts = IocContainer->resolve<IScriptManager>();
            Scripts->RegisterEvent(EventTypeName, EventFunction);
        }
    ));

    RfgTable["GetMissionName"] = rfg::mission_get_name;
    RfgTable["GetMissionDescription"] = rfg::mission_get_description;
    RfgTable.set_function("LogCurrentMission", []()
    {
        const char* Name = rfg::mission_get_name();
        const char* Description = rfg::mission_get_description();
        if(Name)
        {
            Logger::Log("Mission name: {}\n", Name);
        }
        else
        {
            Logger::Log("No mission name found!\n");
        }
        if(Description)
        {
            Logger::Log("Mission description: {}\n", Description);
        }
        else
        {
            Logger::Log("No mission description found!\n");
        }
    });

    RfgTable["TeleportPlayerIntoVehicle"] = [](vehicle* veh)
    {
        vi_enter_data EnterData{};
        EnterData.specified_seat = VSI_DRIVER;
        EnterData.seat_selection_method = VI_SEAT_SELECTION_METHOD_SPECIFIED;
        EnterData.destination_seat = VSI_DRIVER;
        EnterData.flags.teleport = true;
        rfg::vehicle_interaction_request_enter(Globals::PlayerPtr, veh, &EnterData);
    };
    RfgTable["PlayerExitVehicle"] = [](bool Dive)
    {
        vi_exit_data ExitData = { true, false, false, false, Dive };
        rfg::vehicle_interaction_request_exit(Globals::PlayerPtr, &ExitData);
    };
    RfgTable["VehicleEngineStart"] = [](vehicle* Veh, bool IsPlayer)
    {
        if (!Veh) throw std::exception("Target vehicle is nullptr!");
        rfg::vehicle_engine_start(Veh, nullptr, IsPlayer);
    };
    RfgTable["VehicleEngineStop"] = [](vehicle* Veh, bool IsPlayer, bool Streamout)
    {
        if (!Veh) throw std::exception("Target vehicle is nullptr!");
        rfg::vehicle_engine_stop(Veh, nullptr, IsPlayer, Streamout);
    };
    RfgTable["FlyerEngineStart"] = [](flyer* Veh, bool IsPlayer)
    {
        if (!Veh) throw std::exception("Target flyer is nullptr!");
        rfg::flyer_engine_start(Veh, nullptr, IsPlayer);
    };
    RfgTable["FlyerEngineStop"] = [](flyer* Veh, bool Unused)
    {
        if (!Veh) throw std::exception("Target flyer is nullptr!");
        rfg::flyer_engine_stop(Veh, nullptr, Unused);
    };


    RfgTable["HavokBodyGetLinearVelocity"] = [](uint Handle)->vector
    {
        vector Velocity;
        rfg::havok_body_get_linear_velocity(Handle, Velocity);
        return Velocity;
    };
    RfgTable["HavokBodyGetLinearDampening"] = [](uint Handle)
    {
        return rfg::havok_body_get_linear_dampening(Handle);
    };
    RfgTable["HavokBodyGetAngularDampening"] = [](uint Handle)
    {
        return rfg::havok_body_get_angular_dampening(Handle);
    };
    RfgTable["HavokBodyGetAngularVelocity"] = [](uint Handle)->vector
    {
        vector AngVel;
        rfg::havok_body_get_angular_velocity(Handle, AngVel);
        return AngVel;
    };
    RfgTable["HavokBodySetLinearVelocity"] = [](uint Handle, vector& Velocity)
    {
        rfg::havok_body_set_linear_velocity(Handle, Velocity);
    };
    RfgTable["HavokBodySetLinearDampening"] = [](uint Handle, float LinearDampening)
    {
        rfg::havok_body_set_linear_dampening(Handle, LinearDampening);
    };
    RfgTable["HavokBodySetAngularDampening"] = [](uint Handle, float AngularDampening)
    {
        rfg::havok_body_set_angular_dampening(Handle, AngularDampening);
    };
    RfgTable["HavokBodySetAngularVelocity"] = [](uint Handle, vector& AngularVelocity)
    {
        rfg::havok_body_set_angular_velocity(Handle, AngularVelocity);
    };

    RfgTable["PlayEffect"] = sol::overload(
        //[](uint effect_handle, vector& pos, matrix& orient, bool looping)
        //{
        //    rfg::effects_play(effect_handle, &pos, &orient, looping, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1.0f, false, EFFECTS_CATEGORY_NONE);
        //},
        //[](string& effect_name, vector& pos, matrix& orient, bool looping)
        //{
        //    uint effect_handle = Lua::GetEffectHandle(effect_name);
        //    if(effect_handle == 0xFFFFFFFF)
        //    {
        //        Logger::Log("Could not find valid handle for effect name \"{}\"\n", effect_name);
        //        return;
        //    }
        //    rfg::effects_play(effect_handle, &pos, &orient, looping, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1.0f, false, EFFECTS_CATEGORY_NONE);
        //},
        //[](uint effect_handle, vector pos, matrix orient, bool looping)
        //{
        //    rfg::effects_play(effect_handle, &pos, &orient, looping, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1.0f, false, EFFECTS_CATEGORY_NONE);
        //},
        //[](string& effect_name, vector pos, matrix orient, bool looping)
        //{
        //    uint effect_handle = Lua::GetEffectHandle(effect_name);
        //    if (effect_handle == 0xFFFFFFFF)
        //    {
        //        Logger::Log("Could not find valid handle for effect name \"{}\"\n", effect_name);
        //        return;
        //    }
        //    rfg::effects_play(effect_handle, &pos, &orient, looping, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1.0f, false, EFFECTS_CATEGORY_NONE);
        //},
        [](uint effect_handle, float x, float y, float z)
        {
            vector pos{ x, y, z };
            rfg::effects_play(effect_handle, &pos, &Globals::PlayerPtr->Orientation, false, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1.0f, false, EFFECTS_CATEGORY_NONE);
        }
    );

    RfgTable["SpawnSquad"] = [](string& squadName)
    {
        squad_definition* squadDef = rfg::squad_definition_from_name(squadName.c_str());
        if(!squadDef)
        {
            Logger::LogError("\"{}\" not found in squads.xtbl!", squadName);
            return;
        }

        vector startingPos = Globals::PlayerPtr->Position;
        matrix startingOrient = Globals::PlayerPtr->Orientation;
        squad_spawn_parameters spawnParams;
        rfg::squad_spawn_parameters_constructor(&spawnParams, nullptr);
        spawnParams.squad.squad_def = squadDef;
        int* squadFlagsValue = reinterpret_cast<int*>(&spawnParams.squad.squad_flags);
        *squadFlagsValue |= 0x200;
        spawnParams.orders.orders_type = GFM_ORDERS_TYPE_PATROL;

        rfg_mover* localBuilding = rfg::find_local_building(startingPos);
        if(localBuilding)
        {
            Logger::Log("Found local building at {}. Continuing squad creation.\n", localBuilding->Position.GetDataString(false, true));
            startingPos.y += 5;
            spawnParams.squad.squad_pos = startingPos;
            spawnParams.squad.squad_orient = startingOrient;
            spawnParams.orders.orders_type = GFM_ORDERS_TYPE_DEFEND;
            spawnParams.orders.location_target = localBuilding->Position;
            spawnParams.orders.object_target = localBuilding->Parent;
            spawnParams.orders.location_target = startingPos;

            object_squad* createdSquadObject = rfg::squad_spawn_parameters_create_squad(&spawnParams, nullptr);
            if (createdSquadObject)
            {
                rfg::object_squad_spawn_members(createdSquadObject, nullptr, true, spawnParams.squad.osrp);
                Logger::LogError("Created squad and spawned members. Position is {}.\n", createdSquadObject->Position.GetDataString(false, true));
                int* objFlagsCast = reinterpret_cast<int*>(&createdSquadObject->ObjFlags);
                *objFlagsCast |= 0x20;
            }
            else
            {
                Logger::LogError("Failed to create squad.\n");
            }

            if (spawnParams.created_orders)
                free(spawnParams.created_orders); //Todo: Look in rfg code for more calls to free to see if RSL or RFG are missing any
        }
        else
        {
            Logger::LogWarning("Failed to find local building, attempting to continue squad creation near player.\n");
            startingPos.y += 5;
            bool result = rfg::rfg_snap_to_ground(startingPos);
            Logger::Log("Snap to ground result: {}\n", result);

            spawnParams.squad.squad_pos = startingPos;
            spawnParams.squad.squad_orient = startingOrient;
            spawnParams.orders.location_target = startingPos;

            object_squad* createdSquadObject = rfg::squad_spawn_parameters_create_squad(&spawnParams, nullptr);
            if(createdSquadObject)
            {
                rfg::object_squad_spawn_members(createdSquadObject, nullptr, true, nullptr);
                Logger::Log("Created squad and spawned members. Position is {}.\n", createdSquadObject->Position.GetDataString(false, true));
                int* objFlagsCast = reinterpret_cast<int*>(&createdSquadObject->ObjFlags);
                *objFlagsCast |= 0x20;
            }
            else
            {
                Logger::LogError("Failed to create squad.\n");
            }
        }
    };

    RfgTable["CreatePlayerSquad"] = [](string& squadDefName)
    {
        if (!Globals::PlayerPtr)
            return 0xFFFFFFFF;

        squad_definition* squadDef = rfg::squad_definition_from_name(squadDefName.c_str());
        if(!squadDef)
        {
            Logger::Log("Failed to create player squad. Could not find squad definition with name \"{}\".\n", squadDefName);
            return 0xFFFFFFFF;
        }
        return rfg::player_create_player_squad(Globals::PlayerPtr, nullptr, squadDef);
    };
#endif
}