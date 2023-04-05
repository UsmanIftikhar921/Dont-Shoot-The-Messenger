#ifndef AIRSHIP_SEGMENT_H_
#define AIRSHIP_SEGMENT_H_

#include "game_object.h"
#include "crew.h"
#include <vector>

namespace game {
	class AirshipSegment : public GameObject
	{
	public:
		AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time, GuiState* gui_state) override;

		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) override;

		void UpdateCrew(double delta_time);
		bool AssignCrew(Crew* crew);
		bool UnassignCrew(Crew* crew);
		
	protected:
		// Crew 
		int max_crew_;
		std::vector<Crew*> assigned_crew_;
		

	};
}

#endif