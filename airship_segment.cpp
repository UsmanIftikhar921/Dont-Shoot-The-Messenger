#include "airship_segment.h"

namespace game {
	AirshipSegment::AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture) {
		type_ = ObjType::AIRSHIP_SEGMENT;
	}

	void AirshipSegment::Update(double delta_time) {
		GameObject::Update(delta_time);
	}
}