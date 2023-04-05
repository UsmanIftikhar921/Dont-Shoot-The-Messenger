#include "gui.h"
#include "wheel_gui_elem.h"
#include "close_button_gui_elem.h"

namespace game {

	/* Gui inherits from GameObject */

	Gui::Gui(Geometry* geom, Shader* shader, GLFWwindow* window) : GameObject(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, NULL) {
		type_ = ObjType::OBJ;

		// Construct GUI Element for wheel
		//WheelGuiElem* wheel = new WheelGuiElem(geom, shader, window);
		//addGuiElem(wheel);
		//AddChild(wheel);

		// Construct GUI Element for quit button
		CloseButtonGuiElem* quit_button = new CloseButtonGuiElem(geom, shader, window);
		addGuiElem(quit_button);
		AddChild(quit_button);
	}

	// Update function for moving the player object around
	void Gui::Update(double delta_time, GuiState* gui_state) {
		GameObject::Update(delta_time, gui_state);
	}

	void Gui::addGuiElem(GuiElem* elem) {
		gui_elems_.push_back(elem);
	}

} // namespace game