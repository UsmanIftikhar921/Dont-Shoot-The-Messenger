#include "powerup.h"

namespace game {
	Powerup::Powerup(glm::vec3 position, Geometry* geom, Shader* shader) : Collidable(position, geom, shader, NULL) {
		texture_ = GameObject::textures.GetTexture(34);
		type_ = ObjType::POWERUP;
	}

	void Powerup::HandleCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case AIRSHIP_SEGMENT:
			destroy_ = true;
		}
	}
}