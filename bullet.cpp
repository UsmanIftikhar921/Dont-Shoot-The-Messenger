#include "bullet.h"

namespace game {

/*
	Player inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

	Bullet::Bullet(const glm::vec3& position, Geometry* geom, Shader* shader, bool friendly)
		: Collidable(position, geom, shader, NULL){

		if (friendly) {
			type_ = BULLET_FRIENDLY;
		}
		else {
			type_ = BULLET_ENEMY;
		}

		texture_ = GameObject::textures.GetTexture(13);
		speed_ = 3.0f;
		scale_ = glm::vec2(0.3f, 0.3f);
	
}

// Update function for moving the player object around
void Bullet::Update(double delta_time, GuiState* gui_state) {
	GameObject::Update(delta_time, gui_state);
}

} // namespace game
