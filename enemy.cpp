#include "enemy.h"

namespace game {
	Enemy::Enemy(const glm::vec3& position, Geometry* geom, Shader* shader, GameObject* target) : Collidable(position, geom, shader, NULL) {
		target_ = target;
		texture_ = GameObject::textures.GetTexture(0);
		max_velocity_ = 8.0f;
		state_ = HOME_IN;
		health_ = 4.0f;

		type_ = ENEMY;


		// debugging
		display_debug_pos_ = false;
		debug_object_ = new GameObject(position, geom, shader, GameObject::textures.GetTexture(3));

	}


	void Enemy::Update(double delta_time, GuiState* gui_state) {
		if (health_ <= 0.0f) {
			destroy_ = true;
			std::cout << "Enemy destroyed! You Win!" << std::endl;

		}

		if (glm::length(velocity_) > 0.0f) {
			float new_rotation = glm::atan(-velocity_.x, velocity_.y);

			// For case of just under and just over zero radians
			float rotation_rot_90 = rotation_ + glm::pi<float>() / 2.0f;
			float new_rotation_rot_90 = new_rotation + glm::pi<float>() / 2.0f;

			// If the rotation change is too drastic, rotate towards it incrementally
			if (glm::abs(new_rotation - rotation_) > 0.02f && glm::abs(rotation_rot_90 - new_rotation_rot_90) > 0.02f ) {
				// Incremental rotation
				rotation_ = glm::mix(rotation_, new_rotation, 0.05f);

			}
			else {
				// Instant rotation
				rotation_ = new_rotation;
			}
		}

		if (target_ != nullptr) {

			glm::vec3 target_pos = target_->GetGlobalPosition();
			target_pos.x += 4.0f;
			float target_rotation = target_->GetGlobalRotation();
			target_pos = glm::vec3(glm::rotate(glm::mat4(1.0f), target_rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(target_pos, 1.0f));

			float angle_to_target = glm::atan(target_pos.y - position_.y, target_pos.x - position_.x);

			StateTransitionHandler(delta_time);
			StateHandler(delta_time);
			
		}

		Collidable::Update(delta_time, gui_state);

	}


	void Enemy::StateTransitionHandler(double delta_time) {
		switch (state_) {
		case CHASE:
			break;
		case HOME_IN:
			break;
		case ORBIT:
			break;
		case WAIT:
			break;
		case FIRE:
			break;
		}
	}

	void Enemy::StateHandler(double delta_time) {
		switch (state_) {
		case CHASE:
			ChaseTarget(delta_time);
			break;
		case HOME_IN:
			HomeInOnPoint(target_pos_, target_->GetVelocity(), delta_time);
			break;
		case ORBIT:
			OrbitTarget(delta_time);
			break;
		case WAIT:
			break;
		case FIRE:
			FireOnTarget(delta_time);
			break;
		}
	}

	// Enter State Functions

	void Enemy::EnterOrbitState(float period, float radius, float initial_orbit, float final_orbit) {
		orbit_initial_angle_ = initial_orbit;
		orbit_final_angle_ = final_orbit;
		orbit_period_ = period;
		orbit_radius_ = radius;
		orbit_completed_ = false;
		orbit_enemy_arrived_ = false;

		t_orbit_ = orbit_initial_angle_ * period;

		state_ = ORBIT;
	}

	void Enemy::EnterFireState(void) {
		glm::vec3 target_pos = target_->GetPosition();
		relative_firing_position_ = position_ - target_pos;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(2, 6);
		total_shots_ = dist(rng);

		shots_fired_ = 0;

		state_ = FIRE;
	}

	// State Functions

	void Enemy::ChaseTarget(float delta_time) {
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

	void Enemy::OrbitTarget(float delta_time) {

		if (!orbit_completed_) {
			t_orbit_ += delta_time;
		}
		
		float current_angle = t_orbit_ / orbit_period_;

		float sign = glm::sign(orbit_period_);
		if (sign * current_angle > sign * orbit_final_angle_) {
			orbit_completed_ = true;
		}

		glm::vec3 target_pos = target_->GetPosition();
		glm::vec3 target_vel = target_->GetVelocity();

		glm::vec3 orbit_pos = glm::vec3(glm::cos(current_angle), glm::sin(current_angle), 0.0f) * orbit_radius_;
		glm::vec3 orbit_vel = glm::vec3(glm::sin(current_angle), glm::cos(current_angle), 0.0f) * orbit_radius_ / orbit_period_;

		glm::vec3 pos = target_pos + orbit_pos;
		glm::vec3 vel = target_vel + orbit_vel;

		if (orbit_completed_) {
			vel = target_vel;
		}


		orbit_enemy_arrived_ = HomeInOnPoint(pos, vel, delta_time);

	}

	void Enemy::FireOnTarget(float delta_time) {
		float angle_to_target = glm::atan(target_pos_.y - position_.y, target_pos_.x - position_.x);
		return;
	}

	bool Enemy::HomeInOnPoint(glm::vec3 target_position, glm::vec3 target_velocity, double delta_time) {

		debug_object_->SetPosition(target_position);


		float max_accel_ = 10.0f;

		glm::vec2 curr_pos = glm::vec2(position_.x, position_.y);
		glm::vec2 target_pos = glm::vec2(target_position.x, target_position.y);

		glm::vec2 curr_vel = glm::vec2(velocity_.x, velocity_.y);
		glm::vec2 target_vel = glm::vec2(target_velocity.x, target_velocity.y);

		float deltaX = target_pos.x - curr_pos.x;
		float deltaY = target_pos.y - curr_pos.y;

		float deltaXNext = (target_pos.x) - (curr_pos.x);
		float deltaYNext = (target_pos.y) - (curr_pos.y);

		float arrived_heuristic = 0.0f;
		float deltaVelX = target_vel.x - curr_vel.x;
		float deltaVelY = target_vel.y - curr_vel.y;
		arrived_heuristic = abs(deltaX) + abs(deltaY) + abs(deltaVelX) + abs(deltaVelY);

		if (arrived_heuristic < 0.4f) {
			acceleration_.x = 0.0f;
			acceleration_.y = 0.0f;
			return true;
		}

		// X component

		float velMagSqX = curr_vel.x * curr_vel.x;
		// Account for target velocity
		velMagSqX -= target_vel.x * target_vel.x;

		float decelDistX = (velMagSqX) / (2 * max_accel_);


		if (abs(deltaX) >= decelDistX) {
			acceleration_.x = max_accel_ * glm::sign(deltaX);
		}
		else {
			acceleration_.x = -max_accel_ * glm::sign(curr_vel.x);
		}

		// Y component

		float velMagSqY = curr_vel.y * curr_vel.y;
		// Account for target velocity
		velMagSqY -= target_vel.y * target_vel.y;

		float decelDistY = (velMagSqY) / (2 * max_accel_);


		if (abs(deltaY) >= decelDistY) {
			acceleration_.y = max_accel_ * glm::sign(deltaY);
		}
		else {
			acceleration_.y = -max_accel_ * glm::sign(curr_vel.y);
		}

		return false;


	}

	void Enemy::HandleCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case BULLET_FRIENDLY:
			dbg_render_red_ = true;
			break;
		case BIGBULLET_FRIENDLY:
			dbg_render_red_ = true;
			break;
		}
	}

	void Enemy::HandleNewCollisionEvent(CollisionEvent& event) {
		switch (event.type) {
		case BULLET_FRIENDLY:
			health_ -= 0.1f;
			break;
		case BIGBULLET_FRIENDLY:
			health_ -= 0.2f;
			break;
		}
	}

}