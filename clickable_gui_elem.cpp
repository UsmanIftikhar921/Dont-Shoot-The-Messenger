#include "clickable_gui_elem.h"
#include <iostream>

namespace game {

	/* Gui inherits from GameObject */

	ClickableGuiElem::ClickableGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, glm::vec2 aspect_ratio, GLuint texture) : GuiElem(geom, shader, window) {
		type_ = ObjType::CLICKABLE_GUI_ELEM;
		texture_ = texture;

		//int width, height;
		//glfwGetWindowSize(window_, &width, &height);

		// Set aspect ratio according to scale in comparison to the window
		aspect_ratio_ = glm::vec2(aspect_ratio.x, aspect_ratio.y);
		
		// Set Scale According to Dimensions
		//SetScale(glm::vec2(0.25, 0.25));
		
		clicked_ = false;
	}

	// Update function for moving the player object around
	void ClickableGuiElem::Update(double delta_time, GuiState* gui_state) {

		// Check if you are clicking on the gui element
		if (GuiElemIsClicked()) { 
			clicked_ = true;
		}
		else { 
			clicked_ = false;
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

	bool ClickableGuiElem::GuiElemIsClicked() {

		glm::vec2 mouse_pos = GetMousePos();

		// Get GUI Element's position
		glm::vec3 gui_pos = GetPosition();

		// Define range of values where the GUI Element lies
		float x_range_min;
		float x_range_max;
		float y_range_min;
		float y_range_max;

		// Find Range of values on the window where the GUI Element lies
		x_range_min = gui_pos.x - (scale_.x * aspect_ratio_.x / 2) ;
		x_range_max = gui_pos.x + (scale_.x * aspect_ratio_.x / 2) ;
		y_range_min = gui_pos.y - (scale_.y * aspect_ratio_.y / 2) ;
		y_range_max = gui_pos.y + (scale_.y * aspect_ratio_.y / 2) ;

		// Check if you are clicking on the gui element (assuming it's a rectangle)
		if (mouse_pos.x > x_range_min && mouse_pos.x < x_range_max && mouse_pos.y > y_range_min && mouse_pos.y < y_range_max) {
			return true;
		}
		else {
			return false;
		}
	}

} // namespace game