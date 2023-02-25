#ifndef COLLIDABLE_GAME_OBJECT_H_
#define COLLIDABLE_GAME_OBJECT_H_

#include "game_object.h"
#include "collision_box.h"

namespace game {
	class CollidableGameObject : public GameObject
	{
	public:
		CollidableGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void InitCollisionBox(float collision_radius=0.3);

		void Update(double delta_time) override;
		
		void HandleCollisions(void);

		virtual void HandleCollisionEvent(CollisionEvent& event);
		

	protected:
		CollisionBox * collision_box_;
	};
}

#endif