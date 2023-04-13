#include "gui_elem_collection.h"
#include <iostream>

namespace game {

	/* Gui inherits from GameObject */

	BackgroundGuiElem::BackgroundGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, glm::vec2 aspect_ratio) : GuiElem(geom, shader, window) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		texture_ = GameObject::textures.GetTexture("gui_background");
		scale_ = glm::vec2(aspect_ratio.x, aspect_ratio.y);
	}

	// Update function for moving the player object around
	void BackgroundGuiElem::Update(double delta_time, GuiState* gui_state) {

		// Call the parent's update method to move the object in standard way, if desired
		GuiElem::Update(delta_time, gui_state);
	}

	void BackgroundGuiElem::ProcessInput() {
		// Do nothing
	}

} // namespace game