#ifndef CREW_H_
#define CREW_H_

#include "game_object.h"
#include "gui_state.h"

namespace game {
	
	enum ActivityState {
		IDLE,
		MOVING,
		DOING_TASK,
	};

	class Crew : public GameObject
	{
	public:
		Crew(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time, GuiState* gui_state) override;

		inline bool GetAlive() { return alive_; }
		inline float GetHealth() { return health_; }
		inline bool GetEfficiency() { return efficiency_; }

		inline void SetAlive(bool alive) { alive_ = alive; }
		inline void SetHealth(float health) { health_ = health; }
		inline void SetEfficiency(float efficiency) { efficiency_ = efficiency; }

		

		void SetDestination(glm::vec3 destination);
		ActivityState GetActivityState() { return activity_state_; }

//		void Render(glm::mat4 view_matrix, glm::mat4 parent_matrix, glm::mat4 parent_scale_matrix, double current_time) override;


	protected:
		bool alive_;
		float health_;
		float efficiency_;
		ActivityState activity_state_;

		glm::vec3 destination_;
		float t_;
		float speed_;
		glm::vec3 destination_vector_;



	};

}

#endif