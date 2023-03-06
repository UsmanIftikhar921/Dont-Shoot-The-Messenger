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


	protected:
		AirshipSegment* port_guns_;
		AirshipSegment* starboard_guns_;
		AirshipSegment* port_engine_;
		AirshipSegment* starboard_engine_;
		AirshipSegment* bow_gun_;
		AirshipSegment* boiler_room_;
		AirshipSegment* stern_guns_;
	};
}

#endif