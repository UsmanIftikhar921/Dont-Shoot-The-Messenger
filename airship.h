#ifndef AIRSHIP_H_
#define AIRSHIP_H_

#include "game_object.h"
#include "airship_segment.h"
#include "crew.h"

namespace game {
	class Airship : public GameObject
	{
	public:
		Airship(const glm::vec3& position);

		void Update(double delta_time) override;

		void InitSegments(Geometry* geom, Shader* shader, std::vector<GLuint>* segment_textures);

		void InitCrew(Geometry* geom, Shader* shader, GLuint texture);


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