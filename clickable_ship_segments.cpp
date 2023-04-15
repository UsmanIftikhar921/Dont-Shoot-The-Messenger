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
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableHead::ProcessInput(GuiState* gui_state) {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Do something
		}
	}

	/* Front Body (Left) */
	ClickableFrontBodyLeft::ClickableFrontBodyLeft(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_segment_front_body")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.06f, 0.015f, 0.0f));
		SetScale(glm::vec2(0.05, 0.15));
	}

	void ClickableFrontBodyLeft::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableFrontBodyLeft::ProcessInput(GuiState* gui_state) {
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
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableFrontBodyRight::ProcessInput(GuiState* gui_state) {
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
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableLeftTail::ProcessInput(GuiState* gui_state) {
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
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableRightTail::ProcessInput(GuiState* gui_state) {
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
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableRearOuter::ProcessInput(GuiState* gui_state){
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
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void ClickableRearInner::ProcessInput(GuiState* gui_state) {
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

		ProcessInput(gui_state);

	}

	void ClickableRear::ProcessInput(GuiState* gui_state) {
		rear_inner_->ProcessInput(gui_state);
		rear_outer_->ProcessInput(gui_state);
	}

} // namespace game