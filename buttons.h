#ifndef CLOSE_BUTTON_GUI_ELEM_H_
#define CLOSE_BUTTON_GUI_ELEM_H_

#include "clickable_gui_elem.h"

namespace game {
	class CloseButtonGuiElem : public ClickableGuiElem {

	public:
		CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);

		void Update(double delta_time, GuiState* gui_state) override;

		virtual void ProcessInput() override;
	};
}

#endif