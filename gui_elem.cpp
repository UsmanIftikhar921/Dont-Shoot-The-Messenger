#include "gui_elem.h"

namespace game {

	/* Gui inherits from GameObject */

	GuiElem::GuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, GLuint texture) : GameObject(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, texture) {
		type_ = ObjType::GUI_ELEM;
		window_ = window;
	}

	// Update function for moving the player object around
	void GuiElem::Update(double delta_time, GuiState* gui_state) {


		// Call the parent's update method to move the object in standard way, if desired
		GameObject::Update(delta_time, gui_state);
	}

} // namespace game