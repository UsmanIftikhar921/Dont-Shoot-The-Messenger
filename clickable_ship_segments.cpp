#include "clickable_ship_segments.h"
#include "textures.h"

namespace game {

	/* Head: */
	ClickableHead::ClickableHead(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_head")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.075f, 0.09f, 0.0f));
		SetScale(glm::vec2(0.1, 0.1));
	}

	void ClickableHead::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableHead::ProcessInput() {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Front Body (Left) */
	ClickableFrontBodyLeft::ClickableFrontBodyLeft(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_front_body")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.06f, 0.015f, 0.0f));
		SetScale(glm::vec2(0.05, 0.15));
	}

	void ClickableFrontBodyLeft::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableFrontBodyLeft::ProcessInput() {
		// If the user presses left click on the button, close the window
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Front Body (Right): */
	ClickableFrontBodyRight::ClickableFrontBodyRight(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_front_body")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.09f, 0.015f, 0.0f));
		SetScale(glm::vec2(0.05, 0.15));
	}

	void ClickableFrontBodyRight::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableFrontBodyRight::ProcessInput() {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Left Tail: */
	ClickableLeftTail::ClickableLeftTail(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_left_tail")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.015f, -0.075f, 0.0f));
		SetScale(glm::vec2(0.1, 0.15));
	}

	void ClickableLeftTail::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableLeftTail::ProcessInput() {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Right Tail: */
	ClickableRightTail::ClickableRightTail(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_right_tail")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.135f, -0.075f, 0.0f));
		SetScale(glm::vec2(0.1, 0.15));
	}

	void ClickableRightTail::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableRightTail::ProcessInput() {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Rear Outer: */
	ClickableRearOuter::ClickableRearOuter(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_rear_outer")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.075f, -0.06f, 0.0f));
		SetScale(glm::vec2(0.1, 0.1));
		SetZLayer(-10);
	}

	void ClickableRearOuter::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableRearOuter::ProcessInput() {
		// If the user presses left click on the button, close the window
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Rear Inner: */
	ClickableRearInner::ClickableRearInner(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_rear_inner")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.075f, -0.08f, 0.0f));
		SetScale(glm::vec2(0.05, 0.05));
		SetZLayer(-10);
	}

	void ClickableRearInner::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableRearInner::ProcessInput() {
		// If the user presses left click on the button, close the window
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Rear: */
	ClickableRear::ClickableRear(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		rear_outer_ = new ClickableRearOuter(geom, shader, window);
		AddChild(rear_outer_);
		rear_inner_ = new ClickableRearInner(geom, shader, window);
		AddChild(rear_inner_);
	}

	void ClickableRear::Update(double delta_time, GuiState* gui_state) {
		GuiElem::Update(delta_time, gui_state);	

		bool innerHover = rear_inner_->getHover();
		bool outerHover = rear_outer_->getHover();

		if (innerHover && outerHover) { rear_outer_->setHover(false); }

		ProcessInput();

	}

	void ClickableRear::ProcessInput() {
		rear_inner_->ProcessInput();
		rear_outer_->ProcessInput();
	}

} // namespace game