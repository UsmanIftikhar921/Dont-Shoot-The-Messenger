#include "enemy.h"

namespace game {
	Enemy::Enemy(const glm::vec3& position, Geometry* geom, Shader* shader) : Collidable(position, geom, shader, NULL) {
		target_ = nullptr;
		texture_ = GameObject::textures.GetTexture(2);
	}
	void Enemy::Update(double delta_time) {
		if (target_ != nullptr) {
			OrbitTarget(5.0, 1.0);
		}

		std::cout << "Enemy:" << std::endl;
		std::cout << "	Acceleration: " << acceleration_.x << ", " << acceleration_.y << std::endl;
		std::cout << "	Velocity: " << velocity_.x << ", " << velocity_.y << std::endl << std::endl << std::endl;


		Collidable::Update(delta_time);
	}

	void Enemy::ChaseTarget(void) {
		if (target_ != nullptr) {
			// Get target position
			glm::vec3 target_position = target_->GetPosition();

			// Get direction to target
			glm::vec3 direction = target_position - position_;

			// Normalize direction
			direction = glm::normalize(direction);

			// Set acceleration
			acceleration_ = direction * 2.0f;
		}
	}

	void Enemy::OrbitTarget(float orbit_distance, int orbit_direction) {
		glm::vec3 target_position = target_->GetPosition();

		// Get direction to target
		glm::vec3 direction = target_position - position_;

		// Normalize direction
		direction = glm::normalize(direction);

		// Get angle to target
		float angle = glm::atan(direction.y, direction.x);

		// Set acceleration to orbit
		acceleration_ = glm::vec3(orbit_direction * -glm::sin(angle), orbit_direction * glm::cos(angle), 0.0f) * 2.0f;
		


	}
}