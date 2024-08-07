#ifndef FLANKER_H_
#define FLANKER_H_

#include "enemy.h"
#include "game_object.h"
#include "gun.h"

namespace game {

	class Flanker : public Enemy {
	public:
		Flanker(const glm::vec3& positiong, Geometry* geom, Shader* shader, GLuint Texture, GameObject* target);

		void Update(double delta_time, GuiState* gui_state) override;

		void StateTransitionHandler(double delta_time) override;

		void FireOnTarget(float delta_time) override;


	protected:
		Gun* gun_;

	};

}

#endif