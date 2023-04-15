#ifndef ENGINE_H_
#define ENGINE_H_

#include "game_object.h"
#include "airship_segment.h"
#include <vector>

namespace game {
	class Engine : public AirshipSegment
	{
	public:
		Engine(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float max_power, float rotation_factor);

		void Update(double delta_time, GuiState* gui_state);

		//Getters
		float GetMaxPower() { return max_power_; }
		float GetCurrentMaxPower() { return current_max_power_; }
		float GetTargetPower() { return target_power_; }
		float GetPower() { return power_; }
		float GetRotationMultiplier() { return rotation_multiplier_; }
		float GetRotationFactor() { return rotation_factor_; }

		//Setters
		void SetMaxPower(float max_power) { max_power_ = max_power; }
		void SetTargetPower(float target_power) { target_power_ = target_power; }
		void SetRotationMultiplier(float rotation_multiplier) { rotation_multiplier_ = rotation_multiplier; }
		


	protected:
		void CalculateCurrentMaxPower(float steam_pressure_);
		void CalculatePower();
		void CalculateRotationFactor();

		// Crew 
		float max_power_;
		float current_max_power_;
		float target_power_;
		float power_;
		
		float rotation_multiplier_;
		float rotation_factor_;

		
		
	};
}

#endif