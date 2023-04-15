#include "engine.h"

namespace game {
	Engine::Engine(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float max_power, float rotation_multiplier) : AirshipSegment(position, geom, shader, texture)
	{
		max_power_ = max_power;
		current_max_power_ = max_power;
		target_power_ = 0.0f;
		power_ = 0.0f;
		
		rotation_multiplier_ = rotation_multiplier;
		rotation_factor_ = 0.0f;

		steam_pressure_ = 1.0f;
	}

	void Engine::Update(double delta_time, GuiState* gui_state)
	{
		CalculateCurrentMaxPower(steam_pressure_);
		CalculatePower();
		CalculateRotationFactor();
	}
	
	void Engine::CalculateCurrentMaxPower(float steam_pressure_)
	{
		float health_efficiency_modifier = (health_ * 0.5) + 0.5; // 0.5 to 1.0
		current_max_power_ = max_power_ * steam_pressure_ * health_efficiency_modifier;
	}

	void Engine::CalculatePower()
	{
		if (abs(target_power_) > abs(current_max_power_)) {
			if (target_power_ > 0) {
				power_ = current_max_power_;
			}
			else {
				power_ = -current_max_power_;
			}
		}
		else {
			power_ = target_power_;
		}
	}

	void Engine::CalculateRotationFactor()
	{
		rotation_factor_ = power_ * rotation_multiplier_;
	}
}