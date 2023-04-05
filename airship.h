#ifndef AIRSHIP_H_
#define AIRSHIP_H_

#include "game_object.h"
#include "airship_segment.h"
#include "engine.h"
#include "crew.h"
#include "gun.h"
#include "glm/ext.hpp"

namespace game {
	class Airship : public GameObject
	{
	public:
		Airship(const glm::vec3& position, Geometry* geom, Shader* shader);

		void Update(double delta_time, GuiState* gui_state) override;

		void InitSegments();

		void InitCrew();

		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) override;

		// Getters for segments
		inline AirshipSegment* GetPortGuns() { return port_guns_; }
		inline AirshipSegment* GetStarboardGuns() { return starboard_guns_; }
		inline AirshipSegment* GetBowGuns() { return bow_guns_; }
		inline AirshipSegment* GetSternGuns() { return stern_guns_; }
		inline Engine* GetPortEngine() { return port_engine_; }
		inline Engine* GetStarboardEngine() { return starboard_engine_; }
		inline AirshipSegment* GetBoilerRoom() { return boiler_room_; }

		// Getter for crew
		Crew* GetCrewMember(int index);
		std::vector<Crew*> GetCrewMembers() { return crew_members_; }

	protected:
		AirshipSegment* port_guns_;
		AirshipSegment* starboard_guns_;
		AirshipSegment* bow_guns_;
		AirshipSegment* stern_guns_;
		Engine* port_engine_;
		Engine* starboard_engine_;
		AirshipSegment* boiler_room_;

		std::vector<AirshipSegment*> segments_;

		std::vector<Crew*> crew_members_;
	};
}

#endif