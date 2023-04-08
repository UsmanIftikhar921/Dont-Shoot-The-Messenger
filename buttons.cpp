#include "buttons.h"
#include "textures.h"

namespace game {

	/* Close Button */

	CloseButtonGuiElem::CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : ClickableGuiElem(geom, shader, window, glm::vec2(1,1), GameObject::textures.GetTexture("close_button")) {
		type_ = ObjType::GUI_ELEM;

		// Set Position to top right corner
		SetPosition(glm::vec3(0.95f, 0.95f, 0.0f));
		SetScale(glm::vec2(0.1, 0.1));
	}

	void CloseButtonGuiElem::Update(double delta_time, GuiState* gui_state) {
		ProcessInput();
		ClickableGuiElem::Update(delta_time, gui_state);
	}

	void CloseButtonGuiElem::ProcessInput() {
		// If the user presses left click on the button, close the window
		if (clicked_ && glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window_, true);
		}
	}

} // namespace game