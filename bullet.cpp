#include "bullet.h"

namespace game {

/*
	Player inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

	Bullet::Bullet(const glm::vec3& position, Geometry* geom, Shader* shader)
		: GameObject(position, geom, shader, NULL){
	type_ = BULLET;
	texture_ = GameObject::textures.GetTexture(13);
	speed_ = 3.0f;
	scale_ = glm::vec2(0.2f, 0.2f);
	
}

// Update function for moving the player object around
void Bullet::Update(double delta_time) {
	GameObject::Update(delta_time);
}

} // namespace game




//bool Bullet::RayCircleCollision(glm::vec2 rayOrigin, glm::vec2 rayVector, glm::vec2 circleCenter, float radius, float &t1, float &t2){
//	// Find a, b and c
//	glm::vec2 distance_between_origins = rayOrigin - circleCenter;
//	float a = glm::dot(rayVector, rayVector);
//	float b = 2.0f * glm::dot(rayVector, distance_between_origins); 
//	float c = glm::dot(distance_between_origins, distance_between_origins) - radius*radius;
//
//	// Calculate delta
//	float delta = b*b - 4.0*a*c;
//
//	// If delta is negative, no intersection (return false)
//	if (delta < 0.0f){ return false; }
//	
//	// Otherwise, calculate t1 and t2 (return true)
//	t1 = (-b + sqrt(delta))/(2*a);
//	t2 = (-b - sqrt(delta))/(2*a);
//	return true;
//}


//int Bullet::CheckForCollision(std::vector<GameObject*> obj) {
//
//	// Convert velocity to a vec2
//	glm::vec2 velocity = glm::vec2(velocity_.x, velocity_.y);
//	float t1, t2;
//
//	// Loop through all objects
//	for (int i = 0; i < obj.size(); i++) {
//		// Only check intersections with collidable objects
//		if (obj[i]->GetType() == COLLIDABLE) {
//			// Get the enemy center and radius
//			glm::vec3 pos = obj[i]->GetPosition();
//			glm::vec2 C = glm::vec2(pos.x, pos.y);
//
//			float radius = obj[i]->GetScale().x;
//
//			if (RayCircleCollision(start_, velocity, C, radius, t1, t2)) {
//				if ((t1 > last_time_since_fire_) && (t1 <= time_since_fire_)) { return i; }
//				if ((t2 > last_time_since_fire_) && (t2 <= time_since_fire_)) { return i; }
//			}
//		}
//	}
//	return -1;
//}
