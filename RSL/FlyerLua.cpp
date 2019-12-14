#include "FlyerLua.h"
#include "Functions.h"

void Lua::BindFlyerFlags(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<flyer_flags>();
    Utype.set("LandingGearUp", sol::property(
        [](flyer_flags& Self)->bool {return Self.landing_gear_up; },
        [](flyer_flags& Self, bool Value) {Self.landing_gear_up = Value; }
    ));
    Utype.set("LandingGearCollisionOff", sol::property(
        [](flyer_flags& Self)->bool {return Self.landing_gear_collision_off; },
        [](flyer_flags& Self, bool Value) {Self.landing_gear_collision_off = Value; }
    ));
    Utype.set("NeedsToTakeoff", sol::property(
        [](flyer_flags& Self)->bool {return Self.needs_to_takeoff; },
        [](flyer_flags& Self, bool Value) {Self.needs_to_takeoff = Value; }
    ));
    Utype.set("HasLift", sol::property(
        [](flyer_flags& Self)->bool {return Self.has_lift; },
        [](flyer_flags& Self, bool Value) {Self.has_lift = Value; }
    ));
    Utype.set("StayAtConstantHeight", sol::property(
        [](flyer_flags& Self)->bool {return Self.stay_at_constant_height; },
        [](flyer_flags& Self, bool Value) {Self.stay_at_constant_height = Value; }
    ));
    Utype.set("OnGround", sol::property(
        [](flyer_flags& Self)->bool {return Self.on_ground; },
        [](flyer_flags& Self, bool Value) {Self.on_ground = Value; }
    ));
    RfgTable.set_usertype("FlyerFlags", Utype);
#endif
}

void Lua::BindFlyer(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<flyer>();
    Utype.set("new", sol::constructors<flyer(const flyer&)>());
    Utype.set(sol::base_classes, sol::bases<vehicle, object>());
    //rdd
    //Utype.set("CtlAction", &flyer::ctl_action);
    Utype.set("ReqUrgency", &flyer::req_urgency);
    Utype.set("ReqMaxVel", &flyer::req_max_vel);
    Utype.set("ReqPoint", &flyer::req_point);
    Utype.set("ReqVel", &flyer::req_vel);
    Utype.set("ReqLookAt", &flyer::req_lookat);
    Utype.set("ReqPointIsValid", &flyer::req_point_isvalid);
    Utype.set("ReqVelIsValid", &flyer::req_vel_isvalid);
    Utype.set("ReqLookAtIsValid", &flyer::req_lookat_isvalid);
    Utype.set("ReqStopAtPoint", &flyer::req_stop_at_point);
    Utype.set("ReqHalt", &flyer::req_halt);
    Utype.set("WingIsDetached", &flyer::wing_is_detached);
    Utype.set("VehicleMass", &flyer::vehicle_mass);
    Utype.set("ChassisComCs", &flyer::chassis_com_cs);
    Utype.set("ChassisComWs", &flyer::chassis_com_ws);
    Utype.set("ThrustMatCs", &flyer::thrust_mat_cs);
    Utype.set("ThrustMatWs", &flyer::thrust_mat_ws);
    Utype.set("ThrustUpTarget", &flyer::thrust_up_target);
    Utype.set("HoverNoiseVec", &flyer::hover_noise_vec);
    Utype.set("HoverNoiseVecNew", &flyer::hover_noise_vec_new);
    Utype.set("HoverNoiseVecOld", &flyer::hover_noise_vec_old);
    Utype.set("HoverNoiseTimer", &flyer::hover_noise_timer);
    Utype.set("HoverNoiseDur", &flyer::hover_noise_dur);
    Utype.set("EngineOffSuspensionPeriod", &flyer::engine_off_suspension_period);
    Utype.set("TurbineRpmTarget", &flyer::turbine_rpm_target);
    Utype.set("TurbineRpm", &flyer::turbine_rpm);
    Utype.set("TurbineLoad", &flyer::turbine_load);
    Utype.set("LWing", &flyer::l_wing);
    Utype.set("RWing", &flyer::r_wing);
    Utype.set("LCanard", &flyer::l_canard);
    Utype.set("RCanard", &flyer::r_canard);
    Utype.set("WingtipEffect", sol::property([](flyer& Self) {return std::ref(Self.wingtip_effect); }));
    Utype.set("FrontThruster", sol::property([](flyer& Self) {return std::ref(Self.front_thruster); }));
    Utype.set("CenterThruster", sol::property([](flyer& Self) {return std::ref(Self.center_thruster); }));
    Utype.set("MainEngines", sol::property([](flyer& Self) {return std::ref(Self.main_engines); }));
    Utype.set("Jetwash", &flyer::jetwash);
    Utype.set("EngineForce", &flyer::engine_force);
    Utype.set("StartupTimer", &flyer::startup_timer);
    Utype.set("LastPlayerDamage", &flyer::last_player_damage);
    Utype.set("CatchFireTimer", &flyer::catch_fire_timer);
    Utype.set("FlyerFlags", &flyer::flyer_flags);
    RfgTable.set_usertype("Flyer", Utype);
#endif
}
