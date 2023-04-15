#include "powerup.h"

namespace game {
	Powerup::Powerup(glm::vec3 position, Geometry* geom, Shader* shader) : Collidable(position, geom, shader, NULL) {
	}
}