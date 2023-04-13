#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"
#include "collidable.h"

namespace game {

	class Enemy : public Collidable {
	public:
		Enemy(const glm::vec3& positiong, Geometry* geom, Shader* shader);

		void Update(double delta_time, GuiState* gui_state) override;

		// Getters
		inline GameObject* GetTarget(void) { return target_; }

		// Setters
		inline void SetTarget(GameObject* target) { target_ = target; }

		void ChaseTarget(void);

		void OrbitTarget(float orbit_distance, int orbit_direction); // -1 = clockwise, 1 = counter-clockwise


	protected:
		GameObject* target_;



	};

}





#endif
