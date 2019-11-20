#include "HkpSolverInfoLua.h"
#include "Functions.h"

void Lua::BindHkpSolverInfo(sol::state& LuaState)
{
#if LUA_ENABLED
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    auto Utype = RfgTable.create_simple_usertype<hkpSolverInfo>();
    Utype.set("new", sol::no_constructor);
    //Utype.set("", &hkpSolverInfo::m_padding); //Seems to just be padding for the class in memory. Dunno why
    Utype.set("Tau", &hkpSolverInfo::m_tau);
    Utype.set("Damping", &hkpSolverInfo::m_damping);
    Utype.set("FrictionTau", &hkpSolverInfo::m_frictionTau);
    //Utype.set("", &hkpSolverInfo::m_globalAccelerationPerSubStep); //Todo: Bind hkVector4f and test if these 4 values can be changed 
    //Utype.set("", &hkpSolverInfo::m_globalAccelerationPerStep);
    //Utype.set("", &hkpSolverInfo::m_integrateVelocityFactor);
    //Utype.set("", &hkpSolverInfo::m_invIntegrateVelocityFactor);
    Utype.set("DampDivTau", &hkpSolverInfo::m_dampDivTau);
    Utype.set("TauDivDamp", &hkpSolverInfo::m_tauDivDamp);
    Utype.set("DampDivFrictionTau", &hkpSolverInfo::m_dampDivFrictionTau);
    Utype.set("FrictionTauDivDamp", &hkpSolverInfo::m_frictionTauDivDamp);
    Utype.set("ContactRestingVelocity", &hkpSolverInfo::m_contactRestingVelocity);
    //Utype.set("", &hkpSolverInfo::m_deactivationInfo); //Todo: Bind hkSolverInfo_DeactivationInfo and then bind this variable and test it.
    Utype.set("DeltaTime", sol::readonly(&hkpSolverInfo::m_deltaTime));
    Utype.set("InvDeltaTime", sol::readonly(&hkpSolverInfo::m_invDeltaTime));
    Utype.set("NumSteps", &hkpSolverInfo::m_numSteps);
    Utype.set("NumMicroSteps", &hkpSolverInfo::m_numMicroSteps);
    Utype.set("InvNumMicroSteps", sol::readonly(&hkpSolverInfo::m_invNumMicroSteps));
    Utype.set("InvNumSteps", sol::readonly(&hkpSolverInfo::m_invNumSteps));
    Utype.set("ForceCoherentConstraintOrderingInSolver",
        sol::property(
            [](hkpSolverInfo& Self) {return static_cast<bool>(Self.m_forceCoherentConstraintOrderingInSolver.m_bool); },
            [](hkpSolverInfo& Self, bool Value) {Self.m_forceCoherentConstraintOrderingInSolver.m_bool = static_cast<char>(Value); }
        ));
    //Utype.set("", &hkpSolverInfo::m_deactivationNumInactiveFramesSelectFlag); //Todo: Try binding this
    //Utype.set("", &hkpSolverInfo::m_deactivationIntegrateCounter);
    //Utype.set("", &hkpSolverInfo::m_maxConstraintViolationSqrd);
    RfgTable.set_usertype("hkpSolverInfo", Utype);
#endif
}
