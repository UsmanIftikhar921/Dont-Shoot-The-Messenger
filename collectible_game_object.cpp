#include "collectible_game_object.h"

namespace game {
	
	CollectibleGameObject::CollectibleGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture) {
		type_ = COLLECTIBLE;
		collidable_ = true;
	}

	void CollectibleGameObject::RegisterPickup(void) {
		destroyed_ = true;
	}
	
}