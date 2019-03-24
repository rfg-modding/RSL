#include "FreeCamGui.h"
#include "CameraWrapper.h"

FreeCamGui::FreeCamGui(bool * _OpenState, std::string _Title)
{
	OpenState = _OpenState;
	Title = _Title;

}

FreeCamGui::~FreeCamGui()
{

}

void FreeCamGui::Draw()
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
	if (!Camera)
	{
		ImGui::Text(std::string(std::string(u8"Camera pointer not set. What do? ") + std::string(ICON_FA_FROWN_OPEN)).c_str());
		ImGui::End();
		return;
	}
	
	ImGui::PushFont(FontBig);
	ImGui::Text("Free cam settings:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Toggle free cam"))
	{
		Camera->ToggleFreeCamera();
	}
	ImGui::Checkbox("Return player to original position?", &ReturnPlayerToOriginalPosition);
	ImGui::SameLine();
	Utilities::GUI::ShowHelpMarker("If this is on the player will be teleported back to their original position after the free cam is disabled. If it's off then the player will be dropped wherever the free cam deactivates. So be careful.");
	ImGui::InputFloat("Move speed", &Camera->CameraSpeed, 0.1, 5.0, 3);

	//ImGui::Checkbox("Have player follow camera", &PlayerFollowCam);
	//ImGui::SameLine();
	//Utilities::GUI::ShowHelpMarker("This causes the player to follow the camera via teleportation. This is a workaround to make npc and vehicles spawns work.");
	
	//ImGui::InputFloat("Real FOV", (float*)Camera->RealFOV, 0.1, 5.0, 3);
	//ImGui::InputFloat("Ideal FOV", (float*)Camera->IdealFOV, 0.1, 5.0, 3);

	ImGui::Text("Far clip distance: ");
	ImGui::SameLine();
	ImGui::TextColored(SecondaryTextColor, std::to_string(game_render_get_far_clip_distance()).c_str());

	//ImGui::PushItemWidth(300.0f);
	ImGui::InputFloat("Custom far clip distance", &CustomFarClipDistance, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	if (ImGui::Button("Set"))
	{
		game_render_set_far_clip_distance(CustomFarClipDistance);
	}

	/*ImGui::Separator();
	ImGui::PushFont(FontBig);
	ImGui::Text("Additional camera settings:");
	ImGui::PopFont();
	ImGui::Separator();
	if (GlobalMainSceneCameraPtr)
	{
		ImGui::InputFloat("FOV", &GlobalMainSceneCameraPtr->m_fov, 1.0, 5.0, 3);
		ImGui::InputFloat("Near clip", &GlobalMainSceneCameraPtr->m_near_clip, 1.0, 5.0, 3);
		ImGui::InputFloat("Far clip", &GlobalMainSceneCameraPtr->m_far_clip, 1.0, 5.0, 3);
		ImGui::InputFloat("High lod far clip", &GlobalMainSceneCameraPtr->m_high_lod_far_clip, 1.0, 5.0, 3);
	}
	else
	{
		ImGui::Text("Main scene camera hook has not been completed. Can't display additional camera tweaks.");
	}

	if (GlobalMainScenePtr)
	{
		ImGui::SliderFloat("Time value", &GlobalMainScenePtr->m_time_val, 0.0f, 5000.0f);
		ImGui::SliderFloat("Time of day value", &GlobalMainScenePtr->m_time_of_day_val, 0.0f, 5000.0f);

		
	}
	else
	{
		ImGui::Text("Main scene pointer is null. Can't show options.");
	}*/
	

	/*ImGui::Separator();
	ImGui::PushFont(FontBig);
	ImGui::Text("Additional camera settings (rl_state_manager):");
	ImGui::PopFont();

	if (GlobalRlStateManagerPtr)
	{
		if (GlobalRlStateManagerPtr->m_active_camera_p)
		{
			const void* address = static_cast<const void*>(&*GlobalRlStateManagerPtr->m_active_camera_p);
			std::stringstream ss;
			ss << address;
			std::string AddressString = ss.str();
			ImGui::Text("Address of current rl_camera:");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, AddressString.c_str());
		}
		else
		{
			ImGui::Text("m_active_camera_p is null");
		}

	}
	else
	{
		ImGui::Text("Render state manager hook has not been completed. Can't display additional camera tweaks.");
	}

	ImGui::Separator();
	ImGui::PushFont(FontBig);
	ImGui::Text("Renderer metrics:");
	ImGui::PopFont();

	if (GlobalRlRenderLibPtr)
	{
		if (GlobalRlRenderLibPtr)
		{
			ImGui::Text("Warning flags: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_warning_flags).c_str());

			ImGui::Text("Particle batches: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_particle_batches).c_str());

			ImGui::Text("Particle batch average: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_particle_batch_average).c_str());

			ImGui::Text("Num dps per group values: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_num_dps_per_group_vals).c_str());

			ImGui::Text("Max dps per group: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_max_dps_per_group).c_str());

			ImGui::Text("Total dps per group: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_total_dps_per_group).c_str());

			ImGui::Text("CPU render time: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_cpu_render_time).c_str());

			ImGui::Text("GPU render time: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_gpu_render_time).c_str());

			ImGui::Text("CPU scene render time: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_cpu_scene_render_time).c_str());

			ImGui::Text("Num draw calls: ");
			ImGui::SameLine();
			ImGui::TextColored(SecondaryTextColor, std::to_string(GlobalRlRenderLibPtr->m_metrics_p->m_num_draw_calls).c_str());
		}
		else
		{
			ImGui::Text("m_metrics_p is null");
		}
	}
	else
	{
		ImGui::Text("Renderlib hook has not been completed. Render metrics.");
	}*/

	ImGui::End();
}
