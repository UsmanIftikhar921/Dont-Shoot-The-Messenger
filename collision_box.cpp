#include "collision_box.h"

namespace game {

	std::vector<CollisionBox*> CollisionBox::collision_boxes_;
	
		
	CollisionBox::CollisionBox(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float radius, ObjType parent_type, int parent_id)
		: GameObject(position, geom, shader, texture) {
		radius_ = radius;
		parent_type_ = parent_type;
		parent_id_ = parent_id;
		
		collisions_ = new std::vector<CollisionEvent*>();
		collisions_this_frame_ = new std::vector<CollisionEvent*>();

		// add this collision box to the static list of collision boxes
		collision_boxes_.push_back(this);
	}

	void CollisionBox::Update(double delta_time) {
		UpdateCollisions(delta_time);
		
		
		GameObject::Update(delta_time);
	}
	
	void CollisionBox::UpdateCollisions(double delta_time) {
		std::vector<CollisionEvent*>* new_collisions = new std::vector<CollisionEvent*>();
		for (int i = 0; i < collisions_this_frame_->size(); i++) {

			// vector that will replace collisions_
			CollisionEvent* new_col = collisions_this_frame_->at(i);
			// check if this collision is already in collisions_
			for (int j = 0; j < collisions_->size(); j++) {
				CollisionEvent* old_col = collisions_->at(j);

				// if the collision is already in collisions_, update the durration
				if (new_col->id == old_col->id) {
					new_col->duration = old_col->duration + delta_time;

					// remove new_col from collisions_this_frame_
					collisions_this_frame_->erase(collisions_this_frame_->begin() + i);
					i--;

					// remove the old collision from collisions_ so that it isn't checked again
					collisions_->erase(collisions_->begin() + j);
					j--;
				}

				// add the new collision to the vector that will replace collisions_
				new_collisions->push_back(new_col);
			}
		}
		// replace collisions_ with the new vector 
		collisions_ = new_collisions;

	}

	void CollisionBox::CheckCollision(CollisionBox* other) {
		if (other->GetRadius() + radius_ > glm::distance(position_, other->GetPosition())) {
			// Collision detected
			CollisionEvent* new_event = new CollisionEvent();
			new_event->type = other->parent_type_;
			new_event->duration = 0.0f;
			new_event->id = other->parent_id_;
			collisions_this_frame_->push_back(new_event);
		}
	}

}