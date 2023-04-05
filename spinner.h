#ifndef SPINNER_H_
#define SPINNER_H_

#include "game_object.h"

namespace game {
	class Spinner : public GameObject
	{
	public:
		Spinner(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
		
		void Update(double delta_time, GuiState* gui_state) override;


	};
}

#endif