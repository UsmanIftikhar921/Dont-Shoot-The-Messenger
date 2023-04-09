#include "enemy.h"

namespace game {

	ChaserEnemy::ChaserEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : Collidable(position, geom, shader, texture) {
		type_ = ENEMY;
	}

	// Update function for moving the player object around
	void ChaserEnemy::Update(double delta_time) {

		// Update time since last shot
		//if(time_since_last_shot_ < time_between_shots_) time_since_last_shot_ += delta_time;

		// Update target based on mouse position
		target_ = glm::vec3(GetMousePos(),0.0f);
		
		// Update position
		ChaseTarget(delta_time);

		Collidable::Update(delta_time);
	}

	void ChaserEnemy::HandleCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case ObjType::COLLIDABLE:
			dbg_render_red_ = true;
			break;
		}
	}

	void ChaserEnemy::ChaseTarget(double delta_time) {
		// Accelerate when not at max speed
		if (glm::length(velocity_) < max_speed_) {
			velocity_ += acceleration_ * glm::normalize(target_ - position_);
		}
		// Decelerate when at max speed
		else {
			velocity_ -= acceleration_ * glm::normalize(velocity_);
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