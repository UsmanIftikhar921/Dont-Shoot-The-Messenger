#include "big_bullet.h"

namespace game {

	/*
		Player inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	BigBullet::BigBullet(const glm::vec3& position, Geometry* geom, Shader* shader, bool friendly)
		: Bullet(position, geom, shader, friendly) {
		
		if (friendly)
			type_ = BIGBULLET_FRIENDLY;
		else {
			type_ = BIGBULLET_ENEMY;
		}

		texture_ = GameObject::textures.GetTexture(18);
		speed_ = 0.5f;
		scale_ = glm::vec2(0.2f, 0.2f);
		rotation_speed_ = 2.0f;
	}

	// Update function for moving the player object around
	void BigBullet::Update(double delta_time) {
		rotation_ += rotation_speed_ * delta_time;
		Bullet::Update(delta_time);
	}

} // namespace game
