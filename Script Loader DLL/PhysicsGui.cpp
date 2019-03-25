#include "PhysicsGui.h"


PhysicsGui::PhysicsGui(bool* _OpenState, std::string _Title)
{
	OpenState = _OpenState;
	Title = _Title;
}

PhysicsGui::~PhysicsGui()
{

}

void PhysicsGui::Draw()
{
	if (!*OpenState)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), OpenState))
	{
		ImGui::End();
		return;
	}

	if (GlobalhkpWorldPtr)
	{
		ImGui::PushFont(FontBig);
		ImGui::Text("Physics settings:");
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::PushStyleColor(ImGuiCol_Text, ColorRed);
		ImGui::PushItemWidth(400.0f);
		ImGui::TextWrapped("Warning: Be very careful with this menu if you want your game to be stable. Changing these values can make things go wacky quick.");
		ImGui::PopStyleColor();
		ImGui::Separator();

		ImGui::PushItemWidth(230.0f);
		ImGui::InputFloat("Custom physics timestep multiplier", &CustomPhysicsTimeStepMultiplier, 0.01, 0.5, 3);
		ImGui::SameLine();
		ImGui::Checkbox("Use", &UseCustomPhysicsTimestepMultiplier);
		ImGui::Separator();

		if (!CurrentGravity)
		{
			CurrentGravity = hkpWorldGetGravity(GlobalhkpWorldPtr, NULL);

			if (CurrentGravity)
			{
				CustomGravityVector.m_quad.m128_f32[0] = CurrentGravity->m_quad.m128_f32[0];
				CustomGravityVector.m_quad.m128_f32[1] = CurrentGravity->m_quad.m128_f32[1];
				CustomGravityVector.m_quad.m128_f32[2] = CurrentGravity->m_quad.m128_f32[2];
				CustomGravityVector.m_quad.m128_f32[3] = CurrentGravity->m_quad.m128_f32[3];

				DefaultGravityVector.m_quad.m128_f32[0] = CurrentGravity->m_quad.m128_f32[0];
				DefaultGravityVector.m_quad.m128_f32[1] = CurrentGravity->m_quad.m128_f32[1];
				DefaultGravityVector.m_quad.m128_f32[2] = CurrentGravity->m_quad.m128_f32[2];
				DefaultGravityVector.m_quad.m128_f32[3] = CurrentGravity->m_quad.m128_f32[3];
			}
		}
		if (CurrentGravity)
		{
			ImGui::Text("Current gravity vector: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::string(std::string("(") + std::to_string(CurrentGravity->m_quad.m128_f32[0]) + std::string(", ")
				+ std::to_string(CurrentGravity->m_quad.m128_f32[1]) + std::string(", ")
				+ std::to_string(CurrentGravity->m_quad.m128_f32[2]) + std::string(", ")
				+ std::to_string(CurrentGravity->m_quad.m128_f32[3]) + std::string(")")).c_str());
		}
		else
		{
			ImGui::Text("Can't print current gravity. Null pointer to value");
		}

		ImGui::Text("Default gravity vector: ");
		ImGui::SameLine();
		ImGui::TextColored(SecondaryTextColor, std::string(std::string("(") + std::to_string(DefaultGravityVector.m_quad.m128_f32[0]) + std::string(", ")
			+ std::to_string(DefaultGravityVector.m_quad.m128_f32[1]) + std::string(", ")
			+ std::to_string(DefaultGravityVector.m_quad.m128_f32[2]) + std::string(", ")
			+ std::to_string(DefaultGravityVector.m_quad.m128_f32[3]) + std::string(")")).c_str());
		ImGui::InputFloat4("Gravity", CustomGravityVector.m_quad.m128_f32, 3);
		ImGui::SameLine();
		if (ImGui::Button("Set##GravitySetButton"))
		{
			hkpWorldSetGravity(GlobalhkpWorldPtr, NULL, &CustomGravityVector);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset##GravityResetButton"))
		{
			hkpWorldSetGravity(GlobalhkpWorldPtr, NULL, &DefaultGravityVector);
		}

		ImGui::Separator();
		ImGui::PushFont(FontBig);
		ImGui::Text("Solver settings:");
		ImGui::PopFont();
		ImGui::Separator();
		hkpSolverInfo* SolverPtr = &GlobalhkpWorldPtr->m_dynamicsStepInfo.m_solverInfo;
		if (ImGui::Button("Reset all"))
		{
			SolverPtr->m_tau = 0.600f;
			SolverPtr->m_damping = 1.000f;
			SolverPtr->m_frictionTau = 0.300f;
			SolverPtr->m_dampDivTau = 1.667f;
			SolverPtr->m_tauDivDamp = 0.600f;
			SolverPtr->m_dampDivFrictionTau = 3.333f;
			SolverPtr->m_frictionTauDivDamp = 0.300f;
			SolverPtr->m_contactRestingVelocity = 0.200f;
			SolverPtr->m_numSteps = 4;
			SolverPtr->m_numMicroSteps = 1;
			SolverPtr->m_forceCoherentConstraintOrderingInSolver.m_bool = (char)false;
		}

		if (SolverPtr)
		{
			//ImGui::InputFloat("Padding", &SolverPtr->m_padding, 0.01, 0.1, 3);
			ImGui::InputFloat("Tau", &SolverPtr->m_tau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##Tau"))
			{
				SolverPtr->m_tau = 0.600f;
			}
			ImGui::InputFloat("Damping", &SolverPtr->m_damping, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##Damping"))
			{
				SolverPtr->m_damping = 1.000f;
			}
			ImGui::InputFloat("Friction tau", &SolverPtr->m_frictionTau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##FrictionTau"))
			{
				SolverPtr->m_frictionTau = 0.300f;
			}
			///hkVector4f m_globalAccelerationPerSubStep;
			///hkVector4f m_globalAccelerationPerStep;
			///hkVector4f m_integrateVelocityFactor;
			///hkVector4f m_invIntegrateVelocityFactor;
			ImGui::InputFloat("Damp div tau", &SolverPtr->m_dampDivTau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##DampDivTau"))
			{
				SolverPtr->m_dampDivTau = 1.667f;
			}
			ImGui::InputFloat("Tau div damp", &SolverPtr->m_tauDivDamp, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##TauDivDamp"))
			{
				SolverPtr->m_tauDivDamp = 0.600f;
			}
			ImGui::PushItemWidth(230.0f);
			ImGui::InputFloat("Damp div friction tau", &SolverPtr->m_dampDivFrictionTau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##DampDivFrictionTau"))
			{
				SolverPtr->m_dampDivFrictionTau = 3.333f;
			}
			ImGui::PushItemWidth(230.0f);
			ImGui::InputFloat("Friction tau div damp", &SolverPtr->m_frictionTauDivDamp, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##FrictionTauDivDamp"))
			{
				SolverPtr->m_frictionTauDivDamp = 0.300f;
			}
			ImGui::PushItemWidth(230.0f);
			ImGui::InputFloat("Contact resting velocity", &SolverPtr->m_contactRestingVelocity, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##ContactRestingVelocity"))
			{
				SolverPtr->m_contactRestingVelocity = 0.200f;
			}
			///hkpSolverInfo_DeactivationInfo m_deactivationInfo[6];
			ImGui::Text("Delta time: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(SolverPtr->m_deltaTime).c_str());
			//ImGui::InputFloat("Delta time", &, 0.01, 0.1, 3);
			//ImGui::InputFloat("Inverse delta time", &SolverPtr->m_invDeltaTime, 0.01, 0.1, 3);
			ImGui::InputInt("Num steps", &SolverPtr->m_numSteps);
			ImGui::SameLine();
			if (ImGui::Button("Reset##NumSteps"))
			{
				SolverPtr->m_numSteps = 4;
			}
			ImGui::PushItemWidth(230.0f);
			ImGui::InputInt("Num micro steps", &SolverPtr->m_numMicroSteps);
			ImGui::SameLine();
			if (ImGui::Button("Reset##NumMicroSteps"))
			{
				SolverPtr->m_numMicroSteps = 1;
			}
			//
			//ImGui::InputFloat("Inverse num micro steps", &SolverPtr->m_invNumMicroSteps, 0.01, 0.1, 3);
			//ImGui::InputFloat("Inverse num steps", &SolverPtr->m_invNumSteps, 0.01, 0.1, 3);
			ImGui::Checkbox("Force coherent constraint ordering in solver", (bool*)&SolverPtr->m_forceCoherentConstraintOrderingInSolver.m_bool);
			///char m_deactivationNumInactiveFramesSelectFlag[2];
			///char m_deactivationIntegrateCounter;
			//ImGui::InputFloat("Max constraint violation squared", &SolverPtr->m_maxConstraintViolationSqrd, 0.01, 0.1, 3);
		}
		else
		{
			ImGui::Text("Havok solver pointer invalid. Can't display solver gui.");
		}

		ImGui::Separator();
		ImGui::PushFont(FontBig);
		ImGui::Text("Physics info:");
		ImGui::PopFont();
		ImGui::Separator();

		ImGui::Text("Simulation type: ");
		ImGui::SameLine();
		int SimType = GlobalhkpWorldPtr->m_simulationType.m_storage;
		if (SimType == SIMULATION_TYPE_INVALID)
		{
			ImGui::TextColored(SecondaryTextColor, "Invalid");
		}
		else if (SimType == SIMULATION_TYPE_DISCRETE)
		{
			ImGui::TextColored(SecondaryTextColor, "Discrete");
		}
		else if (SimType == SIMULATION_TYPE_CONTINUOUS)
		{
			ImGui::TextColored(SecondaryTextColor, "Continuous");
		}
		else if (SimType == SIMULATION_TYPE_MULTITHREADED)
		{
			ImGui::TextColored(SecondaryTextColor, "Multi-threaded");
		}
		else
		{
			ImGui::TextColored(SecondaryTextColor, "Unknown");
		}
	}
	else
	{
		ImGui::Text("Havok world pointer invalid. Can't display physics gui.");
	}
	ImGui::End();
}
