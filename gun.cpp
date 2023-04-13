#include "gun.h"


namespace game {

	/*
		Player inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Gun::Gun(const glm::vec3& position, Geometry* geom, Shader* shader, GunType gun_type)
		: Task(position, geom, shader, 1.0f) {
		texture_ = GameObject::textures.GetTexture(14);
		type_ = GUN;
		gun_type_ = gun_type;
	}

	Gun::~Gun() {
	}

	void Gun::Update(double delta_time) {
		srand(delta_time);
		Task::Update(delta_time);
	}

	void Gun::PerformTask(float efficiency_modifier) {
		if (!ready_) {
			return;
		}
		Fire();
		ready_ = false;
		cooldown_timer_ = completion_time_;
		efficiency_modifier_ = efficiency_modifier;
	}


	void Gun::Fire() {
		glm::vec3 bullet_pos = GetGlobalPosition();
		float bullet_rot = GetGlobalRotation();
		glm::vec3 bullet_bearing = GetGlobalBearing();
		
		glm::vec3 gun_vel = GetGlobalVelocity();
		
		if (gun_type_ == STANDARD) {
			Bullet* bullet = new Bullet(bullet_pos, geometry_, shader_);
			bullet->SetVelocity((bullet_bearing * bullet->GetSpeed()) + gun_vel);
			bullet->SetRotation(bullet_rot);

			// Add the bullet to the game
			GameObject::GetScene()->AddChild(bullet);

		}
		else if (gun_type_ == HEAVY) {

			// Generate random number between 1 and -1

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 50);
			float rand_rot = ((float)dist6(rng) / 50) - 0.5f;
			bullet_bearing = glm::vec3(glm::rotate(glm::mat4(1.0f), rand_rot, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(bullet_bearing, 1.0f));

			BigBullet* bullet = new BigBullet(bullet_pos, geometry_, shader_);
			bullet->SetVelocity((bullet_bearing * bullet->GetSpeed()) + gun_vel);
			bullet->SetRotation(bullet_rot);

			// Add the bullet to the game
			GameObject::GetScene()->AddChild(bullet);
		}

		

	}

} // namespace game