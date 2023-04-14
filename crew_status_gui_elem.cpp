#include "crew_status_gui_elem.h"
#include <iostream>

namespace game {

	/* Background: */
	CrewStatusBgElem::CrewStatusBgElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("crew_status_bg");
		SetScale(glm::vec2(0.5f, 1.0f));
		SetZLayer(-50);
	}
	void CrewStatusBgElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void CrewStatusBgElem::ProcessInput() {}

	/* Health: */
	CrewStatusHealthElem::CrewStatusHealthElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("crew_status_health");
		SetPosition(glm::vec3(-0.1f,0.0f,0.0f));
		SetScale(glm::vec2(0.1f, 0.15f));
		SetZLayer(-50);
	}
	void CrewStatusHealthElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void CrewStatusHealthElem::ProcessInput() {}

	/* Crew Position: */
	CrewStatusPositionElem::CrewStatusPositionElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		SetZLayer(-75);
		SetPosition(glm::vec3(-0.03f, 0.0f, 0.0f));

		// Add Parts
		head_ = new ClickableHead(geom, shader, window);
		AddChild(head_);

		front_body_left_ = new ClickableFrontBodyLeft(geom, shader, window);
		AddChild(front_body_left_);

		front_body_right_ = new ClickableFrontBodyRight(geom, shader, window);
		AddChild(front_body_right_);

		rear_ = new ClickableRear(geom, shader, window);
		AddChild(rear_);

		left_tail_ = new ClickableLeftTail(geom, shader, window);
		AddChild(left_tail_);

		right_tail_ = new ClickableRightTail(geom, shader, window);
		AddChild(right_tail_);
	}

	void CrewStatusPositionElem::Update(double delta_time, GuiState* gui_state) { 
		GuiElem::Update(delta_time, gui_state);
		ProcessInput();
	}
	void CrewStatusPositionElem::ProcessInput() {
		// If the user presses left click on the button, close the window
		if (head_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);

			// Change all others to original color
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (front_body_left_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (front_body_right_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (rear_->GetRearInner()->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (rear_->GetRearOuter()->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (right_tail_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (left_tail_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			color_modifier_ = glm::vec3(0.0f, 1.0f, 0.0f);
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}


} // namespace game