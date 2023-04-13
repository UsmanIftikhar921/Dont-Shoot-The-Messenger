#ifndef TASK_H_
#define TASK_H_

#include "game_object.h"
#include <vector>

namespace game {

	class Task : public GameObject {

	public:
		Task(const glm::vec3& position, Geometry* geom, Shader* shader, float completion_time_);

		void Update(double delta_time) override;
		
		virtual void PerformTask(float efficiency_modifier) = 0;

		void ResetTask();

		inline bool GetReady() { return ready_; }
		
		
	
	protected:
		float completion_time_;
		float cooldown_timer_;
		float efficiency_modifier_;
		bool ready_;
	};
}

#endif