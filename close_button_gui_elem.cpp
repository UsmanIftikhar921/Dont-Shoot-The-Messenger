#include "close_button_gui_elem.h"
#include "textures.h"

namespace game {

	/* Gui inherits from Gui Elem */

	CloseButtonGuiElem::CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(512,512), GameObject::textures.GetTexture("close_button")) {
		type_ = ObjType::GUI_ELEM;
	}


	// Update function for moving the player object around
	void CloseButtonGuiElem::Update(double delta_time, GuiState* gui_state) {

		// Process input
		ProcessInput();

		// Call the parent's update method to move the object in standard way, if desired
		GuiElem::Update(delta_time, gui_state);
	}

	void CloseButtonGuiElem::ProcessInput() {
		if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) { glfwSetWindowShouldClose(window_, true); }
	}

} // namespace game