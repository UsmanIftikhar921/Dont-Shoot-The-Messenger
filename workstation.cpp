#include "workstation.h"

namespace game {
	Workstation::Workstation(const glm::vec3& position, Geometry* geom, Shader* shader, Task* task) : GameObject(position, geom, shader, NULL)
	{
		type_ = ObjType::WORKSTATION;
		occupied_ = false;
		crew_arrived_ = false;
		crew_ = nullptr;
		task_object_ = task;
		AddChild(task_object_);

		texture_ = GameObject::textures.GetTexture(15);
	}

	void Workstation::Update(double delta_time)
	{
		if (occupied_) {
			if (!crew_->GetAlive()) {
				UnassignCrew();
				return;
			}
			
			if (!crew_arrived_) {
				if (crew_->GetActivityState() == ActivityState::DOING_TASK) {
					crew_arrived_ = true;
				}
			}
			if (crew_arrived_ && crew_->GetActivityState() != ActivityState::DOING_TASK) {
				crew_arrived_ = false;
				UnassignCrew();
			}
			else {
				if (task_object_->GetReady() && crew_->GetActivityState() == ActivityState::DOING_TASK) {
					task_object_->PerformTask(crew_->GetHealth());
				}
			}
		}
		GameObject::Update(delta_time);
	}

	void Workstation::AssignCrew(Crew* crew)
	{
		crew_ = crew;
		occupied_ = true;
		texture_ = GameObject::textures.GetTexture(16);
	}

	void Workstation::UnassignCrew()
	{
		crew_ = nullptr;
		occupied_ = false;
		texture_ = GameObject::textures.GetTexture(15);
		crew_arrived_ = false;
		task_object_->ResetTask();
	}
	
}