#include "collision_box.h"
#include <string>

namespace game {

	std::vector<CollisionBox*> CollisionBox::collision_boxes_;

	static glm::vec2 RotateAroundPoint(glm::vec2 point, glm::vec2 origin, float rotation) {
		glm::vec2 rotated_point;
		rotated_point.x = cos(rotation) * (point.x - origin.x) - sin(rotation) * (point.y - origin.y) + origin.x;
		rotated_point.y = sin(rotation) * (point.x - origin.x) + cos(rotation) * (point.y - origin.y) + origin.y;
		return rotated_point;
	}

	static bool RectContainsPoint(glm::vec2 rect_pos, float rect_width, float rect_height, float rect_rotation, glm::vec2 point) {
		glm::vec2 rect_corners[4];

		// Get corners of rect taking into account rotation
		rect_corners[0] = glm::vec2(rect_pos.x - rect_width / 2, rect_pos.y - rect_height / 2);
		rect_corners[1] = glm::vec2(rect_pos.x + rect_width / 2, rect_pos.y - rect_height / 2);
		rect_corners[2] = glm::vec2(rect_pos.x + rect_width / 2, rect_pos.y + rect_height / 2);
		rect_corners[3] = glm::vec2(rect_pos.x - rect_width / 2, rect_pos.y + rect_height / 2);

		for (int i = 0; i < 4; i++) {
			rect_corners[i] = RotateAroundPoint(rect_corners[i], rect_pos, rect_rotation);
		}

		// Check if point is inside rect
		if (point.x > rect_corners[0].x && point.x < rect_corners[1].x && point.y > rect_corners[0].y && point.y < rect_corners[3].y) return true;
		else return false;
	}

	static bool CircleContainsPoint(glm::vec2 circle_pos, float circle_radius, glm::vec2 point) {
		if (glm::distance(circle_pos, point) < circle_radius) return true;
		else return false;
	}


	static bool CircleCircleCollision(CollisionBox* a, CollisionBox* b) {
		float distance = glm::abs(glm::distance(a->GetGlobalPosition(), b->GetGlobalPosition()));
		if (a->GetRadius() > distance) return true;
		else return false;
	}

	static bool RectRectCollision(CollisionBox* a, CollisionBox* b) {
		
		glm::vec2 a_pos = glm::vec2(a->GetGlobalPosition().x, a->GetGlobalPosition().y);
		glm::vec2 b_pos = glm::vec2(b->GetGlobalPosition().x, b->GetGlobalPosition().y);

		float a_rotation = a->GetGlobalRotation();
		float b_rotation = b->GetGlobalRotation();

		glm::vec2 a_corners[4];
		glm::vec2 b_corners[4];

		// Get corners of a taking into account rotation
		a_corners[0] = glm::vec2(a_pos.x - a->GetWidth() / 2, a_pos.y - a->GetHeight() / 2);
		a_corners[1] = glm::vec2(a_pos.x + a->GetWidth() / 2, a_pos.y - a->GetHeight() / 2);
		a_corners[2] = glm::vec2(a_pos.x + a->GetWidth() / 2, a_pos.y + a->GetHeight() / 2);
		a_corners[3] = glm::vec2(a_pos.x - a->GetWidth() / 2, a_pos.y + a->GetHeight() / 2);

		for (int i = 0; i < 4; i++) {
			a_corners[i] = RotateAroundPoint(a_corners[i], a_pos, a_rotation);
		}

		// Get corners of b taking into account rotation
		b_corners[0] = glm::vec2(b_pos.x - b->GetWidth() / 2, b_pos.y - b->GetHeight() / 2);
		b_corners[1] = glm::vec2(b_pos.x + b->GetWidth() / 2, b_pos.y - b->GetHeight() / 2);
		b_corners[2] = glm::vec2(b_pos.x + b->GetWidth() / 2, b_pos.y + b->GetHeight() / 2);
		b_corners[3] = glm::vec2(b_pos.x - b->GetWidth() / 2, b_pos.y + b->GetHeight() / 2);

		for (int i = 0; i < 4; i++) {
			b_corners[i] = RotateAroundPoint(b_corners[i], b_pos, b_rotation);
		}

		glm::vec2 projection_axes[4];
		projection_axes[0] = glm::vec2(a_corners[1].x - a_corners[0].x, a_corners[1].y - a_corners[0].y);
		projection_axes[1] = glm::vec2(a_corners[2].x - a_corners[1].x, a_corners[2].y - a_corners[1].y);
		projection_axes[2] = glm::vec2(b_corners[1].x - b_corners[0].x, b_corners[1].y - b_corners[0].y);
		projection_axes[3] = glm::vec2(b_corners[2].x - b_corners[1].x, b_corners[2].y - b_corners[1].y);


		bool collision = true;
		for (int i = 0; i < 4; i++) {

			glm::vec2 projection_axis = projection_axes[i];
			float min_a = INFINITY;
			float min_b = INFINITY;
			float max_a = -INFINITY;
			float max_b = -INFINITY;

			for (int j = 0; j < 4; j++) {
				// Project corners of a and b onto the projection axis
				if (glm::dot(a_corners[j], projection_axis) < min_a) min_a = glm::dot(a_corners[j], projection_axis);
				if (glm::dot(a_corners[j], projection_axis) > max_a) max_a = glm::dot(a_corners[j], projection_axis);

				if (glm::dot(b_corners[j], projection_axis) < min_b) min_b = glm::dot(b_corners[j], projection_axis);
				if (glm::dot(b_corners[j], projection_axis) > max_b) max_b = glm::dot(b_corners[j], projection_axis);

			}
			if (max_a < min_b || max_b < min_a) {

				collision = false;
				break;
			}
		}
		
		return collision;

	}

