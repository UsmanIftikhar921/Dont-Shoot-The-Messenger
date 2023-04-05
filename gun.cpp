#include "gun.h"

namespace game {

	/*
		Player inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Gun::Gun(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture) {
		texture_ = texture;
		type_ = GUN;
		fire_rate_ = 1.0f;
		cooldown_ = 0.0f;
		fire_state_ = READY;
	}

	Gun::~Gun() {
	}

	void Gun::Update(double delta_time) {
		switch (fire_state_) {
		case COOLDOWN:
			cooldown_ -= delta_time;
			if (cooldown_ <= 0.0f) {
				fire_state_ = READY;
		}
			break;
		case READY:
			break;
		case FIRING:
			cooldown_ = fire_rate_;
			fire_state_ = COOLDOWN;
			Fire();
		}
		GameObject::Update(delta_time);
	}
	bool Gun::TryFire() {
		if (fire_state_ == READY) {
			fire_state_ = FIRING;
			return true;
		}
		return false;
	}

	void Gun::Fire() {
		glm::vec3 bullet_pos = GetGlobalPosition();
		float bullet_rot = GetGlobalRotation();
		glm::vec3 bullet_bearing = glm::vec3(-sin(bullet_rot), cos(bullet_rot), 0.0f);
		
		Bullet* bullet = new Bullet(bullet_pos, geometry_, shader_);
		bullet->SetVelocity(bullet_bearing * bullet->GetSpeed());
		bullet->SetRotation(bullet_rot);

		// Add the bullet to the game
		GameObject::GetScene()->AddChild(bullet);
		

	}

} // namespace game