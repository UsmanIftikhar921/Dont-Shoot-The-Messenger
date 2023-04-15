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
	void CrewStatusBgElem::ProcessInput(GuiState* gui_state) {}

	/* Health: */
	int CrewStatusHealthElem::NumOfCrewGuiElems = 0;
	CrewStatusHealthElem::CrewStatusHealthElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("crew_status_health");
		SetPosition(glm::vec3(-0.1f,0.0f,0.0f));
		SetScale(glm::vec2(0.1f, 0.15f));
		SetZLayer(-50);
		crew_gui_num_ = NumOfCrewGuiElems;
		NumOfCrewGuiElems++;
	}
	void CrewStatusHealthElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void CrewStatusHealthElem::ProcessInput(GuiState* gui_state) {}

	/* Crew Position: */
	int CrewStatusPositionElem::NumOfCrewGuiElems = 0;
	CrewStatusPositionElem::CrewStatusPositionElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		SetZLayer(-75);
		SetPosition(glm::vec3(-0.03f, 0.0f, 0.0f));
		crew_gui_num_ = NumOfCrewGuiElems;
		NumOfCrewGuiElems++;

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
		ProcessInput(gui_state);
	}

	// You DO NOT want to look at whatever lies within...
	void CrewStatusPositionElem::ProcessInput(GuiState* gui_state) {
		// If the user presses left click on the button, close the window
		if (head_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			head_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));

			// Change all others to original color
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::BOW;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
		else if (front_body_left_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			front_body_left_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::PORT_GUNS;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
		else if (front_body_right_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			front_body_right_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::STARBOARD_GUNS;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
		else if (rear_->GetRearInner()->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			rear_->GetRearInner()->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::BOILER;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
		else if (rear_->GetRearOuter()->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::STERN_GUNS;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
		else if (right_tail_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			right_tail_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			left_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::STARBOARD_ENGINE;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
		else if (left_tail_->getHover() && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Change to green
			left_tail_->SetColorModifier(glm::vec3(0.0f, 1.0f, 0.0f));
			// Change all others to original color
			head_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_left_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			front_body_right_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearInner()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			rear_->GetRearOuter()->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));
			right_tail_->SetColorModifier(glm::vec3(1.0f, 1.0f, 1.0f));

			// Get crew data vector from gui_state
			std::vector<CrewData> crew_data = gui_state->GetCrewDataVec();
			// Set the crew's assigned segment to the one that was clicked
			crew_data.at(crew_gui_num_).assigned_segment = Segment::PORT_ENGINE;
			// Pass the updated crew data vector back to gui_state
			gui_state->SetCrewDataVec(crew_data);
		}
	}


} // namespace game