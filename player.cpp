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

	// Special player updates go here

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



} // namespace game
