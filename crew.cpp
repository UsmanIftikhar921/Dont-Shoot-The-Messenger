#include "crew.h"

namespace game {
	Crew::Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::CREW;
		z_layer_ = 5;
		SetScale(glm::vec2(0.1f, 0.1f));

		alive_ = true;
		health_ = 1.0f;
		efficiency_ = 1.0f;
	}

	void Crew::Update(double delta_time) {
		if (health_ <= 0.0f) {
			alive_ = false;
		}
		if (alive_) {
			efficiency_ = health_;
			color_modifier_ = glm::vec3(health_);
		}
		GameObject::Update(delta_time);
	}
}