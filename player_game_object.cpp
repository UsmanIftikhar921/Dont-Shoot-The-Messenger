#include "player_game_object.h"

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture)
	: GameObject(position, geom, shader, texture) {
	hp_ = 3;
	invincible_ = false;
	invincible_timer_ = 0.0f;
	type_ = PLAYER;
	collidable_ = true;
	collectibles_ = 0;
}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {

	// Special player updates go here

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
	if (invincible_) {
		invincible_timer_ -= delta_time;
		if (invincible_timer_ <= 0.0f) {
			invincible_ = false;
		}
	}
	
	if (hp_ <= 0) {
		destroyed_ = true;
	}
}

bool PlayerGameObject::RegisterHit() {
	if (invincible_) {
		return false;
	}
	
	--hp_;
	
	if (hp_ <= 0) {
		return true;
	}
	
	return false;
}

void PlayerGameObject::RegisterCollectible() {
	++collectibles_;
	if (collectibles_ >= 5) {
		invincible_ = true;
		invincible_timer_ = 10.0f;
		collectibles_ = 0;
	}
}

} // namespace game
