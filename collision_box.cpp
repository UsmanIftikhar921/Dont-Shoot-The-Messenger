#include "collision_box.h"

namespace game {

	std::vector<CollisionBox*> CollisionBox::collision_boxes_;
	
		
	CollisionBox::CollisionBox(const glm::vec3& position, float radius, ObjType parent_type, int parent_id, Geometry* geom, Shader* shader, GLuint texture) 
		: GameObject(position, geom, shader, texture) {
		radius_ = radius;
		parent_type_ = parent_type;
		parent_id_ = parent_id;
		type_ = ObjType::COLLISION_BOX;

		// add this collision box to the static list of collision boxes
		collision_boxes_.push_back(this);		
	}
	
	CollisionBox::~CollisionBox() {
		// remove this collision box from the static list of collision boxes
		for (int i = 0; i < collision_boxes_.size(); i++) {
			if (collision_boxes_.at(i) == this) {
				collision_boxes_.erase(collision_boxes_.begin() + i);
				break;
			}
		}
	}

	void CollisionBox::Update(double delta_time, GuiState* gui_state) {

		UpdateCollisions(delta_time);
		
		GameObject::Update(delta_time, gui_state);
		
		PostUpdateCleanup();
	}

	void CollisionBox::UpdateCollisions(double delta_time) {
		// vector that will replace collisions_
		std::vector<CollisionEvent> collisions_updated;

		for (int i = 0; i < collisions_this_frame_.size(); i++) {
			
			CollisionEvent collision = collisions_this_frame_.at(i);

			// Check if collision is ongoing, if so update the duration
			bool collision_is_ongoing = false;
			for (int j = 0; j < collisions_.size(); j++) {
				CollisionEvent ongoing_collision = collisions_.at(j);
				
				if (collision.id == ongoing_collision.id) {

					collision_is_ongoing = true;
					collision.duration = ongoing_collision.duration + delta_time;

					// Erase ongoing collision from collisions_ to prevent redundant checks of collisions this frame
					collisions_.erase(collisions_.begin() + j);

					break;
				}

			}

			// If collision is ongoing, add it to the updated collisions vector
			if (!collision_is_ongoing) {
				new_collisions_.push_back(collision);
			}
			collisions_updated.push_back(collision);


		}

		// replace collisions_ with the new vector 
		collisions_ = collisions_updated;


	}

	void CollisionBox::PostUpdateCleanup(void) {
		// clear collisions_this_frame_
		collisions_this_frame_.clear();
	}

	void CollisionBox::CheckCollision(CollisionBox* other) {
		float distance = glm::abs(glm::distance(global_position_, other->GetGlobalPosition()));
		if (radius_ > distance) {
			// Collision detected
			CollisionEvent new_event;

			new_event.type = other->parent_type_;
			new_event.id = other->parent_id_;
			new_event.duration = 0.0f;
			collisions_this_frame_.push_back(new_event);			
		}
	}

}