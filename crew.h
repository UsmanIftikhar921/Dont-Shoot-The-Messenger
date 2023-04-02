#ifndef CREW_H_
#define CREW_H_

#include "game_object.h"

namespace game {
	class Crew : public GameObject
	{
	public:
		Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time) override;


	};
}

#endif