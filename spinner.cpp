#include "spinner.h"

namespace game {
	Spinner::Spinner(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture)
	{
		type_ = ObjType::SPINNER;
	}

	void Spinner::Update(double delta_time) {
		rotation_ += 7.0f * delta_time;
		orbit_rotation_ += 1.0f * delta_time;
	}
}