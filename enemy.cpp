#include "enemy.h"

namespace game {

	ChaserEnemy::ChaserEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : Collidable(position, geom, shader, texture) {
		type_ = ENEMY;
		max_velocity_ = 1.0f;
	}

	// Update function for moving the player object around
	void ChaserEnemy::Update(double delta_time) {

		// Update target based on mouse position
		target_ = glm::vec3(GetMousePos(),0.0f);

		ChangeState(delta_time);

		Collidable::Update(delta_time);
	}

	void ChaserEnemy::HandleCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case ObjType::COLLIDABLE:
			dbg_render_red_ = true;
			break;
		}
	}

	glm::vec2 ChaserEnemy::GetMousePos() {
		double xpos, ypos;
		glfwGetCursorPos(window_, &xpos, &ypos);

		// Make sure the mouse position is in the range of the window
		int width, height;
		glfwGetWindowSize(window_, &width, &height);

		if (xpos < 0) { xpos = 0; }
		if (xpos > width) { xpos = width; }
		if (ypos < 0) { ypos = 0; }
		if (ypos > height) { ypos = height; }

		// Set the mouse position to be in the range of -3.5 to 3.5
		xpos = (xpos / width) * 7.0f - 3.5f;
		ypos = - ( (ypos / height) * 7.0f - 3.5f) ;

		return glm::vec2(xpos, ypos);
	}

	void ChaserEnemy::HomeInOnPoint(glm::vec3& target, float delta_time) {
		if (state_ != EnemyState::CHASING) return;

		glm::vec2 curr_pos = glm::vec2(position_.x, position_.y);
		glm::vec2 target_pos = glm::vec2(target.x, target.y);

		glm::vec2 curr_vel = glm::vec2(velocity_.x, velocity_.y);
		glm::vec2 target_vel = glm::vec2(0.0f, 0.0f);

		float deltaX = target_pos.x - curr_pos.x;
		float deltaY = target_pos.y - curr_pos.y;

		float dist = glm::sqrt(deltaX * deltaX + deltaY * deltaY);

		if (dist < 0.01) {
			acceleration_.x = 0.0f;
			acceleration_.y = 0.0f;
			velocity_.x = target_vel.x;
			velocity_.y = target_vel.y;
			position_.x = target_pos.x;
			position_.y = target_pos.y;
			state_ = EnemyState::IDLE;
			return;
		}

		float velMagSq = glm::length(curr_vel) * glm::length(curr_vel);

		float decelDist = (velMagSq) / (2 * max_velocity_);

		if (dist >= decelDist) {
			acceleration_ = glm::vec3(glm::normalize(glm::vec2(deltaX, deltaY)) * max_velocity_, 0.0f);
			velocity_ += glm::normalize(target_ - position_);
		}
		else {
			acceleration_ = glm::vec3(glm::normalize(glm::vec2(deltaX, deltaY)) * -max_velocity_, 0.0f);
			velocity_ -= glm::normalize(velocity_);
		}
	}

	void ChaserEnemy::OrbitAroundTarget(glm::vec3& target, float radius, double delta_time) {
		if (state_ != EnemyState::ORBITING) return;

		// Calculate the angle to orbit at
		float angle = glm::atan(position_.y - target.y, position_.x - target.x);

		// Calculate the new position
		position_.x = target.x + radius * glm::cos(angle);
		position_.y = target.y + radius * glm::sin(angle);

		// Calculate the new velocity
		velocity_.x = -radius * glm::sin(angle);
		velocity_.y = radius * glm::cos(angle);

		// Calculate the new acceleration (broken rn)
		//acceleration_.x = -radius * glm::cos(angle);
		//acceleration_.y = -radius * glm::sin(angle);

	}

	void ChaserEnemy::ChangeState(float delta_time) {
		switch (state_) {
			case EnemyState::IDLE:
				if (target_ != position_) { state_ = EnemyState::CHASING; }
				break;

			case EnemyState::CHASING:
				HomeInOnPoint(target_, delta_time);
				if (glm::distance(position_, target_) < 1.0f) { state_ = EnemyState::ORBITING; }
				break;

			case EnemyState::ORBITING:
				OrbitAroundTarget(target_, 1.0f, delta_time);
				break;
		}
	}


	//bool Enemy::canShoot() { return time_since_last_shot_ > time_between_shots_; }

	// INTENDED USE:
	// PROVIDE THE ADDRESS OF A BULLET OBJECT THAT HAS AN INITIALIZED TEXTURE, GEOMETRY, AND SHADER
	// YOU WILL GET A BULLET OBJECT BACK WITH THE POSITION AND VELOCITY SET	
	//void Player::initBullet(Bullet** bullet, glm::vec3 position, glm::vec3 velocity, float rotation) {
	//	Bullet* changeBullet = *bullet;
	//	changeBullet->SetPosition(position);
	//	changeBullet->SetVelocity(velocity);
	//	changeBullet ->SetRotation(rotation);
	//	time_since_last_shot_ = 0.0f;
	//	return;
	//}

} // namespace game