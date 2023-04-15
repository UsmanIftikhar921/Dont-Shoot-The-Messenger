#ifndef WORKSTATION_H
#define WORKSTATION_H

#include "game_object.h"
#include "crew.h"
#include "task.h"
#include <vector>

namespace game {
	class Workstation : public GameObject
	{
	public:
		Workstation(const glm::vec3& position, Geometry* geom, Shader* shader, Task* task);

		void Update(double delta_time, GuiState* gui_state) override;
		
		void AssignCrew(Crew* crew);
		void UnassignCrew();

		bool IsOccupied() { return occupied_; }
		Crew* GetCrew() { return crew_; }
		
	protected:
		bool occupied_;
		bool crew_arrived_;
		Crew* crew_;
		
		Task* task_object_;
	};
}


#endif