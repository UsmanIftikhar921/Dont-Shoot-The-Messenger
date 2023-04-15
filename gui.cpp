#include "gui.h"
#include "wheel_gui_elem.h"
#include "buttons.h"
#include "gui_elem_collection.h"

namespace game {

	/* Gui inherits from GameObject */

	Gui::Gui(Geometry* geom, Shader* shader, GLFWwindow* window) : GameObject(glm::vec3(0.0f, 0.0f, 0.0f), geom, shader, NULL) {
		type_ = ObjType::GUI;
		window_ = window;

		InitGui();
	}

	// Update function for moving the player object around
	void Gui::Update(double delta_time, GuiState* gui_state) {
		GameObject::Update(delta_time, gui_state);
	}

	void Gui::InitGui() {
		// Create a close button gui clickable element
		CloseButtonGuiElem* quit_button = new CloseButtonGuiElem(geometry_, shader_, window_);
		AddGuiElem(quit_button);

		// Create a background gui element
		BackgroundGuiElem* background = new BackgroundGuiElem(geometry_, shader_, window_);
		AddGuiElem(background);

		// Create a crew gui element
		CrewGuiElem* crew1 = new CrewGuiElem(geometry_, shader_, window_);
		AddGuiElem(crew1);

		CrewGuiElem* crew2 = new CrewGuiElem(geometry_, shader_, window_);
		AddGuiElem(crew2);

		CrewGuiElem* crew3 = new CrewGuiElem(geometry_, shader_, window_);
		AddGuiElem(crew3);

		CrewGuiElem* crew4 = new CrewGuiElem(geometry_, shader_, window_);
		AddGuiElem(crew4);
	}

	void Gui::AddGuiElem(GuiElem* elem) {
		gui_elems_.push_back(elem);
		AddChild(elem);
	}

} // namespace game