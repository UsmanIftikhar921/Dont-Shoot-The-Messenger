#include "spinner.h"
#include <iostream>

namespace game {
	Spinner::Spinner(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture)
	{
		type_ = ObjType::SPINNER;
	}

	void Spinner::Update(double delta_time, GuiState* gui_state) {
		rotation_ += 7.0f * delta_time;
		orbit_rotation_ += 1.0f * delta_time;
	}
}