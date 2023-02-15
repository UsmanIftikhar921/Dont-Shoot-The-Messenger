#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include "collidable_game_object.h"

namespace game {
	class EnemyGameObject : public GameObject {
	public:
		EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
		bool RegisterHit(void) override;

	protected:

	};

}


#endif