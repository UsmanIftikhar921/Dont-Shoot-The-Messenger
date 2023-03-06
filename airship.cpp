#include "airship.h"

namespace game {

	Airship::Airship(const glm::vec3& position) : GameObject(position) {
		type_ = ObjType::AIRSHIP;
	}

	void Airship::Update(double delta_time)  {
		GameObject::Update(delta_time);
	}

}