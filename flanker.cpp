#include "flanker.h"

namespace game {
	Flanker::Flanker(const glm::vec3& positiong, Geometry* geom, Shader* shader, GameObject* target) : Enemy(positiong, geom, shader, target) {


		EnterOrbitState(1.5f, 5.0f, glm::pi<float>(), 2.0*glm::pi<float>());
		gun_ = new Gun(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, false);
		gun_->SetZLayer(-1);
		gun_->SetRotation(glm::pi<float>() / 2);
		gun_->SetScale(glm::vec2(0.4f, 0.4f));
		AddChild(gun_);
	}

	void Flanker::Update(double delta_time, GuiState* gui_state) {
		glm::vec3 target_pos = target_->GetPosition();
		float angle_from_enemy_to_target = -glm::atan(target_pos.x - position_.x, target_pos.y - position_.y);
		float enemy_rotation = GetGlobalRotation();
		float new_gun_rotation = angle_from_enemy_to_target - enemy_rotation;
		gun_->SetRotation(new_gun_rotation);

		Enemy::Update(delta_time, gui_state);
	}

	void Flanker::StateTransitionHandler(double delta_time) {
		switch (state_) {
		case CHASE:
			break;

		case HOME_IN:
			break;

		case ORBIT:
			if (orbit_completed_ && orbit_enemy_arrived_) {
				std::cout << "Flanker: Orbit completed, entering fire state" << std::endl;
				//gun_->SetRotation(glm::atan(target_->GetPosition().y - position_.y, target_->GetPosition().x - position_.x) - GetGlobalRotation());
				EnterFireState();
			}
			break;

		case WAIT:
			break;

		case FIRE:
			if (shots_fired_ >= total_shots_) {
				std::cout << "Flanker: Shots fired, entering orbit state" << std::endl;
				EnterOrbitState(1.5f, 5.0f, glm::mod(orbit_final_angle_, 2.0f*glm::pi<float>()), glm::mod(orbit_final_angle_, 2.0f * glm::pi<float>()) + glm::pi<float>());
			}
			break;
		}
	}

	void Flanker::FireOnTarget(float delta_time) {
		if (gun_->PerformTask(1.0f)) shots_fired_ += 1;

		glm::vec3 new_firing_pos = target_->GetPosition() + relative_firing_position_;
		HomeInOnPoint(new_firing_pos, target_->GetVelocity(), delta_time);
	}


}