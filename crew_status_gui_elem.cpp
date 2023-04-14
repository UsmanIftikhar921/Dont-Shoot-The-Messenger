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

		// Add Parts
		head = new ClickableHead(geom, shader, window);
		AddChild(head);

		front_body_left = new ClickableFrontBodyLeft(geom, shader, window);
		AddChild(front_body_left);

		front_body_right = new ClickableFrontBodyRight(geom, shader, window);
		AddChild(front_body_right);

		//left_tail = new ClickableLeftTail(geom, shader, window);
		//AddChild(left_tail);

		//right_tail = new ClickableRightTail(geom, shader, window);
		//AddChild(right_tail);

		//rear_outer = new ClickableRearOuter(geom, shader, window);
		//AddChild(rear_outer);

		//rear_inner = new ClickableRearInner(geom, shader, window);
		//AddChild(rear_inner);
	}

	void CrewStatusPositionElem::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void CrewStatusPositionElem::ProcessInput() {}


} // namespace game