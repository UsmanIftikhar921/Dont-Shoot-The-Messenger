#include "engine_power_gui_elem.h"
#include "textures.h"

namespace game {

	/* Background: */
	EnginePowerGuiBackground::EnginePowerGuiBackground(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("ship_status_power_selector_bg");
		SetScale(glm::vec2(0.15f, 0.3f));
		SetZLayer(-50);
	}
	void EnginePowerGuiBackground::Update(double delta_time, GuiState* gui_state) { GuiElem::Update(delta_time, gui_state); }
	void EnginePowerGuiBackground::ProcessInput(GuiState* gui_state) {}

	/* Top Green: */
	TopGreenElem::TopGreenElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_green")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, 0.118f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void TopGreenElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void TopGreenElem::ProcessInput(GuiState* gui_state) {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Top Orange */
	TopOrangeElem::TopOrangeElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_orange")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, 0.077f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void TopOrangeElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void TopOrangeElem::ProcessInput(GuiState* gui_state) {
		// If the user presses left click on the button, close the window
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Top Red: */
	TopRedElem::TopRedElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_red")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, 0.0375f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void TopRedElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void TopRedElem::ProcessInput(GuiState* gui_state) {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Grey: */
	GreyElem::GreyElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_grey")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, 0.0f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void GreyElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void GreyElem::ProcessInput(GuiState* gui_state) {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Bottom Red: */
	BottomRedElem::BottomRedElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_red")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, -0.0375f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void BottomRedElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void BottomRedElem::ProcessInput(GuiState* gui_state) {
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Bottom Orange: */
	BottomOrangeElem::BottomOrangeElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_orange")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, -0.077f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void BottomOrangeElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void BottomOrangeElem::ProcessInput(GuiState* gui_state) {
		// If the user presses left click on the button, close the window
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Bottom Green: */
	BottomGreenElem::BottomGreenElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(0.5, 0.5), GameObject::textures.GetTexture("ship_status_power_selector_green")) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		SetPosition(glm::vec3(0.001f, -0.118f, 0.0f));
		SetScale(glm::vec2(0.038, 0.036));
		SetZLayer(-60);
	}

	void BottomGreenElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void BottomGreenElem::ProcessInput(GuiState* gui_state) {
		// If the user presses left click on the button, close the window
		if (hover_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Functionality Goes Here:
		}
	}

	/* Selector: */
	SelectorElem::SelectorElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::GUI_ELEM;
	}

	void SelectorElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput(gui_state);
		GuiElem::Update(delta_time, gui_state);
	}

	void SelectorElem::ProcessInput(GuiState* gui_state) {

	}

} // namespace game