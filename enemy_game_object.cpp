#include "enemy_game_object.h"

namespace game {

	EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture) {
		type_ = ENEMY;
		collidable_ = true;
	}

	bool EnemyGameObject::RegisterHit(void) {
		destroyed_ = true;
		return true;
	}

}