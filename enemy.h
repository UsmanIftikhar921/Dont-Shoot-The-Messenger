#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"
#include "collidable.h"
#include <glm/gtc/matrix_transform.hpp>
#include <random>



namespace game {

	enum EnemyState {
		CHASE,
		HOME_IN,
		ORBIT,
		WAIT,
		FIRE,
	};

	class Enemy : public Collidable {
	public:
		Enemy(const glm::vec3& positiong, Geometry* geom, Shader* shader, GameObject* target);

		void Update(double delta_time, GuiState* gui_state) override;

		virtual void StateTransitionHandler(double delta_time);

		void StateHandler(double delta_time);

		// Getters
		inline GameObject* GetTarget(void) { return target_; }

		// Setters
		inline void SetTarget(GameObject* target) { target_ = target; }

		bool HomeInOnPoint(glm::vec3 target_position, glm::vec3 target_velocity, double delta_time);



		// State Functions
		void ChaseTarget(float delta_time);
		void HomeInOnTarget(float delta_time);
		void OrbitTarget(float delta_time);
		void Wait(float delta_time);
		virtual void FireOnTarget(float delta_time);


		// State Enter functions
		void EnterChaseState(void);
		void EnterHomeInState(void);
		void EnterOrbitState(float period, float radius, float initial_orbit, float final_orbit);
		void EnterWaitState(void);
		void EnterFireState(void);

		void HandleCollisionEvent(CollisionEvent& event) override;

		void HandleNewCollisionEvent(CollisionEvent& event) override;

	protected:
		GameObject* target_;

		glm::vec3 target_pos_;

		EnemyState state_;

		// Orbit state variables
		float orbit_period_;
		float orbit_radius_;
		float orbit_initial_angle_;
		float orbit_final_angle_;
		float t_orbit_;
		bool orbit_completed_;
		bool orbit_enemy_arrived_;

		// Fire state variables
		glm::vec3 relative_firing_position_;
		int shots_fired_;
		int total_shots_;

		// Debugging
		bool display_debug_pos_;
		GameObject* debug_object_;
		GLuint debug_pos_texture_;


	};

}





#endif
