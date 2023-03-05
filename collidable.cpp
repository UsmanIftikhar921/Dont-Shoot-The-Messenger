#include "collidable.h"

namespace game {
	Collidable::Collidable(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : GameObject(position, geom, shader, texture)
	{
		type_ = ObjType::COLLIDABLE;
		collision_box_ = NULL; // InitCollisionBox will set in InitCollisionBox (can't be done in constructor because of issues with type_ in derrived classes)
	}

	void Collidable::InitCollisionBox(float collision_radius, Geometry* geom, Shader* shader, GLuint texture) {
		collision_box_ = new CollisionBox(glm::vec3(0.0f), collision_radius, type_, unique_id_, geom, shader, texture);
		AddChild(collision_box_);
	}

	void Collidable::Update(double delta_time) {		
		dbg_render_red_ = false;
		
		GameObject::Update(delta_time);

		// Must be called after GameObject::Update() so that the collision box (child) is updated
		HandleCollisions();
	}
	
	void Collidable::HandleCollisions(void) {
		int collisions = collision_box_->GetCollisions().size();

		int collisions_to_handle = collision_box_->GetCollisions().size();
		for (int i = 0; i < collision_box_->GetCollisions().size(); i++) {
			CollisionEvent event = collision_box_->GetCollisions().at(i);
			HandleCollisionEvent(event);
		}
	}

	void Collidable::HandleCollisionEvent(CollisionEvent& event) {
		
		switch (event.type) {
		case ObjType::PLAYER:
			dbg_render_red_ = true;
			break;
		}
	}
}