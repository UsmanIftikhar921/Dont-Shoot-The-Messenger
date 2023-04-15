#include "gui_elem_collection.h"
#include <iostream>

namespace game {

	/* Background GUI Element */
	BackgroundGuiElem::BackgroundGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("gui_background");
		SetScale(glm::vec2(2.0f, 2.0f));
	}

	void BackgroundGuiElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void BackgroundGuiElem::ProcessInput() {}

	/* Crew GUI Element: */
	int CrewGuiElem::crew_count = 0;
	CrewGuiElem::CrewGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		SetScale(glm::vec2(0.6f, 0.6f));
		SetPosition(glm::vec3(-0.835f, 0.8f - (0.3 * crew_count), 0.0f));
		crew_count++;

		crew_status_position_elem_ = new CrewStatusPositionElem(geom, shader, window);
		AddChild(crew_status_position_elem_);
		crew_status_health_elem_ = new CrewStatusHealthElem(geom, shader, window);
		AddChild(crew_status_health_elem_);	
		crew_status_bg_elem_ = new CrewStatusBgElem(geom, shader, window);
		AddChild(crew_status_bg_elem_);
	}

	void CrewGuiElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void CrewGuiElem::ProcessInput() {}

} // namespace game