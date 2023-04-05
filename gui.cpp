#include "gui.h"
#include "wheel_gui_elem.h"
#include "close_button_gui_elem.h"

namespace game {

	/* Gui inherits from GameObject */

	Gui::Gui(Geometry* geom, Shader* shader, GLFWwindow* window, GuiState* gui_state) : GameObject(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, NULL) {
		type_ = ObjType::OBJ;
		gui_state_ = gui_state;

		// Construct GUI Element for wheel
		WheelGuiElem* wheel = new WheelGuiElem(geom, shader, window);
		addGuiElem(wheel);
		AddChild(wheel);

		// Construct GUI Element for quit button

	}

	// Update function for moving the player object around
	void Gui::Update(double delta_time, GuiState* gui_state) {
		// Special GUI Updates go here:
		

		GameObject::Update(delta_time, gui_state);
	}

	void Gui::addGuiElem(GuiElem* elem) {
		gui_elems_.push_back(elem);
	}

} // namespace game