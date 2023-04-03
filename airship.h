#ifndef AIRSHIP_H_
#define AIRSHIP_H_

#include "game_object.h"
#include "airship_segment.h"
#include "crew.h"
#include "glm/ext.hpp"

namespace game {
	class Airship : public GameObject
	{
	public:
		Airship(const glm::vec3& position, Geometry* geom, Shader* shader);

		void Update(double delta_time) override;

		void InitSegments();

		void InitCrew();

		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) override;


	protected:
		AirshipSegment* port_guns_;
		AirshipSegment* starboard_guns_;
		AirshipSegment* bow_guns_;
		AirshipSegment* stern_guns_;
		AirshipSegment* port_engine_;
		AirshipSegment* starboard_engine_;
		AirshipSegment* boiler_room_;

		std::vector<AirshipSegment*> segments_;

		std::vector<Crew*> crew_members_;
	};
}

#endif