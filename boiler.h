#ifndef BOILER_H_
#define BOILER_H_

#include "game_object.h"
#include "airship_segment.h"
#include <vector>

namespace game {
	class Boiler : public AirshipSegment
	{
	public:
		Boiler(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
		
		//void Update(double delta_time, GuiState* gui_state) override;

		
	protected:
		float steam_pressure_;
		float steam_pressure_loss_rate_;

	};
}

#endif