#include "PhysicsGui.h"

void PhysicsGui::Draw()
{
	if (!Visible)
        return;

    ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), &Visible))
	{
		ImGui::End();
		return;
	}

	if (Globals::hkpWorldPtr)
	{
		ImGui::PushFont(Globals::FontBig);
		ImGui::Text("Physics settings:");
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::PushStyleColor(ImGuiCol_Text, Globals::ColorRed);
        ImGui::SetNextItemWidth(300.0f);
		ImGui::TextWrapped("Warning: Be very careful with this menu if you want your game to be stable. Changing these values can make things go wacky quick.");
		ImGui::PopStyleColor();
		ImGui::Separator();

		if (!CurrentGravity)
		{
			CurrentGravity = rfg::hkpWorldGetGravity(Globals::hkpWorldPtr, NULL);
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
			ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::string("(") + std::to_string(CurrentGravity->m_quad.m128_f32[0]) + std::string(", ")
				+ std::to_string(CurrentGravity->m_quad.m128_f32[1]) + std::string(", ")
				+ std::to_string(CurrentGravity->m_quad.m128_f32[2]) + std::string(", ")
				+ std::to_string(CurrentGravity->m_quad.m128_f32[3]) + std::string(")")).c_str());
		}
		else
            ImGui::Text("Can't print current gravity. Null pointer to value");

        ImGui::Text("Default gravity vector: ");
		ImGui::SameLine();
		ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::string("(") + std::to_string(DefaultGravityVector.m_quad.m128_f32[0]) + std::string(", ")
			+ std::to_string(DefaultGravityVector.m_quad.m128_f32[1]) + std::string(", ")
			+ std::to_string(DefaultGravityVector.m_quad.m128_f32[2]) + std::string(", ")
			+ std::to_string(DefaultGravityVector.m_quad.m128_f32[3]) + std::string(")")).c_str());
		ImGui::InputFloat4("Gravity", CustomGravityVector.m_quad.m128_f32, 3);
		ImGui::SameLine();
		if (ImGui::Button("Set##GravitySetButton"))
            rfg::hkpWorldSetGravity(Globals::hkpWorldPtr, NULL, &CustomGravityVector);

        ImGui::SameLine();
		if (ImGui::Button("Reset##GravityResetButton"))
            rfg::hkpWorldSetGravity(Globals::hkpWorldPtr, NULL, &DefaultGravityVector);

        ImGui::Separator();
		ImGui::PushFont(Globals::FontBig);
		ImGui::Text("Solver settings:");
		ImGui::PopFont();
		ImGui::Separator();
		hkpSolverInfo* SolverPtr = &Globals::hkpWorldPtr->m_dynamicsStepInfo.m_solverInfo;
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
			ImGui::SetNextItemWidth(230.0f);
			ImGui::InputFloat("Tau", &SolverPtr->m_tau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##Tau"))
                SolverPtr->m_tau = 0.600f;

			ImGui::SetNextItemWidth(230.0f);
		    ImGui::InputFloat("Damping", &SolverPtr->m_damping, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##Damping"))
                SolverPtr->m_damping = 1.000f;

			ImGui::SetNextItemWidth(230.0f);
		    ImGui::InputFloat("Friction tau", &SolverPtr->m_frictionTau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##FrictionTau"))
                SolverPtr->m_frictionTau = 0.300f;

			ImGui::SetNextItemWidth(230.0f);
			ImGui::InputFloat("Damp div tau", &SolverPtr->m_dampDivTau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##DampDivTau"))
                SolverPtr->m_dampDivTau = 1.667f;

			ImGui::SetNextItemWidth(230.0f);
		    ImGui::InputFloat("Tau div damp", &SolverPtr->m_tauDivDamp, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##TauDivDamp"))
                SolverPtr->m_tauDivDamp = 0.600f;

		    ImGui::SetNextItemWidth(230.0f);
			ImGui::InputFloat("Damp div friction tau", &SolverPtr->m_dampDivFrictionTau, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##DampDivFrictionTau"))
                SolverPtr->m_dampDivFrictionTau = 3.333f;

		    ImGui::SetNextItemWidth(230.0f);
			ImGui::InputFloat("Friction tau div damp", &SolverPtr->m_frictionTauDivDamp, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##FrictionTauDivDamp"))
                SolverPtr->m_frictionTauDivDamp = 0.300f;

		    ImGui::SetNextItemWidth(230.0f);
			ImGui::InputFloat("Contact resting velocity", &SolverPtr->m_contactRestingVelocity, 0.01, 0.1, 3);
			ImGui::SameLine();
			if (ImGui::Button("Reset##ContactRestingVelocity"))
                SolverPtr->m_contactRestingVelocity = 0.200f;

			Util::Gui::LabelAndValue("Delta time: ", std::to_string(SolverPtr->m_deltaTime));
			ImGui::SetNextItemWidth(230.0f);
			ImGui::InputInt("Num steps", &SolverPtr->m_numSteps);
			ImGui::SameLine();
			if (ImGui::Button("Reset##NumSteps"))
                SolverPtr->m_numSteps = 4;

		    ImGui::SetNextItemWidth(230.0f);
			ImGui::InputInt("Num micro steps", &SolverPtr->m_numMicroSteps);
			ImGui::SameLine();
			if (ImGui::Button("Reset##NumMicroSteps"))
                SolverPtr->m_numMicroSteps = 1;

			ImGui::Checkbox("Force coherent constraint ordering in solver", (bool*)&SolverPtr->m_forceCoherentConstraintOrderingInSolver.m_bool);
		}
		else
            ImGui::Text("Havok solver pointer invalid. Can't display solver gui.");

        ImGui::Separator();
		ImGui::PushFont(Globals::FontBig);
		ImGui::Text("Physics info:");
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Text("Simulation type: ");
		ImGui::SameLine();

		int SimType = Globals::hkpWorldPtr->m_simulationType.m_storage;
		if (SimType == SIMULATION_TYPE_INVALID)
            ImGui::TextColored(Globals::SecondaryTextColor, "Invalid");
        else if (SimType == SIMULATION_TYPE_DISCRETE)
            ImGui::TextColored(Globals::SecondaryTextColor, "Discrete");
        else if (SimType == SIMULATION_TYPE_CONTINUOUS)
            ImGui::TextColored(Globals::SecondaryTextColor, "Continuous");
        else if (SimType == SIMULATION_TYPE_MULTITHREADED)
            ImGui::TextColored(Globals::SecondaryTextColor, "Multi-threaded");
        else
            ImGui::TextColored(Globals::SecondaryTextColor, "Unknown");
    }
	else
        ImGui::Text("Havok world pointer invalid. Can't display physics gui.");

    ImGui::End();
}
