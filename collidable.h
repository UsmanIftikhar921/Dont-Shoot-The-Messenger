#ifndef COLLIDABLE_H_
#define COLLIDABLE_H_

#include "game_object.h"
#include "collision_box.h"

namespace game {
	class Collidable : public GameObject
	{
	public:
		Collidable(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void InitCollisionBox(glm::vec3 position, float collision_radius);
		void InitCollisionBox(glm::vec3 position, float width, float height);

		void Update(double delta_time) override;

		void HandleCollisions(void);

		virtual void HandleCollisionEvent(CollisionEvent& event);

		virtual void HandleNewCollisionEvent(CollisionEvent& event);
		

	protected:
		CollisionBox * collision_box_;
	};
}

#endif