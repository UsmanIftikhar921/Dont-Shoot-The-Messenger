#include "player.h"

namespace game {

/*
	Player inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

	Player::Player(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: Collidable(position, geom, shader, texture){
	type_ = PLAYER;
}

// Update function for moving the player object around
void Player::Update(double delta_time) {

	// Update time since last shot
	if(time_since_last_shot_ < time_between_shots_) time_since_last_shot_ += delta_time;

	// Call the parent's update method to move the object in standard way, if desired
	Collidable::Update(delta_time);
}

void Player::HandleCollisionEvent(CollisionEvent& event) {
	switch (event.type) {
	case ObjType::COLLIDABLE:
		dbg_render_red_ = true;
		break;
	}
}

bool Player::canShoot() { return time_since_last_shot_ > time_between_shots_; }

// INTENDED USE: 
// PROVIDE THE ADDRESS OF A BULLET OBJECT THAT HAS AN INITIALIZED TEXTURE, GEOMETRY, AND SHADER 
// YOU WILL GET A BULLET OBJECT BACK WITH THE POSITION AND VELOCITY SET	
void Player::initBullet(Bullet** bullet, glm::vec3 position, glm::vec3 velocity, float rotation) {
	Bullet* changeBullet = *bullet;
	changeBullet->SetPosition(position);
	changeBullet->SetRotation(rotation);
	changeBullet->SetScale(glm::vec2(0.25f, 0.25f));
	changeBullet->SetVelocity(GetBearing() * 3.0f);
	changeBullet->InitCollisionBox(0.125f);
	time_since_last_shot_ = 0.0f;

	GameObject* scene = id_map_[0];
	scene->AddChild(changeBullet);
	return;
}

} // namespace game
