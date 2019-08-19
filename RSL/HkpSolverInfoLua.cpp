#include "HkpSolverInfoLua.h"
#include "Functions.h"

void Lua::BindHkpSolverInfo(sol::state& LuaState)
{
    auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
    RfgTable.new_usertype<hkpSolverInfo>
    (
        "hkpSolverInfo",
        "new", sol::no_constructor,
        //"", &hkpSolverInfo::m_padding, //Seems to just be padding for the class in memory. Dunno why
        "Tau", &hkpSolverInfo::m_tau,
        "Damping", &hkpSolverInfo::m_damping,
        "FrictionTau", &hkpSolverInfo::m_frictionTau,
        //"", &hkpSolverInfo::m_globalAccelerationPerSubStep, //Todo: Bind hkVector4f and test if these 4 values can be changed 
        //"", &hkpSolverInfo::m_globalAccelerationPerStep,
        //"", &hkpSolverInfo::m_integrateVelocityFactor,
        //"", &hkpSolverInfo::m_invIntegrateVelocityFactor,
        "DampDivTau", &hkpSolverInfo::m_dampDivTau,
        "TauDivDamp", &hkpSolverInfo::m_tauDivDamp,
        "DampDivFrictionTau", &hkpSolverInfo::m_dampDivFrictionTau,
        "FrictionTauDivDamp", &hkpSolverInfo::m_frictionTauDivDamp,
        "ContactRestingVelocity", &hkpSolverInfo::m_contactRestingVelocity,
        //"", &hkpSolverInfo::m_deactivationInfo, //Todo: Bind hkSolverInfo_DeactivationInfo and then bind this variable and test it.
        "DeltaTime", sol::readonly(&hkpSolverInfo::m_deltaTime),
        "InvDeltaTime", sol::readonly(&hkpSolverInfo::m_invDeltaTime),
        "NumSteps", &hkpSolverInfo::m_numSteps,
        "NumMicroSteps", &hkpSolverInfo::m_numMicroSteps,
        "InvNumMicroSteps", sol::readonly(&hkpSolverInfo::m_invNumMicroSteps),
        "InvNumSteps", sol::readonly(&hkpSolverInfo::m_invNumSteps),
        "ForceCoherentConstraintOrderingInSolver", sol::property(
            [](hkpSolverInfo& Self) {return static_cast<bool>(Self.m_forceCoherentConstraintOrderingInSolver.m_bool); },
            [](hkpSolverInfo& Self, bool Value) {Self.m_forceCoherentConstraintOrderingInSolver.m_bool = static_cast<char>(Value); })
    );
}
