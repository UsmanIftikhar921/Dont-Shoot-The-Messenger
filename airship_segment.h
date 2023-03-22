#ifndef AIRSHIP_SEGMENT_H_
#define AIRSHIP_SEGMENT_H_

#include "game_object.h"

namespace game {
	class AirshipSegment : public GameObject
	{
	public:
		AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time) override;

		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, double current_time) override;


	};
}

#endif