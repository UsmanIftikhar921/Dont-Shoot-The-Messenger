#include "task.h"

namespace game {

	Task::Task(const glm::vec3& position, Geometry* geom, Shader* shader, float completion_time) : GameObject(position, geom, shader, NULL) {
		type_ = ObjType::TASK;
		completion_time_ = completion_time;
		efficiency_modifier_ = 1.0f;
		cooldown_timer_ = 0.0f;
		ready_ = true;
	}

	void Task::Update(double delta_time) {
		if (!ready_) {
			cooldown_timer_ -= (float)delta_time * efficiency_modifier_;
			if (cooldown_timer_ <= 0.0f) {
				cooldown_timer_ = 0.0f;
				ready_ = true;
			}
		}
		GameObject::Update(delta_time);
	}

	void Task::ResetTask() {
		ready_ = false;
		cooldown_timer_ = completion_time_;
	}

	
}