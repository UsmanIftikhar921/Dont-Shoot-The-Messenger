#include "boiler.h"

namespace game {
	Boiler::Boiler(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture) : AirshipSegment(position, geom, shader, texture)
	{
		steam_pressure_ = 1.0f;
		steam_pressure_loss_rate_ = 0.1f;
	}
	
}