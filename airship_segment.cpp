#include "airship_segment.h"

namespace game {
	AirshipSegment::AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::AIRSHIP_SEGMENT;
	}

	void AirshipSegment::Update(double delta_time) {
		GameObject::Update(delta_time);
	}

	void AirshipSegment::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, double current_time) {
		GameObject::Render(view_matrix, parent_matrix, current_time);
	}
}