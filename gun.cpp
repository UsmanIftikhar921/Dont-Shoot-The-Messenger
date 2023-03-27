#include "gun.h"

namespace game {

	/*
		Player inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Gun::Gun(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture) {
		type_ = GUN;
	}

	// Update function for moving the player object around
	void Gun::Update(double delta_time) {

		// Decrease cooldown timer
		if (can_fire_ == false) { cooldown_timer_ -= delta_time; }

		if (cooldown_timer_ <= 0) {
			can_fire_ = true;
			cooldown_timer_ = fire_rate_;
		}

		// Call the parent's update method to move the object in standard way, if desired
		GameObject::Update(delta_time);
	}

	void Gun::Fire() {
		if (can_fire_ == false) return;

		Bullet* bullet = new Bullet(global_position_, geometry_, shader_, GameObject::textures.GetTexture("bullet"));
		bullet->SetPosition(glm::vec3(2.0f, 2.0f, 0.0f));
		bullet->SetRotation(rotation_);
		bullet->SetScale(glm::vec2(0.25f, 0.25f));
		bullet->SetVelocity(GetBearing() * 3.0f);
		bullet->InitCollisionBox(0.25f);
		can_fire_ = false;		 
		GameObject* scene = id_map_[0];
		scene->AddChild(bullet);
		return;
	}

} // namespace game