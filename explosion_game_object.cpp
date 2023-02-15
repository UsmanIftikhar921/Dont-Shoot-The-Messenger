#include "explosion_game_object.h"

namespace game {
	
	ExplosionGameObject::ExplosionGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float duration)
		: GameObject(position, geom, shader, texture) {
		time_remaining_ = duration;
		collidable_ = false;
		type_ = EXPLOSION;
	}
	
	void ExplosionGameObject::Update(double delta_time) {
		time_remaining_ -= delta_time;
		if (time_remaining_ <= 0.0) {
			destroyed_ = true;
		}
	}

	bool ExplosionGameObject::RegisterHit() {
		return false;
	}

}