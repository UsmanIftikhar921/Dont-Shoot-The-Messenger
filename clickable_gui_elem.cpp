#include "clickable_gui_elem.h"
#include <iostream>

namespace game {

	/* Gui inherits from GameObject */

	ClickableGuiElem::ClickableGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, glm::vec2 aspect_ratio, GLuint texture) : GuiElem(geom, shader, window) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		texture_ = texture;
		hover_ = false;
		aspect_ratio_ = aspect_ratio;
	}

	// Update function for moving the player object around
	void ClickableGuiElem::Update(double delta_time, GuiState* gui_state) {

		// Check if you are clicking on the gui element
		if (MouseOnGuiElem()) { 
			hover_ = true;
		}
		else { 
			hover_ = false;
		}

		// Call the parent's update method to move the object in standard way, if desired
		GuiElem::Update(delta_time, gui_state);
	}

	glm::vec2 ClickableGuiElem::GetMousePos() {
		double xpos, ypos;
		glfwGetCursorPos(window_, &xpos, &ypos);

		// Make sure the mouse position is in the range of the window
		int width, height;
		glfwGetWindowSize(window_, &width, &height);

		if (xpos < 0) { xpos = 0; }
		if (xpos > width) { xpos = width; }
		if (ypos < 0) { ypos = 0; }
		if (ypos > height) { ypos = height; }

		// Set the mouse position to be in the range of -1 to 1 (left is -1, right is 1)
		xpos = (xpos / width) * 2 - 1;
		ypos = - ( (ypos / height) * 2 - 1 );

		return glm::vec2(xpos, ypos);
	}

	glm::vec2 ClickableGuiElem::GetWindowSize() {
		int width, height;
		glfwGetWindowSize(window_, &width, &height);
		return glm::vec2(width, height);
	}

	bool ClickableGuiElem::MouseOnGuiElem() {
		// Should work on images with transparent backgrounds
		glm::vec2 mouse_pos = GetMousePos();
		glm::vec2 window_size = GetWindowSize();

		// Get the position of the gui element
		
		glm::vec2 gui_elem_pos = glm::vec2(GetGlobalPosition());

		// Get the size of the gui element
		glm::vec2 gui_elem_size = glm::vec2(aspect_ratio_.x * scale_.x, aspect_ratio_.y * scale_.y);

		// Check if the mouse is within the gui element
		if (mouse_pos.x > gui_elem_pos.x - gui_elem_size.x / 2 && mouse_pos.x < gui_elem_pos.x + gui_elem_size.x / 2 &&
			mouse_pos.y > gui_elem_pos.y - gui_elem_size.y / 2 && mouse_pos.y < gui_elem_pos.y + gui_elem_size.y / 2) {
			return true;
		}
		else {
			return false;
		}
	}

} // namespace game