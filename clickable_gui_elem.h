#ifndef CLICKABLE_GUI_ELEM_H_
#define CLICKABLE_GUI_ELEM_H_

#include "gui_elem.h"

namespace game {
	class ClickableGuiElem : public GuiElem
	{
	public:
		ClickableGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window, glm::vec2 aspect_ratio, GLuint texture);

		void Update(double delta_time, GuiState* gui_state) override;

		bool MouseOnGuiElem();

		bool getHover() { return hover_; }
		void setHover(bool hover) { hover_ = hover; }

	protected:
		glm::vec2 aspect_ratio_;
		bool hover_;

		glm::vec2 GetMousePos();
		glm::vec2 GetWindowSize();
	};
}

#endif