	static bool CircleRectCollision(CollisionBox* a, CollisionBox* b) {
		CollisionBox* circle;
		CollisionBox* rect;
		if (a->GetShape() == CollisionShape::CIRCLE) {
			circle = a;
			rect = b;
		}
		else {
			circle = b;
			rect = a;
		}

		glm::vec2 circle_pos = glm::vec2(circle->GetGlobalPosition().x, circle->GetGlobalPosition().y);
		glm::vec2 rect_pos = glm::vec2(rect->GetGlobalPosition().x, rect->GetGlobalPosition().y);

		float rect_rotation = rect->GetGlobalRotation();

		// NOTE: Ignores case where rect edge intersects circle because I'm lazy
		if (RectContainsPoint(rect_pos, rect->GetWidth() * rect->GetScale().x, rect->GetHeight() * rect->GetScale().y, rect_rotation, circle_pos)) return true;
		
		glm::vec2 rect_corners[4];
		rect_corners[0] = glm::vec2(rect_pos.x - rect->GetWidth() / 2, rect_pos.y - rect->GetHeight() / 2);
		rect_corners[1] = glm::vec2(rect_pos.x + rect->GetWidth() / 2, rect_pos.y - rect->GetHeight() / 2);
		rect_corners[2] = glm::vec2(rect_pos.x + rect->GetWidth() / 2, rect_pos.y + rect->GetHeight() / 2);
		rect_corners[3] = glm::vec2(rect_pos.x - rect->GetWidth() / 2, rect_pos.y + rect->GetHeight() / 2);

		for (int i = 0; i < 4; i++) {
			rect_corners[i] = RotateAroundPoint(rect_corners[i], rect_pos, rect_rotation);
			if (CircleContainsPoint(circle_pos, circle->GetRadius(), rect_corners[i])) return true;
		}
		return false;
		


	}

		
	CollisionBox::CollisionBox(const glm::vec3& position, float radius, ObjType parent_type, int parent_id, Geometry* geom, Shader* shader) 
		: GameObject(position, geom, shader, NULL) {
		
		radius_ = radius;
		width_ = NULL;
		height_ = NULL;
		
		parent_type_ = parent_type;
		parent_id_ = parent_id;
		type_ = ObjType::COLLISION_BOX;
		shape_ = CollisionShape::CIRCLE;

		texture_ = GameObject::textures.GetTexture(3);
		SetZLayer(-3);
		

		// add this collision box to the static list of collision boxes
		collision_boxes_.push_back(this);		
	}

	CollisionBox::CollisionBox(const glm::vec3& position, float width, float height, ObjType parent_type, int parent_id, Geometry* geom, Shader* shader) 
		: GameObject(position, geom, shader, NULL) {
		
		width_ = width;
		height_ = height;
		radius_ = NULL;
		
		parent_type_ = parent_type;
		parent_id_ = parent_id;
		type_ = ObjType::COLLISION_BOX;
		shape_ = CollisionShape::RECTANGLE;

		texture_ = GameObject::textures.GetTexture(17);
		SetZLayer(-3);


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

	void CollisionBox::Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) {
		
		if (shape_ == CollisionShape::CIRCLE) {
			scale_ = glm::vec2(radius_, radius_);
		}
		else if (shape_ == CollisionShape::RECTANGLE) {
			scale_ = glm::vec2(width_, height_);
		}
		GameObject::Render(view_matrix, parent_matrix, glm::mat4(1.0f), current_time);
	}

	void CollisionBox::UpdateCollisions(double delta_time) {
		// vector that will replace collisions_
		std::vector<CollisionEvent> collisions_updated;
		new_collisions_.clear();

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
		bool collision_detected = false;
				
		if (shape_ == other->GetShape()) {
			if (shape_ == CollisionShape::CIRCLE) {
				collision_detected = CircleCircleCollision(this, other);
			}
			else if (shape_ == CollisionShape::RECTANGLE) {
				collision_detected = RectRectCollision(this, other);
			}
		}
		else {
			collision_detected = CircleRectCollision(this, other);
		}

		if (collision_detected) {
			// Collision detected
			CollisionEvent new_event;
			new_event.type = other->parent_type_;
			new_event.id = other->parent_id_;
			new_event.duration = 0.0f;
			
			collisions_this_frame_.push_back(new_event);
			

		}
		
	}



}