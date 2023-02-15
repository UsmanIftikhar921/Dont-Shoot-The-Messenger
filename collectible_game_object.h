#ifndef COLLECTIBLE_GAME_OBJECT_H_
#define COLLECTIBLE_GAME_OBJECT_H_

#include "game_object.h"

namespace game {
	class CollectibleGameObject : public GameObject
	{
	public:
		CollectibleGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
		CollectibleGameObject(void);

		void RegisterPickup(void);
	};
}


#endif