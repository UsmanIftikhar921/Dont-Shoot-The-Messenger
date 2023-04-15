#include "gui_elem_collection.h"
#include "engine_power_gui_elem.h"
#include <iostream>

namespace game {

	/* Background GUI Element */
	BackgroundGuiElem::BackgroundGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("gui_background");
		SetScale(glm::vec2(2.0f, 2.0f));
	}

	void BackgroundGuiElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void BackgroundGuiElem::ProcessInput(GuiState* gui_state) {}

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
	void CrewGuiElem::ProcessInput(GuiState* gui_state) {}

	/* Engine Power GUI Element: */
	EnginePowerGuiElem::EnginePowerGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;

		engine_power_gui_background_ = new EnginePowerGuiBackground(geom, shader, window);
		AddChild(engine_power_gui_background_);

		top_green_elem_ = new TopGreenElem(geom, shader, window);
		AddChild(top_green_elem_);
		top_orange_elem_ = new TopOrangeElem(geom, shader, window);
		AddChild(top_orange_elem_);
		top_red_elem_ = new TopRedElem(geom, shader, window);
		AddChild(top_red_elem_);
		grey_elem_ = new GreyElem(geom, shader, window);
		AddChild(grey_elem_);
		bottom_red_elem_ = new BottomRedElem(geom, shader, window);
		AddChild(bottom_red_elem_);
		bottom_orange_elem_ = new BottomOrangeElem(geom, shader, window);
		AddChild(bottom_orange_elem_);
		bottom_green_elem_ = new BottomGreenElem(geom, shader, window);
		AddChild(bottom_green_elem_);
	}

	void EnginePowerGuiElem::Update(double delta_time, GuiState* gui_state) { 
		GuiElem::Update(delta_time, gui_state);
		ProcessInput(gui_state);
	}
	void EnginePowerGuiElem::ProcessInput(GuiState* gui_state) {
		// If the user presses left click on the button, close the window
		if (top_green_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			top_green_elem_->SetColorModifier(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (top_orange_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			top_orange_elem_->SetColorModifier(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (top_red_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			top_red_elem_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (grey_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			grey_elem_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (bottom_red_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			bottom_red_elem_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (bottom_orange_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			bottom_orange_elem_->SetColorModifier(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (bottom_green_elem_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			bottom_green_elem_->SetColorModifier(glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}


} // namespace game