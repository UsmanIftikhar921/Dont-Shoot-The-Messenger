#include "close_button_gui_elem.h"
#include "textures.h"

namespace game {

	/* Gui inherits from Gui Elem */

	CloseButtonGuiElem::CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(1,1), GameObject::textures.GetTexture("close_button")) {
		type_ = ObjType::GUI_ELEM;

		// Set Position to top right corner
		SetPosition(glm::vec3(0.94f, 0.94f, 0.0f));
		SetScale(glm::vec2(0.15, 0.15));
	}


	// Update function for moving the player object around
	void CloseButtonGuiElem::Update(double delta_time, GuiState* gui_state) {
		// Process input
		ProcessInput();

		// Call the parent's update method to move the object in standard way, if desired
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void CloseButtonGuiElem::ProcessInput() {
		// If clicked_ is true, and the user presses left click, close the window
		if (clicked_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window_, true);
		}
	}

} // namespace game