#ifndef CLOSE_BUTTON_GUI_ELEM_H_
#define CLOSE_BUTTON_GUI_ELEM_H_

#include "clickable_gui_elem.h"

namespace game {

	/* Close Button: */
	class CloseButtonGuiElem : public ClickableGuiElem {

	public:
		CloseButtonGuiElem(Geometry* geom, Shader* shader, GLFWwindow* window);

		void Update(double delta_time, GuiState* gui_state) override;

		virtual void ProcessInput() override;
	};

	/* Other Button Class Definitions Go Here: */

}

#endif