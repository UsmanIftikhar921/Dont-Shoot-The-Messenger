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

	enum CollisionShape {
		CIRCLE,
		RECTANGLE
	};

	class CollisionBox : public GameObject {
	public:
		// Circle collision box
		CollisionBox(const glm::vec3& position, float radius, ObjType parent_type, int parent_id, Geometry* geom, Shader* shader);

		// Rectangle collision box
		CollisionBox(const glm::vec3& position, float width, float height, ObjType parent_type, int parent_id, Geometry* geom, Shader* shader);
		
		~CollisionBox();
		
		void Update(double delta_time, GuiState* gui_state) override;

		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) override;

		// Getters and Setters
		inline float GetRadius(void) { return radius_; }
		inline void SetRadius(float radius) { radius_ = radius; }

		inline float GetWidth(void) { return width_; }
		inline void SetWidth(float width) { width_ = width; }
		inline float GetHeight(void) { return height_; }
		inline void SetHeight(float height) { height_ = height; }
		inline void SetWidthHeight(float width, float height) { width_ = width; height_ = height; }

		inline CollisionShape GetShape(void) { return shape_; }

		inline std::vector<CollisionEvent> GetCollisions(void) { return collisions_; }
		inline std::vector<CollisionEvent> GetNewCollisions(void) { return new_collisions_;  }
		
		void CheckCollision(CollisionBox* other);

		
		// Static methods
		
		// Check for collisions between all collision boxes
		// This should be called once per frame
		
		static void ProcessCollisions() {
			for (int i = 0; i < collision_boxes_.size(); i++) {
				collision_boxes_.at(i)->collisions_this_frame_.clear();
				for (int j = 0; j < collision_boxes_.size(); j++) {
					if (i != j) collision_boxes_.at(i)->CheckCollision(collision_boxes_.at(j));
				}
			}
		}

		static std::string GetCollisionEventDbgString(CollisionEvent event) {
			return "(type: " + GetEnumName(event.type) + ", id: " + std::to_string(event.id) + ", durration: " + std::to_string(event.duration) + ")";
		}

	protected:
		ObjType parent_type_;
		int parent_id_;
		
		// All collisions, both those that are new this frame and those that have been going on for a while
		std::vector<CollisionEvent> collisions_;

		// Collisions that just started this frame
		std::vector<CollisionEvent> new_collisions_;
		
		// All collision events that occurred this frame (durration not updated)
		std::vector<CollisionEvent> collisions_this_frame_;

		void UpdateCollisions(double delta_time);

		// Called at the end of the frame to reset things for the next frame
		void PostUpdateCleanup(void);

		float radius_;
		float width_;
		float height_;

		CollisionShape shape_;
		
		// Static members
		static std::vector<CollisionBox*> collision_boxes_;


	};
}

#endif

