#include "airship_segment.h"

namespace game {
	AirshipSegment::AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::AIRSHIP_SEGMENT;
		z_layer_ = 10;
		max_crew_ = 2;
	}

	void AirshipSegment::Update(double delta_time, GuiState* gui_state) {
		GameObject::Update(delta_time, gui_state);
	}

	void AirshipSegment::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) {
		GameObject::Render(view_matrix, parent_matrix, parent_scale_matrix, current_time);
	}
}