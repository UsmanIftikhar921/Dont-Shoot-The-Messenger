#include "close_button_gui_elem.h"

namespace game {

	/* Gui inherits from Gui Elem */

	CloseButtonGuiElem::CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::OBJ;
	}


	// Update function for moving the player object around
	void GuiElem::Update(double delta_time, GuiState gui_state) {

		if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window_, true);
		}

		// Call the parent's update method to move the object in standard way, if desired
		GuiElem::Update(delta_time, gui_state);
	}

} // namespace game