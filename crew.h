#ifndef CREW_H_
#define CREW_H_

#include "game_object.h"

namespace game {
	class Crew : public GameObject
	{
	public:
		Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time, GuiState* gui_state) override;

//		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) override;


	protected:
		bool alive_;
		float health_;
		float efficiency_;
	};

}

#endif