#ifndef CLICKABLE_GUI_ELEM_H_
#define CLICKABLE_GUI_ELEM_H_

#include "gui_elem.h"

namespace game {
	class ClickableGuiElem : public GuiElem
	{
	public:
		ClickableGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, glm::vec2 dimensions, GLuint texture);

		void Update(double delta_time, GuiState* gui_state) override;

		// Check if you are clicking on the gui element
		bool GuiElemIsClicked();


	protected:
		// Dimensions of GUI Element
		glm::vec2 dimensions_;
		bool clicked_;

		glm::vec2 GetMousePos();
		glm::vec2 GetWindowSize();
	};
}

#endif