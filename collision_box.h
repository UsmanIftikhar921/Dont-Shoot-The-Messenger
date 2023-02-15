#ifndef COLLISION_BOX_H_
#define COLLISION_BOX_H_

#include "game_object.h"
#include <vector>

namespace game {

	struct CollisionEvent {
		ObjType type;
		float duration;
		int id;
	};
	
	class CollisionBox : public GameObject {
	public:
		CollisionBox(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float radius, ObjType parent_type, int parent_id);
		
		void Update(double delta_time) override;

		// Getters and Setters
		inline float GetRadius(void) { return radius_; }

		inline std::vector<CollisionEvent*> * GetCollisions(void) { return collisions_; }
		void CheckCollision(CollisionBox* other);

		// Static methods
		
		// Check for collisions between all collision boxes
		// This should be called once per frame
		static void ProcessCollisions() {
			for (int i = 0; i < collision_boxes_.size(); i++) {
				for (int j = i + 1; j < collision_boxes_.size(); j++) {
					collision_boxes_.at(i)->CheckCollision(collision_boxes_.at(j));
				}
			}
		}

	protected:
		ObjType parent_type_;
		int parent_id_;
		
		// All collisions, both those that are new this frame and those that have been going on for a while
		std::vector<CollisionEvent*> * collisions_;
		
		// Collisions that have just started this frame (Won't be correct until after UpdateCollisions() is called in Update)
		std::vector<CollisionEvent*> * collisions_this_frame_;

		void UpdateCollisions(double delta_time);

		float radius_;
		
		// Static members
		static std::vector<CollisionBox*> collision_boxes_;


	};
}

#endif

