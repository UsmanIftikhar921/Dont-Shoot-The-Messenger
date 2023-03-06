#include "crew.h"

namespace game {
	Crew::Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::CREW;
	}

	void Crew::Update(double delta_time) {
		GameObject::Update(delta_time);
	}
}