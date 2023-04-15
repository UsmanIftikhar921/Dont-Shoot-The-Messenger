#ifndef AIRSHIP_SEGMENT_H_
#define AIRSHIP_SEGMENT_H_

#include "game_object.h"
#include "collidable.h"
#include "crew.h"
#include "workstation.h"
#include <vector>

namespace game {
	class AirshipSegment : public Collidable
	{
	public:
		AirshipSegment(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time, GuiState* gui_state) override;

		bool AssignCrew(Crew* crew);
		bool UnassignCrew(Crew* crew);
		bool HasCrew(Crew* crew);

		void SetCrewDestination(Crew* crew, Workstation* workstation);

		void HandleCollisionEvent(CollisionEvent& event) override;
		void HandleNewCollisionEvent(CollisionEvent& event) override;

		void AddWorkstation(Workstation* workstation);
		bool RemoveWorkstation(Workstation* workstation);

		bool GetDisable() { return disable_; }
		void SetDisable(bool disable);

		bool powerup_pickup;
		
	protected:
		// Crew 
		int num_workstations_;
		std::vector<Workstation*> workstations_;

		float health_;
		bool disable_;
		

	};
}

#endif