#include "collidable_game_object.h"

namespace game {
	CollidableGameObject::CollidableGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float collision_radius) : GameObject(position, geom, shader, texture)
	{
		collision_box_ = new CollisionBox(position, geom, shader, NULL, collision_radius, type_, unique_id_);
		children_.push_back(collision_box_);
	}

	void CollidableGameObject::Update(double delta_time) {		
		dbg_render_red_ = false;
		HandleCollisions();
		
		GameObject::Update(delta_time);
	}
	
	void CollidableGameObject::HandleCollisions(void) {
		for (int i = 0; i < collision_box_->GetCollisions()->size(); i++) {
			CollisionEvent event = *collision_box_->GetCollisions()->at(i);
			HandleCollisionEvent(event);
		}
	}

	void CollidableGameObject::HandleCollisionEvent(CollisionEvent& event) {
		switch (event.type) {

		case ObjType::COLLIDABLE:
			dbg_render_red_ = true;
			break;

		}
	}
}