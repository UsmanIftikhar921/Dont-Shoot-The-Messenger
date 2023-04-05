#include "wheel_gui_elem.h"

namespace game {

	/* Gui inherits from Gui Elem */

	WheelGuiElem::WheelGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window) : GuiElem(geom, shader, window) {
		type_ = ObjType::OBJ;
	}


	// Update function for moving the player object around
	void WheelGuiElem::Update(double delta_time, GuiState* gui_state) {

		// Call the parent's update method to move the object in standard way, if desired
		GuiElem::Update(delta_time, gui_state);
	}

} // namespace game