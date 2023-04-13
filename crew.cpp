#include "crew.h"

namespace game {
	Crew::Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::CREW;
		z_layer_ = 5;
		SetScale(glm::vec2(0.1f, 0.1f));

		alive_ = true;
		health_ = 1.0f;
		efficiency_ = 1.0f;

		activity_state_ = ActivityState::IDLE;

		t_ = 0.0f;
		speed_ = 0.5f;
		destination_vector_ = position;
	}

	void Crew::Update(double delta_time) {
		if (health_ <= 0.0f) {
			alive_ = false;
			activity_state_ = ActivityState::IDLE;
		}
		if (alive_) {
			efficiency_ = health_;
			color_modifier_ = glm::vec3(health_);

			if (activity_state_ == ActivityState::MOVING) {
				t_ += speed_ * efficiency_ * delta_time;
				if (t_ >= 1.0f) {
					t_ = 1.0f;
					activity_state_ = ActivityState::DOING_TASK;
				}
				position_ = destination_ - destination_vector_ * (1.0f - t_);
			}
		}
		GameObject::Update(delta_time);
	}

	void Crew::SetDestination(glm::vec3 destination) {
		
		if (activity_state_ == ActivityState::MOVING || destination == destination_) {
			return;
		}
		activity_state_ = ActivityState::MOVING;	
		destination_ = destination;
		t_ = 0.0f;
		destination_vector_ = destination_ - position_;
		
	}
}