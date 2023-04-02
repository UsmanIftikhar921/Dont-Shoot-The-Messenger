#include "crew.h"

namespace game {
	Crew::Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::CREW;
		SetScale(glm::vec2(0.2f, 0.2f));
	}

	void Crew::Update(double delta_time) {
		GameObject::Update(delta_time);
	}
}